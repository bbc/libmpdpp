/*****************************************************************************
 * DASH MPD parsing library in C++: Descriptor class
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
#include "libmpd++/exceptions.hh"

#include "libmpd++/Descriptor.hh"

LIBMPDPP_NAMESPACE_BEGIN

Descriptor::Descriptor(xmlpp::Node &node)
    :m_schemeIdUri()
    ,m_value()
    ,m_id()
{
    auto node_set = node.find("@schemeIdUri");
    if (node_set.size() != 1) throw ParseError(node.get_name() + " must have a schemeIdUri attribute");
    xmlpp::Attribute *scheme_id_attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
    m_schemeIdUri = scheme_id_attr->get_value();

    node_set = node.find("@value");
    if (node_set.size() == 1) {
        xmlpp::Attribute *value_attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_value = value_attr->get_value();
    }

    node_set = node.find("@id");
    if (node_set.size() == 1) {
        xmlpp::Attribute *id_attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_id = id_attr->get_value();
    }
}

void Descriptor::setXMLElement(xmlpp::Element &elem) const
{
    elem.set_attribute("schemeIdUri", std::string(m_schemeIdUri));
    if (m_value.has_value()) elem.set_attribute("value", m_value.value());
    if (m_id.has_value()) elem.set_attribute("id", m_id.value());
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
