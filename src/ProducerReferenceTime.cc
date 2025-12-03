/*****************************************************************************
 * DASH MPD parsing library in C++: ProducerReferenceTime class
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

#include "libmpd++/ProducerReferenceTime.hh"

LIBMPDPP_NAMESPACE_BEGIN

ProducerReferenceTime::ProducerReferenceTime()
{
}

ProducerReferenceTime::ProducerReferenceTime(const ProducerReferenceTime &other)
{
}

ProducerReferenceTime::ProducerReferenceTime(ProducerReferenceTime &&other)
{
}

ProducerReferenceTime &ProducerReferenceTime::operator=(const ProducerReferenceTime &other)
{
    return *this;
}

ProducerReferenceTime &ProducerReferenceTime::operator=(ProducerReferenceTime &&other)
{
    return *this;
}

bool ProducerReferenceTime::operator==(const ProducerReferenceTime &other) const
{
    return true;
}

// protected:

ProducerReferenceTime::ProducerReferenceTime(xmlpp::Node &node)
{
}

void ProducerReferenceTime::setXMLElement(xmlpp::Element &elem) const
{
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
