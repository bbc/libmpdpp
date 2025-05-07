#ifndef _BBC_PARSE_DASH_MPD_MULTIPLE_SEGMENT_BASE_HH_
#define _BBC_PARSE_DASH_MPD_MULTIPLE_SEGMENT_BASE_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: MultipleSegmentBase class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <optional>

#include "macros.hh"
#include "SegmentBase.hh"
#include "SegmentTimeline.hh"
#include "URL.hh"

namespace xmlpp {
    class Element;
    class Node;
}

LIBPARSEMPD_NAMESPACE_BEGIN

class LIBPARSEMPD_PUBLIC_API MultipleSegmentBase : public SegmentBase {
public:
    using duration_type = SegmentBase::duration_type;

    MultipleSegmentBase();
    MultipleSegmentBase(const MultipleSegmentBase &other);
    MultipleSegmentBase(MultipleSegmentBase &&other);

    virtual ~MultipleSegmentBase() {};

    MultipleSegmentBase &operator=(const MultipleSegmentBase &other);
    MultipleSegmentBase &operator=(MultipleSegmentBase &&other);

    bool operator==(const MultipleSegmentBase &other) const;

    // @duration
    bool hasDuration() const { return m_duration.has_value(); };
    const std::optional<unsigned int> &duration() const { return m_duration; };
    MultipleSegmentBase &duration(const std::nullopt_t&) { m_duration.reset(); return *this; };
    MultipleSegmentBase &duration(unsigned int val) { m_duration = val; return *this; };

    // @startNumber
    bool hasStartNumber() const { return m_startNumber.has_value(); };
    const std::optional<unsigned int> &startNumber() const { return m_startNumber; };
    MultipleSegmentBase &startNumber(const std::nullopt_t&) { m_startNumber.reset(); return *this; };
    MultipleSegmentBase &startNumber(unsigned int val) { m_startNumber = val; return *this; };

    // @endNumber
    bool hasEndNumber() const { return m_endNumber.has_value(); };
    const std::optional<unsigned int> &endNumber() const { return m_endNumber; };
    MultipleSegmentBase &endNumber(const std::nullopt_t&) { m_endNumber.reset(); return *this; };
    MultipleSegmentBase &endNumber(unsigned int val) { m_endNumber = val; return *this; };

    // SegmentTimeline child
    bool hasSegmentTimeline() const { return m_segmentTimeline.has_value(); };
    const std::optional<SegmentTimeline> &segmentTimeline() const { return m_segmentTimeline; };
    MultipleSegmentBase &segmentTimeline(const std::nullopt_t&) { m_segmentTimeline.reset(); return *this; };
    MultipleSegmentBase &segmentTimeline(const SegmentTimeline &val) { m_segmentTimeline = val; return *this; };
    MultipleSegmentBase &segmentTimeline(SegmentTimeline &&val) { m_segmentTimeline = std::move(val); return *this; };

    // BitstreamSwitching child
    bool hasBitstreamSwitching() const { return m_bitstreamSwitching.has_value(); };
    const std::optional<URL> &bitstreamSwitching() const { return m_bitstreamSwitching; };
    MultipleSegmentBase &bitstreamSwitching(const std::nullopt_t&) { m_bitstreamSwitching.reset(); return *this; };
    MultipleSegmentBase &bitstreamSwitching(const URL &val) { m_bitstreamSwitching = val; return *this; };
    MultipleSegmentBase &bitstreamSwitching(URL &&val) { m_bitstreamSwitching = std::move(val); return *this; };

protected:
    MultipleSegmentBase(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    // MultipleSegmentBase element from ISO 23009-1:2022 Clause 5.3.9.2.3
    // Attributes
    std::optional<unsigned int> m_duration;
    std::optional<unsigned int> m_startNumber;
    std::optional<unsigned int> m_endNumber;
    // Elements
    std::optional<SegmentTimeline> m_segmentTimeline;
    std::optional<URL> m_bitstreamSwitching;
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_MULTIPLE_SEGMENT_BASE_HH_*/
