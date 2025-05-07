/*****************************************************************************
 * DASH MPD parsing library in C++: Ratio class
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

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/exceptions.hh"

#include "libmpd++/Ratio.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

Ratio::Ratio(const std::string &ratio_str)
    : m_numerator(0)
    , m_denominator(0)
{
    convertString(ratio_str);
}

bool Ratio::operator==(const Ratio &other) const {
    return (m_numerator == other.m_numerator) &&
           (m_denominator == other.m_denominator);
}

Ratio::operator std::string() const {
    std::ostringstream oss;
    oss << m_numerator << ":" << m_denominator;
    return oss.str();
}

Ratio::Ratio(xmlpp::Node &node)
    : m_numerator(0)
    , m_denominator(0)
{
    std::string ratio = node.eval_to_string(".//text()");
    convertString(ratio);
}

void Ratio::setXMLElement(xmlpp::Element &elem) const {
    elem.add_child_text(std::string(*this));
}

void Ratio::convertString(const std::string &ratio_str) {
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
