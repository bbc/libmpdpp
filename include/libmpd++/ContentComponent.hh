#ifndef _BBC_PARSE_DASH_MPD_CONTENT_COMPONENT_HH_
#define _BBC_PARSE_DASH_MPD_CONTENT_COMPONENT_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: ContentComponent class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
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

class AdaptationSet;

/**
 * @brief ContentComponent class
 * @headerfile libmpd++/ContentComponent.hh <libmpd++/ContentComponent.hh>
 * Note: This class is not complete.
 * This is a container to hold the properties of a media content component described by ContentComponent element as defined in ISO 23009-1:2022.
 *
 */
class LIBMPDPP_PUBLIC_API ContentComponent {
public:
    /** Default constructor
     *
     * Creates an empty ContentComponent.
     */
    ContentComponent() {};
    
    /** Destructor
     */
    virtual ~ContentComponent() {};

    /** Equality operator
     *
     * @brief Compares this ContentComponent with another for equality.
     * This operator overload allows checking if two ContentComponent instances are equal.
     * Currently, the implementation always returns true, meaning all instances are considered equal,
     * regardless of their internal state.
     * @param to_compare A constant reference to the ContentComponent instance to compare against.
     * @return `true` if the components are considered equal, false otherwise..
     */
    bool operator==(const ContentComponent &to_compare) const { return true; };

///@cond PROTECTED
protected:
    friend class AdaptationSet;

    /**
     * XML constructor (internal use only)
     *
     * Create a new ContentComponent from an XML %ContentComponent element.
     *
     * @param node The libxml++ Node for the %ContentComponent element contained in Adaptation Set.
     */
    ContentComponent(xmlpp::Node&);

    /**
     * Set a libxml++ Element attributes and children for XML output
     *
     * This will set all relevant attributes and child elements from the settings of this ContentComponent.
     *
     * @param element The libxml++ Element to populate.
     */
    void setXMLElement(xmlpp::Element&) const;

///@endcond PROTECTED

private:
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_CONTENT_COMPONENT_HH_*/
