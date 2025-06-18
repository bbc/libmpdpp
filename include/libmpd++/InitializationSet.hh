#ifndef _BBC_PARSE_DASH_MPD_INITIALIZATION_SET_HH_
#define _BBC_PARSE_DASH_MPD_INITIALIZATION_SET_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: InitializationSet class
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
#include "RepresentationBase.hh"

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

/** InitializationSet class
 * @headerfile libmpd++/InitializationSet.hh <libmpd++/InitializationSet.hh>
 *
 * This is the container representing the %InitializationSetType type from the %DASH %MPD %XML schema from ISO 23009-1:2022
 * Clause 5.3.12.3.
 *
 * @todo Add the attributes and child elements storage for the %InitializationSetType %XML schema type.
 */
class LIBMPDPP_PUBLIC_API InitializationSet : public RepresentationBase {
public:
    InitializationSet() :RepresentationBase() {};

    virtual ~InitializationSet() {};

    bool operator==(const InitializationSet &other) const { return RepresentationBase::operator==(other); };

///@cond PROTECTED
protected:
    friend class MPD;
    InitializationSet(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // TODO: add the attributes and child element member variables
    // ISO 23009-1:2022 Clause 5.3.12.3
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_INITIALIZATION_SET_HH_*/
