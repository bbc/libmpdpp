#ifndef _BBC_PARSE_DASH_MPD_PATCH_LOCATION_HH_
#define _BBC_PARSE_DASH_MPD_PATCH_LOCATION_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: PatchLocation class
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

namespace xmlpp {
    class Element;
    class Node;
}

LIBPARSEMPD_NAMESPACE_BEGIN

class LIBPARSEMPD_PUBLIC_API PatchLocation {
public:
    PatchLocation() {};
    bool operator==(const PatchLocation &other) const { return true; };
protected:
    friend class MPD;
    PatchLocation(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_PATCH_LOCATION_HH_*/
