#ifndef _BBC_PARSE_DASH_MPD_ADAPTATION_SET_HH_
#define _BBC_PARSE_DASH_MPD_ADAPTATION_SET_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: AdaptationSet class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <iostream>
#include <string>
#include <list>

#include "macros.hh"
#include "Accessibility.hh"
#include "BaseURL.hh"
#include "ContentComponent.hh"
#include "Descriptor.hh"
#include "EventStream.hh"
#include "Label.hh"
#include "Preselection.hh"
#include "Rating.hh"
#include "Role.hh"
#include "Representation.hh"
#include "RFC6838ContentType.hh"
#include "RatioType.hh"
#include "FrameRate.hh"
#include "Sap.hh"
#include "SegmentBase.hh"
#include "SegmentTemplate.hh"
#include "SegmentList.hh"
#include "ServiceDescription.hh"
#include "Subset.hh"
#include "Viewpoint.hh"
#include "XLink.hh"


namespace xmlpp {
    class Element;
    class Node;
}

LIBPARSEMPD_NAMESPACE_BEGIN

class Period;
class Acccessibility;
class Role;
class Rating;
class Viewpoint;
class ContentComponent;

class LIBPARSEMPD_PUBLIC_API AdaptationSet {
public:
    AdaptationSet() {};
    AdaptationSet(const AdaptationSet &to_copy);
    AdaptationSet(AdaptationSet &&to_move);

    AdaptationSet &operator=(const AdaptationSet &to_copy);
    AdaptationSet &operator=(AdaptationSet &&to_move);



    bool operator==(const AdaptationSet &) const { return true; };

    bool hasId() const { return m_id.has_value(); };
    const std::optional<unsigned int> &id() const { return m_id; };
    AdaptationSet &id(const std::nullopt_t &) { m_id.reset(); return *this;};
    AdaptationSet &id(unsigned int id) { m_id = id; return *this;};
    AdaptationSet &id(const std::optional<unsigned int> &id) { m_id = id; return *this;};
    AdaptationSet &id(std::optional<unsigned int> &&id) { m_id = std::move(id);return *this;};

    bool hasGroup() const { return m_group.has_value(); };
    const std::optional<unsigned int> &group() const { return m_group; };
    AdaptationSet &group(const std::nullopt_t &) { m_group.reset(); return *this;};
    AdaptationSet &group(unsigned int group) { m_group = group; return *this;};
    AdaptationSet &group(const std::optional<unsigned int> &group) { m_group = group; return *this;};
    AdaptationSet &group(std::optional<unsigned int> &&group) { m_group = std::move(group);return *this;};
    
    bool haslang() const { return m_lang.has_value(); };
    const std::optional<std::string> &lang() const { return m_lang; };
    AdaptationSet &lang(const std::nullopt_t &) { m_lang.reset(); return *this; };
    AdaptationSet &lang(const std::string &lang) { m_lang = lang; return *this; };
    AdaptationSet &lang(std::string &&lang) { m_lang = std::move(lang); return *this; };
    AdaptationSet &lang(const std::optional<std::string> &lang) { m_lang = lang; return *this; };
    AdaptationSet &lang(std::optional<std::string> &&lang) { m_lang = std::move(lang); return *this; };

    bool hasContentType() const { return m_contentType.has_value(); };
    const std::optional<RFC6838ContentType> &contentType() const {return m_contentType;};
    AdaptationSet &contentType(const std::nullopt_t &) { m_contentType.reset(); return *this; };
    AdaptationSet &contentType(const RFC6838ContentType &contentType) {m_contentType = contentType; return *this;};
    AdaptationSet &contentType(const RFC6838ContentType &&contentType) {m_contentType = std::move(contentType); return *this;};
    AdaptationSet &contentType(const std::optional<RFC6838ContentType> &contentType) { m_contentType = contentType; return *this;};
    AdaptationSet &contentType(const std::optional<RFC6838ContentType> &&contentType) { m_contentType = std::move(contentType); return *this;};

    bool hasPar() const { return m_par.has_value(); };
    const std::optional<RatioType> &par() const {return m_par;};
    AdaptationSet &par(const std::nullopt_t &) { m_par.reset(); return *this; };
    AdaptationSet &par(const RatioType &par) {m_par = par; return *this;};
    AdaptationSet &par(const RatioType &&par) {m_par = std::move(par); return *this;};
    AdaptationSet &par(const std::optional<RatioType> &par) { m_par = par; return *this;};
    AdaptationSet &par(const std::optional<RatioType> &&par) { m_par = std::move(par); return *this;};

    bool hasMinBandwidth() const { return m_minBandwidth.has_value(); };
    const std::optional<double> &minBandwidth() const { return m_minBandwidth; };
    AdaptationSet &minBandwidth(const std::nullopt_t &) { m_minBandwidth.reset(); return *this;};
    AdaptationSet &minBandwidth(double minBandwidth) { m_minBandwidth = minBandwidth; return *this;};
    AdaptationSet &minBandwidth(const std::optional<double> &minBandwidth) { m_minBandwidth = minBandwidth; return *this;};
    AdaptationSet &minBandwidth(std::optional<double> &&minBandwidth) { m_minBandwidth = std::move(minBandwidth);return *this;};

    bool hasMaxBandwidth() const { return m_maxBandwidth.has_value(); };
    const std::optional<double> &maxBandwidth() const { return m_maxBandwidth; };
    AdaptationSet &maxBandwidth(const std::nullopt_t &) { m_maxBandwidth.reset(); return *this;};
    AdaptationSet &maxBandwidth(double maxBandwidth) { m_maxBandwidth = maxBandwidth; return *this;};
    AdaptationSet &maxBandwidth(const std::optional<double> &maxBandwidth) { m_maxBandwidth = maxBandwidth; return *this;};
    AdaptationSet &maxBandwidth(std::optional<double> &&maxBandwidth) { m_maxBandwidth = std::move(maxBandwidth);return *this;};

    bool hasMinWidth() const { return m_minWidth.has_value(); };
    const std::optional<unsigned int> &minWidth() const { return m_minWidth; };
    AdaptationSet &minWidth(const std::nullopt_t &) { m_minWidth.reset(); return *this;};
    AdaptationSet &minWidth(unsigned int minWidth) { m_minWidth = minWidth; return *this;};
    AdaptationSet &minWidth(const std::optional<unsigned int> &minWidth) { m_minWidth = minWidth; return *this;};
    AdaptationSet &minWidth(std::optional<unsigned int> &&minWidth) { m_minWidth = std::move(minWidth);return *this;};

    bool hasMaxWidth() const { return m_maxWidth.has_value(); };
    const std::optional<unsigned int> &maxWidth() const { return m_maxWidth; };
    AdaptationSet &maxWidth(const std::nullopt_t &) { m_maxWidth.reset(); return *this;};
    AdaptationSet &maxWidth(unsigned int maxWidth) { m_maxWidth = maxWidth; return *this;};
    AdaptationSet &maxWidth(const std::optional<unsigned int> &maxWidth) { m_maxWidth = maxWidth; return *this;};
    AdaptationSet &maxWidth(std::optional<unsigned int> &&maxWidth) { m_maxWidth = std::move(maxWidth);return *this;};

    bool hasMinHeight() const { return m_minHeight.has_value(); };
    const std::optional<unsigned int> &minHeight() const { return m_minHeight; };
    AdaptationSet &minHeight(const std::nullopt_t &) { m_minHeight.reset(); return *this;};
    AdaptationSet &minHeight(unsigned int minHeight) { m_minHeight = minHeight; return *this;};
    AdaptationSet &minHeight(const std::optional<unsigned int> &minHeight) { m_minHeight = minHeight; return *this;};
    AdaptationSet &minHeight(std::optional<unsigned int> &&minHeight) { m_minHeight = std::move(minHeight);return *this;};
    
    bool hasMaxHeight() const { return m_maxHeight.has_value(); };
    const std::optional<unsigned int> &maxHeight() const { return m_maxHeight; };
    AdaptationSet &maxHeight(const std::nullopt_t &) { m_maxHeight.reset(); return *this;};
    AdaptationSet &maxHeight(unsigned int maxHeight) { m_maxHeight = maxHeight; return *this;};
    AdaptationSet &maxHeight(const std::optional<unsigned int> &maxHeight) { m_maxHeight = maxHeight; return *this;};
    AdaptationSet &maxHeight(std::optional<unsigned int> &&maxHeight) { m_maxHeight = std::move(maxHeight);return *this;};

    bool hasMinFrameRate() const { return m_minFrameRate.has_value(); };
    const std::optional<FrameRate> &minFrameRate() const {return m_minFrameRate;};
    AdaptationSet &minFrameRate(const std::nullopt_t &) { m_minFrameRate.reset(); return *this; };
    AdaptationSet &minFrameRate(const FrameRate &minFrameRate) {m_minFrameRate = minFrameRate; return *this;};
    AdaptationSet &minFrameRate(const FrameRate &&minFrameRate) {m_minFrameRate = std::move(minFrameRate); return *this;};
    AdaptationSet &minFrameRate(const std::optional<FrameRate> &minFrameRate) { m_minFrameRate = minFrameRate; return *this;};
    AdaptationSet &minFrameRate(const std::optional<FrameRate> &&minFrameRate) { m_minFrameRate = std::move(minFrameRate); return *this;};

    bool hasMaxFrameRate() const { return m_maxFrameRate.has_value(); };
    const std::optional<FrameRate> &maxFrameRate() const {return m_maxFrameRate;};
    AdaptationSet &maxFrameRate(const std::nullopt_t &) { m_maxFrameRate.reset(); return *this; };
    AdaptationSet &maxFrameRate(const FrameRate &maxFrameRate) {m_maxFrameRate = maxFrameRate; return *this;};
    AdaptationSet &maxFrameRate(const FrameRate &&maxFrameRate) {m_maxFrameRate = std::move(maxFrameRate); return *this;};
    AdaptationSet &maxFrameRate(const std::optional<FrameRate> &maxFrameRate) { m_maxFrameRate = maxFrameRate; return *this;};
    AdaptationSet &maxFrameRate(const std::optional<FrameRate> &&maxFrameRate) { m_maxFrameRate = std::move(maxFrameRate); return *this;};

    bool hasSegmentAlignment() const { return m_segmentAlignment.has_value(); };
    const std::optional<bool> &segmentAlignment() const { return m_segmentAlignment; };
    AdaptationSet &segmentAlignment(const std::nullopt_t &) { m_segmentAlignment.reset(); return *this;};
    AdaptationSet &segmentAlignment(bool segmentAlignment) { m_segmentAlignment = segmentAlignment; return *this;};
    AdaptationSet &segmentAlignment(const std::optional<bool> &segmentAlignment) { m_segmentAlignment = segmentAlignment; return *this;};
    AdaptationSet &segmentAlignment(std::optional<bool> &&segmentAlignment) { m_segmentAlignment = std::move(segmentAlignment);return *this;};

    bool bitstreamSwitching() const { return m_bitstreamSwitching; };
    AdaptationSet &bitstreamSwitching(bool bitstream_switching) { m_bitstreamSwitching = bitstream_switching; return *this; };

    bool hasSubsegmentAlignment() const { return m_subsegmentAlignment.has_value(); };
    const std::optional<bool> &subsegmentAlignment() const { return m_subsegmentAlignment; };
    AdaptationSet &subsegmentAlignment(const std::nullopt_t &) { m_subsegmentAlignment.reset(); return *this;};
    AdaptationSet &subsegmentAlignment(bool subsegmentAlignment) { m_subsegmentAlignment = subsegmentAlignment; return *this;};
    AdaptationSet &subsegmentAlignment(const std::optional<bool> &subsegmentAlignment) { m_subsegmentAlignment = subsegmentAlignment; return *this;};
    AdaptationSet &subsegmentAlignment(std::optional<bool> &&subsegmentAlignment) { m_subsegmentAlignment = std::move(subsegmentAlignment);return *this;};

    bool hasSubsegmentStartsWithSAP() const { return m_subsegmentStartsWithSAP.has_value(); };
    const std::optional<Sap> &subsegmentStartsWithSAP() const {return m_subsegmentStartsWithSAP;};
    AdaptationSet &subsegmentStartsWithSAP(const std::nullopt_t &) { m_subsegmentStartsWithSAP.reset(); return *this; };
    AdaptationSet &subsegmentStartsWithSAP(const Sap &subsegmentStartsWithSAP) {m_subsegmentStartsWithSAP = subsegmentStartsWithSAP; return *this;};
    AdaptationSet &subsegmentStartsWithSAP(const Sap &&subsegmentStartsWithSAP) {m_subsegmentStartsWithSAP = std::move(subsegmentStartsWithSAP); return *this;};
    AdaptationSet &subsegmentStartsWithSAP(const std::optional<Sap> &subsegmentStartsWithSAP) { m_subsegmentStartsWithSAP = subsegmentStartsWithSAP; return *this;};
    AdaptationSet &subsegmentStartsWithSAP(const std::optional<Sap> &&subsegmentStartsWithSAP) { m_subsegmentStartsWithSAP = std::move(subsegmentStartsWithSAP); return *this;};

    const std::list<unsigned int> &initializationSetRefs() const { return m_initializationSetRefs; };
    AdaptationSet &initializationSetRefs(std::list<unsigned int> initializationSetRefs) { m_initializationSetRefs = initializationSetRefs; return *this;};
    
    bool hasinitializationPrincipal() const { return m_initializationPrincipal.has_value(); };
    const std::optional<std::string> &initializationPrincipal() const { return m_initializationPrincipal; };
    AdaptationSet &initializationPrincipal(const std::nullopt_t &) { m_initializationPrincipal.reset(); return *this; };
    AdaptationSet &initializationPrincipal(const std::string &initializationPrincipal) { m_initializationPrincipal = initializationPrincipal; return *this; };
    AdaptationSet &initializationPrincipal(std::string &&initializationPrincipal) { m_initializationPrincipal = std::move(initializationPrincipal); return *this; };
    AdaptationSet &initializationPrincipal(const std::optional<std::string> &initializationPrincipal) { m_initializationPrincipal = initializationPrincipal; return *this; };
    AdaptationSet &initializationPrincipal(std::optional<std::string> &&initializationPrincipal) { m_lang = std::move(initializationPrincipal); return *this; };

    //std::list<Accessibility>       m_accessibility;
    const std::list<Accessibility> &accessibility() const { return m_accessibility; };
    std::list<Accessibility>::const_iterator accessibilityBegin() const { return m_accessibility.cbegin(); };
    std::list<Accessibility>::const_iterator accessibilityEnd() const { return m_accessibility.cend(); };
    std::list<Accessibility>::iterator accessibilityBegin() { return m_accessibility.begin(); };
    std::list<Accessibility>::iterator accessibilityEnd() { return m_accessibility.end(); };
    AdaptationSet &accessibilityAdd(const Accessibility &accessibility);
    AdaptationSet &accessibilityAdd(Accessibility &&accessibility);
    AdaptationSet &accessibilityRemove(const Accessibility &accessibility);
    AdaptationSet &accessibilityRemove(const std::list<Accessibility>::const_iterator &);
    AdaptationSet &accessibilityRemove(const std::list<Accessibility>::iterator &);

    //std::list<Role>                m_roles;
    const std::list<Role> &roles() const { return m_roles; };
    std::list<Role>::const_iterator rolesBegin() const { return m_roles.cbegin(); };
    std::list<Role>::const_iterator rolesEnd() const { return m_roles.cend(); };
    std::list<Role>::iterator rolesBegin() { return m_roles.begin(); };
    std::list<Role>::iterator rolesEnd() { return m_roles.end(); };
    AdaptationSet &roleAdd(const Role &role);
    AdaptationSet &roleAdd(Role &&role);
    AdaptationSet &roleRemove(const Role &role);
    AdaptationSet &roleRemove(const std::list<Role>::const_iterator &);
    AdaptationSet &roleRemove(const std::list<Role>::iterator &);

    //std::list<Rating>              m_ratings;
    const std::list<Rating> &ratings() const { return m_ratings; };
    std::list<Rating>::const_iterator ratingsBegin() const { return m_ratings.cbegin(); };
    std::list<Rating>::const_iterator ratingsEnd() const { return m_ratings.cend(); };
    std::list<Rating>::iterator ratingsBegin() { return m_ratings.begin(); };
    std::list<Rating>::iterator ratingsEnd() { return m_ratings.end(); };
    AdaptationSet &ratingAdd(const Rating &rating);
    AdaptationSet &ratingAdd(Rating &&rating);
    AdaptationSet &ratingRemove(const Rating &rating);
    AdaptationSet &ratingRemove(const std::list<Rating>::const_iterator &);
    AdaptationSet &ratingRemove(const std::list<Rating>::iterator &);

    //std::list<Viewpoint>           m_viewpoints;
    const std::list<Viewpoint> &viewpoints() const { return m_viewpoints; };
    std::list<Viewpoint>::const_iterator viewpointsBegin() const { return m_viewpoints.cbegin(); };
    std::list<Viewpoint>::const_iterator viewpointsEnd() const { return m_viewpoints.cend(); };
    std::list<Viewpoint>::iterator viewpointsBegin() { return m_viewpoints.begin(); };
    std::list<Viewpoint>::iterator viewpointsEnd() { return m_viewpoints.end(); };
    AdaptationSet &viewpointAdd(const Viewpoint &viewpoint);
    AdaptationSet &viewpointAdd(Viewpoint &&viewpoint);
    AdaptationSet &viewpointRemove(const Viewpoint &viewpoint);
    AdaptationSet &viewpointRemove(const std::list<Viewpoint>::const_iterator &);
    AdaptationSet &viewpointRemove(const std::list<Viewpoint>::iterator &);

    //std::list<ContentComponent>    m_contentComponent;
    const std::list<ContentComponent> &contentComponents() const { return m_contentComponents; };
    std::list<ContentComponent>::const_iterator contentComponentsBegin() const { return m_contentComponents.cbegin(); };
    std::list<ContentComponent>::const_iterator contentComponentsEnd() const { return m_contentComponents.cend(); };
    std::list<ContentComponent>::iterator contentComponentsBegin() { return m_contentComponents.begin(); };
    std::list<ContentComponent>::iterator contentComponentsEnd() { return m_contentComponents.end(); };
    AdaptationSet &contentComponentAdd(const ContentComponent &ContentComponent);
    AdaptationSet &contentComponentAdd(ContentComponent &&ContentComponent);
    AdaptationSet &ContentComponentRemove(const ContentComponent &ContentComponenti);
    AdaptationSet &ContentComponentRemove(const std::list<ContentComponent>::const_iterator &);
    AdaptationSet &ContentComponentRemove(const std::list<ContentComponent>::iterator &);

    //std::list<BaseURL>             m_baseURLs;
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

    //std::optional<SegmentBase>     m_segmentBase;
    bool hasSegmentBase() const { return m_segmentBase.has_value(); };
    const std::optional<SegmentBase> &segmentBase() const { return m_segmentBase; };
    AdaptationSet &segmentBase(const std::nullopt_t &) { m_segmentBase.reset(); return *this; };
    AdaptationSet &segmentBase(const SegmentBase &seg_base) { m_segmentBase = seg_base; return *this; };
    AdaptationSet &segmentBase(SegmentBase &&seg_base) { m_segmentBase = std::move(seg_base); return *this; };
    AdaptationSet &segmentBase(const std::optional<SegmentBase> &seg_base) { m_segmentBase = seg_base; return *this; };
    AdaptationSet &segmentBase(std::optional<SegmentBase> &&seg_base) { m_segmentBase = std::move(seg_base); return *this; };

    //std::optional<SegmentList>     m_segmentList;
    bool hasSegmentList() const { return m_segmentList.has_value(); };
    const std::optional<SegmentList> &segmentList() const { return m_segmentList; };
    AdaptationSet &segmentList(const std::nullopt_t &) { m_segmentList.reset(); return *this; };
    AdaptationSet &segmentList(const SegmentList &seg_list) { m_segmentList = seg_list; return *this; };
    AdaptationSet &segmentList(SegmentList &&seg_list) { m_segmentList = std::move(seg_list); return *this; };
    AdaptationSet &segmentList(const std::optional<SegmentList> &seg_list) { m_segmentList = seg_list; return *this; };
    AdaptationSet &segmentList(std::optional<SegmentList> &&seg_list) { m_segmentList = std::move(seg_list); return *this; };

    //std::optional<SegmentTemplate> m_segmentTemplate;
    bool hasSegmentTemplate() const { return m_segmentTemplate.has_value(); };
    const std::optional<SegmentTemplate> &segmentTemplate() const { return m_segmentTemplate; };
    AdaptationSet &segmentTemplate(const std::nullopt_t &) { m_segmentTemplate.reset(); return *this; };
    AdaptationSet &segmentTemplate(const SegmentTemplate &seg_template) {m_segmentTemplate = seg_template; return *this; };
    AdaptationSet &segmentTemplate(SegmentTemplate &&seg_template) {m_segmentTemplate = std::move(seg_template); return *this; };
    AdaptationSet &segmentTemplate(const std::optional<SegmentTemplate> &seg_template) {m_segmentTemplate = seg_template; return *this; };
    AdaptationSet &segmentTemplate(std::optional<SegmentTemplate> &&seg_template) {m_segmentTemplate = std::move(seg_template); return *this; };

    //std::list<Representation>      m_representations;
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


    
    AdaptationSet &setPeriod(Period *period) { m_period = period; return *this; };

protected:
    friend class MPD;
    friend class Period;
    AdaptationSet(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    Period *m_period;

    // Period attributes (ISO 23009-1:2022 Table 5)
    std::optional<XLink>           m_xlink;
    std::optional<unsigned int>    m_id;
    std::optional<unsigned int>    m_group;
    std::optional<std::string>     m_lang;
    std::optional<RFC6838ContentType>     m_contentType;
    std::optional<RatioType>       m_par;
    std::optional<double>          m_minBandwidth;
    std::optional<double>          m_maxBandwidth;
    std::optional<unsigned int>    m_minWidth;
    std::optional<unsigned int>    m_maxWidth;
    std::optional<unsigned int>    m_minHeight;
    std::optional<unsigned int>    m_maxHeight;
    std::optional<FrameRate>       m_minFrameRate;
    std::optional<FrameRate>       m_maxFrameRate;
    std::optional<bool>            m_segmentAlignment;
    bool                           m_bitstreamSwitching;
    std::optional<bool>            m_subsegmentAlignment;
    std::optional<Sap>             m_subsegmentStartsWithSAP;
    std::list<unsigned int>        m_initializationSetRefs;
    std::optional<std::string>     m_initializationPrincipal;
    
    // Period child elements (ISO 23009-1:2022 Table 5)
    std::list<Accessibility>       m_accessibility;
    std::list<Role>                m_roles;
    std::list<Rating>              m_ratings;
    std::list<Viewpoint>           m_viewpoints;
    std::list<ContentComponent>    m_contentComponents;
    std::list<BaseURL>             m_baseURLs;
    std::optional<SegmentBase>     m_segmentBase;
    std::optional<SegmentList>     m_segmentList;
    std::optional<SegmentTemplate> m_segmentTemplate;
    std::list<Representation>      m_representations;

};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_ADAPTATION_SET_HH_*/
