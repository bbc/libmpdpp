#ifndef _BBC_PARSE_DASH_MPD_DECOMPOSED_URL_HH_
#define _BBC_PARSE_DASH_MPD_DECOMPOSED_URL_HH_
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
#include <stdint.h>

#include <list>
#include <string>

#include "libmpd++/macros.hh"

LIBMPDPP_NAMESPACE_BEGIN

class DecomposedURL {
public:
    DecomposedURL();
    DecomposedURL(const DecomposedURL &other);
    DecomposedURL(DecomposedURL &&other);
    DecomposedURL(const std::string &url);
    DecomposedURL(const DecomposedURL &base, const std::string &url);
    DecomposedURL(const std::string &scheme, const std::string &userinfo, const std::string &host, uint16_t port,
                  const std::string &path, const std::string &query, const std::string &fragment);
    DecomposedURL(const DecomposedURL &base, const std::string &scheme, const std::string &userinfo, const std::string &host,
                  uint16_t port, const std::string &path, const std::string &query, const std::string &fragment);

    DecomposedURL &operator=(const DecomposedURL&);
    DecomposedURL &operator=(DecomposedURL&&);
    bool operator==(const DecomposedURL&) const;
    bool operator!=(const DecomposedURL &other) const { return !(*this == other); };
    DecomposedURL &operator+=(const DecomposedURL&);
    DecomposedURL operator+(const DecomposedURL&);

    operator std::string() const;

    bool isNormalized() const;
    DecomposedURL &normalize();

    const std::string &scheme() const { return m_scheme; };
    DecomposedURL &scheme(const std::string &scheme_name) {
        m_scheme = scheme_name;
        if (m_portDefault) {
            if(scheme_name.compare("http") == 0) {
                m_port = 80;
            } else if (scheme_name.compare("https") == 0) {
                m_port = 443;
            }
        }
        return *this;
    };

    const std::string &userinfo() const { return m_userInfo; };
    DecomposedURL &userinfo(const std::string &user_info) {
        m_userInfo = user_info;
        return *this;
    };

    const std::string &host() const { return m_host; };
    DecomposedURL &host(const std::string &hostname) {
        m_host = hostname;
        return *this;
    };

    uint16_t port() const { return m_port; };
    DecomposedURL &port(uint16_t portnum) {
        m_port = portnum;
        m_portDefault = false;
        return *this;
    };

    std::string authority() {
        std::string out = m_host;
        if (m_port > 0) {
            out += ":";
            out += std::to_string(m_port);
        } /*else if (m_scheme == "https") {
            out += ":443";
        } else {
            out += ":80";
        }*/
        return out;
    };
    std::string path() const;
    DecomposedURL &path(const std::string &thepath);
    std::string pathString() const;
    DecomposedURL &pathString(const std::string &path_string);
    const std::list<std::string> &pathSegments() const {
        return m_pathSegments;
    };
    DecomposedURL &pathSegments(const std::list<std::string> &path_segments) {
        m_pathSegments = path_segments;
        return *this;
    };
    DecomposedURL &appendPath(const std::string &relative_path);
    DecomposedURL &appendPathSegment(const std::string &path_segment);

    const std::string &query() const { return m_query; };
    DecomposedURL &query(const std::string &query_str) {
        m_query = query_str;
        return *this;
    };

    const std::string &fragment() const { return m_fragment; };
    DecomposedURL &fragment(const std::string &fragment_str) {
        m_fragment = fragment_str;
        return *this;
    };

    bool isNull() const {
        return m_port == 0 && m_scheme.empty() && m_userInfo.empty() &&
               m_host.empty() && m_pathSegments.size() == 0 && m_query.empty() &&
               m_fragment.empty();
    };

protected:
    std::list<std::string> m_pathSegments;

private:
    std::string m_scheme;
    std::string m_userInfo;
    std::string m_host;
    uint16_t m_port;
    bool m_portDefault;
    std::string m_query;
    std::string m_fragment;
};

LIBMPDPP_NAMESPACE_END

inline std::ostream &operator<<(std::ostream &os, const LIBMPDPP_NAMESPACE_CLASS(DecomposedURL) &url)
{
    os << std::string(url);
    return os;
}

/* vim:ts=8:sts=4:sw=4:expandtab:
 */

#endif /* _BBC_PARSE_DASH_MPD_DECOMPOSED_URL_HH_ */
