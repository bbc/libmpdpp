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
    if (m_t.has_value() != other.m_t.has_value()) return false;
    if (m_t && !(m_t.value() == other.m_t.value())) return false;

    if (m_n.has_value() != other.m_n.has_value()) return false;
    if (m_n && !(m_n.value() == other.m_n.value())) return false;

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

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
