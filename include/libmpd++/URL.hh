#ifndef _BBC_PARSE_DASH_MPD_URL_HH_
#define _BBC_PARSE_DASH_MPD_URL_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: URL class
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
#include "URI.hh"

namespace xmlpp {
    class Node;
}

LIBPARSEMPD_NAMESPACE_BEGIN

class LIBPARSEMPD_PUBLIC_API URL : public URI {
public:
    using URI::URI;
    using URI::operator=;
    using URI::operator std::string;
    using URI::operator==;

    virtual ~URL() {};

protected:
    friend class MPD;
    URL(xmlpp::Node&);
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_URL_HH_*/
