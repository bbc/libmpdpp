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
#include <string>

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

/**
 * @brief ContentPopularityRate class
 * @headerfile libmpd++/ContentPopularityRate.hh <libmpd++/ContentPopularityRate.hh>
 *
 * This is the container for ContentPopularityRate that indicated a level of popularity of the containing entity
 * (i.e., the Adaptation Set, Representation orPreselection) within the Media Presentation
 *
 */
class LIBMPDPP_PUBLIC_API ContentPopularityRate {
public:

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
    // ContentPopularityRate attributes (ISO 23009-1:2022 Clause X.X.X.X)

    // ContentPopularityRate child elements (ISO 23009-1:2022 Clause X.X.X.X)
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_CONTENT_POPULARITY_RATE_HH_*/

