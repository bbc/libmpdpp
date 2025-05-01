#ifndef _BBC_PARSE_DASH_MPD_BASE_URL_HH_
#define _BBC_PARSE_DASH_MPD_BASE_URL_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: BaseURL class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
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

LIBPARSEMPD_NAMESPACE_BEGIN

class MPD;
class Period;
class AdaptationSet;

class LIBPARSEMPD_PUBLIC_API BaseURL : public URI {
public:
    using duration_type = std::chrono::microseconds;

    BaseURL() {};
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

protected:
    friend class MPD;
    friend class Period;
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

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_BASE_URL_HH_*/
