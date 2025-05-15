/*****************************************************************************
 * DASH MPD parsing library in C++: SegmentList class
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
#include "libmpd++/MultipleSegmentBase.hh"
#include "libmpd++/Period.hh"

#include "libmpd++/SegmentList.hh"

LIBMPDPP_NAMESPACE_BEGIN

static const std::string g_empty_string;

const std::string &SegmentList::getMediaURLForSegment(unsigned long segment_number) const
{
    if (segment_number >= m_segmentURLs.size()) return g_empty_string;
    auto it = m_segmentURLs.begin();
    for (decltype(segment_number) i = 0; i < segment_number; i++) it++;
    const auto &seg_url = *it;
    if (seg_url.hasMedia()) return seg_url.media().value().str();
    return g_empty_string;
}

const std::string &SegmentList::getMediaURLForSegmentTime(unsigned long time) const
{
    // TODO: iterate to the m_segmentURLs to find the one representing @a time.
    return g_empty_string;
}

const std::string &SegmentList::getMediaURLForSegmentTime(const duration_type &time) const
{
    double ts = 1.0;
    if (hasTimescale()) {
        ts = timescale().value();
    }

    auto time_in_sec = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1> > >(time);
    unsigned long t = static_cast<unsigned long>(time_in_sec.count() * ts);

    return getMediaURLForSegmentTime(t);
}

const std::string &SegmentList::getInitializationURL() const
{
    if (hasInitialization() && initialization().value().hasSourceURL())
        return initialization().value().sourceURL().value().str();

    return g_empty_string;
}

/* protected: */
SegmentList::SegmentList(xmlpp::Node &node)
    :MultipleSegmentBase(node)
{
}

void SegmentList::setXMLElement(xmlpp::Element &elem) const
{
    MultipleSegmentBase::setXMLElement(elem);
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
