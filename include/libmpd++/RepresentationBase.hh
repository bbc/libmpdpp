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

