#ifndef _BBC_PARSE_DASH_MPD_FAILOVER_CONTENT_HH_
#define _BBC_PARSE_DASH_MPD_FAILOVER_CONTENT_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: FailoverContent class
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

class SegmentBase;

class LIBMPDPP_PUBLIC_API FailoverContent {
public:
    FailoverContent() {};

    virtual ~FailoverContent() {};

    bool operator==(const FailoverContent &) const { return true; };

protected:
    friend class SegmentBase;
    FailoverContent(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_FAILOVER_CONTENT_HH_*/
