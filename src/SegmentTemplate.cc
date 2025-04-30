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

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/Period.hh"

#include "libmpd++/SegmentTemplate.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

/* protected: */
SegmentTemplate::SegmentTemplate(xmlpp::Node&)
{
}

void SegmentTemplate::setXMLElement(xmlpp::Element&) const
{
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
