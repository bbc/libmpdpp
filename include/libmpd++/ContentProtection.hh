#ifndef _BBC_PARSE_DASH_MPD_CONTENT_PROTECTION_HH_
#define _BBC_PARSE_DASH_MPD_CONTENT_PROTECTION_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: ContentProtection class
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
#include "Descriptor.hh"

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

/** ContentProtection class
 * @headerfile libmpd++/ContentProtection.hh <libmpd++/ContentProtection.hh>
 *
 * This is a container for the %ContentProtectionType element from the %DASH %MPD %XML schema.
 * The schema definition can be found in ISO 23009-1:2022 Clause 5.8.4.1.5
 */
class LIBMPDPP_PUBLIC_API ContentProtection : public Descriptor {
public:

    /** Default constructor (deleted)
     *
     * This class must be instantiated with at least a schemeId.
     */
    ContentProtection() = delete;

    /**@{*/
    /** Constructor
     * 
     * Create a new ContentProtection object withthe @p scheme_id set as the @@schemeId attribute.
     *
     * @param scheme_id The @@schemeId attribute value for the content protection.
     * @param value The optional @@value attribute value for the content protection.
     * @param id The optional @@id attribute value for the content protection.
     * @param robustness The optional @@robustness attribute value.
     * @param ref_id The optional @@refId attribute value.
     * @param ref The optional @@ref attribute value.
     */
    ContentProtection(const URI &scheme_id,
                      const std::optional<std::string> &value = std::nullopt,
                      const std::optional<std::string> &id = std::nullopt,
                      const std::optional<std::string> &robustness = std::nullopt,
                      const std::optional<std::string> &ref_id = std::nullopt,
                      const std::optional<std::string> &ref = std::nullopt);
    ContentProtection(URI &&scheme_id,
                      const std::optional<std::string> &value = std::nullopt,
                      const std::optional<std::string> &id = std::nullopt,
                      const std::optional<std::string> &robustness = std::nullopt,
                      const std::optional<std::string> &ref_id = std::nullopt,
                      const std::optional<std::string> &ref = std::nullopt);
    /**@}*/

    /** Copy constructor
     *
     * @param to_copy The other ContentProtection object to copy as a new ContentProtection.
     */
    ContentProtection(const ContentProtection &to_copy);

    /** Move constructor
     *
     * @param to_move The other ContentProtection object to move the values and resources from to make a new ContentProtection.
     */
    ContentProtection(ContentProtection &&to_move);

    /** Destructor
     */
    virtual ~ContentProtection() {};

    ContentProtection &operator=(const ContentProtection &to_copy);
    ContentProtection &operator=(ContentProtection &&to_move);

    /** Equality operator
     *
     * @brief Compares this ContentProtection with another for equality.
     * This operator overload allows checking if two ContentProtection instances are equal.
     * Currently, the implementation always returns true, meaning all instances are considered equal,
     * regardless of their internal state.
     * @param other A constant reference to the ContentProtection instance to compare against.
     * @return `true` if the ContentProtection are considered equal, false otherwise.
     */
    bool operator==(const ContentProtection &other) const;

    // @robustness
    bool hasRobustness() const { return m_robustness.has_value(); };
    const std::optional<std::string> &robustness() const { return m_robustness; };
    ContentProtection &robustness(const std::nullopt_t&) { m_robustness.reset(); return *this; };
    ContentProtection &robustness(const std::string &val) { m_robustness = val; return *this; };
    ContentProtection &robustness(std::string &&val) { m_robustness = std::move(val); return *this; };
    ContentProtection &robustness(const std::optional<std::string> &val) { m_robustness = val; return *this; };
    ContentProtection &robustness(std::optional<std::string> &&val) { m_robustness = std::move(val); return *this; };
    
    // @refId
    bool hasRefId() const { return m_refId.has_value(); };
    const std::optional<std::string> &refId() const { return m_refId; };
    ContentProtection &refId(const std::nullopt_t&) { m_refId.reset(); return *this; };
    ContentProtection &refId(const std::string &val) { m_refId = val; return *this; };
    ContentProtection &refId(std::string &&val) { m_refId = std::move(val); return *this; };
    ContentProtection &refId(const std::optional<std::string> &val) { m_refId = val; return *this; };
    ContentProtection &refId(std::optional<std::string> &&val) { m_refId = std::move(val); return *this; };

    // @ref
    bool hasRef() const { return m_ref.has_value(); };
    const std::optional<std::string> &ref() const { return m_ref; };
    ContentProtection &ref(const std::nullopt_t&) { m_ref.reset(); return *this; };
    ContentProtection &ref(const std::string &val) { m_ref = val; return *this; };
    ContentProtection &ref(std::string &&val) { m_ref = std::move(val); return *this; };
    ContentProtection &ref(const std::optional<std::string> &val) { m_ref = val; return *this; };
    ContentProtection &ref(std::optional<std::string> &&val) { m_ref = std::move(val); return *this; };

///@cond PROTECTED
protected:
    friend class MPD;
    friend class Period;
    friend class RepresentationBase;

     /**
     * XML constructor (internal use only)
     *
     * Create a new ContentProtection from an XML %ContentProtection element.
     *
     * @param node The libxml++ Node for the %ContentProtection element.
     */
    ContentProtection(xmlpp::Node &node);

    /**
     * Set a libxml++ Element attributes and children for XML output
     *
     * This will set all relevant attributes and child elements from the settings of this ContentProtection.
     *
     * @param element The libxml++ Element to populate.
     */
    void setXMLElement(xmlpp::Element &element) const;
///@endcond PROTECTED

private:
    std::optional<std::string> m_robustness; // string with no whitespace
    std::optional<std::string> m_refId;      // xs:ID type
    std::optional<std::string> m_ref;        // xs:IDREF type
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_CONTENT_PROTECTION_HH_*/
