/*****************************************************************************
 * DASH MPD parsing library in C++: Role class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <optional>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/AdaptationSet.hh"
#include "libmpd++/Representation.hh"

#include "libmpd++/Role.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

Role::Role(xmlpp::Node&)
{
}

void Role::setXMLElement(xmlpp::Element&) const
{
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
