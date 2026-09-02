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
#include <chrono>
#include <optional>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/exceptions.hh"
#include "libmpd++/SegmentBase.hh"
#include "libmpd++/SegmentTimeline.hh"
#include "libmpd++/URL.hh"

#include "constants.hh"
#include "conversions.hh"

#include "libmpd++/MultipleSegmentBase.hh"

LIBMPDPP_NAMESPACE_BEGIN

MultipleSegmentBase::MultipleSegmentBase()
    :SegmentBase()
    ,m_duration()
    ,m_startNumber()
    ,m_endNumber()
    ,m_segmentTimeline()
    ,m_bitstreamSwitching()
{
}

MultipleSegmentBase::MultipleSegmentBase(const MultipleSegmentBase &other)
    :SegmentBase(other)
    ,m_duration(other.m_duration)
    ,m_startNumber(other.m_startNumber)
    ,m_endNumber(other.m_endNumber)
    ,m_segmentTimeline(other.m_segmentTimeline)
    ,m_bitstreamSwitching(other.m_bitstreamSwitching)
{
}

MultipleSegmentBase::MultipleSegmentBase(MultipleSegmentBase &&other)
    :SegmentBase(std::move(other))
    ,m_duration(std::move(other.m_duration))
    ,m_startNumber(std::move(other.m_startNumber))
    ,m_endNumber(std::move(other.m_endNumber))
    ,m_segmentTimeline(std::move(other.m_segmentTimeline))
    ,m_bitstreamSwitching(std::move(other.m_bitstreamSwitching))
{
}

MultipleSegmentBase &MultipleSegmentBase::operator=(const MultipleSegmentBase &other)
{
    m_duration = other.m_duration;
    m_startNumber = other.m_startNumber;
    m_endNumber = other.m_endNumber;
    m_segmentTimeline = other.m_segmentTimeline;
    m_bitstreamSwitching = other.m_bitstreamSwitching;
    return *this;
}

MultipleSegmentBase &MultipleSegmentBase::operator=(MultipleSegmentBase &&other)
{
    m_duration = std::move(other.m_duration);
    m_startNumber = std::move(other.m_startNumber);
    m_endNumber = std::move(other.m_endNumber);
    m_segmentTimeline = std::move(other.m_segmentTimeline);
    m_bitstreamSwitching = std::move(other.m_bitstreamSwitching);
    return *this;
}

bool MultipleSegmentBase::operator==(const MultipleSegmentBase &other) const
{
    if (m_duration != other.m_duration) return false;
    if (m_startNumber != other.m_startNumber) return false;
    if (m_endNumber != other.m_endNumber) return false;
    if (m_segmentTimeline != other.m_segmentTimeline) return false;
    if (m_bitstreamSwitching != other.m_bitstreamSwitching) return false;

    return true;
}

MultipleSegmentBase::duration_type MultipleSegmentBase::durationAsDurationType() const
{
    duration_type ret;

    if (m_duration) {
        double ts = 1.0;
        if (hasTimescale()) {
            ts = 1.0 / timescale().value();
        }
        ret = std::chrono::duration_cast<duration_type>(std::chrono::duration<double, std::ratio<1> >(m_duration.value() * ts));
    }

    return ret;
}

unsigned long MultipleSegmentBase::segmentNumberToTime(unsigned long segment_number) const
{
    // time = m_duration * segment_number since m_duration is already in the correct timescale
    if (m_duration) return m_duration.value() * segment_number;
    // Without @duration the segment times come from the SegmentTimeline, where @startNumber names
    // the first segment described, so segment_number indexes that timeline.
    if (m_segmentTimeline) {
        auto start = m_segmentTimeline.value().segmentStartTime(segment_number);
        if (start) return start.value();
    }
    return 0; // neither @duration nor a timeline: one segment starting at the period start
}

// Get wallclock duration of a segment from Period start
MultipleSegmentBase::duration_type MultipleSegmentBase::segmentNumberToDurationType(unsigned long segment_number) const
{
    // time = m_duration / m_timescale * segment_number, where m_timescale defaults to 1 if not given.
    if (m_duration) return durationAsDurationType() * segment_number;
    if (m_segmentTimeline) {
        auto start = m_segmentTimeline.value().segmentStartTime(segment_number);
        if (start) {
            double ts = hasTimescale()?static_cast<double>(timescale().value()):1.0;
            return std::chrono::duration_cast<duration_type>(std::chrono::duration<double, std::ratio<1> >(start.value() / ts));
        }
    }
    return duration_type(0); // neither @duration nor a timeline: one segment at the period start
}

// Get segment number from offset from Period start in the current timescale
unsigned long MultipleSegmentBase::timeOffsetToSegmentNumber(unsigned long time_offset) const
{
    // segment_number = floor(time_offset / m_duration)
    if (m_duration) return (time_offset / m_duration.value());
    return 0; // no duration then there's only one segment
}

// Get segment number that contains the wallclock duration since Period start
unsigned long MultipleSegmentBase::durationTypeToSegmentNumber(const MultipleSegmentBase::duration_type &offset) const
{
    if (offset.count() < 0) return 0;
    if (m_duration) return (offset / durationAsDurationType());
    /* Without @duration the timeline decides which segment covers this offset. Returning 0 here
       regardless, as this did before, made every time map to the first segment the timeline
       describes, so a live presentation addressed by SegmentTimeline always resolved to the oldest
       segment still in its window however recent the query time. */
    if (m_segmentTimeline) {
        const SegmentTimeline &timeline = m_segmentTimeline.value();
        double ts = hasTimescale()?static_cast<double>(timescale().value()):1.0;
        double secs = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1> > >(offset).count();
        unsigned long time = static_cast<unsigned long>(secs * ts);
        auto index = timeline.segmentIndexForTime(time);
        if (index) return index.value();
        /* Past the end of the timeline, which is normal while the next segment is still being
           produced: the last segment it describes is the most recent one addressable. */
        unsigned long count = timeline.segmentCount();
        if (count > 0) {
            auto last_start = timeline.segmentStartTime(count - 1);
            if (last_start && time >= last_start.value()) return count - 1;
        }
    }
    return 0; // neither @duration nor a timeline: there's only one segment
}

// protected

MultipleSegmentBase::MultipleSegmentBase(xmlpp::Node &node)
    :SegmentBase(node)
    ,m_duration()
    ,m_startNumber()
    ,m_endNumber()
    ,m_segmentTimeline()
    ,m_bitstreamSwitching()
{
    static const xmlpp::Node::PrefixNsMap ns_map = {
        {"mpd", MPD_NS}
    };
    xmlpp::Node::NodeSet node_set;

    node_set = node.find("@duration");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_duration = static_cast<unsigned int>(std::stoul(attr->get_value()));
    }

    node_set = node.find("@startNumber");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_startNumber = static_cast<unsigned int>(std::stoul(attr->get_value()));
    }

    node_set = node.find("@endNumber");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_endNumber = static_cast<unsigned int>(std::stoul(attr->get_value()));
    }

    node_set = node.find("mpd:SegmentTimeline", ns_map);
    if (node_set.size() == 1) {
        m_segmentTimeline = SegmentTimeline(*node_set.front());
    } else if (node_set.size() > 1) {
        throw ParseError("There can be only one SegmentTimeline child of a MultipleSegmentBase type element");
    }

    node_set = node.find("mpd:BitstreamSwitching", ns_map);
    if (node_set.size() == 1) {
        m_bitstreamSwitching = URL(*node_set.front());
    } else if (node_set.size() > 1) {
        throw ParseError("There can be only one BitstreamSwitching child of a MultipleSegmentBase type element");
    }
}

void MultipleSegmentBase::setXMLElement(xmlpp::Element &elem) const
{
    // Do parent class additions first
    SegmentBase::setXMLElement(elem);

    // Attributes
    if (m_duration) {
        elem.set_attribute("duration", std::to_string(m_duration.value()));
    }
    if (m_startNumber) {
        elem.set_attribute("startNumber", std::to_string(m_startNumber.value()));
    }
    if (m_endNumber) {
        elem.set_attribute("endNumber", std::to_string(m_endNumber.value()));
    }
    // Elements
    if (m_segmentTimeline) {
        xmlpp::Element *child = elem.add_child_element("SegmentTimeline");
        m_segmentTimeline.value().setXMLElement(*child);
    }
    if (m_bitstreamSwitching) {
        xmlpp::Element *child = elem.add_child_element("BitstreamSwitching");
        m_bitstreamSwitching.value().setXMLElement(*child);
    }
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
