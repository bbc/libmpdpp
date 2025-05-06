#ifndef _BBC_PARSE_DASH_MPD_CONTENT_COMPONENT_HH_
#define _BBC_PARSE_DASH_MPD_CONTENT_COMPONENT_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: ContentComponent class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
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

class LIBPARSEMPD_PUBLIC_API ContentComponent {
public:
    ContentComponent() {};

    virtual ~ContentComponent() {};

    bool operator==(const ContentComponent&) const { return true; };

protected:
    friend class AdaptationSet;
    ContentComponent(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_CONTENT_COMPONENT_HH_*/
