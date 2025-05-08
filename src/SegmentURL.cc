/*****************************************************************************
 * DASH MPD parsing library in C++: SegmentURL class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <optional>

#include <libxml++/libxml++.h>

#include "libmpd++/macros.hh"
#include "libmpd++/SingleRFC7233Range.hh"
#include "libmpd++/URI.hh"

#include "libmpd++/SegmentURL.hh"

LIBMPDPP_NAMESPACE_BEGIN

SegmentURL::SegmentURL()
    :m_media()
    ,m_mediaRange()
    ,m_index()
    ,m_indexRange()
{
}

SegmentURL::SegmentURL(const SegmentURL &other)
    :m_media(other.m_media)
    ,m_mediaRange(other.m_mediaRange)
    ,m_index(other.m_index)
    ,m_indexRange(other.m_indexRange)
{
}

SegmentURL::SegmentURL(SegmentURL &&other)
    :m_media(std::move(other.m_media))
    ,m_mediaRange(std::move(other.m_mediaRange))
    ,m_index(std::move(other.m_index))
    ,m_indexRange(std::move(other.m_indexRange))
{
}

SegmentURL &SegmentURL::operator=(const SegmentURL &other)
{
    m_media = other.m_media;
    m_mediaRange = other.m_mediaRange;
    m_index = other.m_index;
    m_indexRange = other.m_indexRange;
    return *this;
}

SegmentURL &SegmentURL::operator=(SegmentURL &&other)
{
    m_media = std::move(other.m_media);
    m_mediaRange = std::move(other.m_mediaRange);
    m_index = std::move(other.m_index);
    m_indexRange = std::move(other.m_indexRange);
    return *this;
}

bool SegmentURL::operator==(const SegmentURL &other) const
{
#define COMPARE_OPT(var) do { \
        if (var.has_value() != other.var.has_value()) return false; \
        if (var && !(var.value() == other.var.value())) return false; \
    } while(0)

    COMPARE_OPT(m_media);
    COMPARE_OPT(m_mediaRange);
    COMPARE_OPT(m_index);
    COMPARE_OPT(m_indexRange);

#undef COMPARE_OPT

    return true;
}

// protected:
SegmentURL::SegmentURL(xmlpp::Node &node)
    :m_media()
    ,m_mediaRange()
    ,m_index()
    ,m_indexRange()
{
    xmlpp::Node::NodeSet node_set;

#define OPT_ATTR_FN(name, fn) do { \
        node_set = node.find("@" #name); \
        if (node_set.size() > 0) { \
            xmlpp::Attribute *attr = dynamic_cast<xmlpp::Attribute*>(node_set.front()); \
            m_ ## name = fn(std::string(attr->get_value())); \
        } \
    } while(0)

    OPT_ATTR_FN(media, URI);
    OPT_ATTR_FN(mediaRange, SingleRFC7233Range);
    OPT_ATTR_FN(index, URI);
    OPT_ATTR_FN(indexRange, SingleRFC7233Range);

#undef OPT_ATTR_FN
}

void SegmentURL::setXMLElement(xmlpp::Element &elem) const
{
#define OPT_ATTR(name) do { \
        if (m_ ## name) { \
            elem.set_attribute(#name, std::string(m_ ## name.value())); \
        } \
    } while(0)

    OPT_ATTR(media);
    OPT_ATTR(mediaRange);
    OPT_ATTR(index);
    OPT_ATTR(indexRange);

#undef OPT_ATTR
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
