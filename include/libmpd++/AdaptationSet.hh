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
#include <string>
#include <list>
#include <optional>
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

class LIBMPDPP_PUBLIC_API AdaptationSet : public RepresentationBase {
public:
    AdaptationSet();
    AdaptationSet(const AdaptationSet&);
    AdaptationSet(AdaptationSet&&);

    virtual ~AdaptationSet() {};

    AdaptationSet &operator=(const AdaptationSet&);
    AdaptationSet &operator=(AdaptationSet&&);

    bool operator==(const AdaptationSet &) const;

    // @id
    bool hasId() const { return m_id.has_value(); };
    const std::optional<unsigned int> &id() const { return m_id; };
    AdaptationSet &id(const std::nullopt_t &) { m_id.reset(); return *this;};
    AdaptationSet &id(unsigned int id) { m_id = id; return *this;};
    AdaptationSet &id(const std::optional<unsigned int> &id) { m_id = id; return *this;};
    AdaptationSet &id(std::optional<unsigned int> &&id) { m_id = std::move(id);return *this;};

    // @group
    bool hasGroup() const { return m_group.has_value(); };
    const std::optional<unsigned int> &group() const { return m_group; };
    AdaptationSet &group(const std::nullopt_t &) { m_group.reset(); return *this;};
    AdaptationSet &group(unsigned int group) { m_group = group; return *this;};
    AdaptationSet &group(const std::optional<unsigned int> &group) { m_group = group; return *this;};
    AdaptationSet &group(std::optional<unsigned int> &&group) { m_group = std::move(group);return *this;};
    
    // @lang
    bool hasLang() const { return m_lang.has_value(); };
    const std::optional<std::string> &lang() const { return m_lang; };
    AdaptationSet &lang(const std::nullopt_t &) { m_lang.reset(); return *this; };
    AdaptationSet &lang(const std::string &lang) { m_lang = lang; return *this; };
    AdaptationSet &lang(std::string &&lang) { m_lang = std::move(lang); return *this; };
    AdaptationSet &lang(const std::optional<std::string> &lang) { m_lang = lang; return *this; };
    AdaptationSet &lang(std::optional<std::string> &&lang) { m_lang = std::move(lang); return *this; };

    // @contentType
    bool hasContentType() const { return m_contentType.has_value(); };
    const std::optional<RFC6838ContentType> &contentType() const {return m_contentType;};
    AdaptationSet &contentType(const std::nullopt_t &) { m_contentType.reset(); return *this; };
    AdaptationSet &contentType(const RFC6838ContentType &content_type) {m_contentType = content_type; return *this;};
    AdaptationSet &contentType(RFC6838ContentType &&content_type) {m_contentType = std::move(content_type); return *this;};
    AdaptationSet &contentType(const std::optional<RFC6838ContentType> &content_type) { m_contentType = content_type; return *this;};
    AdaptationSet &contentType(std::optional<RFC6838ContentType> &&content_type) { m_contentType = std::move(content_type); return *this;};

    // @par
    bool hasPar() const { return m_par.has_value(); };
    const std::optional<Ratio> &par() const {return m_par;};
    AdaptationSet &par(const std::nullopt_t &) { m_par.reset(); return *this; };
    AdaptationSet &par(const Ratio &par) {m_par = par; return *this;};
    AdaptationSet &par(Ratio &&par) {m_par = std::move(par); return *this;};
    AdaptationSet &par(const std::optional<Ratio> &par) { m_par = par; return *this;};
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

    // @segmentAlignment
    bool segmentAlignment() const { return m_segmentAlignment; };
    AdaptationSet &segmentAlignment(bool segment_alignment) { m_segmentAlignment = segment_alignment; return *this;};

    // @subsegmentAlignment
    bool subsegmentAlignment() const { return m_subsegmentAlignment; };
    AdaptationSet &subsegmentAlignment(bool subsegment_alignment) { m_subsegmentAlignment = subsegment_alignment; return *this;};

    // @subsegmentStartsWithSAP
    const SAP &subsegmentStartsWithSAP() const {return m_subsegmentStartsWithSAP;};
    AdaptationSet &subsegmentStartsWithSAP(const SAP &subsegment_starts_with_sap) {m_subsegmentStartsWithSAP = subsegment_starts_with_sap; return *this;};
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

    void selectAllRepresentations();
    void selectRepresentation(const Representation&, bool deselect_others = false);
    void selectRepresentation(const std::list<Representation>::const_iterator&, bool deselect_others = false);
    void selectRepresentation(const std::list<Representation>::iterator&, bool deselect_others = false);

    void deselectAllRepresentations();
    void deselectRepresentation(const Representation&);
    void deselectRepresentation(const std::list<Representation>::const_iterator&);
    void deselectRepresentation(const std::list<Representation>::iterator&);

protected:
    friend class MPD;
    friend class Period;
    friend class Representation;
    AdaptationSet(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
    AdaptationSet &setPeriod(Period *period) { m_period = period; return *this; };
    std::string getMediaURL(const SegmentTemplate::Variables &) const;
    std::string getInitializationURL(const SegmentTemplate::Variables &) const;

private:
    Period *m_period;
    std::unordered_set<const Representation*> m_selectedRepresentations;

    // Period attributes (ISO 23009-1:2022 Table 5)
    std::optional<XLink>               m_xlink;
    std::optional<unsigned int>        m_id;
    std::optional<unsigned int>        m_group;
    std::optional<std::string>         m_lang;
    std::optional<RFC6838ContentType>  m_contentType;
    std::optional<Ratio>               m_par;
    std::optional<unsigned int>        m_minBandwidth;
    std::optional<unsigned int>        m_maxBandwidth;
    std::optional<unsigned int>        m_minWidth;
    std::optional<unsigned int>        m_maxWidth;
    std::optional<unsigned int>        m_minHeight;
    std::optional<unsigned int>        m_maxHeight;
    std::optional<FrameRate>           m_minFrameRate;
    std::optional<FrameRate>           m_maxFrameRate;
    bool                               m_segmentAlignment;
    bool                               m_subsegmentAlignment;
    SAP                                m_subsegmentStartsWithSAP;
    std::optional<bool>                m_bitstreamSwitching;
    std::list<unsigned int>            m_initializationSetRefs;
    std::optional<URI>                 m_initializationPrincipal;
    
    // Period child elements (ISO 23009-1:2022 Table 5)
    std::list<Descriptor>          m_accessibilities;
    std::list<Descriptor>          m_roles;
    std::list<Descriptor>          m_ratings;
    std::list<Descriptor>          m_viewpoints;
    std::list<ContentComponent>    m_contentComponents;
    std::list<BaseURL>             m_baseURLs;
    std::optional<SegmentBase>     m_segmentBase;
    std::optional<SegmentList>     m_segmentList;
    std::optional<SegmentTemplate> m_segmentTemplate;
    std::list<Representation>      m_representations;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_ADAPTATION_SET_HH_*/
