#ifndef _BBC_PARSE_DASH_MPD_CONTENT_PROTECTION_HH_
#define _BBC_PARSE_DASH_MPD_CONTENT_PROTECTION_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: ContentProtection class
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
    class Element;
    class Node;
}

LIBPARSEMPD_NAMESPACE_BEGIN

class LIBPARSEMPD_PUBLIC_API ContentProtection {
public:
    ContentProtection() {};
    bool operator==(const ContentProtection &other) const { return true; };
protected:
    friend class MPD;
    friend class Period;
    ContentProtection(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_CONTENT_PROTECTION_HH_*/
