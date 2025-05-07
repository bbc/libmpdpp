/*****************************************************************************
 * DASH MPD parsing library in C++: RFC6838ContentType class
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

#include "libmpd++/RFC6838ContentType.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

RFC6838ContentType::RFC6838ContentType(const std::string &value) {
    convertString(value);
}

RFC6838ContentType::~RFC6838ContentType() {
}

RFC6838ContentType &RFC6838ContentType::value(const std::string &val) {
    convertString(val);
    return *this;
}

RFC6838ContentType::RFC6838ContentType(xmlpp::Node &node) {
    std::string value_str = node.eval_to_string(".//text()");
    convertString(value_str);
}

void RFC6838ContentType::setXMLElement(xmlpp::Element &elem) const {
    elem.add_child_text(static_cast<std::string>(*this));
}

void RFC6838ContentType::convertString(const std::string &val) {
    if (val == "text" || val == "image" || val == "audio" ||
        val == "video" || val == "application" || val == "font") {
        m_value = val;
    } else {
        throw ParseError("Invalid RFC6838 content type: " + val);
    }
}

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
