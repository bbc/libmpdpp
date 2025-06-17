#ifndef _BBC_PARSE_DASH_MPD_LABEL_HH_
#define _BBC_PARSE_DASH_MPD_LABEL_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Label class
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <optional>
#include <string>

#include "macros.hh"

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

class Period;

/** Label class
 *
 * Container for %LabelType elements from an %MPD (ISO 23009-1:2022 Clause 5.3.10.3).
 */
class LIBMPDPP_PUBLIC_API Label : public std::string {
public:
    Label() : std::string(), m_id(0), m_lang() {};
    Label(const std::string &val) : std::string(val), m_id(0), m_lang() {};
    Label(std::string &&val) : std::string(std::move(val)), m_id(0), m_lang() {};
    Label(const Label &other) : std::string(other), m_id(other.m_id), m_lang(other.m_lang) {};
    Label(Label &&other) : std::string(std::move(other)), m_id(other.m_id), m_lang(std::move(other.m_lang)) {};

    virtual ~Label() {};

    Label &operator=(const std::string &val) { std::string::operator=(val); return *this; };
    Label &operator=(std::string &&val) { std::string::operator=(std::move(val)); return *this; };

    Label &operator=(const Label &to_copy) { std::string::operator=(to_copy); m_id = to_copy.m_id; m_lang = to_copy.m_lang; return *this; };
    Label &operator=(Label &&to_move) { std::string::operator=(std::move(to_move)); m_id = to_move.m_id; m_lang = std::move(to_move.m_lang); return *this; };

    bool operator==(const Label &to_compare) const;

    // @id
    unsigned int id() const { return m_id; };
    Label &id(unsigned int val) { m_id = val; return *this; };

    //@lang
    bool hasLang() const { return m_lang.has_value(); };
    const std::optional<std::string> &lang() const { return m_lang; };
    Label &lang(const std::nullopt_t&) { m_lang.reset(); return *this; };
    Label &lang(const std::string &val) { m_lang = val; return *this; };
    Label &lang(std::string &&val) { m_lang = std::move(val); return *this; };
    Label &lang(const std::optional<std::string> &val) { m_lang = val; return *this; };
    Label &lang(std::optional<std::string> &&val) { m_lang = std::move(val); return *this; };

///@cond PROTECTED
protected:
    friend class Period;
    friend class RepresentationBase;
    Label(xmlpp::Node &node);
    void setXMLElement(xmlpp::Element &elem) const;
///@endcond PROTECTED

private:
    // LabelType attributes from ISO 23009-1:2022 Clause 5.3.10.3
    unsigned int               m_id;
    std::optional<std::string> m_lang;

    // LabelType data type from ISO 23009-1:2022 Clause 5.3.10.3
    std::string                m_label;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_LABEL_HH_*/
