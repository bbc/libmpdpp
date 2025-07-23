/*****************************************************************************
 * DASH MPD parsing library in C++: AdaptationSet class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
 *            David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <cmath>
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <sstream>
#include <glibmm/ustring.h>
#include <libxml++/libxml++.h>
#include <libxml/tree.h>

#include "libmpd++/macros.hh"
#include "libmpd++/ContentComponent.hh"
#include "libmpd++/exceptions.hh"
#include "libmpd++/MPD.hh"
#include "libmpd++/Period.hh"
#include "libmpd++/Representation.hh"
#include "libmpd++/SegmentAvailability.hh"
#include "libmpd++/XLink.hh"

#include "constants.hh"
#include "conversions.hh"
#include "stream_ops.hh"

#include "libmpd++/AdaptationSet.hh"

LIBMPDPP_NAMESPACE_BEGIN

AdaptationSet::AdaptationSet()
    :RepresentationBase()
    ,m_period(nullptr)
    ,m_selectedRepresentations()
    ,m_xlink()
    ,m_id()
    ,m_group()
    ,m_lang()
    ,m_contentType()
    ,m_par()
    ,m_minBandwidth()
    ,m_maxBandwidth()
    ,m_minWidth()
    ,m_maxWidth()
    ,m_minHeight()
    ,m_maxHeight()
    ,m_minFrameRate()
    ,m_maxFrameRate()
    ,m_segmentAlignment(false)
    ,m_subsegmentAlignment(false)
    ,m_subsegmentStartsWithSAP(0)
    ,m_bitstreamSwitching()
    ,m_initializationSetRefs()
    ,m_initializationPrincipal()
    ,m_accessibilities()
    ,m_roles()
    ,m_ratings()
    ,m_viewpoints()
    ,m_contentComponents()
    ,m_baseURLs()
    ,m_segmentBase()
    ,m_segmentList()
    ,m_segmentTemplate()
    ,m_representations()
{
}

AdaptationSet::AdaptationSet(const AdaptationSet &other)
    :RepresentationBase(other)
    ,m_period(other.m_period)
    ,m_selectedRepresentations(other.m_selectedRepresentations)
    ,m_xlink(other.m_xlink)
    ,m_id(other.m_id)
    ,m_group(other.m_group)
    ,m_lang(other.m_lang)
    ,m_contentType(other.m_contentType)
    ,m_par(other.m_par)
    ,m_minBandwidth(other.m_minBandwidth)
    ,m_maxBandwidth(other.m_maxBandwidth)
    ,m_minWidth(other.m_minWidth)
    ,m_maxWidth(other.m_maxWidth)
    ,m_minHeight(other.m_minHeight)
    ,m_maxHeight(other.m_maxHeight)
    ,m_minFrameRate(other.m_minFrameRate)
    ,m_maxFrameRate(other.m_maxFrameRate)
    ,m_segmentAlignment(other.m_segmentAlignment)
    ,m_subsegmentAlignment(other.m_subsegmentAlignment)
    ,m_subsegmentStartsWithSAP(other.m_subsegmentStartsWithSAP)
    ,m_bitstreamSwitching(other.m_bitstreamSwitching)
    ,m_initializationSetRefs(other.m_initializationSetRefs)
    ,m_initializationPrincipal(other.m_initializationPrincipal)
    ,m_accessibilities(other.m_accessibilities)
    ,m_roles(other.m_roles)
    ,m_ratings(other.m_ratings)
    ,m_viewpoints(other.m_viewpoints)
    ,m_contentComponents(other.m_contentComponents)
    ,m_baseURLs(other.m_baseURLs)
    ,m_segmentBase(other.m_segmentBase)
    ,m_segmentList(other.m_segmentList)
    ,m_segmentTemplate(other.m_segmentTemplate)
    ,m_representations()
{
    for (auto &rep : other.m_representations) {
        auto it = m_selectedRepresentations.find(&rep);
        m_representations.push_back(rep);
        auto &new_rep = m_representations.back();
        new_rep.setAdaptationSet(this);
        if (it != m_selectedRepresentations.end()) {
            m_selectedRepresentations.erase(it);
            m_selectedRepresentations.insert(&new_rep);
        }
    }
}

AdaptationSet::AdaptationSet(AdaptationSet &&other)
    :RepresentationBase(std::move(other))
    ,m_period(other.m_period)
    ,m_selectedRepresentations(std::move(other.m_selectedRepresentations))
    ,m_xlink(std::move(other.m_xlink))
    ,m_id(std::move(other.m_id))
    ,m_group(std::move(other.m_group))
    ,m_lang(std::move(other.m_lang))
    ,m_contentType(std::move(other.m_contentType))
    ,m_par(std::move(other.m_par))
    ,m_minBandwidth(std::move(other.m_minBandwidth))
    ,m_maxBandwidth(std::move(other.m_maxBandwidth))
    ,m_minWidth(std::move(other.m_minWidth))
    ,m_maxWidth(std::move(other.m_maxWidth))
    ,m_minHeight(std::move(other.m_minHeight))
    ,m_maxHeight(std::move(other.m_maxHeight))
    ,m_minFrameRate(std::move(other.m_minFrameRate))
    ,m_maxFrameRate(std::move(other.m_maxFrameRate))
    ,m_segmentAlignment(std::move(other.m_segmentAlignment))
    ,m_subsegmentAlignment(std::move(other.m_subsegmentAlignment))
    ,m_subsegmentStartsWithSAP(std::move(other.m_subsegmentStartsWithSAP))
    ,m_bitstreamSwitching(std::move(other.m_bitstreamSwitching))
    ,m_initializationSetRefs(std::move(other.m_initializationSetRefs))
    ,m_initializationPrincipal(std::move(other.m_initializationPrincipal))
    ,m_accessibilities(std::move(other.m_accessibilities))
    ,m_roles(std::move(other.m_roles))
    ,m_ratings(std::move(other.m_ratings))
    ,m_viewpoints(std::move(other.m_viewpoints))
    ,m_contentComponents(std::move(other.m_contentComponents))
    ,m_baseURLs(std::move(other.m_baseURLs))
    ,m_segmentBase(std::move(other.m_segmentBase))
    ,m_segmentList(std::move(other.m_segmentList))
    ,m_segmentTemplate(std::move(other.m_segmentTemplate))
    ,m_representations()
{
    for (auto &rep : other.m_representations) {
        auto it = m_selectedRepresentations.find(&rep);
        m_representations.push_back(std::move(rep));
        auto &new_rep = m_representations.back();
        new_rep.setAdaptationSet(this);
        if (it != m_selectedRepresentations.end()) {
            m_selectedRepresentations.erase(it);
            m_selectedRepresentations.insert(&new_rep);
        }
    }
}

AdaptationSet &AdaptationSet::operator=(const AdaptationSet &other)
{
    RepresentationBase::operator=(other);
    m_period = other.m_period;
    m_selectedRepresentations = other.m_selectedRepresentations;
    m_xlink = other.m_xlink;
    m_id = other.m_id;
    m_group = other.m_group;
    m_lang = other.m_lang;
    m_contentType = other.m_contentType;
    m_par = other.m_par;
    m_minBandwidth = other.m_minBandwidth;
    m_maxBandwidth = other.m_maxBandwidth;
    m_minWidth = other.m_minWidth;
    m_maxWidth = other.m_maxWidth;
    m_minHeight = other.m_minHeight;
    m_maxHeight = other.m_maxHeight;
    m_minFrameRate = other.m_minFrameRate;
    m_maxFrameRate = other.m_maxFrameRate;
    m_segmentAlignment = other.m_segmentAlignment;
    m_subsegmentAlignment = other.m_subsegmentAlignment;
    m_subsegmentStartsWithSAP = other.m_subsegmentStartsWithSAP;
    m_bitstreamSwitching = other.m_bitstreamSwitching;
    m_initializationSetRefs = other.m_initializationSetRefs;
    m_initializationPrincipal = other.m_initializationPrincipal;
    m_accessibilities = other.m_accessibilities;
    m_roles = other.m_roles;
    m_ratings = other.m_ratings;
    m_viewpoints = other.m_viewpoints;
    m_contentComponents = other.m_contentComponents;
    m_baseURLs = other.m_baseURLs;
    m_segmentBase = other.m_segmentBase;
    m_segmentList = other.m_segmentList;
    m_segmentTemplate = other.m_segmentTemplate;
    m_representations.clear();
    for (auto &rep : other.m_representations) {
        auto it = m_selectedRepresentations.find(&rep);
        m_representations.push_back(rep);
        auto &new_rep = m_representations.back();
        new_rep.setAdaptationSet(this);
        if (it != m_selectedRepresentations.end()) {
            m_selectedRepresentations.erase(it);
            m_selectedRepresentations.insert(&new_rep);
        }
    }

    return *this;
}

AdaptationSet &AdaptationSet::operator=(AdaptationSet &&other)
{
    RepresentationBase::operator=(std::move(other));
    m_period = other.m_period;
    m_selectedRepresentations = std::move(other.m_selectedRepresentations);
    m_xlink = std::move(other.m_xlink);
    m_id = std::move(other.m_id);
    m_group = std::move(other.m_group);
    m_lang = std::move(other.m_lang);
    m_contentType = std::move(other.m_contentType);
    m_par = std::move(other.m_par);
    m_minBandwidth = std::move(other.m_minBandwidth);
    m_maxBandwidth = std::move(other.m_maxBandwidth);
    m_minWidth = std::move(other.m_minWidth);
    m_maxWidth = std::move(other.m_maxWidth);
    m_minHeight = std::move(other.m_minHeight);
    m_maxHeight = std::move(other.m_maxHeight);
    m_minFrameRate = std::move(other.m_minFrameRate);
    m_maxFrameRate = std::move(other.m_maxFrameRate);
    m_segmentAlignment = std::move(other.m_segmentAlignment);
    m_subsegmentAlignment = std::move(other.m_subsegmentAlignment);
    m_subsegmentStartsWithSAP = std::move(other.m_subsegmentStartsWithSAP);
    m_bitstreamSwitching = std::move(other.m_bitstreamSwitching);
    m_initializationSetRefs = std::move(other.m_initializationSetRefs);
    m_initializationPrincipal = std::move(other.m_initializationPrincipal);
    m_accessibilities = std::move(other.m_accessibilities);
    m_roles = std::move(other.m_roles);
    m_ratings = std::move(other.m_ratings);
    m_viewpoints = std::move(other.m_viewpoints);
    m_contentComponents = std::move(other.m_contentComponents);
    m_baseURLs = std::move(other.m_baseURLs);
    m_segmentBase = std::move(other.m_segmentBase);
    m_segmentList = std::move(other.m_segmentList);
    m_segmentTemplate = std::move(other.m_segmentTemplate);
    m_representations.clear();

    for (auto &rep : other.m_representations) {
        auto it = m_selectedRepresentations.find(&rep);
        m_representations.push_back(std::move(rep));
        auto &new_rep = m_representations.back();
        new_rep.setAdaptationSet(this);
        if (it != m_selectedRepresentations.end()) {
            m_selectedRepresentations.erase(it);
            m_selectedRepresentations.insert(&new_rep);
        }
    }

    return *this;
}

bool AdaptationSet::operator==(const AdaptationSet &to_compare) const
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

    if (m_segmentAlignment != to_compare.m_segmentAlignment) return false;
    if (m_subsegmentAlignment != to_compare.m_subsegmentAlignment) return false;
    if (!(m_subsegmentStartsWithSAP == to_compare.m_subsegmentStartsWithSAP)) return false;

    COMPARE_OPT_VALUES(m_id);
    COMPARE_OPT_VALUES(m_group);
    COMPARE_OPT_VALUES(m_lang);
    COMPARE_OPT_VALUES(m_contentType);
    COMPARE_OPT_VALUES(m_par);
    COMPARE_OPT_VALUES(m_minBandwidth);
    COMPARE_OPT_VALUES(m_maxBandwidth);
    COMPARE_OPT_VALUES(m_minWidth);
    COMPARE_OPT_VALUES(m_maxWidth);
    COMPARE_OPT_VALUES(m_minHeight);
    COMPARE_OPT_VALUES(m_maxHeight);
    COMPARE_OPT_VALUES(m_minFrameRate);
    COMPARE_OPT_VALUES(m_maxFrameRate);
    COMPARE_OPT_VALUES(m_bitstreamSwitching);
    COMPARE_OPT_VALUES(m_initializationPrincipal);
    COMPARE_OPT_VALUES(m_segmentBase);
    COMPARE_OPT_VALUES(m_segmentList);
    COMPARE_OPT_VALUES(m_segmentTemplate);

    COMPARE_ANY_ORDER_LISTS(m_accessibilities);
    COMPARE_ANY_ORDER_LISTS(m_roles);
    COMPARE_ANY_ORDER_LISTS(m_ratings);
    COMPARE_ANY_ORDER_LISTS(m_viewpoints);
    COMPARE_ANY_ORDER_LISTS(m_contentComponents);
    COMPARE_ANY_ORDER_LISTS(m_contentComponents);
    COMPARE_ANY_ORDER_LISTS(m_baseURLs);
    COMPARE_ANY_ORDER_LISTS(m_representations);

    return RepresentationBase::operator==(to_compare);
}

MPD *AdaptationSet::getMPD()
{
    if (m_period) return m_period->getMPD();
    return nullptr;
}

const MPD *AdaptationSet::getMPD() const
{
    if (m_period) return m_period->getMPD();
    return nullptr;
}

std::list<BaseURL> AdaptationSet::getBaseURLs() const
{
    if (m_baseURLs.size() == 0 && m_period) return m_period->getBaseURLs();

    std::list<BaseURL> ret;
    std::list<BaseURL> parent_urls_cache;
    bool have_parent_urls = false;
    for (const auto &base_url : m_baseURLs) {
        if (base_url.url().isAbsoluteURL()) {
            ret.push_back(base_url);
        } else {
            if (m_period) {
                if (!have_parent_urls) {
                    parent_urls_cache = m_period->getBaseURLs();
                    have_parent_urls = true;
                }
                ret.push_back(base_url.resolveURL(parent_urls_cache));
            } else {
                ret.push_back(base_url);
            }
        }
    }
    return ret;
}

/* protected: */

AdaptationSet::AdaptationSet(xmlpp::Node &node)
    :RepresentationBase(node)
    ,m_period(nullptr)
    ,m_selectedRepresentations()
    ,m_xlink()
    ,m_id()
    ,m_group()
    ,m_lang()
    ,m_contentType()
    ,m_par()
    ,m_minBandwidth()
    ,m_maxBandwidth()
    ,m_minWidth()
    ,m_maxWidth()
    ,m_minHeight()
    ,m_maxHeight()
    ,m_minFrameRate()
    ,m_maxFrameRate()
    ,m_segmentAlignment(false)
    ,m_subsegmentAlignment(false)
    ,m_subsegmentStartsWithSAP(0)
    ,m_bitstreamSwitching()
    ,m_initializationSetRefs()
    ,m_initializationPrincipal()
    ,m_accessibilities()
    ,m_roles()
    ,m_ratings()
    ,m_viewpoints()
    ,m_contentComponents()
    ,m_baseURLs()
    ,m_segmentBase()
    ,m_segmentList()
    ,m_segmentTemplate()
    ,m_representations()
{
    static const xmlpp::Node::PrefixNsMap ns_map = {
        {"mpd", MPD_NS}, {"xlink", XLINK_NS}
    };
    xmlpp::Node::NodeSet node_set;

    node_set = node.find("@xlink:href", ns_map);
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        std::string xlink_href = attr->get_value();
        auto actuate = XLink::ACTUATE_ON_REQUEST;
        node_set = node.find("@xlink:actuate", ns_map);
        if (node_set.size() > 0) {
            attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
            std::string xlink_actuate = attr->get_value();
            if (xlink_actuate == "onLoad") actuate = XLink::ACTUATE_ON_LOAD;
            else if (xlink_actuate != "onRequest") throw ParseError("AdaptationSet/@xlink:actuate can only be either \"onLoad\" or \"onRequest\"");
        }
        m_xlink = XLink(xlink_href, actuate, XLink::TYPE_SIMPLE, XLink::SHOW_EMBED);
    }

    node_set = node.find("@id");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_id =static_cast<unsigned int>(std::stoul(attr->get_value()));
    }

    node_set = node.find("@group");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_group =static_cast<unsigned int>(std::stoul(attr->get_value()));
    }

    node_set = node.find("@lang");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_lang = std::string(attr->get_value());
    }

    node_set = node.find("@contentType");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_contentType = RFC6838ContentType(std::string(attr->get_value()));
    }

    node_set = node.find("@par");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_par = Ratio(std::string(attr->get_value()));
    }

    node_set = node.find("@minBandwidth");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_minBandwidth = std::stod(attr->get_value());
    }

    node_set = node.find("@maxBandwidth");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_maxBandwidth = std::stod(attr->get_value());
    }

    node_set = node.find("@minWidth");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_minWidth =static_cast<unsigned int>(std::stoul(attr->get_value()));
    }

    node_set = node.find("@maxWidth");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_maxWidth =static_cast<unsigned int>(std::stoul(attr->get_value()));
    }

    node_set = node.find("@minHeight");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_minHeight =static_cast<unsigned int>(std::stoul(attr->get_value()));
    }

    node_set = node.find("@maxHeight");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_maxHeight =static_cast<unsigned int>(std::stoul(attr->get_value()));
    }

    node_set = node.find("@minFrameRate");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_minFrameRate = FrameRate(std::string(attr->get_value()));
    }

    node_set = node.find("@maxFrameRate");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_maxFrameRate = FrameRate(std::string(attr->get_value()));
    }

    node_set = node.find("@segmentAlignment");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        if (attr->get_value() == "true" || attr->get_value() == "1") {
            m_segmentAlignment = true;
        } else if (attr->get_value() == "false" || attr->get_value() == "0") {
            m_segmentAlignment = false;
        } else {
            throw ParseError("AdaptationSet/@segmentAlignment can only be \"true\", \"1\", \"false\" or \"0\", if present");
        }
    }

    node_set = node.find("@subsegmentAlignment");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        if (attr->get_value() == "true" || attr->get_value() == "1") {
            m_subsegmentAlignment = true;
        } else if (attr->get_value() == "false" || attr->get_value() == "0") {
            m_subsegmentAlignment = false;
        } else {
            throw ParseError("AdaptationSet/@subsegmentAlignment can only be \"true\", \"1\", \"false\" or \"0\", if present");
        }
    }

    node_set = node.find("@subsegmentStartsWithSAP");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_subsegmentStartsWithSAP = SAP(std::string(attr->get_value()));
    }

    node_set = node.find("@bitstreamSwitching");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        if (attr->get_value() == "true" || attr->get_value() == "1") {
            m_bitstreamSwitching = true;
        } else if (attr->get_value() == "false" || attr->get_value() == "0") {
            m_bitstreamSwitching = false;
        } else {
            throw ParseError("AdaptationSet/@bitstreamSwitching can only be \"true\", \"1\", \"false\" or \"0\", if present");
        }
    }

    node_set = node.find("@initializationSetRef", ns_map);
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        std::string::size_type start_pos = 0;
        std::string attr_val = attr->get_value();
        for (auto pos = attr_val.find_first_of(','); pos != std::string::npos; start_pos = pos+1, pos = attr_val.find_first_of(',')) {
            auto val = attr_val.substr(start_pos, pos - start_pos);
            if (!val.empty()) {
                m_initializationSetRefs.push_back(static_cast<unsigned int>(std::stoul(val)));
            }
        }
        auto val = attr_val.substr(start_pos);
        if (!val.empty()) {
            m_initializationSetRefs.push_back(static_cast<unsigned int>(std::stoul(val)));
        }
    }

    node_set = node.find("@initializationPrincipal");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_initializationPrincipal = std::string(attr->get_value());
    }

    node_set = node.find("mpd:Accessibility", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_accessibilities.push_back(Descriptor(*node));
        }
    }

    node_set = node.find("mpd:Role", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_roles.push_back(Descriptor(*node));
        }
    }

    node_set = node.find("mpd:Rating", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_ratings.push_back(Descriptor(*node));
        }
    }

    node_set = node.find("mpd:Viewpoint", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_viewpoints.push_back(Descriptor(*node));
        }
    }

    node_set = node.find("mpd:ContentComponent", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_contentComponents.push_back(ContentComponent(*node));
        }
    }

    node_set = node.find("mpd:BaseURL", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_baseURLs.push_back(BaseURL(*node));
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

    node_set = node.find("mpd:Representation", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_representations.push_back(Representation(*node));
            m_representations.back().setAdaptationSet(this);
        }
    }

}

const Descriptor &AdaptationSet::accessibility(std::list<Descriptor>::size_type idx) const
{
    if (idx >= m_accessibilities.size()) {
        throw std::out_of_range("AdaptationSet Accessibility does not exist");
    }
    auto it = m_accessibilities.cbegin();
    while (idx > 0 && it != m_accessibilities.cend()) { it++; idx--; }
    return *it;
}

bool AdaptationSet::accessibilitiesContains(const Descriptor &descriptor) const
{
    return std::find(m_accessibilities.cbegin(), m_accessibilities.cend(), descriptor) != m_accessibilities.cend();
}

AdaptationSet &AdaptationSet::accessibilitiesAdd(const Descriptor &accessibility)
{
    m_accessibilities.push_back(accessibility);
    return *this;
}

AdaptationSet &AdaptationSet::accessibilitiesAdd(Descriptor &&accessibility)
{
    m_accessibilities.push_back(std::move(accessibility));
    return *this;
}

AdaptationSet &AdaptationSet::accessibilitiesRemove(const Descriptor &accessibility)
{
    m_accessibilities.remove(accessibility);
    return *this;
}

AdaptationSet &AdaptationSet::accessibilitiesRemove(const std::list<Descriptor>::const_iterator &it)
{
    m_accessibilities.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::accessibilitiesRemove(const std::list<Descriptor>::iterator &it)
{
    m_accessibilities.erase(it);
    return *this;
}

const Descriptor &AdaptationSet::role(std::list<Descriptor>::size_type idx) const
{
    if (idx >= m_roles.size()) {
        throw std::out_of_range("AdaptationSet Role does not exist");
    }
    auto it = m_roles.cbegin();
    while (idx > 0 && it != m_roles.cend()) { it++; idx--; }
    return *it;
}

bool AdaptationSet::rolesContains(const Descriptor &descriptor) const
{
    return std::find(m_roles.cbegin(), m_roles.cend(), descriptor) != m_roles.cend();
}

AdaptationSet &AdaptationSet::rolesAdd(const Descriptor &role)
{
    m_roles.push_back(role);
    return *this;
}

AdaptationSet &AdaptationSet::rolesAdd(Descriptor &&role)
{
    m_roles.push_back(std::move(role));
    return *this;
}

AdaptationSet &AdaptationSet::rolesRemove(const Descriptor &role)
{
    m_roles.remove(role);
    return *this;
}

AdaptationSet &AdaptationSet::rolesRemove(const std::list<Descriptor>::const_iterator &it)
{
    m_roles.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::rolesRemove(const std::list<Descriptor>::iterator &it)
{
    m_roles.erase(it);
    return *this;
}

const Descriptor &AdaptationSet::rating(std::list<Descriptor>::size_type idx) const
{
    if (idx >= m_ratings.size()) {
        throw std::out_of_range("AdaptationSet Rating does not exist");
    }
    auto it = m_ratings.cbegin();
    while (idx > 0 && it != m_ratings.cend()) { it++; idx--; }
    return *it;
}

bool AdaptationSet::ratingsContains(const Descriptor &descriptor) const
{
    return std::find(m_ratings.cbegin(), m_ratings.cend(), descriptor) != m_ratings.cend();
}

AdaptationSet &AdaptationSet::ratingsAdd(const Descriptor &rating)
{
    m_ratings.push_back(rating);
    return *this;
}

AdaptationSet &AdaptationSet::ratingsAdd(Descriptor &&rating)
{
    m_ratings.push_back(std::move(rating));
    return *this;
}

AdaptationSet &AdaptationSet::ratingsRemove(const Descriptor &rating)
{
    m_ratings.remove(rating);
    return *this;
}

AdaptationSet &AdaptationSet::ratingsRemove(const std::list<Descriptor>::const_iterator &it)
{
    m_ratings.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::ratingsRemove(const std::list<Descriptor>::iterator &it)
{
    m_ratings.erase(it);
    return *this;
}

const Descriptor &AdaptationSet::viewpoint(std::list<Descriptor>::size_type idx) const
{
    if (idx >= m_viewpoints.size()) {
        throw std::out_of_range("AdaptationSet Role does not exist");
    }
    auto it = m_viewpoints.cbegin();
    while (idx > 0 && it != m_viewpoints.cend()) { it++; idx--; }
    return *it;
}

bool AdaptationSet::viewpointsContains(const Descriptor &descriptor) const
{
    return std::find(m_viewpoints.cbegin(), m_viewpoints.cend(), descriptor) != m_viewpoints.cend();
}

AdaptationSet &AdaptationSet::viewpointsAdd(const Descriptor &rating)
{
    m_viewpoints.push_back(rating);
    return *this;
}

AdaptationSet &AdaptationSet::viewpointsAdd(Descriptor &&rating)
{
    m_viewpoints.push_back(std::move(rating));
    return *this;
}

AdaptationSet &AdaptationSet::viewpointsRemove(const Descriptor &rating)
{
    m_viewpoints.remove(rating);
    return *this;
}

AdaptationSet &AdaptationSet::viewpointsRemove(const std::list<Descriptor>::const_iterator &it)
{
    m_viewpoints.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::viewpointsRemove(const std::list<Descriptor>::iterator &it)
{
    m_viewpoints.erase(it);
    return *this;
}

const ContentComponent &AdaptationSet::contentComponent(std::list<ContentComponent>::size_type idx) const
{
    if (idx >= m_contentComponents.size()) {
        throw std::out_of_range("AdaptationSet ContentComponent does not exist");
    }
    auto it = m_contentComponents.cbegin();
    while (idx > 0 && it != m_contentComponents.cend()) { it++; idx--; }
    return *it;
}

bool AdaptationSet::contentComponentsContains(const ContentComponent &content_component) const
{
    return std::find(m_contentComponents.cbegin(), m_contentComponents.cend(), content_component) != m_contentComponents.cend();
}

AdaptationSet &AdaptationSet::contentComponentsAdd(const ContentComponent &content_component)
{
    m_contentComponents.push_back(content_component);
    return *this;
}

AdaptationSet &AdaptationSet::contentComponentsAdd(ContentComponent &&content_component)
{
    m_contentComponents.push_back(std::move(content_component));
    return *this;
}

AdaptationSet &AdaptationSet::contentComponentsRemove(const ContentComponent &content_component)
{
    m_contentComponents.remove(content_component);
    return *this;
}

AdaptationSet &AdaptationSet::contentComponentsRemove(const std::list<ContentComponent>::const_iterator &it)
{
    m_contentComponents.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::contentComponentsRemove(const std::list<ContentComponent>::iterator &it)
{
    m_contentComponents.erase(it);
    return *this;
}

const BaseURL &AdaptationSet::baseURL(std::list<BaseURL>::size_type idx) const
{
    if (idx >= m_baseURLs.size()) {
        throw std::out_of_range("AdaptationSet BaseURL does not exist");
    }
    auto it = m_baseURLs.cbegin();
    while (idx > 0 && it != m_baseURLs.cend()) { it++; idx--; }
    return *it;
}

bool AdaptationSet::baseURLsContains(const BaseURL &base_url) const
{
    return std::find(m_baseURLs.cbegin(), m_baseURLs.cend(), base_url) != m_baseURLs.cend();
}

AdaptationSet &AdaptationSet::baseURLsAdd(const BaseURL &base_url)
{
    m_baseURLs.push_back(base_url);
    return *this;
}

AdaptationSet &AdaptationSet::baseURLsAdd(BaseURL &&base_url)
{
    m_baseURLs.push_back(std::move(base_url));
    return *this;
}

AdaptationSet &AdaptationSet::baseURLsRemove(const BaseURL &base_url)
{
    m_baseURLs.remove(base_url);
    return *this;
}

AdaptationSet &AdaptationSet::baseURLsRemove(const std::list<BaseURL>::const_iterator &it)
{
    m_baseURLs.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::baseURLsRemove(const std::list<BaseURL>::iterator &it)
{
    m_baseURLs.erase(it);
    return *this;
}

const Representation &AdaptationSet::representation(std::list<Representation>::size_type idx) const
{
    if (idx >= m_representations.size()) {
        throw std::out_of_range("AdaptationSet Representation does not exist");
    }
    auto it = m_representations.cbegin();
    while (idx > 0 && it != m_representations.cend()) { it++; idx--; } 
    return *it;
}

bool AdaptationSet::representationsContains(const Representation &representation) const
{
    return std::find(m_representations.cbegin(), m_representations.cend(), representation) != m_representations.cend();
}

AdaptationSet &AdaptationSet::representationsAdd(const Representation &representation)
{
    m_representations.push_back(representation);
    m_representations.back().setAdaptationSet(this);
    return *this;
}

AdaptationSet &AdaptationSet::representationsAdd(Representation &&representation)
{
    m_representations.push_back(std::move(representation));
    m_representations.back().setAdaptationSet(this);
    return *this;
}

AdaptationSet &AdaptationSet::representationsRemove(const Representation &representation)
{
    auto it = std::find(m_representations.begin(), m_representations.end(), representation);
    return representationsRemove(it);
}

AdaptationSet &AdaptationSet::representationsRemove(const std::list<Representation>::const_iterator &it)
{
    if (it != m_representations.end()) {
        auto &rep = *it;
        m_representations.erase(it);
        m_selectedRepresentations.erase(&rep);
    }
    return *this;
}

AdaptationSet &AdaptationSet::representationsRemove(const std::list<Representation>::iterator &it)
{
    if (it != m_representations.end()) {
        auto &rep = *it;
        m_representations.erase(it);
        m_selectedRepresentations.erase(&rep);
    }
    return *this;
}

void AdaptationSet::selectAllRepresentations()
{
    for (auto it = m_representations.begin(); it != m_representations.end(); it++) {
        selectRepresentation(it);
    }
}

void AdaptationSet::selectRepresentation(const Representation &rep, bool deselect_others)
{
    auto it = std::find(m_representations.begin(), m_representations.end(), rep);
    selectRepresentation(it, deselect_others);
}

void AdaptationSet::selectRepresentation(const std::list<Representation>::const_iterator &rep_it, bool deselect_others)
{
    if (rep_it == m_representations.end()) {
        if (deselect_others) deselectAllRepresentations();
    } else {
        auto &rep = *rep_it;
        if (deselect_others) {
            m_selectedRepresentations = {&rep};
        } else {
            m_selectedRepresentations.insert(&rep);
        }
    }
}

void AdaptationSet::selectRepresentation(const std::list<Representation>::iterator &rep_it, bool deselect_others)
{
    if (rep_it == m_representations.end()) {
        if (deselect_others) deselectAllRepresentations();
    } else {
        auto &rep = *rep_it;
        if (deselect_others) {
            m_selectedRepresentations = {&rep};
        } else {
            m_selectedRepresentations.insert(&rep);
        }
    }
}

void AdaptationSet::deselectAllRepresentations()
{
    m_selectedRepresentations.clear();
}

void AdaptationSet::deselectRepresentation(const Representation &rep)
{
    auto it = std::find(m_representations.begin(), m_representations.end(), rep);
    deselectRepresentation(it);
}

void AdaptationSet::deselectRepresentation(const std::list<Representation>::const_iterator &rep_it)
{
    if (rep_it != m_representations.end()) {
        auto &rep = *rep_it;
        m_selectedRepresentations.erase(&rep);
    }
}

void AdaptationSet::deselectRepresentation(const std::list<Representation>::iterator &rep_it)
{
    if (rep_it != m_representations.end()) {
        auto &rep = *rep_it;
        m_selectedRepresentations.erase(&rep);
    }
}

std::list<SegmentAvailability> AdaptationSet::selectedSegmentAvailability(const AdaptationSet::time_type &query_time) const
{
    std::list<SegmentAvailability> ret;

    for (auto rep_ptr : m_selectedRepresentations) {
        ret.push_back(rep_ptr->segmentAvailability(query_time));
    }

    return ret;
}

std::list<SegmentAvailability> AdaptationSet::selectedInitializationSegments() const
{
    std::unordered_set<SegmentAvailability> ret;
    for (auto rep_ptr : m_selectedRepresentations) {
        ret.insert(rep_ptr->initialisationSegmentAvailability());
    }
    return std::list<SegmentAvailability>(ret.begin(), ret.end());
}

// protected:

static Glib::ustring get_ns_prefix_for(xmlpp::Element &elem, const Glib::ustring &namespace_uri, const Glib::ustring &namespace_prefix)
{
    auto ns_ptr = xmlSearchNsByHref(elem.cobj()->doc, elem.cobj(), reinterpret_cast<const xmlChar*>(namespace_uri.c_str()));
    if (ns_ptr == nullptr) {
        auto root_node = xmlDocGetRootElement(elem.cobj()->doc);
        ns_ptr = xmlNewNs(root_node, reinterpret_cast<const xmlChar*>(namespace_uri.c_str()), reinterpret_cast<const xmlChar*>(namespace_prefix.c_str()));
    }
    return Glib::ustring(reinterpret_cast<const char*>(ns_ptr->prefix));
}


void AdaptationSet::setXMLElement(xmlpp::Element &elem) const
{
    RepresentationBase::setXMLElement(elem);

    if (m_xlink.has_value()) {
        const Glib::ustring& xlink_prefix = get_ns_prefix_for(elem, XLINK_NS, "xlink");
        elem.set_attribute("href", std::string(m_xlink.value().href()), xlink_prefix);
        if (m_xlink.value().actuate() != XLink::ACTUATE_ON_REQUEST) {
            elem.set_attribute("actuate", "onLoad", xlink_prefix);
        }
    } else {
        // Attributes
        if (m_id.has_value()) {
            elem.set_attribute("id", std::to_string(m_id.value()));
        }

        if(m_group.has_value()) {
            elem.set_attribute("group", std::to_string(m_group.value()));
        }

        if(m_lang.has_value()) {
            elem.set_attribute("lang", m_lang.value());
        }

        if (m_contentType.has_value()) {
            elem.set_attribute("contentType", std::string(m_contentType.value()));
        }

        if (m_par.has_value()) {
            elem.set_attribute("par", std::string(m_par.value()));
        }

        if(m_minBandwidth.has_value()) {
           elem.set_attribute("minBandwidth", std::to_string(m_minBandwidth.value()));
        }

        if(m_maxBandwidth.has_value()) {
            elem.set_attribute("maxBandwidth", std::to_string(m_maxBandwidth.value()));
        }

        if(m_minWidth.has_value()) {
            elem.set_attribute("minWidth", std::to_string(m_minWidth.value()));
        }

        if(m_maxWidth.has_value()) {
            elem.set_attribute("maxWidth", std::to_string(m_maxWidth.value()));
        }

        if(m_minHeight.has_value()) {
            elem.set_attribute("minHeight", std::to_string(m_minHeight.value()));
        }

        if(m_maxHeight.has_value()) {
            elem.set_attribute("maxHeight", std::to_string(m_maxHeight.value()));
        }
        if (m_minFrameRate.has_value()) {
            elem.set_attribute("minFrameRate", std::string(m_minFrameRate.value()));
        }

        if (m_maxFrameRate.has_value()) {
            elem.set_attribute("maxFrameRate", std::string(m_maxFrameRate.value()));
        }

        if (m_segmentAlignment) {
            elem.set_attribute("segmentAlignment", "true");
        }

        if (m_subsegmentAlignment) {
            elem.set_attribute("subsegmentAlignment", "true");
        }

        if (m_subsegmentStartsWithSAP != 0) {
            elem.set_attribute("subsegmentStartsWithSAP", std::string(m_subsegmentStartsWithSAP));
        }

        if (m_bitstreamSwitching.has_value()) {
            elem.set_attribute("bitstreamSwitching", m_bitstreamSwitching.value()?"true":"false");
        }

        if (m_initializationSetRefs.size() > 0) {
            std::ostringstream oss;
            const char *sep = "";
            for (const auto &init_set_ref : m_initializationSetRefs) {
                oss << sep << init_set_ref;
                sep = ",";
            }
            elem.set_attribute("initializationSetRef", oss.str());
        }

        if(m_initializationPrincipal.has_value()) {
            elem.set_attribute("initializationPrincipal", std::string(m_initializationPrincipal.value()));
        }

        for (const auto &accessibility : m_accessibilities) {
            xmlpp::Element *child = elem.add_child_element("Accessibility");
            accessibility.setXMLElement(*child);
        }

        for (const auto &role : m_roles) {
            xmlpp::Element *child = elem.add_child_element("Role");
            role.setXMLElement(*child);
        }


        for (const auto &rating : m_ratings) {
            xmlpp::Element *child = elem.add_child_element("Rating");
            rating.setXMLElement(*child);
        }

        for (const auto &view_point : m_viewpoints) {
            xmlpp::Element *child = elem.add_child_element("ViewPoint");
            view_point.setXMLElement(*child);
        }

        for (const auto &content_comp : m_contentComponents) {
            xmlpp::Element *child = elem.add_child_element("ContentComponent");
            content_comp.setXMLElement(*child);
        }

        for (const auto &base_url : m_baseURLs) {
            xmlpp::Element *child = elem.add_child_element("BaseURL");
            base_url.setXMLElement(*child);
        }
        if (m_segmentBase.has_value()) {
            xmlpp::Element *child = elem.add_child_element("SegmentBase");
            m_segmentBase.value().setXMLElement(*child);
        }
        if (m_segmentList.has_value()) {
            xmlpp::Element *child = elem.add_child_element("SegmentList");
            m_segmentList.value().setXMLElement(*child);
        }
        if (m_segmentTemplate.has_value()) {
            xmlpp::Element *child = elem.add_child_element("SegmentTemplate");
            m_segmentTemplate.value().setXMLElement(*child);
        }

        for (const auto &repr : m_representations) {
            xmlpp::Element *child = elem.add_child_element("Representation");
            repr.setXMLElement(*child);
        }
    }
}

std::string AdaptationSet::getMediaURL(const SegmentTemplate::Variables &vars) const
{
    if (m_segmentTemplate.has_value()) {
        return m_segmentTemplate.value().formatMediaTemplate(vars);
    }
    if (m_segmentList.has_value()) {
        if (vars.number()) {
            return m_segmentList.value().getMediaURLForSegment(vars.number().value());
        } else if (vars.time()) {
            return m_segmentList.value().getMediaURLForSegmentTime(vars.time().value());
        }
    }
    if (m_period) {
        return m_period->getMediaURL(vars);
    }
    return std::string();
}

std::string AdaptationSet::getInitializationURL(const SegmentTemplate::Variables &vars) const
{
    if (m_segmentTemplate.has_value()) {
        return m_segmentTemplate.value().formatInitializationTemplate(vars);
    }
    if (m_segmentList.has_value()) {
        return m_segmentList.value().getInitializationURL();
    }
    if (m_period) {
        return m_period->getInitializationURL(vars);
    }
    return std::string();
}

SegmentAvailability AdaptationSet::getMediaAvailability(const SegmentTemplate::Variables &vars) const
{
    SegmentAvailability ret;
    std::list<BaseURL> base_urls;
    const MPD *mpd = getMPD();

    if (m_segmentTemplate.has_value()) {
        base_urls = getBaseURLs();
        unsigned int ts = 1;
        if (m_segmentTemplate.value().hasTimescale()) {
            ts = m_segmentTemplate.value().timescale().value();
        }
        if (base_urls.empty()) {
            if (mpd && mpd->hasAvailabilityStartTime()) {
                ret.availabilityStartTime(mpd->availabilityStartTime().value() + vars.timeAsDurationType(ts));
            }
        } else {
            const BaseURL &base_url = base_urls.front();
            if (base_url.hasAvailabilityTimeOffset()) {
                if (mpd && mpd->hasAvailabilityStartTime()) {
                    if (std::isnan(base_url.availabilityTimeOffset().value())) {
                        // All segments available at the MPD@availabilityStartTime
                        ret.availabilityStartTime(mpd->availabilityStartTime().value());
                    } else {
                        // available at MPD@availabilityStartTime - @availabilityTimeOffset + segment_time
                        ret.availabilityStartTime(mpd->availabilityStartTime().value() - std::chrono::duration_cast<duration_type>(std::chrono::duration<double, std::ratio<1>>(base_url.availabilityTimeOffset().value())) + vars.timeAsDurationType(ts));
                    }
                }
            } else if (mpd && mpd->hasAvailabilityStartTime()) {
                // available at MPD@availabilityStartTime + segment_time
                ret.availabilityStartTime(mpd->availabilityStartTime().value() + vars.timeAsDurationType(ts));
            }
        }
        if (mpd) {
            if (mpd->hasAvailabilityEndTime()) {
                ret.availabilityEndTime(mpd->presentationTimeToSystemTime(mpd->availabilityEndTime().value()));
            }
            ret.availabilityStartTime(mpd->presentationTimeToSystemTime(ret.availabilityStartTime()));
        }
        if (m_segmentTemplate.value().hasDuration()) {
            ret.segmentDuration(m_segmentTemplate.value().durationAsDurationType());
            if (mpd && mpd->isLive()) {
                ret.availabilityStartTime(ret.availabilityStartTime() + std::chrono::duration_cast<time_type::duration>(ret.segmentDuration()));
            }
        }
        ret.segmentURL(URI(m_segmentTemplate.value().formatMediaTemplate(vars)).resolveUsingBaseURLs(base_urls));
    } else if (m_segmentList.has_value()) {
        base_urls = getBaseURLs();
        if (base_urls.empty()) {
            if (mpd && mpd->hasAvailabilityStartTime()) {
                ret.availabilityStartTime(mpd->availabilityStartTime().value());
            }
        } else {
            const BaseURL &base_url = base_urls.front();
            if (base_url.hasAvailabilityTimeOffset() && !std::isnan(base_url.availabilityTimeOffset().value())) {
                if (mpd && mpd->hasAvailabilityStartTime()) {
                    ret.availabilityStartTime(mpd->availabilityStartTime().value() - std::chrono::duration_cast<duration_type>(std::chrono::duration<double, std::ratio<1>>(base_url.availabilityTimeOffset().value())));
                }
            } else if (mpd && mpd->hasAvailabilityStartTime()) {
                ret.availabilityStartTime(mpd->availabilityStartTime().value());
            }
        }
        ret.segmentDuration(m_segmentList.value().durationAsDurationType());
        if (mpd) {
            if (mpd->hasAvailabilityEndTime()) {
                ret.availabilityEndTime(mpd->presentationTimeToSystemTime(mpd->availabilityEndTime().value()));
            }
            ret.availabilityStartTime(mpd->presentationTimeToSystemTime(ret.availabilityStartTime()));
            if (mpd->isLive()) {
                ret.availabilityStartTime(ret.availabilityStartTime() + std::chrono::duration_cast<time_type::duration>(ret.segmentDuration()));
            }
        }

        if (vars.number()) {
            ret.segmentURL(URI(m_segmentList.value().getMediaURLForSegment(vars.number().value())).resolveUsingBaseURLs(base_urls));
        } else if (vars.time()) {
            ret.segmentURL(URI(m_segmentList.value().getMediaURLForSegmentTime(vars.time().value())).resolveUsingBaseURLs(base_urls));
        }
    } else if (m_period) {
        ret = m_period->getMediaAvailability(vars);
    }

    return ret;
}

SegmentAvailability AdaptationSet::getInitialisationAvailability(const SegmentTemplate::Variables &vars) const
{
    SegmentAvailability ret;
    std::list<BaseURL> base_urls;

    if (m_segmentTemplate.has_value()) {
        base_urls = getBaseURLs();
        ret.segmentURL(URI(m_segmentTemplate.value().formatInitializationTemplate(vars)).resolveUsingBaseURLs(base_urls));
    } else if (m_segmentList.has_value()) {
        base_urls = getBaseURLs();
        ret.segmentURL(URI(m_segmentList.value().getInitializationURL()).resolveUsingBaseURLs(base_urls));
    } else if (m_period) {
        ret = m_period->getInitialisationAvailability(vars);
        return ret;
    }

    if (!base_urls.empty()) {
        const BaseURL &base_url = base_urls.front();
        const MPD *mpd = getMPD();
        if (base_url.hasAvailabilityTimeOffset()) {
            if (mpd && mpd->hasAvailabilityStartTime()) {
                ret.availabilityStartTime(mpd->presentationTimeToSystemTime(mpd->availabilityStartTime().value() - std::chrono::duration_cast<duration_type>(std::chrono::duration<double, std::ratio<1> >(base_url.availabilityTimeOffset().value()))));
            }
        } else {
            if (mpd && mpd->hasAvailabilityStartTime()) {
                ret.availabilityStartTime(mpd->presentationTimeToSystemTime(mpd->availabilityStartTime().value()));
            } else {
                ret.availabilityStartTime(std::chrono::system_clock::now());
            }
        }
    } else {
        ret.availabilityStartTime(std::chrono::system_clock::now());
    }

    return ret;
}

AdaptationSet::time_type AdaptationSet::getPeriodStartTime() const
{
    if (m_period) return m_period->getPeriodStartTime();
    return AdaptationSet::time_type(); // just return epoch if we can't find the period
}

std::optional<AdaptationSet::duration_type> AdaptationSet::getPeriodDuration() const
{   
    if (m_period) return m_period->getPeriodDuration();
    return std::optional<AdaptationSet::duration_type>(); // just return epoch if we can't find the period
}
 
const MultipleSegmentBase &AdaptationSet::getMultiSegmentBase() const
{
    if (m_segmentTemplate) return m_segmentTemplate.value();
    if (m_segmentList) return m_segmentTemplate.value();
    if (m_segmentBase) {
        static MultipleSegmentBase multi_no_duration;
        static_cast<SegmentBase&>(multi_no_duration) = m_segmentBase.value(); // copy over SegmentBase values
        return multi_no_duration;
    }
    if (m_period) return m_period->getMultiSegmentBase();

    static const MultipleSegmentBase empty_multi;
    return empty_multi;
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
