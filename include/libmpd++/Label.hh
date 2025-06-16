#ifndef _BBC_PARSE_DASH_MPD_LABEL_HH_
#define _BBC_PARSE_DASH_MPD_LABEL_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Label class
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

class Period;

/** Label class
 *
 * Container for %Label elements from an %MPD.
 *
 * @todo Add the attributes and children.
 */
class LIBMPDPP_PUBLIC_API Label {
public:
    Label() {};

    virtual ~Label() {};

    bool operator==(const Label&) const { return true; };

///@cond PROTECTED
protected:
    friend class Period;
    friend class RepresentationBase;
    Label(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // TODO: Add the attributes and child elements for Label
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_LABEL_HH_*/
