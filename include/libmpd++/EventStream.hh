#ifndef _BBC_PARSE_DASH_MPD_EVENT_STREAM_HH_
#define _BBC_PARSE_DASH_MPD_EVENT_STREAM_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: EventStream class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
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

class Period;

/** EventStream class
 * @headerfile libmpd++/EventStream.hh <libmpd++/EventStream.hh>
 *
 * This is a container for %DASH %MPD %XML EventStream elements. Thsi class is derived from the %DASH %MPD %XML schema for the
 * %EventStreamType as found in ISO 23009-1:2022 Clause 5.10.2.3.
 *
 * @todo This class is incomplete and needs storage adding for attributes and child elements.
 */
class LIBMPDPP_PUBLIC_API EventStream {
public:

    /** Default constructor
     * 
     * Create an empty EventStream element.
     */
    EventStream() {};
    
    /** Destructor
     */
    virtual ~EventStream() {};

    /** Comparison operator
     *
     * @param other The other EventStream to comnpare to this one.
     * @return `true` if the value of @p other is the same as the value of this EventStream, otherwise `false`.
     */
    bool operator==(const EventStream &other) const { return true; };

///@cond PROTECTED
protected:
    friend class Period;
    friend class RepresentationBase;

    /** Constructor from libxml++ Node
     *
     * Extract a new EventStream from the %EventStream element node passed in @p node.
     *
     * @param node The libxml++ Node to read the EventStream element attributes and value from.
     */
    EventStream(xmlpp::Node &node);

     /** Set a libxml++ Node from this EventStream
     *
     * Set the attributes and value for a %EventStream element from this EventStream.
     *
     * @param element The Element to fill in the attributes and value for.
     */
    void setXMLElement(xmlpp::Element &element) const;
///@endcond PROTECTED

private:
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_EVENT_STREAM_HH_*/
