#ifndef _BBC_PARSE_DASH_MPD_SUB_REPRESENTATION_HH_
#define _BBC_PARSE_DASH_MPD_SUB_REPRESENTATION_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: SubRepresentation class
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

class LIBMPDPP_PUBLIC_API SubRepresentation {
public:
    SubRepresentation() {};

    virtual ~SubRepresentation() {};

    bool operator==(const SubRepresentation&) const { return true; };

protected:
    friend class Representation;
    SubRepresentation(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SUB_REPRESENTATION_HH_*/
