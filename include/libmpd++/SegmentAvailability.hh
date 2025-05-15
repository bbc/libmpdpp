#ifndef _BBC_PARSE_DASH_MPD_SEGMENT_AVAILABILITY_HH_
#define _BBC_PARSE_DASH_MPD_SEGMENT_AVAILABILITY_HH_
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
#include <iostream>
#include <optional>

#include "macros.hh"
#include "URI.hh"

LIBMPDPP_NAMESPACE_BEGIN

/** SegmentAvailability class
 *
 * This class is used to return details of the availability of a segment and where it can be found
 */
class LIBMPDPP_PUBLIC_API SegmentAvailability {
public:
    using time_type = std::chrono::system_clock::time_point;
    using duration_type = std::chrono::microseconds;

    SegmentAvailability();
    SegmentAvailability(const SegmentAvailability &to_copy);
    SegmentAvailability(SegmentAvailability &&to_move);
    SegmentAvailability(const time_type &availability_start, const duration_type &segment_length, const URI &segment_url,
                        const std::optional<time_type> &availability_end = std::nullopt);

    virtual ~SegmentAvailability() {};

    SegmentAvailability &operator=(const SegmentAvailability &to_copy);
    SegmentAvailability &operator=(SegmentAvailability &&to_move);

    int compare(const SegmentAvailability &to_compare) const;
    bool operator<(const SegmentAvailability &to_compare) const { return compare(to_compare) > 0; };
    bool operator<=(const SegmentAvailability &to_compare) const { return compare(to_compare) >= 0; };
    bool operator==(const SegmentAvailability &to_compare) const { return compare(to_compare) == 0; };
    bool operator!=(const SegmentAvailability &to_compare) const { return compare(to_compare) != 0; };
    bool operator>(const SegmentAvailability &to_compare) const { return compare(to_compare) < 0; };
    bool operator>=(const SegmentAvailability &to_compare) const { return compare(to_compare) <= 0; };

    // Accessors
    const time_type &availabilityStartTime() const { return m_availabilityStartTime; };
    SegmentAvailability &availabilityStartTime(const time_type &val) { m_availabilityStartTime = val; return *this; };
    SegmentAvailability &availabilityStartTime(time_type &&val) { m_availabilityStartTime = std::move(val); return *this; };

    bool hasAvailabilityEndTime() const { return m_availabilityEndTime.has_value(); };
    const std::optional<time_type> &availabilityEndTime() const { return m_availabilityEndTime; };
    SegmentAvailability &availabilityEndTime(const std::nullopt_t&) { m_availabilityEndTime.reset(); return *this; };
    SegmentAvailability &availabilityEndTime(const time_type &val) { m_availabilityEndTime = val; return *this; };
    SegmentAvailability &availabilityEndTime(time_type &&val) { m_availabilityEndTime = std::move(val); return *this; };
    SegmentAvailability &availabilityEndTime(const std::optional<time_type> &val) { m_availabilityEndTime = val; return *this; };
    SegmentAvailability &availabilityEndTime(std::optional<time_type> &&val) { m_availabilityEndTime = std::move(val); return *this; };

    const duration_type &segmentDuration() const { return m_segmentDuration; };
    SegmentAvailability &segmentDuration(const duration_type &val) { m_segmentDuration = val; return *this; };
    SegmentAvailability &segmentDuration(duration_type &&val) { m_segmentDuration = std::move(val); return *this; };

    const URI &segmentURL() const { return m_segmentURL; };
    SegmentAvailability &segmentURL(const URI &val) { m_segmentURL = val; return *this; };
    SegmentAvailability &segmentURL(URI &&val) { m_segmentURL = std::move(val); return *this; };

    // Convenience
    bool isAvailable() const;

    std::size_t hash() const noexcept;

private:
    // SegmentAvailability for query results
    time_type m_availabilityStartTime;
    std::optional<time_type> m_availabilityEndTime;
    duration_type m_segmentDuration;
    URI m_segmentURL;
};

LIBMPDPP_NAMESPACE_END

namespace std {
    template<>
    struct hash<LIBMPDPP_NAMESPACE_CLASS(SegmentAvailability)> {
        std::size_t operator()(const LIBMPDPP_NAMESPACE_CLASS(SegmentAvailability) &s) const noexcept {
            return s.hash();
        };
    };
}

LIBMPDPP_PUBLIC_API std::ostream &operator<<(std::ostream &os, const LIBMPDPP_NAMESPACE_CLASS(SegmentAvailability) &s);

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SEGMENT_AVAILABILITY_HH_*/
