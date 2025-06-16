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

class LIBMPDPP_PUBLIC_API FrameRate {
public:
    using size_type = size_t;

    FrameRate()
        : m_numerator(0)
        , m_denominator(1)
    {}

    FrameRate(const std::string &frame_rate_str);

    FrameRate(size_type numerator, size_type denominator = 1)
        : m_numerator(numerator)
        , m_denominator(denominator)
    {}

    virtual ~FrameRate() {};

    bool operator==(const FrameRate &other) const;

    operator std::string() const;

    size_type numerator() const { return m_numerator; }
    FrameRate &numerator(size_type num) { m_numerator = num; return *this; }

    size_type denominator() const { return m_denominator; }
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
