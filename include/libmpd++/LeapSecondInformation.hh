#ifndef _BBC_PARSE_DASH_MPD_LEAP_SECOND_INFORMATION_HH_
#define _BBC_PARSE_DASH_MPD_LEAP_SECOND_INFORMATION_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: LeapSecondInformation class
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

/** LeapSecondInformation class
 * @headerfile libmpd++/LeapSecondInformation.hh <libmpd++/LeapSecondInformation.hh>
 *
 * Container for %LeapSecondInformationType elements in %DASH %MPDs (ISO 23009-1:2022 Clause 5.13.3)
 *
 * @todo Add the attributes and child elements for LeapSecondInformation.
 */
class LIBMPDPP_PUBLIC_API LeapSecondInformation {
public:
    LIBMPDPP_PUBLIC_API LeapSecondInformation() {};

///@cond PROTECTED
protected:
    friend class MPD;
    LeapSecondInformation(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // TODO: add the attributes and child elements for LeapSecondInformation
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_LEAP_SECOND_INFORMATION_HH_*/
