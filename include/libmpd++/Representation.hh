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
#include "SegmentAvailability.hh"
#include "SegmentBase.hh"
#include "SegmentTemplate.hh"
#include "SegmentList.hh"
#include "ServiceDescription.hh"
#include "SubRepresentation.hh"
#include "Subset.hh"
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

/** Representation class
 * @headerfile libmpd++/Representation.hh <libmpd++/Representation.hh>
 *
 * This is the container for %Representation elements from an %MPD and follows the schema description of %RepresentationType from
 * ISO 23009-1:2022 Clause 5.3.5.3.
 */
class LIBMPDPP_PUBLIC_API Representation : public RepresentationBase {
public:
    using time_type = std::chrono::system_clock::time_point; ///< The type used to represent date-time values in this class
    using duration_type = std::chrono::microseconds;         ///< The type used to represent duration values in this class

    /** Default constructor
     *
     * Create an empty Representation object
     */
    Representation();

    /** Copy constructor
     *
     * Create a new Representation as a copy of @p to_copy.
     *
     * @param to_copy The Representation object to copy into the new Representation.
     */
    Representation(const Representation &to_copy);

    /** Move constructor
     *
     * Create a new Representation using the values and resources of @p to_move.
     *
     * @param to_move The Representation object take the values and resources from to create the new Representation.
     */
    Representation(Representation &&to_move);

    /** Destructor
     */
    virtual ~Representation() {};

    /** Copy operator
     *
     * Make this Representation a copy of @p to_copy.
     *
     * @param to_copy The Representation object to copy into this Representation.
     * @return This Representation.
     */
    Representation &operator=(const Representation &to_copy);

    /** Move operator
     *
     * Make this Representation a copy of @p to_move by moving the values and resources.
     *
     * @param to_move The Representation object to move into this Representation.
     * @return This Representation.
     */
    Representation &operator=(Representation &&to_move);

    /** Equality operator
     *
     * Check if @p to_compare contains the same value as this Representation.
     *
     * @param to_compare The other Representation to compare to this Representation.
     * @return `true` if the values match, otherwise `false`.
     */
    bool operator==(const Representation &to_compare) const;

    /**@{*/
    /** Get the MPD this Representation is attached to
     *
     * Gets the MPD object this Representation is attached to. This is the equivalent of:
     * @code{.cpp}
     * getAdaptationSet() ? getAdaptationSet()->getMPD() : nullptr
     * @endcode
     *
     * @return The MPD this Representation is part of or `nullptr`
     */
    MPD *getMPD();
    const MPD *getMPD() const;
    /**@}*/

    /**@{*/
    /** Get the Period this Representation is attached to
     *
     * Gets the Period object this Representation is attached to. This is the equivalent of:
     * @code{.cpp}
     * getAdaptationSet() ? getAdaptationSet()->getPeriod() : nullptr
     * @endcode
     *
     * @return The Period this Representation is part of or `nullptr`.
     */
    Period *getPeriod();
    const Period *getPeriod() const;
    /**@}*/

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

    /**@{*/
    /** Get the AdaptationSet this Representation is attached to
     *
     * Gets the AdaptationSet object that this Representation is a child of. If the Representation has not been added to an
     * AdaptationSet then `nullptr` is returned.
     *
     * @return The AdaptationSet this Representation is part of or `nullptr`.
     */
    AdaptationSet *getAdaptationSet() { return m_adaptationSet; };
    const AdaptationSet *getAdaptationSet() const { return m_adaptationSet; };
    /**@}*/

    /** Get media URL
     *
     * Get the media URL for a given @p segment_number.
     *
     * @param segment_number The segment number to fetch the URL for.
     *
     * @return The media segment URL or an empty URL if the segment is unknown.
     */
    URI getMediaURL(unsigned long segment_number) const;

    /** Get media URL
     *
     * Get the media URL for a given @p segment_number.
     *
     * @param segment_time The segment time to fetch the URL for.
     *
     * @return The media segment URL or an empty URL if the segment is unknown.
     */
    URI getMediaURL(time_type segment_time) const;

    /** Get initialisation segment URL
     *
     * Get the initialisation segment URL.
     *
     * @return The initialisation segment URL or an empty URL if no segment information is available.
     */
    URI getInitializationURL() const;

    /** Get the list of relevant BaseURLs
     *
     * Get the list of relevant BaseURLs, resolved to absolute URLs when possible.
     *
     * @return A list of resolves BaseURLs that apply at for this Representation.
     */
    std::list<BaseURL> getBaseURLs() const;

    /** Is this Representation selected by its AdaptationSet?
     *
     * @return `true` if the Representation is selected in its AdaptationSet.
     */
    bool isSelected() const;

    /** Get the full segment availability information
     *
     * This returns the full segment availability information for the first segment on or after the @p query_time provided.
     *
     * If no segment is available then the SegmentAvailability object returned will have an empty URL.
     *
     * @param query_time The system wallclock time we are querying for.
     *
     * @return The SegmentAvailability for the next available segment or an empty SegmentAvailability if no segment is available.
     */
    SegmentAvailability segmentAvailability(const time_type &query_time) const;

    /** Get the segment availability information of the initialisation segment
     *
     * This returns the full segment availability information for the initialisation segment. If no initialization segment is
     * available then the SegmentAvailability object returned will have an empty URL.
     *
     * @return The SegmentAvailability for the initialisation segment or an empty SegmentAvailability if no initialisation segment
     *         is available.
     */
    SegmentAvailability initialisationSegmentAvailability() const;

///@cond PROTECTED
protected:
    friend class AdaptationSet;
    Representation(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
    void setAdaptationSet(AdaptationSet *);
///@endcond PROTECTED

private:
    SegmentTemplate::Variables getTemplateVars() const;
    SegmentTemplate::Variables getTemplateVars(unsigned long segment_number) const;
    SegmentTemplate::Variables getTemplateVars(const time_type &time) const;
    time_type getPeriodStartTime() const;
    std::optional<duration_type> getPeriodDuration() const;
    const MultipleSegmentBase &getMultiSegmentBase() const;

    AdaptationSet                 *m_adaptationSet;       ///< The AdaptationSet this Representation is part of or `nullptr`

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

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_REPRESENTATION_HH_*/

