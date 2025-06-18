#ifndef _BBC_PARSE_DASH_MPD_PATCH_LOCATION_HH_
#define _BBC_PARSE_DASH_MPD_PATCH_LOCATION_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: PatchLocation class
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

/** PatchLocation class
 * @headerfile libmpd++/PatchLocation.hh <libmpd++/PatchLocation.hh>
 *
 * Container for %DASH %MPD schema %PatchLocationType as found in ISO 23009-1:2022 Clause 5.15.2.
 *
 * @todo Add the attributes and child elements for %PatchLocationType in the schema.
 */
class LIBMPDPP_PUBLIC_API PatchLocation : public URI {
public:
    PatchLocation() :URI() {};

    virtual ~PatchLocation() {};

    bool operator==(const PatchLocation &other) const { return URI::operator==(other); };

///@cond PROTECTED
protected:
    friend class MPD;
    PatchLocation(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // TODO: Add the attributes and child elements for %PatchLocationType in the schema.
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_PATCH_LOCATION_HH_*/
