#ifndef _BBC_PARSE_DASH_MPD_REPRESENTATION_HH_
#define _BBC_PARSE_DASH_MPD_REPRESENTATION_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Representation class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
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
#include "BaseURL.hh"
#include "ContentProtection.hh"
#include "Descriptor.hh"
#include "EventStream.hh"
#include "ExtendedBandwidth.hh"
#include "Label.hh"
#include "Preselection.hh"
#include "SegmentBase.hh"
#include "SegmentTemplate.hh"
#include "SegmentList.hh"
#include "ServiceDescription.hh"
#include "SubRepresentation.hh"
#include "Subset.hh"
#include "XLink.hh"

namespace xmlpp {
    class Element;
    class Node;
}

LIBPARSEMPD_NAMESPACE_BEGIN

class LIBPARSEMPD_PUBLIC_API Representation {
public:
    using duration_type = std::chrono::microseconds;

    Representation();
    Representation(const Representation &to_copy);
    Representation(Representation &&to_move);

    virtual ~Representation() {};

    Representation &operator=(const Representation &to_copy);
    Representation &operator=(Representation &&to_move);

    bool operator==(const Representation &to_compare) const;

    Representation &setMPD(MPD *mpd) { m_mpd = mpd; return *this; };
    MPD *getMPD() { return m_mpd; };
    const MPD *getMPD() const { return m_mpd; };

    const std::string &id() const { return m_id; };
    Representation &id(const std::string &id) { m_id = id; return *this; };
    Representation &id(std::string &&id) { m_id = std::move(id); return *this; };

    const double &bandwidth() const { return m_bandwidth; };
    Representation &bandwidth(const double &bandwidth) { m_bandwidth = bandwidth; return *this; };
    Representation &bandwidth(double &&bandwidth) { m_bandwidth = std::move(bandwidth); return *this; };

    bool hasQualityRanking() const { return m_qualityRanking.has_value(); };
    const std::optional<int> &qualityRanking() const { return m_qualityRanking; };
    Representation &qualityRanking(const std::nullopt_t &) { m_qualityRanking.reset(); return *this; };
    Representation &qualityRanking(const int &qRanking) { m_qualityRanking = qRanking; return *this; };
    Representation &qualityRanking(const std::optional<int> &qRanking) { m_qualityRanking = qRanking; return *this; };

    std::list<std::string> &dependencyId() { return m_dependencyIds; };

    std::list<std::string> &associationId() { return m_associationIds; };

    std::list<std::string> &associationType() { return m_associationTypes; };

    std::list<std::string> &mediaStreamStructureId() { return m_mediaStreamStructureIds; };

protected:
    friend class MPD;
    friend class AdaptationSet;
    Representation(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    MPD                           *m_mpd;
    AdaptationSet                 *m_adaptationSet;

    // Representation attributes (ISO 23009-1:2022 Table 9)
    std::string                    m_id;
    double                         m_bandwidth;
    std::optional<int>             m_qualityRanking; 
    std::list<std::string>         m_dependencyIds;
    std::list<std::string>         m_associationIds;
    std::list<std::string>         m_associationTypes;
    std::list<std::string>         m_mediaStreamStructureIds;

    // Representation child elements (ISO 23009-1:2022 Table 9)
    std::list<BaseURL>             m_baseURLs;
    std::list<ExtendedBandwidth>   m_extendedBandwidths;
    std::list<SubRepresentation>   m_subRepresentations;
    std::optional<SegmentBase>     m_segmentBase;
    std::optional<SegmentList>     m_segmentList;
    std::optional<SegmentTemplate> m_segmentTemplate;
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_REPRESENTATION_HH_*/

