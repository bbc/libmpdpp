#ifndef _BBC_PARSE_DASH_MPD_SAP_HH_
#define _BBC_PARSE_DASH_MPD_SAP_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Sap class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <optional>
#include <string>
#include <sstream>

#include "macros.hh"

namespace xmlpp {
    class Element;
    class Node;
}

LIBPARSEMPD_NAMESPACE_BEGIN

class AdaptationSet;

class LIBPARSEMPD_PUBLIC_API Sap {
public:
    using value_type = unsigned int;

    Sap()
        : m_value(0)
    {}

    Sap(const std::string &sap_str);

    Sap(value_type value);

    virtual ~Sap() {};

    bool operator==(const Sap &other) const;

    operator std::string() const;

    value_type value() const { return m_value; }

    Sap &value(value_type val);

protected:
    friend AdaptationSet;
    Sap(xmlpp::Node &node);

    void setXMLElement(xmlpp::Element &elem) const;

private:
    void convertString(const std::string &sap_str);

    value_type m_value;
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SAP_HH_*/
