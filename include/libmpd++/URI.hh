#ifndef _BBC_PARSE_DASH_MPD_URI_HH_
#define _BBC_PARSE_DASH_MPD_URI_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: URI class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <iostream>
#include <string>

#include "macros.hh"

namespace xmlpp {
    class Node;
}

LIBPARSEMPD_NAMESPACE_BEGIN

class LIBPARSEMPD_PUBLIC_API URI {
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

protected:
    friend class MPD;
    URI(xmlpp::Node&);

private:
    void validate();

    std::string m_uri;
};

LIBPARSEMPD_NAMESPACE_END

std::ostream &operator<<(std::ostream &os, const LIBPARSEMPD_NAMESPACE_CLASS(URI) &uri);

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_URI_HH_*/
