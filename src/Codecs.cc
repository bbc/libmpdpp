/*****************************************************************************
 * DASH MPD parsing library in C++: Codecs class
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

#include "libmpd++/Codecs.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

Codecs::Codecs()
{
}

Codecs::Codecs(const std::string &attr_val)
{
}

Codecs::Codecs(const Codecs &other)
{
}

Codecs::Codecs(Codecs &&other)
{
}

Codecs &Codecs::operator=(const Codecs &other)
{
    return *this;
}

Codecs &Codecs::operator=(Codecs &&other)
{
    return *this;
}

bool Codecs::operator==(const Codecs &other) const
{
    return false;
}

Codecs::operator std::string() const
{
    return "";
}

// protected:

Codecs::Codecs(xmlpp::Node &node)
{
}

void Codecs::setXMLElement(xmlpp::Element &elem) const
{
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
