#ifndef _BBC_PARSE_DASH_MPD_CONTENT_PROTECTION_HH_
#define _BBC_PARSE_DASH_MPD_CONTENT_PROTECTION_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: ContentProtection class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <iostream>
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

class LIBMPDPP_PUBLIC_API ContentProtection {
public:

      /** Default constructor
     *
     * Creates an empty ContentProtection.
     */
    ContentProtection() {};

    /** Equality operator
     *
     * @brief Compares this ContentProtection with another for equality.
     * This operator overload allows checking if two ContentProtection instances are equal.
     * Currently, the implementation always returns true, meaning all instances are considered equal,
     * regardless of their internal state.
     * @param other A constant reference to the ContentProtection instance to compare against.
     * @return `true` if the ContentProtection are considered equal, false otherwise.
     */
    bool operator==(const ContentProtection &other) const { return true; };

///@cond PROTECTED
protected:
    friend class MPD;
    friend class Period;
    friend class RepresentationBase;

     /**
     * XML constructor (internal use only)
     *
     * Create a new ContentProtection from an XML %ContentProtection element.
     *
     * @param node The libxml++ Node for the %ContentProtection element.
     */
    ContentProtection(xmlpp::Node &node);

    /**
     * Set a libxml++ Element attributes and children for XML output
     *
     * This will set all relevant attributes and child elements from the settings of this ContentProtection.
     *
     * @param element The libxml++ Element to populate.
     */
    void setXMLElement(xmlpp::Element &element) const;
///@endcond PROTECTED
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_CONTENT_PROTECTION_HH_*/
