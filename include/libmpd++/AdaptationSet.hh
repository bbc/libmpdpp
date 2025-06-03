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

namespace xmlpp {
    class Element;
    class Node;
}

LIBMPDPP_NAMESPACE_BEGIN

/**
 * AdaptationSet class
 *
 * @headerfile libmpd++/AdaptationSet.hh <libmpd++/AdaptationSet.hh>
 *
 * This is the container for AdaptationSet representations from an MPD.
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
     * Copies the @a lang value into the @@lang attribute.
     *
     * @param lang The language identifier to set the @@lang attribute to.
     * @return This AdaptationSet.
     */
    AdaptationSet &lang(const std::string &lang) { m_lang = lang; return *this; };

    /**
     * Set the @@lang attribute value (move)
     *
     * Move the @a lang value into the @@lang attribute.
     *
     * @param lang The language identifier to set the @@lang attribute to.
     * @return This AdaptationSet.
     */
    AdaptationSet &lang(std::string &&lang) { m_lang = std::move(lang); return *this; };

    /**
     * Set the @@lang attribute value (optional value copy)
     *
     * Copy the optional @a lang value as the setting for the @@lang attribute.
     *
     * @param lang The optional language identifier to set the @@lang attribute to.
     * @return This AdaptationSet.
     */
    AdaptationSet &lang(const std::optional<std::string> &lang) { m_lang = lang; return *this; };

    /**
     * Set the @@lang attribute value (optional value move)
     *
     * Move the optional @a lang value as the setting for the @@lang attribute.
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
     * Set the @@contentType attribute to a copy of the @a content_type value.
     *
     * @param content_type The RFC6838 content type to set the @@contentType attribute to.
     * @return This AdaptationSet.
     */
    AdaptationSet &contentType(const RFC6838ContentType &content_type) {m_contentType = content_type; return *this;};

    /**
     * Set the @@contentType attribute value (move)
     *
     * Move the RFC6838 content type value, @a content_type, into the @@contentType attribute.
     *
     * @param content_type The RFC6838 content type to move to the @@contentType attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &contentType(RFC6838ContentType &&content_type) {m_contentType = std::move(content_type); return *this;};

    /**
     * Set the @@contentType attribute value (optional value copy)
     *
     * Copy the optional value from @a content_type to the @@contentType attribute.
     *
     * @param content_type The optional RFC6838 content type value to copy into the @@contentType attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &contentType(const std::optional<RFC6838ContentType> &content_type) { m_contentType = content_type; return *this;};

    /**
     * Set the @@contentType attribute value (optional value move)
     *
     * Move the optional value from @a content_type into the @@contentType attribute.
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
     * Copy the Ratio @a par as the value of the @@par attribute.
     *
     * @param par The picture aspect ratio to copy into the @@par attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &par(const Ratio &par) {m_par = par; return *this;};

    /**
     * Set the @@par attribute value (move)
     *
     * Move the Ratio @a par into the value of the @@par attribute.
     *
     * @param par The picture aspect ratio to move into the @@par attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &par(Ratio &&par) {m_par = std::move(par); return *this;};

    /**
     * Set the @@par attribute value (optional value copy)
     *
     * Copy the optional Ratio @a par into the value of the @@par attribute.
     *
     * @param par The optional picture aspect ratio to copy into the @@par attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &par(const std::optional<Ratio> &par) { m_par = par; return *this;};

    /**
     * Set the @@par attribute value (optional value move)
     *
     * Move the optional Ratio @a par into the value of the @@par attribute.
     *
     * @param par The optional picture aspect ratio to move into the @@par attribute.
     * @return This AdaptationSet.
     */
    AdaptationSet &par(std::optional<Ratio> &&par) { m_par = std::move(par); return *this;};

    // @minBandwidth;
    bool hasMinBandwidth() const { return m_minBandwidth.has_value(); };
    const std::optional<unsigned int> &minBandwidth() const { return m_minBandwidth; };
    AdaptationSet &minBandwidth(const std::nullopt_t &) { m_minBandwidth.reset(); return *this;};
    AdaptationSet &minBandwidth(unsigned int min_bandwidth) { m_minBandwidth = min_bandwidth; return *this;};
    AdaptationSet &minBandwidth(const std::optional<unsigned int> &min_bandwidth) { m_minBandwidth = min_bandwidth; return *this;};
    AdaptationSet &minBandwidth(std::optional<unsigned int> &&min_bandwidth) { m_minBandwidth = std::move(min_bandwidth);return *this;};

    // @maxBandwidth
    bool hasMaxBandwidth() const { return m_maxBandwidth.has_value(); };
    const std::optional<unsigned int> &maxBandwidth() const { return m_maxBandwidth; };
    AdaptationSet &maxBandwidth(const std::nullopt_t &) { m_maxBandwidth.reset(); return *this;};
    AdaptationSet &maxBandwidth(unsigned int max_bandwidth) { m_maxBandwidth = max_bandwidth; return *this;};
    AdaptationSet &maxBandwidth(const std::optional<unsigned int> &max_bandwidth) { m_maxBandwidth = max_bandwidth; return *this;};
    AdaptationSet &maxBandwidth(std::optional<unsigned int> &&max_bandwidth) { m_maxBandwidth = std::move(max_bandwidth);return *this;};

    // @minWidth
    bool hasMinWidth() const { return m_minWidth.has_value(); };
    const std::optional<unsigned int> &minWidth() const { return m_minWidth; };
    AdaptationSet &minWidth(const std::nullopt_t &) { m_minWidth.reset(); return *this;};
    AdaptationSet &minWidth(unsigned int min_width) { m_minWidth = min_width; return *this;};
    AdaptationSet &minWidth(const std::optional<unsigned int> &min_width) { m_minWidth = min_width; return *this;};
    AdaptationSet &minWidth(std::optional<unsigned int> &&min_width) { m_minWidth = std::move(min_width);return *this;};

    // @maxWidth
    bool hasMaxWidth() const { return m_maxWidth.has_value(); };
    const std::optional<unsigned int> &maxWidth() const { return m_maxWidth; };
    AdaptationSet &maxWidth(const std::nullopt_t &) { m_maxWidth.reset(); return *this;};
    AdaptationSet &maxWidth(unsigned int max_width) { m_maxWidth = max_width; return *this;};
    AdaptationSet &maxWidth(const std::optional<unsigned int> &max_width) { m_maxWidth = max_width; return *this;};
    AdaptationSet &maxWidth(std::optional<unsigned int> &&max_width) { m_maxWidth = std::move(max_width);return *this;};

    // @minHeight
    bool hasMinHeight() const { return m_minHeight.has_value(); };
    const std::optional<unsigned int> &minHeight() const { return m_minHeight; };
    AdaptationSet &minHeight(const std::nullopt_t &) { m_minHeight.reset(); return *this;};
    AdaptationSet &minHeight(unsigned int min_height) { m_minHeight = min_height; return *this;};
    AdaptationSet &minHeight(const std::optional<unsigned int> &min_height) { m_minHeight = min_height; return *this;};
    AdaptationSet &minHeight(std::optional<unsigned int> &&min_height) { m_minHeight = std::move(min_height);return *this;};

    // @maxHeight
    bool hasMaxHeight() const { return m_maxHeight.has_value(); };
    const std::optional<unsigned int> &maxHeight() const { return m_maxHeight; };
    AdaptationSet &maxHeight(const std::nullopt_t &) { m_maxHeight.reset(); return *this;};
    AdaptationSet &maxHeight(unsigned int max_height) { m_maxHeight = max_height; return *this;};
    AdaptationSet &maxHeight(const std::optional<unsigned int> &max_height) { m_maxHeight = max_height; return *this;};
    AdaptationSet &maxHeight(std::optional<unsigned int> &&max_height) { m_maxHeight = std::move(max_height);return *this;};

    // @minFrameRate
    bool hasMinFrameRate() const { return m_minFrameRate.has_value(); };
    const std::optional<FrameRate> &minFrameRate() const {return m_minFrameRate;};
    AdaptationSet &minFrameRate(const std::nullopt_t &) { m_minFrameRate.reset(); return *this; };
    AdaptationSet &minFrameRate(const FrameRate &min_frame_rate) {m_minFrameRate = min_frame_rate; return *this;};
    AdaptationSet &minFrameRate(FrameRate &&min_frame_rate) {m_minFrameRate = std::move(min_frame_rate); return *this;};
    AdaptationSet &minFrameRate(const std::optional<FrameRate> &min_frame_rate) { m_minFrameRate = min_frame_rate; return *this;};
    AdaptationSet &minFrameRate(std::optional<FrameRate> &&min_frame_rate) { m_minFrameRate = std::move(min_frame_rate); return *this;};

    // @maxFrameRate
    bool hasMaxFrameRate() const { return m_maxFrameRate.has_value(); };
    const std::optional<FrameRate> &maxFrameRate() const {return m_maxFrameRate;};
    AdaptationSet &maxFrameRate(const std::nullopt_t &) { m_maxFrameRate.reset(); return *this; };
    AdaptationSet &maxFrameRate(const FrameRate &max_frame_rate) {m_maxFrameRate = max_frame_rate; return *this;};
    AdaptationSet &maxFrameRate(FrameRate &&max_frame_rate) {m_maxFrameRate = std::move(max_frame_rate); return *this;};
    AdaptationSet &maxFrameRate(const std::optional<FrameRate> &max_frame_rate) { m_maxFrameRate = max_frame_rate; return *this;};
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
    bool hasBitstreamSwitching() const { return m_bitstreamSwitching.has_value(); };
    const std::optional<bool> &bitstreamSwitching() const { return m_bitstreamSwitching; };
    AdaptationSet &bitstreamSwitching(const std::nullopt_t&) { m_bitstreamSwitching.reset(); return *this; };
    AdaptationSet &bitstreamSwitching(bool bitstream_switching) { m_bitstreamSwitching = bitstream_switching; return *this; };
    AdaptationSet &bitstreamSwitching(const std::optional<bool> &bitstream_switching) { m_bitstreamSwitching = bitstream_switching; return *this; };
    AdaptationSet &bitstreamSwitching(std::optional<bool> &&bitstream_switching) { m_bitstreamSwitching = std::move(bitstream_switching); return *this; };

    // @initializationSetRefs
    const std::list<unsigned int> &initializationSetRefs() const { return m_initializationSetRefs; };
    AdaptationSet &initializationSetRefs(std::list<unsigned int> initialization_set_refs) { m_initializationSetRefs = initialization_set_refs; return *this;};

    // @initializationPrincipal
    bool hasInitializationPrincipal() const { return m_initializationPrincipal.has_value(); };
    const std::optional<URI> &initializationPrincipal() const { return m_initializationPrincipal; };
    AdaptationSet &initializationPrincipal(const std::nullopt_t &) { m_initializationPrincipal.reset(); return *this; };
    AdaptationSet &initializationPrincipal(const URI &initialization_principal) { m_initializationPrincipal = initialization_principal; return *this; };
    AdaptationSet &initializationPrincipal(URI &&initialization_principal) { m_initializationPrincipal = std::move(initialization_principal); return *this; };
    AdaptationSet &initializationPrincipal(const std::optional<URI> &initialization_principal) { m_initializationPrincipal = initialization_principal; return *this; };
    AdaptationSet &initializationPrincipal(std::optional<URI> &&initialization_principal) { m_lang = std::move(initialization_principal); return *this; };

    // Accessibility children
    const std::list<Descriptor> &accessibility() const { return m_accessibilities; };
    std::list<Descriptor>::const_iterator accessibilityBegin() const { return m_accessibilities.cbegin(); };
    std::list<Descriptor>::const_iterator accessibilityEnd() const { return m_accessibilities.cend(); };
    std::list<Descriptor>::iterator accessibilityBegin() { return m_accessibilities.begin(); };
    std::list<Descriptor>::iterator accessibilityEnd() { return m_accessibilities.end(); };
    AdaptationSet &accessibilityAdd(const Descriptor &accessibility);
    AdaptationSet &accessibilityAdd(Descriptor &&accessibility);
    AdaptationSet &accessibilityRemove(const Descriptor &accessibility);
    AdaptationSet &accessibilityRemove(const std::list<Descriptor>::const_iterator &);
    AdaptationSet &accessibilityRemove(const std::list<Descriptor>::iterator &);

    // Role children
    const std::list<Descriptor> &roles() const { return m_roles; };
    std::list<Descriptor>::const_iterator rolesBegin() const { return m_roles.cbegin(); };
    std::list<Descriptor>::const_iterator rolesEnd() const { return m_roles.cend(); };
    std::list<Descriptor>::iterator rolesBegin() { return m_roles.begin(); };
    std::list<Descriptor>::iterator rolesEnd() { return m_roles.end(); };
    AdaptationSet &roleAdd(const Descriptor &role);
    AdaptationSet &roleAdd(Descriptor &&role);
    AdaptationSet &roleRemove(const Descriptor &role);
    AdaptationSet &roleRemove(const std::list<Descriptor>::const_iterator &);
    AdaptationSet &roleRemove(const std::list<Descriptor>::iterator &);

    // Rating children
    const std::list<Descriptor> &ratings() const { return m_ratings; };
    std::list<Descriptor>::const_iterator ratingsBegin() const { return m_ratings.cbegin(); };
    std::list<Descriptor>::const_iterator ratingsEnd() const { return m_ratings.cend(); };
    std::list<Descriptor>::iterator ratingsBegin() { return m_ratings.begin(); };
    std::list<Descriptor>::iterator ratingsEnd() { return m_ratings.end(); };
    AdaptationSet &ratingAdd(const Descriptor &rating);
    AdaptationSet &ratingAdd(Descriptor &&rating);
    AdaptationSet &ratingRemove(const Descriptor &rating);
    AdaptationSet &ratingRemove(const std::list<Descriptor>::const_iterator &);
    AdaptationSet &ratingRemove(const std::list<Descriptor>::iterator &);

    // Viewpoint children
    const std::list<Descriptor> &viewpoints() const { return m_viewpoints; };
    std::list<Descriptor>::const_iterator viewpointsBegin() const { return m_viewpoints.cbegin(); };
    std::list<Descriptor>::const_iterator viewpointsEnd() const { return m_viewpoints.cend(); };
    std::list<Descriptor>::iterator viewpointsBegin() { return m_viewpoints.begin(); };
    std::list<Descriptor>::iterator viewpointsEnd() { return m_viewpoints.end(); };
    AdaptationSet &viewpointAdd(const Descriptor &viewpoint);
    AdaptationSet &viewpointAdd(Descriptor &&viewpoint);
    AdaptationSet &viewpointRemove(const Descriptor &viewpoint);
    AdaptationSet &viewpointRemove(const std::list<Descriptor>::const_iterator &);
    AdaptationSet &viewpointRemove(const std::list<Descriptor>::iterator &);

    // ContentComponent children
    const std::list<ContentComponent> &contentComponents() const { return m_contentComponents; };
    std::list<ContentComponent>::const_iterator contentComponentsBegin() const { return m_contentComponents.cbegin(); };
    std::list<ContentComponent>::const_iterator contentComponentsEnd() const { return m_contentComponents.cend(); };
    std::list<ContentComponent>::iterator contentComponentsBegin() { return m_contentComponents.begin(); };
    std::list<ContentComponent>::iterator contentComponentsEnd() { return m_contentComponents.end(); };
    AdaptationSet &contentComponentAdd(const ContentComponent &content_component);
    AdaptationSet &contentComponentAdd(ContentComponent &&content_component);
    AdaptationSet &ContentComponentRemove(const ContentComponent &content_component);
    AdaptationSet &ContentComponentRemove(const std::list<ContentComponent>::const_iterator &);
    AdaptationSet &ContentComponentRemove(const std::list<ContentComponent>::iterator &);

    // BaseURL children
    const std::list<BaseURL> &baseURLs() const { return m_baseURLs; };
    std::list<BaseURL>::const_iterator baseURLsBegin() const { return m_baseURLs.cbegin(); };
    std::list<BaseURL>::const_iterator baseURLsEnd() const { return m_baseURLs.cend(); };
    std::list<BaseURL>::iterator baseURLsBegin() { return m_baseURLs.begin(); };
    std::list<BaseURL>::iterator baseURLsEnd() { return m_baseURLs.end(); };
    AdaptationSet &baseURLAdd(const BaseURL &base_url);
    AdaptationSet &baseURLAdd(BaseURL &&base_url);
    AdaptationSet &baseURLRemove(const BaseURL &base_url);
    AdaptationSet &baseURLRemove(const std::list<BaseURL>::const_iterator &);
    AdaptationSet &baseURLRemove(const std::list<BaseURL>::iterator &);
    std::list<BaseURL> getBaseURLs() const;

    // SegmentBase child
    bool hasSegmentBase() const { return m_segmentBase.has_value(); };
    const std::optional<SegmentBase> &segmentBase() const { return m_segmentBase; };
    AdaptationSet &segmentBase(const std::nullopt_t &) { m_segmentBase.reset(); return *this; };
    AdaptationSet &segmentBase(const SegmentBase &seg_base) { m_segmentBase = seg_base; return *this; };
    AdaptationSet &segmentBase(SegmentBase &&seg_base) { m_segmentBase = std::move(seg_base); return *this; };
    AdaptationSet &segmentBase(const std::optional<SegmentBase> &seg_base) { m_segmentBase = seg_base; return *this; };
    AdaptationSet &segmentBase(std::optional<SegmentBase> &&seg_base) { m_segmentBase = std::move(seg_base); return *this; };

    // SegmentList child
    bool hasSegmentList() const { return m_segmentList.has_value(); };
    const std::optional<SegmentList> &segmentList() const { return m_segmentList; };
    AdaptationSet &segmentList(const std::nullopt_t &) { m_segmentList.reset(); return *this; };
    AdaptationSet &segmentList(const SegmentList &seg_list) { m_segmentList = seg_list; return *this; };
    AdaptationSet &segmentList(SegmentList &&seg_list) { m_segmentList = std::move(seg_list); return *this; };
    AdaptationSet &segmentList(const std::optional<SegmentList> &seg_list) { m_segmentList = seg_list; return *this; };
    AdaptationSet &segmentList(std::optional<SegmentList> &&seg_list) { m_segmentList = std::move(seg_list); return *this; };

    // SegmentTemplate child
    bool hasSegmentTemplate() const { return m_segmentTemplate.has_value(); };
    const std::optional<SegmentTemplate> &segmentTemplate() const { return m_segmentTemplate; };
    AdaptationSet &segmentTemplate(const std::nullopt_t &) { m_segmentTemplate.reset(); return *this; };
    AdaptationSet &segmentTemplate(const SegmentTemplate &seg_template) {m_segmentTemplate = seg_template; return *this; };
    AdaptationSet &segmentTemplate(SegmentTemplate &&seg_template) {m_segmentTemplate = std::move(seg_template); return *this; };
    AdaptationSet &segmentTemplate(const std::optional<SegmentTemplate> &seg_template) {m_segmentTemplate = seg_template; return *this; };
    AdaptationSet &segmentTemplate(std::optional<SegmentTemplate> &&seg_template) {m_segmentTemplate = std::move(seg_template); return *this; };

    // Representation children
    const std::list<Representation> &representations() const { return m_representations; };
    std::list<Representation>::const_iterator representationsBegin() const { return m_representations.cbegin(); };
    std::list<Representation>::const_iterator representationsEnd() const { return m_representations.cend(); };
    std::list<Representation>::iterator representationsBegin() { return m_representations.begin(); };
    std::list<Representation>::iterator representationsEnd() { return m_representations.end(); };
    AdaptationSet &representationAdd(const Representation &representation);
    AdaptationSet &representationAdd(Representation &&representation);
    AdaptationSet &representationRemove(const Representation &representation);
    AdaptationSet &representationRemove(const std::list<Representation>::const_iterator &);
    AdaptationSet &representationRemove(const std::list<Representation>::iterator &);

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
     * This will remove the Representation, @a rep, from the set of selected Representation objects.
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
     * This will remove the Representation, referenced by the @a rep_it iterator, from the set of selected Representation objects.
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
     * segments available on or after @a query_time. The returned list will be empty if there are no media segments on or after
     * @a query_time available in the parent Period associated with this AdaptationSet, i.e. the @a query_time is after the end
     * of the Period or after the MPD/@@availabilityEndTime.
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

protected:
    friend class MPD;
    friend class Period;
    friend class Representation;

    /**
     * XML constructor (internal use only)
     *
     * Create a new AdaptationSet from an XML \AdaptationSet element.
     *
     * @param node The libxml++ Node for the \AdaptationSet element to ingest.
     * @return A new AdaptationSet
     */
    AdaptationSet(xmlpp::Node &node);

    /**
     * Set a libxml++ Element attributes and children for XML output
     *
     * This will set all relevant attributes and child elements from the settings of this AdaptationSet.
     *
     * @param element The libxml++ Element to populate.
     */
    void setXMLElement(xmlpp::Element&) const;

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
     * Using the @a vars, get a media URL by applying a SegmentTemplate or SegmentList attached to this AdaptationSet.
     *
     * @param vars The segment variables to apply to any template or list index.
     * @return The URL string for the media or an empty string if no template or list could be found.
     */
    std::string getMediaURL(const SegmentTemplate::Variables &vars) const;

    /**
     * Get an initialization segment URL
     *
     * Using the @a vars, get an initialization segment URL by applying a SegmentTemplate or SegmentList attached to this
     * AdaptationSet.
     *
     * @param vars The segment variables to apply to any template or list index.
     * @return The URL string for the initialization segment or an empty string if no template or list could be found.
     */
    std::string getInitializationURL(const SegmentTemplate::Variables &vars) const;

    /**
     * Get the media segment availability and URL
     *
     * Using the @a vars, get media segment metadata by applying a SegmentTemplate or SegmentList attached to this AdaptationSet.
     *
     * @param vars The segment variables to apply to any template or list index.
     * @return The segment availability times and URL. The URL will be empty if no suitable segment could be found.
     */
    SegmentAvailability getMediaAvailability(const SegmentTemplate::Variables &vars) const;

    /**
     * Get the initialization segment availability and URL
     *
     * Using the @a vars, get initialization segment metadata by applying a SegmentTemplate or SegmentList attached to this
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

private:
    Period *m_period;                                              ///< The Period object this adaptation set is a child of
    std::unordered_set<const Representation*> m_selectedRepresentations; ///< An index to the set of selected Representation entries

    // Period attributes (ISO 23009-1:2022 Table 5)
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

    // Period child elements (ISO 23009-1:2022 Table 5)
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
