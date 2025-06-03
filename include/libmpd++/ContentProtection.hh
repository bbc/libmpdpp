#ifndef _BBC_PARSE_DASH_MPD_CONTENT_PROTECTION_HH_
#define _BBC_PARSE_DASH_MPD_CONTENT_PROTECTION_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: ContentProtection class
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

class LIBMPDPP_PUBLIC_API ContentProtection {
public:
    ContentProtection() {};
    bool operator==(const ContentProtection &other) const { return true; };
protected:
    friend class MPD;
    friend class Period;
    ContentProtection(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_CONTENT_PROTECTION_HH_*/
