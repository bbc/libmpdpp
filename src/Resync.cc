/*****************************************************************************
 * DASH MPD parsing library in C++: Resync class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <string>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"

#include "libmpd++/Resync.hh"

LIBMPDPP_NAMESPACE_BEGIN

Resync::Resync()
{
}

Resync::Resync(const Resync &other)
{
}

Resync::Resync(Resync &&other)
{
}

Resync &Resync::operator=(const Resync &other)
{
    return *this;
}

Resync &Resync::operator=(Resync &&other)
{
    return *this;
}

bool Resync::operator==(const Resync &other) const
{
    return true;
}

// protected:

Resync::Resync(xmlpp::Node &node)
{
}

void Resync::setXMLElement(xmlpp::Element &elem) const
{
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
