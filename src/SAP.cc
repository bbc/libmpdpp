/*****************************************************************************
 * DASH MPD parsing library in C++: SAP class
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

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/exceptions.hh"

#include "libmpd++/SAP.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

SAP::SAP()
    :m_value(0)
{
}

SAP::SAP(const std::string &sap_str)
    :m_value(0)
{
    convertString(sap_str);
}

SAP::SAP(value_type value)
    :m_value(value)
{
    if (value > 6)
        throw RangeError("SAP value out of range: must be between 0 and 6");
}

SAP::SAP(const SAP &other)
    :m_value(other.m_value)
{
}

SAP::SAP(SAP &&other)
    :m_value(std::move(other.m_value))
{
}

SAP &SAP::operator=(const SAP &other)
{
    m_value = other.m_value;
    return *this;
}

SAP &SAP::operator=(SAP &&other)
{
    m_value = other.m_value;
    return *this;
}

bool SAP::operator==(const SAP &other) const
{
    return m_value == other.m_value;
}

SAP::operator std::string() const
{
    return std::to_string(m_value);
}

SAP &SAP::value(value_type val)
{
    if (val > 6)
        throw RangeError("SAP value out of range: must be between 0 and 6 inclusive");
    m_value = val;
    return *this;
}

SAP::SAP(xmlpp::Node &node)
    :m_value(0)
{
    std::string text = node.eval_to_string(".//text()");
    convertString(text);
}

void SAP::setXMLElement(xmlpp::Element &elem) const
{
    elem.add_child_text(std::string(*this));
}

void SAP::convertString(const std::string &sap_str)
{
    if (sap_str.empty()) throw ParseError("SAP string is empty");

    try {
        unsigned long val = std::stoul(sap_str);
        if (val > 6)
            throw ParseError("SAP value out of range: must be between 0 and 6 inclusive");
        m_value = static_cast<value_type>(val);
    } catch (const std::exception &e) {
        throw ParseError(std::string("SAP conversion error: ") + e.what());
    }
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
