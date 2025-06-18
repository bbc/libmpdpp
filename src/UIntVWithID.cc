/*****************************************************************************
 * DASH MPD parsing library in C++: UIntVWithID class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
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
#include "libmpd++/exceptions.hh"
#include "libmpd++/RFC6838ContentType.hh"
#include "libmpd++/URI.hh"

#include "conversions.hh"

#include "libmpd++/UIntVWithID.hh"

LIBMPDPP_NAMESPACE_BEGIN

UIntVWithID::UIntVWithID(unsigned int id,
                const std::list<URI> &profiles,
                const std::optional<RFC6838ContentType> &content_type)
    :std::list<unsigned int>()
    ,m_id(id)
    ,m_profiles(profiles)
    ,m_contentType(content_type)
{
}

UIntVWithID::UIntVWithID(const std::list<unsigned int> &init, unsigned int id,
                const std::list<URI> &profiles,
                const std::optional<RFC6838ContentType> &content_type)
    :std::list<unsigned int>(init)
    ,m_id(id)
    ,m_profiles(profiles)
    ,m_contentType(content_type)
{
}

UIntVWithID::UIntVWithID(std::list<unsigned int> &&init, unsigned int id,
                const std::list<URI> &profiles,
                const std::optional<RFC6838ContentType> &content_type)
    :std::list<unsigned int>(std::move(init))
    ,m_id(id)
    ,m_profiles(profiles)
    ,m_contentType(content_type)
{
}

UIntVWithID::UIntVWithID(std::initializer_list<unsigned int> init, unsigned int id,
                const std::list<URI> &profiles,
                const std::optional<RFC6838ContentType> &content_type)
    :std::list<unsigned int>(init)
    ,m_id(id)
    ,m_profiles(profiles)
    ,m_contentType(content_type)
{
}

UIntVWithID::UIntVWithID(const UIntVWithID &to_copy)
    :std::list<unsigned int>(to_copy)
    ,m_id(to_copy.m_id)
    ,m_profiles(to_copy.m_profiles)
    ,m_contentType(to_copy.m_contentType)
{
}

UIntVWithID::UIntVWithID(UIntVWithID &&to_move)
    :std::list<unsigned int>(std::move(to_move))
    ,m_id(to_move.m_id)
    ,m_profiles(std::move(to_move.m_profiles))
    ,m_contentType(std::move(to_move.m_contentType))
{
}

UIntVWithID &UIntVWithID::operator=(const UIntVWithID &to_copy)
{
    std::list<unsigned int>::operator=(to_copy);
    m_id = to_copy.m_id;
    m_profiles = to_copy.m_profiles;
    m_contentType = to_copy.m_contentType;

    return *this;
}

UIntVWithID &UIntVWithID::operator=(UIntVWithID &&to_move)
{
    std::list<unsigned int>::operator=(std::move(to_move));
    m_id = to_move.m_id;
    m_profiles = std::move(to_move.m_profiles);
    m_contentType = std::move(to_move.m_contentType);

    return *this;
}

bool UIntVWithID::operator==(const UIntVWithID &other) const
{
    if (m_id != other.m_id) return false;
    if (m_contentType.has_value() != other.m_contentType.has_value()) return false;
    if (m_contentType && m_contentType.value() != other.m_contentType.value()) return false;
    if (m_profiles.size() != other.m_profiles.size()) return false;
    {
        std::list<URI> to_find(other.m_profiles);
        for (const auto &profile : m_profiles) {
            auto it = std::find(to_find.begin(), to_find.end(), profile);
            if (it == to_find.end()) return false;
            to_find.erase(it);
        }
    }
    if (size() != other.size()) return false;
    {
        std::list<unsigned int> to_find(other);
        for (auto val : *this) {
            auto it = std::find(to_find.begin(), to_find.end(), val);
            if (it == to_find.end()) return false;
            to_find.erase(it);
        }
    }
    return true;
}

const URI &UIntVWithID::profile(std::list<URI>::size_type idx) const
{
    if (idx >= m_profiles.size())
        throw std::out_of_range("access of index beyond the @profiles entries in UIntVWithID type");
    auto it = m_profiles.begin();
    while (idx > 0) { it++; idx--; }
    return *it;
}

UIntVWithID &UIntVWithID::profilesRemove(const URI &val)
{
    return profilesRemove(std::find(m_profiles.begin(), m_profiles.end(), val));
}

UIntVWithID &UIntVWithID::profilesRemove(const std::list<URI>::const_iterator &it)
{
    if (it != m_profiles.cend()) {
        m_profiles.erase(it);
    }
    return *this;
}

UIntVWithID &UIntVWithID::profilesRemove(const std::list<URI>::iterator &it)
{
    if (it != m_profiles.end()) {
        m_profiles.erase(it);
    }
    return *this;
}

UIntVWithID::operator std::string() const
{
    std::ostringstream oss;
    const char *sep = "";
    for (auto val : *this) {
        oss << sep << val;
        sep = " ";
    }
    return oss.str();
}

// protected:
UIntVWithID::UIntVWithID(xmlpp::Node &node)
    :std::list<unsigned int>()
    ,m_id(0)
    ,m_profiles()
    ,m_contentType()
{
    std::string value_str = node.eval_to_string(".//text()");
    std::list<unsigned int>::operator=(str_to_list<unsigned int>(value_str, ' '));

    auto node_set = node.find("@id");
    if (node_set.size() == 0) {
        throw InvalidMPD("UIntVWithID element type must contain an id attribute");
    } else {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_id = static_cast<unsigned int>(std::stoul(std::string(attr->get_value())));
    }

    node_set = node.find("@profiles");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_profiles = str_to_list<URI>(attr->get_value());
    }

    node_set = node.find("@contentType");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_contentType = RFC6838ContentType(attr->get_value());
    }
}

void UIntVWithID::setXMLElement(xmlpp::Element &elem) const
{
    elem.add_child_text(static_cast<std::string>(*this));

    elem.set_attribute("id", std::to_string(m_id));

    if (!m_profiles.empty()) {
        std::ostringstream oss;
        const char *sep = "";
        for (const auto &profile : m_profiles) {
            oss << sep << profile;
            sep = ",";
        }
        elem.set_attribute("profiles", oss.str());
    }

    if (m_contentType) {
        elem.set_attribute("contentType", static_cast<std::string>(m_contentType.value()));
    }
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
