/*****************************************************************************
 * DASH MPD parsing library in C++: BaseURL class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <chrono>
#include <optional>
#include <string>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/URL.hh"

#include "conversions.hh"

#include "libmpd++/BaseURL.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

BaseURL::BaseURL(const std::string &url)
    :URI(url)
    ,m_serviceLocation()
    ,m_byteRange()
    ,m_availabilityTimeOffset()
    ,m_availabilityTimeComplete()
    ,m_timeShiftBufferDepth()
    ,m_rangeAccess(false)
{
}

BaseURL::BaseURL(std::string &&url)
    :URI(std::move(url))
    ,m_serviceLocation()
    ,m_byteRange()
    ,m_availabilityTimeOffset()
    ,m_availabilityTimeComplete()
    ,m_timeShiftBufferDepth()
    ,m_rangeAccess(false)
{
}

BaseURL::BaseURL(const BaseURL &other)
    :URI(other)
    ,m_serviceLocation(other.m_serviceLocation)
    ,m_byteRange(other.m_byteRange)
    ,m_availabilityTimeOffset(other.m_availabilityTimeOffset)
    ,m_availabilityTimeComplete(other.m_availabilityTimeComplete)
    ,m_timeShiftBufferDepth(other.m_timeShiftBufferDepth)
    ,m_rangeAccess(other.m_rangeAccess)
{
}

BaseURL::BaseURL(BaseURL &&other)
    :URI(std::move(other))
    ,m_serviceLocation(std::move(other.m_serviceLocation))
    ,m_byteRange(std::move(other.m_byteRange))
    ,m_availabilityTimeOffset(std::move(other.m_availabilityTimeOffset))
    ,m_availabilityTimeComplete(std::move(other.m_availabilityTimeComplete))
    ,m_timeShiftBufferDepth(std::move(other.m_timeShiftBufferDepth))
    ,m_rangeAccess(other.m_rangeAccess)
{
}

BaseURL &BaseURL::operator=(const BaseURL &other)
{
    URI::operator=(other);
    m_serviceLocation = other.m_serviceLocation;
    m_byteRange = other.m_byteRange;
    m_availabilityTimeOffset = other.m_availabilityTimeOffset;
    m_availabilityTimeComplete = other.m_availabilityTimeComplete;
    m_timeShiftBufferDepth = other.m_timeShiftBufferDepth;
    m_rangeAccess = other.m_rangeAccess;

    return *this;
}

BaseURL &BaseURL::operator=(BaseURL &&other)
{
    URI::operator=(std::move(other));
    m_serviceLocation = std::move(other.m_serviceLocation);
    m_byteRange = std::move(other.m_byteRange);
    m_availabilityTimeOffset = std::move(other.m_availabilityTimeOffset);
    m_availabilityTimeComplete = std::move(other.m_availabilityTimeComplete);
    m_timeShiftBufferDepth = std::move(other.m_timeShiftBufferDepth);
    m_rangeAccess = other.m_rangeAccess;

    return *this;
}

bool BaseURL::operator==(const BaseURL &other) const
{
    if (!URI::operator==(other)) return false;

    if (m_rangeAccess != other.m_rangeAccess) return false;

    if (m_timeShiftBufferDepth.has_value() != other.m_timeShiftBufferDepth.has_value()) return false;
    if (m_timeShiftBufferDepth.has_value() && m_timeShiftBufferDepth.value() != other.m_timeShiftBufferDepth.value()) return false;

    if (m_availabilityTimeComplete.has_value() != other.m_availabilityTimeComplete.has_value()) return false;
    if (m_availabilityTimeComplete.has_value() && m_availabilityTimeComplete.value() != other.m_availabilityTimeComplete.value())
        return false;

    if (m_availabilityTimeOffset.has_value() != other.m_availabilityTimeOffset.has_value()) return false;
    if (m_availabilityTimeOffset.has_value() && m_availabilityTimeOffset.value() != other.m_availabilityTimeOffset.value())
        return false;

    if (m_byteRange.has_value() != other.m_byteRange.has_value()) return false;
    if (m_byteRange.has_value() && m_byteRange.value() != other.m_byteRange.value()) return false;

    if (m_serviceLocation.has_value() != other.m_serviceLocation.has_value()) return false;
    if (m_serviceLocation.has_value() && m_serviceLocation.value() != other.m_serviceLocation.value()) return false;

    return true;
}

BaseURL::BaseURL(xmlpp::Node &node)
    :URI(node)
    ,m_serviceLocation()
    ,m_byteRange()
    ,m_availabilityTimeOffset()
    ,m_availabilityTimeComplete()
    ,m_timeShiftBufferDepth()
    ,m_rangeAccess(false)
{
    auto node_set = node.find("@serviceLocation");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_serviceLocation = std::string(attr->get_value());
    }

    node_set = node.find("@byteRange");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_byteRange = std::string(attr->get_value());
    }

    node_set = node.find("@availabilityTimeOffset");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_availabilityTimeOffset = std::stod(attr->get_value());
    }

    node_set = node.find("@availabilityTimeComplete");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_availabilityTimeComplete = (attr->get_value() == "true");
    }

    node_set = node.find("@timeShiftBufferDepth");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_timeShiftBufferDepth = str_to_duration<BaseURL::duration_type>(attr->get_value());
    }

    node_set = node.find("@rangeAccess");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_rangeAccess = (attr->get_value() == "true");
    }
}

void BaseURL::setXMLElement(xmlpp::Element &elem) const
{
    if (m_serviceLocation.has_value() && !m_serviceLocation.value().empty()) {
        elem.set_attribute("serviceLocation", m_serviceLocation.value());
    }
    if (m_byteRange.has_value() && !m_byteRange.value().empty()) {
        elem.set_attribute("byteRange", m_byteRange.value());
    }
    if (m_availabilityTimeOffset.has_value()) {
        elem.set_attribute("availabilityTimeOffset", std::format("%d", m_availabilityTimeOffset.value()));
    }
    if (m_availabilityTimeComplete.has_value()) {
        elem.set_attribute("availabilityTimeComplete", m_availabilityTimeComplete.value()?"true":"false");
    }
    if (m_timeShiftBufferDepth.has_value()) {
        elem.set_attribute("timeShiftBufferDepth", format_duration(std::chrono::round<std::chrono::milliseconds>(m_timeShiftBufferDepth.value())));
    }
    if (m_rangeAccess) {
        elem.set_attribute("rangeAccess", "true");
    }
    URI::setXMLElement(elem);
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
