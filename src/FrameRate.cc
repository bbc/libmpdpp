/*****************************************************************************
 * DASH MPD parsing library in C++: FrameRate class
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

#include "libmpd++/FrameRate.hh"

LIBMPDPP_NAMESPACE_BEGIN

FrameRate::FrameRate(const std::string &frame_rate_str)
    : m_numerator(0)
    , m_denominator(1)
{
    convertString(frame_rate_str);
}

FrameRate::operator std::string() const {
    std::ostringstream oss;
    oss << m_numerator;
    if (m_denominator != 1) {
        oss << "/" << m_denominator;
    }
    return oss.str();
}

// Protected constructor: create a FrameRate from an XML node.
FrameRate::FrameRate(xmlpp::Node &node)
    : m_numerator(0)
    , m_denominator(1)
{
    std::string text = node.eval_to_string(".//text()");
    convertString(text);
}

void FrameRate::setXMLElement(xmlpp::Element &elem) const {
    elem.add_child_text(std::string(*this));
}

// Private method to convert a string representation into the numerator and denominator.
// If no '/' is found, the denominator defaults to 1.
void FrameRate::convertString(const std::string &frame_rate_str) {
    auto pos = frame_rate_str.find('/');
    if (pos == std::string::npos) {
        if (frame_rate_str.empty()) {
            m_numerator = 1;
        } else {
            m_numerator = std::stoul(frame_rate_str);
        }
        m_denominator = 1;
    } else {
        std::string numerator_str = frame_rate_str.substr(0, pos);
        std::string denominator_str = frame_rate_str.substr(pos + 1);

        if (numerator_str.empty() || denominator_str.empty())
            throw ParseError("Bad FrameRate string: missing numerator or denominator");

        m_numerator = std::stoul(numerator_str);
        m_denominator = std::stoul(denominator_str);
    }
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
