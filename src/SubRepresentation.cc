/*****************************************************************************
 * DASH MPD parsing library in C++: SubRepresentation class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <list>
#include <optional>
#include <sstream>
#include <string>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/RepresentationBase.hh"

#include "conversions.hh"

#include "libmpd++/SubRepresentation.hh"

LIBMPDPP_NAMESPACE_BEGIN

SubRepresentation::SubRepresentation()
    :RepresentationBase()
    ,m_level()
    ,m_dependencyLevel()
    ,m_bandwidth()
    ,m_contentComponent()
{
}

SubRepresentation::SubRepresentation(const SubRepresentation &to_copy)
    :RepresentationBase(to_copy)
    ,m_level(to_copy.m_level)
    ,m_dependencyLevel(to_copy.m_dependencyLevel)
    ,m_bandwidth(to_copy.m_bandwidth)
    ,m_contentComponent(to_copy.m_contentComponent)
{
}

SubRepresentation::SubRepresentation(SubRepresentation &&to_move)
    :RepresentationBase(std::move(to_move))
    ,m_level(std::move(to_move.m_level))
    ,m_dependencyLevel(std::move(to_move.m_dependencyLevel))
    ,m_bandwidth(std::move(to_move.m_bandwidth))
    ,m_contentComponent(std::move(to_move.m_contentComponent))
{
}

SubRepresentation &SubRepresentation::operator=(const SubRepresentation &to_copy)
{
    RepresentationBase::operator=(to_copy);
    m_level = to_copy.m_level;
    m_dependencyLevel = to_copy.m_dependencyLevel;
    m_bandwidth = to_copy.m_bandwidth;
    m_contentComponent = to_copy.m_contentComponent;

    return *this;
}

SubRepresentation &SubRepresentation::operator=(SubRepresentation &&to_move)
{
    RepresentationBase::operator=(std::move(to_move));
    m_level = std::move(to_move.m_level);
    m_dependencyLevel = std::move(to_move.m_dependencyLevel);
    m_bandwidth = std::move(to_move.m_bandwidth);
    m_contentComponent = std::move(to_move.m_contentComponent);

    return *this;
}

bool SubRepresentation::operator==(const SubRepresentation &to_compare) const
{
    if (m_level != to_compare.m_level) return false;
    if (m_dependencyLevel.size() != to_compare.m_dependencyLevel.size()) return false;
    {
        std::list<unsigned int> to_find(to_compare.m_dependencyLevel);
        for (auto val : m_dependencyLevel) {
            auto it = std::find(to_find.begin(), to_find.end(), val);
            if (it == to_find.end()) return false;
            to_find.erase(it);
        }
    }
    if (m_bandwidth != to_compare.m_bandwidth) return false;
    if (m_contentComponent.size() != to_compare.m_contentComponent.size()) return false;
    {
        std::list<std::string> to_find(to_compare.m_contentComponent);
        for (const auto &val : m_contentComponent) {
            auto it = std::find(to_find.begin(), to_find.end(), val);
            if (it == to_find.end()) return false;
            to_find.erase(it);
        }
    }

    return RepresentationBase::operator==(to_compare);
}

// protected:
SubRepresentation::SubRepresentation(xmlpp::Node &node)
    :RepresentationBase(node)
    ,m_level()
    ,m_dependencyLevel()
    ,m_bandwidth()
    ,m_contentComponent()
{
    auto node_set = node.find("@level");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_level = static_cast<unsigned int>(std::stoul(attr->get_value()));
    }

    node_set = node.find("@dependencyLevel");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_dependencyLevel = str_to_list<unsigned int>(attr->get_value());
    }

    node_set = node.find("@bandwidth");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_bandwidth = static_cast<unsigned int>(std::stoul(attr->get_value()));
    }

    node_set = node.find("@contentComponent");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_contentComponent = str_to_list<std::string>(attr->get_value());
    }
}

void SubRepresentation::setXMLElement(xmlpp::Element &elem) const
{
    RepresentationBase::setXMLElement(elem);

    if (m_level) {
        elem.set_attribute("level", std::to_string(m_level.value()));
    }

    if (!m_dependencyLevel.empty()) {
        std::ostringstream oss;
        const char *sep = "";
        for (auto val : m_dependencyLevel) {
            oss << sep << val;
            sep = ",";
        }
        elem.set_attribute("dependencyLevel", oss.str());
    }

    if (m_bandwidth) {
        elem.set_attribute("bandwidth", std::to_string(m_bandwidth.value()));
    }

    if (!m_contentComponent.empty()) {
        std::ostringstream oss;
        const char *sep = "";
        for (const auto &val : m_contentComponent) {
            oss << sep << val;
            sep = ",";
        }
        elem.set_attribute("contentComponent", oss.str());
    }
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
