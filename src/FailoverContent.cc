/*****************************************************************************
 * DASH MPD parsing library in C++: FailoverContent class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <optional>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"

#include "libmpd++/FailoverContent.hh"

LIBMPDPP_NAMESPACE_BEGIN

// protected:

FailoverContent::FailoverContent(xmlpp::Node&)
{
}

void FailoverContent::setXMLElement(xmlpp::Element&) const
{
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
