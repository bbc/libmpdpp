/*****************************************************************************
 * DASH MPD parsing library in C++: URL class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"

#include "libmpd++/URL.hh"

LIBMPDPP_NAMESPACE_BEGIN

URL::URL()
    :m_sourceURL()
    ,m_range()
{
}

URL::URL(const URL &other)
    :m_sourceURL(other.m_sourceURL)
    ,m_range(other.m_range)
{
}

URL::URL(URL &&other)
    :m_sourceURL(std::move(other.m_sourceURL))
    ,m_range(std::move(other.m_range))
{
}

URL &URL::operator=(const URL &other)
{
    m_sourceURL = other.m_sourceURL;
    m_range = other.m_range;
    return *this;
}

URL &URL::operator=(URL &&other)
{
    m_sourceURL = std::move(other.m_sourceURL);
    m_range = std::move(other.m_range);
    return *this;
}

bool URL::operator==(const URL &other) const
{
    if (m_sourceURL != other.m_sourceURL) return false;
    if (m_range != other.m_range) return false;

    return true;
}

// protected

URL::URL(xmlpp::Node &node)
    :m_sourceURL()
    ,m_range()
{
    xmlpp::Node::NodeSet node_set;

    node_set = node.find("@sourceURL");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_sourceURL = std::string(attr->get_value());
    }

    node_set = node.find("@range");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_range = SingleRFC7233Range(std::string(attr->get_value()));
    }
}

void URL::setXMLElement(xmlpp::Element &elem) const
{
    if (m_sourceURL) {
        elem.set_attribute("sourceURL", std::string(m_sourceURL.value()));
    }
    if (m_range) {
        elem.set_attribute("range", std::string(m_range.value()));
    }
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
