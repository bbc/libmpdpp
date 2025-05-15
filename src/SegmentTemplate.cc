/*****************************************************************************
 * DASH MPD parsing library in C++: SegmentTemplate class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <optional>
#include <exception>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/Period.hh"

#include "libmpd++/SegmentTemplate.hh"

LIBMPDPP_NAMESPACE_BEGIN

/******** SegmentTemplate::Variables ********/

std::string SegmentTemplate::Variables::format(const std::string &fmt, const std::optional<unsigned int> &start_number) const
{
    // If string is not even big enough for formatting...
    if (fmt.size() < 2) throw std::runtime_error("bad format for a template substitution");

    // handle escape sequence
    if (fmt == "$$") return "$";

    // handle non-formatted fields
    if (fmt == "$RepresentationID$") {
        if (m_representationId) return m_representationId.value();
        throw std::runtime_error("RepresentationID substitution without a RepresentationID being set");
    }

    // If variable is malformatted, ignore
    if (fmt[0] != '$' || fmt[fmt.size()-1] != '$') throw std::runtime_error("bad format for a template substitution");

    // All other fields can contain a format specifier "%0<width>d" at the end
    int width = 1;
    auto varname = fmt.substr(1,fmt.size()-2);
    if (varname[varname.size()-1] == 'd') {
        // may have format width
        std::string::size_type pos;
        for (pos = varname.size()-2; pos > 1 && varname[pos] >= '0' && varname[pos] <= '9'; pos--);
        if (pos >= 0 && varname[pos] == '%' && varname[pos+1] == '0') {
            width = std::stoi(varname.substr(pos+2, varname.size()-pos-3));
            varname.erase(pos);
        }
    }

    if (varname == "Number") {
        if (m_number) {
            return std::format("{:0{}d}", m_number.value() + (start_number?start_number.value():1), width);
        }
        throw std::runtime_error("Number substitution without a Number being set");
    }
    if (varname == "Bandwidth") {
        if(m_bandwidth) return std::format("{:0{}d}", m_bandwidth.value(), width);
        throw std::runtime_error("Bandwidth substitution without a Bandwidth being set");
    }
    if (varname == "Time") {
        if (m_time) return std::format("{:0{}d}", m_time.value(), width);
        throw std::runtime_error("Time substitution without a Time being set");
    }
    if (varname == "SubNumber") {
        if (m_subNumber) return std::format("{:0{}d}", m_subNumber.value(), width);
        throw std::runtime_error("SubNumber substitution without a SubNumber being set");
    }

    // If we can't substitute, throw an exception
    throw std::runtime_error("Substitute for \"" + fmt + "\" unrecognised");
}

/******** SegmentTemplate ********/

SegmentTemplate::SegmentTemplate()
    :MultipleSegmentBase()
    ,m_media()
    ,m_index()
    ,m_initialization()
    ,m_bitstreamSwitching()
{
}

SegmentTemplate::SegmentTemplate(const SegmentTemplate &other)
    :MultipleSegmentBase(other)
    ,m_media(other.m_media)
    ,m_index(other.m_index)
    ,m_initialization(other.m_initialization)
    ,m_bitstreamSwitching(other.m_bitstreamSwitching)
{
}

SegmentTemplate::SegmentTemplate(SegmentTemplate &&other)
    :MultipleSegmentBase(std::move(other))
    ,m_media(std::move(other.m_media))
    ,m_index(std::move(other.m_index))
    ,m_initialization(std::move(other.m_initialization))
    ,m_bitstreamSwitching(std::move(other.m_bitstreamSwitching))
{
}

SegmentTemplate &SegmentTemplate::operator=(const SegmentTemplate &other)
{
    MultipleSegmentBase::operator=(other);
    m_media = other.m_media;
    m_index = other.m_index;
    m_initialization = other.m_initialization;
    m_bitstreamSwitching = other.m_bitstreamSwitching;
    return *this;
}

SegmentTemplate &SegmentTemplate::operator=(SegmentTemplate &&other)
{
    MultipleSegmentBase::operator=(std::move(other));
    m_media = std::move(other.m_media);
    m_index = std::move(other.m_index);
    m_initialization = std::move(other.m_initialization);
    m_bitstreamSwitching = std::move(other.m_bitstreamSwitching);
    return *this;
}

bool SegmentTemplate::operator==(const SegmentTemplate &other) const
{
    if (m_media.has_value() != other.m_media.has_value()) return false;
    if (m_media && !(m_media.value() == other.m_media.value())) return false;

    if (m_index.has_value() != other.m_index.has_value()) return false;
    if (m_index && !(m_index.value() == other.m_index.value())) return false;

    if (m_initialization.has_value() != other.m_initialization.has_value()) return false;
    if (m_initialization && !(m_initialization.value() == other.m_initialization.value())) return false;

    if (m_bitstreamSwitching.has_value() != other.m_bitstreamSwitching.has_value()) return false;
    if (m_bitstreamSwitching && !(m_bitstreamSwitching.value() == other.m_bitstreamSwitching.value())) return false;

    return MultipleSegmentBase::operator==(other);
}

std::string SegmentTemplate::formatMediaTemplate(const SegmentTemplate::Variables &vars) const
{
    std::string ret;
    if (m_media) {
        ret = formatTemplate(m_media.value(), vars);
    }
    return ret;
}

std::string SegmentTemplate::formatIndexTemplate(const SegmentTemplate::Variables &vars) const
{
    std::string ret;
    if (m_index) {
        ret = formatTemplate(m_index.value(), vars);
    }
    return ret;
}

std::string SegmentTemplate::formatInitializationTemplate(const SegmentTemplate::Variables &vars) const
{
    std::string ret;
    if (m_initialization) {
        ret = formatTemplate(m_initialization.value(), vars);
    }
    return ret;
}

std::string SegmentTemplate::formatBitstreamSwitchingTemplate(const SegmentTemplate::Variables &vars) const
{
    std::string ret;
    if (m_bitstreamSwitching) {
        ret = formatTemplate(m_bitstreamSwitching.value(), vars);
    }
    return ret;
}

/* protected: */
SegmentTemplate::SegmentTemplate(xmlpp::Node &node)
    :MultipleSegmentBase(node)
    ,m_media()
    ,m_index()
    ,m_initialization()
    ,m_bitstreamSwitching()
{
    xmlpp::Node::NodeSet node_set;

    node_set = node.find("@media");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_media = std::string(attr->get_value());
    }

    node_set = node.find("@index");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_index = std::string(attr->get_value());
    }

    node_set = node.find("@initialization");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_initialization = std::string(attr->get_value());
    }

    node_set = node.find("@bitstreamSwitching");
    if (node_set.size() > 0) {
        xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front());
        m_bitstreamSwitching = std::string(attr->get_value());
    }
}

void SegmentTemplate::setXMLElement(xmlpp::Element &elem) const
{
    MultipleSegmentBase::setXMLElement(elem);
    if (m_media) {
        elem.set_attribute("media", m_media.value());
    }
    if (m_index) {
        elem.set_attribute("index", m_index.value());
    }
    if (m_initialization) {
        elem.set_attribute("initialization", m_initialization.value());
    }
    if (m_bitstreamSwitching) {
        elem.set_attribute("bitstreamSwitching", m_bitstreamSwitching.value());
    }
}

// private:

std::string SegmentTemplate::formatTemplate(const std::string &fmt, const SegmentTemplate::Variables &vars) const
{
    std::string ret(fmt);
    const auto &start_number = startNumber();
    for (auto pos = ret.find_first_of('$'); pos != std::string::npos; pos = ret.find_first_of('$', pos+1)) {
        auto epos = ret.find_first_of('$', pos+1);
        if (epos == std::string::npos) break;
        try {
            ret.replace(pos, epos-pos+1, vars.format(ret.substr(pos, epos-pos+1), start_number));
        } catch (std::runtime_error &ex) {
        }
    }
    return ret;
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
