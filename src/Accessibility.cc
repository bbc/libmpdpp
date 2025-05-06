/*****************************************************************************
 * DASH MPD parsing library in C++: Accessibility class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <optional>
#include <iostream>

#include <string>
#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"

#include "libmpd++/Accessibility.hh"


LIBPARSEMPD_NAMESPACE_BEGIN

Accessibility::Accessibility(xmlpp::Node &node)
{
}

void Accessibility::setXMLElement(xmlpp::Element &element) const
{
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
