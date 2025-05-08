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

namespace xmlpp {
    class Element;
    class Node;
}

LIBMPDPP_NAMESPACE_BEGIN

class LIBMPDPP_PUBLIC_API Switching {
public:
    Switching();
    Switching(const Switching &to_copy);
    Switching(Switching &&to_move);

    virtual ~Switching() {};

    Switching &operator=(const Switching &to_copy);
    Switching &operator=(Switching &&to_move);

    bool operator==(const Switching &to_compare) const;

protected:
    friend class RepresentationBase;
    Switching(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    // Switching attributes (ISO 23009-1:2022 Clause X.X.X.X)

    // Switching child elements (ISO 23009-1:2022 Clause X.X.X.X)
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SWITCHING_HH_*/

