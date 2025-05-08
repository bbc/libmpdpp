#ifndef _BBC_PARSE_DASH_MPD_SAP_HH_
#define _BBC_PARSE_DASH_MPD_SAP_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: SAP class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <optional>
#include <string>
#include <sstream>

#include "macros.hh"

namespace xmlpp {
    class Element;
    class Node;
}

LIBMPDPP_NAMESPACE_BEGIN

class LIBMPDPP_PUBLIC_API SAP {
public:
    using value_type = unsigned int;

    SAP();
    SAP(const std::string &sap_str);
    SAP(value_type value);
    SAP(const SAP&);
    SAP(SAP&&);

    virtual ~SAP() {};

    SAP &operator=(const SAP&);
    SAP &operator=(SAP&&);

    bool operator==(const SAP &other) const;

    operator std::string() const;

    value_type value() const { return m_value; }

    SAP &value(value_type val);

protected:
    friend class AdaptationSet;
    SAP(xmlpp::Node &node);
    void setXMLElement(xmlpp::Element &elem) const;

private:
    void convertString(const std::string &sap_str);

    value_type m_value;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SAP_HH_*/
