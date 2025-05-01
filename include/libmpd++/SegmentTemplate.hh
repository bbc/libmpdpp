#ifndef _BBC_PARSE_DASH_MPD_SEGMENTTEMPLATE_HH_
#define _BBC_PARSE_DASH_MPD_SEGMENTTEMPLATE_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: SegmentTemplate class
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
#include "MultipleSegmentBase.hh"

namespace xmlpp {
    class Element;
    class Node;
}

LIBPARSEMPD_NAMESPACE_BEGIN

class LIBPARSEMPD_PUBLIC_API SegmentTemplate : public MultipleSegmentBase {
public:
    SegmentTemplate() :MultipleSegmentBase() {};

    virtual ~SegmentTemplate() {};

    bool operator==(const SegmentTemplate &) const;

protected:
    friend class Period;
    SegmentTemplate(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SEGMENTTEMPLATE_HH_*/
