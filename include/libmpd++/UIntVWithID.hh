#ifndef _BBC_PARSE_DASH_MPD_U_INT_V_WITH_I_D_HH_
#define _BBC_PARSE_DASH_MPD_U_INT_V_WITH_I_D_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: UIntVWithID class
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

class LIBPARSEMPD_PUBLIC_API UIntVWithID {
public:
    UIntVWithID() {};
    bool operator==(const UIntVWithID &other) const { return true; };
protected:
    friend class MPD;
    UIntVWithID(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_U_INT_V_WITH_I_D_HH_*/
