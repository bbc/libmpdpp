/*****************************************************************************
 * DASH MPD parsing library in C++: RandomAccess class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <string>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"

#include "libmpd++/RandomAccess.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

RandomAccess::RandomAccess()
{
}

RandomAccess::RandomAccess(const RandomAccess &other)
{
}

RandomAccess::RandomAccess(RandomAccess &&other)
{
}

RandomAccess &RandomAccess::operator=(const RandomAccess &other)
{
    return *this;
}

RandomAccess &RandomAccess::operator=(RandomAccess &&other)
{
    return *this;
}

bool RandomAccess::operator==(const RandomAccess &other) const
{
    return false;
}

// protected:

RandomAccess::RandomAccess(xmlpp::Node &node)
{
}

void RandomAccess::setXMLElement(xmlpp::Element &elem) const
{
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
