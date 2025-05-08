#ifndef _BBC_PARSE_DASH_MPD_RANDOM_ACCESS_HH_
#define _BBC_PARSE_DASH_MPD_RANDOM_ACCESS_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: RandomAccess class
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

namespace xmlpp {
    class Element;
    class Node;
}

LIBMPDPP_NAMESPACE_BEGIN

class LIBMPDPP_PUBLIC_API RandomAccess {
public:
    RandomAccess();
    RandomAccess(const RandomAccess &to_copy);
    RandomAccess(RandomAccess &&to_move);

    virtual ~RandomAccess() {};

    RandomAccess &operator=(const RandomAccess &to_copy);
    RandomAccess &operator=(RandomAccess &&to_move);

    bool operator==(const RandomAccess &to_compare) const;

protected:
    friend class RepresentationBase;
    RandomAccess(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    // RandomAccess attributes (ISO 23009-1:2022 Clause X.X.X.X)

    // RandomAccess child elements (ISO 23009-1:2022 Clause X.X.X.X)
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_RANDOM_ACCESS_HH_*/

