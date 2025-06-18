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

/** Codecs class
 * @headerfile libmpd++/Codecs.hh <libmpd++/Codecs.hh>
 *
 * This class models the codecs listed in an @@codecs attribute in a DASH MPD.
 *
 * This is a container for the %CodecsType from the %DASH %MPD %XML schema from ISO 23009-1:2022 Clause 5.3.7.3.
 */
class LIBMPDPP_PUBLIC_API Codecs {
public:
    /** Codecs encoding values
     * @headerfile libmpd++/Codecs.hh <libmpd++/Codecs.hh>
     * 
     * This models the character set and language encodings for extended @@codecs attribute values.
     */
    class Encoding {
    public:

        /** Default constructor
         *
         * Creates an empty Encoding instance.
         */
        Encoding() :m_charset(), m_language() {};

         /** Copy constructor
          *
          * Creates a new Encoding object which is a copy of @p other.
          *
          * @param other The Encoding object to copy.
          */
        Encoding(const Encoding &other) :m_charset(other.m_charset), m_language(other.m_language) {};
        
        /** Move constructor
         *
         * Creates a new Encoding object which transfers the resources from @p other.
         *
         * @param other The Encoding object to move.
         */
        Encoding(Encoding &other) :m_charset(std::move(other.m_charset)), m_language(std::move(other.m_language)) {};
        
        /** Construct with encoding string
         *
         * Make a new Encoding with @p encoding as the encoding string.
         *
         * @param encoding The encoding to set this Encoding value to.
         */
        Encoding(const std::string &encoding);

        /** Destructor
         */
        virtual ~Encoding() {};

        /** Copy operator
         *
         * Copies the values from @p other into this Encoding object.
         *
         * @param other The Encoding object to copy.
         * @return This Encoding object.
         */
        Encoding &operator=(const Encoding &other) { m_charset = other.m_charset; m_language = other.m_language; return *this; };
        
        /** Move operator
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
         * Compares this Encoding with another for equality.
         * This operator overload allows checking if two Encoding instances are equal.
         *
         * @param other A constant reference to the Encoding instance to compare against.
         * @return `true` if the Encoding instances are considered equal, `false` otherwise.
         */
        bool operator==(const Encoding &other) const { return m_charset == other.m_charset && m_language == other.m_language; };
        
        /** In-equality operator
         *
         * Compares this Encoding with another for in-equality.
         * This operator overload allows checking if two Encoding instances are not equal.
         * @param other A constant reference to the Encoding instance to compare against.
         * @return `true` if the Encoding are considered not equal, `false` otherwise.
         */
        bool operator!=(const Encoding &other) const { return m_charset != other.m_charset || m_language != other.m_language; };

        /** @pnchor Codecs_Encoding_operator_std_string
         * @brief String cast operator
         * 
         * Return a string representation of the encodings values (as would appear in the @@codecs attribute).
         *
         * @return The character set and language encoding string.
         */
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

    /** Construct from an attribute value string
     * 
     * @param attr_value The attribute value string to split into a Codecs list.
     */
    Codecs(const std::string &attr_value);

     /** Copy constructor
     *
     * Creates a new Codecs object which is a copy of @p to_copy.
     *
     * @param to_copy The Codecs object to copy.
     */
    Codecs(const Codecs &to_copy);

    /** Move constructor
     *
     * Creates a new Codecs object which transfers the resources from @p to_move.
     *
     * @param to_move The Codecs object to move.
     */
    Codecs(Codecs &&to_move);

    /** Destructor
     */
    virtual ~Codecs() {};

    /** Copy operator
     *
     * Copies the values from @p to_copy into this Codecs object.
     *
     * @param to_copy The Codecs object to copy.
     * @return This Codecs object.
     */
    Codecs &operator=(const Codecs &to_copy);

    /** Move operator
     *
     * Transfers the resources from @p to_move into this Codecs object.
     *
     * @param to_move The Codecs object to move.
     * @return This Codes object.
     */
    Codecs &operator=(Codecs &&to_move);
    
    /** Equality operator
     *
     * Compares this Codecs with another for equality.
     *
     * @param to_compare A constant reference to the Codecs instance to compare against.
     * @return `true` if the Codecs are considered equal, false otherwise..
     */
    bool operator==(const Codecs &to_compare) const;

    /** @pnchor Codecs_operator_std_string
     * @brief String cast operator
     * 
     * This converts the Codecs list into a string suitable for use in a @@codecs attribute in an MPD.
     *
     * @return The attribute string value for the Codecs list.
     */
    operator std::string() const;

    /** Check if this Codecs list has an encoding set
     *
     * @return `true` if an Encoding object is set on this Codecs list object.
     */
    bool hasEncoding() const { return m_encoding.has_value(); };

    /** Get the codecs encoding
     *
     * @return The optional codecs encoding.
     */
    const std::optional<Encoding> &encoding() const { return m_encoding; };

    /** Unset the codec encoding
     *
     * Remove any encoding set on this Codecs object.
     *
     * @return This Codecs object.
     */
    Codecs &encoding(const std::nullopt_t &) { m_encoding.reset(); return *this; };

    /**@{*/
    /** Set the codec encoding
     *
     * @param enc The encoding to set for this Codecs object.
     * @return This Codecs object.
     */
    Codecs &encoding(const Encoding &enc) { m_encoding = enc; return *this; };
    Codecs &encoding(Encoding &&enc) { m_encoding = std::move(enc); return *this; };
    Codecs &encoding(const std::optional<Encoding> &enc) { m_encoding = enc; return *this; };
    Codecs &encoding(std::optional<Encoding> &&enc) { m_encoding = std::move(enc); return *this; };
    /**@}*/

    /** Get the codecs list
     *
     * @return ths codecs list for this Codecs list object.
     */
    const std::list<std::string> &codecs() const { return m_codecs; };

    /**@{*/
    /** Get an iterator for the start of the Codecs list
     *
     * @return An iterator pointing to the start of the Codecs list.
     */
    std::list<std::string>::const_iterator cbegin() const { return m_codecs.cbegin(); };
    std::list<std::string>::const_iterator begin() const { return m_codecs.cbegin(); };
    std::list<std::string>::iterator begin() { return m_codecs.begin(); };
    std::list<std::string>::const_iterator codecsBegin() const { return m_codecs.cbegin(); };
    std::list<std::string>::iterator codecsBegin() { return m_codecs.begin(); };
    /**@}*/

    /**@{*/
    /** Get an iterator for the end of the Codecs list
     *
     * @return An iterator pointing to the end of the Codecs list.
     */
    std::list<std::string>::const_iterator cend() const { return m_codecs.cend(); };
    std::list<std::string>::const_iterator end() const { return m_codecs.cend(); };
    std::list<std::string>::iterator end() { return m_codecs.end(); };
    std::list<std::string>::const_iterator codecsEnd() const { return m_codecs.cend(); };
    std::list<std::string>::iterator codecsEnd() { return m_codecs.end(); };
    /**@}*/

    /** Get a codec from the list
     *
     * @param idx The index of the codec to get, starting at 0 for the first codec.
     * @return The codec value at index @p idx.
     * @throw std::out_of_range If @p idx is greater than or equal to the number of codecs in the list.
     */
    const std::string &codec(std::list<std::string>::size_type idx) const;

    /**@{*/
    /** Add a codec to the list
     *
     * @param codec The codec to add to the codecs list.
     * @return This Codecs list object.
     */
    Codecs &codecsAdd(const std::string &codec) { m_codecs.push_back(codec); return *this; };
    Codecs &codecsAdd(std::string &&codec) { m_codecs.push_back(std::move(codec)); return *this; };
    /**@}*/

    /** Remove a codec by value
     *
     * Remove a codec from the list which has the same value as @p codec.
     *
     * @param codec The value to remove from the list.
     * @return This Codecs list object.
     */
    Codecs &codecsRemove(const std::string &codec);

    /**@{*/
    /** Remove a codec by iterator
     *
     * @param it Iterator referencing the codec to remove from the list.
     * @return This Codecs list object.
     */
    Codecs &codecsRemove(const std::list<std::string>::const_iterator &it);
    Codecs &codecsRemove(const std::list<std::string>::iterator &it);
    /**@}*/

private:
    // CodecsType from ISO 23009-1:2022 Clause 5.3.7.3
    std::optional<Encoding> m_encoding; ///< The optional character set and language encoding for the codecs list
    std::list<std::string> m_codecs;    ///< The codecs list
};

LIBMPDPP_NAMESPACE_END

/** Stream output operator for @ref com::bbc::libmpdpp::Codecs::Encoding "Codecs::Encoding"
 *
 * This will convert the @ref com::bbc::libmpdpp::Codecs::Encoding "Encoding" to a string and append it to the @p os output stream.
 *
 * @param os The stream to output the @ref com::bbc::libmpdpp::Codecs::Encoding "Encoding" to.
 * @param enc The @ref com::bbc::libmpdpp::Codecs::Encoding "Encoding" to output.
 * @return The @p os stream.
 * @see @ref Codecs_Encoding_operator_std_string "Codecs::Encoding::operator std::string()"
 */
LIBMPDPP_PUBLIC_API std::ostream &operator<<(std::ostream &os, const LIBMPDPP_NAMESPACE_CLASS(Codecs::Encoding) &enc);

/** Stream output operator for @ref com::bbc::libmpdpp::Codecs "Codecs"
 *
 * This will convert the @ref com::bbc::libmpdpp::Codecs "Codecs" to a string and append it to the @p os output stream.
 *
 * @param os The stream to output the @ref com::bbc::libmpdpp::Codecs "Codecs" to.
 * @param codecs The @ref com::bbc::libmpdpp::Codecs "Codecs" to output.
 * @return The @p os stream.
 * @see @ref Codecs_operator_std_string "Codecs::operator std::string()"
 */
LIBMPDPP_PUBLIC_API std::ostream &operator<<(std::ostream &os, const LIBMPDPP_NAMESPACE_CLASS(Codecs) &codecs);

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_CODECS_HH_*/
