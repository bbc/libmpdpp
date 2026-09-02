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
#include <optional>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/exceptions.hh"
#include "libmpd++/FailoverContent.hh"
#include "libmpd++/SingleRFC7233Range.hh"
#include "libmpd++/URL.hh"

#include "constants.hh"
#include "conversions.hh"

#include <functional>

#include "libmpd++/SegmentTimeline.hh"

LIBMPDPP_NAMESPACE_BEGIN

/****** SegmentTimeline::S ******/

SegmentTimeline::S::S()
    :m_t()
    ,m_n()
    ,m_d(0)
    ,m_r(0)
    ,m_k(1)
{
}

SegmentTimeline::S::S(const SegmentTimeline::S &other)
    :m_t(other.m_t)
    ,m_n(other.m_n)
    ,m_d(other.m_d)
    ,m_r(other.m_r)
    ,m_k(other.m_k)
{
}

SegmentTimeline::S::S(SegmentTimeline::S &&other)
    :m_t(std::move(other.m_t))
    ,m_n(std::move(other.m_n))
    ,m_d(std::move(other.m_d))
    ,m_r(std::move(other.m_r))
    ,m_k(std::move(other.m_k))
{
}

SegmentTimeline::S &SegmentTimeline::S::operator=(const SegmentTimeline::S &other)
{
    m_t = other.m_t;
    m_n = other.m_n;
    m_d = other.m_d;
    m_r = other.m_r;
    m_k = other.m_k;
    return *this;
}

SegmentTimeline::S &SegmentTimeline::S::operator=(SegmentTimeline::S &&other)
{
    m_t = std::move(other.m_t);
    m_n = std::move(other.m_n);
    m_d = other.m_d;
    m_r = other.m_r;
    m_k = other.m_k;
    return *this;
}

bool SegmentTimeline::S::operator==(const SegmentTimeline::S &other) const
{
    if (m_t != other.m_t) return false;
    if (m_n != other.m_n) return false;
    if (m_d != other.m_d) return false;
    if (m_r != other.m_r) return false;
    if (m_k != other.m_k) return false;

    return true;
}

// protected for SegmentTimeline::S

SegmentTimeline::S::S(xmlpp::Node &node)
    :m_t()
    ,m_n()
    ,m_d(0)
    ,m_r(0)
    ,m_k(1)
{
    xmlpp::Node::NodeSet node_set;

    node_set = node.find("@t");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_t = std::stoul(std::string(attr->get_value()));
    }

    node_set = node.find("@n");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_n = std::stoul(std::string(attr->get_value()));
    }

    node_set = node.find("@d");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_d = std::stoul(std::string(attr->get_value()));
    } else {
        throw ParseError("SegmentTimeline/S must have a \"d\" attribute");
    }

    node_set = node.find("@r");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_r = std::stoi(std::string(attr->get_value()));
    }

    node_set = node.find("@k");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_k = std::stoul(std::string(attr->get_value()));
    }
}

void SegmentTimeline::S::setXMLElement(xmlpp::Element &elem) const
{
}

/******** SegmentTimeline ********/

// protected:

SegmentTimeline::SegmentTimeline(xmlpp::Node &node)
    :m_sLines()
{
    static const xmlpp::Node::PrefixNsMap ns_map = {
        {"mpd", MPD_NS}
    };
    xmlpp::Node::NodeSet node_set = node.find("mpd:S", ns_map);

    for (auto node : node_set) {
        m_sLines.push_back(S(*node));
    }
}

void SegmentTimeline::setXMLElement(xmlpp::Element &elem) const
{
    for (auto &s : m_sLines) {
        xmlpp::Element *child = elem.add_child_element("S");
        s.setXMLElement(*child);
    }
}


/* Walks the segments this timeline describes, calling @p fn(index, start, duration) for each until
   it returns true. Series are contiguous by default: ISO/IEC 23009-1:2026 clause 5.3.9.6.3,
   Table 24, @t: "If not present, then the value shall be assumed to be zero for the first S element
   and for the subsequent S elements, the value shall be assumed to be the sum of the previous S
   element's earliest presentation time and contiguous duration."

   A negative @r repeats the series until the start of the next one, or to the end of the Period for
   the last series. The Period's duration is not visible here, so a negative @r on the final series
   is taken as describing a single segment; a caller needing the open-ended case must bound it from
   the Period itself. */
void SegmentTimeline::forEachSegment(const std::function<bool(unsigned long, unsigned long, unsigned long)> &fn) const
{
    unsigned long index = 0;
    unsigned long next_start = 0;

    for (auto it = m_sLines.cbegin(); it != m_sLines.cend(); ++it) {
        unsigned long start = it->m_t.has_value() ? it->m_t.value() : next_start;
        unsigned long dur = it->m_d;
        if (dur == 0) continue; // a zero duration series describes nothing addressable
        unsigned long repeats;
        if (it->m_r < 0) {
            auto next = std::next(it);
            if (next != m_sLines.cend() && next->m_t.has_value() && next->m_t.value() > start) {
                unsigned long span = next->m_t.value() - start;
                repeats = (span + dur - 1) / dur;
                if (repeats > 0) repeats -= 1;
            } else {
                repeats = 0;
            }
        } else {
            repeats = static_cast<unsigned long>(it->m_r);
        }
        for (unsigned long i = 0; i <= repeats; i++) {
            if (fn(index, start, dur)) return;
            index++;
            start += dur;
        }
        next_start = start;
    }
}

unsigned long SegmentTimeline::segmentCount() const
{
    unsigned long count = 0;
    forEachSegment([&count](unsigned long, unsigned long, unsigned long) -> bool {
            count++;
            return false;
        });
    return count;
}

std::optional<unsigned long> SegmentTimeline::segmentStartTime(unsigned long index) const
{
    std::optional<unsigned long> ret;
    forEachSegment([&ret, index](unsigned long i, unsigned long start, unsigned long) -> bool {
            if (i != index) return false;
            ret = start;
            return true;
        });
    return ret;
}

std::optional<unsigned long> SegmentTimeline::segmentDuration(unsigned long index) const
{
    std::optional<unsigned long> ret;
    forEachSegment([&ret, index](unsigned long i, unsigned long, unsigned long dur) -> bool {
            if (i != index) return false;
            ret = dur;
            return true;
        });
    return ret;
}

std::optional<unsigned long> SegmentTimeline::segmentIndexForTime(unsigned long time) const
{
    std::optional<unsigned long> ret;
    forEachSegment([&ret, time](unsigned long i, unsigned long start, unsigned long dur) -> bool {
            if (time < start || time >= start + dur) return false;
            ret = i;
            return true;
        });
    return ret;
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
