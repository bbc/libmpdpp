/*****************************************************************************
 * DASH MPD parsing library in C++: SegmentList class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <optional>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/MultipleSegmentBase.hh"
#include "libmpd++/Period.hh"

#include "libmpd++/SegmentList.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

/* protected: */
SegmentList::SegmentList(xmlpp::Node &node)
    :MultipleSegmentBase(node)
{
}

void SegmentList::setXMLElement(xmlpp::Element &elem) const
{
    MultipleSegmentBase::setXMLElement(elem);
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
