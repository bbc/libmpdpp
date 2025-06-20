#ifndef _BBC_PARSE_DASH_MPD_SWITCHING_HH_
#define _BBC_PARSE_DASH_MPD_SWITCHING_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Switching class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
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

/** Switching class
 * @headerfile libmpd++/Switching.hh <libmpd++/Switching.hh>
 *
 * Container for %DASH %MPD schema %SwitchingType as found in ISO 23009-1:2022 Clause 5.3.3.4.
 *
 * @todo Add the attributes and child elements for %SwitchingType in the schema.
 */
class LIBMPDPP_PUBLIC_API Switching {
public:
    Switching();
    Switching(const Switching &to_copy);
    Switching(Switching &&to_move);

    virtual ~Switching() {};

    Switching &operator=(const Switching &to_copy);
    Switching &operator=(Switching &&to_move);

    bool operator==(const Switching &to_compare) const;

///@cond PROTECTED
protected:
    friend class RepresentationBase;
    Switching(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // TODO: Add the attributes and child elements for %SwitchingType in the schema.
    // Switching attributes (ISO 23009-1:2022 Clause X.X.X.X)

    // Switching child elements (ISO 23009-1:2022 Clause X.X.X.X)
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SWITCHING_HH_*/

