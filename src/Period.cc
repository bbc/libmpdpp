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

#include "libmpd++/Period.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

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
    if (m_id.has_value() != to_compare.m_id.has_value()) return false;
    if (m_id.has_value() && m_id.value() != to_compare.m_id.value()) return false;

    if (m_start.has_value() != to_compare.m_start.has_value()) return false;
    if (m_start.has_value() && m_start.value() != to_compare.m_start.value()) return false;

    if (m_duration.has_value() != to_compare.m_duration.has_value()) return false;
    if (m_duration.has_value() && m_duration.value() != to_compare.m_duration.value()) return false;

    if (m_bitstreamSwitching != to_compare.m_bitstreamSwitching) return false;

    return false;
    //return true;
}

Period::Period(xmlpp::Node&)
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

void Period::setXMLElement(xmlpp::Element&) const
{
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
