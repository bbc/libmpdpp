#ifndef _BBC_PARSE_DASH_MPD_REPRESENTATION_HH_
#define _BBC_PARSE_DASH_MPD_REPRESENTATION_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Representation class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
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
#include "BaseURL.hh"
#include "ContentProtection.hh"
#include "Descriptor.hh"
#include "EventStream.hh"
#include "ExtendedBandwidth.hh"
#include "Label.hh"
#include "Preselection.hh"
#include "RepresentationBase.hh"
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

class LIBPARSEMPD_PUBLIC_API Representation : public RepresentationBase {
public:
    Representation();
    Representation(const Representation &to_copy);
    Representation(Representation &&to_move);

    virtual ~Representation() {};

    Representation &operator=(const Representation &to_copy);
    Representation &operator=(Representation &&to_move);

    bool operator==(const Representation &to_compare) const;

    MPD *getMPD();
    const MPD *getMPD() const;

    const std::string &id() const { return m_id; };
    Representation &id(const std::string &id) { m_id = id; return *this; };
    Representation &id(std::string &&id) { m_id = std::move(id); return *this; };

    unsigned int bandwidth() const { return m_bandwidth; };
    Representation &bandwidth(unsigned int bandwidth) { m_bandwidth = bandwidth; return *this; };

    bool hasQualityRanking() const { return m_qualityRanking.has_value(); };
    const std::optional<unsigned int> &qualityRanking() const { return m_qualityRanking; };
    Representation &qualityRanking(const std::nullopt_t &) { m_qualityRanking.reset(); return *this; };
    Representation &qualityRanking(unsigned int qual_rank) { m_qualityRanking = qual_rank; return *this; };
    Representation &qualityRanking(const std::optional<unsigned int> &qual_rank) { m_qualityRanking = qual_rank; return *this; };

    const std::list<std::string> &dependencyId() const { return m_dependencyIds; };

    const std::list<std::string> &associationId() const { return m_associationIds; };

    const std::list<std::string> &associationType() const { return m_associationTypes; };

    const std::list<std::string> &mediaStreamStructureId() const { return m_mediaStreamStructureIds; };

    AdaptationSet *getAdaptationSet() { return m_adaptationSet; };
    const AdaptationSet *getAdaptationSet() const { return m_adaptationSet; };

protected:
    friend class AdaptationSet;
    Representation(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
    void setAdaptationSet(AdaptationSet *);

private:
    AdaptationSet                 *m_adaptationSet;

    // Representation attributes (ISO 23009-1:2022 Table 9)
    std::string                    m_id;
    unsigned int                   m_bandwidth;
    std::optional<unsigned int>    m_qualityRanking; 
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

