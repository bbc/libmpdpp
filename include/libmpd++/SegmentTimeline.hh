#ifndef _BBC_PARSE_DASH_MPD_SEGMENT_TIMELINE_HH_
#define _BBC_PARSE_DASH_MPD_SEGMENT_TIMELINE_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: SegmentTimeline class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <chrono>
#include <functional>
#include <optional>
#include <list>

#include "macros.hh"
#include "FailoverContent.hh"
#include "SingleRFC7233Range.hh"
#include "URL.hh"

/**@cond
 */
// Forward declarations for types only used by pointer or reference
namespace xmlpp {
    class Element;
    class Node;
}
/**@endcond
 */

LIBMPDPP_NAMESPACE_BEGIN

/** SegmentTimeline class
 * @headerfile libmpd++/SegmentTimeline.hh <libmpd++/SegmentTimeline.hh>
 *
 * Container for %DASH %MPD schema %SegmentTimelineType found in ISO 23009-1:2022 Clause 5.3.9.6.3.
 */
class LIBMPDPP_PUBLIC_API SegmentTimeline {
public:
    using duration_type = std::chrono::microseconds;

    /** SegmentTimeline::S class
     *
     * Container for %DASH %MPD schema %SType.
     */
    class LIBMPDPP_PUBLIC_API S {
    public:
        S();
        S(const S&);
        S(S&&);

        virtual ~S() {};

        S &operator=(const S&);
        S &operator=(S&&);

        bool operator==(const S&) const;

    ///@cond PROTECTED
    protected:
        friend class SegmentTimeline;
        S(xmlpp::Node&);
        void setXMLElement(xmlpp::Element&) const;
    ///@endcond PROTECTED

    private:
        // S element type ISO 23009-1:2022 Clause 5.3.9.6.3
        std::optional<unsigned long> m_t;
        std::optional<unsigned long> m_n;
        unsigned long m_d;
        int m_r;
        unsigned long m_k;
    };

    SegmentTimeline() :m_sLines() {};
    SegmentTimeline(const SegmentTimeline &other) :m_sLines(other.m_sLines) {};
    SegmentTimeline(SegmentTimeline &&other) :m_sLines(std::move(other.m_sLines)) {};

    virtual ~SegmentTimeline() {};

    SegmentTimeline &operator=(const SegmentTimeline &other) { m_sLines = other.m_sLines; return *this; };
    SegmentTimeline &operator=(SegmentTimeline &&other) { m_sLines = std::move(other.m_sLines); return *this; };

    bool operator==(const SegmentTimeline &other) const { return m_sLines == other.m_sLines; };

    /**@{*/
    /** Segment timeline queries
     *
     * A SegmentTimeline describes its segments as a sequence of series (@c S elements), each series
     * covering @c \@r + 1 segments of identical duration @c \@d starting at @c \@t. These map an
     * index, counted from the first segment the timeline describes and therefore corresponding to
     * @c \@startNumber, to that segment's start time and duration, and back.
     *
     * ISO/IEC 23009-1:2026 clause 5.3.9.6.3, Table 24, @c \@t: "If not present, then the value shall
     * be assumed to be zero for the first S element and for the subsequent S elements, the value
     * shall be assumed to be the sum of the previous S element's earliest presentation time and
     * contiguous duration."
     *
     * Times and durations are in @c \@timescale units, as they appear in the timeline.
     */
    /** Number of segments this timeline describes */
    unsigned long segmentCount() const;
    /** Start time of the segment at @p index, or @c std::nullopt if @p index is out of range */
    std::optional<unsigned long> segmentStartTime(unsigned long index) const;
    /** Duration of the segment at @p index, or @c std::nullopt if @p index is out of range */
    std::optional<unsigned long> segmentDuration(unsigned long index) const;
    /** Index of the segment whose interval contains @p time, or @c std::nullopt if @p time lies
     *  outside every series this timeline describes */
    std::optional<unsigned long> segmentIndexForTime(unsigned long time) const;
    /**@}*/

///@cond PROTECTED
protected:
    friend class MultipleSegmentBase;
    void forEachSegment(const std::function<bool(unsigned long, unsigned long, unsigned long)> &fn) const;
    SegmentTimeline(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // SegmentTimeline element from ISO 23009-1:2022 Clause 5.3.9.6.3
    std::list<S> m_sLines;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SEGMENT_TIMELINE_HH_*/
