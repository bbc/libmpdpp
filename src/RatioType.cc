/*****************************************************************************
 * DASH MPD parsing library in C++: RatioType class
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

#include "libmpd++/RatioType.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

RatioType::RatioType(const std::string &ratio_str)
    : m_numerator(0)
    , m_denominator(0)
{
    convertString(ratio_str);
}

bool RatioType::operator==(const RatioType &other) const {
    return (m_numerator == other.m_numerator) &&
           (m_denominator == other.m_denominator);
}

RatioType::operator std::string() const {
    std::ostringstream oss;
    oss << m_numerator << ":" << m_denominator;
    return oss.str();
}

RatioType::RatioType(xmlpp::Node &node)
    : m_numerator(0)
    , m_denominator(0)
{
    std::string ratio = node.eval_to_string(".//text()");
    convertString(ratio);
}

void RatioType::setXMLElement(xmlpp::Element &elem) const {
    elem.add_child_text(std::string(*this));
}

void RatioType::convertString(const std::string &ratio_str) {
    auto pos = ratio_str.find_first_of(':');
    if (pos == std::string::npos)
        throw ParseError("Bad Ratio string: missing colon");

    std::string numerator = ratio_str.substr(0, pos);
    std::string denominator = ratio_str.substr(pos + 1);

    if (numerator.empty() || denominator.empty())
        throw ParseError("Bad Ratio string: numerator or denominator empty");

    m_numerator = std::stoul(numerator);
    m_denominator = std::stoul(denominator);
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
