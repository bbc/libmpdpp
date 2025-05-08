#ifndef _BBC_PARSE_DASH_MPD_PROGRAM_INFORMATION_HH_
#define _BBC_PARSE_DASH_MPD_PROGRAM_INFORMATION_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: ProgramInformation class
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

namespace xmlpp {
    class Element;
    class Node;
}

LIBMPDPP_NAMESPACE_BEGIN

class LIBMPDPP_PUBLIC_API ProgramInformation {
public:
    ProgramInformation() {};
    bool operator==(const ProgramInformation &other) const { return true; };
protected:
    friend class MPD;
    ProgramInformation(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_PROGRAM_INFORMATION_HH_*/
