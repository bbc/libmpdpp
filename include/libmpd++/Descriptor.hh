#ifndef _BBC_PARSE_DASH_MPD_DESCRIPTOR_HH_
#define _BBC_PARSE_DASH_MPD_DESCRIPTOR_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Descriptor class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <iostream>
#include <optional>
#include <string>

#include "macros.hh"
#include "URI.hh"

namespace xmlpp {
    class Element;
    class Node;
}

LIBPARSEMPD_NAMESPACE_BEGIN

class LIBPARSEMPD_PUBLIC_API Descriptor {
public:
    Descriptor() = delete;
    Descriptor(const URI &scheme_id, const std::optional<std::string> &value = std::nullopt, const std::optional<std::string> &id = std::nullopt)
        :m_schemeIdUri(scheme_id)
        ,m_value(value)
    {};
    Descriptor(URI &&scheme_id, const std::optional<std::string> &value = std::nullopt, const std::optional<std::string> &id = std::nullopt)
        :m_schemeIdUri(scheme_id)
        ,m_value(value)
    {};
    Descriptor(const Descriptor &other)
        :m_schemeIdUri(other.m_schemeIdUri)
        ,m_value(other.m_value)
        ,m_id(other.m_id)
    {};
    Descriptor(Descriptor &&other)
        :m_schemeIdUri(std::move(other.m_schemeIdUri))
        ,m_value(std::move(other.m_value))
        ,m_id(std::move(other.m_id))
    {};

    virtual ~Descriptor() {};

    Descriptor &operator=(const Descriptor &other) {
        m_schemeIdUri = other.m_schemeIdUri;
        m_value = other.m_value;
        m_id = other.m_id;
        return *this;
    };

    Descriptor &operator=(Descriptor &&other) {
        m_schemeIdUri = std::move(other.m_schemeIdUri);
        m_value = std::move(other.m_value);
        m_id = std::move(other.m_id);
        return *this;
    };

    const URI &schemeId() const { return m_schemeIdUri; };
    URI &schemeId() { return m_schemeIdUri; };
    Descriptor &schemeId(const URI &scheme_id) { m_schemeIdUri = scheme_id; return *this; };
    Descriptor &schemeId(URI &&scheme_id) { m_schemeIdUri = std::move(scheme_id); return *this; };

    bool has_value() const { return m_value.has_value(); };
    const std::optional<std::string> &value() const { return m_value; };
    std::optional<std::string> &value() { return m_value; };
    Descriptor &value(const std::nullopt_t&) { m_value.reset(); return *this; };
    Descriptor &value(const std::string &val) { m_value = val; return *this; };
    Descriptor &value(std::string &&val) { m_value = std::move(val); return *this; };

    bool has_id() const { return m_id.has_value(); };
    const std::optional<std::string> &id() const { return m_id; };
    std::optional<std::string> &id() { return m_id; };
    Descriptor &id(const std::nullopt_t&) { m_id.reset(); return *this; };
    Descriptor &id(const std::string &id) { m_id = id; return *this; };
    Descriptor &id(std::string &&id) { m_id = std::move(id); return *this; };

protected:
    friend class MPD;
    Descriptor(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    // Attributes
    URI m_schemeIdUri;
    std::optional<std::string> m_value;
    std::optional<std::string> m_id;
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_DESCRIPTOR_HH_*/
