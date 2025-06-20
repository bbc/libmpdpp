#ifndef _BBC_PARSE_DASH_MPD_RFC6838_CONTENT_TYPE_HH_
#define _BBC_PARSE_DASH_MPD_RFC6838_CONTENT_TYPE_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: RFC6838ContentType class
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

/** RFC6838ContentType class
 * @headerfile libmpd++/RFC6838ContentType.hh <libmpd++/RFC6838ContentType.hh>
 *
 * Container for %DASH %MPD schema %RFC6838ContentTypeType found in ISO 23009-1:2022 Clause 5.3.3.3.
 */
class LIBMPDPP_PUBLIC_API RFC6838ContentType {
public:
    RFC6838ContentType(const std::string &value);
    virtual ~RFC6838ContentType();
    bool operator==(const RFC6838ContentType &other) const { return m_value == other.m_value; }
    operator std::string() const { return m_value; }
    const std::string &value() const { return m_value; }
    RFC6838ContentType &value(const std::string &val);

///@cond PROTECTED
protected:
    friend class AdaptationSet;
    RFC6838ContentType(xmlpp::Node &node);
    void setXMLElement(xmlpp::Element &elem) const;
///@endcond PROTECTED

private:
    void convertString(const std::string &val);
    std::string m_value;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_RFC6838_CONTENT_TYPE_HH_*/
