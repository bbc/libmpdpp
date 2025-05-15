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

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/AdaptationSet.hh"
#include "libmpd++/BaseURL.hh"
#include "libmpd++/ContentProtection.hh"
#include "libmpd++/Descriptor.hh"
#include "libmpd++/EventStream.hh"
#include "libmpd++/ExtendedBandwidth.hh"
#include "libmpd++/Label.hh"
#include "libmpd++/MPD.hh"
#include "libmpd++/Period.hh"
#include "libmpd++/Preselection.hh"
#include "libmpd++/SegmentBase.hh"
#include "libmpd++/SegmentTemplate.hh"
#include "libmpd++/SegmentList.hh"
#include "libmpd++/SubRepresentation.hh"
#include "libmpd++/XLink.hh"

#include "constants.hh"
#include "conversions.hh"
#include "stream_ops.hh"

#include "libmpd++/Representation.hh"

LIBMPDPP_NAMESPACE_BEGIN

Representation::Representation()
    :RepresentationBase()
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
    :RepresentationBase(to_copy)
    ,m_adaptationSet(nullptr)
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
    :RepresentationBase(std::move(to_move))
    ,m_adaptationSet(nullptr)
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
    RepresentationBase::operator=(to_copy);
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
    RepresentationBase::operator=(std::move(to_move));
    m_adaptationSet = to_move.m_adaptationSet;
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

    return RepresentationBase::operator==(to_compare);
}

MPD *Representation::getMPD()
{
    if (m_adaptationSet) return m_adaptationSet->getMPD();
    return nullptr;
}

const MPD *Representation::getMPD() const
{
    if (m_adaptationSet) return m_adaptationSet->getMPD();
    return nullptr;
}

Period *Representation::getPeriod()
{
    if (m_adaptationSet) return m_adaptationSet->getPeriod();
    return nullptr;
}
const Period *Representation::getPeriod() const
{
    if (m_adaptationSet) return m_adaptationSet->getPeriod();
    return nullptr;
}

URI Representation::getMediaURL(unsigned long segment_number) const
{
    if (m_segmentTemplate.has_value()) {
        return URI(m_segmentTemplate.value().formatMediaTemplate(getTemplateVars(segment_number))).resolveUsingBaseURLs(getBaseURLs());
    }
    if (m_segmentList.has_value()) {
        return URI(m_segmentList.value().getMediaURLForSegment(segment_number)).resolveUsingBaseURLs(getBaseURLs());
    }
    if (m_adaptationSet) {
        return URI(m_adaptationSet->getMediaURL(getTemplateVars(segment_number))).resolveUsingBaseURLs(m_adaptationSet->getBaseURLs());
    }
    return URI();
}

URI Representation::getMediaURL(time_type segment_time) const
{
    if (m_segmentTemplate.has_value()) {
        return URI(m_segmentTemplate.value().formatMediaTemplate(getTemplateVars(segment_time))).resolveUsingBaseURLs(getBaseURLs());
    }
    if (m_segmentList.has_value()) {
        // TODO: convert @a segment_time to a time offset for this presentation in the time base provided
        return URI(m_segmentList.value().getMediaURLForSegmentTime(0 /*segment_time*/)).resolveUsingBaseURLs(getBaseURLs());
    }
    if (m_adaptationSet) {
        return URI(m_adaptationSet->getMediaURL(getTemplateVars(segment_time))).resolveUsingBaseURLs(m_adaptationSet->getBaseURLs());
    }
    return URI();
}

URI Representation::getInitializationURL() const
{
    if (m_segmentTemplate.has_value()) {
        return URI(m_segmentTemplate.value().formatInitializationTemplate(getTemplateVars())).resolveUsingBaseURLs(getBaseURLs());
    }
    if (m_segmentList.has_value()) {
        return URI(m_segmentList.value().getInitializationURL()).resolveUsingBaseURLs(getBaseURLs());
    }
    if (m_adaptationSet) {
        return URI(m_adaptationSet->getInitializationURL(getTemplateVars())).resolveUsingBaseURLs(m_adaptationSet->getBaseURLs());
    }
    return URI();
}

std::list<BaseURL> Representation::getBaseURLs() const
{
    if (m_baseURLs.size() == 0 && m_adaptationSet) return m_adaptationSet->getBaseURLs();

    std::list<BaseURL> ret;
    std::list<BaseURL> parent_urls_cache;
    bool have_parent_urls = false;
    for (const auto &base_url : m_baseURLs) {
        if (base_url.url().isAbsoluteURL()) {
            ret.push_back(base_url);
        } else {
            if (m_adaptationSet) {
                if (!have_parent_urls) {
                    parent_urls_cache = m_adaptationSet->getBaseURLs();
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

bool Representation::isSelected() const
{
    if (!m_adaptationSet) return false;
    return m_adaptationSet->selectedRepresentations().contains(this);
}

SegmentAvailability Representation::segmentAvailability(const time_type &query_time) const
{
    SegmentAvailability ret;
    std::list<BaseURL> base_urls;

    time_type pres_time = query_time;
    const MPD *mpd = getMPD();
    if (mpd) {
        pres_time = mpd->systemTimeToPresentationTime(query_time);
        const auto &multi_base = getMultiSegmentBase();
        if (!mpd->isLive() && multi_base.hasDuration()) {
            // we want the next available, not the current segment for non-live
            pres_time += std::chrono::duration_cast<time_type::duration>(multi_base.durationAsDurationType());
        }
    }

    if (m_segmentTemplate) {
        base_urls = getBaseURLs();
        auto vars = getTemplateVars(pres_time);
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
                // Availability is at the end of segments for live
                ret.availabilityStartTime(ret.availabilityStartTime() + std::chrono::duration_cast<time_type::duration>(ret.segmentDuration()));
            }
        }
        ret.segmentURL(URI(m_segmentTemplate.value().formatMediaTemplate(vars)).resolveUsingBaseURLs(base_urls));
    } else if (m_segmentList.has_value()) {
        const Period *period = getPeriod();
        base_urls = getBaseURLs();
        duration_type pres_offset;
        if (!period) {
            // Assume a period start of 0 and availabilityStartTime of 0 - best we can do without any other information
            pres_offset = std::chrono::duration_cast<duration_type>(pres_time.time_since_epoch());
        } else {
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
            if (mpd) {
                ret.availabilityEndTime(mpd->availabilityEndTime());
            }
            pres_offset = std::chrono::duration_cast<duration_type>(pres_time - ret.availabilityStartTime()) - period->calcStart().value();
        }
        if (mpd) {
            // Adjust times back to system wallclock
            if (ret.hasAvailabilityEndTime()) {
                ret.availabilityEndTime(mpd->presentationTimeToSystemTime(ret.availabilityEndTime().value()));
            }
            ret.availabilityStartTime(mpd->presentationTimeToSystemTime(ret.availabilityStartTime()));
        }
        ret.segmentDuration(m_segmentList.value().durationAsDurationType());
        if (mpd && mpd->isLive()) {
            ret.availabilityStartTime(ret.availabilityStartTime() + std::chrono::duration_cast<time_type::duration>(ret.segmentDuration()));
        }
        ret.segmentURL(URI(m_segmentList.value().getMediaURLForSegmentTime(pres_offset)).resolveUsingBaseURLs(base_urls));
    }
    if (m_adaptationSet) {
        ret = m_adaptationSet->getMediaAvailability(getTemplateVars(pres_time));
    }

    return ret;
}

SegmentAvailability Representation::initialisationSegmentAvailability() const
{
    SegmentAvailability ret;
    std::list<BaseURL> base_urls;

    if (m_segmentTemplate.has_value()) {
        base_urls = getBaseURLs();
        ret.segmentURL(URI(m_segmentTemplate.value().formatInitializationTemplate(getTemplateVars())).resolveUsingBaseURLs(base_urls));
    } else if (m_segmentList.has_value()) {
        base_urls = getBaseURLs();
        ret.segmentURL(URI(m_segmentList.value().getInitializationURL()).resolveUsingBaseURLs(base_urls));
    } else if (m_adaptationSet) {
        ret = m_adaptationSet->getInitialisationAvailability(getTemplateVars());
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

// protected:

namespace {
    template<class T>
    std::list<T> split_attribute_str(const std::string &attr_value, char sep = ',')
    {
        std::list<T> ret;
        std::string::size_type start_pos = 0;
        for (auto pos = attr_value.find_first_of(sep); pos != std::string::npos; start_pos = pos+1, pos = attr_value.find_first_of(sep, start_pos)) {
            ret.push_back(T(attr_value.substr(start_pos, pos-start_pos)));
        }
        ret.push_back(T(attr_value.substr(start_pos)));

        return ret;
    }
}

Representation::Representation(xmlpp::Node &node)
    :RepresentationBase(node)
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
        m_associationIds = split_attribute_str<std::string>(attr->get_value());
    }

    node_set = node.find("@associationType");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_associationTypes = split_attribute_str<std::string>(attr->get_value());

    }

    node_set = node.find("@mediaStreamStructureId");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_mediaStreamStructureIds = split_attribute_str<std::string>(attr->get_value());
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
    RepresentationBase::setXMLElement(elem);

    // Attributes
    if(!m_id.empty()) {
        elem.set_attribute("id", m_id);
    }
    if (m_bandwidth != 0) {
        elem.set_attribute("bandwidth", std::to_string(m_bandwidth));
    }
    if (m_qualityRanking.has_value()) {
        elem.set_attribute("qualityRanking", std::to_string(m_qualityRanking.value()));
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

void Representation::setAdaptationSet(AdaptationSet *adapt_set)
{
    m_adaptationSet = adapt_set;
}

// private:

SegmentTemplate::Variables Representation::getTemplateVars() const
{
    return SegmentTemplate::Variables(m_id, std::nullopt, m_bandwidth);
}

SegmentTemplate::Variables Representation::getTemplateVars(unsigned long segment_number) const
{
    SegmentTemplate::Variables ret(getTemplateVars());

    ret.number(segment_number);

    auto &multi_seg_base = getMultiSegmentBase();
    ret.time(multi_seg_base.segmentNumberToTime(segment_number));

    return ret;
}

SegmentTemplate::Variables Representation::getTemplateVars(const Representation::time_type &time) const
{
    SegmentTemplate::Variables ret(getTemplateVars());

    auto &multi_seg_base = getMultiSegmentBase();
    auto period_start = getPeriodStartTime();
    unsigned long seg_num = 0;

    if (time > period_start) {
        seg_num = multi_seg_base.durationTypeToSegmentNumber(std::chrono::duration_cast<duration_type>(time - period_start));
    }

    return getTemplateVars(seg_num);
}

Representation::time_type Representation::getPeriodStartTime() const
{
    if (m_adaptationSet) return m_adaptationSet->getPeriodStartTime();
    return Representation::time_type(); // just return epoch if we can't find the adaptation set
}

const MultipleSegmentBase &Representation::getMultiSegmentBase() const
{
    if (m_segmentTemplate) return m_segmentTemplate.value();
    if (m_segmentList) return m_segmentTemplate.value();
    if (m_segmentBase) {
        static MultipleSegmentBase multi_no_duration;
        static_cast<SegmentBase&>(multi_no_duration) = m_segmentBase.value(); // copy over SegmentBase values
        return multi_no_duration;
    }
    if (m_adaptationSet) return m_adaptationSet->getMultiSegmentBase();

    static const MultipleSegmentBase empty_multi;
    return empty_multi;
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
