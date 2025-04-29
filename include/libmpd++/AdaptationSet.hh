#ifndef _BBC_PARSE_DASH_MPD_ADAPTATION_SET_HH_
#define _BBC_PARSE_DASH_MPD_ADAPTATION_SET_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: AdaptationSet class
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

class LIBPARSEMPD_PUBLIC_API AdaptationSet {
public:
    LIBPARSEMPD_PUBLIC_API AdaptationSet() {};
protected:
    friend class Period;
    AdaptationSet(xmlpp::Node&);
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_ADAPTATION_SET_HH_*/
