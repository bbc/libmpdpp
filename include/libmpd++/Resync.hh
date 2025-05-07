#ifndef _BBC_PARSE_DASH_MPD_RESYNC_HH_
#define _BBC_PARSE_DASH_MPD_RESYNC_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Resync class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <string>

#include "macros.hh"

namespace xmlpp {
    class Element;
    class Node;
}

LIBPARSEMPD_NAMESPACE_BEGIN

class LIBPARSEMPD_PUBLIC_API Resync {
public:
    Resync();
    Resync(const Resync &to_copy);
    Resync(Resync &&to_move);

    virtual ~Resync() {};

    Resync &operator=(const Resync &to_copy);
    Resync &operator=(Resync &&to_move);

    bool operator==(const Resync &to_compare) const;

protected:
    friend class RepresentationBase;
    Resync(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    // Resync attributes (ISO 23009-1:2022 Clause X.X.X.X)

    // Resync child elements (ISO 23009-1:2022 Clause X.X.X.X)
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_RESYNC_HH_*/

