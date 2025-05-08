#ifndef _BBC_PARSE_DASH_MPD_XLINK_HH_
#define _BBC_PARSE_DASH_MPD_XLINK_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: XLink class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <optional>

#include "macros.hh"

namespace xmlpp {
    class Element;
    class Node;
}

LIBMPDPP_NAMESPACE_BEGIN

class Period;
class AdaptationSet;

class LIBMPDPP_PUBLIC_API XLink {
public:
    enum ActuateEnum {
        ACTUATE_ON_REQUEST,
        ACTUATE_ON_LOAD
    };

    enum TypeEnum {
        TYPE_SIMPLE
    };

    enum ShowEnum {
        SHOW_EMBED
    };

    XLink()
        :m_href()
        ,m_actuate(ACTUATE_ON_REQUEST)
        ,m_type(TYPE_SIMPLE)
        ,m_show(SHOW_EMBED)
    {};
    XLink(const URI &href, ActuateEnum actuate = ACTUATE_ON_REQUEST, TypeEnum typ = TYPE_SIMPLE, ShowEnum show = SHOW_EMBED)
        :m_href(href)
        ,m_actuate(actuate)
        ,m_type(typ)
        ,m_show(show)
    {};
    XLink(const XLink &other)
        :m_href(other.m_href)
        ,m_actuate(other.m_actuate)
        ,m_type(other.m_type)
        ,m_show(other.m_show)
    {};
    XLink(XLink &&other)
        :m_href(std::move(other.m_href))
        ,m_actuate(other.m_actuate)
        ,m_type(other.m_type)
        ,m_show(other.m_show)
    {};

    virtual ~XLink() {};

    XLink &operator=(const XLink &other) {
        m_href = other.m_href;
        m_actuate = other.m_actuate;
        m_type = other.m_type;
        m_show = other.m_show;
        return *this;
    }
    XLink &operator=(XLink &&other) {
        m_href = std::move(other.m_href);
        m_actuate = other.m_actuate;
        m_type = other.m_type;
        m_show = other.m_show;
        return *this;
    }

    bool operator==(const XLink &other) const;

    const URI &href() const { return m_href; };

    const ActuateEnum actuate() const { return m_actuate; };

    const TypeEnum type() const { return m_type; };

    const ShowEnum show() const { return m_show; };

protected:
    friend class Period;
    friend class AdaptationSet;
    //XLink(xmlpp::Node&);
    //void setXMLElement(xmlpp::Element&) const;

private:
    URI m_href;
    ActuateEnum m_actuate;
    TypeEnum m_type;
    ShowEnum m_show;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_XLINK_HH_*/
