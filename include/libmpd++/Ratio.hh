#ifndef _BBC_PARSE_DASH_MPD_RATIO_TYPE_HH_
#define _BBC_PARSE_DASH_MPD_RATIO_TYPE_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Ratio class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <optional>
#include <string>
#include <sstream>

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

/** Ratio class
 *
 * Container for %DASH %MPD schema %RatioType.
 */
class LIBMPDPP_PUBLIC_API Ratio {
public:
    using size_type = size_t;

    Ratio()
        : m_numerator(0)
        , m_denominator(0)
    {};

    Ratio(const std::string &ratio_str);

    Ratio(size_type numerator, size_type denominator)
        : m_numerator(numerator)
        , m_denominator(denominator)
    {};

    virtual ~Ratio() {};

    bool operator==(const Ratio &other) const;

    operator std::string() const;

    size_type numerator() const { return m_numerator; }
    Ratio &numerator(size_type num) { m_numerator = num; return *this; }
    size_type denominator() const { return m_denominator; }
    Ratio &denominator(size_type den) { m_denominator = den; return *this; }

///@cond PROTECTED
protected:
    friend class AdaptationSet;
    Ratio(xmlpp::Node &node);
    void setXMLElement(xmlpp::Element &elem) const;
///@endcond PROTECTED

private:
    void convertString(const std::string &ratio_str);

    size_type m_numerator;
    size_type m_denominator;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_RATIO_TYPE_HH_*/
