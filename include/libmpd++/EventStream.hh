#ifndef _BBC_PARSE_DASH_MPD_EVENT_STREAM_HH_
#define _BBC_PARSE_DASH_MPD_EVENT_STREAM_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: EventStream class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <optional>

#include "macros.hh"

namespace xmlpp {
    class Element;
    class Node;
}

LIBMPDPP_NAMESPACE_BEGIN

class Period;

class LIBMPDPP_PUBLIC_API EventStream {
public:
    EventStream() {};

    virtual ~EventStream() {};

    bool operator==(const EventStream&) const { return true; };

protected:
    friend class Period;
    friend class RepresentationBase;
    EventStream(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_EVENT_STREAM_HH_*/
