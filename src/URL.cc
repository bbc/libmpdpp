/*****************************************************************************
 * DASH MPD parsing library in C++: URL class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"

#include "libmpd++/URL.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

URL::URL(xmlpp::Node &node)
    :URI(node)
{
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
