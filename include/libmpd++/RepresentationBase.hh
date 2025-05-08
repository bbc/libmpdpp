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

namespace xmlpp {
    class Element;
    class Node;
}

LIBMPDPP_NAMESPACE_BEGIN

class LIBMPDPP_PUBLIC_API RepresentationBase {
public:
    enum VideoScan {
        VIDEO_SCAN_PROGRESSIVE,
        VIDEO_SCAN_INTERLACED,
        VIDEO_SCAN_UNKNOWN
    };

    RepresentationBase();
    RepresentationBase(const RepresentationBase &to_copy);
    RepresentationBase(RepresentationBase &&to_move);

    virtual ~RepresentationBase() {};

    RepresentationBase &operator=(const RepresentationBase &to_copy);
    RepresentationBase &operator=(RepresentationBase &&to_move);

    bool operator==(const RepresentationBase &to_compare) const;

    // @profiles
    // @width
    // @height
    // @sar
    // @frameRate
    // @audioSamplingRate
    // @mimeType
    // @segmentProfiles
    // @codecs
    // @containerProfiles
    // @maximumSAPPeriod
    // @startWithSAP
    // @maxPlayoutRate
    // @codingDependency
    // @scanType
    // @selectionPriority
    // @tag

    // FramePacking children
    // AudioChannelConfiguration children
    // ContentProtection children
    // OutputProtection child
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

protected:
    RepresentationBase(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    // RepresentationBase attributes (ISO 23009-1:2022 Clause 5.3.7.3)
    std::list<URI>              m_profiles;
    std::optional<unsigned int> m_width;
    std::optional<unsigned int> m_height;
    std::optional<Ratio>        m_sar;
    std::optional<FrameRate>    m_frameRate;
    std::list<unsigned int>     m_audioSamplingRate; // if present must contain 1 or 2 entries
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
    std::list<Descriptor>            m_contentProtections;
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

