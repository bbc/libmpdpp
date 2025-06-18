#ifndef _BBC_PARSE_DASH_MPD_SUBSET_HH_
#define _BBC_PARSE_DASH_MPD_SUBSET_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Subset class
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

/** Subset class
 * @headerfile libmpd++/Subset.hh <libmpd++/Subset.hh>
 *
 * Container for %DASH %MPD schema %SubsetType as found in ISO 23009-1:2022 Clause 5.3.8.3.
 *
 * @todo Add the attributes and child elements for %SubsetType in the schema.
 */
class LIBMPDPP_PUBLIC_API Subset {
public:
    Subset() {};

    virtual ~Subset() {};

    bool operator==(const Subset&) const { return true; };

///@cond PROTECTED
protected:
    friend class Period;
    Subset(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // TODO: Add the attributes and child elements for SubsetType in the schema.
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SUBSET_HH_*/
