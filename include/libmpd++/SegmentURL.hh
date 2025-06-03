#ifndef _BBC_PARSE_DASH_MPD_SEGMENT_URL_HH_
#define _BBC_PARSE_DASH_MPD_SEGMENT_URL_HH_
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
#include <chrono>
#include <optional>

#include "macros.hh"
#include "SingleRFC7233Range.hh"
#include "URI.hh"

/**@cond
 */
// Forward declarations for types only used by pointer or reference
namespace xmlpp {
    class Element;
    class Node;
}
/**@endcond
 */

LIBMPDPP_NAMESPACE_BEGIN

class LIBMPDPP_PUBLIC_API SegmentURL {
public:
    SegmentURL();
    SegmentURL(const SegmentURL &other);
    SegmentURL(SegmentURL &&other);

    virtual ~SegmentURL() {};

    SegmentURL &operator=(const SegmentURL &other);
    SegmentURL &operator=(SegmentURL &&other);

    bool operator==(const SegmentURL &other) const;

    // @media
    bool hasMedia() const { return m_media.has_value(); };
    const std::optional<URI> &media() const { return m_media; };
    SegmentURL &media(const std::nullopt_t&) { m_media.reset(); return *this; };
    SegmentURL &media(const URI &val) { m_media = val; return *this; };
    SegmentURL &media(URI &&val) { m_media = std::move(val); return *this; };

    // @mediaRange
    bool hasMediaRange() const { return m_mediaRange.has_value(); };
    const std::optional<SingleRFC7233Range> &mediaRange() const { return m_mediaRange; };
    SegmentURL &mediaRange(const std::nullopt_t&) { m_mediaRange.reset(); return *this; };
    SegmentURL &mediaRange(const SingleRFC7233Range &val) { m_mediaRange = val; return *this; };
    SegmentURL &mediaRange(SingleRFC7233Range &&val) { m_mediaRange = std::move(val); return *this; };

    // @index
    bool hasIndex() const { return m_index.has_value(); };
    const std::optional<URI> &index() const { return m_index; };
    SegmentURL &index(const std::nullopt_t&) { m_index.reset(); return *this; };
    SegmentURL &index(const URI &val) { m_index = val; return *this; };
    SegmentURL &index(URI &&val) { m_index = std::move(val); return *this; };

    // @indexRange
    bool hasIndexRange() const { return m_indexRange.has_value(); };
    const std::optional<SingleRFC7233Range> &indexRange() const { return m_indexRange; };
    SegmentURL &indexRange(const std::nullopt_t&) { m_indexRange.reset(); return *this; };
    SegmentURL &indexRange(const SingleRFC7233Range &val) { m_indexRange = val; return *this; };
    SegmentURL &indexRange(SingleRFC7233Range &&val) { m_indexRange = std::move(val); return *this; };

protected:
    friend class Period;
    SegmentURL(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    // SegmentURL element from ISO 23009-1:2022 Clause 5.3.9.3.3
    // Attributes
    std::optional<URI> m_media;
    std::optional<SingleRFC7233Range> m_mediaRange;
    std::optional<URI> m_index;
    std::optional<SingleRFC7233Range> m_indexRange;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SEGMENT_URL_HH_*/
