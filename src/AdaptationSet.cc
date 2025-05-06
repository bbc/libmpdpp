/*****************************************************************************
 * DASH MPD parsing library in C++: AdaptationSet class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */

#include <list>
#include <memory>
#include <optional>
#include <string>
#include <sstream>
#include <glibmm/ustring.h>
#include <libxml++/libxml++.h>
#include <libxml/tree.h>

#include "libmpd++/exceptions.hh"
#include "libmpd++/macros.hh"
#include "libmpd++/AdaptationSet.hh"
#include "libmpd++/XLink.hh"
#include "libmpd++/Representation.hh"

#include "constants.hh"
#include "conversions.hh"


LIBPARSEMPD_NAMESPACE_BEGIN

AdaptationSet::AdaptationSet(const AdaptationSet &to_copy)
    :m_xlink(to_copy.m_xlink)
    ,m_id(to_copy.m_id)
    ,m_group(to_copy.m_group)
    ,m_lang(to_copy.m_lang)
    ,m_contentType(to_copy.m_contentType)
    ,m_par(to_copy.m_par)
    ,m_minBandwidth(to_copy.m_minBandwidth)
    ,m_maxBandwidth(to_copy.m_maxBandwidth)
    ,m_minWidth(to_copy.m_minWidth)
    ,m_maxWidth(to_copy.m_maxWidth)
    ,m_minHeight(to_copy.m_minHeight)
    ,m_maxHeight(to_copy.m_maxHeight)
    ,m_minFrameRate(to_copy.m_minFrameRate)
    ,m_maxFrameRate(to_copy.m_maxFrameRate)
    ,m_segmentAlignment(to_copy.m_segmentAlignment)
    ,m_bitstreamSwitching(to_copy.m_bitstreamSwitching)
    ,m_subsegmentAlignment(to_copy.m_subsegmentAlignment)
    ,m_subsegmentStartsWithSAP(to_copy.m_subsegmentStartsWithSAP)
    ,m_initializationSetRefs(to_copy.m_initializationSetRefs)
    ,m_initializationPrincipal(to_copy.m_initializationPrincipal)
    ,m_accessibility(to_copy.m_accessibility)
    ,m_roles(to_copy.m_roles)
    ,m_ratings(to_copy.m_ratings)
    ,m_viewpoints(to_copy.m_viewpoints)
    ,m_contentComponents(to_copy.m_contentComponents)
    ,m_baseURLs(to_copy.m_baseURLs)
    ,m_segmentBase(to_copy.m_segmentBase)
    ,m_segmentList(to_copy.m_segmentList)
    ,m_segmentTemplate(to_copy.m_segmentTemplate)
    ,m_representations(to_copy.m_representations)
{
}

AdaptationSet::AdaptationSet(AdaptationSet &&to_move)
    :m_xlink(std::move(to_move.m_xlink))
    ,m_id(std::move(to_move.m_id))
    ,m_group(std::move(to_move.m_group))
    ,m_lang(std::move(to_move.m_lang))
    ,m_contentType(std::move(to_move.m_contentType))
    ,m_par(std::move(to_move.m_par))
    ,m_minBandwidth(std::move(to_move.m_minBandwidth))
    ,m_maxBandwidth(std::move(to_move.m_maxBandwidth))
    ,m_minWidth(std::move(to_move.m_minWidth))
    ,m_maxWidth(std::move(to_move.m_maxWidth))
    ,m_minHeight(std::move(to_move.m_minHeight))
    ,m_maxHeight(std::move(to_move.m_maxHeight))
    ,m_minFrameRate(std::move(to_move.m_minFrameRate))
    ,m_maxFrameRate(std::move(to_move.m_maxFrameRate))
    ,m_segmentAlignment(std::move(to_move.m_segmentAlignment))
    ,m_bitstreamSwitching(std::move(to_move.m_bitstreamSwitching))
    ,m_subsegmentAlignment(std::move(to_move.m_subsegmentAlignment))
    ,m_subsegmentStartsWithSAP(std::move(to_move.m_subsegmentStartsWithSAP))
    ,m_initializationSetRefs(std::move(to_move.m_initializationSetRefs))
    ,m_initializationPrincipal(std::move(to_move.m_initializationPrincipal))
    ,m_accessibility(std::move(to_move.m_accessibility))
    ,m_roles(std::move(to_move.m_roles))
    ,m_ratings(std::move(to_move.m_ratings))
    ,m_viewpoints(std::move(to_move.m_viewpoints))
    ,m_contentComponents(std::move(to_move.m_contentComponents))
    ,m_baseURLs(std::move(to_move.m_baseURLs))
    ,m_segmentBase(std::move(to_move.m_segmentBase))
    ,m_segmentList(std::move(to_move.m_segmentList))
    ,m_segmentTemplate(std::move(to_move.m_segmentTemplate))
    ,m_representations(std::move(to_move.m_representations))
{
}

AdaptationSet &AdaptationSet::operator=(const AdaptationSet &to_copy)
{
    m_xlink = to_copy.m_xlink;
    m_id = to_copy.m_id;
    m_group = to_copy.m_group;
    m_lang = to_copy.m_lang;
    m_contentType = to_copy.m_contentType;
    m_par = to_copy.m_par;
    m_minBandwidth = to_copy.m_minBandwidth;
    m_maxBandwidth = to_copy.m_maxBandwidth;
    m_minWidth = to_copy.m_minWidth;
    m_maxWidth = to_copy.m_maxWidth;
    m_minHeight = to_copy.m_minHeight;
    m_maxHeight = to_copy.m_maxHeight;
    m_minFrameRate = to_copy.m_minFrameRate;
    m_maxFrameRate = to_copy.m_maxFrameRate;
    m_segmentAlignment = to_copy.m_segmentAlignment;
    m_bitstreamSwitching = to_copy.m_bitstreamSwitching;
    m_subsegmentAlignment = to_copy.m_subsegmentAlignment;
    m_subsegmentStartsWithSAP = to_copy.m_subsegmentStartsWithSAP;
    m_initializationSetRefs = to_copy.m_initializationSetRefs;
    m_initializationPrincipal = to_copy.m_initializationPrincipal;
    m_accessibility = to_copy.m_accessibility;
    m_roles = to_copy.m_roles;
    m_ratings = to_copy.m_ratings;
    m_viewpoints = to_copy.m_viewpoints;
    m_contentComponents = to_copy.m_contentComponents;
    m_baseURLs = to_copy.m_baseURLs;
    m_segmentBase = to_copy.m_segmentBase;
    m_segmentList = to_copy.m_segmentList;
    m_segmentTemplate = to_copy.m_segmentTemplate;
    m_representations = to_copy.m_representations;
    return *this;
}

AdaptationSet &AdaptationSet::operator=(AdaptationSet &&to_move)
{
    m_xlink = std::move(to_move.m_xlink);
    m_id = std::move(to_move.m_id);
    m_group = std::move(to_move.m_group);
    m_lang = std::move(to_move.m_lang);
    m_contentType = std::move(to_move.m_contentType);
    m_par = std::move(to_move.m_par);
    m_minBandwidth = std::move(to_move.m_minBandwidth);
    m_maxBandwidth = std::move(to_move.m_maxBandwidth);
    m_minWidth = std::move(to_move.m_minWidth);
    m_maxWidth = std::move(to_move.m_maxWidth);
    m_minHeight = std::move(to_move.m_minHeight);
    m_maxHeight = std::move(to_move.m_maxHeight);
    m_minFrameRate = std::move(to_move.m_minFrameRate);
    m_maxFrameRate = std::move(to_move.m_maxFrameRate);
    m_segmentAlignment = std::move(to_move.m_segmentAlignment);
    m_bitstreamSwitching = std::move(to_move.m_bitstreamSwitching);
    m_subsegmentAlignment = std::move(to_move.m_subsegmentAlignment);
    m_subsegmentStartsWithSAP = std::move(to_move.m_subsegmentStartsWithSAP);
    m_initializationSetRefs = std::move(to_move.m_initializationSetRefs);
    m_initializationPrincipal = std::move(to_move.m_initializationPrincipal);
    m_accessibility = std::move(to_move.m_accessibility);
    m_roles = std::move(to_move.m_roles);
    m_ratings = std::move(to_move.m_ratings);
    m_viewpoints = std::move(to_move.m_viewpoints);
    m_contentComponents = std::move(to_move.m_contentComponents);
    m_baseURLs = std::move(to_move.m_baseURLs);
    m_segmentBase = std::move(to_move.m_segmentBase);
    m_segmentList = std::move(to_move.m_segmentList);
    m_segmentTemplate = std::move(to_move.m_segmentTemplate);
    m_representations = std::move(to_move.m_representations);
    return *this;
}

/* protected: */
AdaptationSet::AdaptationSet(xmlpp::Node &node)
:m_xlink()
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
,m_bitstreamSwitching(false)
,m_subsegmentAlignment(false)
,m_subsegmentStartsWithSAP(0)
,m_initializationSetRefs()
,m_initializationPrincipal()
,m_accessibility()
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
        m_par = RatioType(std::string(attr->get_value()));
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
        if (attr->get_value() == "true") {
            m_segmentAlignment = true;
        }
    }

    node_set = node.find("@bitstreamSwitching");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        if (attr->get_value() == "true") {
            m_bitstreamSwitching = true;
        }
    }

     node_set = node.find("@subsegmentAlignment");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        if (attr->get_value() == "true") {
            m_subsegmentAlignment = true;
        }
    }

    node_set = node.find("@subsegmentStartsWithSAP");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
	m_subsegmentStartsWithSAP = Sap(static_cast<unsigned int>(std::stoul(attr->get_value())));
    }

    node_set = node.find("@initializationSetRef", ns_map);
    if (node_set.size() > 0) {
	xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
	std::istringstream iss(attr->get_value());
	unsigned int value = 0;
	while (iss >> value) {
            m_initializationSetRefs.push_back(value);
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
            m_accessibility.push_back(Accessibility(*node));
        }
    }

    node_set = node.find("mpd:Role", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_roles.push_back(Role(*node));
        }
    }

    node_set = node.find("mpd:Rating", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_ratings.push_back(Rating(*node));
        }
    }

    node_set = node.find("mpd:Viewpoint", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_viewpoints.push_back(Viewpoint(*node));
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
        }
    }

}

AdaptationSet &AdaptationSet::accessibilityAdd(const Accessibility &accessibility)
{
    m_accessibility.push_back(accessibility);
    return *this;
}

AdaptationSet &AdaptationSet::accessibilityAdd(Accessibility &&accessibility)
{
    m_accessibility.push_back(std::move(accessibility));
    return *this;
}

AdaptationSet &AdaptationSet::accessibilityRemove(const Accessibility &accessibility)
{
    m_accessibility.remove(accessibility);
    return *this;
}

AdaptationSet &AdaptationSet::accessibilityRemove(const std::list<Accessibility>::const_iterator &it)
{
    m_accessibility.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::accessibilityRemove(const std::list<Accessibility>::iterator &it)
{
    m_accessibility.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::roleAdd(const Role &role)
{
    m_roles.push_back(role);
    return *this;
}

AdaptationSet &AdaptationSet::roleAdd(Role &&role)
{
    m_roles.push_back(std::move(role));
    return *this;
}

AdaptationSet &AdaptationSet::roleRemove(const Role &role)
{
    m_roles.remove(role);
    return *this;
}

AdaptationSet &AdaptationSet::roleRemove(const std::list<Role>::const_iterator &it)
{
    m_roles.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::roleRemove(const std::list<Role>::iterator &it)
{
    m_roles.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::ratingAdd(const Rating &rating)
{
    m_ratings.push_back(rating);
    return *this;
}

AdaptationSet &AdaptationSet::ratingAdd(Rating &&rating)
{
    m_ratings.push_back(std::move(rating));
    return *this;
}

AdaptationSet &AdaptationSet::ratingRemove(const Rating &rating)
{
    m_ratings.remove(rating);
    return *this;
}

AdaptationSet &AdaptationSet::ratingRemove(const std::list<Rating>::const_iterator &it)
{
    m_ratings.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::ratingRemove(const std::list<Rating>::iterator &it)
{
    m_ratings.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::viewpointAdd(const Viewpoint &rating)
{
    m_viewpoints.push_back(rating);
    return *this;
}

AdaptationSet &AdaptationSet::viewpointAdd(Viewpoint &&rating)
{
    m_viewpoints.push_back(std::move(rating));
    return *this;
}

AdaptationSet &AdaptationSet::viewpointRemove(const Viewpoint &rating)
{
    m_viewpoints.remove(rating);
    return *this;
}

AdaptationSet &AdaptationSet::viewpointRemove(const std::list<Viewpoint>::const_iterator &it)
{
    m_viewpoints.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::viewpointRemove(const std::list<Viewpoint>::iterator &it)
{
    m_viewpoints.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::contentComponentAdd(const ContentComponent &rating)
{
    m_contentComponents.push_back(rating);
    return *this;
}

AdaptationSet &AdaptationSet::contentComponentAdd(ContentComponent &&rating)
{
    m_contentComponents.push_back(std::move(rating));
    return *this;
}

AdaptationSet &AdaptationSet::ContentComponentRemove(const ContentComponent &rating)
{
    m_contentComponents.remove(rating);
    return *this;
}

AdaptationSet &AdaptationSet::ContentComponentRemove(const std::list<ContentComponent>::const_iterator &it)
{
    m_contentComponents.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::ContentComponentRemove(const std::list<ContentComponent>::iterator &it)
{
    m_contentComponents.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::baseURLAdd(const BaseURL &base_url)
{
    m_baseURLs.push_back(base_url);
    return *this;
}

AdaptationSet &AdaptationSet::baseURLAdd(BaseURL &&base_url)
{
    m_baseURLs.push_back(std::move(base_url));
    return *this;
}

AdaptationSet &AdaptationSet::baseURLRemove(const BaseURL &base_url)
{
    m_baseURLs.remove(base_url);
    return *this;
}

AdaptationSet &AdaptationSet::baseURLRemove(const std::list<BaseURL>::const_iterator &it)
{
    m_baseURLs.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::baseURLRemove(const std::list<BaseURL>::iterator &it)
{
    m_baseURLs.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::representationAdd(const Representation &representation)
{
    m_representations.push_back(representation);
    return *this;
}

AdaptationSet &AdaptationSet::representationAdd(Representation &&representation)
{
    m_representations.push_back(std::move(representation));
    return *this;
}

AdaptationSet &AdaptationSet::representationRemove(const Representation &representation)
{
    m_representations.remove(representation);
    return *this;
}

AdaptationSet &AdaptationSet::representationRemove(const std::list<Representation>::const_iterator &it)
{
    m_representations.erase(it);
    return *this;
}

AdaptationSet &AdaptationSet::representationRemove(const std::list<Representation>::iterator &it)
{
    m_representations.erase(it);
    return *this;
}

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
            m_contentType.value().setXMLElement(elem);
        }

        if (m_par.has_value()) {
            m_par.value().setXMLElement(elem);
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
            m_minFrameRate.value().setXMLElement(elem);
        }

        if (m_maxFrameRate.has_value()) {
            m_maxFrameRate.value().setXMLElement(elem);
        }

        if (m_segmentAlignment.has_value()) {
            if (m_segmentAlignment.value()) {
                elem.set_attribute("segmentAlignment", "true");
	    }		

        }

        if (m_bitstreamSwitching) {
            elem.set_attribute("bitstreamSwitching", "true");
        }

        if (m_subsegmentAlignment.has_value()) {
            if (m_segmentAlignment.value()) {
                elem.set_attribute("subsegmentAlignment", "true");
            }
        }


        if (m_subsegmentStartsWithSAP.has_value()) {
            m_subsegmentStartsWithSAP.value().setXMLElement(elem);
        }

        for (const auto &init_set_ref : m_initializationSetRefs) {
	    elem.set_attribute("initializationSetRef", std::to_string(init_set_ref));
        }

        if(m_initializationPrincipal.has_value()) {
            elem.set_attribute("initializationPrincipal", m_initializationPrincipal.value());
        }
	
	for (const auto &accessibility : m_accessibility) {
            xmlpp::Element *child = elem.add_child_element("Accessibility");
            accessibility.setXMLElement(*child);
        }

        for (const auto &role : m_roles) {
            xmlpp::Element *child = elem.add_child_element("Roles");
            role.setXMLElement(*child);
        }


        for (const auto &rating : m_ratings) {
            xmlpp::Element *child = elem.add_child_element("Ratings");
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

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
