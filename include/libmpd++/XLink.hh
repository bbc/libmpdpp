#ifndef _BBC_PARSE_DASH_MPD_XLINK_HH_
#define _BBC_PARSE_DASH_MPD_XLINK_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: XLink class
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

class Period;

class LIBPARSEMPD_PUBLIC_API XLink {
public:
    XLink() {};

    virtual ~XLink() {};

protected:
    friend class Period;
    XLink(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_XLINK_HH_*/
