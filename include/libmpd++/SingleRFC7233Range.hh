#ifndef _BBC_PARSE_DASH_MPD_SINGLE_RFC7233_RANGE_HH_
#define _BBC_PARSE_DASH_MPD_SINGLE_RFC7233_RANGE_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: SingleRFC7233Range class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
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

/** SingleRFC7233Range class
 * @headerfile libmpd++/SingleRFC7233Range.hh <libmpd++/SingleRFC7233Range.hh>
 *
 * Container for %DASH %MPD schema %SingleRFC7233RangeType as found in ISO 23009-1:2022 Clause 5.3.9.2.3.
 */
class LIBMPDPP_PUBLIC_API SingleRFC7233Range {
public:
    using size_type = size_t;

    SingleRFC7233Range()
        :m_fromByte(0)
        ,m_toByte()
    {};
    SingleRFC7233Range(const std::string &range_str);
    SingleRFC7233Range(size_type from, const std::optional<size_type> &to = std::nullopt)
        :m_fromByte(from)
        ,m_toByte(to)
    {};

    virtual ~SingleRFC7233Range() {};

    bool operator==(const SingleRFC7233Range &) const;

    operator std::string() const;

    size_type from() const { return m_fromByte; };
    SingleRFC7233Range &from(size_type val) { m_fromByte = val; return *this; };

    size_type to(size_type max_bytes) const { return m_toByte.has_value()?(m_toByte.value()<max_bytes?m_toByte.value():max_bytes-1):max_bytes-1; };
    const std::optional<size_type> &to() const { return m_toByte; };
    SingleRFC7233Range &to(const std::nullopt_t&) { m_toByte.reset(); return *this; };
    SingleRFC7233Range &to(size_type val) { m_toByte = val; return *this; };

///@cond PROTECTED
protected:
    friend class Period;
    SingleRFC7233Range(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    void convertString(const std::string&);

    size_type m_fromByte;
    std::optional<size_type> m_toByte;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SINGLE_RFC7233_RANGE_HH_*/
