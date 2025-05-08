/*****************************************************************************
 * DASH MPD parsing library in C++: ContentPopularityRate class
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

#include "libmpd++/ContentPopularityRate.hh"

LIBMPDPP_NAMESPACE_BEGIN

ContentPopularityRate::ContentPopularityRate()
{
}

ContentPopularityRate::ContentPopularityRate(const ContentPopularityRate &other)
{
}

ContentPopularityRate::ContentPopularityRate(ContentPopularityRate &&other)
{
}

ContentPopularityRate &ContentPopularityRate::operator=(const ContentPopularityRate &other)
{
    return *this;
}

ContentPopularityRate &ContentPopularityRate::operator=(ContentPopularityRate &&other)
{
    return *this;
}

bool ContentPopularityRate::operator==(const ContentPopularityRate &other) const
{
    return false;
}

// protected:

ContentPopularityRate::ContentPopularityRate(xmlpp::Node &node)
{
}

void ContentPopularityRate::setXMLElement(xmlpp::Element &elem) const
{
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
