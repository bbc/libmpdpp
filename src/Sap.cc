/*****************************************************************************
 * DASH MPD parsing library in C++: Sap class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): Dev Audsin <dev.audsin@bbc.co.uk>
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

#include "libmpd++/Sap.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

Sap::Sap(const std::string &sap_str)
    : m_value(0)
{
    convertString(sap_str);
}

Sap::Sap(value_type value)
    : m_value(value)
{
    if (value > 6)
        throw ParseError("Sap value out of range: must be between 0 and 6");
}

bool Sap::operator==(const Sap &other) const {
    return m_value == other.m_value;
}

Sap::operator std::string() const {
    std::ostringstream oss;
    oss << m_value;
    return oss.str();
}

Sap &Sap::value(value_type val) {
    if (val > 6)
        throw ParseError("Sap value out of range: must be between 0 and 6");
    m_value = val;
    return *this;
}

Sap::Sap(xmlpp::Node &node)
    : m_value(0)
{
    std::string text = node.eval_to_string(".//text()");
    convertString(text);
}

void Sap::setXMLElement(xmlpp::Element &elem) const {
    elem.add_child_text(std::string(*this));
}

void Sap::convertString(const std::string &sap_str) {
    if (sap_str.empty())
        throw ParseError("Sap string is empty");

    try {
        unsigned long val = std::stoul(sap_str);
        if (val > 6)
            throw ParseError("Sap value out of range: must be between 0 and 6");
        m_value = static_cast<value_type>(val);
    } catch (const std::exception &e) {
        throw ParseError(std::string("Sap conversion error: ") + e.what());
    }
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
