#ifndef _BBC_PARSE_DASH_MPD_PRESELECTION_HH_
#define _BBC_PARSE_DASH_MPD_PRESELECTION_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Preselection class
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

class Period;

/** Preselection class
 * @headerfile libmpd++/Preselection.hh <libmpd++/Preselection.hh>
 *
 * Container for %DASH %MPD schema %PreselectionType as found in ISO 23009-1:2022 Clause 5.3.11.4.
 *
 * @todo Add the attributes and child elements for %PreselectionType in the schema.
 */
class LIBMPDPP_PUBLIC_API Preselection : public RepresentationBase {
public:
    Preselection() :RepresentationBase() {};

    virtual ~Preselection() {};

    bool operator==(const Preselection &other) const { return RepresentationBase::operator==(other); };

///@cond PROTECTED
protected:
    friend class Period;
    Preselection(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // TODO: Add the attributes and child elements for %PreselectionType in the schema.
    // ISO 23009-1:2022 Clause 5.3.11.4
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_PRESELECTION_HH_*/
