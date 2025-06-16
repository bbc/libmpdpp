#ifndef _BBC_PARSE_DASH_MPD_PRODUCER_REFERENCE_TIME_HH_
#define _BBC_PARSE_DASH_MPD_PRODUCER_REFERENCE_TIME_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: ProducerReferenceTime class
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

/** ProducerReferenceTime class
 *
 * Container for %DASH %MPD schema %ProducerReferenceTimeType.
 *
 * @todo Add the attributes and child elements for %MetricType in the schema.
 */
class LIBMPDPP_PUBLIC_API ProducerReferenceTime {
public:
    ProducerReferenceTime();
    ProducerReferenceTime(const ProducerReferenceTime &to_copy);
    ProducerReferenceTime(ProducerReferenceTime &&to_move);

    virtual ~ProducerReferenceTime() {};

    ProducerReferenceTime &operator=(const ProducerReferenceTime &to_copy);
    ProducerReferenceTime &operator=(ProducerReferenceTime &&to_move);

    bool operator==(const ProducerReferenceTime &to_compare) const;

///@cond PROTECTED
protected:
    friend class RepresentationBase;
    ProducerReferenceTime(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // TODO: Add the attributes and child elements for %MetricType in the schema.
    // ProducerReferenceTime attributes (ISO 23009-1:2022 Clause X.X.X.X)

    // ProducerReferenceTime child elements (ISO 23009-1:2022 Clause X.X.X.X)
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_PRODUCER_REFERENCE_TIME_HH_*/

