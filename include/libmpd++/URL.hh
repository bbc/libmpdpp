#ifndef _BBC_PARSE_DASH_MPD_URL_HH_
#define _BBC_PARSE_DASH_MPD_URL_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: URL class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <iostream>
#include <string>

#include "macros.hh"
#include "SingleRFC7233Range.hh"
#include "URI.hh"

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

/** URL class
 * @headerfile libmpd++/URL.hh <libmpd++/URL.hh>
 *
 * Container for %DASH %MPD schema %URLType (ISO 23009-1:2022 Clause 5.3.9.2.3).
 */
class LIBMPDPP_PUBLIC_API URL {
public:
    URL();
    URL(const URL&);
    URL(URL&&);

    virtual ~URL() {};

    URL &operator=(const URL&);
    URL &operator=(URL&&);

    bool operator==(const URL &other) const;

    // @sourceURL
    bool hasSourceURL() const { return m_sourceURL.has_value(); };
    const std::optional<URI> &sourceURL() const { return m_sourceURL; };
    URL &sourceURL(const std::nullopt_t&) { m_sourceURL.reset(); return *this; };
    URL &sourceURL(const URI &val) { m_sourceURL = val; return *this; };
    URL &sourceURL(URI &&val) { m_sourceURL = std::move(val); return *this; };

    // @range
    bool hasRange() const { return m_range.has_value(); };
    const std::optional<SingleRFC7233Range> &range() const { return m_range; };
    URL &range(const std::nullopt_t&) { m_range.reset(); return *this; };
    URL &range(const SingleRFC7233Range &val) { m_range = val; return *this; };
    URL &range(SingleRFC7233Range &&val) { m_range = std::move(val); return *this; };

///@cond PROTECTED
protected:
    friend class MPD;
    friend class Period;
    friend class AdaptationSet;
    friend class Representation;
    friend class BaseURL;
    friend class SegmentBase;
    friend class MultipleSegmentBase;
    URL(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // URLType from ISO 23009-1:2022 Clause 5.3.9.2.3
    std::optional<URI> m_sourceURL;
    std::optional<SingleRFC7233Range> m_range;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_URL_HH_*/
