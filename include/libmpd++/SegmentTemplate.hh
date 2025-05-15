#ifndef _BBC_PARSE_DASH_MPD_SEGMENT_TEMPLATE_HH_
#define _BBC_PARSE_DASH_MPD_SEGMENT_TEMPLATE_HH_
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
#include <chrono>
#include <optional>
#include <string>

#include "macros.hh"
#include "MultipleSegmentBase.hh"

namespace xmlpp {
    class Element;
    class Node;
}

LIBMPDPP_NAMESPACE_BEGIN

class AdaptationSet;
class Representation;

class LIBMPDPP_PUBLIC_API SegmentTemplate : public MultipleSegmentBase {
public:
    class Variables {
    public:
        using duration_type = std::chrono::microseconds;

        Variables(const std::optional<std::string> &rep_id = std::nullopt,
                  const std::optional<unsigned long> &number = std::nullopt,
                  const std::optional<unsigned int> &bandwidth = std::nullopt,
                  const std::optional<unsigned long> &time = std::nullopt,
                  const std::optional<unsigned long> &sub_number = std::nullopt
                 )
            :m_representationId(rep_id)
            ,m_number(number)
            ,m_bandwidth(bandwidth)
            ,m_time(time)
            ,m_subNumber(sub_number)
        {};
        Variables(const Variables &other)
            :m_representationId(other.m_representationId)
            ,m_number(other.m_number)
            ,m_bandwidth(other.m_bandwidth)
            ,m_time(other.m_time)
            ,m_subNumber(other.m_subNumber)
        {};
        Variables(Variables &&other)
            :m_representationId(std::move(other.m_representationId))
            ,m_number(std::move(other.m_number))
            ,m_bandwidth(std::move(other.m_bandwidth))
            ,m_time(std::move(other.m_time))
            ,m_subNumber(std::move(other.m_subNumber))
        {};

        virtual ~Variables() {};

        Variables &operator=(const Variables &other) {
            m_representationId = other.m_representationId;
            m_number = other.m_number;
            m_bandwidth = other.m_bandwidth;
            m_time = other.m_time;
            m_subNumber = other.m_subNumber;
            return *this;
        };

        Variables &operator=(Variables &&other) {
            m_representationId = std::move(other.m_representationId);
            m_number = std::move(other.m_number);
            m_bandwidth = std::move(other.m_bandwidth);
            m_time = std::move(other.m_time);
            m_subNumber = std::move(other.m_subNumber);
            return *this;
        };

        const std::optional<std::string> &representationId() const { return m_representationId; };
        std::optional<std::string> &representationId() { return m_representationId; };
        Variables &representationId(const std::nullopt_t&) { m_representationId.reset(); return *this; };
        Variables &representationId(const std::string &val) { m_representationId = val; return *this; };
        Variables &representationId(std::string &&val) { m_representationId = std::move(val); return *this; };

        const std::optional<unsigned long> &number() const { return m_number; };
        std::optional<unsigned long> &number() { return m_number; };
        Variables &number(const std::nullopt_t&) { m_number.reset(); return *this; };
        Variables &number(unsigned long val) { m_number = val; return *this; };

        const std::optional<unsigned int> &bandwidth() const { return m_bandwidth; };
        std::optional<unsigned int> &bandwidth() { return m_bandwidth; };
        Variables &bandwidth(const std::nullopt_t&) { m_bandwidth.reset(); return *this; };
        Variables &bandwidth(unsigned int val) { m_bandwidth = val; return *this; };

        const std::optional<unsigned long> &time() const { return m_time; };
        std::optional<unsigned long> &time() { return m_time; };
        Variables &time(const std::nullopt_t&) { m_time.reset(); return *this; };
        Variables &time(unsigned long val) { m_time = val; return *this; };
        duration_type timeAsDurationType(unsigned int timescale) const {
            return std::chrono::duration_cast<duration_type>(std::chrono::duration<double, std::ratio<1> >(static_cast<double>(m_time?m_time.value():0) / timescale));
        };

        const std::optional<unsigned long> &subNumber() const { return m_subNumber; };
        std::optional<unsigned long> &subNumber() { return m_subNumber; };
        Variables &subNumber(const std::nullopt_t&) { m_subNumber.reset(); return *this; };
        Variables &subNumber(unsigned long val) { m_subNumber = val; return *this; };

        std::string format(const std::string &format, const std::optional<unsigned int> &start_number = std::nullopt) const;

    private:
        std::optional<std::string> m_representationId;
        std::optional<unsigned long> m_number;
        std::optional<unsigned int> m_bandwidth;
        std::optional<unsigned long> m_time;
        std::optional<unsigned long> m_subNumber;
    };

    SegmentTemplate();
    SegmentTemplate(const SegmentTemplate&);
    SegmentTemplate(SegmentTemplate&&);

    virtual ~SegmentTemplate() {};

    SegmentTemplate &operator=(const SegmentTemplate&);
    SegmentTemplate &operator=(SegmentTemplate&&);

    bool operator==(const SegmentTemplate &) const;

    std::string formatMediaTemplate(const Variables &) const;
    std::string formatIndexTemplate(const Variables &) const;
    std::string formatInitializationTemplate(const Variables &) const;
    std::string formatBitstreamSwitchingTemplate(const Variables &) const;

    // @media
    bool hasMedia() const { return m_media.has_value(); };
    const std::optional<std::string> &media() const { return m_media; };
    SegmentTemplate &media(const std::nullopt_t&) { m_media.reset(); return *this; };
    SegmentTemplate &media(const std::string &val) { m_media = val; return *this; };
    SegmentTemplate &media(std::string &&val) { m_media = std::move(val); return *this; };

    // @index
    bool hasIndex() const { return m_index.has_value(); };
    const std::optional<std::string> &index() const { return m_index; };
    SegmentTemplate &index(const std::nullopt_t&) { m_index.reset(); return *this; };
    SegmentTemplate &index(const std::string &val) { m_index = val; return *this; };
    SegmentTemplate &index(std::string &&val) { m_index = std::move(val); return *this; };

    // @initialization
    bool hasInitialization() const { return m_initialization.has_value(); };
    const std::optional<std::string> &initialization() const { return m_initialization; };
    SegmentTemplate &initialization(const std::nullopt_t&) { m_initialization.reset(); return *this; };
    SegmentTemplate &initialization(const std::string &val) { m_initialization = val; return *this; };
    SegmentTemplate &initialization(std::string &&val) { m_initialization = std::move(val); return *this; };

    // @bitstreamSwitching
    bool hasBitstreamSwitching() const { return m_bitstreamSwitching.has_value(); };
    const std::optional<std::string> &bitstreamSwitching() const { return m_bitstreamSwitching; };
    SegmentTemplate &bitstreamSwitching(const std::nullopt_t&) { m_bitstreamSwitching.reset(); return *this; };
    SegmentTemplate &bitstreamSwitching(const std::string &val) { m_bitstreamSwitching = val; return *this; };
    SegmentTemplate &bitstreamSwitching(std::string &&val) { m_bitstreamSwitching = std::move(val); return *this; };

protected:
    friend class Period;
    friend class AdaptationSet;
    friend class Representation;
    SegmentTemplate(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;

private:
    std::string formatTemplate(const std::string &fmt, const Variables &vars) const;

    // SegmentTemplate derived from ISO 23009-1:2022 Clause 5.3.9.4.3
    // Attributes
    std::optional<std::string> m_media;
    std::optional<std::string> m_index;
    std::optional<std::string> m_initialization;
    std::optional<std::string> m_bitstreamSwitching;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_SEGMENT_TEMPLATE_HH_*/
