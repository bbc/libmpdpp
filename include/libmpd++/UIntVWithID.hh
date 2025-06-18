#ifndef _BBC_PARSE_DASH_MPD_U_INT_V_WITH_I_D_HH_
#define _BBC_PARSE_DASH_MPD_U_INT_V_WITH_I_D_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: UIntVWithID class
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

/** UIntVWithID class
 *
 * Container for %DASH %MPD schema %UIntVWithIDType.
 */
class LIBMPDPP_PUBLIC_API UIntVWithID : public std::list<unsigned int> {
public:
    UIntVWithID() = delete;
    UIntVWithID(unsigned int id,
                const std::list<URI> &profiles = std::list<URI>{},
                const std::optional<RFC6838ContentType> &content_type = std::nullopt);
    UIntVWithID(const std::list<unsigned int> &init, unsigned int id,
                const std::list<URI> &profiles = std::list<URI>{},
                const std::optional<RFC6838ContentType> &content_type = std::nullopt);
    UIntVWithID(std::list<unsigned int> &&init, unsigned int id,
                const std::list<URI> &profiles = std::list<URI>{},
                const std::optional<RFC6838ContentType> &content_type = std::nullopt);
    UIntVWithID(std::initializer_list<unsigned int> init, unsigned int id,
                const std::list<URI> &profiles = std::list<URI>{},
                const std::optional<RFC6838ContentType> &content_type = std::nullopt);
    UIntVWithID(const UIntVWithID &to_copy);
    UIntVWithID(UIntVWithID &&to_move);

    virtual ~UIntVWithID() {};

    UIntVWithID &operator=(const UIntVWithID &to_copy);
    UIntVWithID &operator=(UIntVWithID &&to_move);

    bool operator==(const UIntVWithID &other) const;

    operator std::string() const;

    // @id
    unsigned int id() const { return m_id; };
    UIntVWithID &id(unsigned int val) { m_id = val; return *this; };

    // @profiles
    const std::list<URI> &profiles() const { return m_profiles; };
    std::list<URI>::const_iterator profilesBegin() const { return m_profiles.cbegin(); };
    std::list<URI>::iterator profilesBegin() { return m_profiles.begin(); };
    std::list<URI>::const_iterator profilesEnd() const { return m_profiles.cend(); };
    std::list<URI>::iterator profilesEnd() { return m_profiles.end(); };
    const URI &profile(std::list<URI>::size_type idx) const;
    UIntVWithID &profiles(const std::list<URI> &val) { m_profiles = val; return *this; };
    UIntVWithID &profiles(std::list<URI> &&val) { m_profiles = std::move(val); return *this; };
    UIntVWithID &profilesAdd(const URI &val) { m_profiles.push_back(val); return *this; };
    UIntVWithID &profilesAdd(URI &&val) { m_profiles.push_back(std::move(val)); return *this; };
    UIntVWithID &profilesRemove(const URI &val);
    UIntVWithID &profilesRemove(const std::list<URI>::const_iterator &it);
    UIntVWithID &profilesRemove(const std::list<URI>::iterator &it);

    // @contentType
    bool hasContentType() const { return m_contentType.has_value(); };
    const std::optional<RFC6838ContentType> &contentType() const { return m_contentType; };
    UIntVWithID &contentType(const std::nullopt_t&) { m_contentType.reset(); return *this; };
    UIntVWithID &contentType(const RFC6838ContentType &val) { m_contentType = val; return *this; };
    UIntVWithID &contentType(RFC6838ContentType &&val) { m_contentType = std::move(val); return *this; };
    UIntVWithID &contentType(const std::optional<RFC6838ContentType> &val) { m_contentType = val; return *this; };
    UIntVWithID &contentType(std::optional<RFC6838ContentType> &&val) { m_contentType = std::move(val); return *this; };

///@cond PROTECTED
protected:
    friend class MPD;
    UIntVWithID(xmlpp::Node&);
    void setXMLElement(xmlpp::Element&) const;
///@endcond PROTECTED

private:
    unsigned int                      m_id;
    std::list<URI>                    m_profiles;
    std::optional<RFC6838ContentType> m_contentType;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_U_INT_V_WITH_I_D_HH_*/
