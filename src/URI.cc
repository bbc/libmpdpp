/*****************************************************************************
 * DASH MPD parsing library in C++: URI class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <iostream>
#include <regex>
#include <string>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/BaseURL.hh"

#include "DecomposedURL.hh"

#include "libmpd++/URI.hh"

LIBMPDPP_NAMESPACE_BEGIN

void URI::validate()
{
    // check m_uri is a valid URI string and throw std::domain_error if not
    static const std::regex validator_regex("^(?:[a-zA-Z][-a-zA-Z0-9+.]*:)?(?://(?:(?:[-a-zA-Z0-9._~!$&'()*+,;=:]|%[a-fA-F0-9][a-fA-F0-9])*@)?(?:\\[(?:v[a-fA-F0-9]+\\.[-a-zA-Z0-9._~!$&'()*+,;=:]+|(?:(?:(?:[a-fA-F0-9]){1,4}:){6}(?:(?:[a-fA-F0-9]){1,4}:(?:[a-fA-F0-9]){1,4}|(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])(?:\\.(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])){3})|::(?:(?:[a-fA-F0-9]){1,4}:){5}(?:(?:[a-fA-F0-9]){1,4}:(?:[a-fA-F0-9]){1,4}|(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])(?:\\.(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])){3})|(?:(?:[a-fA-F0-9]){1,4})?::(?:(?:[a-fA-F0-9]){1,4}:){4}(?:(?:[a-fA-F0-9]){1,4}:(?:[a-fA-F0-9]){1,4}|(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])(?:\\.(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])){3})|(?:(?:(?:[a-fA-F0-9]){1,4}:){0,1}(?:[a-fA-F0-9]){1,4})?::(?:(?:[a-fA-F0-9]){1,4}:){3}(?:(?:[a-fA-F0-9]){1,4}:(?:[a-fA-F0-9]){1,4}|(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])(?:\\.(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])){3})|(?:(?:(?:[a-fA-F0-9]){1,4}:){0,2}(?:[a-fA-F0-9]){1,4})?::(?:(?:[a-fA-F0-9]){1,4}:){2}(?:(?:[a-fA-F0-9]){1,4}:(?:[a-fA-F0-9]){1,4}|(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])(?:\\.(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])){3})|(?:(?:(?:[a-fA-F0-9]){1,4}:){0,3}(?:[a-fA-F0-9]){1,4})?::(?:[a-fA-F0-9]){1,4}:(?:(?:[a-fA-F0-9]){1,4}:(?:[a-fA-F0-9]){1,4}|(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])(?:\\.(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])){3})|(?:(?:(?:[a-fA-F0-9]){1,4}:){0,4}(?:[a-fA-F0-9]){1,4})?::(?:(?:[a-fA-F0-9]){1,4}:(?:[a-fA-F0-9]){1,4}|(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])(?:\\.(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])){3})|(?:(?:(?:[a-fA-F0-9]){1,4}:){0,5}(?:[a-fA-F0-9]){1,4})?::(?:[a-fA-F0-9]){1,4}|(?:(?:(?:[a-fA-F0-9]){1,4}:){0,6}(?:[a-fA-F0-9]){1,4})?::))\\]|(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])(?:\\.(?:[0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])){3}|(?:[-a-zA-Z0-9._~!$&'()*+,;=]|%[a-fA-F0-9][a-fA-F0-9])*)(?::[0-9]*)?(?:/(?:[-a-zA-Z0-9._~!$&'()*+,;=:@]|%[a-fA-F0-9][a-fA-F0-9])*)*|/(?:(?:[-a-zA-Z0-9._~!$&'()*+,;=:@]|%[a-fA-F0-9][a-fA-F0-9])+(?:/(?:[-a-zA-Z0-9._~!$&'()*+,;=:@]|%[a-fA-F0-9][a-fA-F0-9])*)*)?|(?:[-a-zA-Z0-9._~!$&'()*+,;=:@]|%[a-fA-F0-9][a-fA-F0-9])+(?:/(?:[-a-zA-Z0-9._~!$&'()*+,;=:@]|%[a-fA-F0-9][a-fA-F0-9])*)*|)(?:\\?(?:[-a-zA-Z0-9._~!$&'()*+,;=:@/?]|%[a-fA-F0-9][a-fA-F0-9])*)?(?:#(?:[-a-zA-Z0-9._~!$&'()*+,;=:@/?]|%[a-fA-F0-9][a-fA-F0-9])*)?$", std::regex_constants::ECMAScript);
    if (!std::regex_match(m_uri, validator_regex))
        throw std::domain_error("Not a valid URI");
}

URI::URI(xmlpp::Node &node)
{
    // Take all text in the element as the URI
    m_uri = node.eval_to_string(".//text()");
    validate();
}

void URI::setXMLElement(xmlpp::Element &elem) const
{
    elem.add_child_text(m_uri);
}

static const std::regex g_url_split("^(?:([^:/?#]+):)?(?://([^/?#]*))?([^?#]*)(?:\\?([^#]*))?(?:#(.*))?$");

bool URI::isURL() const
{
    return std::regex_match(m_uri, g_url_split);
}

bool URI::isAbsoluteURL() const
{
    std::smatch result;
    if (!std::regex_match(m_uri, result, g_url_split)) return false;
    return result[1].matched && result[2].matched;
}

URI URI::resolveUsingBaseURLs(const std::list<BaseURL> &base_urls) const
{
    if (!isURL()) return *this;          // not a URL so can't resolve, just return this URI
    if (isAbsoluteURL()) return *this;   // already an absolute URL, just return this URL
    if (base_urls.empty()) return *this; // nothing to resolve with, so just return this URL

    // find BaseURL to use (just use first for now)
    const auto &base_url = base_urls.front();
    std::string new_url = std::string(DecomposedURL(DecomposedURL(base_url.url()), m_uri));

    return URI(new_url);
}

LIBMPDPP_NAMESPACE_END

std::ostream &operator<<(std::ostream &os, const LIBMPDPP_NAMESPACE_CLASS(URI) &uri)
{
    os << uri.str();
    return os;
}

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
