#ifndef _BBC_PARSE_DASH_MPD_SEGMENT_BASE_HH_
#define _BBC_PARSE_DASH_MPD_SEGMENT_BASE_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: SegmentBase class
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

class AdaptationSet;
class Representation;

/** SegmentBase class
 *
 * Container for %DASH %MPD schema %SegmentBaseType.
 */
class LIBMPDPP_PUBLIC_API SegmentBase {
public:
    using duration_type = std::chrono::microseconds;

    SegmentBase();
    SegmentBase(const SegmentBase &other);
    SegmentBase(SegmentBase &&other);

    virtual ~SegmentBase() {};

    SegmentBase &operator=(const SegmentBase &other);
    SegmentBase &operator=(SegmentBase &&other);

    bool operator==(const SegmentBase &other) const;

    // @timescale
    bool hasTimescale() const { return m_timescale.has_value(); };
    const std::optional<unsigned int> &timescale() const { return m_timescale; };
    SegmentBase &timescale(const std::nullopt_t&) { m_timescale.reset(); return *this; };
    SegmentBase &timescale(unsigned int val) { m_timescale = val; return *this; };

    // @eptDelta
    bool hasEptDelta() const { return m_eptDelta.has_value(); };
    const std::optional<int> &eptDelta() const { return m_eptDelta; };
    SegmentBase &eptDelta(const std::nullopt_t&) { m_eptDelta.reset(); return *this; };
    SegmentBase &eptDelta(int val) { m_eptDelta = val; return *this; };

    // @pdDelta
    bool hasPdDelta() const { return m_pdDelta.has_value(); };
    const std::optional<int> &pdDelta() const { return m_pdDelta; };
    SegmentBase &pdDelta(const std::nullopt_t&) { m_pdDelta.reset(); return *this; };
    SegmentBase &pdDelta(int val) { m_pdDelta = val; return *this; };

    // @presentationTimeOffest
    bool hasPresentationTimeOffest() const { return m_presentationTimeOffset.has_value(); };
    const std::optional<unsigned long> &presentationTimeOffest() const { return m_presentationTimeOffset; };
    SegmentBase &presentationTimeOffest(const std::nullopt_t&) { m_presentationTimeOffset.reset(); return *this; };
    SegmentBase &presentationTimeOffest(unsigned long val) { m_presentationTimeOffset = val; return *this; };

    // @presentationDuration
    bool hasPresentationDuration() const { return m_presentationDuration.has_value(); };
    const std::optional<unsigned long> &presentationDuration() const { return m_presentationDuration; };
    SegmentBase &presentationDuration(const std::nullopt_t&) { m_presentationDuration.reset(); return *this; };
    SegmentBase &presentationDuration(unsigned long val) { m_presentationDuration = val; return *this; };

    // @timeShiftBufferDepth
    bool hasTimeShiftBufferDepth() const { return m_timeShiftBufferDepth.has_value(); };
    const std::optional<duration_type> &timeShiftBufferDepth() const { return m_timeShiftBufferDepth; };
    SegmentBase &timeShiftBufferDepth(const std::nullopt_t&) { m_timeShiftBufferDepth.reset(); return *this; };
    SegmentBase &timeShiftBufferDepth(const duration_type &val) { m_timeShiftBufferDepth = val; return *this; };
    SegmentBase &timeShiftBufferDepth(duration_type &&val) { m_timeShiftBufferDepth = std::move(val); return *this; };

    // @indexRange
    bool hasIndexRange() const { return m_indexRange.has_value(); };
    const std::optional<SingleRFC7233Range> &indexRange() const { return m_indexRange; };
    SegmentBase &indexRange(const std::nullopt_t&) { m_indexRange.reset(); return *this; };
    SegmentBase &indexRange(const SingleRFC7233Range &val) { m_indexRange = val; return *this; };
    SegmentBase &indexRange(SingleRFC7233Range &&val) { m_indexRange = std::move(val); return *this; };

    // @indexRangeExact
    bool indexRangeExact() const { return m_indexRangeExact; };
    SegmentBase &indexRangeExact(bool val) { m_indexRangeExact = val; return *this; };

    // @availabilityTimeOffset
    bool hasAvailabilityTimeOffset() const { return m_availabilityTimeOffset.has_value(); };
    const std::optional<double> &availabilityTimeOffset() const { return m_availabilityTimeOffset; };
    SegmentBase &availabilityTimeOffset(const std::nullopt_t&) { m_availabilityTimeOffset.reset(); return *this; };
    SegmentBase &availabilityTimeOffset(double val) { m_availabilityTimeOffset = val; return *this; };

    // @availabilityTimeComplete
    bool availabilityTimeComplete() const { return m_availabilityTimeComplete; };
    SegmentBase &availabilityTimeComplete(bool val) { m_availabilityTimeComplete = val; return *this; };

    // Initialization child
    bool hasInitialization() const { return m_initialization.has_value(); };
    const std::optional<URL> &initialization() const { return m_initialization; };
    SegmentBase &initialization(const std::nullopt_t&) { m_initialization.reset(); return *this; };
    SegmentBase &initialization(const URL &val) { m_initialization = val; return *this; };
    SegmentBase &initialization(URL &&val) { m_initialization = std::move(val); return *this; };

    // RepresentationIndex child
    bool hasRepresentationIndex() const { return m_representationIndex.has_value(); };
    const std::optional<URL> &representationIndex() const { return m_representationIndex; };
    SegmentBase &representationIndex(const std::nullopt_t&) { m_representationIndex.reset(); return *this; };
    SegmentBase &representationIndex(const URL &val) { m_representationIndex = val; return *this; };
    SegmentBase &representationIndex(URL &&val) { m_representationIndex = std::move(val); return *this; };

    // FailoverContent child
    bool hasFailoverContent() const { return m_failoverContent.has_value(); };
    const std::optional<FailoverContent> &failoverContent() const { return m_failoverContent; };
    SegmentBase &failoverContent(const std::nullopt_t&) { m_failoverContent.reset(); return *this; };
    SegmentBase &failoverContent(const FailoverContent &val) { m_failoverContent = val; return *this; };
    SegmentBase &failoverContent(FailoverContent &&val) { m_failoverContent = std::move(val); return *this; };

///@cond PROTECTED
protected:
    friend class Period;
    friend class Representation;
    friend class AdaptationSet;
    SegmentBase(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // SegmentBase element from ISO 23009-1:2022 Clause 5.3.9.2.3
    // Attributes
    std::optional<unsigned int> m_timescale;
    std::optional<int> m_eptDelta;
    std::optional<int> m_pdDelta;
    std::optional<unsigned long> m_presentationTimeOffset;
    std::optional<unsigned long> m_presentationDuration;
    std::optional<duration_type> m_timeShiftBufferDepth;
    std::optional<SingleRFC7233Range> m_indexRange;
    bool m_indexRangeExact;
    std::optional<double> m_availabilityTimeOffset;
    bool m_availabilityTimeComplete;
    // Elements
    std::optional<URL> m_initialization;
    std::optional<URL> m_representationIndex;
    std::optional<FailoverContent> m_failoverContent;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SEGMENT_BASE_HH_*/
