#ifndef _BBC_PARSE_DASH_MPD_ADAPTATION_SET_HH_
#define _BBC_PARSE_DASH_MPD_ADAPTATION_SET_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: AdaptationSet class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
 *            David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <chrono>
#include <list>
#include <optional>
#include <string>
#include <unordered_set>

#include "macros.hh"
#include "BaseURL.hh"
#include "ContentComponent.hh"
#include "Descriptor.hh"
#include "Representation.hh"
#include "RepresentationBase.hh"
#include "RFC6838ContentType.hh"
#include "Ratio.hh"
#include "FrameRate.hh"
#include "SAP.hh"
#include "SegmentAvailability.hh"
#include "SegmentBase.hh"
#include "SegmentList.hh"
#include "SegmentTemplate.hh"
#include "URI.hh"
#include "XLink.hh"

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

/**
 * @brief AdaptationSet class
 * @headerfile libmpd++/AdaptationSet.hh <libmpd++/AdaptationSet.hh>
 *
 * This is the container for the AdaptationSet element from an MPD, and follows the %AdaptationSetType from the %DASH %MPD %XML
 * schema found in ISO 23009-1:2022 Clause 5.3.3.3.
 *
 * The AdaptationSet also allows the application to mark child Representations as "selected". The selected set of Representations
 * can then be queried to find out the availability of the next media segments or to find the initialization segments associated
 * with those representations.
 */
class LIBMPDPP_PUBLIC_API AdaptationSet : public RepresentationBase {
public:
    using time_type = std::chrono::system_clock::time_point; ///< Date-time type
    using duration_type = std::chrono::microseconds;         ///< Time duration type

    /**
     * Default constructor
     *
     * Creates an empty AdaptationSet object which can be attached to a @ref Period.
     */
    AdaptationSet();

    /**
     * Copy constructor
     *
     * Creates a new AdaptationSet object which is a copy of @p other.
     *
     * @param other The AdaptationSet object to copy.
     */
    AdaptationSet(const AdaptationSet &other);

    /**
     * Move constructor
     *
     * Creates a new AdaptationSet object which transfers the resources from @p other.
     *
     * @param other The AdaptationSet object to move.
     */
    AdaptationSet(AdaptationSet &&other);

    /**
     * Destructor
     */
    virtual ~AdaptationSet() {};

    /**
     * Copy operator
     *
     * Copies the values from @p other into this AdaptationSet object.
     *
     * @param other The AdaptationSet object to copy.
     * @return This AdaptationSet object.
     */
    AdaptationSet &operator=(const AdaptationSet &other);

    /**
     * Move operator
     *
     * Transfers the resources from @p other into this AdaptationSet object.
     *
     * @param other The AdaptationSet object to move.
     * @return This AdaptationSet object.
     */
    AdaptationSet &operator=(AdaptationSet &&other);

    /**
     * Equality operator
     *
     * Compare the value of this AdaptationSet to @p other.
     *
     * @param other The AdaptationSet object to compare this object to.
     * @return `true` if this AdaptationSet object contains the same values as @p other, otherwise `false`.
     */
    bool operator==(const AdaptationSet &other) const;

    ///@{
    /** Get the MPD this AdaptationSet is attached to
     *
     * @return A pointer to the @ref MPD that this AdaptationSet is attached to (via the parent @ref Period) or `nullptr` if this
     *         object is not attached to an @ref MPD.
     */
    MPD *getMPD();
    const MPD *getMPD() const;
    ///@}

    ///@{
    /** Get the Period this AdaptationSet is attached to
     *
     * @return A pointer to the @ref Period that this AdaptationSet is attached to or `nullptr` if this object is not attached to a
     *         @ref Period.
     */
    Period *getPeriod() { return m_period; };
    const Period *getPeriod() const { return m_period; };
    ///@}

    // @id

    /**
     * Check if the @@id attribute is set
     *
     * @return `true` if the @@id attribute has a value, otherwise `false`.
     */
    bool hasId() const { return m_id.has_value(); };

    /**
     * Get the optional @@id attribute value
     *
     * @return The optional id number.
     */
    const std::optional<unsigned int> &id() const { return m_id; };

    /**
     * Unset the @@id attribute value
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &id(const std::nullopt_t &) { m_id.reset(); return *this;};

    /**
     * Set the @@id attribute value
     *
     * @param id The number to assign this AdaptationSet.
     * @return This AdaptationSet.
     */
    AdaptationSet &id(unsigned int id) { m_id = id; return *this;};

    /**
     * Set the @@id attribute value
     *
     * @param id An optional number to copy into the @@id attribute value.
     * @return This AdaptationSet.
     */
    AdaptationSet &id(const std::optional<unsigned int> &id) { m_id = id; return *this;};

    /**
     * Set the @@id attribute value
     *
     * @param id An optional number to move into the @@id attribute value.
     * @return This AdaptationSet.
     */
    AdaptationSet &id(std::optional<unsigned int> &&id) { m_id = std::move(id);return *this;};

    // @group

    /**
     * Check if the @@group attribute is set
     *
     * @return `true` if the @@group attribute has a value, otherwise `false`.
     */
    bool hasGroup() const { return m_group.has_value(); };

    /**
     * Get the optional @@group attribute value
     *
     * @return The optional group number.
     */
    const std::optional<unsigned int> &group() const { return m_group; };

    /**
     * Unset the @@group attribute value
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &group(const std::nullopt_t &) { m_group.reset(); return *this;};

    /**
     * Set the @@group attribute value
     *
     * @param group The group number to assign this AdaptationSet.
     * @return This AdaptationSet.
     */
    AdaptationSet &group(unsigned int group) { m_group = group; return *this;};

    /**
     * Set the @@group attribute value
     *
     * @param group The optional group number to copy to this AdaptationSet.
     * @return This AdaptationSet.
     */
    AdaptationSet &group(const std::optional<unsigned int> &group) { m_group = group; return *this;};

    /**
     * Set the @@group attribute value
     *
     * @param group The optional group number to move to this AdaptationSet.
     * @return This AdaptationSet.
     */
    AdaptationSet &group(std::optional<unsigned int> &&group) { m_group = std::move(group);return *this;};

    // @lang

    /**
     * Check if the @@lang attribute is set
     *
     * @return `true` if the @@lang attribute has a value, otherwise `false`.
     */
    bool hasLang() const { return m_lang.has_value(); };

    /**
     * Get the optional @@lang attribute value
     *
     * @return The optional language identifier.
     */
    const std::optional<std::string> &lang() const { return m_lang; };

    /**
     * Unset the @@lang attribute value
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &lang(const std::nullopt_t &) { m_lang.reset(); return *this; };

    /**
     * Set the @@lang attribute value (copy)
     *
     * Copies the @p lang value into the @@lang attribute.
     *
     * @param lang The language identifier to set the @@lang attribute to.
     * @return This AdaptationSet.
     */
    AdaptationSet &lang(const std::string &lang) { m_lang = lang; return *this; };

    /**
     * Set the @@lang attribute value (move)
     *
     * Move the @p lang value into the @@lang attribute.
     *
     * @param lang The language identifier to set the @@lang attribute to.
     * @return This AdaptationSet.
     */
    AdaptationSet &lang(std::string &&lang) { m_lang = std::move(lang); return *this; };

    /**
     * Set the @@lang attribute value (optional value copy)
     *
     * Copy the optional @p lang value as the setting for the @@lang attribute.
     *
     * @param lang The optional language identifier to set the @@lang attribute to.
     * @return This AdaptationSet.
     */
    AdaptationSet &lang(const std::optional<std::string> &lang) { m_lang = lang; return *this; };

    /**
     * Set the @@lang attribute value (optional value move)
     *
     * Move the optional @p lang value as the setting for the @@lang attribute.
     *
     * @param lang The optional language identifier to set the @@lang attribute to.
     * @return This AdaptationSet.
     */
    AdaptationSet &lang(std::optional<std::string> &&lang) { m_lang = std::move(lang); return *this; };

    // @contentType

    /**
     * Check if the @@contentType attribute is set
     *
     * @return `true` if the @@contentType attribute has a value, otherwise `false`.
     */
    bool hasContentType() const { return m_contentType.has_value(); };

    /**
     * Get the optional @@contentType attribute value
     *
     * @return The optional RFC6838 content type.
     */
    const std::optional<RFC6838ContentType> &contentType() const {return m_contentType;};

    /**
     * Unset the @@contentType attribute value
     *
     * Removes any value currently set for the @@contentType attribute.
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &contentType(const std::nullopt_t &) { m_contentType.reset(); return *this; };

    /**
     * Set the @@contentType attribute value (copy)
     *
     * Set the @@contentType attribute to a copy of the @p content_type value.
     *
     * @param content_type The RFC6838 content type to set the @@contentType attribute to.
     * @return This AdaptationSet.
     */
    AdaptationSet &contentType(const RFC6838ContentType &content_type) {m_contentType = content_type; return *this;};

    /**
     * Set the @@contentType attribute value (move)
     *
     * Move the RFC6838 content type value, @p content_type, into the @@contentType attribute.
     *
     * @param content_type The RFC6838 content type to move to the @@contentType attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &contentType(RFC6838ContentType &&content_type) {m_contentType = std::move(content_type); return *this;};

    /**
     * Set the @@contentType attribute value (optional value copy)
     *
     * Copy the optional value from @p content_type to the @@contentType attribute.
     *
     * @param content_type The optional RFC6838 content type value to copy into the @@contentType attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &contentType(const std::optional<RFC6838ContentType> &content_type) { m_contentType = content_type; return *this;};

    /**
     * Set the @@contentType attribute value (optional value move)
     *
     * Move the optional value from @p content_type into the @@contentType attribute.
     *
     * @param content_type The optional RFC6838 content type value to move into the @@contentType attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &contentType(std::optional<RFC6838ContentType> &&content_type) { m_contentType = std::move(content_type); return *this;};

    // @par
    
    /**
     * Check if the @@par attribute is set
     *
     * @return `true` if the @@par attribute has a value, otherwise `false`.
     */
    bool hasPar() const { return m_par.has_value(); };

    /**
     * Get the optional @@par attribute value
     *
     * @return The optional picture aspect ratio.
     */
    const std::optional<Ratio> &par() const {return m_par;};

    /**
     * Unset the @@par attribute value
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &par(const std::nullopt_t &) { m_par.reset(); return *this; };

    /**
     * Set the @@par attribute value (copy)
     *
     * Copy the Ratio @p par as the value of the @@par attribute.
     *
     * @param par The picture aspect ratio to copy into the @@par attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &par(const Ratio &par) {m_par = par; return *this;};

    /**
     * Set the @@par attribute value (move)
     *
     * Move the Ratio @p par into the value of the @@par attribute.
     *
     * @param par The picture aspect ratio to move into the @@par attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &par(Ratio &&par) {m_par = std::move(par); return *this;};

    /**
     * Set the @@par attribute value (optional value copy)
     *
     * Copy the optional Ratio @p par into the value of the @@par attribute.
     *
     * @param par The optional picture aspect ratio to copy into the @@par attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &par(const std::optional<Ratio> &par) { m_par = par; return *this;};

    /**
     * Set the @@par attribute value (optional value move)
     *
     * Move the optional Ratio @p par into the value of the @@par attribute.
     *
     * @param par The optional picture aspect ratio to move into the @@par attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &par(std::optional<Ratio> &&par) { m_par = std::move(par); return *this;};

    // @minBandwidth;

    /**
     * Check if the @@minBandwidth attribute is set
     *
     * @return `true` if the @@minBandwidth attribute has a value, otherwise `false`.
     */
    bool hasMinBandwidth() const { return m_minBandwidth.has_value(); };

    /**
     * Get the optional @@minBandwidth attribute value
     *
     * @return The optional minimum bandwidth.
     */
    const std::optional<unsigned int> &minBandwidth() const { return m_minBandwidth; };

    /**
     * Unset the @@minBandwidth attribute value
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &minBandwidth(const std::nullopt_t &) { m_minBandwidth.reset(); return *this;};

    /**
     * Set the @@minBandwidth attribute value
     *
     * @param min_bandwidth The minimum bandwidth value to set for the @@minBandwidth attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &minBandwidth(unsigned int min_bandwidth) { m_minBandwidth = min_bandwidth; return *this;};

    /**
     * Set the @@minBandwidth attribute value (optional value copy)
     *
     * Copy the optional @p min_bandwidth into the value of the @@minBandwidth attribute.
     *
     * @param min_bandwidth The optional minimum bandwidth to copy into the @@minBandwidth attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &minBandwidth(const std::optional<unsigned int> &min_bandwidth) { m_minBandwidth = min_bandwidth; return *this;};

    /**
     * Set the @@minBandwidth attribute value (optional value move)
     *
     * Move the optional @p min_bandwidth into the @@minBandwidth attribute.
     *
     * @param min_bandwidth The optional minimum bandwidth to move into the @@minBandwidth attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &minBandwidth(std::optional<unsigned int> &&min_bandwidth) { m_minBandwidth = std::move(min_bandwidth);return *this;};

    // @maxBandwidth

    /**
     * Check if the @@maxBandwidth attribute is set
     *
     * @return `true` if the @@maxBandwidth attribute has a value, otherwise `false`.
     */
    bool hasMaxBandwidth() const { return m_maxBandwidth.has_value(); };

    /**
     * Get the optional @@maxBandwidth attribute value
     *
     * @return The optional maximum bandwidth.
     */
    const std::optional<unsigned int> &maxBandwidth() const { return m_maxBandwidth; };

    /**
     * Unset the @@maxBandwidth attribute value
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &maxBandwidth(const std::nullopt_t &) { m_maxBandwidth.reset(); return *this;};

    /**
     * Set the @@maxBandwidth attribute value
     *
     * @param max_bandwidth The maximum bandwidth value to set for the @@maxBandwidth attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &maxBandwidth(unsigned int max_bandwidth) { m_maxBandwidth = max_bandwidth; return *this;};

    /**
     * Set the @@maxBandwidth attribute value (optional value copy)
     *
     * Copy the optional @p max_bandwidth into the value of the @@maxBandwidth attribute.
     *
     * @param max_bandwidth The optional maximum bandwidth to copy into the @@maxBandwidth attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &maxBandwidth(const std::optional<unsigned int> &max_bandwidth) { m_maxBandwidth = max_bandwidth; return *this;};

    /**
     * Set the @@maxBandwidth attribute value (optional value move)
     *
     * Move the optional @p max_bandwidth into the @@maxBandwidth attribute.
     *
     * @param max_bandwidth The optional maximum bandwidth to move into the @@maxBandwidth attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &maxBandwidth(std::optional<unsigned int> &&max_bandwidth) { m_maxBandwidth = std::move(max_bandwidth);return *this;};

    // @minWidth

    /**
     * Check if the @@minWidth attribute is set
     *
     * @return `true` if the @@minWidth attribute has a value, otherwise `false`.
     */
    bool hasMinWidth() const { return m_minWidth.has_value(); };

    /**
     * Get the optional @@minWidth attribute value
     *
     * @return The optional minimum video width.
     */
    const std::optional<unsigned int> &minWidth() const { return m_minWidth; };

    /**
     * Unset the @@minWidth attribute value
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &minWidth(const std::nullopt_t &) { m_minWidth.reset(); return *this;};

    /**
     * Set the @@minWidth attribute value
     *
     * @param min_width The minimum video width value to set for the @@minWidth attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &minWidth(unsigned int min_width) { m_minWidth = min_width; return *this;};

    /**
     * Set the @@minWidth attribute value (optional value copy)
     *
     * Copy the optional @p min_width into the value of the @@minWidth attribute.
     *
     * @param min_width The optional minimum video width to copy into the @@minWidth attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &minWidth(const std::optional<unsigned int> &min_width) { m_minWidth = min_width; return *this;};

    /**
     * Set the @@minWidth attribute value (optional value move)
     *
     * Move the optional @p min_width into the @@minWidth attribute.
     *
     * @param min_width The optional minimum video width to move into the @@minWidth attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &minWidth(std::optional<unsigned int> &&min_width) { m_minWidth = std::move(min_width);return *this;};

    // @maxWidth

    /**
     * Check if the @@maxWidth attribute is set
     *
     * @return `true` if the @@maxWidth attribute has a value, otherwise `false`.
     */
    bool hasMaxWidth() const { return m_maxWidth.has_value(); };

    /**
     * Get the optional @@maxWidth attribute value
     *
     * @return The optional maximum video width.
     */
    const std::optional<unsigned int> &maxWidth() const { return m_maxWidth; };

    /**
     * Unset the @@maxWidth attribute value
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &maxWidth(const std::nullopt_t &) { m_maxWidth.reset(); return *this;};

    /**
     * Set the @@maxWidth attribute value
     *
     * @param max_width The maximum video width value to set for the @@maxWidth attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &maxWidth(unsigned int max_width) { m_maxWidth = max_width; return *this;};

    /**
     * Set the @@maxWidth attribute value (optional value copy)
     *
     * Copy the optional @p max_width into the value of the @@maxWidth attribute.
     *
     * @param max_width The optional maximum video width to copy into the @@maxWidth attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &maxWidth(const std::optional<unsigned int> &max_width) { m_maxWidth = max_width; return *this;};

    /**
     * Set the @@maxWidth attribute value (optional value move)
     *
     * Move the optional @p max_width into the @@maxWidth attribute.
     *
     * @param max_width The optional maximum video width to move into the @@maxWidth attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &maxWidth(std::optional<unsigned int> &&max_width) { m_maxWidth = std::move(max_width);return *this;};

    // @minHeight

    /**
     * Check if the @@minHeight attribute is set
     *
     * @return `true` if the @@minHeight attribute has a value, otherwise `false`.
     */
    bool hasMinHeight() const { return m_minHeight.has_value(); };

    /**
     * Get the optional @@minHeight attribute value
     *
     * @return The optional minimum video height.
     */
    const std::optional<unsigned int> &minHeight() const { return m_minHeight; };

    /**
     * Unset the @@minHeight attribute value
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &minHeight(const std::nullopt_t &) { m_minHeight.reset(); return *this;};

    /**
     * Set the @@minHeight attribute value
     *
     * @param min_height The minimum video height value to set for the @@minHeight attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &minHeight(unsigned int min_height) { m_minHeight = min_height; return *this;};

    /**
     * Set the @@minHeight attribute value (optional value copy)
     *
     * Copy the optional @p min_height into the value of the @@minHeight attribute.
     *
     * @param min_height The optional minimum video height to copy into the @@minHeight attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &minHeight(const std::optional<unsigned int> &min_height) { m_minHeight = min_height; return *this;};

    /**
     * Set the @@minHeight attribute value (optional value move)
     *
     * Move the optional @p min_height into the @@minHeight attribute.
     *
     * @param min_height The optional minimum video height to move into the @@minHeight attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &minHeight(std::optional<unsigned int> &&min_height) { m_minHeight = std::move(min_height);return *this;};

    // @maxHeight

    /**
     * Check if the @@maxHeight attribute is set
     *
     * @return `true` if the @@maxHeight attribute has a value, otherwise `false`.
     */
    bool hasMaxHeight() const { return m_maxHeight.has_value(); };

    /**
     * Get the optional @@maxHeight attribute value
     *
     * @return The optional maximum video height.
     */
    const std::optional<unsigned int> &maxHeight() const { return m_maxHeight; };

    /**
     * Unset the @@maxHeight attribute value
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &maxHeight(const std::nullopt_t &) { m_maxHeight.reset(); return *this;};

    /**
     * Set the @@maxHeight attribute value
     *
     * @param max_height The maximum video height value to set for the @@maxHeight attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &maxHeight(unsigned int max_height) { m_maxHeight = max_height; return *this;};

    /**
     * Set the @@maxHeight attribute value (optional value copy)
     *
     * Copy the optional @p max_height into the value of the @@maxHeight attribute.
     *
     * @param max_height The optional maximum video height to copy into the @@maxHeight attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &maxHeight(const std::optional<unsigned int> &max_height) { m_maxHeight = max_height; return *this;};

    /**
     * Set the @@maxHeight attribute value (optional value move)
     *
     * Move the optional @p max_height into the @@maxHeight attribute.
     *
     * @param max_height The optional maximum video height to move into the @@maxHeight attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &maxHeight(std::optional<unsigned int> &&max_height) { m_maxHeight = std::move(max_height);return *this;};

    // @minFrameRate

    /**
     * Check if the @@minFrameRate attribute is set
     *
     * @return `true` if the @@minFrameRate attribute has a value, otherwise `false`.
     */
    bool hasMinFrameRate() const { return m_minFrameRate.has_value(); };

    /**
     * Get the optional @@minFrameRate attribute value
     *
     * @return The optional minimum video frame rate.
     */
    const std::optional<FrameRate> &minFrameRate() const {return m_minFrameRate;};

    /**
     * Unset the @@minFrameRate attribute value
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &minFrameRate(const std::nullopt_t &) { m_minFrameRate.reset(); return *this; };

    /**
     * Set the @@minFrameRate attribute value (copy)
     *
     * Copy the @p min_frame_rate value into the @@minFrameRate attribute.
     *
     * @param min_frame_rate The minimum video frame rate to copy into the @@minFrameRate attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &minFrameRate(const FrameRate &min_frame_rate) {m_minFrameRate = min_frame_rate; return *this;};

    /**
     * Set the @@minFrameRate attribute value (move)
     *
     * Move the @p min_frame_rate value into the @@minFrameRate attribute.
     *
     * @param min_frame_rate The minimum video frame rate to move into the @@minFrameRate attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &minFrameRate(FrameRate &&min_frame_rate) {m_minFrameRate = std::move(min_frame_rate); return *this;};

    /**
     * Set the @@minFrameRate attribute value (optional value copy)
     *
     * Copy the optional @p min_frame_rate into the value of the @@minFrameRate attribute.
     *
     * @param min_frame_rate The optional minimum video frame rate to copy into the @@minFrameRate attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &minFrameRate(const std::optional<FrameRate> &min_frame_rate) { m_minFrameRate = min_frame_rate; return *this;};

    /**
     * Set the @@minFrameRate attribute value (optional value move)
     *
     * Move the optional @p min_frame_rate into the @@minFrameRate attribute.
     *
     * @param min_frame_rate The optional minimum video frame rate to move into the @@minFrameRate attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &minFrameRate(std::optional<FrameRate> &&min_frame_rate) { m_minFrameRate = std::move(min_frame_rate); return *this;};

    // @maxFrameRate

    /**
     * Check if the @@maxFrameRate attribute is set
     *
     * @return `true` if the @@maxFrameRate attribute has a value, otherwise `false`.
     */
    bool hasMaxFrameRate() const { return m_maxFrameRate.has_value(); };

    /**
     * Get the optional @@maxFrameRate attribute value
     *
     * @return The optional maximum video frame rate.
     */
    const std::optional<FrameRate> &maxFrameRate() const {return m_maxFrameRate;};

    /**
     * Unset the @@maxFrameRate attribute value
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &maxFrameRate(const std::nullopt_t &) { m_maxFrameRate.reset(); return *this; };

    /**
     * Set the @@maxFrameRate attribute value (copy)
     *
     * Copy the @p max_frame_rate value into the @@maxFrameRate attribute.
     *
     * @param max_frame_rate The maximum video frame rate to copy into the @@maxFrameRate attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &maxFrameRate(const FrameRate &max_frame_rate) {m_maxFrameRate = max_frame_rate; return *this;};

    /**
     * Set the @@maxFrameRate attribute value (move)
     *
     * Move the @p max_frame_rate value into the @@maxFrameRate attribute.
     *
     * @param max_frame_rate The maximum video frame rate to move into the @@maxFrameRate attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &maxFrameRate(FrameRate &&max_frame_rate) {m_maxFrameRate = std::move(max_frame_rate); return *this;};

    /**
     * Set the @@maxFrameRate attribute value (optional value copy)
     *
     * Copy the optional @p max_frame_rate into the value of the @@maxFrameRate attribute.
     *
     * @param max_frame_rate The optional maximum video frame rate to copy into the @@maxFrameRate attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &maxFrameRate(const std::optional<FrameRate> &max_frame_rate) { m_maxFrameRate = max_frame_rate; return *this;};

    /**
     * Set the @@maxFrameRate attribute value (optional value move)
     *
     * Move the optional @p max_frame_rate into the @@maxFrameRate attribute.
     *
     * @param max_frame_rate The optional maximum video frame rate to move into the @@maxFrameRate attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &maxFrameRate(std::optional<FrameRate> &&max_frame_rate) { m_maxFrameRate = std::move(max_frame_rate); return *this;};

    // @segmentAlignment (deprecated)

    /**
     * Get the @@segmentAlignment attribute value
     *
     * This indicates that all segments in child Representations align without overlap.
     *
     * @return The segment alignment flag.
     */
    bool segmentAlignment() const { return m_segmentAlignment; };

    /**
     * Set the @@segmentAlignment attribute value
     *
     * This indicates that all segments in child Representation entries align without overlap. The default for this attribute is
     * false, therefore setting this value to false will omit it from any XML output.
     *
     * @param segment_alignment The value to set the segment alignment flag (@@segmentAlignment attribute) to.
     * @return This AdaptationSet.
     */
    AdaptationSet &segmentAlignment(bool segment_alignment) { m_segmentAlignment = segment_alignment; return *this;};

    // @subsegmentAlignment (deprecated)

    /**
     * Get the @@subsegmentAlignment attribute value
     *
     * This indicates that all subsegments in child Representations align without overlap.
     *
     * @return The subsegment alignment flag.
     */
    bool subsegmentAlignment() const { return m_subsegmentAlignment; };

    /**
     * Set the @@subsegmentAlignment attribute value
     *
     * This indicates that all subsegments in child Representation entries align without overlap. The default for this attribute is
     * false, therefore setting this value to false will omit it from any XML output.
     *
     * @param subsegment_alignment The value to set the segment alignment flag (@@subsegmentAlignment attribute) to.
     * @return This AdaptationSet.
     */
    AdaptationSet &subsegmentAlignment(bool subsegment_alignment) { m_subsegmentAlignment = subsegment_alignment; return *this;};

    // @subsegmentStartsWithSAP

    /**
     * Get the @@subsegmentStartsWithSAP attribute value
     *
     * @return The @@subsegmentStartsWithSAP attribute value.
     */
    const SAP &subsegmentStartsWithSAP() const {return m_subsegmentStartsWithSAP;};

    /**
     * Set the @@subsegmentStartsWithSAP attribute value (copy)
     *
     * The default for this value is 0, therefore setting this to 0 will cause it to be omitted from any XML output.
     *
     * @param subsegment_starts_with_sap The subsegment start with SAP value to copy to the @@subsegmentStartsWithSAP attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &subsegmentStartsWithSAP(const SAP &subsegment_starts_with_sap) {m_subsegmentStartsWithSAP = subsegment_starts_with_sap; return *this;};

    /**
     * Set the @@subsegmentStartsWithSAP attribute value (move)
     *
     * The default for this value is 0, therefore setting this to 0 will cause it to be omitted from any XML output.
     *
     * @param subsegment_starts_with_sap The subsegment start with SAP value to move to the @@subsegmentStartsWithSAP attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &subsegmentStartsWithSAP(SAP &&subsegment_starts_with_sap) {m_subsegmentStartsWithSAP = std::move(subsegment_starts_with_sap); return *this;};

    // @bitstreamSwitching

    /** Check if the @@bitstreamSwitching attribute is set
     *
     * @return `true` if the @@bitstreamSwitching attribute has a value, otherwise `false`.
     */
    bool hasBitstreamSwitching() const { return m_bitstreamSwitching.has_value(); };

    /** Get the optional @@bitstreamSwitching attribute value
     *
     * @return The optional bitstream switching flag.
     */
    const std::optional<bool> &bitstreamSwitching() const { return m_bitstreamSwitching; };

    /** Unset the @@bitstreamSwitching attribute value
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &bitstreamSwitching(const std::nullopt_t&) { m_bitstreamSwitching.reset(); return *this; };

    /** Set the @@bitstreamSwitching attribute value
     *
     * @param bitstream_switching The bitstream switching flag value to set in the @@bitstreamSwitching attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &bitstreamSwitching(bool bitstream_switching) { m_bitstreamSwitching = bitstream_switching; return *this; };

    /** Set the @@bitstreamSwitching attribute value (optional value copy)
     *
     * Copy the optional @p bitstream_switching into the value of the @@bitstreamSwitching attribute.
     *
     * @param bitstream_switching The optional bitstream switching flag to copy into the @@bitstreamSwitching attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &bitstreamSwitching(const std::optional<bool> &bitstream_switching) { m_bitstreamSwitching = bitstream_switching; return *this; };

    /** Set the @@bitstreamSwitching attribute value (optional value move)
     *
     * Move the optional @p bitstream_switching into the @@bitstreamSwitching attribute.
     *
     * @param bitstream_switching The optional bitstream switching flag to move into the @@bitstreamSwitching attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &bitstreamSwitching(std::optional<bool> &&bitstream_switching) { m_bitstreamSwitching = std::move(bitstream_switching); return *this; };

    // @initializationSetRefs

    /**
     * Get the list of Initialization Set references from the @@initializationSetRefs attribute value
     *
     * @return The list of Initialization Set references.
     */
    const std::list<unsigned int> &initializationSetRefs() const { return m_initializationSetRefs; };

    /**@{*/
    /**
     * Get an iterator pointing to the start of the Initialization Set references list
     *
     * @return An iterator pointing to the start of the Initialization Set references list.
     */
    std::list<unsigned int>::const_iterator initializationSetRefsBegin() const { return m_initializationSetRefs.cbegin(); };
    std::list<unsigned int>::iterator initializationSetRefsBegin() { return m_initializationSetRefs.begin(); };
    /**@}*/

    /**@{*/
    /**
     * Get an iterator pointing to the end of the Initialization Set references list
     *
     * @return An iterator pointing to the start of the Initialization Set references list.
     */
    std::list<unsigned int>::const_iterator initializationSetRefsEnd() const { return m_initializationSetRefs.cend(); };
    std::list<unsigned int>::iterator initializationSetRefsEnd() { return m_initializationSetRefs.end(); };
    /**@}*/

    /** Get the Initialization Set reference at the given list index
     * 
     * @param idx The list index of the Initialization Set reference to retrieve.
     * @return The Initialization Set reference at the list index @p idx.
     * @throw std::out_of_range if @p idx is after the end of the Initialization Set reference list.
     */
    unsigned int initializationSetRef(std::list<unsigned int>::size_type idx) const {
        if (idx >= m_initializationSetRefs.size())
            throw std::out_of_range("AdaptationSet Initialization Set Reference does not exist");
        auto it = m_initializationSetRefs.cbegin();
        while (idx > 0 && it != m_initializationSetRefs.cend()) {it++; idx--;}
        return *it;
    };

    /**
     * Check if the Initialization Set reference list contains a given reference value
     *
     * @param ref The reference value to check.
     * @return `true` if the Initialization Set reference list contains the value of @p ref, otherwise `false`.
     */
    bool initializationSetRefsContains(unsigned int ref) const { return std::find(m_initializationSetRefs.cbegin(), m_initializationSetRefs.cend(), ref) != m_initializationSetRefs.cend(); };

    /**
     * Add an Initialization Set reference to the list of Initialization Set references
     *
     * @param ref The Initialization Set reference value to add.
     * @return This AdaptationSet.
     */
    AdaptationSet &initializationSetRefAdd(unsigned int ref) { m_initializationSetRefs.push_back(ref); return *this; };

    /**
     * Remove an Initialization Set reference from the list of Initialization Set references (by value)
     *
     * @param ref The Initialization Set reference value to remove from the list of Initialization Set references.
     * @return This AdaptationSet.
     */
    AdaptationSet &initializationSetRefRemove(unsigned int ref) { auto it = std::find(m_initializationSetRefs.cbegin(), m_initializationSetRefs.cend(), ref); if (it != m_initializationSetRefs.cend()) m_initializationSetRefs.erase(it); return *this; };

    /**@{*/
    /**
     * Remove an Initialization Set reference from the list of Initialization Set references (by iterator)
     *
     * @param it An iterator pointing to an entry in the list of Initialization Set references.
     * @return This AdaptationSet.
     *
     * @see initializationSetRefsBegin()
     * @see initializationSetRefsEnd()
     */
    AdaptationSet &initializationSetRefRemove(const std::list<unsigned int>::const_iterator &it) { m_initializationSetRefs.erase(it); return *this; };
    AdaptationSet &initializationSetRefRemove(const std::list<unsigned int>::iterator &it) { m_initializationSetRefs.erase(it); return *this; };
    /**@}*/

    /**
     * Set the list of Initialization Set references (copy)
     *
     * Set the list of Initialization Set references to a copy of the list in @p initialization_set_refs. This replaces the current
     * list.
     *
     * @param initialization_set_refs A list of Initialization Set references to copy into this list of Initialization Set
     *                                references.
     * @return This AdaptationSet.
     */
    AdaptationSet &initializationSetRefs(const std::list<unsigned int> &initialization_set_refs) { m_initializationSetRefs = initialization_set_refs; return *this;};

    /**
     * Set the list of Initialization Set references (move)
     *
     * Replace the list of Initialization Set references with the list from @p initialization_set_refs.
     *
     * @param initialization_set_refs A list of Initialization Set references to move into this list of Initialization Set
     *                                references.
     * @return This AdaptationSet.
     */
    AdaptationSet &initializationSetRefs(std::list<unsigned int> &&initialization_set_refs) { m_initializationSetRefs = std::move(initialization_set_refs); return *this;};

    // @initializationPrincipal

    /**
     * Check if the @@initializationPrincipal attribute is set
     *
     * @return `true` if the @@initializationPrincipal attribute has a value, otherwise `false`.
     */
    bool hasInitializationPrincipal() const { return m_initializationPrincipal.has_value(); };

    /**
     * Get the optional @@initializationPrincipal attribute value
     *
     * @return The optional Initialization Principle URL.
     */
    const std::optional<URI> &initializationPrincipal() const { return m_initializationPrincipal; };

    /**
     * Unset the @@initializationPrincipal attribute value
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &initializationPrincipal(const std::nullopt_t &) { m_initializationPrincipal.reset(); return *this; };

    /**
     * Set the @@initializationPrincipal attribute value (copy)
     *
     * @param initialization_principal The Initialization Principle URL to set for the @@initializationPrincipal attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &initializationPrincipal(const URI &initialization_principal) { m_initializationPrincipal = initialization_principal; return *this; };

    /**
     * Set the @@initializationPrincipal attribute value (move)
     *
     * @param initialization_principal The Initialization Principle URL to move into the @@initializationPrincipal attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &initializationPrincipal(URI &&initialization_principal) { m_initializationPrincipal = std::move(initialization_principal); return *this; };

    /**
     * Set the @@initializationPrincipal attribute value (optional value copy)
     *
     * Copy the optional @p initialization_principal into the value of the @@initializationPrincipal attribute.
     *
     * @param initialization_principal The optional Initialization Principle URL to copy into the @@initializationPrincipal
     *                                 attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &initializationPrincipal(const std::optional<URI> &initialization_principal) { m_initializationPrincipal = initialization_principal; return *this; };

    /**
     * Set the @@initializationPrincipal attribute value (optional value move)
     *
     * Move the optional @p initialization_principal into the value of the @@initializationPrincipal attribute.
     *
     * @param initialization_principal The optional Initialization Principle URL to move into the @@initializationPrincipal
     *                                 attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &initializationPrincipal(std::optional<URI> &&initialization_principal) { m_lang = std::move(initialization_principal); return *this; };

    // Accessibility children

    /** Get the list of %Accessibility child elements
     *
     * @return The list of %Accessibility child Descriptor elements
     */
    const std::list<Descriptor> &accessibilities() const { return m_accessibilities; };
    /**@{*/
    /**
     * Get the start of %Accessibility elements list iterator
     *
     * @return An iterator pointing to the start of the %Accessibility elements list.
     */
    std::list<Descriptor>::const_iterator accessibilitiesBegin() const { return m_accessibilities.cbegin(); };
    std::list<Descriptor>::iterator accessibilitiesBegin() { return m_accessibilities.begin(); };
    /**@}*/

    /**@{*/
    /**
     * Get the end of %Accessibility elements list iterator
     *
     * @return An iterator pointing to the end of the %Accessibility elements list.
     */
    std::list<Descriptor>::const_iterator accessibilitiesEnd() const { return m_accessibilities.cend(); };
    std::list<Descriptor>::iterator accessibilitiesEnd() { return m_accessibilities.end(); };
    /**@}*/

    /** Get an %Accessibility element
     * 
     * Gets the %Accessibility Descriptor element at index @p idx in the %Accessibility elements list.
     *
     * @param idx The index of the element to fetch.
     * @return The %Accessibility Descriptor at index @p idx.
     * @throw std::out_of_range If @p idx is beyond the end of the list.
     */
    const Descriptor &accessibility(std::list<Descriptor>::size_type idx) const;

    /** Check if an %Accessibility Descriptor is in the list
     * 
     * @param descriptor The %Accessibility Descriptor to look for.
     * @return `true` if a Descriptor with the same value as @p descriptor is found, otherwise `false`.
     */
    bool accessibilitiesContains(const Descriptor &descriptor) const;

    /**@{*/
    /** Add a Descriptor to the %Accessibility elements
     *
     * @param accessibility The %Accessibility Descriptor to add to the list of %Accessibility elements.
     * @return This AdaptationSet.
     */
    AdaptationSet &accessibilitiesAdd(const Descriptor &accessibility);
    AdaptationSet &accessibilitiesAdd(Descriptor &&accessibility);
    /**@}*/

    /** Remove an %Accessibility Descriptor from the %Accessibility elements
     *
     * If the Descriptor @p accessibility exists in the %Accessibility elements, remove it from the list.
     *
     * @param accessibility The %Accessibility Descriptor to remove from the list of %Accessibility elements.
     * @return This AdaptationSet.
     */
    AdaptationSet &accessibilitiesRemove(const Descriptor &accessibility);

    /**@{*/
    /** Remove an %Accessibility Descriptor from the %Accessibility elements
     *
     * Removes the %Accessibility Descriptor, referenced by the iterator @p it, from the list of %Accessibility elements.
     *
     * @param it An iterator referencing an entry in the %Accessibility elements list.
     * @return This AdaptationSet.
     * @see accessibilitiesBegin()
     * @see accessibilitiesEnd()
     */
    AdaptationSet &accessibilitiesRemove(const std::list<Descriptor>::const_iterator &it);
    AdaptationSet &accessibilitiesRemove(const std::list<Descriptor>::iterator &it);
    /**@}*/

    // Role children

    /** Get the list of %Role child elements
     *
     * @return The list of %Role child Descriptor elements
     */
    const std::list<Descriptor> &roles() const { return m_roles; };

    /**@{*/
    /**
     * Get the start of %Role elements list iterator
     *
     * @return An iterator pointing to the start of the %Role elements list.
     */
    std::list<Descriptor>::const_iterator rolesBegin() const { return m_roles.cbegin(); };
    std::list<Descriptor>::iterator rolesBegin() { return m_roles.begin(); };
    /**@}*/

    /**@{*/
    /**
     * Get the end of %Role elements list iterator
     *
     * @return An iterator pointing to the end of the %Role elements list.
     */
    std::list<Descriptor>::const_iterator rolesEnd() const { return m_roles.cend(); };
    std::list<Descriptor>::iterator rolesEnd() { return m_roles.end(); };
    /**@}*/

    /** Get an %Role element
     * 
     * Gets the %Role Descriptor element at index @p idx in the %Role elements list.
     *
     * @param idx The index of the element to fetch.
     * @return The %Role Descriptor at index @p idx.
     * @throw std::out_of_range If @p idx is beyond the end of the list.
     */
    const Descriptor &role(std::list<Descriptor>::size_type idx) const;

    /** Check if a %Role Descriptor is in the list
     * 
     * @param descriptor The %Role Descriptor to look for.
     * @return `true` if a Descriptor with the same value as @p descriptor is found, otherwise `false`.
     */
    bool rolesContains(const Descriptor &descriptor) const;

    /**@{*/
    /** Add a Descriptor to the %Role elements
     *
     * @param role The %Role Descriptor to add to the list of %Role elements.
     * @return This AdaptationSet.
     */
    AdaptationSet &rolesAdd(const Descriptor &role);
    AdaptationSet &rolesAdd(Descriptor &&role);
    /**@}*/

    /** Remove a %Role Descriptor from the %Role elements
     *
     * If the Descriptor @p role exists in the %Role elements, remove it from the list.
     *
     * @param role The %Role Descriptor to remove from the list of %Role elements.
     * @return This AdaptationSet.
     */
    AdaptationSet &rolesRemove(const Descriptor &role);

    /**@{*/
    /** Remove a %Role Descriptor from the %Role elements
     *
     * Removes the %Role Descriptor, referenced by the iterator @p it, from the list of %Role elements.
     *
     * @param it An iterator referencing an entry in the %Role elements list.
     * @return This AdaptationSet.
     * @see rolesBegin()
     * @see rolesEnd()
     */
    AdaptationSet &rolesRemove(const std::list<Descriptor>::const_iterator &it);
    AdaptationSet &rolesRemove(const std::list<Descriptor>::iterator &it);
    /**@}*/

    // Rating children

    /** Get the list of %Rating child elements
     *
     * @return The list of %Rating child Descriptor elements
     */
    const std::list<Descriptor> &ratings() const { return m_ratings; };

    /**@{*/
    /**
     * Get the start of %Rating elements list iterator
     *
     * @return An iterator pointing to the start of the %Rating elements list.
     */
    std::list<Descriptor>::const_iterator ratingsBegin() const { return m_ratings.cbegin(); };
    std::list<Descriptor>::iterator ratingsBegin() { return m_ratings.begin(); };
    /**@}*/

    /**@{*/
    /**
     * Get the end of %Rating elements list iterator
     *
     * @return An iterator pointing to the end of the %Rating elements list.
     */
    std::list<Descriptor>::const_iterator ratingsEnd() const { return m_ratings.cend(); };
    std::list<Descriptor>::iterator ratingsEnd() { return m_ratings.end(); };
    /**@}*/

    /** Get an %Rating element
     * 
     * Gets the %Rating Descriptor element at index @p idx in the %Rating elements list.
     *
     * @param idx The index of the element to fetch.
     * @return The %Rating Descriptor at index @p idx.
     * @throw std::out_of_range If @p idx is beyond the end of the list.
     */
    const Descriptor &rating(std::list<Descriptor>::size_type idx) const;

    /** Check if a %Rating Descriptor is in the list
     * 
     * @param descriptor The %Rating Descriptor to look for.
     * @return `true` if a Descriptor with the same value as @p descriptor is found, otherwise `false`.
     */
    bool ratingsContains(const Descriptor &descriptor) const;

    /**@{*/
    /** Add a Descriptor to the %Rating elements
     *
     * @param rating The %Rating Descriptor to add to the list of %Rating elements.
     * @return This AdaptationSet.
     */
    AdaptationSet &ratingsAdd(const Descriptor &rating);
    AdaptationSet &ratingsAdd(Descriptor &&rating);
    /**@}*/

    /** Remove a %Rating Descriptor from the %Rating elements
     *
     * If the Descriptor @p rating exists in the %Rating elements, remove it from the list.
     *
     * @param rating The %Rating Descriptor to remove from the list of %Rating elements.
     * @return This AdaptationSet.
     */
    AdaptationSet &ratingsRemove(const Descriptor &rating);

    /**@{*/
    /** Remove a %Rating Descriptor from the %Rating elements
     *
     * Removes the %Rating Descriptor, referenced by the iterator @p it, from the list of %Rating elements.
     *
     * @param it An iterator referencing an entry in the %Rating elements list.
     * @return This AdaptationSet.
     * @see ratingsBegin()
     * @see ratingsEnd()
     */
    AdaptationSet &ratingsRemove(const std::list<Descriptor>::const_iterator &it);
    AdaptationSet &ratingsRemove(const std::list<Descriptor>::iterator &it);
    /**@}*/

    // Viewpoint children

    /** Get the list of %Viewpoint child elements
     *
     * @return The list of %Viewpoint child Descriptor elements
     */
    const std::list<Descriptor> &viewpoints() const { return m_viewpoints; };

    /**@{*/
    /**
     * Get the start of %Viewpoint elements list iterator
     *
     * @return An iterator pointing to the start of the %Viewpoint elements list.
     */
    std::list<Descriptor>::const_iterator viewpointsBegin() const { return m_viewpoints.cbegin(); };
    std::list<Descriptor>::iterator viewpointsBegin() { return m_viewpoints.begin(); };
    /**@}*/

    /**@{*/
    /**
     * Get the end of %Viewpoint elements list iterator
     *
     * @return An iterator pointing to the end of the %Viewpoint elements list.
     */
    std::list<Descriptor>::const_iterator viewpointsEnd() const { return m_viewpoints.cend(); };
    std::list<Descriptor>::iterator viewpointsEnd() { return m_viewpoints.end(); };
    /**@}*/

    /** Get an %Viewpoint element
     * 
     * Gets the %Viewpoint Descriptor element at index @p idx in the %Viewpoint elements list.
     *
     * @param idx The index of the element to fetch.
     * @return The %Viewpoint Descriptor at index @p idx.
     * @throw std::out_of_range If @p idx is beyond the end of the list.
     */
    const Descriptor &viewpoint(std::list<Descriptor>::size_type idx) const;

    /** Check if a %Viewpoint Descriptor is in the list
     * 
     * @param descriptor The %Viewpoint Descriptor to look for.
     * @return `true` if a Descriptor with the same value as @p descriptor is found, otherwise `false`.
     */
    bool viewpointsContains(const Descriptor &descriptor) const;

    /**@{*/
    /** Add a Descriptor to the %Viewpoint elements
     *
     * @param viewpoint The %Viewpoint Descriptor to add to the list of %Viewpoint elements.
     * @return This AdaptationSet.
     */
    AdaptationSet &viewpointsAdd(const Descriptor &viewpoint);
    AdaptationSet &viewpointsAdd(Descriptor &&viewpoint);
    /**@}*/

    /** Remove a %Viewpoint Descriptor from the %Viewpoint elements
     *
     * If the Descriptor @p viewpoint exists in the %Viewpoint elements, remove it from the list.
     *
     * @param viewpoint The %Viewpoint Descriptor to remove from the list of %Viewpoint elements.
     * @return This AdaptationSet.
     */
    AdaptationSet &viewpointsRemove(const Descriptor &viewpoint);

    /**@{*/
    /** Remove a %Viewpoint Descriptor from the %Viewpoint elements
     *
     * Removes the %Viewpoint Descriptor, referenced by the iterator @p it, from the list of %Viewpoint elements.
     *
     * @param it An iterator referencing an entry in the %Viewpoint elements list.
     * @return This AdaptationSet.
     * @see viewpointsBegin()
     * @see viewpointsEnd()
     */
    AdaptationSet &viewpointsRemove(const std::list<Descriptor>::const_iterator &it);
    AdaptationSet &viewpointsRemove(const std::list<Descriptor>::iterator &it);
    /**@}*/

    // ContentComponent children

    /** Get the list of %ContentComponent child elements
     *
     * @return The list of %ContentComponent child elements
     */
    const std::list<ContentComponent> &contentComponents() const { return m_contentComponents; };

    /**@{*/
    /**
     * Get the start of %ContentComponent elements list iterator
     *
     * @return An iterator pointing to the start of the %ContentComponent elements list.
     */
    std::list<ContentComponent>::const_iterator contentComponentsBegin() const { return m_contentComponents.cbegin(); };
    std::list<ContentComponent>::iterator contentComponentsBegin() { return m_contentComponents.begin(); };
    /**@}*/

    /**@{*/
    /**
     * Get the end of %ContentComponent elements list iterator
     *
     * @return An iterator pointing to the end of the %ContentComponent elements list.
     */
    std::list<ContentComponent>::const_iterator contentComponentsEnd() const { return m_contentComponents.cend(); };
    std::list<ContentComponent>::iterator contentComponentsEnd() { return m_contentComponents.end(); };
    /**@}*/

    /** Get an %ContentComponent element
     * 
     * Gets the %ContentComponent element at index @p idx in the %ContentComponent elements list.
     *
     * @param idx The index of the element to fetch.
     * @return The %ContentComponent at index @p idx.
     * @throw std::out_of_range If @p idx is beyond the end of the list.
     */
    const ContentComponent &contentComponent(std::list<ContentComponent>::size_type idx) const;

    /** Check if a %ContentComponent is in the list
     * 
     * @param content_component The %ContentComponent to look for.
     * @return `true` if a ContentComponent with the same value as @p content_component is found, otherwise `false`.
     */
    bool contentComponentsContains(const ContentComponent &content_component) const;

    /**@{*/
    /** Add a ContentComponent to the %ContentComponent elements
     *
     * @param content_component The %ContentComponent to add to the list of %ContentComponent elements.
     * @return This AdaptationSet.
     */
    AdaptationSet &contentComponentsAdd(const ContentComponent &content_component);
    AdaptationSet &contentComponentsAdd(ContentComponent &&content_component);
    /**@}*/

    /** Remove a %ContentComponent from the %ContentComponent elements
     *
     * If the ContentComponent @p content_component exists in the %ContentComponent elements, remove it from the list.
     *
     * @param content_component The %ContentComponent to remove from the list of %ContentComponent elements.
     * @return This AdaptationSet.
     */
    AdaptationSet &contentComponentsRemove(const ContentComponent &content_component);

    /**@{*/
    /** Remove a %ContentComponent from the %ContentComponent elements
     *
     * Removes the %ContentComponent, referenced by the iterator @p it, from the list of %ContentComponent elements.
     *
     * @param it An iterator referencing an entry in the %ContentComponent elements list.
     * @return This AdaptationSet.
     * @see contentComponentsBegin()
     * @see contentComponentsEnd()
     */
    AdaptationSet &contentComponentsRemove(const std::list<ContentComponent>::const_iterator &it);
    AdaptationSet &contentComponentsRemove(const std::list<ContentComponent>::iterator &it);
    /**@}*/

    // BaseURL children

    /** Get the list of %BaseURL child elements
     *
     * @return The list of %BaseURL child elements
     */
    const std::list<BaseURL> &baseURLs() const { return m_baseURLs; };

    /**@{*/
    /**
     * Get the start of %BaseURL elements list iterator
     *
     * @return An iterator pointing to the start of the %BaseURL elements list.
     */
    std::list<BaseURL>::const_iterator baseURLsBegin() const { return m_baseURLs.cbegin(); };
    std::list<BaseURL>::iterator baseURLsBegin() { return m_baseURLs.begin(); };
    /**@}*/

    /**@{*/
    /**
     * Get the end of %BaseURL elements list iterator
     *
     * @return An iterator pointing to the end of the %BaseURL elements list.
     */
    std::list<BaseURL>::const_iterator baseURLsEnd() const { return m_baseURLs.cend(); };
    std::list<BaseURL>::iterator baseURLsEnd() { return m_baseURLs.end(); };
    /**@}*/

    /** Get an %BaseURL element
     * 
     * Gets the %BaseURL element at index @p idx in the %BaseURL elements list.
     *
     * @param idx The index of the element to fetch.
     * @return The %BaseURL at index @p idx.
     * @throw std::out_of_range If @p idx is beyond the end of the list.
     */
    const BaseURL &baseURL(std::list<BaseURL>::size_type idx) const;

    /** Check if a %BaseURL is in the list
     * 
     * @param base_url The %BaseURL to look for.
     * @return `true` if a BaseURL with the same value as @p base_url is found, otherwise `false`.
     */
    bool baseURLsContains(const BaseURL &base_url) const;

    /**@{*/
    /** Add a BaseURL to the %BaseURL elements
     *
     * @param base_url The %BaseURL to add to the list of %BaseURL elements.
     * @return This AdaptationSet.
     */
    AdaptationSet &baseURLsAdd(const BaseURL &base_url);
    AdaptationSet &baseURLsAdd(BaseURL &&base_url);
    /**@}*/

    /** Remove a %BaseURL from the %BaseURL elements
     *
     * If the BaseURL @p base_url exists in the %BaseURL elements, remove it from the list.
     *
     * @param base_url The %BaseURL to remove from the list of %BaseURL elements.
     * @return This AdaptationSet.
     */
    AdaptationSet &baseURLsRemove(const BaseURL &base_url);

    /**@{*/
    /** Remove a %BaseURL from the %BaseURL elements
     *
     * Removes the %BaseURL, referenced by the iterator @p it, from the list of %BaseURL elements.
     *
     * @param it An iterator referencing an entry in the %BaseURL elements list.
     * @return This AdaptationSet.
     * @see baseURLsBegin()
     * @see baseURLsEnd()
     */
    AdaptationSet &baseURLsRemove(const std::list<BaseURL>::const_iterator &it);
    AdaptationSet &baseURLsRemove(const std::list<BaseURL>::iterator &it);
    /**@}*/

    /** Get the list of BaseURL entries that apply for this AdaptationSet
     *
     * @return A list of BaseURL entries from this AdaptationSet merged with entries from the Period and MPD.
     */ 
    std::list<BaseURL> getBaseURLs() const;

    // SegmentBase child

    /** Check if a %SegmentBase element is present
     *
     * @return `true` if a SegmentBase has been set, otherwise `false`.
     */
    bool hasSegmentBase() const { return m_segmentBase.has_value(); };

    /** Get the optional SegmentBase
     * 
     * @return The optional SegmentBase for this AdaptationSet.
     */
    const std::optional<SegmentBase> &segmentBase() const { return m_segmentBase; };

    /** Unset the optional SegmentBase
     *
     * Removes the %SegmentBase element from this AdaptationSet.
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &segmentBase(const std::nullopt_t &) { m_segmentBase.reset(); return *this; };

    /** Set the SegmentBase
     *
     * Copy the SegmentBase from @p seg_base as the SegmentBase for this AdaptationSet.
     *
     * @param seg_base The SegmentBase to set on this AdaptationSet.
     * @return This AdaptationSet.
     */
    AdaptationSet &segmentBase(const SegmentBase &seg_base) { m_segmentBase = seg_base; return *this; };

    /** Set the SegmentBase
     *
     * Move the value of SegmentBase @p seg_base as the SegmentBase for this AdaptationSet.
     *
     * @param seg_base The SegmentBase to set on this AdaptationSet.
     * @return This AdaptationSet.
     */
    AdaptationSet &segmentBase(SegmentBase &&seg_base) { m_segmentBase = std::move(seg_base); return *this; };

    /**@{*/
    /** Set the SegmentBase
     *
     * Set the SegmentBase of this AdaptationSet to @p seg_base.
     *
     * @param seg_base The SegmentBase to set in this AdaptationSet.
     * @return This AdaptationSet.
     */
    AdaptationSet &segmentBase(const std::optional<SegmentBase> &seg_base) { m_segmentBase = seg_base; return *this; };
    AdaptationSet &segmentBase(std::optional<SegmentBase> &&seg_base) { m_segmentBase = std::move(seg_base); return *this; };
    /**@}*/

    // SegmentList child

    /** Check if a %SegmentList element is present
     *
     * @return `true` if a SegmentList has been set, otherwise `false`.
     */
    bool hasSegmentList() const { return m_segmentList.has_value(); };

    /** Get the optional SegmentList
     * 
     * @return The optional SegmentList for this AdaptationSet.
     */
    const std::optional<SegmentList> &segmentList() const { return m_segmentList; };

    /** Unset the optional SegmentList
     *
     * Removes the %SegmentList element from this AdaptationSet.
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &segmentList(const std::nullopt_t &) { m_segmentList.reset(); return *this; };

    /** Set the SegmentList
     *
     * Copy the SegmentList from @p seg_list as the SegmentList for this AdaptationSet.
     *
     * @param seg_list The SegmentList to set on this AdaptationSet.
     * @return This AdaptationSet.
     */
    AdaptationSet &segmentList(const SegmentList &seg_list) { m_segmentList = seg_list; return *this; };

    /** Set the SegmentList
     *
     * Move the value of SegmentList @p seg_list as the SegmentList for this AdaptationSet.
     *
     * @param seg_list The SegmentList to set on this AdaptationSet.
     * @return This AdaptationSet.
     */
    AdaptationSet &segmentList(SegmentList &&seg_list) { m_segmentList = std::move(seg_list); return *this; };

    /**@{*/
    /** Set the SegmentList
     *
     * Set the SegmentList of this AdaptationSet to @p seg_list.
     *
     * @param seg_list The SegmentList to set in this AdaptationSet.
     * @return This AdaptationSet.
     */
    AdaptationSet &segmentList(const std::optional<SegmentList> &seg_list) { m_segmentList = seg_list; return *this; };
    AdaptationSet &segmentList(std::optional<SegmentList> &&seg_list) { m_segmentList = std::move(seg_list); return *this; };
    /**@}*/

    // SegmentTemplate child

    /** Check if a %SegmentTemplate element is present
     *
     * @return `true` if a SegmentTemplate has been set, otherwise `false`.
     */
    bool hasSegmentTemplate() const { return m_segmentTemplate.has_value(); };

    /** Get the optional SegmentTemplate
     * 
     * @return The optional SegmentTemplate for this AdaptationSet.
     */
    const std::optional<SegmentTemplate> &segmentTemplate() const { return m_segmentTemplate; };

    /** Unset the optional SegmentTemplate
     *
     * Removes the %SegmentTemplate element from this AdaptationSet.
     *
     * @return This AdaptationSet.
     */
    AdaptationSet &segmentTemplate(const std::nullopt_t &) { m_segmentTemplate.reset(); return *this; };

    /** Set the SegmentTemplate
     *
     * Copy the SegmentTemplate from @p seg_template as the SegmentTemplate for this AdaptationSet.
     *
     * @param seg_template The SegmentTemplate to set on this AdaptationSet.
     * @return This AdaptationSet.
     */
    AdaptationSet &segmentTemplate(const SegmentTemplate &seg_template) {m_segmentTemplate = seg_template; return *this; };

    /** Set the SegmentTemplate
     *
     * Move the value of SegmentTemplate @p seg_template as the SegmentTemplate for this AdaptationSet.
     *
     * @param seg_template The SegmentTemplate to set on this AdaptationSet.
     * @return This AdaptationSet.
     */
    AdaptationSet &segmentTemplate(SegmentTemplate &&seg_template) {m_segmentTemplate = std::move(seg_template); return *this; };

    /**@{*/
    /** Set the SegmentTemplate
     *
     * Set the SegmentTemplate of this AdaptationSet to @p seg_template.
     *
     * @param seg_template The SegmentTemplate to set in this AdaptationSet.
     * @return This AdaptationSet.
     */
    AdaptationSet &segmentTemplate(const std::optional<SegmentTemplate> &seg_template) {m_segmentTemplate = seg_template; return *this; };
    AdaptationSet &segmentTemplate(std::optional<SegmentTemplate> &&seg_template) {m_segmentTemplate = std::move(seg_template); return *this; };
    /**@}*/

    // Representation children

    /** Get the list of %Representation child elements
     *
     * @return The list of %Representation child elements
     */
    const std::list<Representation> &representations() const { return m_representations; };

    /**@{*/
    /**
     * Get the start of %Representation elements list iterator
     *
     * @return An iterator pointing to the start of the %Representation elements list.
     */
    std::list<Representation>::const_iterator representationsBegin() const { return m_representations.cbegin(); };
    std::list<Representation>::iterator representationsBegin() { return m_representations.begin(); };
    /**@}*/

    /**@{*/
    /**
     * Get the end of %Representation elements list iterator
     *
     * @return An iterator pointing to the end of the %Representation elements list.
     */
    std::list<Representation>::const_iterator representationsEnd() const { return m_representations.cend(); };
    std::list<Representation>::iterator representationsEnd() { return m_representations.end(); };
    /**@}*/

    /** Get an %Representation element
     * 
     * Gets the %Representation element at index @p idx in the %Representation elements list.
     *
     * @param idx The index of the element to fetch.
     * @return The %Representation at index @p idx.
     * @throw std::out_of_range If @p idx is beyond the end of the list.
     */
    const Representation &representation(std::list<Representation>::size_type idx) const;

    /** Check if a %Representation is in the list
     * 
     * @param representation The %Representation to look for.
     * @return `true` if a Representation with the same value as @p representation is found, otherwise `false`.
     */
    bool representationsContains(const Representation &representation) const;

    /**@{*/
    /** Add a Representation to the %Representation elements
     *
     * @param representation The %Representation to add to the list of %Representation elements.
     * @return This AdaptationSet.
     */
    AdaptationSet &representationsAdd(const Representation &representation);
    AdaptationSet &representationsAdd(Representation &&representation);
    /**@}*/

    /** Remove a %Representation from the %Representation elements
     *
     * If the Representation @p representation exists in the %Representation elements, remove it from the list.
     *
     * @param representation The %Representation to remove from the list of %Representation elements.
     * @return This AdaptationSet.
     */
    AdaptationSet &representationsRemove(const Representation &representation);

    /**@{*/
    /** Remove a %Representation from the %Representation elements
     *
     * Removes the %Representation, referenced by the iterator @p it, from the list of %Representation elements.
     *
     * @param it An iterator referencing an entry in the %Representation elements list.
     * @return This AdaptationSet.
     * @see representationsBegin()
     * @see representationsEnd()
     */
    AdaptationSet &representationsRemove(const std::list<Representation>::const_iterator &it);
    AdaptationSet &representationsRemove(const std::list<Representation>::iterator &it);
    /**@}*/

    // Representation selection

    /** Mark all Representations as selected
     * 
     * This will mark all child Represtation objects as selected for this AdaptationSet.
     *
     * @see selectRepresentation()
     * @see deselectAllRepresentations()
     * @see deselectRepresentation()
     * @see selectedSegmentAvailability()
     * @see selectedInitializationSegments()
     */
    void selectAllRepresentations();

    /**
     * Mark a Representation as selected
     *
     * @param rep The Representation to add to the list of selected Representation objects.
     * @param deselect_others `true` if other representations already selected should be deselected.
     *
     * @see selectAllRepresentations()
     * @see deselectAllRepresentations()
     * @see deselectRepresentation()
     * @see selectedSegmentAvailability()
     * @see selectedInitializationSegments()
     */
    void selectRepresentation(const Representation &rep, bool deselect_others = false);

    /**@{*/
    /**
     * Mark a Representation as selected
     *
     * @param rep_it The iterator for the Representation to add to the list of selected Representation objects.
     * @param deselect_others `true` if other representations, that are already selected, should be deselected.
     *
     * @see representationsBegin()
     * @see representationsEnd()
     * @see selectAllRepresentations()
     * @see deselectAllRepresentations()
     * @see deselectRepresentation()
     * @see selectedSegmentAvailability()
     * @see selectedInitializationSegments()
     */
    void selectRepresentation(const std::list<Representation>::const_iterator &rep_it, bool deselect_others = false);
    void selectRepresentation(const std::list<Representation>::iterator &rep_it, bool deselect_others = false);
    /**@}*/

    /**
     * Deselect all Representations
     *
     * This will empty the set of selected Representation objects.
     *
     * @see selectAllRepresentations()
     * @see selectRepresentation()
     * @see deselectRepresentation()
     * @see selectedSegmentAvailability()
     * @see selectedInitializationSegments()
     */
    void deselectAllRepresentations();

    /**
     * Deselect a Representation
     *
     * This will remove the Representation, @p rep, from the set of selected Representation objects.
     *
     * @param rep The Representation to remove from the set of selected Representation objects.
     *
     * @see selectAllRepresentations()
     * @see selectRepresentation()
     * @see deselectAllRepresentations()
     * @see selectedSegmentAvailability()
     * @see selectedInitializationSegments()
     */
    void deselectRepresentation(const Representation &rep);

    /**@{*/
    /**
     * Deselect a Representation
     *
     * This will remove the Representation, referenced by the @p rep_it iterator, from the set of selected Representation objects.
     *
     * @param rep_it The iterator referencing the Representation to remove.
     *
     * @see selectAllRepresentations()
     * @see selectRepresentation()
     * @see deselectAllRepresentations()
     * @see selectedSegmentAvailability()
     * @see selectedInitializationSegments()
     */
    void deselectRepresentation(const std::list<Representation>::const_iterator &rep_it);
    void deselectRepresentation(const std::list<Representation>::iterator &rep_it);
    /**@}*/

    /**
     * Get the set of selected Representation objects
     *
     * @return The set of selected Representation objects.
     */
    const std::unordered_set<const Representation*> &selectedRepresentations() const { return m_selectedRepresentations; };

    // Representation querying

    /**
     * Get the list of media segment availability metadata for all selected Representation objects
     *
     * This obtains a list of media segment availability metadata, for all currently selected Representation objects, for media
     * segments available on or after @p query_time. The returned list will be empty if there are no media segments on or after
     * @p query_time available in the parent Period associated with this AdaptationSet, i.e. the @p query_time is after the end
     * of the Period or after the MPD/@@pvailabilityEndTime.
     *
     * @param query_time The time to find media segments at or after from the selected Representation objects.
     * @return A list of media segment availability metadata.
     */
    std::list<SegmentAvailability> selectedSegmentAvailability(const time_type &query_time) const;

    /**
     * Get the list of initialization segment availability metadata for all selected Representation objects
     *
     * This obtains a list of initialization segment availability metadata, for all currently selected Representation objects.
     * The returned list will be empty if there are no initialization segments for the selected Representations.
     *
     * @return A list of initialization segment availability metadata.
     */
    std::list<SegmentAvailability> selectedInitializationSegments() const;

///@cond PROTECTED
protected:
    friend class MPD;
    friend class Period;
    friend class Representation;

    /**
     * XML constructor (internal use only)
     *
     * Create a new AdaptationSet from an XML %AdaptationSet element.
     *
     * @param node The libxml++ Node for the %AdaptationSet element to ingest.
     */
    AdaptationSet(xmlpp::Node &node);

    /**
     * Set a libxml++ Element attributes and children for XML output
     *
     * This will set all relevant attributes and child elements from the settings of this AdaptationSet.
     *
     * @param element The libxml++ Element to populate.
     */
    void setXMLElement(xmlpp::Element &element) const;

    /**
     * Set the parent Period object
     *
     * @param period The Period to set as this AdaptationSet's parent object.
     * @return This AdaptationSet.
     */
    AdaptationSet &setPeriod(Period *period) { m_period = period; return *this; };

    /**
     * Get a media segment URL
     *
     * Using the @p vars, get a media URL by applying a SegmentTemplate or SegmentList attached to this AdaptationSet.
     *
     * @param vars The segment variables to apply to any template or list index.
     * @return The URL string for the media or an empty string if no template or list could be found.
     */
    std::string getMediaURL(const SegmentTemplate::Variables &vars) const;

    /**
     * Get an initialization segment URL
     *
     * Using the @p vars, get an initialization segment URL by applying a SegmentTemplate or SegmentList attached to this
     * AdaptationSet.
     *
     * @param vars The segment variables to apply to any template or list index.
     * @return The URL string for the initialization segment or an empty string if no template or list could be found.
     */
    std::string getInitializationURL(const SegmentTemplate::Variables &vars) const;

    /**
     * Get the media segment availability and URL
     *
     * Using the @p vars, get media segment metadata by applying a SegmentTemplate or SegmentList attached to this AdaptationSet.
     *
     * @param vars The segment variables to apply to any template or list index.
     * @return The segment availability times and URL. The URL will be empty if no suitable segment could be found.
     */
    SegmentAvailability getMediaAvailability(const SegmentTemplate::Variables &vars) const;

    /**
     * Get the initialization segment availability and URL
     *
     * Using the @p vars, get initialization segment metadata by applying a SegmentTemplate or SegmentList attached to this
     * AdaptationSet.
     *
     * @param vars The segment variables to apply to any template or list index.
     * @return The initialization segment availability times and URL. The URL will be empty if no suitable initialization segment
     *         could be found.
     */
    SegmentAvailability getInitialisationAvailability(const SegmentTemplate::Variables &vars) const;

    /**
     * Get the start time for the parent Period
     *
     * @return The system wallclock time for the parent Period start, or the epoch if there is no parent.
     */
    time_type getPeriodStartTime() const;

    /**
     * Get the duration of the parent Period
     *
     * @return The duration of the parent Period, if known, or std::nullopt if there is no paranet Period or the Period has no
     *         duration.
     */
    std::optional<duration_type> getPeriodDuration() const;

    /**
     * Get the MultipleSegmentBase appropriate for this AdaptationSet
     *
     * Returns the MultipleSegmentBase object for a SegmentTemplate or SegmentList associated with this AdaptationSet or, as a
     * fallback the parent Period.
     *
     * @return The MultipleSegmentBase object found.
     */
    const MultipleSegmentBase &getMultiSegmentBase() const;

///@endcond PROTECTED

private:
    Period *m_period;                                              ///< The Period object this adaptation set is a child of
    std::unordered_set<const Representation*> m_selectedRepresentations; ///< An index to the set of selected Representation entries

    // Period attributes (ISO 23009-1:2022 Clause 5.3.3.3)
    std::optional<XLink>               m_xlink;                    ///< The XLink settings for AdaptationSet HTTP referencing
    std::optional<unsigned int>        m_id;                       ///< The AdaptationSet @@id number
    std::optional<unsigned int>        m_group;                    ///< The AdaptationSet @@group number
    std::optional<std::string>         m_lang;                     ///< The language identifier
    std::optional<RFC6838ContentType>  m_contentType;              ///< The content type
    std::optional<Ratio>               m_par;                      ///< The picture aspect ratio
    std::optional<unsigned int>        m_minBandwidth;             ///< The minimum bandwidth requirement
    std::optional<unsigned int>        m_maxBandwidth;             ///< The maximum bandwidth requirement
    std::optional<unsigned int>        m_minWidth;                 ///< The minimum video width
    std::optional<unsigned int>        m_maxWidth;                 ///< The maximum video width
    std::optional<unsigned int>        m_minHeight;                ///< The minimum video height
    std::optional<unsigned int>        m_maxHeight;                ///< The maximum video height
    std::optional<FrameRate>           m_minFrameRate;             ///< The minimum video frame rate
    std::optional<FrameRate>           m_maxFrameRate;             ///< The maximum video frame rate
    bool                               m_segmentAlignment;         ///< The segment alignment flag (default: false)
    bool                               m_subsegmentAlignment;      ///< The subsegment alignment flag (default: false)
    SAP                                m_subsegmentStartsWithSAP;  ///< The subsegment start with SAP value (default: 0)
    std::optional<bool>                m_bitstreamSwitching;       ///< The bitstream switching flag
    std::list<unsigned int>            m_initializationSetRefs;    ///< The array of Initialization Set identifiers
    std::optional<URI>                 m_initializationPrincipal;  ///< The Initialization Segment URL

    // Period child elements (ISO 23009-1:2022 Clause 5.3.3.3)
    std::list<Descriptor>          m_accessibilities;              ///< Accessibility descriptors
    std::list<Descriptor>          m_roles;                        ///< Role descriptors
    std::list<Descriptor>          m_ratings;                      ///< Rating descriptors
    std::list<Descriptor>          m_viewpoints;                   ///< Viewpoint descriptors
    std::list<ContentComponent>    m_contentComponents;            ///< ContentComponent entries
    std::list<BaseURL>             m_baseURLs;                     ///< BaseURL entries
    std::optional<SegmentBase>     m_segmentBase;                  ///< The SegmentBase entry
    std::optional<SegmentList>     m_segmentList;                  ///< The SegmentList entry
    std::optional<SegmentTemplate> m_segmentTemplate;              ///< The SegmentTemplate entry
    std::list<Representation>      m_representations;              ///< The Representation child objects
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_ADAPTATION_SET_HH_*/
