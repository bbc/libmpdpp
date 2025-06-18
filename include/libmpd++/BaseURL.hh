#ifndef _BBC_PARSE_DASH_MPD_BASE_URL_HH_
#define _BBC_PARSE_DASH_MPD_BASE_URL_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: BaseURL class
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
class Representation;
class AdaptationSet;

/** BaseURL class
 * @headerfile libmpd++/BaseURL.hh <libmpd++/BaseURL.hh>
 *
 * This is a container for %BaseURL element values and attributes as given in the %DASH %MPD %XML schema found in ISO 23009-1:2022
 * Clause 5.6.3.
 */
class LIBMPDPP_PUBLIC_API BaseURL : public URI {
public:
    using duration_type = std::chrono::microseconds; ///< The type used to represent durations in this class

    /** Default constructor
     * 
     * Create an empty BaseURL element.
     */ 
    BaseURL();

    /**@{*/
    /** Construct with %URL
     * 
     * Make a new BaseURL with @p url as the %URL string.
     *
     * @param url The %URL to set this BaseURL value to.
     */
    BaseURL(const std::string &url);
    BaseURL(std::string &&url);
    /**@}*/

    /** Copy constructor
     *
     * Create a new BaseURL which is a copy of @p other.
     *
     * @param other The other BaseURL to copy.
     */
    BaseURL(const BaseURL &other);

    /** Move constructor
     *
     * Create a new BaseURL by moving the values and resources from the @p other BaseURL.
     *
     * @param other The other BaseURL to transfer the values and resources from.
     */
    BaseURL(BaseURL &&other);

    /** Destructor
     */
    virtual ~BaseURL() {};

    /**@{*/
    /** Assignment operator
     *
     * Set this BaseURL to the same value as @p other.
     *
     * @param other The other BaseURL to copy/move into this BaseURL.
     * @return This BaseURL.
     */
    BaseURL &operator=(const BaseURL &other);
    BaseURL &operator=(BaseURL &&other);
    /**@}*/

    /** Comparison operator
     * 
     * @param other The other BaseURL to comnpare to this one.
     * @return `true` if the value of @p other is the same as the value of this BaseURL, otherwise `false`.
     */
    bool operator==(const BaseURL &other) const;

    /**@{*/
    /** Get the %URL value
     * 
     * @return the %URL value for this BaseURL.
     */
    const URI &url() const { return static_cast<const URI&>(*this); };
    URI &url() { return static_cast<URI&>(*this); };
    /**@}*/

    /**@{*/
    /** Set the %URL value
     *
     * @param _url The %URL to set this BaseURL to.
     * @return This BaseURL.
     */
    BaseURL &url(const URI &_url) { URI::operator=(_url); return *this; };
    BaseURL &url(URI &&_url) { URI::operator=(std::move(_url)); return *this; };
    /**@}*/

    /** Create a new BaseURL with the resolved version of this URL
     *
     * Create a copy of this BaseURL with the url resolved using the provided @p base_urls.
     * If this BaseURL is absolute then the result will just be a copy of this one.
     * If this BaseURL is relative then the @p base_urls list will be used to generate an absolute (if possible) %URL by combining
     * the relative %URL from this BaseURL with one of the absolute URLs from @p base_urls.
     *
     * @param base_urls The list of BaseURL to use as base URL when resolving this URL.
     * @return A copy of this BaseURL resolved using @p base_urls.
     */
    BaseURL resolveURL(const std::list<BaseURL> &base_urls) const;

    // @serviceLocation

    /** Check if the serviceLocation attribute is set
     *
     * @return `true` if the serviceLocation attribute has been set.
     */
    bool hasServiceLocation() const { return m_serviceLocation.has_value(); };

    /** Get the optional serviceLocation attribute value
     *
     * @return The optional serviceLocation attribute value.
     */
    const std::optional<std::string> &serviceLocation() const { return m_serviceLocation; };

    /** Unset the serviceLocation attribute value
     *
     * @return This BaseURL.
     */
    BaseURL &serviceLocation(const std::nullopt_t&) { m_serviceLocation.reset(); return *this; };

    /**@{*/
    /** Set the @@serviceLocation attribute value
     *
     * @param val The value to set for the @@serviceLocation attribute.
     * @return This BaseURL.
     */
    BaseURL &serviceLocation(const std::string &val) { m_serviceLocation = val; return *this; };
    BaseURL &serviceLocation(std::string &&val) { m_serviceLocation = std::move(val); return *this; };
    /**@}*/

    // @byteRange

    /** Check if the @@byteRange attribute has been set
     *
     * @return `true` if the @@byteRange attribute has been set.
     */
    bool hasByteRange() const { return m_byteRange.has_value(); };

    /** Get the optional @@byteRange attribute value
     *
     * @return The optional @@byteRange attribute value.
     */
    const std::optional<std::string> &byteRange() const { return m_byteRange; };

    /** Unset the @@byteRange attribute value
     *
     * @return This BaseURL.
     */
    BaseURL &byteRange(const std::nullopt_t&) { m_byteRange.reset(); return *this; };

    /**@{*/
    /** Set the optional @@byteRange attribute value
     *
     * @param val The value of the byte range to set as the @@byteRange attribute.
     * @return This BaseURL.
     */
    BaseURL &byteRange(const std::string &val) { m_byteRange = val; return *this; };
    BaseURL &byteRange(std::string &&val) { m_byteRange = std::move(val); return *this; };
    /**@}*/

    // @pvailabilityTimeOffset

    /** Check if the @@pvailabilityTimeOffset attribute has been set
     *
     * @return `true` if the @@pvailabilityTimeOffset attribute has been set, otherwise `false`.
     */
    bool hasAvailabilityTimeOffset() const { return m_availabilityTimeOffset.has_value(); };

    /** Get the optional @@pvailabilityTimeOffset attribute value
     *
     * @return The optional availability time offset.
     */
    const std::optional<double> &availabilityTimeOffset() const { return m_availabilityTimeOffset; };

    /** Unset the @@pvailabilityTimeOffset attribute value
     *
     * @return This BaseURL.
     */
    BaseURL &availabilityTimeOffset(const std::nullopt_t&) { m_availabilityTimeOffset.reset(); return *this; };

    /** Set the @@pvailabilityTimeOffset attribute value
     *
     * @param val The value to set as the @@pvailabilityTimeOffset attribute value.
     * @return This BaseURL.
     */
    BaseURL &availabilityTimeOffset(double val) { m_availabilityTimeOffset = val; return *this; };

    // @pvailabilityTimeComplete

    /** Check if the @@pvailabilityTimeComplete attribute has been set
     *
     * @return `true` if the @@pvailabilityTimeComplete attribute has been set.
     */
    bool hasAvailabilityTimeComplete() const { return m_availabilityTimeComplete.has_value(); };

    /** Get the optional @@pvailabilityTimeComplete attribute value
     *
     * @return the Optional @@pvailabilityTimeComplete attribute flag.
     */
    const std::optional<bool> &availabilityTimeComplete() const { return m_availabilityTimeComplete; };

    /** Unset the @@pvailabilityTimeComplete attribute value
     *
     * @return This BaseURL.
     */
    BaseURL &availabilityTimeComplete(const std::nullopt_t&) { m_availabilityTimeComplete.reset(); return *this; };

    /** Set the @@pvailabilityTimeComplete attribute value
     *
     * @param val The value for the @@pvailabilityTimeComplete attribute.
     * @return This BaseURL.
     */
    BaseURL &availabilityTimeComplete(bool val) { m_availabilityTimeComplete = val; return *this; };

    // @timeShiftBufferDepth

    /** Check if the @@timeShiftBufferDepth attribute value has been set
     *
     * @return `true` if the @@timeShiftBufferDepth attribute value has been set.
     */
    bool hasTimeShiftBufferDepth() const { return m_timeShiftBufferDepth.has_value(); };

    /** Get the optional @@timeShiftBufferDepth attribute value
     *
     * @return The optional value for the @@timeShiftBufferDepth attribute.
     */
    const std::optional<duration_type> &timeShiftBufferDepth() const { return m_timeShiftBufferDepth; };

    /** Unset the @@timeShiftBufferDepth attribute value
     *
     * @return This BaseURL.
     */
    BaseURL &timeShiftBufferDepth(const std::nullopt_t&) { m_timeShiftBufferDepth.reset(); return *this; };

    /**@{*/
    /** Set the @@timeShiftBufferDepth attribute value
     *
     * @param val The value to set for the @@timeShiftBufferDepth attribute.
     * @return This BaseURL.
     */
    BaseURL &timeShiftBufferDepth(const duration_type &val) { m_timeShiftBufferDepth = val; return *this; };
    BaseURL &timeShiftBufferDepth(duration_type &&val) { m_timeShiftBufferDepth = std::move(val); return *this; };
    /**@}*/

    // @rangeAccess

    /** Get the @@rangeAccess attribute value
     *
     * @return The @@rangeAccess attribute value.
     */
    bool rangeAccess() const { return m_rangeAccess; };

    /** Set the @@rangeAccess attribute value
     *
     * Sets the @@rangeAccess attribute value. Setting this to the default value of `false` will cause this field to be omitted
     * from XML output.
     *
     * @param val The value to set the @@rangeAccess attribute to.
     * @return This BaseURL.
     */
    BaseURL &rangeAccess(bool val) { m_rangeAccess = val; return *this; };

///@cond PROTECTED
protected:
    friend class MPD;
    friend class Period;
    friend class Representation;
    friend class AdaptationSet;

    /** Constructor from libxml++ Node
     *
     * Extract a new BaseURL from the %BaseURL element node passed in @p node.
     *
     * @param node The libxml++ Node to read the BaseURL element attributes and value from.
     */
    BaseURL(xmlpp::Node &node);

    /** Set a libxml++ Node from this BaseURL
     *
     * Set the attributes and value for a %BaseURL element from this BaseURL.
     *
     * @param elem The Element to fill in the attributes and value for.
     */
    void setXMLElement(xmlpp::Element &elem) const;
///@endcond PROTECTED

private:
    // BaseURL attributes ISO 23009-1:2022 Clause 5.6.3
    std::optional<std::string>   m_serviceLocation;          ///< The optional @@serviceLocation attribute value
    std::optional<std::string>   m_byteRange;                ///< The optional @@byteRange attribute value
    std::optional<double>        m_availabilityTimeOffset;   ///< The optional @@pvailabilityTimeOffset attribute value
    std::optional<bool>          m_availabilityTimeComplete; ///< The optional @@pvailabilityTimeComplete attribute flag value
    std::optional<duration_type> m_timeShiftBufferDepth;     ///< The optional @@timeShiftBufferDepth attribute value
    bool                         m_rangeAccess;              ///< The @@rangeAccess attribute value (default: false)
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_BASE_URL_HH_*/
