#ifndef _BBC_PARSE_DASH_MPD_ADAPTATION_SET_HH_
#define _BBC_PARSE_DASH_MPD_ADAPTATION_SET_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: AdaptationSet class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
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

    bool operator==(const AdaptationSet &) const { return true; };

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
    std::list<ContentComponent>    m_contentComponent;
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
