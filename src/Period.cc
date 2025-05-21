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
#include <cmath>
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <unordered_set>

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
#include "stream_ops.hh"

#include "libmpd++/Period.hh"

using namespace std::literals::chrono_literals;
LIBMPDPP_NAMESPACE_BEGIN

Period::Period()
    :m_mpd(nullptr)
    ,m_previousSibling(nullptr)
    ,m_nextSibling(nullptr)
    ,m_xlink()
    ,m_id()
    ,m_start()
    ,m_duration()
    ,m_bitstreamSwitching(false)
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
    ,m_cache(new Period::Cache)
{
}

Period::Period(const Period &to_copy)
    :m_mpd(to_copy.m_mpd)
    ,m_previousSibling(to_copy.m_previousSibling)
    ,m_nextSibling(to_copy.m_nextSibling)
    ,m_xlink(to_copy.m_xlink)
    ,m_id(to_copy.m_id)
    ,m_start(to_copy.m_start)
    ,m_duration(to_copy.m_duration)
    ,m_bitstreamSwitching(to_copy.m_bitstreamSwitching)
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
    ,m_cache(new Period::Cache(*to_copy.m_cache))
{
    for (auto &adapt_set : m_adaptationSets) {
        adapt_set.setPeriod(this);
    }
    for (auto &adapt_set : m_emptyAdaptationSets) {
        adapt_set.setPeriod(this);
    }
}

Period::Period(Period &&to_move)
    :m_mpd(to_move.m_mpd)
    ,m_previousSibling(to_move.m_previousSibling)
    ,m_nextSibling(to_move.m_nextSibling)
    ,m_xlink(std::move(to_move.m_xlink))
    ,m_id(std::move(to_move.m_id))
    ,m_start(std::move(to_move.m_start))
    ,m_duration(std::move(to_move.m_duration))
    ,m_bitstreamSwitching(to_move.m_bitstreamSwitching)
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
    ,m_cache(new Period::Cache(std::move(*to_move.m_cache)))
{
    for (auto &adapt_set : m_adaptationSets) {
        adapt_set.setPeriod(this);
    }
    for (auto &adapt_set : m_emptyAdaptationSets) {
        adapt_set.setPeriod(this);
    }
}

Period::~Period()
{
    delete m_cache;
}

Period &Period::operator=(const Period &to_copy)
{
    m_mpd = to_copy.m_mpd;
    m_previousSibling = to_copy.m_previousSibling;
    m_nextSibling = to_copy.m_nextSibling;
    m_xlink = to_copy.m_xlink;
    m_id = to_copy.m_id;
    m_start = to_copy.m_start;
    m_duration = to_copy.m_duration;
    m_bitstreamSwitching = to_copy.m_bitstreamSwitching;
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
    *m_cache = *to_copy.m_cache;

    for (auto &adapt_set : m_adaptationSets) {
        adapt_set.setPeriod(this);
    }
    for (auto &adapt_set : m_emptyAdaptationSets) {
        adapt_set.setPeriod(this);
    }

    return *this;
}

Period &Period::operator=(Period &&to_move)
{
    m_mpd = to_move.m_mpd;
    m_previousSibling = to_move.m_previousSibling;
    m_nextSibling = to_move.m_nextSibling;
    m_xlink = std::move(to_move.m_xlink);
    m_id = std::move(to_move.m_id);
    m_start = std::move(to_move.m_start);
    m_duration = std::move(to_move.m_duration);
    m_bitstreamSwitching = to_move.m_bitstreamSwitching;
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
    *m_cache = std::move(*to_move.m_cache);

    for (auto &adapt_set : m_adaptationSets) {
        adapt_set.setPeriod(this);
    }
    for (auto &adapt_set : m_emptyAdaptationSets) {
        adapt_set.setPeriod(this);
    }

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

Period &Period::baseURLAdd(const BaseURL &base_url)
{
    m_baseURLs.push_back(base_url);
    return *this;
}

Period &Period::baseURLAdd(BaseURL &&base_url)
{
    m_baseURLs.push_back(std::move(base_url));
    return *this;
}

Period &Period::baseURLRemove(const BaseURL &base_url)
{
    auto it = std::find(m_baseURLs.begin(), m_baseURLs.end(), base_url);
    return baseURLRemove(it);
}

Period &Period::baseURLRemove(const std::list<BaseURL>::const_iterator &it)
{
    if (it != m_baseURLs.end()) {
        m_baseURLs.erase(it);
    }
    return *this;
}

Period &Period::baseURLRemove(const std::list<BaseURL>::iterator &it)
{
    if (it != m_baseURLs.end()) {
        m_baseURLs.erase(it);
    }
    return *this;
}

std::list<BaseURL> Period::getBaseURLs() const
{
    if (m_baseURLs.empty() && m_mpd) return m_mpd->getBaseURLs();

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

Period &Period::eventStreamAdd(const EventStream &event_stream)
{
    m_eventStreams.push_back(event_stream);
    return *this;
}

Period &Period::eventStreamAdd(EventStream &&event_stream)
{
    m_eventStreams.push_back(std::move(event_stream));
    return *this;
}

Period &Period::eventStreamRemove(const EventStream &event_stream)
{
    return eventStreamRemove(std::find(m_eventStreams.begin(), m_eventStreams.end(), event_stream));
}

Period &Period::eventStreamRemove(const std::list<EventStream>::const_iterator &it)
{
    if (it != m_eventStreams.end()) {
        m_eventStreams.erase(it);
    }
    return *this;
}

Period &Period::eventStreamRemove(const std::list<EventStream>::iterator &it)
{
    if (it != m_eventStreams.end()) {
        m_eventStreams.erase(it);
    }
    return *this;
}

Period &Period::serviceDescriptionAdd(const ServiceDescription &service_desc)
{
    m_serviceDescriptions.push_back(service_desc);
    return *this;
}

Period &Period::serviceDescriptionAdd(ServiceDescription &&service_desc)
{
    m_serviceDescriptions.push_back(std::move(service_desc));
    return *this;
}

Period &Period::serviceDescriptionRemove(const ServiceDescription &service_desc)
{
    return serviceDescriptionRemove(std::find(m_serviceDescriptions.begin(), m_serviceDescriptions.end(), service_desc));
}

Period &Period::serviceDescriptionRemove(const std::list<ServiceDescription>::const_iterator &it)
{
    if (it != m_serviceDescriptions.end()) {
        m_serviceDescriptions.erase(it);
    }
    return *this;
}

Period &Period::serviceDescriptionRemove(const std::list<ServiceDescription>::iterator &it)
{
    if (it != m_serviceDescriptions.end()) {
        m_serviceDescriptions.erase(it);
    }
    return *this;
}

Period &Period::contentProtectionAdd(const ContentProtection &content_prot)
{
    m_contentProtections.push_back(content_prot);
    return *this;
}

Period &Period::contentProtectionAdd(ContentProtection &&content_prot)
{
    m_contentProtections.push_back(std::move(content_prot));
    return *this;
}

Period &Period::contentProtectionRemove(const ContentProtection &content_prot)
{
    return contentProtectionRemove(std::find(m_contentProtections.begin(), m_contentProtections.end(), content_prot));
}

Period &Period::contentProtectionRemove(const std::list<ContentProtection>::const_iterator &it)
{
    if (it != m_contentProtections.end()) {
        m_contentProtections.erase(it);
    }
    return *this;
}

Period &Period::contentProtectionRemove(const std::list<ContentProtection>::iterator &it)
{
    if (it != m_contentProtections.end()) {
        m_contentProtections.erase(it);
    }
    return *this;
}

Period &Period::adaptationSetAdd(const AdaptationSet &adapt_set)
{
    m_adaptationSets.push_back(adapt_set);
    m_adaptationSets.back().setPeriod(this);
    return *this;
}

Period &Period::adaptationSetAdd(AdaptationSet &&adapt_set)
{
    m_adaptationSets.push_back(std::move(adapt_set));
    m_adaptationSets.back().setPeriod(this);
    return *this;
}

Period &Period::adaptationSetRemove(const AdaptationSet &adapt_set)
{
    return adaptationSetRemove(std::find(m_adaptationSets.begin(), m_adaptationSets.end(), adapt_set));
}

Period &Period::adaptationSetRemove(const std::list<AdaptationSet>::const_iterator &it)
{
    if (it != m_adaptationSets.end()) {
        m_adaptationSets.erase(it);
    }
    return *this;
}

Period &Period::adaptationSetRemove(const std::list<AdaptationSet>::iterator &it)
{
    if (it != m_adaptationSets.end()) {
        m_adaptationSets.erase(it);
    }
    return *this;
}

Period &Period::subsetAdd(const Subset &subset)
{
    m_subsets.push_back(subset);
    return *this;
}

Period &Period::subsetAdd(Subset &&subset)
{
    m_subsets.push_back(std::move(subset));
    return *this;
}

Period &Period::subsetRemove(const Subset &subset)
{
    return subsetRemove(std::find(m_subsets.begin(), m_subsets.end(), subset));
}

Period &Period::subsetRemove(const std::list<Subset>::const_iterator &it)
{
    if (it != m_subsets.end()) {
        m_subsets.erase(it);
    }
    return *this;
}

Period &Period::subsetRemove(const std::list<Subset>::iterator &it)
{
    if (it != m_subsets.end()) {
        m_subsets.erase(it);
    }
    return *this;
}

Period &Period::supplementalPropertyAdd(const Descriptor &supp_prop)
{
    m_supplementalProperties.push_back(supp_prop);
    return *this;
}

Period &Period::supplementalPropertyAdd(Descriptor &&supp_prop)
{
    m_supplementalProperties.push_back(std::move(supp_prop));
    return *this;
}

Period &Period::supplementalPropertyRemove(const Descriptor &supp_prop)
{
    return supplementalPropertyRemove(std::find(m_supplementalProperties.begin(), m_supplementalProperties.end(), supp_prop));
}

Period &Period::supplementalPropertyRemove(const std::list<Descriptor>::const_iterator &it)
{
    if (it != m_supplementalProperties.end()) {
        m_supplementalProperties.erase(it);
    }
    return *this;
}

Period &Period::supplementalPropertyRemove(const std::list<Descriptor>::iterator &it)
{
    if (it != m_supplementalProperties.end()) {
        m_supplementalProperties.erase(it);
    }
    return *this;
}

Period &Period::emptyAdaptationSetAdd(const AdaptationSet &adapt_set)
{
    m_emptyAdaptationSets.push_back(adapt_set);
    m_emptyAdaptationSets.back().setPeriod(this);
    return *this;
}

Period &Period::emptyAdaptationSetAdd(AdaptationSet &&adapt_set)
{
    m_emptyAdaptationSets.push_back(std::move(adapt_set));
    m_emptyAdaptationSets.back().setPeriod(this);
    return *this;
}

Period &Period::emptyAdaptationSetRemove(const AdaptationSet &adapt_set)
{
    return emptyAdaptationSetRemove(std::find(m_emptyAdaptationSets.begin(), m_emptyAdaptationSets.end(), adapt_set));
}

Period &Period::emptyAdaptationSetRemove(const std::list<AdaptationSet>::const_iterator &it)
{
    if (it != m_emptyAdaptationSets.end()) {
        m_emptyAdaptationSets.erase(it);
    }
    return *this;
}

Period &Period::emptyAdaptationSetRemove(const std::list<AdaptationSet>::iterator &it)
{
    if (it != m_emptyAdaptationSets.end()) {
        m_emptyAdaptationSets.erase(it);
    }
    return *this;
}

Period &Period::groupLabelAdd(const Label &label)
{
    m_groupLabels.push_back(label);
    return *this;
}

Period &Period::groupLabelAdd(Label &&label)
{
    m_groupLabels.push_back(std::move(label));
    return *this;
}

Period &Period::groupLabelRemove(const Label &label)
{
    return groupLabelRemove(std::find(m_groupLabels.begin(), m_groupLabels.end(), label));
}

Period &Period::groupLabelRemove(const std::list<Label>::const_iterator &it)
{
    if (it != m_groupLabels.end()) {
        m_groupLabels.erase(it);
    }
    return *this;
}

Period &Period::groupLabelRemove(const std::list<Label>::iterator &it)
{
    if (it != m_groupLabels.end()) {
        m_groupLabels.erase(it);
    }
    return *this;
}

Period &Period::preselectionAdd(const Preselection &preselection)
{
    m_preselections.push_back(preselection);
    return *this;
}

Period &Period::preselectionAdd(Preselection &&preselection)
{
    m_preselections.push_back(std::move(preselection));
    return *this;
}

Period &Period::preselectionRemove(const Preselection &preselection)
{
    return preselectionRemove(std::find(m_preselections.begin(), m_preselections.end(), preselection));
}

Period &Period::preselectionRemove(const std::list<Preselection>::const_iterator &it)
{
    if (it != m_preselections.end()) {
        m_preselections.erase(it);
    }
    return *this;
}

Period &Period::preselectionRemove(const std::list<Preselection>::iterator &it)
{
    if (it != m_preselections.end()) {
        m_preselections.erase(it);
    }
    return *this;
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
    std::list<SegmentAvailability> ret;

    for (const auto &adapt_set : m_adaptationSets) {
        std::list<SegmentAvailability> adapt_set_segments(adapt_set.selectedSegmentAvailability(query_time));
        ret.insert(ret.end(), adapt_set_segments.begin(), adapt_set_segments.end());
    }

    return ret;
}

std::list<SegmentAvailability> Period::selectedInitializationSegments() const
{
    std::unordered_set<SegmentAvailability> ret;

    for (const auto &adapt_set : m_adaptationSets) {
        std::list<SegmentAvailability> adapt_set_init_segments(adapt_set.selectedInitializationSegments());
        ret.insert(adapt_set_init_segments.begin(), adapt_set_init_segments.end());
    }

    return std::list<SegmentAvailability>(ret.begin(), ret.end());
}

const std::optional<Period::duration_type> &Period::calcStart() const
{
    if (!m_cache->calcStart) {
        cacheCalcTimes();
    }
    return m_cache->calcStart;
}

const std::optional<Period::duration_type> &Period::calcDuration() const
{
    if (!m_cache->calcDuration) {
        cacheCalcTimes();
    }
    return m_cache->calcDuration;
}

// protected:

Period::Period(xmlpp::Node &node)
    :m_mpd(nullptr)
    ,m_previousSibling(nullptr)
    ,m_nextSibling(nullptr)
    ,m_xlink()
    ,m_id()
    ,m_start()
    ,m_duration()
    ,m_bitstreamSwitching(false)
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
    ,m_cache(new Period::Cache)
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

SegmentAvailability Period::getMediaAvailability(const SegmentTemplate::Variables &vars) const
{
    SegmentAvailability ret;
    std::list<BaseURL> base_urls;

    if (m_segmentTemplate.has_value()) {
        base_urls = getBaseURLs();
        unsigned int ts = 1;
        if (m_segmentTemplate.value().hasTimescale()) {
            ts = m_segmentTemplate.value().timescale().value();
        }
        if (base_urls.empty()) {
            if (m_mpd && m_mpd->hasAvailabilityStartTime()) {
                ret.availabilityStartTime(m_mpd->availabilityStartTime().value() + vars.timeAsDurationType(ts));
            }
        } else {
            const BaseURL &base_url = base_urls.front();
            if (base_url.hasAvailabilityTimeOffset()) {
                if (m_mpd && m_mpd->hasAvailabilityStartTime()) {
                    if (std::isnan(base_url.availabilityTimeOffset().value())) {
                        // All segments available at the MPD@availabilityStartTime
                        ret.availabilityStartTime(m_mpd->availabilityStartTime().value());
                    } else {
                        // available at MPD@availabilityStartTime - @availabilityTimeOffset + segment_time
                        ret.availabilityStartTime(m_mpd->availabilityStartTime().value() - std::chrono::duration_cast<duration_type>(std::chrono::duration<double, std::ratio<1>>(base_url.availabilityTimeOffset().value())) + vars.timeAsDurationType(ts));
                    }
                }
            } else if (m_mpd && m_mpd->hasAvailabilityStartTime()) {
                // available at MPD@availabilityStartTime + segment_time
                ret.availabilityStartTime(m_mpd->availabilityStartTime().value() + vars.timeAsDurationType(ts));
            }
        }
        if (m_mpd) {
            if (m_mpd->hasAvailabilityEndTime()) {
                ret.availabilityEndTime(m_mpd->presentationTimeToSystemTime(m_mpd->availabilityEndTime().value()));
            }
            ret.availabilityStartTime(m_mpd->presentationTimeToSystemTime(ret.availabilityStartTime()));
        }
        if (m_segmentTemplate.value().hasDuration()) {
            ret.segmentDuration(m_segmentTemplate.value().durationAsDurationType());
            if (m_mpd && m_mpd->isLive()) {
                ret.availabilityStartTime(ret.availabilityStartTime() + std::chrono::duration_cast<time_type::duration>(ret.segmentDuration()));
            }
        }
        ret.segmentURL(m_segmentTemplate.value().formatMediaTemplate(vars));
    } else if (m_segmentList.has_value()) {
        base_urls = getBaseURLs();
        if (base_urls.empty()) {
            if (m_mpd && m_mpd->hasAvailabilityStartTime()) {
                ret.availabilityStartTime(m_mpd->availabilityStartTime().value());
            }
        } else {
            const BaseURL &base_url = base_urls.front();
            if (base_url.hasAvailabilityTimeOffset() && !std::isnan(base_url.availabilityTimeOffset().value())) {
                if (m_mpd && m_mpd->hasAvailabilityStartTime()) {
                    ret.availabilityStartTime(m_mpd->availabilityStartTime().value() - std::chrono::duration_cast<duration_type>(std::chrono::duration<double, std::ratio<1>>(base_url.availabilityTimeOffset().value())));
                }
            } else if (m_mpd && m_mpd->hasAvailabilityStartTime()) {
                ret.availabilityStartTime(m_mpd->availabilityStartTime().value());
            }
        }
        ret.segmentDuration(m_segmentList.value().durationAsDurationType());
        if (m_mpd) {
            if (m_mpd->hasAvailabilityEndTime()) {
                ret.availabilityEndTime(m_mpd->presentationTimeToSystemTime(m_mpd->availabilityEndTime().value()));
            }
            ret.availabilityStartTime(m_mpd->presentationTimeToSystemTime(ret.availabilityStartTime()));
            if (m_mpd->isLive()) {
                ret.availabilityStartTime(ret.availabilityStartTime() + std::chrono::duration_cast<time_type::duration>(ret.segmentDuration()));
            }
        }

        if (vars.number()) {
            ret.segmentURL(m_segmentList.value().getMediaURLForSegment(vars.number().value()));
        } else if (vars.time()) {
            ret.segmentURL(m_segmentList.value().getMediaURLForSegmentTime(vars.time().value()));
        }
    }

    return ret;
}

SegmentAvailability Period::getInitialisationAvailability(const SegmentTemplate::Variables &vars) const
{
    SegmentAvailability ret;
    std::list<BaseURL> base_urls;

    if (m_segmentTemplate.has_value()) {
        base_urls = getBaseURLs();
        ret.segmentURL(URI(m_segmentTemplate.value().formatInitializationTemplate(vars)).resolveUsingBaseURLs(base_urls));
    } else if (m_segmentList.has_value()) {
        base_urls = getBaseURLs();
        ret.segmentURL(URI(m_segmentList.value().getInitializationURL()).resolveUsingBaseURLs(base_urls));
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

Period::time_type Period::getPeriodStartTime() const
{
    auto mpd = getMPD();
    if (!mpd) return time_type();
    if (!mpd->hasAvailabilityStartTime()) return time_type();

    // cache calculated start time if we don't have it already
    if (!m_cache->calcStart) cacheCalcTimes();

    if (m_cache->calcStart) {
        return mpd->availabilityStartTime().value() + m_cache->calcStart.value();
    }

    return mpd->availabilityStartTime().value();
}

std::optional<Period::duration_type> Period::getPeriodDuration() const
{
    // Try to cache calculated duration if we don't have one
    if (!m_cache->calcDuration) cacheCalcTimes();

    return m_cache->calcDuration;
}

const MultipleSegmentBase &Period::getMultiSegmentBase() const
{
    if (m_segmentTemplate) return m_segmentTemplate.value();
    if (m_segmentList) return m_segmentTemplate.value();
    if (m_segmentBase) {
        static MultipleSegmentBase multi_no_duration;
        SegmentBase &seg_base = multi_no_duration;
        seg_base = m_segmentBase.value(); // copy over SegmentBase values to get timescale
        return multi_no_duration;
    }

    static const MultipleSegmentBase empty_multi;
    return empty_multi;
}

// private:

void Period::cacheCalcTimes() const
{
    bool changed = false;

    // Set or reset our cache values for start and duration
    if (m_start && m_cache->calcStart != m_start) {
        m_cache->calcStart = m_start;
        changed = true;
    }
    if (!m_start && m_cache->calcStart) {
        m_cache->calcStart.reset();
        changed = true;
    }
    if (m_duration && m_cache->calcDuration != m_duration) {
        m_cache->calcDuration = m_duration;
        changed = true;
    }
    if (!m_duration && m_cache->calcDuration) {
        m_cache->calcDuration.reset();
        changed = true;
    }

    // go backward through siblings setting cache to local values
    for (Period *it = m_previousSibling; it; it = it->m_previousSibling) {
        if (it->m_start && it->m_cache->calcStart != it->m_start) {
            it->m_cache->calcStart = it->m_start;
            changed = true;
        }
        if (!it->m_start && it->m_cache->calcStart) {
            it->m_cache->calcStart.reset();
            changed = true;
        }
        if (it->m_duration && it->m_cache->calcDuration != it->m_duration) {
            it->m_cache->calcDuration = it->m_duration;
            changed = true;
        }
        if (!it->m_duration && it->m_cache->calcDuration) {
            it->m_cache->calcDuration.reset();
            changed = true;
        }
    }

    // go forward through siblings setting cache to local values
    for (Period *it = m_nextSibling; it; it = it->m_nextSibling) {
        if (it->m_start && it->m_cache->calcStart != it->m_start) {
            it->m_cache->calcStart = it->m_start;
            changed = true;
        }
        if (!it->m_start && it->m_cache->calcStart) {
            it->m_cache->calcStart.reset();
            changed = true;
        }
        if (it->m_duration && it->m_cache->calcDuration != it->m_duration) {
            it->m_cache->calcDuration = it->m_duration;
            changed = true;
        }
        if (!it->m_duration && it->m_cache->calcDuration) {
            it->m_cache->calcDuration.reset();
            changed = true;
        }
    }

    while (changed) {
        changed = false;

        // go backward through siblings setting relative cache values
        for (const Period *it = this; it; it = it->m_previousSibling) {
            if (!it->m_cache->calcStart && it->m_previousSibling && it->m_previousSibling->m_cache->calcStart && it->m_previousSibling->m_cache->calcDuration) {
                // this start = prev start + prev duration
                it->m_cache->calcStart = it->m_previousSibling->m_cache->calcStart.value() + it->m_previousSibling->m_cache->calcDuration.value();
                changed = true;
            }
            if (!it->m_cache->calcStart && it->m_cache->calcDuration && it->m_nextSibling  && it->m_nextSibling->m_cache->calcStart) {
                // this start = next start - this duration
                it->m_cache->calcStart = it->m_nextSibling->m_cache->calcStart.value() - it->m_cache->calcDuration.value();
                changed = true;
            }
            if (!it->m_cache->calcDuration && it->m_cache->calcStart && it->m_nextSibling && it->m_nextSibling->m_cache->calcStart) {
                // this duration = next start - this start
                it->m_cache->calcDuration = it->m_nextSibling->m_cache->calcStart.value() - it->m_cache->calcStart.value();
                changed = true;
            }
        }

        // go forward through siblings setting relative cache values
        for (Period *it = m_nextSibling; it; it = it->m_previousSibling) {
            if (!it->m_cache->calcStart && it->m_previousSibling && it->m_previousSibling->m_cache->calcStart && it->m_previousSibling->m_cache->calcDuration) {
                // this start = prev start + prev duration
                it->m_cache->calcStart = it->m_previousSibling->m_cache->calcStart.value() + it->m_previousSibling->m_cache->calcDuration.value();
                changed = true;
            }
            if (!it->m_cache->calcStart && it->m_cache->calcDuration && it->m_nextSibling  && it->m_nextSibling->m_cache->calcStart) {
                // this start = next start - this duration
                it->m_cache->calcStart = it->m_nextSibling->m_cache->calcStart.value() - it->m_cache->calcDuration.value();
                changed = true;
            }
            if (!it->m_cache->calcDuration && it->m_cache->calcStart && it->m_nextSibling && it->m_nextSibling->m_cache->calcStart) {
                // this duration = next start - this start
                it->m_cache->calcDuration = it->m_nextSibling->m_cache->calcStart.value() - it->m_cache->calcStart.value();
                changed = true;
            }
        }
    }
}

void Period::cacheCalcClear() const
{
    m_cache->calcStart.reset();
    m_cache->calcDuration.reset();
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
