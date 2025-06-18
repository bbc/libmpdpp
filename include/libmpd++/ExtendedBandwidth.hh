#ifndef _BBC_PARSE_DASH_MPD_EXTENDED_BANDWIDTH_HH_
#define _BBC_PARSE_DASH_MPD_EXTENDED_BANDWIDTH_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: ExtendedBandwidth class
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

class Representation;

/** ExtendedBandwidth class
 * @headerfile libmpd++/ExtendedBandwidth.hh <libmpd++/ExtendedBandwidth.hh>
 *
 * This is a container for %DASH %MPD %ExtendedBandwidth elements and follows the type as given by the %XML schema in
 * ISO 23009-1:2022 Clause 5.3.5.6.
 *
 * @todo This class is incomplete and needs storage for any attributes and child elements adding.
 */
class LIBMPDPP_PUBLIC_API ExtendedBandwidth {
public:
    /** Default constructor
     * 
     * Create an empty ExtendedBandwidth element.
     */
    ExtendedBandwidth() {};
    
    /** Destructor
     */
    virtual ~ExtendedBandwidth() {};

    /** Comparison operator
     *
     * @param other The other ExtendedBandwidth to compare to this one.
     * @return `true` if the value of @p other is the same as the value of this ExtendedBandwidth, otherwise `false`.
     */
    bool operator==(const ExtendedBandwidth &other) const { return true; };

///@cond PROTECTED
protected:
    friend class Representation;

    /** Constructor from libxml++ Node
     *
     * Extract a new ExtendedBandwidth from the %ExtendedBandwidth element node passed in @p node.
     *
     * @param node The libxml++ Node to read the ExtendedBandwidth element attributes and value from.
     */
    ExtendedBandwidth(xmlpp::Node &node);

    /** Set a libxml++ Node from this ExtendedBandwidth
     *
     * Set the attributes and value for a %ExtendedBandwidth element from this ExtendedBandwidth.
     *
     * @param element The Element to fill in the attributes and value for.
     */
    void setXMLElement(xmlpp::Element &element) const;
///@endcond PROTECTED

private:
    // TODO: Add storage for any attributes and child elements of the ExtendedBandwidthType from the DASH MPD XML schema.
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_EXTENDED_BANDWIDTH_HH_*/
