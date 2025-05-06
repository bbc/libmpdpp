#ifndef _BBC_PARSE_DASH_MPD_SEGMENT_LIST_HH_
#define _BBC_PARSE_DASH_MPD_SEGMENT_LIST_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: SegmentList class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <optional>

#include "macros.hh"
#include "MultipleSegmentBase.hh"
#include "SegmentURL.hh"
#include "XLink.hh"

namespace xmlpp {
    class Element;
    class Node;
}

LIBPARSEMPD_NAMESPACE_BEGIN

class Period;
class AdaptationSet;
class Representation;

class LIBPARSEMPD_PUBLIC_API SegmentList : public MultipleSegmentBase {
public:
    SegmentList()
        :MultipleSegmentBase()
        ,m_xLink()
        ,m_segmentURLs()
    {};
    SegmentList(const SegmentList &other)
        :MultipleSegmentBase(other)
        ,m_xLink(other.m_xLink)
        ,m_segmentURLs(other.m_segmentURLs)
    {};
    SegmentList(SegmentList &&other)
        :MultipleSegmentBase(std::move(other))
        ,m_xLink(std::move(other.m_xLink))
        ,m_segmentURLs(std::move(other.m_segmentURLs))
    {};

    virtual ~SegmentList() {};

    SegmentList &operator=(const SegmentList &other) {
        MultipleSegmentBase::operator=(other);
        m_xLink = other.m_xLink;
        m_segmentURLs = other.m_segmentURLs;
        return *this;
    }
    SegmentList &operator=(SegmentList &&other) {
        MultipleSegmentBase::operator=(std::move(other));
        m_xLink = std::move(other.m_xLink);
        m_segmentURLs = std::move(other.m_segmentURLs);
        return *this;
    }

    bool operator==(const SegmentList &other) const {
        if (m_xLink.has_value() != other.m_xLink.has_value()) return false;
        if (m_xLink && !(m_xLink.value() == other.m_xLink.value())) return false;
        if (m_segmentURLs != other.m_segmentURLs) return false;
        return MultipleSegmentBase::operator==(other);
    };

    bool hasXLink() const { return m_xLink.has_value(); };
    const std::optional<XLink> &xLink() const { return m_xLink; };
    SegmentList &xLink(const std::nullopt_t&) { m_xLink.reset(); return *this; };
    SegmentList &xLink(const XLink &val) { m_xLink = val; return *this; };
    SegmentList &xLink(XLink &&val) { m_xLink = std::move(val); return *this; };

    const std::list<SegmentURL> &segmentURLs() const { return m_segmentURLs; };
    std::list<SegmentURL>::const_iterator segmentURLsBegin() const { return m_segmentURLs.cbegin(); };
    std::list<SegmentURL>::const_iterator segmentURLsEnd() const { return m_segmentURLs.cend(); };
    std::list<SegmentURL>::iterator segmentURLsBegin() { return m_segmentURLs.begin(); };
    std::list<SegmentURL>::iterator segmentURLsEnd() { return m_segmentURLs.end(); };
    SegmentList &segmentURLAdd(const SegmentURL &val) { m_segmentURLs.push_back(val); return *this; };
    SegmentList &segmentURLAdd(SegmentURL &&val) { m_segmentURLs.push_back(std::move(val)); return *this; };
    SegmentList &segmentURLRemove(const SegmentURL &val) { m_segmentURLs.remove(val); return *this; };
    SegmentList &segmentURLRemove(const std::list<SegmentURL>::const_iterator &it) { m_segmentURLs.erase(it); return *this; };
    SegmentList &segmentURLRemove(const std::list<SegmentURL>::iterator &it) { m_segmentURLs.erase(it); return *this; };

protected:
    friend class Period;
    friend class Representation;
    friend class AdaptationSet;
    SegmentList(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    // SegmentList derived from XML schema in ISO 23009-1:2022 Clause 5.3.9.3.3
    // Attributes
    std::optional<XLink> m_xLink;
    // Elements
    std::list<SegmentURL> m_segmentURLs;
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SEGMENT_LIST_HH_*/
