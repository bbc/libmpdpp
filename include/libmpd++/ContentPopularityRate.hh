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

        // @popularityRate

        /** Check if @@popularityRate attribute is set
         *
         * @return `true` if @@popularityRate attribute has been set.
         */
        bool hasPopularityRate() const { return m_popularityRate.has_value(); };

        /** Get optional @@popularityRate attribute value
         *
         * @return The optional @@popularityRate attribute value.
         */
        const std::optional<unsigned int> &popularityRate() const { return m_popularityRate; };

        /** Unset the @@popularityRate attribute
         *
         * @return This ContentPopularityRate::PR.
         */
        PR &popularityRate(const std::nullopt_t&) { m_popularityRate.reset(); return *this; };

        /**@{*/
        /** Set the @@popularityRate attribute value
         *
         * @param val The value to set the @@popularityRate attribute to.
         * @return This ContentPopularityRate::PR.
         */
        PR &popularityRate(unsigned int val) { m_popularityRate = val; return *this; };
        PR &popularityRate(const std::optional<unsigned int> &val) { m_popularityRate = val; return *this; };
        PR &popularityRate(std::optional<unsigned int> &&val) { m_popularityRate = std::move(val); return *this; };
        /**@}*/

        // @start

        /** Check if @@start attribute is set
         *
         * @return `true` if @@start attribute has been set.
         */
        bool hasStart() const { return m_start.has_value(); };

        /** Get optional @@start attribute value
         *
         * @return The optional @@start attribute value.
         */
        const std::optional<unsigned long> &start() const { return m_start; };

        /** Unset the @@start attribute
         *
         * @return This ContentPopularityRate::PR.
         */
        PR &start(const std::nullopt_t&) { m_start.reset(); return *this; };

        /**@{*/
        /** Set the @@start attribute value
         *
         * @param val The value to set the @@start attribute to.
         * @return This ContentPopularityRate::PR.
         */
        PR &start(unsigned long val) { m_start = val; return *this; };
        PR &start(const std::optional<unsigned long> &val) { m_start = val; return *this; };
        PR &start(std::optional<unsigned long> &&val) { m_start = std::move(val); return *this; };
        /**@}*/

        // @r

        /** Get the @@r attribute value
         *
         * @return The @@r attribute value.
         */
        int r() const { return m_r; };

        /** Set the @@r attribute value
         *
         * The default for this value is 0, therefore setting the @r attribute to 0 will removing it from the MPD XML output.
         *
         * @param val The value to set the @r value to.
         * @return This PR.
         */
        PR &r(int val) { m_r = val; return *this; };

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

    // PR children

    /** Get the list of PR child elements
     *
     * @return The list of PR elements.
     */
    const std::list<PR> &prs() const { return m_prs; };

    /**@{*/
    /** Get a forward iterator for the start of the PR elements list
     *
     * @return An iterator for the start of the PR elements list
     */
    std::list<PR>::const_iterator cbegin() const { return m_prs.cbegin(); };
    std::list<PR>::const_iterator begin() const { return m_prs.cbegin(); };
    std::list<PR>::iterator begin() { return m_prs.begin(); };
    std::list<PR>::const_iterator prsBegin() const { return m_prs.cbegin(); };
    std::list<PR>::iterator prsBegin() { return m_prs.begin(); };
    /**@}*/

    /**@{*/
    /** Get a forward iterator for the end of the PR elements list
     *
     * @return An iterator for the end of the PR elements list
     */
    std::list<PR>::const_iterator cend() const { return m_prs.cend(); };
    std::list<PR>::const_iterator end() const { return m_prs.cend(); };
    std::list<PR>::iterator end() { return m_prs.end(); };
    std::list<PR>::const_iterator prsEnd() const { return m_prs.cend(); };
    std::list<PR>::iterator prsEnd() { return m_prs.end(); };
    /**@}*/

    /**@{*/
    /** Set the PR elements list
     *
     * Replace the %PRs list with @p prs_list.
     *
     * @param prs_list The list to set as the list of PR elements.
     * @return This ContentPopularityRate.
     */
    ContentPopularityRate &prs(const std::list<PR> &prs_list) { m_prs = prs_list; return *this; };
    ContentPopularityRate &prs(std::list<PR> &&prs_list) { m_prs = std::move(prs_list); return *this; };
    /**@}*/

    /**@{*/
    /** Add a PR to the list of PRs
     *
     * @param pr The PR to add to the end of the list.
     * @return This ContentPopularityRate.
     */
    ContentPopularityRate &prsAdd(const PR &pr) { m_prs.push_back(pr); return *this; };
    ContentPopularityRate &prsAdd(PR &&pr) { m_prs.push_back(std::move(pr)); return *this; };
    /**@}*/

    /** Remove an entry from the PR list by value
     *
     * @param pr The PR value to remove from the list of PR elements.
     * @return This ContentPopularityRate.
     */
    ContentPopularityRate &prsRemove(const PR &pr);

    /**@{*/
    /** Remove an entry from the PR list by iterator
     *
     * @param it An iterator pointing to the entry from the list of PR elements to remove.
     * @return This ContentPopularityRate.
     */
    ContentPopularityRate &prsRemove(const std::list<PR>::iterator &it);
    ContentPopularityRate &prsRemove(const std::list<PR>::const_iterator &it);
    /**@}*/

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

