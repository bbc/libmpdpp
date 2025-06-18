#ifndef _BBC_PARSE_DASH_MPD_SERVICE_DESCRIPTION_HH_
#define _BBC_PARSE_DASH_MPD_SERVICE_DESCRIPTION_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: ServiceDescription class
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

/** ServiceDescription class
 * @headerfile libmpd++/ServiceDescription.hh <libmpd++/ServiceDescription.hh>
 *
 * Container for %DASH %MPD schema %ServiceDescriptionType as found in ISO 23009-1:2022 Clause K.4.3.1.
 *
 * @todo Add the attributes and child elements for %ServiceDescriptionType in the schema.
 */
class LIBMPDPP_PUBLIC_API ServiceDescription {
public:
    ServiceDescription() {};
    bool operator==(const ServiceDescription &other) const { return true; };

///@cond PROTECTED
protected:
    friend class MPD;
    friend class Period;
    ServiceDescription(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // TODO: Add the attributes and child elements for %ServiceDescriptionType in the schema.
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SERVICE_DESCRIPTION_HH_*/
