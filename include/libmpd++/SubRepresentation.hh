#ifndef _BBC_PARSE_DASH_MPD_SUB_REPRESENTATION_HH_
#define _BBC_PARSE_DASH_MPD_SUB_REPRESENTATION_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: SubRepresentation class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <list>
#include <optional>
#include <string>

#include "macros.hh"
#include "RepresentationBase.hh"

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

class Representation;

/** SubRepresentation class
 *
 * Container for %DASH %MPD schema %SubRepresentationType.
 *
 * @todo Add the attributes and child elements for %SubRepresentationType in the schema.
 */
class LIBMPDPP_PUBLIC_API SubRepresentation : public RepresentationBase {
public:
    SubRepresentation();
    SubRepresentation(const SubRepresentation &to_copy);
    SubRepresentation(SubRepresentation &&to_move);

    virtual ~SubRepresentation() {};

    SubRepresentation &operator=(const SubRepresentation &to_copy);
    SubRepresentation &operator=(SubRepresentation &&to_move);

    bool operator==(const SubRepresentation&) const;

    // TODO: Add accessors for attributes.

///@cond PROTECTED
protected:
    friend class Representation;
    SubRepresentation(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // SubRepresentation element attributes - ISO 23009-1:2022 Clause 5.3.6.3
    std::optional<unsigned int> m_level;
    std::list<unsigned int> m_dependencyLevel;
    std::optional<unsigned int> m_bandwidth;
    std::list<std::string> m_contentComponent;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SUB_REPRESENTATION_HH_*/
