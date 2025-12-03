/*****************************************************************************
 * DASH MPD parsing library in C++: ContentPopularityRate class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <algorithm>
#include <list>
#include <optional>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/exceptions.hh"

#include "libmpd++/ContentPopularityRate.hh"

LIBMPDPP_NAMESPACE_BEGIN

/************************** ContentPopularityRate::PR ***********************/

//protected:
ContentPopularityRate::PR::PR(xmlpp::Node &node)
    :m_popularityRate()
    ,m_start()
    ,m_r(0)
{
    auto node_set = node.find("@popularityRate");
    if (!node_set.empty()) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_popularityRate = static_cast<unsigned int>(std::stoul(attr->get_value()));
        if (m_popularityRate < 1 || m_popularityRate > 100)
            throw ParseError("popularityRate attribute of PR must be between 1 and 100 inclusive.");
    }

    node_set = node.find("@start");
    if (!node_set.empty()) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_start = std::stoul(attr->get_value());
    }

    node_set = node.find("@r");
    if (!node_set.empty()) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_r = std::stoi(attr->get_value());
    }
}

void ContentPopularityRate::PR::setXMLElement(xmlpp::Element &elem) const
{
    if (m_popularityRate) {
        elem.set_attribute("popularityRate", std::to_string(m_popularityRate.value()));
    }

    if (m_start) {
        elem.set_attribute("start", std::to_string(m_start.value()));
    }

    if (m_r != 0) {
        elem.set_attribute("r", std::to_string(m_r));
    }
}

/**************************** ContentPopularityRate *************************/

ContentPopularityRate::ContentPopularityRate()
    :m_prs()
{
}

ContentPopularityRate::ContentPopularityRate(const ContentPopularityRate &other)
    :m_prs(other.m_prs)
{
}

ContentPopularityRate::ContentPopularityRate(ContentPopularityRate &&other)
    :m_prs(std::move(other.m_prs))
{
}

ContentPopularityRate &ContentPopularityRate::operator=(const ContentPopularityRate &other)
{
    m_prs = other.m_prs;
    return *this;
}

ContentPopularityRate &ContentPopularityRate::operator=(ContentPopularityRate &&other)
{
    m_prs = std::move(other.m_prs);
    return *this;
}

bool ContentPopularityRate::operator==(const ContentPopularityRate &other) const
{
    if (m_prs.size() != other.m_prs.size()) return false;
    std::list<ContentPopularityRate::PR> to_find(other.m_prs);
    for (const auto &pr : m_prs) {
        auto it = std::find(to_find.begin(), to_find.end(), pr);
        if (it == to_find.end()) return false;
        to_find.erase(it);
    }
    return true;
}

// protected:
ContentPopularityRate::ContentPopularityRate(xmlpp::Node &node)
    :m_prs()
{
    auto node_set = node.find("PR");
    for (auto &n : node_set) {
        m_prs.push_back(ContentPopularityRate::PR(*n));
    }
}

void ContentPopularityRate::setXMLElement(xmlpp::Element &elem) const
{
    for (const auto &pr : m_prs) {
        xmlpp::Element *child = elem.add_child_element("PR");
        pr.setXMLElement(*child);
    }
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
