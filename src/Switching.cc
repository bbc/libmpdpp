/*****************************************************************************
 * DASH MPD parsing library in C++: Switching class
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

#include "libmpd++/Switching.hh"

LIBMPDPP_NAMESPACE_BEGIN

Switching::Switching()
{
}

Switching::Switching(const Switching &other)
{
}

Switching::Switching(Switching &&other)
{
}

Switching &Switching::operator=(const Switching &other)
{
    return *this;
}

Switching &Switching::operator=(Switching &&other)
{
    return *this;
}

bool Switching::operator==(const Switching &other) const
{
    return true;
}

// protected:

Switching::Switching(xmlpp::Node &node)
{
}

void Switching::setXMLElement(xmlpp::Element &elem) const
{
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
