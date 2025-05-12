/*****************************************************************************
 * DASH MPD parsing library in C++: Period class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <chrono>
#include <list>
#include <memory>
#include <optional>
#include <string>

#include <libxml++/libxml++.h>
#include <libxml/tree.h>

#include "libmpd++/exceptions.hh"
#include "libmpd++/macros.hh"
#include "libmpd++/AdaptationSet.hh"
#include "libmpd++/BaseURL.hh"
#include "libmpd++/ContentProtection.hh"
#include "libmpd++/Descriptor.hh"
#include "libmpd++/EventStream.hh"
#include "libmpd++/Label.hh"
#include "libmpd++/MPD.hh"
#include "libmpd++/Preselection.hh"
#include "libmpd++/SegmentAvailability.hh"
#include "libmpd++/SegmentBase.hh"
#include "libmpd++/SegmentTemplate.hh"
#include "libmpd++/SegmentList.hh"
#include "libmpd++/XLink.hh"
#include <glibmm/ustring.h>

#include "constants.hh"
#include "conversions.hh"

#include "libmpd++/Period.hh"

using namespace std::literals::chrono_literals;
LIBMPDPP_NAMESPACE_BEGIN

Period::Period()
    :m_mpd()
    ,m_xlink()
    ,m_id()
    ,m_start()
    ,m_duration()
    ,m_bitstreamSwitching(false)
    ,m_calcStart()
    ,m_calcDuration()
    ,m_baseURLs()
    ,m_segmentBase()
    ,m_segmentList()
    ,m_segmentTemplate()
    ,m_assetIdentifier()
    ,m_eventStreams()
    ,m_serviceDescriptions()
    ,m_contentProtections()
    ,m_adaptationSets()
    ,m_subsets()
    ,m_supplementalProperties()
    ,m_emptyAdaptationSets()
    ,m_groupLabels()
    ,m_preselections()
{
}

Period::Period(const Period &to_copy)
    :m_mpd(to_copy.m_mpd)
    ,m_xlink(to_copy.m_xlink)
    ,m_id(to_copy.m_id)
    ,m_start(to_copy.m_start)
    ,m_duration(to_copy.m_duration)
    ,m_bitstreamSwitching(to_copy.m_bitstreamSwitching)
    ,m_calcStart(to_copy.m_calcStart)
    ,m_calcDuration(to_copy.m_calcDuration)
    ,m_baseURLs(to_copy.m_baseURLs)
    ,m_segmentBase(to_copy.m_segmentBase)
    ,m_segmentList(to_copy.m_segmentList)
    ,m_segmentTemplate(to_copy.m_segmentTemplate)
    ,m_assetIdentifier(to_copy.m_assetIdentifier)
    ,m_eventStreams(to_copy.m_eventStreams)
    ,m_serviceDescriptions(to_copy.m_serviceDescriptions)
    ,m_contentProtections(to_copy.m_contentProtections)
    ,m_adaptationSets(to_copy.m_adaptationSets)
    ,m_subsets(to_copy.m_subsets)
    ,m_supplementalProperties(to_copy.m_supplementalProperties)
    ,m_emptyAdaptationSets(to_copy.m_emptyAdaptationSets)
    ,m_groupLabels(to_copy.m_groupLabels)
    ,m_preselections(to_copy.m_preselections)
{
}

Period::Period(Period &&to_move)
    :m_mpd(std::move(to_move.m_mpd))
    ,m_xlink(std::move(to_move.m_xlink))
    ,m_id(std::move(to_move.m_id))
    ,m_start(std::move(to_move.m_start))
    ,m_duration(std::move(to_move.m_duration))
    ,m_bitstreamSwitching(to_move.m_bitstreamSwitching)
    ,m_calcStart(std::move(to_move.m_calcStart))
    ,m_calcDuration(std::move(to_move.m_calcDuration))
    ,m_baseURLs(std::move(to_move.m_baseURLs))
    ,m_segmentBase(std::move(to_move.m_segmentBase))
    ,m_segmentList(std::move(to_move.m_segmentList))
    ,m_segmentTemplate(std::move(to_move.m_segmentTemplate))
    ,m_assetIdentifier(std::move(to_move.m_assetIdentifier))
    ,m_eventStreams(std::move(to_move.m_eventStreams))
    ,m_serviceDescriptions(std::move(to_move.m_serviceDescriptions))
    ,m_contentProtections(std::move(to_move.m_contentProtections))
    ,m_adaptationSets(std::move(to_move.m_adaptationSets))
    ,m_subsets(std::move(to_move.m_subsets))
    ,m_supplementalProperties(std::move(to_move.m_supplementalProperties))
    ,m_emptyAdaptationSets(std::move(to_move.m_emptyAdaptationSets))
    ,m_groupLabels(std::move(to_move.m_groupLabels))
    ,m_preselections(std::move(to_move.m_preselections))
{
}

Period &Period::operator=(const Period &to_copy)
{
    m_mpd = to_copy.m_mpd;
    m_xlink = to_copy.m_xlink;
    m_id = to_copy.m_id;
    m_start = to_copy.m_start;
    m_duration = to_copy.m_duration;
    m_bitstreamSwitching = to_copy.m_bitstreamSwitching;
    m_calcStart = to_copy.m_calcStart;
    m_calcDuration = to_copy.m_calcDuration;
    m_baseURLs = to_copy.m_baseURLs;
    m_segmentBase = to_copy.m_segmentBase;
    m_segmentList = to_copy.m_segmentList;
    m_segmentTemplate = to_copy.m_segmentTemplate;
    m_assetIdentifier = to_copy.m_assetIdentifier;
    m_eventStreams = to_copy.m_eventStreams;
    m_serviceDescriptions = to_copy.m_serviceDescriptions;
    m_contentProtections = to_copy.m_contentProtections;
    m_adaptationSets = to_copy.m_adaptationSets;
    m_subsets = to_copy.m_subsets;
    m_supplementalProperties = to_copy.m_supplementalProperties;
    m_emptyAdaptationSets = to_copy.m_emptyAdaptationSets;
    m_groupLabels = to_copy.m_groupLabels;
    m_preselections = to_copy.m_preselections;

    return *this;
}

Period &Period::operator=(Period &&to_move)
{
    m_mpd = std::move(to_move.m_mpd);
    m_xlink = std::move(to_move.m_xlink);
    m_id = std::move(to_move.m_id);
    m_start = std::move(to_move.m_start);
    m_duration = std::move(to_move.m_duration);
    m_bitstreamSwitching = to_move.m_bitstreamSwitching;
    m_calcStart = std::move(to_move.m_calcStart);
    m_calcDuration = std::move(to_move.m_calcDuration);
    m_baseURLs = std::move(to_move.m_baseURLs);
    m_segmentBase = std::move(to_move.m_segmentBase);
    m_segmentList = std::move(to_move.m_segmentList);
    m_segmentTemplate = std::move(to_move.m_segmentTemplate);
    m_assetIdentifier = std::move(to_move.m_assetIdentifier);
    m_eventStreams = std::move(to_move.m_eventStreams);
    m_serviceDescriptions = std::move(to_move.m_serviceDescriptions);
    m_contentProtections = std::move(to_move.m_contentProtections);
    m_adaptationSets = std::move(to_move.m_adaptationSets);
    m_subsets = std::move(to_move.m_subsets);
    m_supplementalProperties = std::move(to_move.m_supplementalProperties);
    m_emptyAdaptationSets = std::move(to_move.m_emptyAdaptationSets);
    m_groupLabels = std::move(to_move.m_groupLabels);
    m_preselections = std::move(to_move.m_preselections);

    return *this;
}

bool Period::operator==(const Period &to_compare) const
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


    COMPARE_OPT_VALUES(m_id);
    COMPARE_OPT_VALUES(m_start);
    COMPARE_OPT_VALUES(m_duration);

    if (m_bitstreamSwitching != to_compare.m_bitstreamSwitching) return false;

    COMPARE_ANY_ORDER_LISTS(m_baseURLs);
    COMPARE_OPT_VALUES(m_segmentBase);
    COMPARE_OPT_VALUES(m_segmentList);
    COMPARE_OPT_VALUES(m_segmentTemplate);
    COMPARE_OPT_VALUES(m_assetIdentifier);
    COMPARE_ANY_ORDER_LISTS(m_eventStreams);
    COMPARE_ANY_ORDER_LISTS(m_serviceDescriptions);
    COMPARE_ANY_ORDER_LISTS(m_contentProtections);
    COMPARE_ANY_ORDER_LISTS(m_adaptationSets);
    COMPARE_ANY_ORDER_LISTS(m_subsets);
    COMPARE_ANY_ORDER_LISTS(m_supplementalProperties);
    COMPARE_ANY_ORDER_LISTS(m_emptyAdaptationSets);
    COMPARE_ANY_ORDER_LISTS(m_groupLabels);
    COMPARE_ANY_ORDER_LISTS(m_preselections);

    return true;
}

std::list<BaseURL> Period::getBaseURLs() const
{
    if (m_baseURLs.size() == 0 && m_mpd) return m_mpd->getBaseURLs();

    std::list<BaseURL> ret;
    std::list<BaseURL> parent_urls_cache;
    bool have_parent_urls = false;
    for (const auto &base_url : m_baseURLs) {
        if (base_url.url().isAbsoluteURL()) {
            ret.push_back(base_url);
        } else {
            if (m_mpd) {
                if (!have_parent_urls) {
                    parent_urls_cache = m_mpd->getBaseURLs();
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

void Period::selectAllRepresentations()
{
    for (auto &adapt_set : m_adaptationSets) {
        adapt_set.selectAllRepresentations();
    }
}

void Period::deselectAllRepresentations()
{
    for (auto &adapt_set : m_adaptationSets) {
        adapt_set.deselectAllRepresentations();
    }
}

std::unordered_set<const Representation*> Period::selectedRepresentations() const
{
    std::unordered_set<const Representation*> ret;
    for (auto &adapt_set : m_adaptationSets) {
        const auto &selected_reps = adapt_set.selectedRepresentations();
        ret.insert(selected_reps.begin(), selected_reps.end());
    }
    return ret;
}

std::list<SegmentAvailability> Period::selectedSegmentAvailability(const time_type &query_time) const
{
    // TODO: proper logic to scan all adaptation sets and combine results

    // For now just dummy values
    std::ostringstream oss;
    oss << std::chrono::duration_cast<std::chrono::seconds>(query_time.time_since_epoch()).count();

    return std::list({
        SegmentAvailability(query_time + 1s, 4s, std::string("http://example.com/a/placeholder-") + oss.str() + ".m4s"),
        SegmentAvailability(query_time + 1s, 4s, std::string("http://example.com/v/placeholder-") + oss.str() + ".m4s"),
        SegmentAvailability(query_time + 2s, 4s, std::string("http://example.com/s/placeholder-") + oss.str() + ".m4s")
    });
}

std::list<SegmentAvailability> Period::selectedInitialisationSegments() const
{
    // TODO: proper logic to scan all adaptation sets and combine results

    // For now just dummy values
    time_type avail_start = std::chrono::system_clock::now();
    if (m_mpd && m_mpd->hasAvailabilityStartTime()) {
        avail_start = m_mpd->availabilityStartTime().value();
    }
    return std::list({
        SegmentAvailability(avail_start, 4s, "http://example.com/a/placeholder_init.mp4"),
        SegmentAvailability(avail_start, 4s, "http://example.com/v/placeholder_init.mp4")
    });
}

// protected:

Period::Period(xmlpp::Node &node)
    :m_mpd()
    ,m_xlink()
    ,m_id()
    ,m_start()
    ,m_duration()
    ,m_bitstreamSwitching(false)
    ,m_calcStart()
    ,m_calcDuration()
    ,m_baseURLs()
    ,m_segmentBase()
    ,m_segmentList()
    ,m_segmentTemplate()
    ,m_assetIdentifier()
    ,m_eventStreams()
    ,m_serviceDescriptions()
    ,m_contentProtections()
    ,m_adaptationSets()
    ,m_subsets()
    ,m_supplementalProperties()
    ,m_emptyAdaptationSets()
    ,m_groupLabels()
    ,m_preselections()
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
            else if (xlink_actuate != "onRequest") throw ParseError("Period/@xlink:actuate can only be either \"onLoad\" or \"onRequest\"");
        }
        m_xlink = XLink(xlink_href, actuate, XLink::TYPE_SIMPLE, XLink::SHOW_EMBED);
    }

    node_set = node.find("@id");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_id = std::string(attr->get_value());
    }

    node_set = node.find("@start");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_start = str_to_duration<Period::duration_type>(attr->get_value());
    }

    node_set = node.find("@duration");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_duration = str_to_duration<Period::duration_type>(attr->get_value());
    }

    node_set = node.find("@bitstreamSwitching");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        if (attr->get_value() == "true") {
            m_bitstreamSwitching = true;
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

    node_set = node.find("mpd:AssetIdentifier", ns_map);
    if (node_set.size() > 0) {
        m_assetIdentifier = Descriptor(*node_set.front());
    }

    node_set = node.find("mpd:EventStream", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_eventStreams.push_back(EventStream(*node));
        }
    }

    node_set = node.find("mpd:ServiceDescription", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_serviceDescriptions.push_back(ServiceDescription(*node));
        }
    }

    node_set = node.find("mpd:ContentProtection", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_contentProtections.push_back(ContentProtection(*node));
        }
    }

    node_set = node.find("mpd:AdaptationSet", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            AdaptationSet adapt_set(*node);
            adapt_set.setPeriod(this);
            m_adaptationSets.push_back(std::move(adapt_set));
        }
    }

    node_set = node.find("mpd:Subset", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_subsets.push_back(Subset(*node));
        }
    }

    node_set = node.find("mpd:SupplementalProperty", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_supplementalProperties.push_back(Descriptor(*node));
        }
    }

    node_set = node.find("mpd:EmptyAdaptationSet", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            AdaptationSet adapt_set(*node);
            adapt_set.setPeriod(this);
            m_emptyAdaptationSets.push_back(std::move(adapt_set));
        }
    }

    node_set = node.find("mpd:GroupLabel", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_groupLabels.push_back(Label(*node));
        }
    }

    node_set = node.find("mpd:Preselection", ns_map);
    if (node_set.size() > 0) {
        for (auto node : node_set) {
            m_preselections.push_back(Preselection(*node));
        }
    }
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

void Period::setXMLElement(xmlpp::Element &elem) const
{
    if (m_xlink.has_value()) {
        // Period is referenced from another document
        const Glib::ustring& xlink_prefix = get_ns_prefix_for(elem, XLINK_NS, "xlink");
        elem.set_attribute("href", std::string(m_xlink.value().href()), xlink_prefix);
        if (m_xlink.value().actuate() != XLink::ACTUATE_ON_REQUEST) {
            elem.set_attribute("actuate", "onLoad", xlink_prefix);
        }
    } else {
        // Attributes
        if (m_id.has_value()) {
            elem.set_attribute("id", m_id.value());
        }
        if (m_start.has_value()) {
            elem.set_attribute("start", format_duration(m_start.value()));
        }
        if (m_duration.has_value()) {
            elem.set_attribute("duration", format_duration(m_duration.value()));
        }
        if (m_bitstreamSwitching) {
            elem.set_attribute("bitstreamSwitching", "true");
        }
        // Elements
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
        if (m_assetIdentifier.has_value()) {
            xmlpp::Element *child = elem.add_child_element("AssetIdentifier");
            m_assetIdentifier.value().setXMLElement(*child);
        }
        for (const auto &evt_strm : m_eventStreams) {
            xmlpp::Element *child = elem.add_child_element("EventStream");
            evt_strm.setXMLElement(*child);
        }
        for (const auto &svc_desc : m_serviceDescriptions) {
            xmlpp::Element *child = elem.add_child_element("ServiceDescription");
            svc_desc.setXMLElement(*child);
        }
        for (const auto &cont_prot : m_contentProtections) {
            xmlpp::Element *child = elem.add_child_element("ContentProtection");
            cont_prot.setXMLElement(*child);
        }
        for (const auto &adapt_set : m_adaptationSets) {
            xmlpp::Element *child = elem.add_child_element("AdaptationSet");
            adapt_set.setXMLElement(*child);
        }
        for (const auto &subset : m_subsets) {
            xmlpp::Element *child = elem.add_child_element("Subset");
            subset.setXMLElement(*child);
        }
        for (const auto &supp_prop : m_supplementalProperties) {
            xmlpp::Element *child = elem.add_child_element("SupplementalProperty");
            supp_prop.setXMLElement(*child);
        }
        for (const auto &adapt_set : m_emptyAdaptationSets) {
            xmlpp::Element *child = elem.add_child_element("EmptyAdaptationSet");
            adapt_set.setXMLElement(*child);
        }
        for (const auto &label : m_groupLabels) {
            xmlpp::Element *child = elem.add_child_element("GroupLabel");
            label.setXMLElement(*child);
        }
        for (const auto &presel : m_preselections) {
            xmlpp::Element *child = elem.add_child_element("Preselection");
            presel.setXMLElement(*child);
        }
    }
}

std::string Period::getMediaURL(const SegmentTemplate::Variables &vars) const
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
    return std::string();
}

std::string Period::getInitializationURL(const SegmentTemplate::Variables &vars) const
{
    if (m_segmentTemplate.has_value()) {
        return m_segmentTemplate.value().formatInitializationTemplate(vars);
    }
    if (m_segmentList.has_value()) {
        return m_segmentList.value().getInitializationURL();
    }
    return std::string();
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
