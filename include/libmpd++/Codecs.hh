#ifndef _BBC_PARSE_DASH_MPD_CODECS_HH_
#define _BBC_PARSE_DASH_MPD_CODECS_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Codecs class
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

class LIBPARSEMPD_PUBLIC_API Codecs {
public:
    Codecs();
    Codecs(const std::string&);
    Codecs(const Codecs &to_copy);
    Codecs(Codecs &&to_move);

    virtual ~Codecs() {};

    Codecs &operator=(const Codecs &to_copy);
    Codecs &operator=(Codecs &&to_move);

    bool operator==(const Codecs &to_compare) const;

    operator std::string() const;

protected:
    friend class RepresentationBase;
    Codecs(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    // Codecs attributes (ISO 23009-1:2022 Clause X.X.X.X)

    // Codecs child elements (ISO 23009-1:2022 Clause X.X.X.X)
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_CODECS_HH_*/

