#ifndef _BBC_PARSE_DASH_MPD_CONTENT_POPULARITY_RATE_HH_
#define _BBC_PARSE_DASH_MPD_CONTENT_POPULARITY_RATE_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: ContentPopularityRate class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <list>
#include <optional>

#include "macros.hh"

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

/** ContentPopularityRate class
 * @headerfile libmpd++/ContentPopularityRate.hh <libmpd++/ContentPopularityRate.hh>
 *
 * This is the container for %ContentPopularityRate elements from a %DASH %MPD. This indicates the level of popularity of the
 * containing entity (i.e. the %AdaptationSet, %Representation or %Preselection) within the media presentation.
 *
 * This follows the %DASH %MPD %XML schema definition in ISO 23009-1:2022 Clause 5.14.3.
 */
class LIBMPDPP_PUBLIC_API ContentPopularityRate {
public:

    /** ContentPopularityRate::PR class
     * @headerfile libmpd++/ContentPopularityRate.hh <libmpd++/ContentPopularityRate.hh>
     *
     * This is a container for the %PR elements of a ContentPopularityRate.
     */
    class LIBMPDPP_PUBLIC_API PR {
    public:
        PR() = delete;
        PR(const std::optional<unsigned int> popularity_rate = std::nullopt,
           const std::optional<unsigned long> &start = std::nullopt,
           int r = 0)
            :m_popularityRate(popularity_rate)
            ,m_start(start)
            ,m_r(r)
        {
            if (popularity_rate < 1 || popularity_rate > 100)
                throw std::out_of_range("popularityRate attribute of PR element must be between 1 and 100 inclusive.");
        };
        PR(const PR &other)
            :m_popularityRate(other.m_popularityRate)
            ,m_start(other.m_start)
            ,m_r(other.m_r)
        {};
        PR(PR &&other)
            :m_popularityRate(std::move(other.m_popularityRate))
            ,m_start(std::move(other.m_start))
            ,m_r(other.m_r)
        {};

        virtual ~PR() {};

        PR &operator=(const PR &other) {
            m_popularityRate = other.m_popularityRate;
            m_start = other.m_start;
            m_r = other.m_r;
            return *this;
        };
        PR &operator=(PR &&other) {
            m_popularityRate = std::move(other.m_popularityRate);
            m_start = std::move(other.m_start);
            m_r = other.m_r;
            return *this;
        };

        bool operator==(const PR &other) {
            if (m_r != other.m_r) return false;
            if (m_popularityRate != other.m_popularityRate) return false;
            if (m_start != other.m_start) return false;
            return true;
        }
        bool operator!=(const PR &other) { return !(*this == other); };

        // TODO: Add accessors for attributes

    ///@cond PROTECTED
    protected:
        friend class ContentPopularityRate;
        PR(xmlpp::Node &node);
        void setXMLElement(xmlpp::Element &elem) const;
    ///@endcond PROTECTED

    private:
        std::optional<unsigned int>  m_popularityRate;
        std::optional<unsigned long> m_start;
        int                          m_r; // default is 0
    };

    /** Default constructor
     *
     * Creates an empty ContentPopularityRate.
     */
    ContentPopularityRate();

    /**
     * Copy constructor
     *
     * Creates a new ContentPopularityRate object which is a copy of @p to_copy.
     *
     * @param to_copy The ContentPopularityRate object to copy.
     */
    ContentPopularityRate(const ContentPopularityRate &to_copy);

    /**
     * Move constructor
     *
     * Creates a new ContentPopularityRate object which transfers the resources from @p to_move.
     *
     * @param to_move The ContentPopularityRate object to move.
     */
    ContentPopularityRate(ContentPopularityRate &&to_move);

    /**
     * Destructor
     */
    virtual ~ContentPopularityRate() {};

    /**
     * Copy operator
     *
     * Copies the values from @p to_copy into this ContentPopularityRate object.
     *
     * @param to_copy The ContentPopularityRate object to copy.
     * @return This ContentPopularityRate object.
     */
    ContentPopularityRate &operator=(const ContentPopularityRate &to_copy);

    /**
     * Move operator
     *
     * Transfers the resources from @p to_move into this ContentPopularityRate object.
     *
     * @param to_move The ContentPopularityRate object to move.
     * @return This ContentPopularityRate object.
     */
    ContentPopularityRate &operator=(ContentPopularityRate &&to_move);

    /**
     * Equality operator
     *
     * Compare the value of this ContentPopularityRate to @p to_compare.
     *
     * @param to_compare The ContentPopularityRate object to compare this object to.
     * @return `true` if this ContentPopularityRate object contains the same values as @p to_compare, otherwise `false`.
     */
    bool operator==(const ContentPopularityRate &to_compare) const;

///@cond PROTECTED
protected:
    friend class RepresentationBase;

    /**
     * XML constructor (internal use only)
     *
     * Create a new ContentPopularityRate from an XML %ContentPopularityRate element.
     *
     * @param node The libxml++ Node for the % ContentPopularityRate element.
     */
    ContentPopularityRate(xmlpp::Node &node);

     /**
     * Set a libxml++ Element attributes and children for XML output
     *
     * This will set all relevant attributes and child elements from the settings of this ContentPopularityRate.
     *
     * @param element The libxml++ Element to populate.
     */
    void setXMLElement(xmlpp::Element &element) const;
///@endcond PROTECTED

private:
    // ContentPopularityRate child elements (ISO 23009-1:2022 Clause 5.14.3)
    std::list<PR> m_prs;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_CONTENT_POPULARITY_RATE_HH_*/

