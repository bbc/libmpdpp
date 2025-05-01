/*****************************************************************************
 * DASH MPD parsing library in C++: SegmentBase class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <format>
#include <optional>
#include <string>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/exceptions.hh"
#include "libmpd++/Period.hh"

#include "constants.hh"
#include "conversions.hh"

#include "libmpd++/SegmentBase.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

SegmentBase::SegmentBase()
    :m_timescale()
    ,m_eptDelta()
    ,m_pdDelta()
    ,m_presentationTimeOffset()
    ,m_presentationDuration()
    ,m_timeShiftBufferDepth()
    ,m_indexRange()
    ,m_indexRangeExact(false)
    ,m_availabilityTimeOffset()
    ,m_availabilityTimeComplete(true)
    ,m_initialization()
    ,m_representationIndex()
    ,m_failoverContent()
{
}

SegmentBase::SegmentBase(const SegmentBase &other)
    :m_timescale(other.m_timescale)
    ,m_eptDelta(other.m_eptDelta)
    ,m_pdDelta(other.m_pdDelta)
    ,m_presentationTimeOffset(other.m_presentationTimeOffset)
    ,m_presentationDuration(other.m_presentationDuration)
    ,m_timeShiftBufferDepth(other.m_timeShiftBufferDepth)
    ,m_indexRange(other.m_indexRange)
    ,m_indexRangeExact(other.m_indexRangeExact)
    ,m_availabilityTimeOffset(other.m_availabilityTimeOffset)
    ,m_availabilityTimeComplete(other.m_availabilityTimeComplete)
    ,m_initialization(other.m_initialization)
    ,m_representationIndex(other.m_representationIndex)
    ,m_failoverContent(other.m_failoverContent)
{
}

SegmentBase::SegmentBase(SegmentBase &&other)
    :m_timescale(std::move(other.m_timescale))
    ,m_eptDelta(std::move(other.m_eptDelta))
    ,m_pdDelta(std::move(other.m_pdDelta))
    ,m_presentationTimeOffset(std::move(other.m_presentationTimeOffset))
    ,m_presentationDuration(std::move(other.m_presentationDuration))
    ,m_timeShiftBufferDepth(std::move(other.m_timeShiftBufferDepth))
    ,m_indexRange(std::move(other.m_indexRange))
    ,m_indexRangeExact(other.m_indexRangeExact)
    ,m_availabilityTimeOffset(std::move(other.m_availabilityTimeOffset))
    ,m_availabilityTimeComplete(other.m_availabilityTimeComplete)
    ,m_initialization(std::move(other.m_initialization))
    ,m_representationIndex(std::move(other.m_representationIndex))
    ,m_failoverContent(std::move(other.m_failoverContent))
{
}

SegmentBase &SegmentBase::operator=(const SegmentBase &other)
{
    m_timescale = other.m_timescale;
    m_eptDelta = other.m_eptDelta;
    m_pdDelta = other.m_pdDelta;
    m_presentationTimeOffset = other.m_presentationTimeOffset;
    m_presentationDuration = other.m_presentationDuration;
    m_timeShiftBufferDepth = other.m_timeShiftBufferDepth;
    m_indexRange = other.m_indexRange;
    m_indexRangeExact = other.m_indexRangeExact;
    m_availabilityTimeOffset = other.m_availabilityTimeOffset;
    m_availabilityTimeComplete = other.m_availabilityTimeComplete;
    m_initialization = other.m_initialization;
    m_representationIndex = other.m_representationIndex;
    m_failoverContent = other.m_failoverContent;
    return *this;
}

SegmentBase &SegmentBase::operator=(SegmentBase &&other)
{
    m_timescale = std::move(other.m_timescale);
    m_eptDelta = std::move(other.m_eptDelta);
    m_pdDelta = std::move(other.m_pdDelta);
    m_presentationTimeOffset = std::move(other.m_presentationTimeOffset);
    m_presentationDuration = std::move(other.m_presentationDuration);
    m_timeShiftBufferDepth = std::move(other.m_timeShiftBufferDepth);
    m_indexRange = std::move(other.m_indexRange);
    m_indexRangeExact = other.m_indexRangeExact;
    m_availabilityTimeOffset = std::move(other.m_availabilityTimeOffset);
    m_availabilityTimeComplete = other.m_availabilityTimeComplete;
    m_initialization = std::move(other.m_initialization);
    m_representationIndex = std::move(other.m_representationIndex);
    m_failoverContent = std::move(other.m_failoverContent);
    return *this;
}

bool SegmentBase::operator==(const SegmentBase &other) const
{
    if (m_indexRangeExact != other.m_indexRangeExact) return false;
    if (m_availabilityTimeComplete != other.m_availabilityTimeComplete) return false;

#define COMPARE_OPT_VALUES(var) do { \
        if (var.has_value() != other.var.has_value()) return false; \
        if (var.has_value() && !(var.value() == other.var.value())) return false; \
    } while (0)

    COMPARE_OPT_VALUES(m_timescale);
    COMPARE_OPT_VALUES(m_eptDelta);
    COMPARE_OPT_VALUES(m_pdDelta);
    COMPARE_OPT_VALUES(m_presentationTimeOffset);
    COMPARE_OPT_VALUES(m_presentationDuration);
    COMPARE_OPT_VALUES(m_timeShiftBufferDepth);
    COMPARE_OPT_VALUES(m_indexRange);
    COMPARE_OPT_VALUES(m_availabilityTimeOffset);
    COMPARE_OPT_VALUES(m_initialization);
    COMPARE_OPT_VALUES(m_representationIndex);
    COMPARE_OPT_VALUES(m_failoverContent);

#undef COMPARE_OPT_VALUES

    return true;
}

/* protected: */
SegmentBase::SegmentBase(xmlpp::Node &node)
{
    static const xmlpp::Node::PrefixNsMap ns_map = {
        {"mpd", MPD_NS}
    };
    xmlpp::Node::NodeSet node_set;

    node_set = node.find("@timescale");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_timescale = static_cast<unsigned int>(std::stoul(attr->get_value()));
    }

    node_set = node.find("@eptDelta");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_eptDelta = std::stoi(attr->get_value());
    }

    node_set = node.find("@pdDelta");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_pdDelta = std::stoi(attr->get_value());
    }

    node_set = node.find("@presentationTimeOffset");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_presentationTimeOffset = std::stoul(attr->get_value());
    }

    node_set = node.find("@presentationDuration");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_presentationDuration = std::stoul(attr->get_value());
    }

    node_set = node.find("@timeShiftBufferDepth");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_timeShiftBufferDepth = str_to_duration<duration_type>(std::string(attr->get_value()));
    }

    node_set = node.find("@indexRange");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_indexRange = SingleRFC7233Range(attr->get_value());
    }

    node_set = node.find("@indexRangeExact");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_indexRangeExact = (attr->get_value() == "true");
    }

    node_set = node.find("@availabilityTimeOffset");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_availabilityTimeOffset = std::stod(attr->get_value());
    }

    node_set = node.find("@availabilityTimeComplete");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_availabilityTimeComplete = !(attr->get_value() == "false");
    }

    // Elements
    node_set = node.find("mpd:Initialization", ns_map);
    if (node_set.size() == 1) {
        m_initialization = URL(*node_set.front());
    } else if (node_set.size() > 1) {
        throw ParseError("A SegmentBase can only have one Initialization element");
    }

    node_set = node.find("mpd:RepresentationIndex", ns_map);
    if (node_set.size() == 1) {
        m_representationIndex = URL(*node_set.front());
    } else if (node_set.size() > 1) {
        throw ParseError("A SegmentBase can only have one RepresentationIndex element");
    }

    node_set = node.find("mpd:FailoverContent", ns_map);
    if (node_set.size() == 1) {
        m_failoverContent = FailoverContent(*node_set.front());
    } else if (node_set.size() > 1) {
        throw ParseError("A SegmentBase can only have one FailoverContent element");
    }
}

void SegmentBase::setXMLElement(xmlpp::Element &elem) const
{
    // Attributes
    if (m_timescale.has_value()) {
        elem.set_attribute("timescale", std::format("%u", m_timescale.value()));
    }
    if (m_eptDelta.has_value()) {
        elem.set_attribute("eptDelta", std::format("%i", m_eptDelta.value()));
    }
    if (m_pdDelta.has_value()) {
        elem.set_attribute("pdDelta", std::format("%i", m_pdDelta.value()));
    }
    if (m_presentationTimeOffset.has_value()) {
        elem.set_attribute("presentationTimeOffset", std::format("%lu", m_presentationTimeOffset.value()));
    }
    if (m_presentationDuration.has_value()) {
        elem.set_attribute("presentationDuration", std::format("%lu", m_presentationDuration.value()));
    }
    if (m_timeShiftBufferDepth.has_value()) {
        elem.set_attribute("timeShiftBufferDepth", format_duration(m_timeShiftBufferDepth.value()));
    }
    if (m_indexRange.has_value()) {
        elem.set_attribute("indexRange", std::string(m_indexRange.value()));
    }
    if (m_indexRangeExact) {
        elem.set_attribute("indexRangeExact", "true");
    }
    if (m_availabilityTimeOffset.has_value()) {
        elem.set_attribute("availabilityTimeOffset", std::format("%f", m_availabilityTimeOffset.value()));
    }
    if (!m_availabilityTimeComplete) {
        elem.set_attribute("availabilityTimeComplete", "false");
    }
    // Elements
    if (m_initialization.has_value()) {
        xmlpp::Element *child = elem.add_child_element("Initialization");
        m_initialization.value().setXMLElement(*child);
    }
    if (m_representationIndex.has_value()) {
        xmlpp::Element *child = elem.add_child_element("RepresentationIndex");
        m_representationIndex.value().setXMLElement(*child);
    }
    if (m_failoverContent.has_value()) {
        xmlpp::Element *child = elem.add_child_element("FailoverContent");
        m_failoverContent.value().setXMLElement(*child);
    }
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
