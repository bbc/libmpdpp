#ifndef _BBC_PARSE_DASH_MPD_PROGRAM_INFORMATION_HH_
#define _BBC_PARSE_DASH_MPD_PROGRAM_INFORMATION_HH_
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
#include <optional>
#include <string>

#include "macros.hh"
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

/** ProgramInformation class
 * @headerfile libmpd++/ProgramInformation.hh <libmpd++/ProgramInformation.hh>
 *
 * Container for %DASH %MPD schema %ProgramInformationType as found in ISO 23009-1:2022 Clause 5.7.3.
 *
 * @todo Add the attributes and child elements for %ProgramInformationType in the schema.
 */
class LIBMPDPP_PUBLIC_API ProgramInformation {
public:
    ProgramInformation();
    ProgramInformation(const ProgramInformation &to_copy);
    ProgramInformation(ProgramInformation &&to_move);

    virtual ~ProgramInformation() {};

    ProgramInformation &operator=(const ProgramInformation &to_copy);
    ProgramInformation &operator=(ProgramInformation &&to_move);

    bool operator==(const ProgramInformation &other) const;

    bool hasLang() const { return m_lang.has_value(); };
    const std::optional<std::string> &lang() const { return m_lang; };
    ProgramInformation &lang(const std::nullopt_t&) { m_lang.reset(); return *this; };
    ProgramInformation &lang(const std::string &val) { m_lang = val; return *this; };
    ProgramInformation &lang(std::string &&val) { m_lang = std::move(val); return *this; };
    ProgramInformation &lang(const std::optional<std::string> &val) { m_lang = val; return *this; };
    ProgramInformation &lang(std::optional<std::string> &&val) { m_lang = std::move(val); return *this; };

    bool hasMoreInformationURL() const { return m_moreInformationURL.has_value(); };
    const std::optional<URI> &moreInformationURL() const { return m_moreInformationURL; };
    ProgramInformation &moreInformationURL(const std::nullopt_t&) { m_moreInformationURL.reset(); return *this; };
    ProgramInformation &moreInformationURL(const URI &val) { m_moreInformationURL = val; return *this; };
    ProgramInformation &moreInformationURL(URI &&val) { m_moreInformationURL = std::move(val); return *this; };
    ProgramInformation &moreInformationURL(const std::optional<URI> &val) { m_moreInformationURL = val; return *this; };
    ProgramInformation &moreInformationURL(std::optional<URI> &&val) { m_moreInformationURL = std::move(val); return *this; };

    bool hasTitle() const { return m_title.has_value(); };
    const std::optional<std::string> &title() const { return m_title; };
    ProgramInformation &title(const std::nullopt_t&) { m_title.reset(); return *this; };
    ProgramInformation &title(const std::string &val) { m_title = val; return *this; };
    ProgramInformation &title(std::string &&val) { m_title = std::move(val); return *this; };
    ProgramInformation &title(const std::optional<std::string> &val) { m_title = val; return *this; };
    ProgramInformation &title(std::optional<std::string> &&val) { m_title = std::move(val); return *this; };

    bool hasSource() const { return m_source.has_value(); };
    const std::optional<std::string> &source() const { return m_source; };
    ProgramInformation &source(const std::nullopt_t&) { m_source.reset(); return *this; };
    ProgramInformation &source(const std::string &val) { m_source = val; return *this; };
    ProgramInformation &source(std::string &&val) { m_source = std::move(val); return *this; };
    ProgramInformation &source(const std::optional<std::string> &val) { m_source = val; return *this; };
    ProgramInformation &source(std::optional<std::string> &&val) { m_source = std::move(val); return *this; };

    bool hasCopyright() const { return m_copyright.has_value(); };
    const std::optional<std::string> &copyright() const { return m_copyright; };
    ProgramInformation &copyright(const std::nullopt_t&) { m_copyright.reset(); return *this; };
    ProgramInformation &copyright(const std::string &val) { m_copyright = val; return *this; };
    ProgramInformation &copyright(std::string &&val) { m_copyright = std::move(val); return *this; };
    ProgramInformation &copyright(const std::optional<std::string> &val) { m_copyright = val; return *this; };
    ProgramInformation &copyright(std::optional<std::string> &&val) { m_copyright = std::move(val); return *this; };

///@cond PROTECTED
protected:
    friend class MPD;
    ProgramInformation(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    // The attributes and child elements for %ProgramInformationType in the schema.
    std::optional<std::string> m_lang;
    std::optional<URI>         m_moreInformationURL;

    std::optional<std::string> m_title;
    std::optional<std::string> m_source;
    std::optional<std::string> m_copyright;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_PROGRAM_INFORMATION_HH_*/
