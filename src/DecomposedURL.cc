/*****************************************************************************
 * DASH MPD parsing library in C++: DecomposedURL class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <ctype.h>
#include <stdint.h>

#include <algorithm>
#include <iterator>
#include <list>
#include <sstream>
#include <string>

#include "libmpd++/macros.hh"
#include "libmpd++/exceptions.hh"

#include "DecomposedURL.hh"

LIBMPDPP_NAMESPACE_BEGIN

/**************************************************************************
 * helper functions
 **************************************************************************/

#define _RESERVED_CHARS_GENERIC_DELIMITERS ":/?#[]@"
#define _RESERVED_CHARS_SUBCOMPONENT_DELIMITERS "!$&'()*+,;="
#define _RESERVED_CHARS_ALLOWED_IN_PATH_ELEMENT _RESERVED_CHARS_SUBCOMPONENT_DELIMITERS ":@"
#define _RESERVED_CHARS_ALLOWED_IN_PATH _RESERVED_CHARS_ALLOWED_IN_PATH_ELEMENT "/"
#define _RESERVED_CHARS_ALLOWED_IN_USERINFO _RESERVED_CHARS_SUBCOMPONENT_DELIMITERS ":"

static std::string _uri_char_to_pct_encode(unsigned char c)
{
    const char hex_chars[] = "0123456789ABCDEF";
    std::string ret("%");
    ret += hex_chars[c>>4];
    ret += hex_chars[c&0xF];
    return ret;
}

static std::string _uri_escape_string(const std::string &unescaped, const std::string &allowed_chars)
{
    static const std::string reserved_chars(_RESERVED_CHARS_GENERIC_DELIMITERS _RESERVED_CHARS_SUBCOMPONENT_DELIMITERS);
    std::string ret;

    for (std::string::const_iterator c = unescaped.begin();
         c != unescaped.end();
         ++c) {
        if (reserved_chars.find_first_of(*c) != std::string::npos &&
            allowed_chars.find_first_of(*c) == std::string::npos) {
            ret += _uri_char_to_pct_encode(*c);
        }
        else {
            ret += *c;
        }
    }

    return ret;
}

static std::string _uri_escape_userinfo(const std::string &unescaped)
{
    return _uri_escape_string(unescaped, _RESERVED_CHARS_ALLOWED_IN_USERINFO);
}

static std::string _uri_escape_host(const std::string &unescaped)
{
    return _uri_escape_string(unescaped, _RESERVED_CHARS_SUBCOMPONENT_DELIMITERS);
}

static std::string _uri_escape_host_colon(const std::string &unescaped)
{
    return _uri_escape_string(unescaped, _RESERVED_CHARS_SUBCOMPONENT_DELIMITERS ":");
}

static std::string _uri_escape_path_segment(const std::string &unescaped)
{
    return _uri_escape_string(unescaped, _RESERVED_CHARS_ALLOWED_IN_PATH_ELEMENT);
}

static std::string _uri_escape_query(const std::string &unescaped)
{
    std::string ret(_uri_escape_string(unescaped, "!$'()*,;:@/? =&"));
    for (std::string::iterator c = ret.begin();
         c != ret.end();
         ++c) {
        if (*c == ' ')
            *c = '+';
    }
    return ret;
}

static std::string _uri_escape_fragment(const std::string &unescaped)
{
    return _uri_escape_string(unescaped, _RESERVED_CHARS_ALLOWED_IN_PATH "?");
}

static std::string _uri_unescape_string(const std::string &escaped)
{
    std::string ret;

    for (std::string::size_type pos = 0; pos < escaped.size(); pos++) {
        if (escaped[pos] == '%' && escaped.size() - pos >= 3 &&
            isxdigit(escaped[pos+1]) && isxdigit(escaped[pos+2])) {
            unsigned char a=0, b=0;
            a = escaped[pos+1];
            if (a >= '0' && a <= '9') {
                a -= '0';
            }
            else if (a >= 'A' && a <= 'F') {
                a -= ('A' - 10);
            }
            else {
                a -= ('a' - 10);
            }
            b = escaped[pos+2];
            if (b >= '0' && b <= '9') {
                b -= '0';
            }
            else if (b >= 'A' && b <= 'F') {
                b -= ('A' - 10);
            }
            else {
                b -= ('a' - 10);
            }
            ret += static_cast<char>(a*16+b);
            pos += 2;
        }
        else {
            ret += escaped[pos];
        }
    }

    return ret;
}

static std::list<std::string> _uri_string_to_list(const std::string &path, unsigned char sep, bool convert, bool unescape)
{
    std::list<std::string> ret;

    if (!path.empty()) {
        std::string pct_sep;
        if (convert && !unescape) {
            pct_sep = _uri_char_to_pct_encode(sep);
        }

        std::string::size_type pos1 = 0, pos2;
        do {
            pos2 = path.find_first_of(static_cast<char>(sep), pos1);
            std::string segment(path.substr(pos1, pos2 - pos1));
            if (convert && !unescape) {
                for (std::string::size_type pos(segment.find(pct_sep));
                     pos != std::string::npos;
                     pos = segment.find(pct_sep, pos + 1)) {
                    segment.replace(pos, 3, 1, static_cast<char>(sep));
                }
            }
            if (unescape) {
                segment = _uri_unescape_string(segment);
            }
            ret.push_back(segment);
            if (pos2 != std::string::npos)
                pos1 = pos2 + 1;
        } while (pos2 != std::string::npos);
    }

    return ret;
}

static std::list<std::string> _uri_remove_dot_segments(const std::list<std::string> &original)
{
    std::list<std::string> ret;

    for (auto seg = original.begin(); seg != original.end(); ++seg) {
        auto next = seg;
        ++next;
        if (*seg == ".") {
            // remove single dot segments
        }
        else if (seg->empty() && seg != original.begin() && next != original.end()) {
            // remove empty segments that are not the first or last segment
        }
        else if (*seg == "..") {
            // remove double dot plus previous segment (if it exists)
            if (ret.size() > 0 && !ret.back().empty()) {
                ret.pop_back();
            }
        }
        else {
            // otherwise just copy the segment
            ret.push_back(*seg);
        }
    }

    return ret;
}

static std::string _uri_normalize_lowercase(const std::string &original)
{
    std::string normalized;
    transform(original.begin(), original.end(), back_inserter(normalized), tolower);
    return normalized;
}

static std::string _uri_normalize_scheme(const std::string &original)
{
    return _uri_normalize_lowercase(original);
}

static std::string _uri_normalize_hostname(const std::string &original)
{
    return _uri_normalize_lowercase(original);
}

static std::list<std::string> _uri_normalize_path(const std::list<std::string> &original)
{
    return _uri_remove_dot_segments(original);
}

static std::list<std::string> _uri_merge(const std::list<std::string> &base, const std::list<std::string> &rel)
{
    std::list<std::string> ret(rel);
    // If we don't have a base path or the rel DecomposedURL is absolute...
    if (base.size() == 0) {
        // ensure rel is absolute
        if (ret.size() > 0 && !ret.front().empty()) {
            ret.insert(ret.begin(), std::string());
        }
        // return the relative path
        return ret;
    }

    ret = base;
    ret.pop_back();
    ret.insert(ret.end(), rel.begin(), rel.end());
    return ret;
}

/**************************************************************************
 * DecomposedURL class methods
 **************************************************************************/

DecomposedURL::DecomposedURL()
    :m_pathSegments()
    ,m_scheme()
    ,m_userInfo()
    ,m_host()
    ,m_port(0)
    ,m_portDefault(true)
    ,m_query()
    ,m_fragment()
{
}

DecomposedURL::DecomposedURL(const DecomposedURL &other)
    :m_pathSegments(other.m_pathSegments)
    ,m_scheme(other.m_scheme)
    ,m_userInfo(other.m_userInfo)
    ,m_host(other.m_host)
    ,m_port(other.m_port)
    ,m_portDefault(other.m_portDefault)
    ,m_query(other.m_query)
    ,m_fragment(other.m_fragment)
{
}

DecomposedURL::DecomposedURL(const std::string &url)
    :m_pathSegments()
    ,m_scheme()
    ,m_userInfo()
    ,m_host()
    ,m_port(0)
    ,m_portDefault(true)
    ,m_query()
    ,m_fragment()
{
    if (url.empty()) return;

    // skip initial white space
    std::string::size_type pos = 0;
    while (pos < url.size() && isspace(url[pos])) pos++;

    // get working std::string starting with first non-space
    std::string uri(url.substr(pos));

    // Get scheme if available
    if (!uri.empty() && isalpha(uri[0])) {
        for (pos = 0; pos < uri.size() && (isalnum(uri[pos]) || uri[pos] == '+' || uri[pos] == '-' || uri[pos] == '.'); pos++);
    }
    if (pos > 0 && pos < uri.size() && uri[pos] == ':') {
        m_scheme = uri.substr(0, pos);
        uri.erase(0, pos + 1);
    }

    // Get authority part
    if (uri.size() >= 2 && uri[0] == '/' && uri[1] == '/') {
        uri.erase(0, 2);
        pos = uri.find_first_of("/?#");

        std::string authority(uri.substr(0, pos));
        uri.erase(0, authority.size());

        pos = authority.find_first_of('@');
        if (pos != std::string::npos) {
            m_userInfo = _uri_unescape_string(authority.substr(0, pos));
            authority.erase(0, pos+1);
        }
        if (authority.size() > 0 && authority[0] == '[') {
            pos = authority.find_first_of(']', 1);
            if (pos == std::string::npos) {
                throw ParseError("Unable to parse the host part of the URL.");
            }
            m_host = _uri_unescape_string(authority.substr(1, pos - 1));
            authority.erase(0, pos + 1);
        } else {
            pos = authority.find_first_of(':');
            m_host = _uri_unescape_string(authority.substr(0, pos));
            authority.erase(0, pos);
        }
        if (!authority.empty()) {
            if (authority[0] != ':' || authority.find_first_not_of("0123456789",1) != std::string::npos) {
                throw ParseError("Unable to parse the port part of the URL.");
            }
            char *endptr;
            m_port = strtol(authority.c_str()+1, &endptr, 10);
            m_portDefault = false;
        } else {
            if (m_scheme.compare("http") == 0) {
                m_port = 80;
            } else if (m_scheme.compare("https") == 0) {
                m_port = 443;
            }
        }
    }

    // Get path part
    if (!uri.empty()) {
        pos = uri.find_first_of("?#");
        m_pathSegments = _uri_string_to_list(uri.substr(0, pos), '/', false, true);
        uri.erase(0, pos);
    }

    // Get query std::string
    if (!uri.empty() && uri[0] == '?') {
        pos = uri.find_first_of('#');
        if (pos != std::string::npos) {
            m_query = _uri_unescape_string(uri.substr(1, pos - 1));
        } else {
            m_query = _uri_unescape_string(uri.substr(1));
        }
        uri.erase(0, pos);
    }

    // Get fragment std::string
    if (!uri.empty() && uri[0] == '#') {
        m_fragment = _uri_unescape_string(uri.substr(1));
        uri.clear();
    }

    if (!uri.empty()) {
        throw ParseError("URL parts left over after parse '" + uri + "'");
    }
}

DecomposedURL::DecomposedURL(const DecomposedURL &base, const std::string &url)
    :m_pathSegments(base.m_pathSegments)
    ,m_scheme(base.m_scheme)
    ,m_userInfo(base.m_userInfo)
    ,m_host(base.m_host)
    ,m_port(base.m_port)
    ,m_portDefault(base.m_portDefault)
    ,m_query(base.m_query)
    ,m_fragment(base.m_fragment)
{
    DecomposedURL rel(url);
    operator+=(rel);
}

DecomposedURL::DecomposedURL(const std::string &scheme, const std::string &userinfo, const std::string &host,
         uint16_t port, const std::string &path, const std::string &query,
         const std::string &fragment)
    :m_pathSegments()
    ,m_scheme(scheme)
    ,m_userInfo(userinfo)
    ,m_host(host)
    ,m_port(port)
    ,m_portDefault(false)
    ,m_query(query)
    ,m_fragment(fragment)
{
    m_pathSegments = _uri_string_to_list(path, '/', false, false);
}

DecomposedURL::DecomposedURL(const DecomposedURL& base, const std::string &scheme, const std::string &userinfo,
         const std::string &host, uint16_t port, const std::string &path,
         const std::string &query, const std::string &fragment)
    :m_pathSegments(base.m_pathSegments)
    ,m_scheme(base.m_scheme)
    ,m_userInfo(base.m_userInfo)
    ,m_host(base.m_host)
    ,m_port(base.m_port)
    ,m_portDefault(base.m_portDefault)
    ,m_query(base.m_query)
    ,m_fragment(base.m_fragment)
{
    DecomposedURL rel(scheme, userinfo, host, port, path, query, fragment);
    operator+=(rel);
}

DecomposedURL &DecomposedURL::operator=(const DecomposedURL &other)
{
    m_scheme = other.m_scheme;
    m_userInfo = other.m_userInfo;
    m_host = other.m_host;
    m_port = other.m_port;
    m_portDefault = other.m_portDefault;
    m_pathSegments = other.m_pathSegments;
    m_query = other.m_query;
    m_fragment = other.m_fragment;
    return *this;
}

bool DecomposedURL::operator==(const DecomposedURL &other) const
{
    // Check for same object
    if (this == &other) return true;

    if (m_port != other.m_port) return false;
    if (m_userInfo != other.m_userInfo) return false;
    if (m_query != other.m_query) return false;
    if (m_fragment != other.m_fragment) return false;

    std::string first_cmp, second_cmp;

    first_cmp = _uri_normalize_scheme(m_scheme);
    second_cmp = _uri_normalize_scheme(other.m_scheme);
    if (first_cmp != second_cmp) return false;

    first_cmp = _uri_normalize_hostname(m_host);
    second_cmp = _uri_normalize_hostname(other.m_host);
    if (first_cmp != second_cmp) return false;

    std::list<std::string> first_list(m_pathSegments);
    std::list<std::string> second_list(other.m_pathSegments);
    _uri_normalize_path(first_list);
    _uri_normalize_path(second_list);

    if (first_list != second_list) return false;

    return true;
}

DecomposedURL &DecomposedURL::operator+=(const DecomposedURL &other)
{
    if (isNull()) {
        *this = other;
            return *this;
    }

    if (other.isNull())
        return *this;

    if (!other.m_scheme.empty() && other.m_scheme != m_scheme) {
        m_scheme = other.m_scheme;
        m_userInfo = other.m_userInfo;
        m_host = other.m_host;
        m_port = other.m_port;
        m_portDefault = other.m_portDefault;
        m_pathSegments = _uri_remove_dot_segments(other.m_pathSegments);
        m_query = other.m_query;
    } else {
        if (!other.m_host.empty()) {
            m_userInfo = other.m_userInfo;
            m_host = other.m_host;
            m_port = other.m_port;
            m_portDefault = other.m_portDefault;
            m_pathSegments = _uri_remove_dot_segments(other.m_pathSegments);
            m_query = other.m_query;
        }
        else {
            if (other.m_pathSegments.size() == 0) {
                if (!other.m_query.empty()) {
                    m_query = other.m_query;
                }
            }
            else {
                if (other.m_pathSegments.size() > 0 &&
                    other.m_pathSegments.front().empty()) {
                    m_pathSegments = _uri_remove_dot_segments(other.m_pathSegments);
                }
                else {
                    m_pathSegments = _uri_remove_dot_segments(
                        _uri_merge(m_pathSegments, other.m_pathSegments));
                }
                m_query = other.m_query;
            }
        }
    }
    m_fragment = other.m_fragment;

    if ((m_port == 0) && (!m_scheme.empty())) {
        if(m_scheme.compare("http") == 0) {
                m_port = 80;
            } else if (m_scheme.compare("https") == 0) {
                m_port = 443;
            }
    }

    return *this;
}

DecomposedURL DecomposedURL::operator+(const DecomposedURL &other)
{
    DecomposedURL ret(*this);
    ret += other;
    return ret;
}

DecomposedURL::operator std::string() const
{
    std::ostringstream ostr;

    if (!m_scheme.empty())
        ostr << m_scheme << ":";

    if (!m_userInfo.empty() || !m_host.empty() || m_port != 0)
        ostr << "//";

    if (!m_userInfo.empty())
        ostr << _uri_escape_userinfo(m_userInfo) << "@";

    if (!m_host.empty()) {
        if (m_host.find_first_of(':') != std::string::npos) {
            ostr << "[" << _uri_escape_host_colon(m_host) << "]";
        }
        else {
            ostr << _uri_escape_host(m_host);
        }
    }

    if ((m_port != 0) && (!m_portDefault))
        ostr << ":" << m_port;

    if (m_pathSegments.size() > 0)
        ostr << pathString();

    if (!m_query.empty())
        ostr << "?" << _uri_escape_query(m_query);

    if (!m_fragment.empty())
        ostr << "#" << _uri_escape_fragment(m_fragment);

    return ostr.str();
}

bool DecomposedURL::isNormalized() const
{
    if (_uri_normalize_scheme(m_scheme) != m_scheme) return false;
    if (_uri_normalize_hostname(m_host) != m_host) return false;
    if (_uri_normalize_path(m_pathSegments) != m_pathSegments) return false;

    return true;
}

DecomposedURL &DecomposedURL::normalize()
{
    m_scheme = _uri_normalize_scheme(m_scheme);
    m_host = _uri_normalize_hostname(m_host);
    m_pathSegments = _uri_normalize_path(m_pathSegments);
    return *this;
}

std::string DecomposedURL::path() const
{
    std::string ret;
    const char *sep = "";

    for (std::list<std::string>::const_iterator seg = m_pathSegments.begin();
         seg != m_pathSegments.end();
         ++seg) {
        ret += sep;
        ret += *seg;
        sep = "/";
    }

    return ret;
}

DecomposedURL &DecomposedURL::path(const std::string &thepath)
{
    m_pathSegments = _uri_string_to_list(thepath, '/', false, false);
    return *this;
}

std::string DecomposedURL::pathString() const
{
    std::string ret;
    const char *sep = "";

    for (std::list<std::string>::const_iterator seg = m_pathSegments.begin();
         seg != m_pathSegments.end();
         ++seg) {
        ret += sep;
        ret += _uri_escape_path_segment(*seg);
        sep = "/";
    }

    return ret;
}

DecomposedURL &DecomposedURL::pathString(const std::string &path_string)
{
    m_pathSegments = _uri_string_to_list(path_string, '/', false, true);
    return *this;
}

DecomposedURL &DecomposedURL::appendPath(const std::string &relative_path)
{
    std::list<std::string> new_segs(_uri_string_to_list(relative_path, '/', false, false));
    if (m_pathSegments.size() > 1 && m_pathSegments.back().empty())
        m_pathSegments.pop_back();
    if (new_segs.size() > 0 && new_segs.front().empty())
        new_segs.erase(new_segs.begin());
    m_pathSegments.insert(m_pathSegments.end(), new_segs.begin(), new_segs.end());
    return *this;
}

DecomposedURL &DecomposedURL::appendPathSegment(const std::string &path_segment)
{
    if (!path_segment.empty()) {
        if (m_pathSegments.size() > 1 && m_pathSegments.back().empty())
            m_pathSegments.pop_back();
        m_pathSegments.push_back(path_segment);
    }
    return *this;
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
