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

/** ProgramInformation class
 * @headerfile libmpd++/ProgramInformation.hh <libmpd++/ProgramInformation.hh>
 *
 * Container for %DASH %MPD schema %ProgramInformationType as found in ISO 23009-1:2022 Clause 5.7.3.
 *
 * @todo Add the attributes and child elements for %ProgramInformationType in the schema.
 */
class LIBMPDPP_PUBLIC_API ProgramInformation {
public:
    ProgramInformation() {};
    bool operator==(const ProgramInformation &other) const { return true; };

///@cond PROTECTED
protected:
    friend class MPD;
    ProgramInformation(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // TODO: Add the attributes and child elements for %ProgramInformationType in the schema.
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_PROGRAM_INFORMATION_HH_*/
