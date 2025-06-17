/*****************************************************************************
 * DASH MPD parsing library in C++: Label class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <optional>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"

#include "libmpd++/Label.hh"

LIBMPDPP_NAMESPACE_BEGIN

bool Label::operator==(const Label &to_compare) const
{
    if (m_id != to_compare.m_id) return false;
    if (m_lang.has_value() != to_compare.m_lang.has_value()) return false;
    if (m_lang.has_value() && m_lang.value() != to_compare.m_lang.value()) return false;
    return static_cast<const std::string&>(*this) == static_cast<const std::string&>(to_compare);
}

/* protected: */
Label::Label(xmlpp::Node &node)
    :std::string(node.eval_to_string(".//text()"))
    ,m_id(0)
    ,m_lang()
{
    auto node_set = node.find("@id");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_id = static_cast<unsigned int>(std::stoul(attr->get_value()));
    }

    node_set = node.find("@lang");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_lang = std::string(attr->get_value());
    }
}

void Label::setXMLElement(xmlpp::Element &element) const
{
    element.add_child_text(static_cast<const std::string&>(*this));
    if (m_id != 0) {
        element.set_attribute("id", std::to_string(m_id));
    }
    if (m_lang) {
        element.set_attribute("lang", m_lang.value());
    }
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
