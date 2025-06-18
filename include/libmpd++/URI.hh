#ifndef _BBC_PARSE_DASH_MPD_URI_HH_
#define _BBC_PARSE_DASH_MPD_URI_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: URI class
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

class BaseURL;

/** URI class
 * @headerfile libmpd++/URI.hh <libmpd++/URI.hh>
 *
 * Container for %URI strings.
 *
 * This will parse and validate %URN and %URL strings and can resolve relative %URLs using a set of BaseURL objects from the %MPD.
 */
class LIBMPDPP_PUBLIC_API URI {
public:
    URI() :m_uri() {};
    URI(const char *uri) :m_uri(uri) {validate();};
    URI(const std::string &uri) :m_uri(uri) {validate();};
    URI(std::string &&uri) :m_uri(std::move(uri)) {validate();};
    URI(const URI &other) :m_uri(other.m_uri) {};
    URI(URI &&other) :m_uri(std::move(other.m_uri)) {};

    virtual ~URI() {};

    URI &operator=(const URI &other) { m_uri = other.m_uri; return *this; };
    URI &operator=(URI &&other) { m_uri = std::move(other.m_uri); return *this; };
    URI &operator=(const std::string &val) { m_uri = val; validate(); return *this; };
    URI &operator=(std::string &&val) { m_uri = std::move(val); validate(); return *this; };

    bool operator==(const URI &other) const { return m_uri == other.m_uri; };

    operator std::string() const { return m_uri; };
    const std::string &str() const { return m_uri; };

    URI resolveUsingBaseURLs(const std::list<BaseURL> &base_urls) const;
    bool isURL() const;
    bool isAbsoluteURL() const;

///@cond PROTECTED
protected:
    friend class MPD;
    friend class Period;
    friend class AdaptationSet;
    friend class Representation;
    friend class BaseURL;
    friend class SegmentBase;
    URI(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    void validate();

    std::string m_uri;
};

LIBMPDPP_NAMESPACE_END

LIBMPDPP_PUBLIC_API std::ostream &operator<<(std::ostream &os, const LIBMPDPP_NAMESPACE_CLASS(URI) &uri);

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_URI_HH_*/
