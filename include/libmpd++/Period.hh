#ifndef _BBC_PARSE_DASH_MPD_PERIOD_HH_
#define _BBC_PARSE_DASH_MPD_PERIOD_HH_
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

#include "macros.hh"
#include "AdaptationSet.hh"
#include "BaseURL.hh"
#include "ContentProtection.hh"
#include "Descriptor.hh"
#include "EventStream.hh"
#include "Label.hh"
#include "Preselection.hh"
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

LIBPARSEMPD_NAMESPACE_BEGIN

class LIBPARSEMPD_PUBLIC_API Period {
public:
    using duration_type = std::chrono::microseconds;

    Period();
    Period(const Period &to_copy);
    Period(Period &&to_move);

    virtual ~Period() {};

    Period &operator=(const Period &to_copy);
    Period &operator=(Period &&to_move);

    bool operator==(const Period &to_compare) const;

    Period &setMPD(MPD *mpd) { m_mpd = mpd; return *this; };
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
    Period &start(const std::optional<duration_type> &start) {
        m_start = start;
        return *this;
    };

    bool hasDuration() const { return m_duration.has_value(); };
    const std::optional<duration_type> &duration() const { return m_duration; };
    Period &duration(const std::nullopt_t &) { m_duration.reset(); return *this; };
    Period &duration(const duration_type &durn) { m_duration = durn; return *this; };
    Period &duration(const std::optional<duration_type> &durn) { m_duration = durn; return *this; };

    bool bitstreamSwitching() const { return m_bitstreamSwitching; };
    Period &bitstreamSwitching(bool bitstream_switching) { m_bitstreamSwitching = bitstream_switching; return *this; };

    bool hasCalcStart() const { return m_calcStart.has_value(); };
    const std::optional<duration_type> &calcStart() const { return m_calcStart; };
    bool hasCalcDuration() const { return m_calcDuration.has_value(); };
    const std::optional<duration_type> &calcDuration() const { return m_calcDuration; };
    Period &calcPeriod(const std::optional<Period> &before, const std::optional<Period> &after = std::nullopt);

protected:
    friend class MPD;
    Period(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    MPD                           *m_mpd;

    // Period attributes (ISO 23009-1:2022 Table 4)
    std::optional<XLink>           m_xlink;
    std::optional<std::string>     m_id;
    std::optional<duration_type>   m_start;
    std::optional<duration_type>   m_duration;
    bool                           m_bitstreamSwitching;

    // Derived from attributes and sibling Periods
    std::optional<duration_type>   m_calcStart;
    std::optional<duration_type>   m_calcDuration;

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
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_PERIOD_HH_*/
