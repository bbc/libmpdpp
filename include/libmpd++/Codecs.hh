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

LIBMPDPP_NAMESPACE_BEGIN

class LIBMPDPP_PUBLIC_API Codecs {
public:
    class Encoding {
    public:

        /** Default constructor
         *
         * Creates an empty Encoding instance.
         */
        Encoding() :m_charset(), m_language() {};

         /**
          * Copy constructor
          *
          * Creates a new Encoding object which is a copy of @p other.
          *
          * @param other The Encoding object to copy.
          */
        Encoding(const Encoding &other) :m_charset(other.m_charset), m_language(other.m_language) {};
        
	/**
         * Move constructor
         *
         * Creates a new Encoding object which transfers the resources from @p other.
         *
         * @param other The Encoding object to move.
         */
        Encoding(Encoding &other) :m_charset(std::move(other.m_charset)), m_language(std::move(other.m_language)) {};
        
	/** Construct with encoding string
         *
         * Make a new Encoding with @a encoding as the encoding string.
         *
         * @param encoding The encoding to set this Encoding value to.
         */

	Encoding(const std::string &encoding);

	/**
         * Destructor
         */
        virtual ~Encoding() {};

	/**
         * Copy operator
         *
         * Copies the values from @p other into this Encoding object.
         *
         * @param other The Encoding object to copy.
         * @return This Encoding object.
         */
        Encoding &operator=(const Encoding &other) { m_charset = other.m_charset; m_language = other.m_language; return *this; };
        
	/**
         * Move operator
         *
         * Transfers the resources from @p other into this Encoding object.
         *
         * @param other The Encoding object to move.
         * @return This Encoding object.
         */
	Encoding &operator=(Encoding &&other) {
            m_charset = std::move(other.m_charset); m_language = std::move(other.m_language); return *this;
        };

	/** Equality operator
         *
         * @brief Compares this Encoding with another for equality.
         * This operator overload allows checking if two Encoding instances are equal.
         * @param other A constant reference to the Encoding instance to compare against.
         * @return `true` if the Encoding instances are considered equal, false otherwise..
         */
        bool operator==(const Encoding &other) const { return m_charset == other.m_charset && m_language == other.m_language; };
        
	/** In-equality operator
         *
         * @brief Compares this Encoding with another for in-equality.
         * This operator overload allows checking if two Encoding instances are not equal.
         * @param other A constant reference to the Encoding instance to compare against.
         * @return `true` if the Encoding are considered not equal, false otherwise..
         */
	bool operator!=(const Encoding &other) const { return m_charset != other.m_charset || m_language != other.m_language; };

        operator std::string() const { return m_charset + "'" + m_language + "'"; };

    private:
        std::string m_charset;
        std::string m_language;
    };

    /** Default constructor
     *
     * Creates an empty Codecs.
     */
    Codecs();

    Codecs(const std::string&);

     /**
     * Copy constructor
     *
     * Creates a new Codecs object which is a copy of @p to_copy.
     *
     * @param to_copy The Codecs object to copy.
     */
    Codecs(const Codecs &to_copy);

    /**
     * Move constructor
     *
     * Creates a new Codecs object which transfers the resources from @p to_move.
     *
     * @param to_move The Codecs object to move.
     */
    Codecs(Codecs &&to_move);

    /**
     * Destructor
     */
    virtual ~Codecs() {};

    /**
     * Copy operator
     *
     * Copies the values from @p to_copy into this Codecs object.
     *
     * @param to_copy The Codecs object to copy.
     * @return This Codecs object.
     */
    Codecs &operator=(const Codecs &to_copy);

    /**
     * Move operator
     *
     * Transfers the resources from @p to_move into this Codecs object.
     *
     * @param to_move The Codecs object to move.
     * @return This Codes object.
     */
    Codecs &operator=(Codecs &&to_move);
    
    /** Equality operator
     *
     * @brief Compares this Codecs with another for equality.
     * This operator overload allows checking if two Codecs instances are equal.
     * @param to_compare A constant reference to the Codecs instance to compare against.
     * @return `true` if the Codecs are considered equal, false otherwise..
     */
    bool operator==(const Codecs &to_compare) const;

    operator std::string() const;

private:
    // CodecsType from ISO 23009-1:2022 Clause 5.3.7.3
    std::optional<Encoding> m_encoding;
    std::list<std::string> m_codecs;
};

LIBMPDPP_NAMESPACE_END

LIBMPDPP_PUBLIC_API std::ostream &operator<<(std::ostream &os, const LIBMPDPP_NAMESPACE_CLASS(Codecs::Encoding) &enc);

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_CODECS_HH_*/
