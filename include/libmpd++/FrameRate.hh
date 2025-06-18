#ifndef _BBC_PARSE_DASH_MPD_FRAME_RATE_HH_
#define _BBC_PARSE_DASH_MPD_FRAME_RATE_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: FrameRate class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <string>

#include "macros.hh"

/**@cond
 */
// Forward declarations for types only used by pointer or reference
namespace xmlpp {
    class Element;
    class Node;
}
/**@endcond
 */

LIBMPDPP_NAMESPACE_BEGIN

/** FrameRate class
 * @headerfile libmpd++/FrameRate.hh <libmpd++/FrameRate.hh>
 *
 * This is a container for %DASH %MPD %XML @@frameRate attributes and follows the definition of %FrameRateType from
 * ISO 23009-1:2022 Clause 5.3.3.3.
 *
 * Although the original definition in ISO 23009-1:2022 is simply a restricted string type, this class breaks the string down into
 * a useful numerator and denominator pair.
 */
class LIBMPDPP_PUBLIC_API FrameRate {
public:
    using size_type = size_t; ///< Type used to hold numerators and denominators

    /** Default constructor
     *
     * This will create a new FrameRate value of "0/1".
     */
    FrameRate()
        : m_numerator(0)
        , m_denominator(1)
    {};

    /** Construct from string value
     *
     * This will parse a %DASH %MPD %XML %FrameRateType value and store it in a new FrameRate object. The string should be in the
     * form "<numerator>[/<denominator>]". If the optional denominator part is omitted then the denominator will default to 1.
     *
     * @param frame_rate_str The string to parse.
     * @throw ParseError Thrown if the string cannot be parsed correctly.
     */
    FrameRate(const std::string &frame_rate_str);

    /** Construct by value
     *
     * Construct a new FrameRate from the @p numerator and @p denominator provided.
     *
     * @param numerator The numerator for the frame rate.
     * @param denominator The denominator for the frame rate.
     */
    FrameRate(size_type numerator, size_type denominator = 1)
        : m_numerator(numerator)
        , m_denominator(denominator)
    {};

    /** Copy constructor
     *
     * Make a new copy of @p other.
     *
     * @param other The other FrameRate to copy.
     */
    FrameRate(const FrameRate &other)
        : m_numerator(other.m_numerator)
        , m_denominator(other.m_denominator)
    {};

    /** Move constructor
     *
     * Make a new copy of @p other.
     *
     * @param other The other FrameRate to copy.
     */
    FrameRate(FrameRate &&other)
        : m_numerator(other.m_numerator)
        , m_denominator(other.m_denominator)
    {};

    /** Destructor
     */
    virtual ~FrameRate() {};

    /** Copy operator
     *
     * Copy another FrameRate from @p other into this FrameRate.
     *
     * @param other The other FrameRate to copy.
     * @return This FrameRate.
     */
    FrameRate &operator=(const FrameRate &other) {
        m_numerator = other.m_numerator;
        m_denominator = other.m_denominator;
        return *this;
    };

    /** Move operator
     *
     * Copies another FrameRate from @p other into this FrameRate.
     *
     * @param other The other FrameRate to copy.
     * @return This FrameRate.
     */
    FrameRate &operator=(FrameRate &&other) {
        m_numerator = other.m_numerator;
        m_denominator = other.m_denominator;
        return *this;
    };

    /** Equality operator
     *
     * Check if this FrameRate has the same value as @p other.
     *
     * @param other The other FrameRate to compare to this one.
     * @return `true` if the @p other FrameRate has the same value as this one.
     */
    bool operator==(const FrameRate &other) const {
        return m_numerator == other.m_numerator && m_denominator == other.m_denominator;
    };

    /** Inequality operator
     *
     * Check if this FrameRate does not have the same value as @p other.
     *
     * @param other The other FrameRate to compare to this one.
     * @return `true` if the @p other FrameRate does not have the same value as this one.
     */
    bool operator!=(const FrameRate &other) const { return !(*this == other); };

    /** string cast operator
     *
     * This converts the FrameRate into a string suitable for use as a @@frameRate attribute value.
     *
     * @return The attribute value string for this FrameRate.
     */
    operator std::string() const;

    /** Get the numerator
     *
     * @return The numerator for this FrameRate.
     */
    size_type numerator() const { return m_numerator; }

    /** Set the numerator
     *
     * @param num The new numerator to set.
     * @return This FrameRate.
     */
    FrameRate &numerator(size_type num) { m_numerator = num; return *this; }

    /** Get the denominator
     *
     * @return The denominator for this FrameRate.
     */
    size_type denominator() const { return m_denominator; }

    /** Set the denominator
     *
     * @param den The new denominator to set.
     * @return This FrameRate.
     */
    FrameRate &denominator(size_type den) { m_denominator = den; return *this; }

///@cond PROTECTED
protected:
    friend class AdaptationSet;
    // Construct from an XML node; extracts the text content and converts.
    FrameRate(xmlpp::Node &node);

    // Sets the XML element’s text to the string representation of this frame rate.
    void setXMLElement(xmlpp::Element &elem) const;
///@endcond PROTECTED

private:
    // Converts a frame rate string into numeric components.
    // Throws ParseError if the string is empty or doesn’t follow the pattern.
    void convertString(const std::string &frame_rate_str);

    size_type m_numerator;
    size_type m_denominator;
};


LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_FRAME_RATE_HH_*/
