/*****************************************************************************
 * DASH MPD parsing library in C++: XLink class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <optional>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/URI.hh"

#include "libmpd++/XLink.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

bool XLink::operator==(const XLink &other) const
{
    return m_actuate == other.m_actuate && m_type == other.m_type && m_show == other.m_show && m_href == other.m_href;
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
