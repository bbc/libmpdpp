#ifndef _BBC_PARSE_DASH_MPD_PERIOD_HH_
#define _BBC_PARSE_DASH_MPD_PERIOD_HH_
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
#include <unordered_set>

#include "macros.hh"
#include "AdaptationSet.hh"
#include "BaseURL.hh"
#include "ContentProtection.hh"
#include "Descriptor.hh"
#include "EventStream.hh"
#include "Label.hh"
#include "Preselection.hh"
#include "SegmentAvailability.hh"
#include "SegmentBase.hh"
#include "SegmentTemplate.hh"
#include "SegmentList.hh"
#include "ServiceDescription.hh"
#include "Subset.hh"
#include "XLink.hh"

namespace xmlpp {
    class Element;
    class Node;
}

LIBMPDPP_NAMESPACE_BEGIN

class LIBMPDPP_PUBLIC_API Period {
public:
    using time_type = std::chrono::system_clock::time_point;
    using duration_type = std::chrono::microseconds;

    Period();
    Period(const Period &to_copy);
    Period(Period &&to_move);

    virtual ~Period();

    Period &operator=(const Period &to_copy);
    Period &operator=(Period &&to_move);

    bool operator==(const Period &to_compare) const;

    MPD *getMPD() { return m_mpd; };
    const MPD *getMPD() const { return m_mpd; };

    bool hasId() const { return m_id.has_value(); };
    const std::optional<std::string> &id() const { return m_id; };
    Period &id(const std::nullopt_t &) { m_id.reset(); return *this; };
    Period &id(const std::string &id) { m_id = id; return *this; };
    Period &id(std::string &&id) { m_id = std::move(id); return *this; };
    Period &id(const std::optional<std::string> &id) { m_id = id; return *this; };
    Period &id(std::optional<std::string> &&id) { m_id = std::move(id); return *this; };

    bool hasStart() const { return m_start.has_value(); };
    const std::optional<duration_type> &start() const { return m_start; };
    Period &start(const std::nullopt_t &) { m_start.reset(); return *this; };
    Period &start(const duration_type &start) { m_start = start; return *this; };
    Period &start(const std::optional<duration_type> &start) { m_start = start; return *this; };

    bool hasDuration() const { return m_duration.has_value(); };
    const std::optional<duration_type> &duration() const { return m_duration; };
    Period &duration(const std::nullopt_t &) { m_duration.reset(); return *this; };
    Period &duration(const duration_type &durn) { m_duration = durn; return *this; };
    Period &duration(const std::optional<duration_type> &durn) { m_duration = durn; return *this; };

    bool bitstreamSwitching() const { return m_bitstreamSwitching; };
    Period &bitstreamSwitching(bool bitstream_switching) { m_bitstreamSwitching = bitstream_switching; return *this; };

    //std::list<BaseURL>             m_baseURLs;
    const std::list<BaseURL> &baseURLs() const { return m_baseURLs; };
    std::list<BaseURL>::const_iterator baseURLsBegin() const { return m_baseURLs.cbegin(); };
    std::list<BaseURL>::const_iterator baseURLsEnd() const { return m_baseURLs.cend(); };
    std::list<BaseURL>::iterator baseURLsBegin() { return m_baseURLs.begin(); };
    std::list<BaseURL>::iterator baseURLsEnd() { return m_baseURLs.end(); };
    Period &baseURLAdd(const BaseURL &base_url);
    Period &baseURLAdd(BaseURL &&base_url);
    Period &baseURLRemove(const BaseURL &base_url);
    Period &baseURLRemove(const std::list<BaseURL>::const_iterator &);
    Period &baseURLRemove(const std::list<BaseURL>::iterator &);
    std::list<BaseURL> getBaseURLs() const;

    //std::optional<SegmentBase>     m_segmentBase;
    bool hasSegmentBase() const { return m_segmentBase.has_value(); };
    const std::optional<SegmentBase> &segmentBase() const { return m_segmentBase; };
    Period &segmentBase(const std::nullopt_t &) { m_segmentBase.reset(); return *this; };
    Period &segmentBase(const SegmentBase &seg_base) { m_segmentBase = seg_base; return *this; };
    Period &segmentBase(SegmentBase &&seg_base) { m_segmentBase = std::move(seg_base); return *this; };
    Period &segmentBase(const std::optional<SegmentBase> &seg_base) { m_segmentBase = seg_base; return *this; };
    Period &segmentBase(std::optional<SegmentBase> &&seg_base) { m_segmentBase = std::move(seg_base); return *this; };

    //std::optional<SegmentList>     m_segmentList;
    bool hasSegmentList() const { return m_segmentList.has_value(); };
    const std::optional<SegmentList> &segmentList() const { return m_segmentList; };
    Period &segmentList(const std::nullopt_t &) { m_segmentList.reset(); return *this; };
    Period &segmentList(const SegmentList &seg_list) { m_segmentList = seg_list; return *this; };
    Period &segmentList(SegmentList &&seg_list) { m_segmentList = std::move(seg_list); return *this; };
    Period &segmentList(const std::optional<SegmentList> &seg_list) { m_segmentList = seg_list; return *this; };
    Period &segmentList(std::optional<SegmentList> &&seg_list) { m_segmentList = std::move(seg_list); return *this; };

    //std::optional<SegmentTemplate> m_segmentTemplate;
    bool hasSegmentTemplate() const { return m_segmentTemplate.has_value(); };
    const std::optional<SegmentTemplate> &segmentTemplate() const { return m_segmentTemplate; };
    Period &segmentTemplate(const std::nullopt_t &) { m_segmentTemplate.reset(); return *this; };
    Period &segmentTemplate(const SegmentTemplate &seg_template) {m_segmentTemplate = seg_template; return *this; };
    Period &segmentTemplate(SegmentTemplate &&seg_template) {m_segmentTemplate = std::move(seg_template); return *this; };
    Period &segmentTemplate(const std::optional<SegmentTemplate> &seg_template) {m_segmentTemplate = seg_template; return *this; };
    Period &segmentTemplate(std::optional<SegmentTemplate> &&seg_template) {m_segmentTemplate = std::move(seg_template); return *this; };

    //std::optional<Descriptor>      m_assetIdentifier;
    bool hasAssetIdentifier() const { return m_assetIdentifier.has_value(); };
    const std::optional<Descriptor> &assetIdentifier() const { return m_assetIdentifier; };
    Period &assetIdentifier(const std::nullopt_t &) { m_assetIdentifier.reset(); return *this; };
    Period &assetIdentifier(const Descriptor &asset_id) { m_assetIdentifier = asset_id; return *this; };
    Period &assetIdentifier(Descriptor &&asset_id) { m_assetIdentifier = std::move(asset_id); return *this; };
    Period &assetIdentifier(const std::optional<Descriptor> &asset_id) { m_assetIdentifier = asset_id; return *this; };
    Period &assetIdentifier(std::optional<Descriptor> &&asset_id) { m_assetIdentifier = std::move(asset_id); return *this; };

    //std::list<EventStream>         m_eventStreams;
    const std::list<EventStream> &eventStreams() const { return m_eventStreams; };
    std::list<EventStream>::const_iterator eventStreamsBegin() const { return m_eventStreams.cbegin(); };
    std::list<EventStream>::const_iterator eventStreamsEnd() const { return m_eventStreams.cend(); };
    std::list<EventStream>::iterator eventStreamsBegin() { return m_eventStreams.begin(); };
    std::list<EventStream>::iterator eventStreamsEnd() { return m_eventStreams.end(); };
    Period &eventStreamAdd(const EventStream &event_stream);
    Period &eventStreamAdd(EventStream &&event_stream);
    Period &eventStreamRemove(const EventStream &event_stream);
    Period &eventStreamRemove(const std::list<EventStream>::const_iterator &);
    Period &eventStreamRemove(const std::list<EventStream>::iterator &);

    //std::list<ServiceDescription>  m_serviceDescriptions;
    const std::list<ServiceDescription> &serviceDescriptions() const { return m_serviceDescriptions; };
    std::list<ServiceDescription>::const_iterator serviceDescriptionsBegin() const { return m_serviceDescriptions.cbegin(); };
    std::list<ServiceDescription>::const_iterator serviceDescriptionsEnd() const { return m_serviceDescriptions.cend(); };
    std::list<ServiceDescription>::iterator serviceDescriptionsBegin() { return m_serviceDescriptions.begin(); };
    std::list<ServiceDescription>::iterator serviceDescriptionsEnd() { return m_serviceDescriptions.end(); };
    Period &serviceDescriptionAdd(const ServiceDescription &service_desc);
    Period &serviceDescriptionAdd(ServiceDescription &&service_desc);
    Period &serviceDescriptionRemove(const ServiceDescription &service_desc);
    Period &serviceDescriptionRemove(const std::list<ServiceDescription>::const_iterator &);
    Period &serviceDescriptionRemove(const std::list<ServiceDescription>::iterator &);

    //std::list<ContentProtection>   m_contentProtections;
    const std::list<ContentProtection> &contentProtections() const { return m_contentProtections; };
    std::list<ContentProtection>::const_iterator contentProtectionsBegin() const { return m_contentProtections.cbegin(); };
    std::list<ContentProtection>::const_iterator contentProtectionsEnd() const { return m_contentProtections.cend(); };
    std::list<ContentProtection>::iterator contentProtectionsBegin() { return m_contentProtections.begin(); };
    std::list<ContentProtection>::iterator contentProtectionsEnd() { return m_contentProtections.end(); };
    Period &contentProtectionAdd(const ContentProtection &content_prot);
    Period &contentProtectionAdd(ContentProtection &&content_prot);
    Period &contentProtectionRemove(const ContentProtection &content_prot);
    Period &contentProtectionRemove(const std::list<ContentProtection>::const_iterator &);
    Period &contentProtectionRemove(const std::list<ContentProtection>::iterator &);

    //std::list<AdaptationSet>       m_adaptationSets;
    const std::list<AdaptationSet> &adaptationSets() const { return m_adaptationSets; };
    std::list<AdaptationSet>::const_iterator adaptationSetsBegin() const { return m_adaptationSets.cbegin(); };
    std::list<AdaptationSet>::const_iterator adaptationSetsEnd() const { return m_adaptationSets.cend(); };
    std::list<AdaptationSet>::iterator adaptationSetsBegin() { return m_adaptationSets.begin(); };
    std::list<AdaptationSet>::iterator adaptationSetsEnd() { return m_adaptationSets.end(); };
    Period &adaptationSetAdd(const AdaptationSet &adapt_set);
    Period &adaptationSetAdd(AdaptationSet &&adapt_set);
    Period &adaptationSetRemove(const AdaptationSet &adapt_set);
    Period &adaptationSetRemove(const std::list<AdaptationSet>::const_iterator &);
    Period &adaptationSetRemove(const std::list<AdaptationSet>::iterator &);

    //std::list<Subset>              m_subsets;
    const std::list<Subset> &subsets() const { return m_subsets; };
    std::list<Subset>::const_iterator subsetsBegin() const { return m_subsets.cbegin(); };
    std::list<Subset>::const_iterator subsetsEnd() const { return m_subsets.cend(); };
    std::list<Subset>::iterator subsetsBegin() { return m_subsets.begin(); };
    std::list<Subset>::iterator subsetsEnd() { return m_subsets.end(); };
    Period &subsetAdd(const Subset &subset);
    Period &subsetAdd(Subset &&subset);
    Period &subsetRemove(const Subset &subset);
    Period &subsetRemove(const std::list<Subset>::const_iterator &);
    Period &subsetRemove(const std::list<Subset>::iterator &);

    //std::list<Descriptor>          m_supplementalProperties;
    const std::list<Descriptor> &supplementalProperties() const { return m_supplementalProperties; };
    std::list<Descriptor>::const_iterator supplementalPropertiesBegin() const { return m_supplementalProperties.cbegin(); };
    std::list<Descriptor>::const_iterator supplementalPropertiesEnd() const { return m_supplementalProperties.cend(); };
    std::list<Descriptor>::iterator supplementalPropertiesBegin() { return m_supplementalProperties.begin(); };
    std::list<Descriptor>::iterator supplementalPropertiesEnd() { return m_supplementalProperties.end(); };
    Period &supplementalPropertyAdd(const Descriptor &supp_prop);
    Period &supplementalPropertyAdd(Descriptor &&supp_prop);
    Period &supplementalPropertyRemove(const Descriptor &supp_prop);
    Period &supplementalPropertyRemove(const std::list<Descriptor>::const_iterator &);
    Period &supplementalPropertyRemove(const std::list<Descriptor>::iterator &);

    //std::list<AdaptationSet>       m_emptyAdaptationSets;
    const std::list<AdaptationSet> &emptyAdaptationSets() const { return m_emptyAdaptationSets; };
    std::list<AdaptationSet>::const_iterator emptyAdaptationSetsBegin() const { return m_emptyAdaptationSets.cbegin(); };
    std::list<AdaptationSet>::const_iterator emptyAdaptationSetsEnd() const { return m_emptyAdaptationSets.cend(); };
    std::list<AdaptationSet>::iterator emptyAdaptationSetsBegin() { return m_emptyAdaptationSets.begin(); };
    std::list<AdaptationSet>::iterator emptyAdaptationSetsEnd() { return m_emptyAdaptationSets.end(); };
    Period &emptyAdaptationSetAdd(const AdaptationSet &adapt_set);
    Period &emptyAdaptationSetAdd(AdaptationSet &&adapt_set);
    Period &emptyAdaptationSetRemove(const AdaptationSet &adapt_set);
    Period &emptyAdaptationSetRemove(const std::list<AdaptationSet>::const_iterator &);
    Period &emptyAdaptationSetRemove(const std::list<AdaptationSet>::iterator &);

    //std::list<Label>               m_groupLabels;
    const std::list<Label> &groupLabels() const { return m_groupLabels; };
    std::list<Label>::const_iterator groupLabelsBegin() const { return m_groupLabels.cbegin(); };
    std::list<Label>::const_iterator groupLabelsEnd() const { return m_groupLabels.cend(); };
    std::list<Label>::iterator groupLabelsBegin() { return m_groupLabels.begin(); };
    std::list<Label>::iterator groupLabelsEnd() { return m_groupLabels.end(); };
    Period &groupLabelAdd(const Label &label);
    Period &groupLabelAdd(Label &&label);
    Period &groupLabelRemove(const Label &label);
    Period &groupLabelRemove(const std::list<Label>::const_iterator &);
    Period &groupLabelRemove(const std::list<Label>::iterator &);

    //std::list<Preselection>        m_preselections;
    const std::list<Preselection> &preselections() const { return m_preselections; };
    std::list<Preselection>::const_iterator preselectionsBegin() const { return m_preselections.cbegin(); };
    std::list<Preselection>::const_iterator preselectionsEnd() const { return m_preselections.cend(); };
    std::list<Preselection>::iterator preselectionsBegin() { return m_preselections.begin(); };
    std::list<Preselection>::iterator preselectionsEnd() { return m_preselections.end(); };
    Period &preselectionAdd(const Preselection &preselection);
    Period &preselectionAdd(Preselection &&preselection);
    Period &preselectionRemove(const Preselection &preselection);
    Period &preselectionRemove(const std::list<Preselection>::const_iterator &);
    Period &preselectionRemove(const std::list<Preselection>::iterator &);

    void selectAllRepresentations();
    void deselectAllRepresentations();

    std::unordered_set<const Representation*> selectedRepresentations() const;

    std::list<SegmentAvailability> selectedSegmentAvailability(const time_type &query_time = std::chrono::system_clock::now()) const;
    std::list<SegmentAvailability> selectedInitializationSegments() const;

    Period &setMPD(MPD *mpd) { m_mpd = mpd; return *this; };

    const std::optional<duration_type> &calcStart() const;
    const std::optional<duration_type> &calcDuration() const;

protected:
    friend class MPD;
    friend class AdaptationSet;
    Period(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
    std::string getMediaURL(const SegmentTemplate::Variables&) const;
    std::string getInitializationURL(const SegmentTemplate::Variables&) const;
    SegmentAvailability getMediaAvailability(const SegmentTemplate::Variables&) const;
    SegmentAvailability getInitialisationAvailability(const SegmentTemplate::Variables &vars) const;
    Period &setPreviousSibling(Period *sibling) { m_previousSibling = sibling; cacheCalcClear(); sibling->cacheCalcClear(); return *this; };
    Period &setNextSibling(Period *sibling) { m_nextSibling = sibling; cacheCalcClear(); sibling->cacheCalcClear(); return *this; };
    time_type getPeriodStartTime() const;
    const MultipleSegmentBase &getMultiSegmentBase() const;

private:
    void cacheCalcTimes() const;
    void cacheCalcClear() const;

    MPD                           *m_mpd;
    Period                        *m_previousSibling;
    Period                        *m_nextSibling;

    // Period attributes (ISO 23009-1:2022 Table 4)
    std::optional<XLink>           m_xlink;
    std::optional<std::string>     m_id;
    std::optional<duration_type>   m_start;
    std::optional<duration_type>   m_duration;
    bool                           m_bitstreamSwitching;

    // Period child elements (ISO 23009-1:2022 Table 4)
    std::list<BaseURL>             m_baseURLs;
    std::optional<SegmentBase>     m_segmentBase;
    std::optional<SegmentList>     m_segmentList;
    std::optional<SegmentTemplate> m_segmentTemplate;
    std::optional<Descriptor>      m_assetIdentifier;
    std::list<EventStream>         m_eventStreams;
    std::list<ServiceDescription>  m_serviceDescriptions;
    std::list<ContentProtection>   m_contentProtections;
    std::list<AdaptationSet>       m_adaptationSets;
    std::list<Subset>              m_subsets;
    std::list<Descriptor>          m_supplementalProperties;
    std::list<AdaptationSet>       m_emptyAdaptationSets;
    std::list<Label>               m_groupLabels;
    std::list<Preselection>        m_preselections;

    struct Cache {
        Cache() :calcStart(), calcDuration() {};
        Cache(const Cache &other) :calcStart(other.calcStart), calcDuration(other.calcDuration) {};
        Cache(Cache &&other) :calcStart(std::move(other.calcStart)), calcDuration(std::move(other.calcDuration)) {};
        Cache &operator=(const Cache &other) { calcStart = other.calcStart; calcDuration = other.calcDuration; return *this; };
        Cache &operator=(Cache &&other) { calcStart = std::move(other.calcStart); calcDuration = std::move(other.calcDuration); return *this; };
        ~Cache() {};
        std::optional<Period::duration_type> calcStart;
        std::optional<Period::duration_type> calcDuration;
    } *m_cache;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_PERIOD_HH_*/
