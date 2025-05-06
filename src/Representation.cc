/*****************************************************************************
 * DASH MPD parsing library in C++: Period class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <chrono>
#include <list>
#include <memory>
#include <optional>
#include <string>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/AdaptationSet.hh"
#include "libmpd++/BaseURL.hh"
#include "libmpd++/ContentProtection.hh"
#include "libmpd++/Descriptor.hh"
#include "libmpd++/EventStream.hh"
#include "libmpd++/Label.hh"
#include "libmpd++/Preselection.hh"
#include "libmpd++/SegmentBase.hh"
#include "libmpd++/SegmentTemplate.hh"
#include "libmpd++/SegmentList.hh"
#include "libmpd++/XLink.hh"
#include "libmpd++/ExtendedBandwidth.hh"
#include "libmpd++/SubRepresentation.hh"

#include "constants.hh"
#include "conversions.hh"

#include "libmpd++/Representation.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

Representation::Representation()
    :m_mpd()
    ,m_adaptationSet()
    ,m_id()
    ,m_bandwidth(0)
    ,m_qualityRanking()
    ,m_dependencyIds()
    ,m_associationIds()
    ,m_associationTypes()
    ,m_mediaStreamStructureIds()
    ,m_baseURLs()
    ,m_extendedBandwidths()
    ,m_subRepresentations()
    ,m_segmentBase()
    ,m_segmentList()
    ,m_segmentTemplate()
{
}

Representation::Representation(const Representation &to_copy)
    :m_mpd(to_copy.m_mpd)
    ,m_adaptationSet()
    ,m_id(to_copy.m_id)
    ,m_bandwidth(to_copy.m_bandwidth)
    ,m_qualityRanking(to_copy.m_qualityRanking)
    ,m_dependencyIds(to_copy.m_dependencyIds)
    ,m_associationIds(to_copy.m_associationIds)
    ,m_associationTypes(to_copy.m_associationTypes)
    ,m_mediaStreamStructureIds(to_copy.m_mediaStreamStructureIds)
    ,m_baseURLs(to_copy.m_baseURLs)
    ,m_segmentBase(to_copy.m_segmentBase)
    ,m_segmentList(to_copy.m_segmentList)
    ,m_segmentTemplate(to_copy.m_segmentTemplate)
{
}

Representation::Representation(Representation &&to_move)
    :m_mpd(std::move(to_move.m_mpd))
    ,m_adaptationSet(std::move(to_move.m_adaptationSet))	
    ,m_id(std::move(to_move.m_id))
    ,m_bandwidth(to_move.m_bandwidth)
    ,m_qualityRanking(to_move.m_qualityRanking)
    ,m_dependencyIds(to_move.m_dependencyIds)
    ,m_associationIds(to_move.m_associationIds)
    ,m_associationTypes(to_move.m_associationTypes)
    ,m_mediaStreamStructureIds(to_move.m_mediaStreamStructureIds)
    ,m_baseURLs(std::move(to_move.m_baseURLs))
    ,m_segmentBase(std::move(to_move.m_segmentBase))
    ,m_segmentList(std::move(to_move.m_segmentList))
    ,m_segmentTemplate(std::move(to_move.m_segmentTemplate))
{
}

Representation &Representation::operator=(const Representation &to_copy)
{
    m_mpd = to_copy.m_mpd;
    m_adaptationSet = to_copy.m_adaptationSet;
    m_id = to_copy.m_id;
    m_bandwidth = to_copy.m_bandwidth;
    m_qualityRanking = to_copy.m_qualityRanking;
    m_dependencyIds = to_copy.m_dependencyIds;
    m_associationIds = to_copy.m_associationIds;
    m_associationTypes = to_copy.m_associationTypes;
    m_mediaStreamStructureIds = to_copy.m_mediaStreamStructureIds;
    m_baseURLs = to_copy.m_baseURLs;
    m_segmentBase = to_copy.m_segmentBase;
    m_segmentList = to_copy.m_segmentList;
    m_segmentTemplate = to_copy.m_segmentTemplate;

    return *this;
}

Representation &Representation::operator=(Representation &&to_move)
{
    m_mpd = std::move(to_move.m_mpd);
    m_adaptationSet = std::move(to_move.m_adaptationSet);
    m_id = std::move(to_move.m_id);
    m_bandwidth = std::move(to_move.m_bandwidth);
    m_qualityRanking = std::move(to_move.m_qualityRanking);
    m_dependencyIds = to_move.m_dependencyIds;
    m_associationIds = std::move(to_move.m_associationIds);
    m_associationTypes = std::move(to_move.m_associationTypes);
    m_mediaStreamStructureIds = std::move(to_move.m_mediaStreamStructureIds);
    m_baseURLs = std::move(to_move.m_baseURLs);
    m_extendedBandwidths = std::move(to_move.m_extendedBandwidths);
    m_subRepresentations = std::move(to_move.m_subRepresentations);
    m_segmentBase = std::move(to_move.m_segmentBase);
    m_segmentList = std::move(to_move.m_segmentList);
    m_segmentTemplate = std::move(to_move.m_segmentTemplate);

    return *this;
}

bool Representation::operator==(const Representation &to_compare) const
{

#define COMPARE_OPT_VALUES(var) do { \
        if (var.has_value() != to_compare.var.has_value()) return false; \
        if (var.has_value() && !(var.value() == to_compare.var.value())) return false; \
    } while(0)
#define COMPARE_ANY_ORDER_LISTS(var) do { \
        if (var.size() != to_compare.var.size()) return false; \
        if (var.size() != 0) { \
            auto list_copy = to_compare.var; \
            for (const auto &item : var) { \
                auto it = std::find(list_copy.begin(), list_copy.end(), item); \
                if (it == list_copy.end()) return false; \
                list_copy.erase(it); \
            } \
        } \
    } while (0)

    if (m_id != to_compare.m_id) return false;
    
    if (m_bandwidth != to_compare.m_bandwidth) return false;
    
    COMPARE_OPT_VALUES(m_qualityRanking);
    COMPARE_ANY_ORDER_LISTS(m_dependencyIds);
    COMPARE_ANY_ORDER_LISTS(m_associationIds);
    COMPARE_ANY_ORDER_LISTS(m_associationTypes);
    COMPARE_ANY_ORDER_LISTS(m_mediaStreamStructureIds);

    //return false;
    return true;
}

Representation::Representation(xmlpp::Node &node)
    :m_mpd()
    ,m_adaptationSet()
    ,m_id()
    ,m_bandwidth()
    ,m_qualityRanking()
    ,m_dependencyIds()
    ,m_associationIds()
    ,m_associationTypes()
    ,m_mediaStreamStructureIds()
    ,m_baseURLs()
    ,m_extendedBandwidths()
    ,m_subRepresentations()
    ,m_segmentBase()
    ,m_segmentList()
    ,m_segmentTemplate()
{

    static const xmlpp::Node::PrefixNsMap ns_map = {
        {"mpd", MPD_NS}, {"xlink", XLINK_NS}
    };
    xmlpp::Node::NodeSet node_set;

    node_set = node.find("@id");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_id = std::string(attr->get_value());
    }

    node_set = node.find("@bandwidth");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_bandwidth = std::stod(attr->get_value());
    }

    node_set = node.find("@qualityRanking");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_qualityRanking = std::stoi(attr->get_value());
    }

    node_set = node.find("@dependencyId");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_dependencyIds.push_back(std::string(attr->get_value()));
    }

    node_set = node.find("@id");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_id = std::string(attr->get_value());
    }


    node_set = node.find("@associationId");
    if (node_set.size() > 0) {
	xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_associationIds.push_back(std::string(attr->get_value()));     
    }

    node_set = node.find("@associationType");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_associationTypes.push_back(std::string(attr->get_value()));

    }

    node_set = node.find("@mediaStreamStructureId");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_mediaStreamStructureIds.push_back(std::string(attr->get_value()));
    }

    node_set = node.find("mpd:BaseURL", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_baseURLs.push_back(BaseURL(*node));
        }
    }

    node_set = node.find("mpd:ExtendedBandwidth", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_extendedBandwidths.push_back(ExtendedBandwidth(*node));
        }
    }

    node_set = node.find("mpd:subRepresentation", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_subRepresentations.push_back(SubRepresentation(*node));
        }
    }

    node_set = node.find("mpd:SegmentBase", ns_map);
    if (node_set.size() > 0) {
        m_segmentBase = SegmentBase(*node_set.front());
    }

    node_set = node.find("mpd:SegmentList", ns_map);
    if (node_set.size() > 0) {
        m_segmentList = SegmentList(*node_set.front());
    }

    node_set = node.find("mpd:SegmentTemplate", ns_map);
    if (node_set.size() > 0) {
        m_segmentTemplate = SegmentTemplate(*node_set.front());
    }

}

void Representation::setXMLElement(xmlpp::Element &elem) const
{
    // Attributes
    if(!m_id.empty()) {
        elem.set_attribute("id", m_id);	    
    }
    if (m_bandwidth != 0) {
        elem.set_attribute("bandwidth", std::format("%lu", m_bandwidth));
    }
    if (m_qualityRanking.has_value()) {
        elem.set_attribute("qualityRanking", std::format("%i", m_qualityRanking.value()));
    }

    for (const auto &depId : m_dependencyIds) {
	elem.set_attribute("dependencyId", depId);    
    }

    for (const auto &assocId : m_associationIds) {
        
	elem.set_attribute("associationId", assocId);    
    }

    for (const auto &assocType : m_associationTypes) {
    
	elem.set_attribute("associationType", assocType);    
    }

    for (const auto &streamStructureId : m_mediaStreamStructureIds) {
        elem.set_attribute("mediaStreamStructureId", streamStructureId);
    }

    // Elements
    for (const auto &base_url : m_baseURLs) {
        xmlpp::Element *child = elem.add_child_element("BaseURL");
        base_url.setXMLElement(*child);
    }
    
    for (const auto &ext_bw : m_extendedBandwidths) {
        xmlpp::Element *child = elem.add_child_element("ExtendedBandwidth");
        ext_bw.setXMLElement(*child);
    }


    for (const auto &sub_repr : m_subRepresentations) {
        xmlpp::Element *child = elem.add_child_element("SubRepresentation");
        sub_repr.setXMLElement(*child);
    }

    if (m_segmentBase.has_value()) {
        xmlpp::Element *child = elem.add_child_element("SegmentBase");
        m_segmentBase.value().setXMLElement(*child);
    }

    if (m_segmentBase.has_value()) {
        xmlpp::Element *child = elem.add_child_element("SegmentList");
        m_segmentBase.value().setXMLElement(*child);
    }

    if (m_segmentTemplate.has_value()) {
        xmlpp::Element *child = elem.add_child_element("SegmentTemplate");
        m_segmentTemplate.value().setXMLElement(*child);
    }

}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */

