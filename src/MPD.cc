/*****************************************************************************
 * DASH MPD parsing library in C++: MPD class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */

#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>

#include <libxml++/libxml++.h>
#include <glibmm/ustring.h>

#include "libmpd++/macros.hh"
#include "libmpd++/exceptions.hh"
#include "libmpd++/BaseURL.hh"
#include "libmpd++/ContentProtection.hh"
#include "libmpd++/Descriptor.hh"
#include "libmpd++/InitializationSet.hh"
#include "libmpd++/LeapSecondInformation.hh"
#include "libmpd++/Metrics.hh"
#include "libmpd++/PatchLocation.hh"
#include "libmpd++/Period.hh"
#include "libmpd++/ProgramInformation.hh"
#include "libmpd++/SegmentAvailability.hh"
#include "libmpd++/ServiceDescription.hh"
#include "libmpd++/UIntVWithID.hh"
#include "libmpd++/URI.hh"

#include "constants.hh"
#include "conversions.hh"

#include "libmpd++/MPD.hh"

static const int g_MPD_formatting_xindex = std::ios_base::xalloc();

using namespace std::literals::chrono_literals;
LIBMPDPP_NAMESPACE_BEGIN

static MPD::time_type str_to_time_point(const std::string &str);
static std::list<URI> str_to_uri_list(const std::string &str, char sep = ',');

namespace {
class MPDFormattingOptions {
public:
    MPDFormattingOptions() :m_compact(false) {};
    ~MPDFormattingOptions() {};

    bool compact() const { return m_compact; };
    MPDFormattingOptions &compact(bool is_compact_output) {
        m_compact = is_compact_output;
        return *this;
    };

private:
    bool m_compact;
};
}

static MPDFormattingOptions &get_mpd_formatting(std::ios_base &ios);

MPD::MPD(const duration_type &minimum_buffer_time, const URI &profile, const Period &period, PresentationType presentation_type)
    :m_id()
    ,m_profiles({profile})
    ,m_type(presentation_type)
    ,m_availabilityStartTime()
    ,m_availabilityEndTime()
    ,m_publishTime()
    ,m_mediaPresentationDuration()
    ,m_minimumUpdatePeriod()
    ,m_minBufferTime(minimum_buffer_time)
    ,m_timeShiftBufferDepth()
    ,m_suggestedPresentationDelay()
    ,m_maxSegmentDuration()
    ,m_maxSubsegmentDuration()
    ,m_programInformations()
    ,m_baseURLs()
    ,m_locations()
    ,m_patchLocations()
    ,m_serviceDescriptions()
    ,m_initializationSets()
    ,m_initializationGroups()
    ,m_initializationPresentations()
    ,m_contentProtections()
    ,m_periods({period})
    ,m_metrics()
    ,m_essentialProperties()
    ,m_supplementaryProperties()
    ,m_utcTimings()
    ,m_leapSecondInformation()
    ,m_mpdURL()
    ,m_cache(new Cache)
{
}

MPD::MPD(const duration_type &minimum_buffer_time, const URI &profile, Period &&period, PresentationType presentation_type)
    :m_id()
    ,m_profiles({profile})
    ,m_type(presentation_type)
    ,m_availabilityStartTime()
    ,m_availabilityEndTime()
    ,m_publishTime()
    ,m_mediaPresentationDuration()
    ,m_minimumUpdatePeriod()
    ,m_minBufferTime(minimum_buffer_time)
    ,m_timeShiftBufferDepth()
    ,m_suggestedPresentationDelay()
    ,m_maxSegmentDuration()
    ,m_maxSubsegmentDuration()
    ,m_programInformations()
    ,m_baseURLs()
    ,m_locations()
    ,m_patchLocations()
    ,m_serviceDescriptions()
    ,m_initializationSets()
    ,m_initializationGroups()
    ,m_initializationPresentations()
    ,m_contentProtections()
    ,m_periods()
    ,m_metrics()
    ,m_essentialProperties()
    ,m_supplementaryProperties()
    ,m_utcTimings()
    ,m_leapSecondInformation()
    ,m_mpdURL()
    ,m_cache(new Cache)
{
    m_periods.push_back(std::move(period));
}

MPD::MPD(std::istream &input_stream, const std::optional<URI> &mpd_location)
    :m_id()
    ,m_profiles()
    ,m_type(MPD::STATIC)
    ,m_availabilityStartTime()
    ,m_availabilityEndTime()
    ,m_publishTime()
    ,m_mediaPresentationDuration()
    ,m_minimumUpdatePeriod()
    ,m_minBufferTime()
    ,m_timeShiftBufferDepth()
    ,m_suggestedPresentationDelay()
    ,m_maxSegmentDuration()
    ,m_maxSubsegmentDuration()
    ,m_programInformations()
    ,m_baseURLs()
    ,m_locations()
    ,m_patchLocations()
    ,m_serviceDescriptions()
    ,m_initializationSets()
    ,m_initializationGroups()
    ,m_initializationPresentations()
    ,m_contentProtections()
    ,m_periods()
    ,m_metrics()
    ,m_essentialProperties()
    ,m_supplementaryProperties()
    ,m_utcTimings()
    ,m_leapSecondInformation()
    ,m_mpdURL(mpd_location)
    ,m_cache(new Cache)
{
    xmlpp::DomParser dom_parser;
    dom_parser.parse_stream(input_stream);
    if (dom_parser) {
        extractMPD(dom_parser.get_document());
    }
}

MPD::MPD(const std::vector<char> &mpd_xml, const std::optional<URI> &mpd_location)
    :m_id()
    ,m_profiles()
    ,m_type(MPD::STATIC)
    ,m_availabilityStartTime()
    ,m_availabilityEndTime()
    ,m_publishTime()
    ,m_mediaPresentationDuration()
    ,m_minimumUpdatePeriod()
    ,m_minBufferTime()
    ,m_timeShiftBufferDepth()
    ,m_suggestedPresentationDelay()
    ,m_maxSegmentDuration()
    ,m_maxSubsegmentDuration()
    ,m_programInformations()
    ,m_baseURLs()
    ,m_locations()
    ,m_patchLocations()
    ,m_serviceDescriptions()
    ,m_initializationSets()
    ,m_initializationGroups()
    ,m_initializationPresentations()
    ,m_contentProtections()
    ,m_periods()
    ,m_metrics()
    ,m_essentialProperties()
    ,m_supplementaryProperties()
    ,m_utcTimings()
    ,m_leapSecondInformation()
    ,m_mpdURL(mpd_location)
    ,m_cache(new Cache)
{
    xmlpp::DomParser dom_parser;
    dom_parser.parse_memory(Glib::ustring(mpd_xml.data(), mpd_xml.size()));
    if (dom_parser) {
        extractMPD(dom_parser.get_document());
    }
}

MPD::MPD(const std::vector<unsigned char> &mpd_xml, const std::optional<URI> &mpd_location)
    :m_id()
    ,m_profiles()
    ,m_type(MPD::STATIC)
    ,m_availabilityStartTime()
    ,m_availabilityEndTime()
    ,m_publishTime()
    ,m_mediaPresentationDuration()
    ,m_minimumUpdatePeriod()
    ,m_minBufferTime()
    ,m_timeShiftBufferDepth()
    ,m_suggestedPresentationDelay()
    ,m_maxSegmentDuration()
    ,m_maxSubsegmentDuration()
    ,m_programInformations()
    ,m_baseURLs()
    ,m_locations()
    ,m_patchLocations()
    ,m_serviceDescriptions()
    ,m_initializationSets()
    ,m_initializationGroups()
    ,m_initializationPresentations()
    ,m_contentProtections()
    ,m_periods()
    ,m_metrics()
    ,m_essentialProperties()
    ,m_supplementaryProperties()
    ,m_utcTimings()
    ,m_leapSecondInformation()
    ,m_mpdURL(mpd_location)
    ,m_cache(new Cache)
{
    xmlpp::DomParser dom_parser;
    dom_parser.parse_memory(Glib::ustring(reinterpret_cast<const char*>(mpd_xml.data()), mpd_xml.size()));
    if (dom_parser) {
        extractMPD(dom_parser.get_document());
    }
}

MPD::MPD(const std::string &filename, const std::optional<URI> &mpd_location)
    :m_id()
    ,m_profiles()
    ,m_type(MPD::STATIC)
    ,m_availabilityStartTime()
    ,m_availabilityEndTime()
    ,m_publishTime()
    ,m_mediaPresentationDuration()
    ,m_minimumUpdatePeriod()
    ,m_minBufferTime()
    ,m_timeShiftBufferDepth()
    ,m_suggestedPresentationDelay()
    ,m_maxSegmentDuration()
    ,m_maxSubsegmentDuration()
    ,m_programInformations()
    ,m_baseURLs()
    ,m_locations()
    ,m_patchLocations()
    ,m_serviceDescriptions()
    ,m_initializationSets()
    ,m_initializationGroups()
    ,m_initializationPresentations()
    ,m_contentProtections()
    ,m_periods()
    ,m_metrics()
    ,m_essentialProperties()
    ,m_supplementaryProperties()
    ,m_utcTimings()
    ,m_leapSecondInformation()
    ,m_mpdURL(mpd_location)
    ,m_cache(new Cache)
{
    xmlpp::DomParser dom_parser;
    dom_parser.parse_file(filename);
    if (dom_parser) {
        extractMPD(dom_parser.get_document());
    }
}

MPD::MPD(const MPD &other)
    :m_id(other.m_id)
    ,m_profiles(other.m_profiles)
    ,m_type(other.m_type)
    ,m_availabilityStartTime(other.m_availabilityStartTime)
    ,m_availabilityEndTime(other.m_availabilityEndTime)
    ,m_publishTime(other.m_publishTime)
    ,m_mediaPresentationDuration(other.m_mediaPresentationDuration)
    ,m_minimumUpdatePeriod(other.m_minimumUpdatePeriod)
    ,m_minBufferTime(other.m_minBufferTime)
    ,m_timeShiftBufferDepth(other.m_timeShiftBufferDepth)
    ,m_suggestedPresentationDelay(other.m_suggestedPresentationDelay)
    ,m_maxSegmentDuration(other.m_maxSegmentDuration)
    ,m_maxSubsegmentDuration(other.m_maxSubsegmentDuration)
    ,m_programInformations(other.m_programInformations)
    ,m_baseURLs(other.m_baseURLs)
    ,m_locations(other.m_locations)
    ,m_patchLocations(other.m_patchLocations)
    ,m_serviceDescriptions(other.m_serviceDescriptions)
    ,m_initializationSets(other.m_initializationSets)
    ,m_initializationGroups(other.m_initializationGroups)
    ,m_initializationPresentations(other.m_initializationPresentations)
    ,m_contentProtections(other.m_contentProtections)
    ,m_periods(other.m_periods)
    ,m_metrics(other.m_metrics)
    ,m_essentialProperties(other.m_essentialProperties)
    ,m_supplementaryProperties(other.m_supplementaryProperties)
    ,m_utcTimings(other.m_utcTimings)
    ,m_leapSecondInformation(other.m_leapSecondInformation)
    ,m_mpdURL(other.m_mpdURL)
    ,m_cache(new Cache)
{
    m_cache->haveUtcTimingOffsetFromSystemClock = other.m_cache->haveUtcTimingOffsetFromSystemClock;
    m_cache->utcTimingOffsetFromSystemClock = other.m_cache->utcTimingOffsetFromSystemClock;
    Period *prev = nullptr;
    for (auto &period : m_periods) {
        if (prev) {
            period.setPreviousSibling(prev);
            prev->setNextSibling(&period);
        }
        prev = &period;
    }
}

MPD::MPD(MPD &&other)
    :m_id(std::move(other.m_id))
    ,m_profiles(std::move(other.m_profiles))
    ,m_type(std::move(other.m_type))
    ,m_availabilityStartTime(std::move(other.m_availabilityStartTime))
    ,m_availabilityEndTime(std::move(other.m_availabilityEndTime))
    ,m_publishTime(std::move(other.m_publishTime))
    ,m_mediaPresentationDuration(std::move(other.m_mediaPresentationDuration))
    ,m_minimumUpdatePeriod(std::move(other.m_minimumUpdatePeriod))
    ,m_minBufferTime(std::move(other.m_minBufferTime))
    ,m_timeShiftBufferDepth(std::move(other.m_timeShiftBufferDepth))
    ,m_suggestedPresentationDelay(std::move(other.m_suggestedPresentationDelay))
    ,m_maxSegmentDuration(std::move(other.m_maxSegmentDuration))
    ,m_maxSubsegmentDuration(std::move(other.m_maxSubsegmentDuration))
    ,m_programInformations(std::move(other.m_programInformations))
    ,m_baseURLs(std::move(other.m_baseURLs))
    ,m_locations(std::move(other.m_locations))
    ,m_patchLocations(std::move(other.m_patchLocations))
    ,m_serviceDescriptions(std::move(other.m_serviceDescriptions))
    ,m_initializationSets(std::move(other.m_initializationSets))
    ,m_initializationGroups(std::move(other.m_initializationGroups))
    ,m_initializationPresentations(std::move(other.m_initializationPresentations))
    ,m_contentProtections(std::move(other.m_contentProtections))
    ,m_periods(std::move(other.m_periods))
    ,m_metrics(std::move(other.m_metrics))
    ,m_essentialProperties(std::move(other.m_essentialProperties))
    ,m_supplementaryProperties(std::move(other.m_supplementaryProperties))
    ,m_utcTimings(std::move(other.m_utcTimings))
    ,m_leapSecondInformation(std::move(other.m_leapSecondInformation))
    ,m_mpdURL(std::move(other.m_mpdURL))
    ,m_cache(new Cache)
{
    m_cache->haveUtcTimingOffsetFromSystemClock = other.m_cache->haveUtcTimingOffsetFromSystemClock;
    m_cache->utcTimingOffsetFromSystemClock = std::move(other.m_cache->utcTimingOffsetFromSystemClock);
    Period *prev = nullptr;
    for (auto &period : m_periods) {
        if (prev) {
            period.setPreviousSibling(prev);
            prev->setNextSibling(&period);
        }
        prev = &period;
    }
}

MPD::~MPD()
{
    delete m_cache;
}

MPD &MPD::operator=(const MPD &other)
{
    m_id = other.m_id;
    m_profiles = other.m_profiles;
    m_type = other.m_type;
    m_availabilityStartTime = other.m_availabilityStartTime;
    m_availabilityEndTime = other.m_availabilityEndTime;
    m_publishTime = other.m_publishTime;
    m_mediaPresentationDuration = other.m_mediaPresentationDuration;
    m_minimumUpdatePeriod = other.m_minimumUpdatePeriod;
    m_minBufferTime = other.m_minBufferTime;
    m_timeShiftBufferDepth = other.m_timeShiftBufferDepth;
    m_suggestedPresentationDelay = other.m_suggestedPresentationDelay;
    m_maxSegmentDuration = other.m_maxSegmentDuration;
    m_maxSubsegmentDuration = other.m_maxSubsegmentDuration;
    m_programInformations = other.m_programInformations;
    m_baseURLs = other.m_baseURLs;
    m_locations = other.m_locations;
    m_patchLocations = other.m_patchLocations;
    m_serviceDescriptions = other.m_serviceDescriptions;
    m_initializationSets = other.m_initializationSets;
    m_initializationGroups = other.m_initializationGroups;
    m_initializationPresentations = other.m_initializationPresentations;
    m_contentProtections = other.m_contentProtections;
    m_periods = other.m_periods;
    Period *prev = nullptr;
    for (auto &period : m_periods) {
        period.setMPD(this);
        if (prev) {
            period.setPreviousSibling(prev);
            prev->setNextSibling(&period);
        }
        prev = &period;
    }
    m_metrics = other.m_metrics;
    m_essentialProperties = other.m_essentialProperties;
    m_supplementaryProperties = other.m_supplementaryProperties;
    m_utcTimings = other.m_utcTimings;
    m_leapSecondInformation = other.m_leapSecondInformation;

    m_cache->haveUtcTimingOffsetFromSystemClock = other.m_cache->haveUtcTimingOffsetFromSystemClock;
    m_cache->utcTimingOffsetFromSystemClock = other.m_cache->utcTimingOffsetFromSystemClock;

    return *this;
}

MPD &MPD::operator=(MPD &&other)
{
    m_id = std::move(other.m_id);
    m_profiles = std::move(other.m_profiles);
    m_type = std::move(other.m_type);
    m_availabilityStartTime = std::move(other.m_availabilityStartTime);
    m_availabilityEndTime = std::move(other.m_availabilityEndTime);
    m_publishTime = std::move(other.m_publishTime);
    m_mediaPresentationDuration = std::move(other.m_mediaPresentationDuration);
    m_minimumUpdatePeriod = std::move(other.m_minimumUpdatePeriod);
    m_minBufferTime = std::move(other.m_minBufferTime);
    m_timeShiftBufferDepth = std::move(other.m_timeShiftBufferDepth);
    m_suggestedPresentationDelay = std::move(other.m_suggestedPresentationDelay);
    m_maxSegmentDuration = std::move(other.m_maxSegmentDuration);
    m_maxSubsegmentDuration = std::move(other.m_maxSubsegmentDuration);
    m_programInformations = std::move(other.m_programInformations);
    m_baseURLs = std::move(other.m_baseURLs);
    m_locations = std::move(other.m_locations);
    m_patchLocations = std::move(other.m_patchLocations);
    m_serviceDescriptions = std::move(other.m_serviceDescriptions);
    m_initializationSets = std::move(other.m_initializationSets);
    m_initializationGroups = std::move(other.m_initializationGroups);
    m_initializationPresentations = std::move(other.m_initializationPresentations);
    m_contentProtections = std::move(other.m_contentProtections);
    m_periods = std::move(other.m_periods);
    Period *prev = nullptr;
    for (auto &period : m_periods) {
        period.setMPD(this);
        if (prev) {
            period.setPreviousSibling(prev);
            prev->setNextSibling(&period);
        }
        prev = &period;
    }
    m_metrics = std::move(other.m_metrics);
    m_essentialProperties = std::move(other.m_essentialProperties);
    m_supplementaryProperties = std::move(other.m_supplementaryProperties);
    m_utcTimings = std::move(other.m_utcTimings);
    m_leapSecondInformation = std::move(other.m_leapSecondInformation);

    m_cache->haveUtcTimingOffsetFromSystemClock = other.m_cache->haveUtcTimingOffsetFromSystemClock;
    m_cache->utcTimingOffsetFromSystemClock = std::move(other.m_cache->utcTimingOffsetFromSystemClock);

    return *this;
}

bool MPD::isLive() const
{
    if (m_type != DYNAMIC) return false;                      // Live is "dynamic"
    if (!m_availabilityStartTime.has_value()) return false;   // Live has an availability start time
    // Live matches one of the live profiles
    static const std::vector<URI> live_profiles = {"urn:mpeg:dash:profile:isoff-live:2011", "urn:dvb:dash:profile:dvb-dash:isoff-ext-live:2014"};
    for (const auto &profile : live_profiles) {
        if (find(m_profiles.begin(), m_profiles.end(), profile) != m_profiles.end()) return true;
    }
    return false;
}

std::string MPD::asXML(bool compact_xml) const
{
    xmlpp::Document doc;
    xmlpp::Element *docroot = doc.create_root_node("MPD", MPD_NS);

    if (m_id) {
        docroot->set_attribute("id", m_id.value());
    }
    {
        std::ostringstream oss;
        const char *sep = "";
        for (const auto &u : m_profiles) {
             oss << sep << u;
             sep = ",";
        }
        docroot->set_attribute("profiles", oss.str());
    }
    if (m_type != MPD::STATIC) {
        docroot->set_attribute("type", "dynamic");
    }
    if (m_availabilityStartTime) {
        docroot->set_attribute("availabilityStartTime", std::format(ISO8601_DATE_TIME_FORMAT, std::chrono::round<std::chrono::milliseconds>(m_availabilityStartTime.value())));
    }
    if (m_availabilityEndTime) {
        docroot->set_attribute("availabilityEndTime", std::format(ISO8601_DATE_TIME_FORMAT, std::chrono::round<std::chrono::milliseconds>(m_availabilityEndTime.value())));
    }
    if (m_publishTime) {
        docroot->set_attribute("publishTime", std::format(ISO8601_DATE_TIME_FORMAT, std::chrono::round<std::chrono::milliseconds>(m_publishTime.value())));
    }
    if (m_mediaPresentationDuration) {
        docroot->set_attribute("mediaPresentationDuration", format_duration(std::chrono::round<std::chrono::milliseconds>(m_mediaPresentationDuration.value())));
    }
    if (m_minimumUpdatePeriod) {
        docroot->set_attribute("minimumUpdatePeriod", format_duration(std::chrono::round<std::chrono::milliseconds>(m_minimumUpdatePeriod.value())));
    }
    docroot->set_attribute("minBufferTime", format_duration(std::chrono::round<std::chrono::milliseconds>(m_minBufferTime)));
    if (m_timeShiftBufferDepth) {
        docroot->set_attribute("timeShiftBufferDepth", format_duration(std::chrono::round<std::chrono::milliseconds>(m_timeShiftBufferDepth.value())));
    }
    if (m_suggestedPresentationDelay) {
        docroot->set_attribute("suggestedPresentationDelay", format_duration(std::chrono::round<std::chrono::milliseconds>(m_suggestedPresentationDelay.value())));
    }
    if (m_maxSegmentDuration) {
        docroot->set_attribute("maxSegmentDuration", format_duration(std::chrono::round<std::chrono::milliseconds>(m_maxSegmentDuration.value())));
    }
    if (m_maxSubsegmentDuration) {
        docroot->set_attribute("maxSubsegmentDuration", format_duration(std::chrono::round<std::chrono::milliseconds>(m_maxSubsegmentDuration.value())));
    }

    // Child elements
    for (const auto &pi : m_programInformations) {
        xmlpp::Element *elem = docroot->add_child_element("ProgramInformation");
        pi.setXMLElement(*elem);
    }
    for (const auto &url : m_baseURLs) {
        xmlpp::Element *elem = docroot->add_child_element("BaseURL");
        url.setXMLElement(*elem);
    }
    for (const auto &url : m_locations) {
        xmlpp::Element *elem = docroot->add_child_element("Location");
        elem->add_child_text(std::string(url));
    }
    for (const auto &pl : m_patchLocations) {
        xmlpp::Element *elem = docroot->add_child_element("PatchLocation");
        pl.setXMLElement(*elem);
    }
    for (const auto &sd : m_serviceDescriptions) {
        xmlpp::Element *elem = docroot->add_child_element("ServiceDescription");
        sd.setXMLElement(*elem);
    }
    for (const auto &is : m_initializationSets) {
        xmlpp::Element *elem = docroot->add_child_element("InitializationSet");
        is.setXMLElement(*elem);
    }
    for (const auto &ig : m_initializationGroups) {
        xmlpp::Element *elem = docroot->add_child_element("InitializationGroup");
        ig.setXMLElement(*elem);
    }
    for (const auto &ip : m_initializationPresentations) {
        xmlpp::Element *elem = docroot->add_child_element("InitializationPresentation");
        ip.setXMLElement(*elem);
    }
    for (const auto &cp : m_contentProtections) {
        xmlpp::Element *elem = docroot->add_child_element("ContentProtection");
        cp.setXMLElement(*elem);
    }
    for (const auto &period : m_periods) {
        xmlpp::Element *elem = docroot->add_child_element("Period");
        period.setXMLElement(*elem);
    }
    for (const auto &metric : m_metrics) {
        xmlpp::Element *elem = docroot->add_child_element("Metrics");
        metric.setXMLElement(*elem);
    }
    for (const auto &ep : m_essentialProperties) {
        xmlpp::Element *elem = docroot->add_child_element("EssentialProperty");
        ep.setXMLElement(*elem);
    }
    for (const auto &sp : m_supplementaryProperties) {
        xmlpp::Element *elem = docroot->add_child_element("SupplementaryProperty");
        sp.setXMLElement(*elem);
    }
    for (const auto &timing : m_utcTimings) {
        xmlpp::Element *elem = docroot->add_child_element("UTCTiming");
        timing.setXMLElement(*elem);
    }
    if (m_leapSecondInformation.has_value()) {
        xmlpp::Element *elem = docroot->add_child_element("LeapSecondInformation");
        m_leapSecondInformation.value().setXMLElement(*elem);
    }

    std::ostringstream oss;

    if (compact_xml) {
        doc.write_to_stream(oss);
    } else {
        doc.write_to_stream_formatted(oss);
    }

    return oss.str();
}

std::ostream &MPD::compact(std::ostream &os)
{
    auto &options = get_mpd_formatting(os);
    options.compact(true);
    return os;
}

std::ostream &MPD::pretty(std::ostream &os)
{
    auto &options = get_mpd_formatting(os);
    options.compact(false);
    return os;
}

const std::string &MPD::id(const std::string &default_val) const
{
    if (!m_id.has_value()) return default_val;
    return m_id.value();
}

bool MPD::profilesContain(const URI &uri) const
{
    return std::find(m_profiles.cbegin(), m_profiles.cend(), uri) != m_profiles.cend();
}

MPD &MPD::profileAdd(const URI &uri)
{
    m_profiles.push_back(uri);
    return *this;
}

MPD &MPD::profileAdd(URI &&uri)
{
    m_profiles.push_back(std::move(uri));
    return *this;
}

MPD &MPD::profileRemove(const std::list<URI>::const_iterator &it)
{
    if (m_profiles.size() == 1) {
        throw InvalidMPD("Removing the last profile will make the MPD invalid");
    }
    m_profiles.erase(it);
    return *this;
}

MPD &MPD::profileRemove(const URI &uri)
{
    auto it = std::find(m_profiles.begin(), m_profiles.end(), uri);
    if (it != m_profiles.end()) {
        if (m_profiles.size() == 1) {
            throw InvalidMPD("Removing the last profile will make the MPD invalid");
        }
        m_profiles.erase(it);
    }
    return *this;
}

const MPD::time_type &MPD::availabilityStartTime(const MPD::time_type &default_val) const
{
    if (!m_availabilityStartTime.has_value()) return default_val;
    return m_availabilityStartTime.value();
}

const MPD::time_type &MPD::availabilityEndTime(const MPD::time_type &default_val) const
{
    if (!m_availabilityEndTime.has_value()) return default_val;
    return m_availabilityEndTime.value();
}

const MPD::time_type &MPD::publishTime(const MPD::time_type &default_val) const
{
    if (!m_publishTime.has_value()) return default_val;
    return m_publishTime.value();
}

const MPD::duration_type &MPD::mediaPresentationDuration(const MPD::duration_type &default_val) const
{
    if (!m_mediaPresentationDuration.has_value()) return default_val;
    return m_mediaPresentationDuration.value();
}

const MPD::duration_type &MPD::minimumUpdatePeriod(const MPD::duration_type &default_val) const
{
    if (!m_minimumUpdatePeriod.has_value()) return default_val;
    return m_minimumUpdatePeriod.value();
}

const MPD::duration_type &MPD::timeShiftBufferDepth(const MPD::duration_type &default_val) const
{
    if (!m_timeShiftBufferDepth.has_value()) return default_val;
    return m_timeShiftBufferDepth.value();
}

const MPD::duration_type &MPD::suggestedPresentationDelay(const MPD::duration_type &default_val) const
{
    if (!m_suggestedPresentationDelay.has_value()) return default_val;
    return m_suggestedPresentationDelay.value();
}

const MPD::duration_type &MPD::maxSegmentDuration(const MPD::duration_type &default_val) const
{
    if (!m_maxSegmentDuration.has_value()) return default_val;
    return m_maxSegmentDuration.value();
}

const MPD::duration_type &MPD::maxSubsegmentDuration(const MPD::duration_type &default_val) const
{
    if (!m_maxSubsegmentDuration.has_value()) return default_val;
    return m_maxSubsegmentDuration.value();
}

MPD &MPD::programInformationAdd(const ProgramInformation &prog_info)
{
    m_programInformations.push_back(prog_info);
    return *this;
}

MPD &MPD::programInformationAdd(ProgramInformation &&prog_info)
{
    m_programInformations.push_back(std::move(prog_info));
    return *this;
}

MPD &MPD::programInformationRemove(const ProgramInformation &prog_info)
{
    m_programInformations.remove(prog_info);
    return *this;
}

MPD &MPD::programInformationRemove(const std::list<ProgramInformation>::const_iterator &it)
{
    m_programInformations.erase(it);
    return *this;
}

MPD &MPD::programInformationRemove(const std::list<ProgramInformation>::iterator &it)
{
    m_programInformations.erase(it);
    return *this;
}

MPD &MPD::baseURLAdd(const BaseURL &base_url)
{
    m_baseURLs.push_back(base_url);
    return *this;
}

MPD &MPD::baseURLAdd(BaseURL &&base_url)
{
    m_baseURLs.push_back(std::move(base_url));
    return *this;
}

MPD &MPD::baseURLRemove(const BaseURL &base_url)
{
    m_baseURLs.remove(base_url);
    return *this;
}

MPD &MPD::baseURLRemove(const std::list<BaseURL>::const_iterator &it)
{
    m_baseURLs.erase(it);
    return *this;
}

MPD &MPD::baseURLRemove(const std::list<BaseURL>::iterator &it)
{
    m_baseURLs.erase(it);
    return *this;
}

std::list<BaseURL> MPD::getBaseURLs() const
{
    std::list<BaseURL> ret;
    std::list<BaseURL> acquisition_urls;

    if (m_mpdURL) {
        acquisition_urls.push_back(BaseURL(m_mpdURL.value()));
    }

    if (m_baseURLs.size() == 0) {
        // No BaseURL elements, just use the acquisition URL instead as a plain BaseURL
        ret = std::move(acquisition_urls);
    } else {
        for (const auto &base_url : m_baseURLs) {
            if (base_url.url().isAbsoluteURL()) {
                ret.push_back(base_url);
            } else {
                ret.push_back(base_url.resolveURL(acquisition_urls));
            }
        }
    }
    return ret;
}

MPD &MPD::locationAdd(const URI &location)
{
    m_locations.push_back(location);
    return *this;
}

MPD &MPD::locationAdd(URI &&location)
{
    m_locations.push_back(std::move(location));
    return *this;
}

MPD &MPD::locationRemove(const URI &location)
{
    m_locations.remove(location);
    return *this;
}

MPD &MPD::locationRemove(const std::list<URI>::const_iterator &it)
{
    m_locations.erase(it);
    return *this;
}

MPD &MPD::locationRemove(const std::list<URI>::iterator &it)
{
    m_locations.erase(it);
    return *this;
}

MPD &MPD::patchLocationAdd(const PatchLocation &patch_location)
{
    m_patchLocations.push_back(patch_location);
    return *this;
}

MPD &MPD::patchLocationAdd(PatchLocation &&patch_location)
{
    m_patchLocations.push_back(std::move(patch_location));
    return *this;
}

MPD &MPD::patchLocationRemove(const PatchLocation &patch_location)
{
    m_patchLocations.remove(patch_location);
    return *this;
}

MPD &MPD::patchLocationRemove(const std::list<PatchLocation>::const_iterator &it)
{
    m_patchLocations.erase(it);
    return *this;
}

MPD &MPD::patchLocationRemove(const std::list<PatchLocation>::iterator &it)
{
    m_patchLocations.erase(it);
    return *this;
}

MPD &MPD::serviceDescriptionAdd(const ServiceDescription &service_desc)
{
    m_serviceDescriptions.push_back(service_desc);
    return *this;
}

MPD &MPD::serviceDescriptionAdd(ServiceDescription &&service_desc)
{
    m_serviceDescriptions.push_back(std::move(service_desc));
    return *this;
}

MPD &MPD::serviceDescriptionRemove(const ServiceDescription &service_desc)
{
    m_serviceDescriptions.remove(service_desc);
    return *this;
}

MPD &MPD::serviceDescriptionRemove(const std::list<ServiceDescription>::const_iterator &it)
{
    m_serviceDescriptions.erase(it);
    return *this;
}

MPD &MPD::serviceDescriptionRemove(const std::list<ServiceDescription>::iterator &it)
{
    m_serviceDescriptions.erase(it);
    return *this;
}

MPD &MPD::initializationSetAdd(const InitializationSet &init_set)
{
    m_initializationSets.push_back(init_set);
    return *this;
}

MPD &MPD::initializationSetAdd(InitializationSet &&init_set)
{
    m_initializationSets.push_back(std::move(init_set));
    return *this;
}

MPD &MPD::initializationSetRemove(const InitializationSet &init_set)
{
    m_initializationSets.remove(init_set);
    return *this;
}

MPD &MPD::initializationSetRemove(const std::list<InitializationSet>::const_iterator &it)
{
    m_initializationSets.erase(it);
    return *this;
}

MPD &MPD::initializationSetRemove(const std::list<InitializationSet>::iterator &it)
{
    m_initializationSets.erase(it);
    return *this;
}

MPD &MPD::initializationGroupAdd(const UIntVWithID &init_group)
{
    m_initializationGroups.push_back(init_group);
    return *this;
}

MPD &MPD::initializationGroupAdd(UIntVWithID &&init_group)
{
    m_initializationGroups.push_back(std::move(init_group));
    return *this;
}

MPD &MPD::initializationGroupRemove(const UIntVWithID &init_group)
{
    m_initializationGroups.remove(init_group);
    return *this;
}

MPD &MPD::initializationGroupRemove(const std::list<UIntVWithID>::const_iterator &it)
{
    m_initializationGroups.erase(it);
    return *this;
}

MPD &MPD::initializationGroupRemove(const std::list<UIntVWithID>::iterator &it)
{
    m_initializationGroups.erase(it);
    return *this;
}

MPD &MPD::initializationPresentationAdd(const UIntVWithID &init_pres)
{
    m_initializationPresentations.push_back(init_pres);
    return *this;
}

MPD &MPD::initializationPresentationAdd(UIntVWithID &&init_pres)
{
    m_initializationPresentations.push_back(init_pres);
    return *this;
}

MPD &MPD::initializationPresentationRemove(const UIntVWithID &init_pres)
{
    m_initializationPresentations.remove(init_pres);
    return *this;
}

MPD &MPD::initializationPresentationRemove(const std::list<UIntVWithID>::const_iterator &it)
{
    m_initializationPresentations.erase(it);
    return *this;
}

MPD &MPD::initializationPresentationRemove(const std::list<UIntVWithID>::iterator &it)
{
    m_initializationPresentations.erase(it);
    return *this;
}

MPD &MPD::contentProtectionAdd(const ContentProtection &content_protection)
{
    m_contentProtections.push_back(content_protection);
    return *this;
}

MPD &MPD::contentProtectionAdd(ContentProtection &&content_protection)
{
    m_contentProtections.push_back(std::move(content_protection));
    return *this;
}

MPD &MPD::contentProtectionRemove(const ContentProtection &content_protection)
{
    m_contentProtections.remove(content_protection);
    return *this;
}

MPD &MPD::contentProtectionRemove(const std::list<ContentProtection>::const_iterator &it)
{
    m_contentProtections.erase(it);
    return *this;
}

MPD &MPD::contentProtectionRemove(const std::list<ContentProtection>::iterator &it)
{
    m_contentProtections.erase(it);
    return *this;
}

std::list<Period>::const_iterator MPD::period(const std::string &id) const
{
    return std::find_if(m_periods.cbegin(), m_periods.cend(), [id](const Period &period) -> bool { return period.hasId() && period.id().value() == id; });
}

MPD &MPD::periodAdd(const Period &period)
{
    return periodAdd(Period(period));
}

MPD &MPD::periodAdd(Period &&period)
{
    // Assign this MPD as the parent MPD of the period
    period.setMPD(this);

    if (period.hasStart()) {
        // insert in start time order
        auto start = period.start().value();
        auto it = std::find_if(m_periods.begin(), m_periods.end(), [start](const Period &p) -> bool { auto calc_start = p.calcStart(); return calc_start && calc_start.value() < start; });
        auto next = it;
        if (it != m_periods.end()) {
            period.setPreviousSibling(&(*it));
            next++;
        }
        if (next != m_periods.end()) {
            period.setNextSibling(&(*next));
        }
        auto inserted = m_periods.insert(it, std::move(period));
        if (it != m_periods.end()) {
            it->setNextSibling(&(*inserted));
        }
        if (next != m_periods.end()) {
            next->setPreviousSibling(&(*inserted));
        }
    } else {
        // no start so just stick at the end
        auto it = m_periods.rbegin();
        m_periods.push_back(std::move(period));
        Period &inserted = m_periods.back();
        if (it != m_periods.rend()) {
            it->setNextSibling(&inserted);
            inserted.setPreviousSibling(&(*it));
        }
    }
    return *this;
}

MPD &MPD::periodRemove(const Period &period)
{
    decltype(m_periods)::iterator it;

    if (period.hasId()) {
        // remove by id only
        auto id = period.id().value();
        it = std::find_if(m_periods.begin(), m_periods.end(), [id](const Period &p) -> bool { return p.hasId() && p.id().value() == id; });
    } else {
        // remove by value comparison
        it = std::find(m_periods.begin(), m_periods.end(), period);
    }
    if (it != m_periods.end()) {
        // We found a match, so remove it and adjust surrounding Period objects
        if (m_periods.size() == 1) {
            throw InvalidMPD("Removing the only Period will make the MPD invalid");
        }
        it = m_periods.erase(it);
    }    
    if (it !=  m_periods.end()) {
        auto prev = it;
        // was not the last one so reset surrounding siblings pointers
        if (it != m_periods.begin()) {
            // As long as we are not at the begining of the list we can decrement
            prev--;
        } else {
            // Otherwise there is no previous value
            prev = m_periods.end();
        }
        if (prev != m_periods.end()) {
            it->setPreviousSibling(&(*prev));
            prev->setNextSibling(&(*it));       
        } else {
            // we deleted the begining of the list, so just reset next
            it->setPreviousSibling(nullptr);
        }
    } else {
        // we erased the end of the list to just reset previous
        auto prev = m_periods.rbegin();
        if (prev != m_periods.rend()) {
            prev->setNextSibling(nullptr);
        }
    }
    return *this;
}

MPD &MPD::periodRemove(const std::list<Period>::const_iterator &period_it)
{
    if (m_periods.size() == 1) {
        throw InvalidMPD("Removing the only Period will make the MPD invalid");
    }

    auto it = m_periods.erase(period_it);
    if (it !=  m_periods.end()) {
        // was not the last one so reset surrounding siblings pointers
        auto prev = it;
        if (it != m_periods.begin()) {
            // As long as we are not at the begining of the list we can decrement
            prev--;
        } else {
            // Otherwise there is no previous value
            prev = m_periods.end();
        }
        if (prev != m_periods.end()) {
            it->setPreviousSibling(&(*prev));
            prev->setNextSibling(&(*it));
        } else {
            // we deleted the begining of the list, so just reset next
            it->setPreviousSibling(nullptr);
        }
    } else {
        // we erased the end of the list to just reset previous
        auto prev = m_periods.rbegin();
        if (prev != m_periods.rend()) {
            prev->setNextSibling(nullptr);
        }
    }
    return *this;
}

MPD &MPD::periodRemove(const std::list<Period>::iterator &period_it)
{
    if (m_periods.size() == 1) {
        throw InvalidMPD("Removing the only Period will make the MPD invalid");
    }

    auto it = m_periods.erase(period_it);
    if (it !=  m_periods.end()) {
        // was not the last one so reset surrounding siblings pointers
        auto prev = it;
        if (it != m_periods.begin()) {
            // As long as we are not at the begining of the list we can decrement
            prev--;
        } else {
            // Otherwise there is no previous value
            prev = m_periods.end();
        }
        if (prev != m_periods.end()) {
            it->setPreviousSibling(&(*prev));
            prev->setNextSibling(&(*it));
        } else {
            // we deleted the begining of the list, so just reset next
            it->setPreviousSibling(nullptr);
        }
    } else {
        // we erased the end of the list to just reset previous
        auto prev = m_periods.rbegin();
        if (prev != m_periods.rend()) {
            prev->setNextSibling(nullptr);
        }
    }
    return *this;
}

MPD &MPD::metricAdd(const Metrics &metrics)
{
    m_metrics.push_back(metrics);
    return *this;
}

MPD &MPD::metricAdd(Metrics &&metrics)
{
    m_metrics.push_back(std::move(metrics));
    return *this;
}

MPD &MPD::metricRemove(const Metrics &metrics)
{
    m_metrics.remove(metrics);
    return *this;
}

MPD &MPD::metricRemove(const std::list<Metrics>::const_iterator &it)
{
    m_metrics.erase(it);
    return *this;
}

MPD &MPD::metricRemove(const std::list<Metrics>::iterator &it)
{
    m_metrics.erase(it);
    return *this;
}

MPD &MPD::essentialPropertyAdd(const Descriptor &property)
{
    m_essentialProperties.push_back(property);
    return *this;
}

MPD &MPD::essentialPropertyAdd(Descriptor &&property)
{
    m_essentialProperties.push_back(std::move(property));
    return *this;
}

MPD &MPD::essentialPropertyRemove(const Descriptor &property)
{
    m_essentialProperties.remove(property);
    return *this;
}

MPD &MPD::essentialPropertyRemove(const std::list<Descriptor>::const_iterator &it)
{
    m_essentialProperties.erase(it);
    return *this;
}

MPD &MPD::essentialPropertyRemove(const std::list<Descriptor>::iterator &it)
{
    m_essentialProperties.erase(it);
    return *this;
}

MPD &MPD::supplementaryPropertyAdd(const Descriptor &property)
{
    m_supplementaryProperties.push_back(property);
    return *this;
}

MPD &MPD::supplementaryPropertyAdd(Descriptor &&property)
{
    m_supplementaryProperties.push_back(std::move(property));
    return *this;
}

MPD &MPD::supplementaryPropertyRemove(const Descriptor &property)
{
    m_supplementaryProperties.remove(property);
    return *this;
}

MPD &MPD::supplementaryPropertyRemove(const std::list<Descriptor>::const_iterator &it)
{
    m_supplementaryProperties.erase(it);
    return *this;
}

MPD &MPD::supplementaryPropertyRemove(const std::list<Descriptor>::iterator &it)
{
    m_supplementaryProperties.erase(it);
    return *this;
}

MPD &MPD::utcTimingAdd(const Descriptor &utc_timing)
{
    m_utcTimings.push_back(utc_timing);
    return *this;
}

MPD &MPD::utcTimingAdd(Descriptor &&utc_timing)
{
    m_utcTimings.push_back(std::move(utc_timing));
    return *this;
}

MPD &MPD::utcTimingRemove(const Descriptor &utc_timing)
{
    m_utcTimings.remove(utc_timing);
    return *this;
}

MPD &MPD::utcTimingRemove(const std::list<Descriptor>::const_iterator &it)
{
    m_utcTimings.erase(it);
    return *this;
}

MPD &MPD::utcTimingRemove(const std::list<Descriptor>::iterator &it)
{
    m_utcTimings.erase(it);
    return *this;
}

void MPD::synchroniseWithUTCTiming() const
{
    if (m_utcTimings.empty()) return;

    // TODO: fetch one or more UTCTiming timestamp and store the (mean) offset from the system clock
    //       m_cache->haveUtcTimingOffsetFromSystemClock = true;
    //       m_cache->utcTimingOffsetFromSystemClock = duration to add to system_clock to make UTCTiming result.
}

const LeapSecondInformation &MPD::leapSecondInformation(const LeapSecondInformation &default_val) const
{
    if (!m_leapSecondInformation.has_value()) return default_val;
    return m_leapSecondInformation.value();
}

void MPD::selectAllRepresentations()
{
    for (auto &period : m_periods) {
        period.selectAllRepresentations();
    }
}

void MPD::deselectAllRepresentations()
{
    for (auto &period : m_periods) {
        period.deselectAllRepresentations();
    }
}

std::unordered_set<const Representation*> MPD::selectedRepresentations() const
{
    std::unordered_set<const Representation*> ret;
    for (auto &period : m_periods) {
        auto selected_reps = period.selectedRepresentations();
        ret.insert(selected_reps.begin(), selected_reps.end());
    }
    return ret;
}

std::list<SegmentAvailability> MPD::selectedSegmentAvailability(const time_type &query_time) const
{
    std::list<SegmentAvailability> ret;
    time_type adjusted_time = systemTimeToPresentationTime(query_time);
    typename decltype(m_periods)::const_iterator period_it;
    if (m_availabilityStartTime.has_value() && adjusted_time < m_availabilityStartTime.value()) {
        // Select the first period if our query time is before the DASH starts.
        period_it = m_periods.cbegin();
    } else {
        period_it = getPeriodFor(adjusted_time);
    }
    if (period_it != m_periods.cend()) {
        ret = period_it->selectedSegmentAvailability(query_time);
        if (ret.empty()) {
            // No segments left in the current period, try the next one
            period_it++;
            if (period_it != m_periods.cend()) {
                ret = period_it->selectedSegmentAvailability(query_time);
            }
        }
    }

    return ret;
}

std::list<SegmentAvailability> MPD::selectedInitializationSegments(const time_type &query_time) const
{
    std::list<SegmentAvailability> ret;
    time_type adjusted_time = systemTimeToPresentationTime(query_time);
    typename decltype(m_periods)::const_iterator period_it;
    if (m_availabilityStartTime.has_value() && adjusted_time < m_availabilityStartTime.value()) {
        // Select the first period if our query time is before the DASH starts.
        period_it = m_periods.cbegin();
    } else {
        period_it = getPeriodFor(adjusted_time);
    }
    // If we found a suitable period, query it
    if (period_it != m_periods.cend()) {
        ret = period_it->selectedInitializationSegments();
    }
    return ret;
}

// protected:

MPD::time_type MPD::systemTimeToPresentationTime(const MPD::time_type &system_time) const
{
    if (!m_cache->haveUtcTimingOffsetFromSystemClock) synchroniseWithUTCTiming();
    return system_time + m_cache->utcTimingOffsetFromSystemClock;
}

MPD::time_type MPD::presentationTimeToSystemTime(const MPD::time_type &pres_time) const
{
    if (!m_cache->haveUtcTimingOffsetFromSystemClock) synchroniseWithUTCTiming();
    return pres_time - m_cache->utcTimingOffsetFromSystemClock;
}

// private:

template <class T>
concept has_setMPD = requires(T a)
{
    { a.setMPD(nullptr) };
};

template <class T>
requires has_setMPD<T>
T &_setMPD(MPD *mpd, T &a)
{
    return a.setMPD(mpd);
}

template <class T>
requires (!has_setMPD<T>)
T &_setMPD(MPD *mpd, T &a)
{
    return a;
}

void MPD::extractMPD(void *doc)
{
    if (!doc) return;
    xmlpp::Document *mpd_doc = reinterpret_cast<xmlpp::Document*>(doc);
    xmlpp::Element *mpd_root = mpd_doc->get_root_node();
    if (mpd_root->get_namespace_uri() != MPD_NS) throw ParseError("MPD root node not in " MPD_NS " namespace");
    if (mpd_root->get_name() != "MPD") throw ParseError("MPD root node is not <MPD>");

#define CONCAT(a,b) a##b
#define OPT_ATTR_FN(name,fn) do { \
        node_set = mpd_root->find("@" #name); \
        if (node_set.size() == 1) { \
            xmlpp::Attribute *CONCAT(name,_attr) = dynamic_cast<xmlpp::Attribute*>(node_set.front()); \
            CONCAT(m_,name) = fn(CONCAT(name,_attr)->get_value()); \
        } else { \
            CONCAT(m_,name).reset(); \
        } \
    } while (0)
#define OPT_ATTR_STRING(name) OPT_ATTR_FN(name, std::string)
#define OPT_ATTR_TIME_POINT(name) OPT_ATTR_FN(name, str_to_time_point)
#define OPT_ATTR_DURN(name) OPT_ATTR_FN(name, str_to_duration<MPD::duration_type>)
#define MAND_ATTR_FN(name,fn) do { \
        node_set = mpd_root->find("@" #name); \
        if (node_set.size() == 1) { \
            xmlpp::Attribute *CONCAT(name,_attr) = dynamic_cast<xmlpp::Attribute*>(node_set.front()); \
            CONCAT(m_,name) = fn(CONCAT(name,_attr)->get_value()); \
        } else { \
            throw ParseError("MPD must have a \"" #name "\" attribute"); \
        } \
    } while (0)
#define MAND_ATTR_DURN(name) MAND_ATTR_FN(name, str_to_duration<MPD::duration_type>)
#define OPT_ELEM_LIST_CLASS(var, element, cls) do { \
        node_set = mpd_root->find("mpd:" #element, ns_map); \
        var.clear(); \
        for (auto node : node_set) { \
             var.push_back(cls(*node)); \
             _setMPD(this, var.back()); \
        } \
    } while (0)
#define MAND_ELEM_LIST_CLASS(var, element, cls) do { \
        node_set = mpd_root->find("mpd:" #element, ns_map); \
        if (node_set.size() == 0) throw ParseError("MPD needs at least one " #element " element"); \
        var.clear(); \
        for (auto node : node_set) { \
             var.push_back(cls(*node)); \
             _setMPD(this, var.back()); \
        } \
    } while (0)
#define OPT_ELEM_CLASS(var, element, cls) do { \
        node_set = mpd_root->find("mpd:" #element, ns_map); \
        if (node_set.size() == 0) { \
            var.reset(); \
        } else if (node_set.size() == 1) { \
            var = cls(*node_set.front()); \
            _setMPD(this, var); \
        } else { \
            throw ParseError("MPD has too many " #element " elements"); \
        } \
    } while (0)

    xmlpp::Node::NodeSet node_set;
    static const xmlpp::Node::PrefixNsMap ns_map = {
        {"mpd", MPD_NS}
    };


    OPT_ATTR_STRING(id);
    MAND_ATTR_FN(profiles, str_to_uri_list);

    node_set = mpd_root->find("@type");
    if (node_set.size() == 1) {
        xmlpp::Attribute *type_attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        auto type_val = type_attr->get_value();
        if (type_val == "static") {
            m_type = STATIC;
        } else if (type_val == "dynamic") {
            m_type = DYNAMIC;
        } else {
            throw ParseError("Can only handle \"static\" or \"dynamic\" MPD types");
        }
    } else {
        m_type = STATIC;
    }

    OPT_ATTR_TIME_POINT(availabilityStartTime);
    OPT_ATTR_TIME_POINT(availabilityEndTime);
    OPT_ATTR_TIME_POINT(publishTime);
    OPT_ATTR_DURN(mediaPresentationDuration);
    OPT_ATTR_DURN(minimumUpdatePeriod);
    MAND_ATTR_DURN(minBufferTime);
    OPT_ATTR_DURN(timeShiftBufferDepth);
    OPT_ATTR_DURN(suggestedPresentationDelay);
    OPT_ATTR_DURN(maxSegmentDuration);
    OPT_ATTR_DURN(maxSubsegmentDuration);

    OPT_ELEM_LIST_CLASS(m_programInformations, ProgramInformation, ProgramInformation);
    OPT_ELEM_LIST_CLASS(m_baseURLs, BaseURL, BaseURL);
    OPT_ELEM_LIST_CLASS(m_locations, Location, URI);
    OPT_ELEM_LIST_CLASS(m_patchLocations, PatchLocation, PatchLocation);
    OPT_ELEM_LIST_CLASS(m_serviceDescriptions, ServiceDescription, ServiceDescription);
    OPT_ELEM_LIST_CLASS(m_initializationSets, InitializationSet, InitializationSet);
    OPT_ELEM_LIST_CLASS(m_initializationGroups, InitializationGroup, UIntVWithID);
    OPT_ELEM_LIST_CLASS(m_initializationPresentations, InitializationPresentation, UIntVWithID);
    OPT_ELEM_LIST_CLASS(m_contentProtections, ContentProtection, ContentProtection);
    MAND_ELEM_LIST_CLASS(m_periods, Period, Period);
    OPT_ELEM_LIST_CLASS(m_metrics, Metrics, Metrics);
    OPT_ELEM_LIST_CLASS(m_essentialProperties, EssentialProperty, Descriptor);
    OPT_ELEM_LIST_CLASS(m_supplementaryProperties, SupplementaryProperty, Descriptor);
    OPT_ELEM_LIST_CLASS(m_utcTimings, UTCTiming, Descriptor);
    OPT_ELEM_CLASS(m_leapSecondInformation, LeapSecondInformation, LeapSecondInformation);

    Period *prev = nullptr;
    for (auto &period : m_periods) {
        period.setMPD(this);
        if (prev) {
            period.setPreviousSibling(prev);
            prev->setNextSibling(&period);
        }
        prev = &period;
    }
}

std::list<Period>::const_iterator MPD::getPeriodFor(const MPD::time_type &pres_time) const
{
    if (isLive()) {
        for (auto it = m_periods.cbegin(); it != m_periods.cend(); it++) {
            auto calc_start = it->calcStart();
            auto period_start = (m_availabilityStartTime?m_availabilityStartTime.value():time_type()) +
                                (calc_start?calc_start.value():0s);
            if (pres_time < period_start) break;
            if (pres_time >= period_start) {
                auto calc_duration = it->calcDuration();
                if (!calc_duration) return it;
                auto period_end = period_start + calc_duration.value();
                if (pres_time < period_end) return it;
            }
        }
    } else {
        // TODO: find period for wallclock time in VoD (need to know wallclock start time!)
    }

    return m_periods.cend();
}

MPD::Cache::Cache()
    :haveUtcTimingOffsetFromSystemClock(false)
    ,utcTimingOffsetFromSystemClock(0s)
{
}

static MPDFormattingOptions &get_mpd_formatting(std::ios_base &ios)
{
    auto &pword = ios.pword(g_MPD_formatting_xindex);
    if (pword == nullptr) {
        pword = reinterpret_cast<void*>(new MPDFormattingOptions());
        ios.register_callback([](std::ios_base::event evt, std::ios_base& str, int idx){
            MPDFormattingOptions *options = reinterpret_cast<MPDFormattingOptions*>(str.pword(idx));
            if (evt == std::ios_base::erase_event) {
                if (options) delete options;
            }
        }, g_MPD_formatting_xindex);
    }
    return *reinterpret_cast<MPDFormattingOptions*>(pword);
}

static MPD::time_type str_to_time_point(const std::string &str)
{
    MPD::time_type ret;
    std::istringstream is(str);
    is >> std::chrono::parse("%FT%TZ", ret);
    return ret;
}

static std::list<URI> str_to_uri_list(const std::string &str, char sep)
{
    std::list<URI> ret;
    std::string items(str);

    for (auto posn = items.find_first_of(sep); posn != std::string::npos; posn = items.find_first_of(sep)) {
        std::string item = items.substr(0,posn);
        items = items.substr(posn+1);
        ret.push_back(URI(item));
    }
    ret.push_back(URI(items));

    return ret;
}

LIBMPDPP_NAMESPACE_END

std::ostream &operator<<(std::ostream &os, const LIBMPDPP_NAMESPACE_CLASS(MPD) &mpd)
{
    auto &options = LIBMPDPP_NAMESPACE_CLASS(get_mpd_formatting)(os);
    os << mpd.asXML(options.compact());
    return os;
}

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
