#ifndef _BBC_PARSE_DASH_MPD_MPD_HH_
#define _BBC_PARSE_DASH_MPD_MPD_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: main meson build file
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <chrono>
#include <iostream>
#include <list>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

#include "macros.hh"
#include "BaseURL.hh"
#include "ContentProtection.hh"
#include "Descriptor.hh"
#include "InitializationSet.hh"
#include "LeapSecondInformation.hh"
#include "Metrics.hh"
#include "PatchLocation.hh"
#include "Period.hh"
#include "ProgramInformation.hh"
#include "SegmentAvailability.hh"
#include "ServiceDescription.hh"
#include "UIntVWithID.hh"
#include "URI.hh"

LIBMPDPP_NAMESPACE_BEGIN

/** MPD class
 * @headerfile libmpd++/MPD.hh <libmpd++/MPD.hh>
 *
 * This is the top level class for parsing, manipulating and outputting MPDs.
 *
 * Use this class to parse an existing MPD file or in-memory block, or create a new MPD.
 *
 * This class stores the attributes and elements as described by the %MPDType in ISO 23009-1:2022 Clause 5.2.2.
 *
 * @see The @ref codeExamples "Example library usage" page for examples of using the MPD class.
 */
class LIBMPDPP_PUBLIC_API MPD {
public:
    using time_type = std::chrono::system_clock::time_point; ///< Date-time type used in the MPD
    using duration_type = std::chrono::microseconds;         ///< Time duration type used in the MPD

    /** MPD @@presentationType values enumeration
     */
    enum PresentationType {
        STATIC,  ///< Presentation is static (unchanging, e.g. video on demand)
        DYNAMIC  ///< Presentation is dynamic (can change during playback, e.g. live stream)
    };

    /** Default constructor
     * 
     * This is removed to force mandatory parameters in the MPD to be filled in.
     */
    MPD() = delete;

    /**@{*/
    /** Value constructor
     *
     * This creates a new MPD with the mandatory values from @p minimum_buffer_time, @p profile, @p period and @p presentation_type.
     *
     * @param minimum_buffer_time The duration for the minimum buffer time.
     * @param profile The profile URN.
     * @param period A Period for this MPD.
     * @param presentation_type The presentation type of the MPD, either MPD::STATIC or MPD::DYNAMIC. If not given then MPD::STATIC
     *                          is used as the default.
     */
    MPD(const duration_type &minimum_buffer_time, const URI &profile, const Period &period, PresentationType presentation_type = STATIC);
    MPD(const duration_type &minimum_buffer_time, const URI &profile, Period &&period, PresentationType presentation_type = STATIC);
    /**@}*/

    /** Construct from an input stream
     *
     * @param input_stream The stream to parse the MPD XML from.
     * @param mpd_location The URL the MPD was obtained from.
     */
    MPD(std::istream &input_stream, const std::optional<URI> &mpd_location = std::nullopt);

    /**@{*/
    /** Construct from MPD XML in memory
     *
     * @param mpd_xml The vector containing the MPD XML.
     * @param mpd_location The URL the MPD was obtained from.
     */
    MPD(const std::vector<char> &mpd_xml, const std::optional<URI> &mpd_location = std::nullopt);
    MPD(const std::vector<unsigned char> &mpd_xml, const std::optional<URI> &mpd_location = std::nullopt);
    /**@}*/

    /** Construct from an MPD XML file
     *
     * @param filename The file path of the MPD XML file.
     * @param mpd_location The URL the MPD was obtained from.
     */
    MPD(const std::string &filename, const std::optional<URI> &mpd_location = std::nullopt);

    /** Copy constructor
     * 
     * @param other The MPD to make a new copy of.
     */
    MPD(const MPD &other);

    /** Move constructor
     *
     * @param other The MPD to take the resources and values from to create a new MPD.
     */
    MPD(MPD &&other);

    /** Destructor
     */
    virtual ~MPD();

    /** Copy operator
     * 
     * @param other The MPD to copy into this one.
     * @return This MPD.
     */
    MPD &operator=(const MPD &other);

    /** Move operator
     * 
     * @param other The MPD to take the resources and values from to set in this MPD.
     * @return This MPD.
     */
    MPD &operator=(MPD &&other);

    /** Equality operator
     * 
     * @param other The MPD to compare to this MPD.
     * @return `true` if the @p other MPD represents the same value as this MPD.
     */
    bool operator==(const MPD &other) const;

    /** Check if a source location URL has been set for this MPD
     *
     * Check if the source URL has been set by either using the @ref MPD::sourceURL setters or by providing the @p mpd_location to
     * an MPD::MPD() constructor.
     *
     * @return `true` if a source URL has been set, otherwise `false`.
     * @see MPD::MPD(std::istream&, const std::optional<URI>&)
     * @see MPD::MPD(const std::vector<char>&, const std::optional<URI>&)
     * @see MPD::MPD(const std::vector<unsigned char>&, const std::optional<URI>&)
     * @see MPD::MPD(const std::string&, const std::optional<URI>&)
     * @see MPD::sourceURL(const std::nullopt_t&)
     * @see MPD::sourceURL(const URI&)
     * @see MPD::sourceURL(URI&&)
     * @see MPD::sourceURL(const std::optional<URI>&)
     * @see MPD::sourceURL(std::optional<URI>&&)
     */
    bool hasSourceURL() const { return m_mpdURL.has_value(); };

    /** Get the optional source URL
     *
     * @return The optional source URL.
     */
    const std::optional<URI> &sourceURL() const { return m_mpdURL; };

    /** Unset the source URL
     *
     * Will remove, if set, the source URL from this MPD.
     *
     * @return This MPD.
     */
    MPD &sourceURL(const std::nullopt_t &) { m_mpdURL.reset(); return *this; };

    /**@{*/
    /** Set the source URL
     *
     * @param url The URL to set as the source URL for this MPD.
     */
    MPD &sourceURL(const URI &url) { m_mpdURL = url; return *this; };
    MPD &sourceURL(URI &&url) { m_mpdURL = std::move(url); return *this; };
    MPD &sourceURL(const std::optional<URI> &url) { m_mpdURL = url; return *this; };
    MPD &sourceURL(std::optional<URI> &&url) { m_mpdURL = std::move(url); return *this; };
    /**@}*/

    /** Check if this is a live MPD
     *
     * Check if this is a live or on-demand MPD by checking the @@presentationType and @@profiles attributes.
     *
     * @return `true` if the presentation type is dynamic and the profile matches one of the known live profiles, otherwise `false`.
     */
    bool isLive() const;

    /** Get the MPD as an XML document string
     * 
     * If @p compact_form is `true` then the returned string will omit unnecessary white-space to make the returnned string more
     * compact. If @p compact_form is `false` then a more human readable indented form of the XML is returned.
     *
     * @param compact_form `true` for a compact XML string, `false` for a more readable response.
     * @return The XML representation of the MPD.
     */
    std::string asXML(bool compact_form) const;

    /** Stream manipulator to switch MPD XML streaming to compact form
     * 
     * This will make any subsequent MPD streamed to the std::ostream do so in a compact form.
     *
     * For example the following are both equivalent:
     * @code{.cpp}
     * os << MPD::compact << mpd;
     * os << mpd.asXML(true);
     * @endcode
     *
     * @param os The std::ostream that will be used to output the XML representation of the MPD to at a later time.
     * @return @p os.
     */
    static std::ostream &compact(std::ostream &os);

    /** Stream manipulator to switch MPD XML streaming to pretty form
     * 
     * This will make any subsequent MPD streamed to the std::ostream do so in a pretty form.
     *
     * For example the following are both equivalent:
     * @code{.cpp}
     * os << MPD::pretty << mpd;
     * os << mpd.asXML(false);
     * @endcode
     *
     * @param os The std::ostream that will be used to output the XML representation of the MPD to at a later time.
     * @return @p os.
     */
    static std::ostream &pretty(std::ostream &os);

    bool hasId() const { return m_id.has_value(); };
    const std::string &id(const std::string &default_val) const;
    const std::optional<std::string> &id() const { return m_id; };
    MPD &id(const std::string &val) { m_id = val; return *this; };
    MPD &id(std::string &&val) { m_id = std::move(val); return *this; };
    MPD &id(const std::nullopt_t&) { m_id.reset(); return *this; };

    const std::list<URI> &profiles() const { return m_profiles; };
    std::list<URI>::const_iterator profilesBegin() const { return m_profiles.cbegin(); };
    std::list<URI>::const_iterator profilesEnd() const { return m_profiles.cend(); };
    std::list<URI>::iterator profilesBegin() { return m_profiles.begin(); };
    std::list<URI>::iterator profilesEnd() { return m_profiles.end(); };
    const URI &profile(std::list<URI>::size_type idx) const {
        if (idx >= m_profiles.size())
            throw std::out_of_range("MPD profile does not exist");
        auto it = m_profiles.cbegin();
        while (idx > 0 && it != m_profiles.cend()) {it++; idx--;}
        return *it;
    };
    bool profilesContain(const URI &uri) const;
    MPD &profileAdd(const URI &uri);
    MPD &profileAdd(URI &&uri);
    MPD &profileRemove(const std::list<URI>::const_iterator &it);
    MPD &profileRemove(const URI &uri);

    bool isStaticPresentation() const { return m_type == STATIC; };
    bool isDynamicPresentation() const { return m_type == DYNAMIC; };
    PresentationType presentationType() const { return m_type; };
    MPD &presentationType(PresentationType pres_type) { m_type = pres_type; return *this; };

    bool hasAvailabilityStartTime() const { return m_availabilityStartTime.has_value(); };
    const time_type &availabilityStartTime(const time_type &default_val) const;
    const std::optional<time_type> &availabilityStartTime() const { return m_availabilityStartTime; };
    MPD &availabilityStartTime(const time_type &val) { m_availabilityStartTime = val; return *this; };
    MPD &availabilityStartTime(time_type &&val) { m_availabilityStartTime = std::move(val); return *this; };
    MPD &availabilityStartTime(const std::nullopt_t&) { m_availabilityStartTime.reset(); return *this; };

    bool hasAvailabilityEndTime() const { return m_availabilityEndTime.has_value(); };
    const time_type &availabilityEndTime(const time_type &default_val) const;
    const std::optional<time_type> &availabilityEndTime() const { return m_availabilityEndTime; };
    MPD &availabilityEndTime(const time_type &val) { m_availabilityEndTime = val; return *this; };
    MPD &availabilityEndTime(time_type &&val) { m_availabilityEndTime = std::move(val); return *this; };
    MPD &availabilityEndTime(const std::nullopt_t&) { m_availabilityEndTime.reset(); return *this; };

    bool hasPublishTime() const { return m_publishTime.has_value(); };
    const time_type &publishTime(const time_type &default_val) const;
    const std::optional<time_type> &publishTime() const { return m_publishTime; };
    MPD &publishTime(const time_type &val) { m_publishTime = val; return *this; };
    MPD &publishTime(time_type &&val) { m_publishTime = std::move(val); return *this; };
    MPD &publishTime(const std::nullopt_t&) { m_publishTime.reset(); return *this; };

    bool hasMediaPresentationDuration() const { return m_mediaPresentationDuration.has_value(); };
    const duration_type &mediaPresentationDuration(const duration_type &default_val) const;
    const std::optional<duration_type> &mediaPresentationDuration() const { return m_mediaPresentationDuration; };
    MPD &mediaPresentationDuration(const duration_type &val) { m_mediaPresentationDuration = val; return *this; };
    MPD &mediaPresentationDuration(duration_type &&val) { m_mediaPresentationDuration = std::move(val); return *this; };
    MPD &mediaPresentationDuration(const std::nullopt_t&) { m_mediaPresentationDuration.reset(); return *this; };

    bool hasMinimumUpdatePeriod() const { return m_minimumUpdatePeriod.has_value(); };
    const duration_type &minimumUpdatePeriod(const duration_type &default_val) const;
    const std::optional<duration_type> &minimumUpdatePeriod() const { return m_minimumUpdatePeriod; };
    MPD &minimumUpdatePeriod(const duration_type &val) { m_minimumUpdatePeriod = val; return *this; };
    MPD &minimumUpdatePeriod(duration_type &&val) { m_minimumUpdatePeriod = std::move(val); return *this; };
    MPD &minimumUpdatePeriod(const std::nullopt_t&) { m_minimumUpdatePeriod.reset(); return *this; };

    const duration_type &minBufferTime() const { return m_minBufferTime; };
    MPD &minBufferTime(const duration_type &val) { m_minBufferTime = val; return *this; };
    MPD &minBufferTime(duration_type &&val) { m_minBufferTime = std::move(val); return *this; };

    bool hasTimeShiftBufferDepth() const { return m_timeShiftBufferDepth.has_value(); };
    const duration_type &timeShiftBufferDepth(const duration_type &default_val) const;
    const std::optional<duration_type> &timeShiftBufferDepth() const { return m_timeShiftBufferDepth; };
    MPD &timeShiftBufferDepth(const duration_type &val) { m_timeShiftBufferDepth = val; return *this; };
    MPD &timeShiftBufferDepth(duration_type &&val) { m_timeShiftBufferDepth = std::move(val); return *this; };
    MPD &timeShiftBufferDepth(const std::nullopt_t&) { m_timeShiftBufferDepth.reset(); return *this; };

    bool hasSuggestedPresentationDelay() const { return m_suggestedPresentationDelay.has_value(); };
    const duration_type &suggestedPresentationDelay(const duration_type &default_val) const;
    const std::optional<duration_type> &suggestedPresentationDelay() const { return m_suggestedPresentationDelay; };
    MPD &suggestedPresentationDelay(const duration_type &val) { m_suggestedPresentationDelay = val; return *this; };
    MPD &suggestedPresentationDelay(duration_type &&val) { m_suggestedPresentationDelay = std::move(val); return *this; };
    MPD &suggestedPresentationDelay(const std::nullopt_t&) { m_suggestedPresentationDelay.reset(); return *this; };

    bool hasMaxSegmentDuration() const { return m_maxSegmentDuration.has_value(); };
    const duration_type &maxSegmentDuration(const duration_type &default_val) const;
    const std::optional<duration_type> &maxSegmentDuration() const { return m_maxSegmentDuration; };
    MPD &maxSegmentDuration(const duration_type &val) { m_maxSegmentDuration = val; return *this; };
    MPD &maxSegmentDuration(duration_type &&val) { m_maxSegmentDuration = std::move(val); return *this; };
    MPD &maxSegmentDuration(const std::nullopt_t&) { m_maxSegmentDuration.reset(); return *this; };

    bool hasMaxSubsegmentDuration() const { return m_maxSubsegmentDuration.has_value(); };
    const duration_type &maxSubsegmentDuration(const duration_type &default_val) const;
    const std::optional<duration_type> &maxSubsegmentDuration() const { return m_maxSubsegmentDuration; };
    MPD &maxSubsegmentDuration(const duration_type &val) { m_maxSubsegmentDuration = val; return *this; };
    MPD &maxSubsegmentDuration(duration_type &&val) { m_maxSubsegmentDuration = std::move(val); return *this; };
    MPD &maxSubsegmentDuration(const std::nullopt_t&) { m_maxSubsegmentDuration.reset(); return *this; };

    const std::list<ProgramInformation> &programInformations() const { return m_programInformations; };
    std::list<ProgramInformation>::const_iterator programInformationsBegin() const { return m_programInformations.cbegin(); };
    std::list<ProgramInformation>::const_iterator programInformationsEnd() const { return m_programInformations.cend(); };
    std::list<ProgramInformation>::iterator programInformationsBegin() { return m_programInformations.begin(); };
    std::list<ProgramInformation>::iterator programInformationsEnd() { return m_programInformations.end(); };
    MPD &programInformationAdd(const ProgramInformation &prog_info);
    MPD &programInformationAdd(ProgramInformation &&prog_info);
    MPD &programInformationRemove(const ProgramInformation &prog_info);
    MPD &programInformationRemove(const std::list<ProgramInformation>::const_iterator &);
    MPD &programInformationRemove(const std::list<ProgramInformation>::iterator &);

    const std::list<BaseURL> &baseURLs() const { return m_baseURLs; };
    std::list<BaseURL>::const_iterator baseURLsBegin() const { return m_baseURLs.cbegin(); };
    std::list<BaseURL>::const_iterator baseURLsEnd() const { return m_baseURLs.cend(); };
    std::list<BaseURL>::iterator baseURLsBegin() { return m_baseURLs.begin(); };
    std::list<BaseURL>::iterator baseURLsEnd() { return m_baseURLs.end(); };
    MPD &baseURLAdd(const BaseURL &base_url);
    MPD &baseURLAdd(BaseURL &&base_url);
    MPD &baseURLRemove(const BaseURL &base_url);
    MPD &baseURLRemove(const std::list<BaseURL>::const_iterator &);
    MPD &baseURLRemove(const std::list<BaseURL>::iterator &);

    /** Get the combined BaseURLs
     *
     * This will get the list of BaseURL elements, which are children of the MPD, with their %URLs resolved using the MPD source
     * %URL as the base %URL, i.e. relative BaseURL entries will be resolved using the sourceURL() value (as set by the controlling
     * application).
     *
     * If there are no BaseURLs set, then the return value is copied from the source %URL. If a source URL has been set then a
     * single entry is returned with the source %URL in it, otherwise an empty list is returned.
     *
     * @return The list of BaseURL values applicable at the MPD level.
     */
    std::list<BaseURL> getBaseURLs() const;

    const std::list<URI> &locations() const { return m_locations; };
    std::list<URI>::const_iterator locationsBegin() const { return m_locations.cbegin(); };
    std::list<URI>::const_iterator locationsEnd() const { return m_locations.cend(); };
    std::list<URI>::iterator locationsBegin() { return m_locations.begin(); };
    std::list<URI>::iterator locationsEnd() { return m_locations.end(); };
    MPD &locationAdd(const URI &location);
    MPD &locationAdd(URI &&location);
    MPD &locationRemove(const URI &location);
    MPD &locationRemove(const std::list<URI>::const_iterator &);
    MPD &locationRemove(const std::list<URI>::iterator &);

    const std::list<PatchLocation> &patchLocations() const { return m_patchLocations; };
    std::list<PatchLocation>::const_iterator patchLocationsBegin() const { return m_patchLocations.cbegin(); };
    std::list<PatchLocation>::const_iterator patchLocationsEnd() const { return m_patchLocations.cend(); };
    std::list<PatchLocation>::iterator patchLocationsBegin() { return m_patchLocations.begin(); };
    std::list<PatchLocation>::iterator patchLocationsEnd() { return m_patchLocations.end(); };
    MPD &patchLocationAdd(const PatchLocation &patch_location);
    MPD &patchLocationAdd(PatchLocation &&patch_location);
    MPD &patchLocationRemove(const PatchLocation &patch_location);
    MPD &patchLocationRemove(const std::list<PatchLocation>::const_iterator &);
    MPD &patchLocationRemove(const std::list<PatchLocation>::iterator &);

    const std::list<ServiceDescription> &serviceDescriptions() const { return m_serviceDescriptions; };
    std::list<ServiceDescription>::const_iterator serviceDescriptionsBegin() const { return m_serviceDescriptions.cbegin(); };
    std::list<ServiceDescription>::const_iterator serviceDescriptionsEnd() const { return m_serviceDescriptions.cend(); };
    std::list<ServiceDescription>::iterator serviceDescriptionsBegin() { return m_serviceDescriptions.begin(); };
    std::list<ServiceDescription>::iterator serviceDescriptionsEnd() { return m_serviceDescriptions.end(); };
    MPD &serviceDescriptionAdd(const ServiceDescription &service_desc);
    MPD &serviceDescriptionAdd(ServiceDescription &&service_desc);
    MPD &serviceDescriptionRemove(const ServiceDescription &service_desc);
    MPD &serviceDescriptionRemove(const std::list<ServiceDescription>::const_iterator &);
    MPD &serviceDescriptionRemove(const std::list<ServiceDescription>::iterator &);

    const std::list<InitializationSet> &initializationSets() const { return m_initializationSets; };
    std::list<InitializationSet>::const_iterator initializationSetsBegin() const { return m_initializationSets.cbegin(); };
    std::list<InitializationSet>::const_iterator initializationSetsEnd() const { return m_initializationSets.cend(); };
    std::list<InitializationSet>::iterator initializationSetsBegin() { return m_initializationSets.begin(); };
    std::list<InitializationSet>::iterator initializationSetsEnd() { return m_initializationSets.end(); };
    MPD &initializationSetAdd(const InitializationSet &init_set);
    MPD &initializationSetAdd(InitializationSet &&init_set);
    MPD &initializationSetRemove(const InitializationSet &init_set);
    MPD &initializationSetRemove(const std::list<InitializationSet>::const_iterator &);
    MPD &initializationSetRemove(const std::list<InitializationSet>::iterator &);

    const std::list<UIntVWithID> &initializationGroups() const { return m_initializationGroups; };
    std::list<UIntVWithID>::const_iterator initializationGroupsBegin() const { return m_initializationGroups.cbegin(); };
    std::list<UIntVWithID>::const_iterator initializationGroupsEnd() const { return m_initializationGroups.cend(); };
    std::list<UIntVWithID>::iterator initializationGroupsBegin() { return m_initializationGroups.begin(); };
    std::list<UIntVWithID>::iterator initializationGroupsEnd() { return m_initializationGroups.end(); };
    MPD &initializationGroupAdd(const UIntVWithID &init_group);
    MPD &initializationGroupAdd(UIntVWithID &&init_group);
    MPD &initializationGroupRemove(const UIntVWithID &init_group);
    MPD &initializationGroupRemove(const std::list<UIntVWithID>::const_iterator &);
    MPD &initializationGroupRemove(const std::list<UIntVWithID>::iterator &);

    const std::list<UIntVWithID> &initializationPresentations() const { return m_initializationPresentations; };
    std::list<UIntVWithID>::const_iterator initializationPresentationsBegin() const { return m_initializationPresentations.cbegin(); };
    std::list<UIntVWithID>::const_iterator initializationPresentationsEnd() const { return m_initializationPresentations.cend(); };
    std::list<UIntVWithID>::iterator initializationPresentationsBegin() { return m_initializationPresentations.begin(); };
    std::list<UIntVWithID>::iterator initializationPresentationsEnd() { return m_initializationPresentations.end(); };
    MPD &initializationPresentationAdd(const UIntVWithID &init_pres);
    MPD &initializationPresentationAdd(UIntVWithID &&init_pres);
    MPD &initializationPresentationRemove(const UIntVWithID &init_pres);
    MPD &initializationPresentationRemove(const std::list<UIntVWithID>::const_iterator &);
    MPD &initializationPresentationRemove(const std::list<UIntVWithID>::iterator &);

    const std::list<ContentProtection> &contentProtections() const { return m_contentProtections; };
    std::list<ContentProtection>::const_iterator contentProtectionsBegin() const { return m_contentProtections.cbegin(); };
    std::list<ContentProtection>::const_iterator contentProtectionsEnd() const { return m_contentProtections.cend(); };
    std::list<ContentProtection>::iterator contentProtectionsBegin() { return m_contentProtections.begin(); };
    std::list<ContentProtection>::iterator contentProtectionsEnd() { return m_contentProtections.end(); };
    MPD &contentProtectionAdd(const ContentProtection &content_protection);
    MPD &contentProtectionAdd(ContentProtection &&content_protection);
    MPD &contentProtectionRemove(const ContentProtection &content_protection);
    MPD &contentProtectionRemove(const std::list<ContentProtection>::const_iterator &);
    MPD &contentProtectionRemove(const std::list<ContentProtection>::iterator &);

    const std::list<Period> &periods() const { return m_periods; };
    std::list<Period>::const_iterator period(const std::string &id) const;
    std::list<Period>::const_iterator periodsBegin() const {return m_periods.cbegin(); };
    std::list<Period>::const_iterator periodsEnd() const {return m_periods.cend(); };
    std::list<Period>::iterator period(const std::string &id);
    std::list<Period>::iterator periodsBegin() { return m_periods.begin(); };
    std::list<Period>::iterator periodsEnd() { return m_periods.end(); };
    MPD &periodAdd(const Period &period);
    MPD &periodAdd(Period &&period);
    MPD &periodRemove(const Period &period);
    MPD &periodRemove(const std::list<Period>::const_iterator &period_it);
    MPD &periodRemove(const std::list<Period>::iterator &period_it);

    const std::list<Metrics> &metrics() const { return m_metrics; };
    std::list<Metrics>::const_iterator metricsBegin() const { return m_metrics.cbegin(); };
    std::list<Metrics>::const_iterator metricsEnd() const { return m_metrics.cend(); };
    std::list<Metrics>::iterator metricsBegin() { return m_metrics.begin(); };
    std::list<Metrics>::iterator metricsEnd() { return m_metrics.end(); };
    MPD &metricAdd(const Metrics &prog_info);
    MPD &metricAdd(Metrics &&prog_info);
    MPD &metricRemove(const Metrics &prog_info);
    MPD &metricRemove(const std::list<Metrics>::const_iterator &);
    MPD &metricRemove(const std::list<Metrics>::iterator &);

    const std::list<Descriptor> &essentialProperties() const { return m_essentialProperties; };
    std::list<Descriptor>::const_iterator essentialPropertiesBegin() const { return m_essentialProperties.cbegin(); };
    std::list<Descriptor>::const_iterator essentialPropertiesEnd() const { return m_essentialProperties.cend(); };
    std::list<Descriptor>::iterator essentialPropertiesBegin() { return m_essentialProperties.begin(); };
    std::list<Descriptor>::iterator essentialPropertiesEnd() { return m_essentialProperties.end(); };
    MPD &essentialPropertyAdd(const Descriptor &prog_info);
    MPD &essentialPropertyAdd(Descriptor &&prog_info);
    MPD &essentialPropertyRemove(const Descriptor &prog_info);
    MPD &essentialPropertyRemove(const std::list<Descriptor>::const_iterator &);
    MPD &essentialPropertyRemove(const std::list<Descriptor>::iterator &);

    const std::list<Descriptor> &supplementaryProperties() const { return m_supplementaryProperties; };
    std::list<Descriptor>::const_iterator supplementaryPropertiesBegin() const { return m_supplementaryProperties.cbegin(); };
    std::list<Descriptor>::const_iterator supplementaryPropertiesEnd() const { return m_supplementaryProperties.cend(); };
    std::list<Descriptor>::iterator supplementaryPropertiesBegin() { return m_supplementaryProperties.begin(); };
    std::list<Descriptor>::iterator supplementaryPropertiesEnd() { return m_supplementaryProperties.end(); };
    MPD &supplementaryPropertyAdd(const Descriptor &prog_info);
    MPD &supplementaryPropertyAdd(Descriptor &&prog_info);
    MPD &supplementaryPropertyRemove(const Descriptor &prog_info);
    MPD &supplementaryPropertyRemove(const std::list<Descriptor>::const_iterator &);
    MPD &supplementaryPropertyRemove(const std::list<Descriptor>::iterator &);

    const std::list<Descriptor> &utcTimings() const { return m_utcTimings; };
    std::list<Descriptor>::const_iterator utcTimingsBegin() const { return m_utcTimings.cbegin(); };
    std::list<Descriptor>::const_iterator utcTimingsEnd() const { return m_utcTimings.cend(); };
    std::list<Descriptor>::iterator utcTimingsBegin() { return m_utcTimings.begin(); };
    std::list<Descriptor>::iterator utcTimingsEnd() { return m_utcTimings.end(); };
    MPD &utcTimingAdd(const Descriptor &prog_info);
    MPD &utcTimingAdd(Descriptor &&prog_info);
    MPD &utcTimingRemove(const Descriptor &prog_info);
    MPD &utcTimingRemove(const std::list<Descriptor>::const_iterator &);
    MPD &utcTimingRemove(const std::list<Descriptor>::iterator &);
    void synchroniseWithUTCTiming() const;

    bool hasLeapSecondInformation() const { return m_leapSecondInformation.has_value(); };
    const LeapSecondInformation &leapSecondInformation(const LeapSecondInformation &default_val) const;
    const std::optional<LeapSecondInformation> &leapSecondInformation() const { return m_leapSecondInformation; };
    MPD &leapSecondInformation(const LeapSecondInformation &val) { m_leapSecondInformation = val; return *this; };
    MPD &leapSecondInformation(LeapSecondInformation &&val) { m_leapSecondInformation = std::move(val); return *this; };
    MPD &leapSecondInformation(const std::nullopt_t&) { m_leapSecondInformation.reset(); return *this; };

    /** Select all %Representations
     * 
     * This will mark every Representation in every AdaptationSet in every Period as selected.
     */
    void selectAllRepresentations();

    /** Deselect all %Represtations
     *
     * This will remove every Representation in every AdaptationSet in every Period from the set of selected Representations.
     */
    void deselectAllRepresentations();

    /** Get the list of all selected Representation objects
     * 
     * @return The list of all currently selected @ref Representation "Representations" across all @ref Period "Periods".
     */
    std::unordered_set<const Representation*> selectedRepresentations() const;

    /** Get the media segment availability
     *
     * Gets the list of the segment URLs and their availability for the next segments available on or after @p query_time.
     * If an empty list is returned then the @p query_time represents a time after the last segment is available.
     *
     * @param query_time The time to perform the query for, for live MPDs this is the wallclock time, for on-demand MPDs this is
     *                   the stream offset assuming the stream starts from the epoch.
     * @return The list of the next available segments.
     */
    std::list<SegmentAvailability> selectedSegmentAvailability(const time_type &query_time = std::chrono::system_clock::now()) const;

    /** Get the initialization segment availability
     *
     * Gets the list of the initialisation segment URLs and their availability for the Period into which @p query_time falls.
     * If an empty list is returned then the @p query_time represents a time after the MPD availablility end time or there are no
     * initialization segments in this MPD.
     *
     * @param query_time The time to perform the query for, for live MPDs this is the wallclock time, for on-demand MPDs this is
     *                   the stream offset assuming the stream starts from the epoch.
     * @return The list of the next available segments.
     */
    std::list<SegmentAvailability> selectedInitializationSegments(const time_type &query_time = std::chrono::system_clock::now()) const;

/**@cond PROTECTED
 */
protected:
    friend class Period;
    friend class AdaptationSet;
    friend class Representation;
    time_type systemTimeToPresentationTime(const time_type &system_time) const; // Returns presentation time
    time_type presentationTimeToSystemTime(const time_type &pres_time) const; // Returns system wallclock time
/** @endcond PROTECTED
 */

private:
    void extractMPD(void *doc);
    std::list<Period>::const_iterator getPeriodFor(const time_type &pres_time) const;

    // Derived from ISO 23009-1_2022
    // MPD attributes
    std::optional<std::string> m_id;
    std::list<URI> m_profiles; // Must contain at least 1 entry
    PresentationType m_type;
    std::optional<time_type> m_availabilityStartTime;
    std::optional<time_type> m_availabilityEndTime;
    std::optional<time_type> m_publishTime;
    std::optional<duration_type> m_mediaPresentationDuration;
    std::optional<duration_type> m_minimumUpdatePeriod;
    duration_type m_minBufferTime;
    std::optional<duration_type> m_timeShiftBufferDepth;
    std::optional<duration_type> m_suggestedPresentationDelay;
    std::optional<duration_type> m_maxSegmentDuration;
    std::optional<duration_type> m_maxSubsegmentDuration;
    // MPD elements
    std::list<ProgramInformation> m_programInformations;
    std::list<BaseURL> m_baseURLs;
    std::list<URI> m_locations;
    std::list<PatchLocation> m_patchLocations;
    std::list<ServiceDescription> m_serviceDescriptions;
    std::list<InitializationSet> m_initializationSets;
    std::list<UIntVWithID> m_initializationGroups;
    std::list<UIntVWithID> m_initializationPresentations;
    std::list<ContentProtection> m_contentProtections;
    std::list<Period> m_periods; // must contain at least 1 item
    std::list<Metrics> m_metrics;
    std::list<Descriptor> m_essentialProperties;
    std::list<Descriptor> m_supplementaryProperties;
    std::list<Descriptor> m_utcTimings;
    std::optional<LeapSecondInformation> m_leapSecondInformation;

    // MPD original location (if known)
    std::optional<URI> m_mpdURL;   ///< original location URL as given in the constructor or using the sourceURL() methods

    // Cache values (can change, even in const object, hence the pointer)
    struct Cache {
        Cache();
        bool haveUtcTimingOffsetFromSystemClock;      // Indicate if we've fetched UTCTimings before now
        duration_type utcTimingOffsetFromSystemClock; // Offset derived from UTCTiming or a default of 0s.
    } *m_cache;
};

LIBMPDPP_NAMESPACE_END

LIBMPDPP_PUBLIC_API std::ostream &operator<<(std::ostream &os, const LIBMPDPP_NAMESPACE_CLASS(MPD) &mpd);

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_MPD_HH_*/
