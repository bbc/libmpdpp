#ifndef _BBC_PARSE_DASH_MPD_SEGMENT_TIMELINE_HH_
#define _BBC_PARSE_DASH_MPD_SEGMENT_TIMELINE_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: SegmentTimeline class
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
#include <list>

#include "macros.hh"
#include "FailoverContent.hh"
#include "SingleRFC7233Range.hh"
#include "URL.hh"

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

/** SegmentTimeline class
 * @headerfile libmpd++/SegmentTimeline.hh <libmpd++/SegmentTimeline.hh>
 *
 * Container for %DASH %MPD schema %SegmentTimelineType found in ISO 23009-1:2022 Clause 5.3.9.6.3.
 */
class LIBMPDPP_PUBLIC_API SegmentTimeline {
public:
    using duration_type = std::chrono::microseconds;

    /** SegmentTimeline::S class
     *
     * Container for %DASH %MPD schema %SType.
     */
    class LIBMPDPP_PUBLIC_API S {
    public:
        S();
        S(const S&);
        S(S&&);

        virtual ~S() {};

        S &operator=(const S&);
        S &operator=(S&&);

        bool operator==(const S&) const;

    ///@cond PROTECTED
    protected:
        friend class SegmentTimeline;
        S(xmlpp::Node&);
        void setXMLElement(xmlpp::Element&) const;
    ///@endcond PROTECTED

    private:
        // S element type ISO 23009-1:2022 Clause 5.3.9.6.3
        std::optional<unsigned long> m_t;
        std::optional<unsigned long> m_n;
        unsigned long m_d;
        int m_r;
        unsigned long m_k;
    };

    SegmentTimeline() :m_sLines() {};
    SegmentTimeline(const SegmentTimeline &other) :m_sLines(other.m_sLines) {};
    SegmentTimeline(SegmentTimeline &&other) :m_sLines(std::move(other.m_sLines)) {};

    virtual ~SegmentTimeline() {};

    SegmentTimeline &operator=(const SegmentTimeline &other) { m_sLines = other.m_sLines; return *this; };
    SegmentTimeline &operator=(SegmentTimeline &&other) { m_sLines = std::move(other.m_sLines); return *this; };

    bool operator==(const SegmentTimeline &other) const { return m_sLines == other.m_sLines; };

///@cond PROTECTED
protected:
    friend class MultipleSegmentBase;
    SegmentTimeline(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // SegmentTimeline element from ISO 23009-1:2022 Clause 5.3.9.6.3
    std::list<S> m_sLines;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SEGMENT_TIMELINE_HH_*/
