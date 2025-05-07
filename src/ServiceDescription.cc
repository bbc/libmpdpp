/*****************************************************************************
 * DASH MPD parsing library in C++: ServiceDescription class
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

#include "libmpd++/ServiceDescription.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

ServiceDescription::ServiceDescription(xmlpp::Node&)
{
}

void ServiceDescription::setXMLElement(xmlpp::Element&) const
{
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
