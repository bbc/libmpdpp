#ifndef _BBC_PARSE_DASH_MPD_RESYNC_HH_
#define _BBC_PARSE_DASH_MPD_RESYNC_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Resync class
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

/** Resync class
 *
 * Container for %DASH %MPD schema %ResyncType.
 *
 * @todo Add the attributes and child elements for %ResyncType in the schema.
 */
class LIBMPDPP_PUBLIC_API Resync {
public:
    Resync();
    Resync(const Resync &to_copy);
    Resync(Resync &&to_move);

    virtual ~Resync() {};

    Resync &operator=(const Resync &to_copy);
    Resync &operator=(Resync &&to_move);

    bool operator==(const Resync &to_compare) const;

///@cond PROTECTED
protected:
    friend class RepresentationBase;
    Resync(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // TOOD: Add the attributes and child elements for %ResyncType in the schema.
    // Resync attributes (ISO 23009-1:2022 Clause X.X.X.X)

    // Resync child elements (ISO 23009-1:2022 Clause X.X.X.X)
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_RESYNC_HH_*/

