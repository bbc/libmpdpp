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
#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/URI.hh"

#include "libmpd++/PatchLocation.hh"

LIBMPDPP_NAMESPACE_BEGIN

PatchLocation::PatchLocation(xmlpp::Node &node)
    :URI(node)
{
}

void PatchLocation::setXMLElement(xmlpp::Element &elem) const
{
    URI::setXMLElement(elem);
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
