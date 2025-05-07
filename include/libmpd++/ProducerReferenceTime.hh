#ifndef _BBC_PARSE_DASH_MPD_PRODUCER_REFERENCE_TIME_HH_
#define _BBC_PARSE_DASH_MPD_PRODUCER_REFERENCE_TIME_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: ProducerReferenceTime class
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

class LIBPARSEMPD_PUBLIC_API ProducerReferenceTime {
public:
    ProducerReferenceTime();
    ProducerReferenceTime(const ProducerReferenceTime &to_copy);
    ProducerReferenceTime(ProducerReferenceTime &&to_move);

    virtual ~ProducerReferenceTime() {};

    ProducerReferenceTime &operator=(const ProducerReferenceTime &to_copy);
    ProducerReferenceTime &operator=(ProducerReferenceTime &&to_move);

    bool operator==(const ProducerReferenceTime &to_compare) const;

protected:
    friend class RepresentationBase;
    ProducerReferenceTime(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    // ProducerReferenceTime attributes (ISO 23009-1:2022 Clause X.X.X.X)

    // ProducerReferenceTime child elements (ISO 23009-1:2022 Clause X.X.X.X)
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_PRODUCER_REFERENCE_TIME_HH_*/

