/*****************************************************************************
 * DASH MPD parsing library in C++: RepresentationBase class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <chrono>
#include <functional>
#include <list>
#include <memory>
#include <optional>
#include <string>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/exceptions.hh"
#include "libmpd++/Codecs.hh"
#include "libmpd++/ContentPopularityRate.hh"
#include "libmpd++/ContentProtection.hh"
#include "libmpd++/Descriptor.hh"
#include "libmpd++/EventStream.hh"
#include "libmpd++/FrameRate.hh"
#include "libmpd++/Label.hh"
#include "libmpd++/ProducerReferenceTime.hh"
#include "libmpd++/RandomAccess.hh"
#include "libmpd++/Ratio.hh"
#include "libmpd++/Resync.hh"
#include "libmpd++/SAP.hh"
#include "libmpd++/Switching.hh"
#include "libmpd++/URI.hh"

#include "constants.hh"
#include "conversions.hh"

#include "libmpd++/RepresentationBase.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

RepresentationBase::RepresentationBase()
    :m_profiles()
    ,m_width()
    ,m_height()
    ,m_sar()
    ,m_frameRate()
    ,m_audioSamplingRate()
    ,m_mimeType()
    ,m_segmentProfiles()
    ,m_codecs()
    ,m_containerProfiles()
    ,m_maximumSAPPeriod()
    ,m_startWithSAP()
    ,m_maxPlayoutRate()
    ,m_codingDependency()
    ,m_scanType()
    ,m_selectionPriority(1)
    ,m_tag()
    ,m_framePackings()
    ,m_audioChannelConfigurations()
    ,m_contentProtections()
    ,m_outputProtection()
    ,m_essentialProperties()
    ,m_supplementalProperties()
    ,m_inbandEventStreams()
    ,m_switchings()
    ,m_randomAccesses()
    ,m_groupLabels()
    ,m_labels()
    ,m_producerReferenceTimes()
    ,m_contentPopularityRates()
    ,m_resyncs()
{
}

RepresentationBase::RepresentationBase(const RepresentationBase &to_copy)
    :m_profiles(to_copy.m_profiles)
    ,m_width(to_copy.m_width)
    ,m_height(to_copy.m_height)
    ,m_sar(to_copy.m_sar)
    ,m_frameRate(to_copy.m_frameRate)
    ,m_audioSamplingRate(to_copy.m_audioSamplingRate)
    ,m_mimeType(to_copy.m_mimeType)
    ,m_segmentProfiles(to_copy.m_segmentProfiles)
    ,m_codecs(to_copy.m_codecs)
    ,m_containerProfiles(to_copy.m_containerProfiles)
    ,m_maximumSAPPeriod(to_copy.m_maximumSAPPeriod)
    ,m_startWithSAP(to_copy.m_startWithSAP)
    ,m_maxPlayoutRate(to_copy.m_maxPlayoutRate)
    ,m_codingDependency(to_copy.m_codingDependency)
    ,m_scanType(to_copy.m_scanType)
    ,m_selectionPriority(to_copy.m_selectionPriority)
    ,m_tag(to_copy.m_tag)
    ,m_framePackings(to_copy.m_framePackings)
    ,m_audioChannelConfigurations(to_copy.m_audioChannelConfigurations)
    ,m_contentProtections(to_copy.m_contentProtections)
    ,m_outputProtection(to_copy.m_outputProtection)
    ,m_essentialProperties(to_copy.m_essentialProperties)
    ,m_supplementalProperties(to_copy.m_supplementalProperties)
    ,m_inbandEventStreams(to_copy.m_inbandEventStreams)
    ,m_switchings(to_copy.m_switchings)
    ,m_randomAccesses(to_copy.m_randomAccesses)
    ,m_groupLabels(to_copy.m_groupLabels)
    ,m_labels(to_copy.m_labels)
    ,m_producerReferenceTimes(to_copy.m_producerReferenceTimes)
    ,m_contentPopularityRates(to_copy.m_contentPopularityRates)
    ,m_resyncs(to_copy.m_resyncs)
{
}

RepresentationBase::RepresentationBase(RepresentationBase &&to_move)
    :m_profiles(std::move(to_move.m_profiles))
    ,m_width(std::move(to_move.m_width))
    ,m_height(std::move(to_move.m_height))
    ,m_sar(std::move(to_move.m_sar))
    ,m_frameRate(std::move(to_move.m_frameRate))
    ,m_audioSamplingRate(std::move(to_move.m_audioSamplingRate))
    ,m_mimeType(std::move(to_move.m_mimeType))
    ,m_segmentProfiles(std::move(to_move.m_segmentProfiles))
    ,m_codecs(std::move(to_move.m_codecs))
    ,m_containerProfiles(std::move(to_move.m_containerProfiles))
    ,m_maximumSAPPeriod(std::move(to_move.m_maximumSAPPeriod))
    ,m_startWithSAP(std::move(to_move.m_startWithSAP))
    ,m_maxPlayoutRate(std::move(to_move.m_maxPlayoutRate))
    ,m_codingDependency(std::move(to_move.m_codingDependency))
    ,m_scanType(std::move(to_move.m_scanType))
    ,m_selectionPriority(std::move(to_move.m_selectionPriority))
    ,m_tag(std::move(to_move.m_tag))
    ,m_framePackings(std::move(to_move.m_framePackings))
    ,m_audioChannelConfigurations(std::move(to_move.m_audioChannelConfigurations))
    ,m_contentProtections(std::move(to_move.m_contentProtections))
    ,m_outputProtection(std::move(to_move.m_outputProtection))
    ,m_essentialProperties(std::move(to_move.m_essentialProperties))
    ,m_supplementalProperties(std::move(to_move.m_supplementalProperties))
    ,m_inbandEventStreams(std::move(to_move.m_inbandEventStreams))
    ,m_switchings(std::move(to_move.m_switchings))
    ,m_randomAccesses(std::move(to_move.m_randomAccesses))
    ,m_groupLabels(std::move(to_move.m_groupLabels))
    ,m_labels(std::move(to_move.m_labels))
    ,m_producerReferenceTimes(std::move(to_move.m_producerReferenceTimes))
    ,m_contentPopularityRates(std::move(to_move.m_contentPopularityRates))
    ,m_resyncs(std::move(to_move.m_resyncs))
{
}

RepresentationBase &RepresentationBase::operator=(const RepresentationBase &to_copy)
{
    m_profiles = to_copy.m_profiles;
    m_width = to_copy.m_width;
    m_height = to_copy.m_height;
    m_sar = to_copy.m_sar;
    m_frameRate = to_copy.m_frameRate;
    m_audioSamplingRate = to_copy.m_audioSamplingRate;
    m_mimeType = to_copy.m_mimeType;
    m_segmentProfiles = to_copy.m_segmentProfiles;
    m_codecs = to_copy.m_codecs;
    m_containerProfiles = to_copy.m_containerProfiles;
    m_maximumSAPPeriod = to_copy.m_maximumSAPPeriod;
    m_startWithSAP = to_copy.m_startWithSAP;
    m_maxPlayoutRate = to_copy.m_maxPlayoutRate;
    m_codingDependency = to_copy.m_codingDependency;
    m_scanType = to_copy.m_scanType;
    m_selectionPriority = to_copy.m_selectionPriority;
    m_tag = to_copy.m_tag;
    m_framePackings = to_copy.m_framePackings;
    m_audioChannelConfigurations = to_copy.m_audioChannelConfigurations;
    m_contentProtections = to_copy.m_contentProtections;
    m_outputProtection = to_copy.m_outputProtection;
    m_essentialProperties = to_copy.m_essentialProperties;
    m_supplementalProperties = to_copy.m_supplementalProperties;
    m_inbandEventStreams = to_copy.m_inbandEventStreams;
    m_switchings = to_copy.m_switchings;
    m_randomAccesses = to_copy.m_randomAccesses;
    m_groupLabels = to_copy.m_groupLabels;
    m_labels = to_copy.m_labels;
    m_producerReferenceTimes = to_copy.m_producerReferenceTimes;
    m_contentPopularityRates = to_copy.m_contentPopularityRates;
    m_resyncs = to_copy.m_resyncs;

    return *this;
}

RepresentationBase &RepresentationBase::operator=(RepresentationBase &&to_move)
{
    m_profiles = std::move(to_move.m_profiles);
    m_width = std::move(to_move.m_width);
    m_height = std::move(to_move.m_height);
    m_sar = std::move(to_move.m_sar);
    m_frameRate = std::move(to_move.m_frameRate);
    m_audioSamplingRate = std::move(to_move.m_audioSamplingRate);
    m_mimeType = std::move(to_move.m_mimeType);
    m_segmentProfiles = std::move(to_move.m_segmentProfiles);
    m_codecs = std::move(to_move.m_codecs);
    m_containerProfiles = std::move(to_move.m_containerProfiles);
    m_maximumSAPPeriod = std::move(to_move.m_maximumSAPPeriod);
    m_startWithSAP = std::move(to_move.m_startWithSAP);
    m_maxPlayoutRate = std::move(to_move.m_maxPlayoutRate);
    m_codingDependency = std::move(to_move.m_codingDependency);
    m_scanType = std::move(to_move.m_scanType);
    m_selectionPriority = std::move(to_move.m_selectionPriority);
    m_tag = std::move(to_move.m_tag);
    m_framePackings = std::move(to_move.m_framePackings);
    m_audioChannelConfigurations = std::move(to_move.m_audioChannelConfigurations);
    m_contentProtections = std::move(to_move.m_contentProtections);
    m_outputProtection = std::move(to_move.m_outputProtection);
    m_essentialProperties = std::move(to_move.m_essentialProperties);
    m_supplementalProperties = std::move(to_move.m_supplementalProperties);
    m_inbandEventStreams = std::move(to_move.m_inbandEventStreams);
    m_switchings = std::move(to_move.m_switchings);
    m_randomAccesses = std::move(to_move.m_randomAccesses);
    m_groupLabels = std::move(to_move.m_groupLabels);
    m_labels = std::move(to_move.m_labels);
    m_producerReferenceTimes = std::move(to_move.m_producerReferenceTimes);
    m_contentPopularityRates = std::move(to_move.m_contentPopularityRates);
    m_resyncs = std::move(to_move.m_resyncs);

    return *this;
}

bool RepresentationBase::operator==(const RepresentationBase &to_compare) const
{
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
#define COMPARE_OPT_VALUES(var) do { \
        if (var.has_value() != to_compare.var.has_value()) return false; \
        if (var.has_value() && !(var.value() == to_compare.var.value())) return false; \
    } while(0)

    COMPARE_ANY_ORDER_LISTS(m_profiles);
    COMPARE_OPT_VALUES(m_width);
    COMPARE_OPT_VALUES(m_height);
    COMPARE_OPT_VALUES(m_sar);
    COMPARE_OPT_VALUES(m_frameRate);
    COMPARE_ANY_ORDER_LISTS(m_audioSamplingRate);
    COMPARE_OPT_VALUES(m_mimeType);
    COMPARE_ANY_ORDER_LISTS(m_segmentProfiles);
    COMPARE_OPT_VALUES(m_codecs);
    COMPARE_ANY_ORDER_LISTS(m_containerProfiles);
    COMPARE_OPT_VALUES(m_maximumSAPPeriod);
    COMPARE_OPT_VALUES(m_startWithSAP);
    COMPARE_OPT_VALUES(m_maxPlayoutRate);
    COMPARE_OPT_VALUES(m_codingDependency);
    COMPARE_OPT_VALUES(m_scanType);
    if (m_selectionPriority != to_compare.m_selectionPriority) return false;
    COMPARE_OPT_VALUES(m_tag);

    COMPARE_ANY_ORDER_LISTS(m_framePackings);
    COMPARE_ANY_ORDER_LISTS(m_audioChannelConfigurations);
    COMPARE_ANY_ORDER_LISTS(m_contentProtections);
    COMPARE_OPT_VALUES(m_outputProtection);
    COMPARE_ANY_ORDER_LISTS(m_essentialProperties);
    COMPARE_ANY_ORDER_LISTS(m_supplementalProperties);
    COMPARE_ANY_ORDER_LISTS(m_inbandEventStreams);
    COMPARE_ANY_ORDER_LISTS(m_switchings);
    COMPARE_ANY_ORDER_LISTS(m_randomAccesses);
    COMPARE_ANY_ORDER_LISTS(m_groupLabels);
    COMPARE_ANY_ORDER_LISTS(m_labels);
    COMPARE_ANY_ORDER_LISTS(m_producerReferenceTimes);
    COMPARE_ANY_ORDER_LISTS(m_contentPopularityRates);
    COMPARE_ANY_ORDER_LISTS(m_resyncs);

#undef COMPARE_ANY_ORDER_LISTS
#undef COMPARE_OPT_VALUES

    return true;
}

static unsigned int str_to_ui(const std::string &s)
{
    return static_cast<unsigned int>(std::stoul(s));
}

static bool str_to_bool(const std::string &s)
{
    if (s == "true" || s == "1") return true;
    if (s == "false" || s == "0") return false;
    throw ParseError("Boolean attributes can only contain \"true\", \"1\", \"false\" or \"0\"");
}

static RepresentationBase::VideoScan str_to_VideoScan(const std::string &s)
{
    if (s == "progressive") return RepresentationBase::VIDEO_SCAN_PROGRESSIVE;
    if (s == "interlaced") return RepresentationBase::VIDEO_SCAN_INTERLACED;
    return RepresentationBase::VIDEO_SCAN_UNKNOWN;
}

static std::string bool_to_str(bool val)
{
    return val?"true":"false";
}

static std::string videoScan_to_str(RepresentationBase::VideoScan val)
{
    switch (val) {
    case RepresentationBase::VIDEO_SCAN_PROGRESSIVE:
        return "progressive";
    case RepresentationBase::VIDEO_SCAN_INTERLACED:
        return "interlaced";
    default:
        break;
    }
    return "unknown";
}

namespace {
    template<typename T>
    std::list<T> str_to_list(const std::string &attr_val, char sep = ',')
    {
        std::list<T> ret;
        std::string::size_type start_pos = 0;
        for (auto pos = attr_val.find_first_of(sep); pos != std::string::npos; start_pos = pos+1, pos = attr_val.find_first_of(sep, start_pos)) {
            auto val = attr_val.substr(start_pos, pos - start_pos);
            if (!val.empty()) {
                ret.push_back(T(val));
            }
        }
        auto val = attr_val.substr(start_pos);
        if (!val.empty()) {
            ret.push_back(T(val));
        }
        return ret;
    }

    template<>
    std::list<unsigned int> str_to_list<unsigned int>(const std::string &attr_val, char sep)
    {
        std::list<unsigned int> ret;
        std::string::size_type start_pos = 0;
        for (auto pos = attr_val.find_first_of(sep); pos != std::string::npos; start_pos = pos+1, pos = attr_val.find_first_of(sep, start_pos)) {
            auto val = attr_val.substr(start_pos, pos - start_pos);
            if (!val.empty()) {
                ret.push_back(str_to_ui(val));
            }
        }
        auto val = attr_val.substr(start_pos);
        if (!val.empty()) {
            ret.push_back(str_to_ui(val));
        }
        return ret;
    }
}

// protected:
RepresentationBase::RepresentationBase(xmlpp::Node &node)
    :m_profiles()
    ,m_width()
    ,m_height()
    ,m_sar()
    ,m_frameRate()
    ,m_audioSamplingRate()
    ,m_mimeType()
    ,m_segmentProfiles()
    ,m_codecs()
    ,m_containerProfiles()
    ,m_maximumSAPPeriod()
    ,m_startWithSAP()
    ,m_maxPlayoutRate()
    ,m_codingDependency()
    ,m_scanType()
    ,m_selectionPriority(1)
    ,m_tag()
    ,m_framePackings()
    ,m_audioChannelConfigurations()
    ,m_contentProtections()
    ,m_outputProtection()
    ,m_essentialProperties()
    ,m_supplementalProperties()
    ,m_inbandEventStreams()
    ,m_switchings()
    ,m_randomAccesses()
    ,m_groupLabels()
    ,m_labels()
    ,m_producerReferenceTimes()
    ,m_contentPopularityRates()
    ,m_resyncs()
{
    static const xmlpp::Node::PrefixNsMap ns_map = {
        {"mpd", MPD_NS}
    };
    xmlpp::Node::NodeSet node_set;

#define NODE_ATTR_LIST_CLASS(name, cls) do { \
        node_set = node.find("@" #name); \
        if (node_set.size() > 0) { \
            xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front()); \
            m_ ## name = str_to_list<cls>(attr->get_value()); \
        } \
    } while (0)
#define NODE_ATTR_OPT_FN(name, fn) do { \
        node_set = node.find("@" #name); \
        if (node_set.size() > 0) { \
            xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front()); \
            m_ ## name = fn(attr->get_value()); \
        } \
    } while (0)
#define NODE_ATTR_OPT_FN_DEFAULT(name, fn, dflt) do { \
        node_set = node.find("@" #name); \
        if (node_set.size() > 0) { \
            xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front()); \
            m_ ## name = fn(attr->get_value()); \
        } else { \
            m_ ## name = dflt; \
        } \
    } while (0)

    NODE_ATTR_LIST_CLASS(profiles, URI);
    NODE_ATTR_OPT_FN(width, str_to_ui);
    NODE_ATTR_OPT_FN(height, str_to_ui);
    NODE_ATTR_OPT_FN(sar, Ratio);
    NODE_ATTR_OPT_FN(frameRate, FrameRate);
    NODE_ATTR_LIST_CLASS(audioSamplingRate, unsigned int);
    NODE_ATTR_OPT_FN(mimeType, std::string);
    NODE_ATTR_LIST_CLASS(segmentProfiles, std::string);
    NODE_ATTR_OPT_FN(codecs, Codecs);
    NODE_ATTR_LIST_CLASS(containerProfiles, std::string);
    NODE_ATTR_OPT_FN(maximumSAPPeriod, std::stod);
    NODE_ATTR_OPT_FN(startWithSAP, SAP);
    NODE_ATTR_OPT_FN(maxPlayoutRate, std::stod);
    NODE_ATTR_OPT_FN(codingDependency, str_to_bool);
    NODE_ATTR_OPT_FN(scanType, str_to_VideoScan);
    NODE_ATTR_OPT_FN_DEFAULT(selectionPriority, str_to_ui, 1);
    NODE_ATTR_OPT_FN(tag, std::string);

#undef NODE_ATTR_OPT_FN_DEFAULT
#undef NODE_ATTR_OPT_FN
#undef NODE_ATTR_LIST_CLASS
#undef NODE_ATTR_LIST_TYPE

#define NODE_CHILD_OPT_LIST(name, var, cls) do { \
        node_set = node.find("mpd:" #name, ns_map); \
        for (auto node : node_set) { \
            var.push_back(cls(*node)); \
        } \
    } while (0)
#define NODE_CHILD_OPT(name, var, cls) do { \
        node_set = node.find("mpd:" #name, ns_map); \
        if (node_set.size() > 1) { \
            throw ParseError("<RepresentationBase>/" #name " can only be used once per <RepresentationBase>"); \
        } else if (node_set.size() == 1) { \
            var = cls(*node_set.front()); \
        } \
    } while (0)

    NODE_CHILD_OPT_LIST(FramePacking, m_framePackings, Descriptor);
    NODE_CHILD_OPT_LIST(AudioChannelConfiguration, m_audioChannelConfigurations, Descriptor);
    NODE_CHILD_OPT_LIST(ContentProtection, m_contentProtections, Descriptor);
    NODE_CHILD_OPT(OutputProtection, m_outputProtection, Descriptor);
    NODE_CHILD_OPT_LIST(EssentialProperty, m_essentialProperties, Descriptor);
    NODE_CHILD_OPT_LIST(SupplementalProperty, m_supplementalProperties, Descriptor);
    NODE_CHILD_OPT_LIST(InbandEventStream, m_inbandEventStreams, EventStream);
    NODE_CHILD_OPT_LIST(Switching, m_switchings, Switching);
    NODE_CHILD_OPT_LIST(RandomAccess, m_randomAccesses, RandomAccess);
    NODE_CHILD_OPT_LIST(GroupLabel, m_groupLabels, Label);
    NODE_CHILD_OPT_LIST(Label, m_labels, Label);
    NODE_CHILD_OPT_LIST(ProducerReferenceTime, m_producerReferenceTimes, ProducerReferenceTime);
    NODE_CHILD_OPT_LIST(ContentPopularityRate, m_contentPopularityRates, ContentPopularityRate);
    NODE_CHILD_OPT_LIST(Resync, m_resyncs, Resync);

#undef NODE_CHILD_OPT_LIST
#undef NODE_CHILD_OPT
}

void RepresentationBase::setXMLElement(xmlpp::Element &elem) const
{
#define ELEM_ADD_OPT_ATTR_FMT(name, fmt) do { \
        if (m_ ## name.has_value()) { \
            elem.set_attribute(#name, fmt(m_ ##name.value())); \
        } \
    } while(0)
#define ELEM_ADD_OPT_ATTR_LIST_FN(name, fn) do { \
        if (m_ ## name.size() > 0) { \
            std::ostringstream attr_val; \
            const char *sep = ""; \
            for (const auto &val : m_ ## name) { \
                attr_val << sep << fn(val); \
                sep = ","; \
            } \
            elem.set_attribute(#name, attr_val.str()); \
        } \
    } while(0)
#define ELEM_ADD_OPT_ATTR_LIST(name) ELEM_ADD_OPT_ATTR_LIST_FN(name, std::string)

    ELEM_ADD_OPT_ATTR_LIST(profiles);
    ELEM_ADD_OPT_ATTR_FMT(width, std::to_string);
    ELEM_ADD_OPT_ATTR_FMT(height, std::to_string);
    ELEM_ADD_OPT_ATTR_FMT(sar, std::string);
    ELEM_ADD_OPT_ATTR_FMT(frameRate, std::string);
    ELEM_ADD_OPT_ATTR_LIST_FN(audioSamplingRate, std::to_string);
    ELEM_ADD_OPT_ATTR_FMT(mimeType, std::string);
    ELEM_ADD_OPT_ATTR_LIST(segmentProfiles);
    ELEM_ADD_OPT_ATTR_FMT(codecs, std::string);
    ELEM_ADD_OPT_ATTR_LIST(containerProfiles);
    ELEM_ADD_OPT_ATTR_FMT(maximumSAPPeriod, std::to_string);
    ELEM_ADD_OPT_ATTR_FMT(startWithSAP, std::string);
    ELEM_ADD_OPT_ATTR_FMT(maxPlayoutRate, std::to_string);
    ELEM_ADD_OPT_ATTR_FMT(codingDependency, bool_to_str);
    ELEM_ADD_OPT_ATTR_FMT(scanType, videoScan_to_str);
    if (m_selectionPriority != 1) {
        elem.set_attribute("selectionPriority", std::to_string(m_selectionPriority));
    }
    ELEM_ADD_OPT_ATTR_FMT(tag, std::string);

#undef ELEM_ADD_OPT_ATTR_LIST
#undef ELEM_ADD_OPT_ATTR_FMT

#define ELEM_ADD_OPT_CHILD_LIST(name, var) do { \
        for (const auto &val : var) { \
            xmlpp::Element *child = elem.add_child_element(#name); \
            val.setXMLElement(*child); \
        } \
    } while(0)
#define ELEM_ADD_OPT_CHILD(name, var) do { \
        if (var.has_value()) { \
            xmlpp::Element *child = elem.add_child_element(#name); \
            var.value().setXMLElement(*child); \
        } \
    } while(0)

    ELEM_ADD_OPT_CHILD_LIST(FramePackings, m_framePackings);
    ELEM_ADD_OPT_CHILD_LIST(AudioChannelConfiguration, m_audioChannelConfigurations);
    ELEM_ADD_OPT_CHILD_LIST(ContentProtection, m_contentProtections);
    ELEM_ADD_OPT_CHILD(OutputProtection, m_outputProtection);
    ELEM_ADD_OPT_CHILD_LIST(EssentialProperty, m_essentialProperties);
    ELEM_ADD_OPT_CHILD_LIST(SupplementalProperty, m_supplementalProperties);
    ELEM_ADD_OPT_CHILD_LIST(InbandEventStream, m_inbandEventStreams);
    ELEM_ADD_OPT_CHILD_LIST(Switching, m_switchings);
    ELEM_ADD_OPT_CHILD_LIST(RandomAccess, m_randomAccesses);
    ELEM_ADD_OPT_CHILD_LIST(GroupLabel, m_groupLabels);
    ELEM_ADD_OPT_CHILD_LIST(Label, m_labels);
    ELEM_ADD_OPT_CHILD_LIST(ProducerReferenceTime, m_producerReferenceTimes);
    ELEM_ADD_OPT_CHILD_LIST(ContentPopularityRate, m_contentPopularityRates);
    ELEM_ADD_OPT_CHILD_LIST(Resync, m_resyncs);

#undef ELEM_ADD_OPT_CHILD
#undef ELEM_ADD_OPT_CHILD_LIST
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
