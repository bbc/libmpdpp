#ifndef _BBC_PARSE_DASH_MPD_CODECS_HH_
#define _BBC_PARSE_DASH_MPD_CODECS_HH_
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
#include <iostream>
#include <list>
#include <optional>
#include <string>

#include "macros.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

class LIBPARSEMPD_PUBLIC_API Codecs {
public:
    class Encoding {
    public:
        Encoding() :m_charset(), m_language() {};
        Encoding(const Encoding &other) :m_charset(other.m_charset), m_language(other.m_language) {};
        Encoding(Encoding &other) :m_charset(std::move(other.m_charset)), m_language(std::move(other.m_language)) {};
        Encoding(const std::string&);

        virtual ~Encoding() {};

        Encoding &operator=(const Encoding &other) { m_charset = other.m_charset; m_language = other.m_language; return *this; };
        Encoding &operator=(Encoding &&other) {
            m_charset = std::move(other.m_charset); m_language = std::move(other.m_language); return *this;
        };

        bool operator==(const Encoding &other) const { return m_charset == other.m_charset && m_language == other.m_language; };
        bool operator!=(const Encoding &other) const { return m_charset != other.m_charset || m_language != other.m_language; };

        operator std::string() const { return m_charset + "'" + m_language + "'"; };

    private:
        std::string m_charset;
        std::string m_language;
    };

    Codecs();
    Codecs(const std::string&);
    Codecs(const Codecs &to_copy);
    Codecs(Codecs &&to_move);

    virtual ~Codecs() {};

    Codecs &operator=(const Codecs &to_copy);
    Codecs &operator=(Codecs &&to_move);

    bool operator==(const Codecs &to_compare) const;

    operator std::string() const;

private:
    // CodecsType from ISO 23009-1:2022 Clause 5.3.7.3
    std::optional<Encoding> m_encoding;
    std::list<std::string> m_codecs;
};

LIBPARSEMPD_NAMESPACE_END

std::ostream &operator<<(std::ostream &os, const LIBPARSEMPD_NAMESPACE_CLASS(Codecs::Encoding) &enc);

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_CODECS_HH_*/
