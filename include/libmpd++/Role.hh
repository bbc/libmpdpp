#ifndef _BBC_PARSE_DASH_MPD_ROLE_HH_
#define _BBC_PARSE_DASH_MPD_ROLE_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Role class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <optional>

#include "macros.hh"

namespace xmlpp {
    class Element;
    class Node;
}

LIBPARSEMPD_NAMESPACE_BEGIN

class AdaptationSet;

class LIBPARSEMPD_PUBLIC_API Role {
public:
    Role() {};

    virtual ~Role() {};

    bool operator==(const Role&) const { return true; };

protected:
    friend class AdaptationSet;
    Role(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_ACCESSIBILITY_HH_*/
