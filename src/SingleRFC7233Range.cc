/*****************************************************************************
 * DASH MPD parsing library in C++: SingleRFC7233Range class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
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

#include "libmpd++/SingleRFC7233Range.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

SingleRFC7233Range::SingleRFC7233Range(const std::string &range_str)
    :m_fromByte(0)
    ,m_toByte()
{
    convertString(range_str);
}

bool SingleRFC7233Range::operator==(const SingleRFC7233Range &other) const
{
    if (m_fromByte != other.m_fromByte) return false;

    if (m_toByte.has_value() != other.m_toByte.has_value()) return false;
    if (m_toByte.has_value() && !(m_toByte.value() != other.m_toByte.value())) return false;

    return true;
}

SingleRFC7233Range::operator std::string() const
{
    std::ostringstream oss;

    oss << m_fromByte << "-";
    if (m_toByte) {
        oss << m_toByte.value();
    }

    return oss.str();
}

// protected

SingleRFC7233Range::SingleRFC7233Range(xmlpp::Node &node)
    :m_fromByte(0)
    ,m_toByte()
{
    std::string range = node.eval_to_string(".//text()");
    convertString(range);
}

void SingleRFC7233Range::setXMLElement(xmlpp::Element &elem) const
{
    elem.add_child_text(std::string(*this));
}

// private

void SingleRFC7233Range::convertString(const std::string &range_str)
{
    auto pos = range_str.find_first_of('-');
    if (pos == std::string::npos) throw ParseError("Bad RFC7233 range string");
    auto from = range_str.substr(0,pos);
    auto to = range_str.substr(pos+1);
    if (from.empty()) throw ParseError("Bad RFC7233 range string");
    m_fromByte = std::stoul(from);
    if (!to.empty()) {
        m_toByte = std::stoul(to);
    }
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
