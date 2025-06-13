/*****************************************************************************
 * DASH MPD parsing library in C++: Codecs class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <iomanip>
#include <iostream>
#include <list>
#include <optional>
#include <regex>
#include <string>

#include "libmpd++/macros.hh"
#include "libmpd++/exceptions.hh"

#include "libmpd++/Codecs.hh"

LIBMPDPP_NAMESPACE_BEGIN

static std::string pct_encode(const std::string &str);
static std::string pct_decode(const std::string &pct_encoded_str);
static std::list<std::string> str_to_list(const std::string&);

Codecs::Encoding::Encoding(const std::string &encoding)
{
    auto pos = encoding.find_first_of('\'');
    if (pos == std::string::npos) throw ParseError("@codecs attribute encoding is not parsable");
    if (encoding[encoding.size()-1] != '\'') throw ParseError("@codecs attribute encoding is not parsable");

    m_charset = encoding.substr(0, pos);
    m_language = encoding.substr(pos+1, encoding.size()-pos-2);
}

Codecs::Codecs()
    :m_encoding()
    ,m_codecs()
{
}

Codecs::Codecs(const std::string &attr_val)
    :m_encoding()
    ,m_codecs()
{
    static const std::regex encoding_re("^[-[:alpha:]]+'[[:alpha:]]{1,8}(?:-[[:alpha:]]{1,8})*'");
    std::smatch result;
    if (std::regex_search(attr_val, result, encoding_re)) {
        m_encoding = Encoding(result.str());
        m_codecs = str_to_list(result.suffix());
        for (auto &codec : m_codecs) {
            codec = pct_decode(codec);
        }
    } else {
        m_codecs = str_to_list(attr_val);
    }
}

Codecs::Codecs(const Codecs &other)
    :m_encoding(other.m_encoding)
    ,m_codecs(other.m_codecs)
{
}

Codecs::Codecs(Codecs &&other)
    :m_encoding(std::move(other.m_encoding))
    ,m_codecs(std::move(other.m_codecs))
{
}

Codecs &Codecs::operator=(const Codecs &other)
{
    m_encoding = other.m_encoding;
    m_codecs = other.m_codecs;
    return *this;
}

Codecs &Codecs::operator=(Codecs &&other)
{
    m_encoding = std::move(other.m_encoding);
    m_codecs = std::move(other.m_codecs);
    return *this;
}

bool Codecs::operator==(const Codecs &other) const
{
    if (m_encoding.has_value() != other.m_encoding.has_value()) return false;
    if (m_encoding && !(m_encoding.value() != other.m_encoding.value())) return false;

    if (m_codecs.size() != other.m_codecs.size()) return false;

    auto work_list = other.m_codecs;
    for (const auto &codec : m_codecs) {
        auto it = std::find(work_list.begin(), work_list.end(), codec);
        if (it == work_list.end()) return false;
        work_list.erase(it);
    }

    return false;
}

Codecs::operator std::string() const
{
    std::ostringstream oss;

    if (m_encoding) {
        oss << m_encoding.value();
        const char *sep = "";
        for (const auto &codec : m_codecs) {
            oss << sep << pct_encode(codec);
            sep = ",";
        }
    } else {
        const char *sep = "";
        for (const auto &codec : m_codecs) {
            oss << sep << codec;
        }
    }

    return oss.str();
}

static std::string pct_encode(const std::string &s)
{
    std::string ret(s);
    static const char *subst_chars = "%";
    for (auto pos=ret.find_first_of(subst_chars); pos != std::string::npos; pos = ret.find_first_of(subst_chars, pos+1)) {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << std::hex << static_cast<unsigned int>(ret[pos]);
        ret.insert(pos+1, oss.str());
        pos += 2;
    }
    return ret;
}

static unsigned int hex_to_val(char c)
{
    if (c >= '0' && c <= '9') return c-'0';
    if (c >= 'a' && c <= 'f') return 10+c-'a';
    if (c >= 'A' && c <= 'F') return 10+c-'A';
    throw ParseError("Bad hex value");
}

static std::string pct_decode(const std::string &s)
{
    std::string ret(s);
    static const char *subst_chars = "%";
    for (auto pos=ret.find_first_of(subst_chars); pos != std::string::npos; pos = ret.find_first_of(subst_chars, pos+1)) {
        if (pos+2 >= ret.size()) break;
        auto charval = hex_to_val(ret[pos+1]) * 16 + hex_to_val(ret[pos+2]);
        ret.replace(pos, 3, 1, static_cast<char>(charval));
    }
    return ret;
}

static std::list<std::string> str_to_list(const std::string &val)
{
    std::list<std::string> ret;
    std::string::size_type start_pos = 0;
    for (auto pos = val.find_first_of(',');
         pos != std::string::npos;
         start_pos = pos+1, pos = val.find_first_of(',', start_pos)) {
        ret.push_back(val.substr(start_pos, pos-start_pos));
    }
    ret.push_back(val.substr(start_pos));
    return ret;
}

LIBMPDPP_NAMESPACE_END

std::ostream &operator<<(std::ostream &os, const LIBMPDPP_NAMESPACE_CLASS(Codecs::Encoding) &enc)
{
    os << std::string(enc);
    return os;
}

std::ostream &operator<<(std::ostream &os, const LIBMPDPP_NAMESPACE_CLASS(Codecs) &codecs)
{   
    os << std::string(codecs);
    return os;
}

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
