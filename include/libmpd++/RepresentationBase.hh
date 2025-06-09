#ifndef _BBC_PARSE_DASH_MPD_REPRESENTATION_BASE_HH_
#define _BBC_PARSE_DASH_MPD_REPRESENTATION_BASE_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: RepresentationBase class
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

#include "macros.hh"
#include "Codecs.hh"
#include "ContentPopularityRate.hh"
#include "ContentProtection.hh"
#include "Descriptor.hh"
#include "EventStream.hh"
#include "FrameRate.hh"
#include "Label.hh"
#include "ProducerReferenceTime.hh"
#include "RandomAccess.hh"
#include "Ratio.hh"
#include "Resync.hh"
#include "SAP.hh"
#include "Switching.hh"
#include "URI.hh"

/**@cond
 */
// Forward declarations for types only used by pointer or reference
namespace xmlpp {
    class Element;
    class Node;
}
/**@endcond
 */

LIBMPDPP_NAMESPACE_BEGIN

/** @brief RepresentationBase class
 *
 * This is a container for the common attributes and elements for AdaptationSet and Representation as described in ISO 23009-1:2022.
 */
class LIBMPDPP_PUBLIC_API RepresentationBase {
public:
    /** Enumeration for implemented VideoScan values
     */
    enum VideoScan {
        VIDEO_SCAN_PROGRESSIVE, ///< Video scan value is "progressive"
        VIDEO_SCAN_INTERLACED,  ///< Video scan value is "interlaced"
        VIDEO_SCAN_UNKNOWN      ///< Video scan value is unknown (i.e. not one of the other values)
    };

    /** Default constructor
     *
     * Creates an empty RepresentationBase.
     */
    RepresentationBase();

    /** Copy constructor
     * 
     * Creates a new RepresentationBase which is a copy of @a to_copy.
     *
     * @param to_copy The RepresentationBase to copy.
     */
    RepresentationBase(const RepresentationBase &to_copy);

    /** Move constructor
     *
     * Creates a new RepresentationBase which is a transfer of the resources and values from @a to_move.
     *
     * @param to_move The RepresentationBase to move into this new RepresentationBase.
     */
    RepresentationBase(RepresentationBase &&to_move);

    /** Destructor
     */
    virtual ~RepresentationBase() {};

    /** Copy operator
     *
     * Replace the current RepresentationBase with a copy of the values from @a to_copy.
     *
     * @param to_copy The RepresentationBase to copy.
     * @return This RepresentationBase.
     */
    RepresentationBase &operator=(const RepresentationBase &to_copy);

    /** Move operator
     * 
     * Replace the current RepresentationBase with the resources and values from @a to_move.
     *
     * @param to_move The RepresentationBase to move into this new RepresentationBase.
     * @return This RepresentationBase.
     */
    RepresentationBase &operator=(RepresentationBase &&to_move);

    /** Equality operator
     *
     * Check if @a to_compare has an equal value to this RepresentationBase.
     *
     * @param to_compare The other RepresentationBase to compare to this.
     * @return `true` if this RepresentationBase has the same values as @a to_compare.
     */
    bool operator==(const RepresentationBase &to_compare) const;

    // TODO: provide accessors for the attribute and child element values

    // @profiles

    /** Get the list of profiles
     *
     * @return the list of profile URIs.
     */
    const std::list<URI> &profiles() const { return m_profiles; };

    /**@{*/
    /** Get an iterator for the start of the profiles list
     * 
     * @return An iterator for the start of the profiles list.
     */
    std::list<URI>::const_iterator profilesBegin() const { return m_profiles.cbegin(); };
    std::list<URI>::iterator profilesBegin() { return m_profiles.begin(); };
    /**@}*/

    /**@{*/
    /** Get an iterator for the end of the profiles list
     *
     * @return An iterator for the end of the profiles list.
     */
    std::list<URI>::const_iterator profilesEnd() const { return m_profiles.cend(); };
    std::list<URI>::iterator profilesEnd() { return m_profiles.end(); };
    /**@}*/

    /**@{*/
    /** Set the profiles list
     *
     * @param _profiles The list of profiles to set the profiles list to.
     * @return This RepresentationBase.
     */
    RepresentationBase &profiles(const std::list<URI> &_profiles) { m_profiles = _profiles; return *this; };
    RepresentationBase &profiles(std::list<URI> &&_profiles) { m_profiles = std::move(_profiles); return *this; };
    /**@}*/

    /** Get an entry from the profiles list
     *
     * @param idx The index in the list (starting from 0) of the profile URI to retrieve.
     * @return The profile URI at list index @a idx.
     * @throw std::out_of_range If the @a idx index references a URI outside the profiles list.
     */
    const URI &profile(std::list<URI>::size_type idx) const;

    /**@{*/
    /** Add a value to the profiles list
     *
     * @param val The profile URI value to add to the @@profile attribute.
     * @return This RepresentationBase.
     */
    RepresentationBase &profilesAdd(const URI &val) { m_profiles.push_back(val); return *this; };
    RepresentationBase &profilesAdd(URI &&val) { m_profiles.push_back(std::move(val)); return *this; };
    /**@}*/

    /** Remove a URI from the profiles list by value
     *
     * @param val The profile URI value of the entry to remove from the @@profile attribute.
     * @return This RepresentationBase.
     */
    RepresentationBase &profilesRemove(const URI &val);

    /**@{*/
    /** Remove a URI from the profiles list by iterator
     *
     * @param it An iterator referencing the entry to remove from the @@profile attribute.
     * @return This RepresentationBase.
     */
    RepresentationBase &profilesRemove(const std::list<URI>::const_iterator &it);
    RepresentationBase &profilesRemove(const std::list<URI>::iterator &it);
    /**@}*/

    // @width

    /** Check if the @@width attribute has been set
     *
     * @return `true` if the @@width attribute has been set, otherwise `false`.
     */
    bool hasWidth() const { return m_width.has_value(); };

    /** Get the optional @@width attribute value
     *
     * @return The optional @@width attribute value.
     */
    const std::optional<unsigned int> &width() const { return m_width; };

    /** Unset the optional @@width attribute value
     *
     * @return This RepresentationBase.
     */
    RepresentationBase &width(const std::nullopt_t&) { m_width.reset(); return *this; };

    /** Set the @@width attribute value
     *
     * @param val The value to set in the @@width attribute.
     * @return This RepresentationBase.
     */
    RepresentationBase &width(unsigned int val) { m_width = val; return *this; };

    // @height

    /** Check if the @@height attribute has been set
     *
     * @return `true` if the @@height attribute has been set, otherwise `false`.
     */
    bool hasHeight() const { return m_height.has_value(); };

    /** Get the optional @@height attribute value
     *
     * @return The optional @@height attribute value.
     */
    const std::optional<unsigned int> &height() const { return m_height; };

    /** Unset the optional @@height attribute value
     *
     * @return This RepresentationBase.
     */
    RepresentationBase &height(const std::nullopt_t&) { m_height.reset(); return *this; };

    /**@{*/
    /** Set the @@height attribute value
     *
     * @param val The value to set in the @@height attribute.
     * @return This RepresentationBase.
     */
    RepresentationBase &height(unsigned int val) { m_height = val; return *this; };
    RepresentationBase &height(const std::optional<unsigned int> &val) { m_height = val; return *this; };
    RepresentationBase &height(std::optional<unsigned int> &&val) { m_height = std::move(val); return *this; };
    /**@}*/

    // @sar

    /** Check if the @@sar attribute is set
     *
     * @return `true` if the @@sar attribute is set.
     */
    bool hasSar() const { return m_sar.has_value(); };

    /** Get the optional @@sar attribute value
     *
     * Get the sample aspect ratio.
     *
     * @return The optional sample aspect ratio.
     */
    const std::optional<Ratio> &sar() const { return m_sar; };

    /** Unset the @@sar attribute value
     *
     * @return This RepresentationBase.
     */
    RepresentationBase &sar(const std::nullopt_t&) { m_sar.reset(); return *this; };

    /**@{*/
    /** Set the @@sar attribute value
     *
     * Set the sample aspect ratio.
     *
     * @param val The sample aspect ratio to set in the @@sar attribute.
     * @return This RepresentationBase.
     */
    RepresentationBase &sar(const Ratio &val) { m_sar = val; return *this; };
    RepresentationBase &sar(Ratio &&val) { m_sar = std::move(val); return *this; };
    RepresentationBase &sar(const std::optional<Ratio> &val) { m_sar = val; return *this; };
    RepresentationBase &sar(std::optional<Ratio> &&val) { m_sar = std::move(val); return *this; };
    /**@}*/

    // @frameRate

    /** Check if the @@frameRate attribute has a value set
     *
     * @return `true` if the @@frameRate attribute has a value set.
     */
    bool hasFrameRate() const { return m_frameRate.has_value(); };

    /** Get the optional @@frameRate attribute value
     *
     * @return The optional @@frameRate attribute value.
     */
    const std::optional<FrameRate> &frameRate() const { return m_frameRate; };

    /** Unset the @@frameRate attribute value
     *
     * @return This RepresentationBase.
     */
    RepresentationBase &frameRate(const std::nullopt_t&) { m_frameRate.reset(); return *this; };

    /**@{*/
    /** Set the @@frameRate attribute value
     *
     * @param val The frame rate value to set in the @@frameRate attribute.
     * @return This RepresentationBase.
     */
    RepresentationBase &frameRate(const FrameRate &val) { m_frameRate = val; return *this; };
    RepresentationBase &frameRate(FrameRate &&val) { m_frameRate = std::move(val); return *this; };
    RepresentationBase &frameRate(const std::optional<FrameRate> &val) { m_frameRate = val; return *this; };
    RepresentationBase &frameRate(std::optional<FrameRate> &&val) { m_frameRate = std::move(val); return *this; };
    /**@}*/

    /** Set the @@frameRate attribute value
     *
     * @param numerator The number of frames per @a denominator seconds.
     * @param denominator The number of seconds over which @a numerator frames are given, defaults to 1 if not provided.
     * @return This RepresentationBase.
     */
    RepresentationBase &frameRate(FrameRate::size_type numerator, FrameRate::size_type denominator = 1) {
        m_frameRate = FrameRate(numerator, denominator);
        return *this;
    };

    // @audioSamplingRate

    /** Get the @@audioSamplingRate attribute list
     *
     * @return The @@audioSamplingRate attribute value list.
     */
    const std::list<unsigned int> &audioSamplingRates() const { return m_audioSamplingRates; };

    /**@{*/
    /** Get an iterator for the start of the @@audioSamplingRate attribute value list
     *
     * @return An iterator at the start of the @@audioSamplingRate attribute value list.
     */
    std::list<unsigned int>::const_iterator audioSamplingRatesBegin() const { return m_audioSamplingRates.cbegin(); };
    std::list<unsigned int>::iterator audioSamplingRatesBegin() { return m_audioSamplingRates.begin(); };
    /**@}*/

    /**@{*/
    /** Get an iterator for the end of the @@audioSamplingRate attribute value list
     *
     * @return An iterator at the end of the @@audioSamplingRate attribute value list.
     */
    std::list<unsigned int>::const_iterator audioSamplingRatesEnd() const { return m_audioSamplingRates.cend(); };
    std::list<unsigned int>::iterator audioSamplingRatesEnd() { return m_audioSamplingRates.end(); };
    /**@}*/

    /**@{*/
    /** Set the audio sampling rate list
     *
     * @param rates The list of audio sample rates to set the @@audioSamplingRate attribute to.
     * @return This RepresentationBase.
     */
    RepresentationBase &audioSamplingRates(const std::list<unsigned int> &rates) { m_audioSamplingRates = rates; return *this; };
    RepresentationBase &audioSamplingRates(std::list<unsigned int> &&rates) { m_audioSamplingRates = std::move(rates); return *this; };
    /**@}*/

    /** Get an @@audioSamplingRate attribute value from the list of @@audioSamplingRate attribute values
     *
     * @param idx The index, starting from 0, of the entry in the @@audioSamplingRate attribute values list to retrieve.
     * @return The audio sampling rate from index @a idx is the list of @@audioSamplingRate attribute values.
     * @throw std::out_of_range If the @a idx index value lies outside the list of @@audioSamplingRate attribute values.
     */
    unsigned int audioSamplingRate(std::list<unsigned int>::size_type idx) const;

    /** Add an @@audioSamplingRate entry
     *
     * @param val The @@audioSamplingRate value to add to the list.
     * @return This RepresentationBase.
     */
    RepresentationBase &audioSamplingRatesAdd(unsigned int val) { m_audioSamplingRates.push_back(val); return *this; };

    /** Remove an @@audioSamplingRate value from the list
     *
     * @param val The @@audioSamplingRate value to remove from the list.
     * @return This RepresentationBase.
     */
    RepresentationBase &audioSamplingRatesRemove(unsigned int val);

    /**@{*/
    /** Remove an @@audioSamplingRate entry from the list
     *
     * @param it An iterator for an entry in the @@audioSamplingRate values list.
     * @return This RepresentationBase.
     */
    RepresentationBase &audioSamplingRatesRemove(const std::list<unsigned int>::const_iterator &it);
    RepresentationBase &audioSamplingRatesRemove(const std::list<unsigned int>::iterator &it);
    /**@}*/

    // @mimeType

    /** Check if the @@mimeType attribute has a value set
     *
     * @return `true` if the @@mimeType attribute has a value set.
     */
    bool hasMimeType() const { return m_mimeType.has_value(); };

    /** Get the optional @@mimeType attribute value
     *
     * @return The optional @@mimeType attribute value.
     */
    const std::optional<std::string> &mimeType() const { return m_mimeType; };

    /** Unset the @@mimeType attribute value
     *
     * @return This RepresentationBase.
     */
    RepresentationBase &mimeType(const std::nullopt_t&) { m_mimeType.reset(); return *this; };

    /**@{*/
    /** Set the @@mimeType attribute value
     *
     * @param val The value to set for the @@mimeType attribute
     * @return This RepresentationBase.
     */
    RepresentationBase &mimeType(const std::string &val) { m_mimeType = val; return *this; };
    RepresentationBase &mimeType(std::string &&val) { m_mimeType = std::move(val); return *this; };
    RepresentationBase &mimeType(const std::optional<std::string> &val) { m_mimeType = val; return *this; };
    RepresentationBase &mimeType(std::optional<std::string> &&val) { m_mimeType = std::move(val); return *this; };
    /**@}*/

    // @segmentProfiles

    /** Get the segment profiles list
     *
     * @return The segment profiles list.
     */
    const std::list<std::string> &segmentProfiles() const { return m_segmentProfiles; };

    /**@{*/
    /** Set the segment profiles list
     * @param profiles The list of profiles to set as segment profiles.
     * @return This RepresentationBase.
     */
    RepresentationBase &segmentProfiles(const std::list<std::string> &profiles) { m_segmentProfiles = profiles; return *this; };
    RepresentationBase &segmentProfiles(std::list<std::string> &&profiles) { m_segmentProfiles = std::move(profiles); return *this; };
    /**@}*/

    /**@{*/
    /** Get an iterator referencing the start of the segment profiles list
     *
     * @return An iterator referencing the start of the segment profiles list.
     */
    std::list<std::string>::const_iterator segmentProfilesBegin() const { return m_segmentProfiles.cbegin(); };
    std::list<std::string>::iterator segmentProfilesBegin() { return m_segmentProfiles.begin(); };
    /**@}*/

    /**@{*/
    /** Get an iterator referencing the end of the segment profiles list
     *
     * @return An iterator referencing the end of the segment profiles list.
     */
    std::list<std::string>::const_iterator segmentProfilesEnd() const { return m_segmentProfiles.cend(); };
    std::list<std::string>::iterator segmentProfilesEnd() { return m_segmentProfiles.end(); };
    /**@}*/

    /** Get the segment profile string at an index in the list
     * 
     * This will return the segment profile string at the index given in @a idx (starting at 0). If @a idx fall outside the
     * segment profiles list then a std::out_of_range exception will be thrown.
     *
     * @param idx The index, starting from 0, of the entry to retrieve from the list of segment profiles.
     * @return The segment profile string at list index @a idx.
     * @throw std::out_of_range If @a idx lies outside of the segment profiles list.
     */
    const std::string &segmentProfile(std::list<std::string>::size_type idx) const;

    /**@{*/
    /** Add an entry to the segment profiles list
     * 
     * @param val The string value to add to the segment profiles list.
     * @return This RepresentationBase.
     */
    RepresentationBase &segmentProfilesAdd(const std::string &val) { m_segmentProfiles.push_back(val); return *this; };
    RepresentationBase &segmentProfilesAdd(std::string &&val) { m_segmentProfiles.push_back(std::move(val)); return *this; };
    /**@}*/

    /** Remove an entry to the segment profiles list by value
     *
     * @param val The string value to remove from the segment profiles list.
     * @return This RepresentationBase.
     */
    RepresentationBase &segmentProfilesRemove(const std::string &val);

    /**@{*/
    /** Remove an entry to the segment profiles list by iterator
     *
     * @param it An iterator referencing an entry from the segment profiles list.
     * @return This RepresentationBase.
     */
    RepresentationBase &segmentProfilesRemove(const std::list<std::string>::const_iterator &it);
    RepresentationBase &segmentProfilesRemove(const std::list<std::string>::iterator &it);
    /**@}*/

    // @codecs
    
    /** Check if the @@codecs attribute has a value set
     *
     * @return `true` if the @@codecs attribute has a value set.
     */
    bool hasCodecs() const { return m_codecs.has_value(); };

    /** Get the optional @@codecs attribute value
     *
     * @return The optional @@codecs attribute value.
     */
    const std::optional<Codecs> &codecs() const { return m_codecs; };

    /** Unset the @@codecs attribute value
     *
     * @return This RepresentationBase.
     */
    RepresentationBase &codecs(const std::nullopt_t&) { m_codecs.reset(); return *this; };

    /**@{*/
    /** Set the @@codecs attribute value
     *
     * @param val The value to set for the @@codecs attribute
     * @return This RepresentationBase.
     */
    RepresentationBase &codecs(const Codecs &val) { m_codecs = val; return *this; };
    RepresentationBase &codecs(Codecs &&val) { m_codecs = std::move(val); return *this; };
    RepresentationBase &codecs(const std::optional<Codecs> &val) { m_codecs = val; return *this; };
    RepresentationBase &codecs(std::optional<Codecs> &&val) { m_codecs = std::move(val); return *this; };
    /**@}*/

    // @containerProfiles

    /** Get the container profiles list
     *
     * @return The container profiles list.
     */
    const std::list<std::string> &containerProfiles() const { return m_containerProfiles; };

    /**@{*/
    /** Set the container profiles list
     * @param profiles The list of profiles to set as container profiles.
     * @return This RepresentationBase.
     */
    RepresentationBase &containerProfiles(const std::list<std::string> &profiles) { m_containerProfiles = profiles; return *this; };
    RepresentationBase &containerProfiles(std::list<std::string> &&profiles) { m_containerProfiles = std::move(profiles); return *this; };
    /**@}*/

    /**@{*/
    /** Get an iterator referencing the start of the container profiles list
     *
     * @return An iterator referencing the start of the container profiles list.
     */
    std::list<std::string>::const_iterator containerProfilesBegin() const { return m_containerProfiles.cbegin(); };
    std::list<std::string>::iterator containerProfilesBegin() { return m_containerProfiles.begin(); };
    /**@}*/

    /**@{*/
    /** Get an iterator referencing the end of the container profiles list
     *
     * @return An iterator referencing the end of the container profiles list.
     */
    std::list<std::string>::const_iterator containerProfilesEnd() const { return m_containerProfiles.cend(); };
    std::list<std::string>::iterator containerProfilesEnd() { return m_containerProfiles.end(); };
    /**@}*/

    /** Get the container profile string at an index in the list
     * 
     * This will return the container profile string at the index given in @a idx (starting at 0). If @a idx fall outside the
     * container profiles list then a std::out_of_range exception will be thrown.
     *
     * @param idx The index, starting from 0, of the entry to retrieve from the list of container profiles.
     * @return The container profile string at list index @a idx.
     * @throw std::out_of_range If @a idx lies outside of the container profiles list.
     */
    const std::string &containerProfile(std::list<std::string>::size_type idx) const;

    /**@{*/
    /** Add an entry to the container profiles list
     * 
     * @param val The string value to add to the container profiles list.
     * @return This RepresentationBase.
     */
    RepresentationBase &containerProfilesAdd(const std::string &val) { m_containerProfiles.push_back(val); return *this; };
    RepresentationBase &containerProfilesAdd(std::string &&val) { m_containerProfiles.push_back(std::move(val)); return *this; };
    /**@}*/

    /** Remove an entry to the container profiles list by value
     *
     * @param val The string value to remove from the container profiles list.
     * @return This RepresentationBase.
     */
    RepresentationBase &containerProfilesRemove(const std::string &val);

    /**@{*/
    /** Remove an entry to the container profiles list by iterator
     *
     * @param it An iterator referencing an entry from the container profiles list.
     * @return This RepresentationBase.
     */
    RepresentationBase &containerProfilesRemove(const std::list<std::string>::const_iterator &it);
    RepresentationBase &containerProfilesRemove(const std::list<std::string>::iterator &it);
    /**@}*/

    // @maximumSAPPeriod

    /** Check if the @@maximumSAPPeriod attribute has been set
     *
     * @return `true` if the @@maximumSAPPeriod attribute has been set, otherwise `false`.
     */
    bool hasMaximumSAPPeriod() const { return m_maximumSAPPeriod.has_value(); };

    /** Get the optional @@maximumSAPPeriod attribute value
     *
     * @return The optional @@maximumSAPPeriod attribute value.
     */
    const std::optional<double> &maximumSAPPeriod() const { return m_maximumSAPPeriod; };

    /** Unset the optional @@maximumSAPPeriod attribute value
     *
     * @return This RepresentationBase.
     */
    RepresentationBase &maximumSAPPeriod(const std::nullopt_t&) { m_maximumSAPPeriod.reset(); return *this; };

    /**@{*/
    /** Set the @@maximumSAPPeriod attribute value
     *
     * @param val The value to set in the @@maximumSAPPeriod attribute.
     * @return This RepresentationBase.
     */
    RepresentationBase &maximumSAPPeriod(double val) { m_maximumSAPPeriod = val; return *this; };
    RepresentationBase &maximumSAPPeriod(const std::optional<double> &val) { m_maximumSAPPeriod = val; return *this; };
    RepresentationBase &maximumSAPPeriod(std::optional<double> &&val) { m_maximumSAPPeriod = std::move(val); return *this; };
    /**@}*/

    // @startWithSAP

    /** Check if the @@startWithSAP attribute has a value set
     *
     * @return `true` if the @@startWithSAP attribute has a value set.
     */
    bool hasStartWithSAP() const { return m_startWithSAP.has_value(); };

    /** Get the optional @@startWithSAP attribute value
     *
     * @return The optional @@startWithSAP attribute value.
     */
    const std::optional<SAP> &startWithSAP() const { return m_startWithSAP; };

    /** Unset the @@startWithSAP attribute value
     *
     * @return This RepresentationBase.
     */
    RepresentationBase &startWithSAP(const std::nullopt_t&) { m_startWithSAP.reset(); return *this; };

    /**@{*/
    /** Set the @@startWithSAP attribute value
     *
     * @param val The starts with SAP value to set in the @@startWithSAP attribute.
     * @return This RepresentationBase.
     */
    RepresentationBase &startWithSAP(const SAP &val) { m_startWithSAP = val; return *this; };
    RepresentationBase &startWithSAP(SAP &&val) { m_startWithSAP = std::move(val); return *this; };
    RepresentationBase &startWithSAP(const std::optional<SAP> &val) { m_startWithSAP = val; return *this; };
    RepresentationBase &startWithSAP(std::optional<SAP> &&val) { m_startWithSAP = std::move(val); return *this; };
    /**@}*/

    // @maxPlayoutRate

    /** Check if the @@maxPlayoutRate attribute has been set
     *
     * @return `true` if the @@maxPlayoutRate attribute has been set, otherwise `false`.
     */
    bool hasMaxPlayoutRate() const { return m_maxPlayoutRate.has_value(); };

    /** Get the optional @@maxPlayoutRate attribute value
     *
     * @return The optional @@maxPlayoutRate attribute value.
     */
    const std::optional<double> &maxPlayoutRate() const { return m_maxPlayoutRate; };

    /** Unset the optional @@maxPlayoutRate attribute value
     *
     * @return This RepresentationBase.
     */
    RepresentationBase &maxPlayoutRate(const std::nullopt_t&) { m_maxPlayoutRate.reset(); return *this; };

    /**@{*/
    /** Set the @@maxPlayoutRate attribute value
     *
     * @param val The value to set in the @@maxPlayoutRate attribute.
     * @return This RepresentationBase.
     */
    RepresentationBase &maxPlayoutRate(double val) { m_maxPlayoutRate = val; return *this; };
    RepresentationBase &maxPlayoutRate(const std::optional<double> &val) { m_maxPlayoutRate = val; return *this; };
    RepresentationBase &maxPlayoutRate(std::optional<double> &&val) { m_maxPlayoutRate = std::move(val); return *this; };
    /**@}*/

    // @codingDependency

    /** Check if the @@codingDependency attribute has been set
     *
     * @return `true` if the @@codingDependency attribute has been set, otherwise `false`.
     */
    bool hasCodingDependency() const { return m_codingDependency.has_value(); };

    /** Get the optional @@codingDependency attribute value
     *
     * @return The optional @@codingDependency attribute value.
     */
    const std::optional<bool> &codingDependency() const { return m_codingDependency; };

    /** Unset the optional @@codingDependency attribute value
     *
     * @return This RepresentationBase.
     */
    RepresentationBase &codingDependency(const std::nullopt_t&) { m_codingDependency.reset(); return *this; };

    /**@{*/
    /** Set the @@codingDependency attribute value
     *
     * @param val The value to set in the @@codingDependency attribute.
     * @return This RepresentationBase.
     */
    RepresentationBase &codingDependency(bool val) { m_codingDependency = val; return *this; };
    RepresentationBase &codingDependency(const std::optional<bool> &val) { m_codingDependency = val; return *this; };
    RepresentationBase &codingDependency(std::optional<bool> &&val) { m_codingDependency = std::move(val); return *this; };
    /**@}*/

    // @scanType

    /** Check if the @@scanType attribute has a value set
     *
     * @return `true` if the @@scanType attribute has a value set.
     */
    bool hasScanType() const { return m_scanType.has_value(); };

    /** Get the optional @@scanType attribute value
     *
     * @return The optional @@scanType attribute value.
     */
    const std::optional<VideoScan> &scanType() const { return m_scanType; };

    /** Unset the @@scanType attribute value
     *
     * @return This RepresentationBase.
     */
    RepresentationBase &scanType(const std::nullopt_t&) { m_scanType.reset(); return *this; };

    /**@{*/
    /** Set the @@scanType attribute value
     *
     * @param val The video scan type value to set in the @@scanType attribute.
     * @return This RepresentationBase.
     */
    RepresentationBase &scanType(const VideoScan &val) { m_scanType = val; return *this; };
    RepresentationBase &scanType(VideoScan &&val) { m_scanType = std::move(val); return *this; };
    RepresentationBase &scanType(const std::optional<VideoScan> &val) { m_scanType = val; return *this; };
    RepresentationBase &scanType(std::optional<VideoScan> &&val) { m_scanType = std::move(val); return *this; };
    /**@}*/

    // @selectionPriority

    /** Get the @@selectionPriority attribute value
     *
     * @return The @@selectionPriority attribute value.
     */
    unsigned int selectionPriority() const { return m_selectionPriority; };

    /** Set the @@selectionPriority attribute value
     *
     * If this value is set to the default of 1, then it will be omitted from XML output.
     *
     * @param val Set the @@selectionPriority attribute value to @a val.
     * @return This RepresentationBase.
     */
    RepresentationBase &selectionPriority(unsigned int val) { m_selectionPriority = val; return *this; };

    // @tag

    /** Check if the @@tag attribute has a value set
     *
     * @return `true` if the @@tag attribute has a value set.
     */
    bool hasTag() const { return m_tag.has_value(); };

    /** Get the optional @@tag attribute value
     *
     * @return The optional @@tag attribute value.
     */
    const std::optional<std::string> &tag() const { return m_tag; };

    /** Unset the @@tag attribute value
     *
     * @return This RepresentationBase.
     */
    RepresentationBase &tag(const std::nullopt_t&) { m_tag.reset(); return *this; };

    /**@{*/
    /** Set the @@tag attribute value
     *
     * @param val The value to set for the @@tag attribute
     * @return This RepresentationBase.
     */
    RepresentationBase &tag(const std::string &val) { m_tag = val; return *this; };
    RepresentationBase &tag(std::string &&val) { m_tag = std::move(val); return *this; };
    RepresentationBase &tag(const std::optional<std::string> &val) { m_tag = val; return *this; };
    RepresentationBase &tag(std::optional<std::string> &&val) { m_tag = std::move(val); return *this; };
    /**@}*/

    // FramePacking children

    /** Get the frame packings list
     *
     * @return The frame packings list.
     */
    const std::list<Descriptor> &framePackings() const { return m_framePackings; };

    /**@{*/
    /** Set the frame packings list
     * @param packings The list of frame packings to set as the frame packings list.
     * @return This RepresentationBase.
     */
    RepresentationBase &framePackings(const std::list<Descriptor> &packings) { m_framePackings = packings; return *this; };
    RepresentationBase &framePackings(std::list<Descriptor> &&packings) { m_framePackings = std::move(packings); return *this; };
    /**@}*/

    /**@{*/
    /** Get an iterator referencing the start of the frame packings list
     *
     * @return An iterator referencing the start of the frame packings list.
     */
    std::list<Descriptor>::const_iterator framePackingsBegin() const { return m_framePackings.cbegin(); };
    std::list<Descriptor>::iterator framePackingsBegin() { return m_framePackings.begin(); };
    /**@}*/

    /**@{*/
    /** Get an iterator referencing the end of the frame packings list
     *
     * @return An iterator referencing the end of the frame packings list.
     */
    std::list<Descriptor>::const_iterator framePackingsEnd() const { return m_framePackings.cend(); };
    std::list<Descriptor>::iterator framePackingsEnd() { return m_framePackings.end(); };
    /**@}*/

    /** Get the container profile string at an index in the list
     * 
     * This will return the frame packing descriptor at the index given in @a idx (starting at 0). If @a idx fall outside the
     * frame packings list then a std::out_of_range exception will be thrown.
     *
     * @param idx The index, starting from 0, of the entry to retrieve from the list of frame packings.
     * @return The frame packing descriptor at list index @a idx.
     * @throw std::out_of_range If @a idx lies outside of the frame packings list.
     */
    const Descriptor &framePacking(std::list<Descriptor>::size_type idx) const;

    /**@{*/
    /** Add an entry to the frame packings list
     * 
     * @param val The frame packing descriptor to add to the frame packings list.
     * @return This RepresentationBase.
     */
    RepresentationBase &framePackingsAdd(const Descriptor &val) { m_framePackings.push_back(val); return *this; };
    RepresentationBase &framePackingsAdd(Descriptor &&val) { m_framePackings.push_back(std::move(val)); return *this; };
    /**@}*/

    /** Remove an entry to the frame packings list by value
     *
     * @param val The frame packing descriptor to remove from the frame packings list.
     * @return This RepresentationBase.
     */
    RepresentationBase &framePackingsRemove(const Descriptor &val);

    /**@{*/
    /** Remove an entry to the frame packings list by iterator
     *
     * @param it An iterator referencing an entry from the frame packings list.
     * @return This RepresentationBase.
     */
    RepresentationBase &framePackingsRemove(const std::list<Descriptor>::const_iterator &it);
    RepresentationBase &framePackingsRemove(const std::list<Descriptor>::iterator &it);
    /**@}*/

    // AudioChannelConfiguration children

    /** Get the audio channel configurations list
     *
     * @return The audio channel configurations list.
     */
    const std::list<Descriptor> &audioChannelConfigurations() const { return m_audioChannelConfigurations; };

    /**@{*/
    /** Set the audio channel configurations list
     * @param packings The list of audio channel configurations to set as the audio channel configurations list.
     * @return This RepresentationBase.
     */
    RepresentationBase &audioChannelConfigurations(const std::list<Descriptor> &packings) { m_audioChannelConfigurations = packings; return *this; };
    RepresentationBase &audioChannelConfigurations(std::list<Descriptor> &&packings) { m_audioChannelConfigurations = std::move(packings); return *this; };
    /**@}*/

    /**@{*/
    /** Get an iterator referencing the start of the audio channel configurations list
     *
     * @return An iterator referencing the start of the audio channel configurations list.
     */
    std::list<Descriptor>::const_iterator audioChannelConfigurationsBegin() const { return m_audioChannelConfigurations.cbegin(); };
    std::list<Descriptor>::iterator audioChannelConfigurationsBegin() { return m_audioChannelConfigurations.begin(); };
    /**@}*/

    /**@{*/
    /** Get an iterator referencing the end of the audio channel configurations list
     *
     * @return An iterator referencing the end of the audio channel configurations list.
     */
    std::list<Descriptor>::const_iterator audioChannelConfigurationsEnd() const { return m_audioChannelConfigurations.cend(); };
    std::list<Descriptor>::iterator audioChannelConfigurationsEnd() { return m_audioChannelConfigurations.end(); };
    /**@}*/

    /** Get the container profile string at an index in the list
     * 
     * This will return the audio channel configuration descriptor at the index given in @a idx (starting at 0). If @a idx falls
     * outside the audio channel configurations list then a std::out_of_range exception will be thrown.
     *
     * @param idx The index, starting from 0, of the entry to retrieve from the list of audio channel configurations.
     * @return The audio channel configuration descriptor at list index @a idx.
     * @throw std::out_of_range If @a idx lies outside of the audio channel configurations list.
     */
    const Descriptor &audioChannelConfiguration(std::list<Descriptor>::size_type idx) const;

    /**@{*/
    /** Add an entry to the audio channel configurations list
     * 
     * @param val The audio channel configuration descriptor to add to the audio channel configurations list.
     * @return This RepresentationBase.
     */
    RepresentationBase &audioChannelConfigurationsAdd(const Descriptor &val) {
        m_audioChannelConfigurations.push_back(val); return *this;
    };
    RepresentationBase &audioChannelConfigurationsAdd(Descriptor &&val) {
        m_audioChannelConfigurations.push_back(std::move(val)); return *this;
    };
    /**@}*/

    /** Remove an entry to the audio channel configurations list by value
     *
     * @param val The audio channel configuration descriptor to remove from the audio channel configurations list.
     * @return This RepresentationBase.
     */
    RepresentationBase &audioChannelConfigurationsRemove(const Descriptor &val);

    /**@{*/
    /** Remove an entry to the audio channel configurations list by iterator
     *
     * @param it An iterator referencing an entry from the audio channel configurations list.
     * @return This RepresentationBase.
     */
    RepresentationBase &audioChannelConfigurationsRemove(const std::list<Descriptor>::const_iterator &it);
    RepresentationBase &audioChannelConfigurationsRemove(const std::list<Descriptor>::iterator &it);
    /**@}*/

    // ContentProtection children

    /** Get the content protections list
     *
     * @return The content protections list.
     */
    const std::list<ContentProtection> &contentProtections() const { return m_contentProtections; };

    /**@{*/
    /** Set the content protections list
     * @param protections The list of content protections to set as the content protections list.
     * @return This RepresentationBase.
     */
    RepresentationBase &contentProtections(const std::list<ContentProtection> &protections) {
        m_contentProtections = protections; return *this;
    };
    RepresentationBase &contentProtections(std::list<ContentProtection> &&protections) {
        m_contentProtections = std::move(protections); return *this;
    };
    /**@}*/

    /**@{*/
    /** Get an iterator referencing the start of the content protections list
     *
     * @return An iterator referencing the start of the content protections list.
     */
    std::list<ContentProtection>::const_iterator contentProtectionsBegin() const { return m_contentProtections.cbegin(); };
    std::list<ContentProtection>::iterator contentProtectionsBegin() { return m_contentProtections.begin(); };
    /**@}*/

    /**@{*/
    /** Get an iterator referencing the end of the content protections list
     *
     * @return An iterator referencing the end of the content protections list.
     */
    std::list<ContentProtection>::const_iterator contentProtectionsEnd() const { return m_contentProtections.cend(); };
    std::list<ContentProtection>::iterator contentProtectionsEnd() { return m_contentProtections.end(); };
    /**@}*/

    /** Get the container profile string at an index in the list
     * 
     * This will return the content protection at the index given in @a idx (starting at 0). If @a idx falls
     * outside the content protections list then a std::out_of_range exception will be thrown.
     *
     * @param idx The index, starting from 0, of the entry to retrieve from the list of content protections.
     * @return The content protection at list index @a idx.
     * @throw std::out_of_range If @a idx lies outside of the content protections list.
     */
    const ContentProtection &contentProtection(std::list<ContentProtection>::size_type idx) const;

    /**@{*/
    /** Add an entry to the content protections list
     * 
     * @param val The content protection to add to the content protections list.
     * @return This RepresentationBase.
     */
    RepresentationBase &contentProtectionsAdd(const ContentProtection &val) {
        m_contentProtections.push_back(val); return *this;
    };
    RepresentationBase &contentProtectionsAdd(ContentProtection &&val) {
        m_contentProtections.push_back(std::move(val)); return *this;
    };
    /**@}*/

    /** Remove an entry to the content protections list by value
     *
     * @param val The content protection to remove from the content protections list.
     * @return This RepresentationBase.
     */
    RepresentationBase &contentProtectionsRemove(const ContentProtection &val);

    /**@{*/
    /** Remove an entry to the content protections list by iterator
     *
     * @param it An iterator referencing an entry from the content protections list.
     * @return This RepresentationBase.
     */
    RepresentationBase &contentProtectionsRemove(const std::list<ContentProtection>::const_iterator &it);
    RepresentationBase &contentProtectionsRemove(const std::list<ContentProtection>::iterator &it);
    /**@}*/

    // OutputProtection child

    /** Check if the %OutputProtection element has a value set
     *
     * @return `true` if the %OutputProtection element has a value set.
     */
    bool hasOutputProtection() const { return m_outputProtection.has_value(); };

    /** Get the optional %OutputProtection element value
     *
     * @return The optional %OutputProtection element value.
     */
    const std::optional<Descriptor> &outputProtection() const { return m_outputProtection; };

    /** Unset the %OutputProtection element value
     *
     * @return This RepresentationBase.
     */
    RepresentationBase &outputProtection(const std::nullopt_t&) { m_outputProtection.reset(); return *this; };

    /**@{*/
    /** Set the %OutputProtection element value
     *
     * @param val The output protection descriptor to set in the %OutputProtection element.
     * @return This RepresentationBase.
     */
    RepresentationBase &outputProtection(const Descriptor &val) { m_outputProtection = val; return *this; };
    RepresentationBase &outputProtection(Descriptor &&val) { m_outputProtection = std::move(val); return *this; };
    RepresentationBase &outputProtection(const std::optional<Descriptor> &val) { m_outputProtection = val; return *this; };
    RepresentationBase &outputProtection(std::optional<Descriptor> &&val) { m_outputProtection = std::move(val); return *this; };
    /**@}*/

    // EssentialProperty children
    // SupplementalProperty children
    // InbandEventStream children
    // Switching children
    // RandomAccess children
    // GroupLabel children
    // Label children
    // ProducerReferenceTime children
    // ContentPopularityRate children
    // Resync children

///@cond PROTECTED
protected:
    RepresentationBase(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

///@endcond PROTECTED

private:
    // RepresentationBase attributes (ISO 23009-1:2022 Clause 5.3.7.3)
    std::list<URI>              m_profiles;
    std::optional<unsigned int> m_width;
    std::optional<unsigned int> m_height;
    std::optional<Ratio>        m_sar;
    std::optional<FrameRate>    m_frameRate;
    std::list<unsigned int>     m_audioSamplingRates; // if present must contain 1 or 2 entries
    std::optional<std::string>  m_mimeType;
    std::list<std::string>      m_segmentProfiles;
    std::optional<Codecs>       m_codecs;
    std::list<std::string>      m_containerProfiles;
    std::optional<double>       m_maximumSAPPeriod;
    std::optional<SAP>          m_startWithSAP;
    std::optional<double>       m_maxPlayoutRate;
    std::optional<bool>         m_codingDependency;
    std::optional<VideoScan>    m_scanType;
    unsigned int                m_selectionPriority; // default = 1
    std::optional<std::string>  m_tag;

    // RepresentationBase child elements (ISO 23009-1:2022 Clause 5.3.7.3)
    std::list<Descriptor>            m_framePackings;
    std::list<Descriptor>            m_audioChannelConfigurations;
    std::list<ContentProtection>     m_contentProtections;
    std::optional<Descriptor>        m_outputProtection;
    std::list<Descriptor>            m_essentialProperties;
    std::list<Descriptor>            m_supplementalProperties;
    std::list<EventStream>           m_inbandEventStreams;
    std::list<Switching>             m_switchings;
    std::list<RandomAccess>          m_randomAccesses;
    std::list<Label>                 m_groupLabels;
    std::list<Label>                 m_labels;
    std::list<ProducerReferenceTime> m_producerReferenceTimes;
    std::list<ContentPopularityRate> m_contentPopularityRates;
    std::list<Resync>                m_resyncs;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_REPRESENTATION_BASE_HH_*/

