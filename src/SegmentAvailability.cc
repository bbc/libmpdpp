/*****************************************************************************
 * DASH MPD parsing library in C++: SegmentAvailability class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <chrono>
#include <optional>

#include "libmpd++/macros.hh"
#include "libmpd++/URI.hh"

#include "libmpd++/SegmentAvailability.hh"

LIBMPDPP_NAMESPACE_BEGIN

SegmentAvailability::SegmentAvailability()
    :m_availabilityStartTime()
    ,m_availabilityEndTime()
    ,m_segmentDuration()
    ,m_segmentURL()
{
}

SegmentAvailability::SegmentAvailability(const SegmentAvailability &to_copy)
    :m_availabilityStartTime(to_copy.m_availabilityStartTime)
    ,m_availabilityEndTime(to_copy.m_availabilityEndTime)
    ,m_segmentDuration(to_copy.m_segmentDuration)
    ,m_segmentURL(to_copy.m_segmentURL)
{
}

SegmentAvailability::SegmentAvailability(SegmentAvailability &&to_move)
    :m_availabilityStartTime(std::move(to_move.m_availabilityStartTime))
    ,m_availabilityEndTime(std::move(to_move.m_availabilityEndTime))
    ,m_segmentDuration(std::move(to_move.m_segmentDuration))
    ,m_segmentURL(std::move(to_move.m_segmentURL))
{
}

SegmentAvailability::SegmentAvailability(const time_type &availability_start, const duration_type &segment_length,
                                         const URI &segment_url, const std::optional<time_type> &availability_end)
    :m_availabilityStartTime(availability_start)
    ,m_availabilityEndTime(availability_end)
    ,m_segmentDuration(segment_length)
    ,m_segmentURL(segment_url)
{
}

SegmentAvailability &SegmentAvailability::operator=(const SegmentAvailability &to_copy)
{
    m_availabilityStartTime = to_copy.m_availabilityStartTime;
    m_availabilityEndTime = to_copy.m_availabilityEndTime;
    m_segmentDuration = to_copy.m_segmentDuration;
    m_segmentURL = to_copy.m_segmentURL;

    return *this;
}

SegmentAvailability &SegmentAvailability::operator=(SegmentAvailability &&to_move)
{
    m_availabilityStartTime = std::move(to_move.m_availabilityStartTime);
    m_availabilityEndTime = std::move(to_move.m_availabilityEndTime);
    m_segmentDuration = std::move(to_move.m_segmentDuration);
    m_segmentURL = std::move(to_move.m_segmentURL);

    return *this;
}

int SegmentAvailability::compare(const SegmentAvailability &to_compare) const
{
    if (m_availabilityStartTime < to_compare.m_availabilityStartTime) return 1;
    if (m_availabilityStartTime > to_compare.m_availabilityStartTime) return -1;

    if (m_availabilityEndTime) {
        if (to_compare.m_availabilityEndTime) {
            if (m_availabilityEndTime < to_compare.m_availabilityEndTime) return 1;
            if (m_availabilityEndTime > to_compare.m_availabilityEndTime) return -1;
        } else {
            return -1;
        }
    } else {
        if (to_compare.m_availabilityEndTime) {
            return 1;
        }
    }

    if (m_segmentDuration < to_compare.m_segmentDuration) return 1;
    if (m_segmentDuration >  to_compare.m_segmentDuration) return -1;

    if (m_segmentURL.str() < to_compare.m_segmentURL.str()) return 1;
    if (m_segmentURL.str() > to_compare.m_segmentURL.str()) return -1;

    return 0;
}

bool SegmentAvailability::isAvailable() const
{
    auto now = std::chrono::system_clock::now();
    if (now < m_availabilityStartTime) return false;

    if (m_availabilityEndTime) {
        if (now >= m_availabilityEndTime.value()) return false;
    }

    return true;
}

std::size_t SegmentAvailability::hash() const noexcept
{
    auto h1 = std::hash<time_type::duration::rep>{}(m_availabilityStartTime.time_since_epoch().count());
    auto h2 = std::hash<duration_type::rep>{}(m_segmentDuration.count());
    auto h3 = std::hash<std::string>{}(m_segmentURL.str());
    std::size_t h4 = 0;
    if (m_availabilityEndTime) {
        h4 = std::hash<time_type::duration::rep>{}(m_availabilityEndTime.value().time_since_epoch().count());
    }

    return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
}

LIBMPDPP_NAMESPACE_END

std::ostream &operator<<(std::ostream &os, const LIBMPDPP_NAMESPACE_CLASS(SegmentAvailability) &s)
{
    os << s.segmentURL().str() << " (avail. " << s.availabilityStartTime();
    if (s.hasAvailabilityEndTime()) {
        os << " - " << s.availabilityEndTime().value();
    }
    os << ", duration " << s.segmentDuration() << ")";
    return os;
}

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
