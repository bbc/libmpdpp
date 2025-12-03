/*****************************************************************************
 * DASH MPD parsing library in C++: ProgramInformation class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <iostream>
#include <string>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"

#include "constants.hh"

#include "libmpd++/ProgramInformation.hh"

LIBMPDPP_NAMESPACE_BEGIN

ProgramInformation::ProgramInformation()
    :m_lang()
    ,m_moreInformationURL()
    ,m_title()
    ,m_source()
    ,m_copyright()
{
}

ProgramInformation::ProgramInformation(const ProgramInformation &to_copy)
    :m_lang(to_copy.m_lang)
    ,m_moreInformationURL(to_copy.m_moreInformationURL)
    ,m_title(to_copy.m_title)
    ,m_source(to_copy.m_source)
    ,m_copyright(to_copy.m_copyright)
{
}

ProgramInformation::ProgramInformation(ProgramInformation &&to_move)
    :m_lang(std::move(to_move.m_lang))
    ,m_moreInformationURL(std::move(to_move.m_moreInformationURL))
    ,m_title(std::move(to_move.m_title))
    ,m_source(std::move(to_move.m_source))
    ,m_copyright(std::move(to_move.m_copyright))
{
}

ProgramInformation &ProgramInformation::operator=(const ProgramInformation &to_copy)
{
    m_lang = to_copy.m_lang;
    m_moreInformationURL = to_copy.m_moreInformationURL;
    m_title = to_copy.m_title;
    m_source = to_copy.m_source;
    m_copyright = to_copy.m_copyright;

    return *this;
}

ProgramInformation &ProgramInformation::operator=(ProgramInformation &&to_move)
{
    m_lang = std::move(to_move.m_lang);
    m_moreInformationURL = std::move(to_move.m_moreInformationURL);
    m_title = std::move(to_move.m_title);
    m_source = std::move(to_move.m_source);
    m_copyright = std::move(to_move.m_copyright);

    return *this;
}

bool ProgramInformation::operator==(const ProgramInformation &other) const
{
    return m_lang == other.m_lang && m_moreInformationURL == other.m_moreInformationURL && m_title == other.m_title &&
           m_source == other.m_source && m_copyright == other.m_copyright;
}

// proctected:

ProgramInformation::ProgramInformation(xmlpp::Node &node)
    :m_lang()
    ,m_moreInformationURL()
    ,m_title()
    ,m_source()
    ,m_copyright()
{
    static const xmlpp::Node::PrefixNsMap ns_map = {
        {"mpd", MPD_NS}
    };
    xmlpp::Node::NodeSet node_set;

    node_set = node.find("@lang");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_lang = std::string(attr->get_value());
    }

    node_set = node.find("@moreInformationURL");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_moreInformationURL = URI(std::string(attr->get_value()));
    }

    node_set = node.find("mpd:Title", ns_map);
    if (node_set.size() > 0) {
        m_title = node_set.front()->eval_to_string(".//text()");
    }

    node_set = node.find("mpd:Source", ns_map);
    if (node_set.size() > 0) {
        m_source = node_set.front()->eval_to_string(".//text()");
    }

    node_set = node.find("mpd:Copyright", ns_map);
    if (node_set.size() > 0) {
        m_copyright = node_set.front()->eval_to_string(".//text()");
    }
}

void ProgramInformation::setXMLElement(xmlpp::Element &elem) const
{
    if (m_lang) {
        elem.set_attribute("lang", m_lang.value().c_str());
    }

    if (m_moreInformationURL) {
        elem.set_attribute("moreInformationURL", m_moreInformationURL.value().str());
    }

    if (m_title) {
        xmlpp::Element *child = elem.add_child_element("Title");
        child->add_child_text(m_title.value());
    }

    if (m_source) {
        xmlpp::Element *child = elem.add_child_element("Source");
        child->add_child_text(m_source.value());
    }

    if (m_copyright) {
        xmlpp::Element *child = elem.add_child_element("Copyright");
        child->add_child_text(m_copyright.value());
    }
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
