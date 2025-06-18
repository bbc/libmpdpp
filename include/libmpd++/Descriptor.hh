#ifndef _BBC_PARSE_DASH_MPD_DESCRIPTOR_HH_
#define _BBC_PARSE_DASH_MPD_DESCRIPTOR_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: Descriptor class
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

class MPD;
class Period;

/** Descriptor class
 * @headerfile libmpd++/Descriptor.hh <libmpd++/Descriptor.hh>
 *
 * This is a container for %DASH %MPD %XML elements which use the %DescriptorType from the %XML schema. This type is defined in
 * ISO 23009-1:2022 Clause 5.8.3.
 */
class LIBMPDPP_PUBLIC_API Descriptor {
public:

    /** Default constructor (deleted).
     *
     * This constructor is explicitly deleted to prevent instantiation of a
     * Descriptor object without the necessary initialization parameters.
     * Users must utilize one of the provided parameterized constructors.
     */
    Descriptor() = delete;

    /**@{*/
    /**
     * @brief Constructs a new Descriptor object.
     *
     * This constructor initializes a Descriptor with a required scheme URI and
     * optional value and identifier strings. The optional parameters default to
     * std::nullopt when no value is provided.
     *
     * @param scheme_id The URI specifying the scheme identifier for this descriptor.
     * @param value An optional string value associated with the descriptor. Defaults to std::nullopt.
     * @param id An optional identifier string that further describes the descriptor. Defaults to std::nullopt.
     */
    Descriptor(const URI &scheme_id, const std::optional<std::string> &value = std::nullopt, const std::optional<std::string> &id = std::nullopt)
        :m_schemeIdUri(scheme_id)
        ,m_value(value)
    {};
    Descriptor(URI &&scheme_id, const std::optional<std::string> &value = std::nullopt, const std::optional<std::string> &id = std::nullopt)
        :m_schemeIdUri(scheme_id)
        ,m_value(value)
    {};
    /**@}*/


    /**
     * Copy constructor
     *
     * Creates a new Descriptor object which is a copy of @p other.
     *
     * @param other The Descriptor object to copy.
     */
    Descriptor(const Descriptor &other)
        :m_schemeIdUri(other.m_schemeIdUri)
        ,m_value(other.m_value)
        ,m_id(other.m_id)
    {};

    /**
     * Move constructor
     *
     * Creates a new Descriptor object which transfers the resources from @p other.
     *
     * @param other The ContentPopularityRate object to move.
     */
    Descriptor(Descriptor &&other)
        :m_schemeIdUri(std::move(other.m_schemeIdUri))
        ,m_value(std::move(other.m_value))
        ,m_id(std::move(other.m_id))
    {};

    /**
     * Destructor
     */
    virtual ~Descriptor() {};

     /**
     * Copy operator
     *
     * Copies the values from @p other into this Descriptor object.
     *
     * @param other The Descriptor object to copy.
     * @return This Descriptor object.
     */
    Descriptor &operator=(const Descriptor &other) {
        m_schemeIdUri = other.m_schemeIdUri;
        m_value = other.m_value;
        m_id = other.m_id;
        return *this;
    };

    /**
     * Move operator
     *
     * Transfers the resources from @p other into this Descriptor object.
     *
     * @param other The Descriptor object to move.
     * @return This Descriptor object.
     */
    Descriptor &operator=(Descriptor &&other) {
        m_schemeIdUri = std::move(other.m_schemeIdUri);
        m_value = std::move(other.m_value);
        m_id = std::move(other.m_id);
        return *this;
    };

    /** Comparison operator
     *
     * @param other The other Descriptor to compare to this one.
     * @return `true` if the value of @a other is the same as the value of this Descriptor, otherwise `false`.
     */
    bool operator==(const Descriptor &other) const {
        if (m_schemeIdUri != other.m_schemeIdUri) return false;
        if (m_value.has_value() != other.m_value.has_value()) return false;
        if (m_value.has_value() && m_value.value() != other.m_value.value()) return false;
        if (m_id.has_value() != other.m_id.has_value()) return false;
        if (m_id.has_value() && m_id.value() != other.m_id.value()) return false;
        return true;
    }

    /**@{*/
     /** Get the schemeId URI attribute value
     *
     * @return The schemeId URI attribute value.
     */
    const URI &schemeId() const { return m_schemeIdUri; };
    URI &schemeId() { return m_schemeIdUri; };
    /**@}*/

    /**@{*/
    /** Set the @@schemeIdUri attribute value
     *
     * @param scheme_id The value to set for the @@schemeIdUri attribute.
     * @return This Descriptor.
     */
    Descriptor &schemeId(const URI &scheme_id) { m_schemeIdUri = scheme_id; return *this; };
    Descriptor &schemeId(URI &&scheme_id) { m_schemeIdUri = std::move(scheme_id); return *this; };
    /**@}*/

    /** Check if the value attribute is set
     *
     * @return `true` if the value attribute has been set.
     */
    bool has_value() const { return m_value.has_value(); };

    /**@{*/
     /** Get the optional id attribute value
     *
     * @return The optional id attribute value.
     */
    const std::optional<std::string> &value() const { return m_value; };
    std::optional<std::string> &value() { return m_value; };
    /**@}*/

     /** Unset the value attribute
     *
     * @return This Descriptor.
     */
    Descriptor &value(const std::nullopt_t&) { m_value.reset(); return *this; };
 
    /**@{*/  
    /** Set the @@value attribute value
     *
     * @param val The value to set for the @@value attribute.
     * @return This Descriptor.
     */
    Descriptor &value(const std::string &val) { m_value = val; return *this; };
    Descriptor &value(std::string &&val) { m_value = std::move(val); return *this; };
    /**@}*/

    /** Check if the id attribute is set
     *
     * @return `true` if the id attribute has been set.
     */
    bool has_id() const { return m_id.has_value(); };
    
    
     /**@{*/
     /** Get the optional id attribute value
     *
     * @return The optional id attribute value.
     */
    const std::optional<std::string> &id() const { return m_id; };
    std::optional<std::string> &id() { return m_id; };
    /**@}*/
    
    /** Unset the id attribute value
     *
     * @return This Descriptor.
     */
    Descriptor &id(const std::nullopt_t&) { m_id.reset(); return *this; };

    /**@{*/
    /** Set the @@id attribute value
     *
     * @param id The value to set for the @@id attribute.
     * @return This Descriptor.
     */
    Descriptor &id(const std::string &id) { m_id = id; return *this; };
    Descriptor &id(std::string &&id) { m_id = std::move(id); return *this; };
    /**@}*/

///@cond PROTECTED
protected:
    friend class AdaptationSet;
    friend class MPD;
    friend class Period;
    friend class Representation;
    friend class RepresentationBase;

    /**
     * XML constructor (internal use only)
     *
     * Create a new Descriptor from an XML %Descriptor element.
     *
     * @param node The libxml++ Node for the %Descriptor element.
     */
    Descriptor(xmlpp::Node &node);

     /**
     * Set a libxml++ Element attributes and children for XML output
     *
     * This will set all relevant attributes and child elements from the settings of this Descriptor.
     *
     * @param element The libxml++ Element to populate.
     */
    void setXMLElement(xmlpp::Element &element) const;
///@endcond PROTECTED

private:
    // Attributes
    URI m_schemeIdUri;                  //< @@schemeIdUri attribute value
    std::optional<std::string> m_value; //< The optional @@value attribute value
    std::optional<std::string> m_id;    //< The optional @@id attribute value 
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_DESCRIPTOR_HH_*/
