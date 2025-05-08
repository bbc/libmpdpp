/*****************************************************************************
 * DASH MPD parsing library in C++: ProgramInformation class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <iostream>
#include <string>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"

#include "libmpd++/ProgramInformation.hh"

LIBMPDPP_NAMESPACE_BEGIN

ProgramInformation::ProgramInformation(xmlpp::Node &elem)
{
    // TODO: parse the element into this new ProgramInformation
}

void ProgramInformation::setXMLElement(xmlpp::Element &elem) const
{
    // TODO: Use this ProgramInformation to fill in an XML element
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
