#ifndef _BBC_PARSE_DASH_MPD_BASE_URL_HH_
#define _BBC_PARSE_DASH_MPD_BASE_URL_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: BaseURL class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <chrono>
#include <optional>
#include <string>

#include "macros.hh"
#include "URI.hh"

namespace xmlpp {
    class Element;
    class Node;
}

LIBMPDPP_NAMESPACE_BEGIN

class MPD;
class Period;
class Representation;
class AdaptationSet;

class LIBMPDPP_PUBLIC_API BaseURL : public URI {
public:
    using duration_type = std::chrono::microseconds;

    BaseURL();
    BaseURL(const std::string &url);
    BaseURL(std::string &&url);
    BaseURL(const BaseURL&);
    BaseURL(BaseURL&&);

    virtual ~BaseURL() {};

    BaseURL &operator=(const BaseURL&);
    BaseURL &operator=(BaseURL&&);

    bool operator==(const BaseURL &other) const;

    const URI &url() const { return static_cast<const URI&>(*this); };
    URI &url() { return static_cast<URI&>(*this); };
    BaseURL &url(const URI &_url) { URI::operator=(_url); return *this; };
    BaseURL &url(URI &&_url) { URI::operator=(std::move(_url)); return *this; };

    /* create a copy of this BaseURL with the url resolved using the provided base_urls */
    BaseURL resolveURL(const std::list<BaseURL> &base_urls) const;
    
    // @serviceLocation
    bool hasServiceLocation() const { return m_serviceLocation.has_value(); };
    const std::optional<std::string> &serviceLocation() const { return m_serviceLocation; };
    BaseURL &serviceLocation(const std::nullopt_t&) { m_serviceLocation.reset(); return *this; };
    BaseURL &serviceLocation(const std::string &val) { m_serviceLocation = val; return *this; };
    BaseURL &serviceLocation(std::string &&val) { m_serviceLocation = std::move(val); return *this; };

    // @byteRange
    bool hasByteRange() const { return m_byteRange.has_value(); };
    const std::optional<std::string> &byteRange() const { return m_byteRange; };
    BaseURL &byteRange(const std::nullopt_t&) { m_byteRange.reset(); return *this; };
    BaseURL &byteRange(const std::string &val) { m_byteRange = val; return *this; };
    BaseURL &byteRange(std::string &&val) { m_byteRange = std::move(val); return *this; };

    // @availabilityTimeOffset
    bool hasAvailabilityTimeOffset() const { return m_availabilityTimeOffset.has_value(); };
    const std::optional<double> &availabilityTimeOffset() const { return m_availabilityTimeOffset; };
    BaseURL &availabilityTimeOffset(const std::nullopt_t&) { m_availabilityTimeOffset.reset(); return *this; };
    BaseURL &availabilityTimeOffset(double val) { m_availabilityTimeOffset = val; return *this; };

    // @availabilityTimeComplete
    bool hasAvailabilityTimeComplete() const { return m_availabilityTimeComplete.has_value(); };
    const std::optional<bool> &availabilityTimeComplete() const { return m_availabilityTimeComplete; };
    BaseURL &availabilityTimeComplete(const std::nullopt_t&) { m_availabilityTimeComplete.reset(); return *this; };
    BaseURL &availabilityTimeComplete(bool val) { m_availabilityTimeComplete = val; return *this; };

    // @timeShiftBufferDepth
    bool hasTimeShiftBufferDepth() const { return m_timeShiftBufferDepth.has_value(); };
    const std::optional<duration_type> &timeShiftBufferDepth() const { return m_timeShiftBufferDepth; };
    BaseURL &timeShiftBufferDepth(const std::nullopt_t&) { m_timeShiftBufferDepth.reset(); return *this; };
    BaseURL &timeShiftBufferDepth(const duration_type &val) { m_timeShiftBufferDepth = val; return *this; };
    BaseURL &timeShiftBufferDepth(duration_type &&val) { m_timeShiftBufferDepth = std::move(val); return *this; };

    // @rangeAccess
    bool rangeAccess() const { return m_rangeAccess; };
    BaseURL &rangeAccess(bool val) { m_rangeAccess = val; return *this; };

protected:
    friend class MPD;
    friend class Period;
    friend class Representation;
    friend class AdaptationSet;
    BaseURL(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    // BaseURL attributes ISO 23009-1 Table 30
    std::optional<std::string>   m_serviceLocation;
    std::optional<std::string>   m_byteRange;
    std::optional<double>        m_availabilityTimeOffset;
    std::optional<bool>          m_availabilityTimeComplete;
    std::optional<duration_type> m_timeShiftBufferDepth;
    bool                         m_rangeAccess;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_BASE_URL_HH_*/
