/*****************************************************************************
 * DASH MPD parsing library in C++: ContentProtection class
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

#include "libmpd++/ContentProtection.hh"

LIBMPDPP_NAMESPACE_BEGIN

ContentProtection::ContentProtection(const URI &scheme_id,
                      const std::optional<std::string> &value,
                      const std::optional<std::string> &id,
                      const std::optional<std::string> &robustness,
                      const std::optional<std::string> &ref_id,
                      const std::optional<std::string> &ref)
    :Descriptor(scheme_id, value, id)
    ,m_robustness(robustness)
    ,m_refId(ref_id)
    ,m_ref(ref)
{
}

ContentProtection::ContentProtection(URI &&scheme_id,
                      const std::optional<std::string> &value,
                      const std::optional<std::string> &id,
                      const std::optional<std::string> &robustness,
                      const std::optional<std::string> &ref_id,
                      const std::optional<std::string> &ref)
    :Descriptor(std::move(scheme_id), value, id)
    ,m_robustness(robustness)
    ,m_refId(ref_id)
    ,m_ref(ref)
{   
}

ContentProtection::ContentProtection(const ContentProtection &to_copy)
    :Descriptor(to_copy)
    ,m_robustness(to_copy.m_robustness)
    ,m_refId(to_copy.m_refId)
    ,m_ref(to_copy.m_ref)
{
}

ContentProtection::ContentProtection(ContentProtection &&to_move)
    :Descriptor(std::move(to_move))
    ,m_robustness(std::move(to_move.m_robustness))
    ,m_refId(std::move(to_move.m_refId))
    ,m_ref(std::move(to_move.m_ref))
{
}

ContentProtection &ContentProtection::operator=(const ContentProtection &to_copy)
{
    Descriptor::operator=(to_copy);
    m_robustness = to_copy.m_robustness;
    m_refId = to_copy.m_refId;
    m_ref = to_copy.m_ref;
    return *this;
}

ContentProtection &ContentProtection::operator=(ContentProtection &&to_move)
{
    Descriptor::operator=(std::move(to_move));
    m_robustness = std::move(to_move.m_robustness);
    m_refId = std::move(to_move.m_refId);
    m_ref = std::move(to_move.m_ref);
    return *this;
}

bool ContentProtection::operator==(const ContentProtection &to_compare) const
{
    if (m_robustness != to_compare.m_robustness) return false;
    if (m_refId != to_compare.m_refId) return false;
    if (m_ref != to_compare.m_ref) return false;

    return Descriptor::operator==(to_compare);
}

// protected:
ContentProtection::ContentProtection(xmlpp::Node &node)
    :Descriptor(node)
    ,m_robustness()
    ,m_refId()
    ,m_ref()
{
    auto node_set = node.find("@robustness");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_robustness = std::string(attr->get_value());
    }

    node_set = node.find("@refId");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_refId = std::string(attr->get_value());
    }

    node_set = node.find("@ref");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_ref = std::string(attr->get_value());
    }
}

void ContentProtection::setXMLElement(xmlpp::Element &element) const
{
    Descriptor::setXMLElement(element);

    if (m_robustness) {
        element.set_attribute("robustness", m_robustness.value());
    }

    if (m_refId) {
        element.set_attribute("refId", m_refId.value());
    }

    if (m_ref) {
        element.set_attribute("ref", m_ref.value());
    }
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
