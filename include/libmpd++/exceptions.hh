#ifndef _BBC_PARSE_DASH_MPD_EXCEPTIONS_HH_
#define _BBC_PARSE_DASH_MPD_EXCEPTIONS_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: common library exceptions
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <exception>

#include "macros.hh"

LIBMPDPP_NAMESPACE_BEGIN

/** ParseError exception class
 * @headerfile libmpd++/exceptions.hh <libmpd++/exceptions.hh>
 *
 * This type is thrown when the library encounters an error in parsing the %MPD input.
 */
class LIBMPDPP_PUBLIC_API ParseError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
    using std::runtime_error::operator=;

    virtual ~ParseError() = default;
};

/** InvalidMPD exception class
 * @headerfile libmpd++/exceptions.hh <libmpd++/exceptions.hh>
 *
 * This type is thrown when the MPD or child objects contain values inconsistent with a correct %MPD. This could include out of
 * range values or missing child objects.
 */
class LIBMPDPP_PUBLIC_API InvalidMPD : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
    using std::runtime_error::operator=;

    virtual ~InvalidMPD() = default;
};

/** RangeError exception class
 * @headerfile libmpd++/exceptions.hh <libmpd++/exceptions.hh>
 *
 * This type is thrown when a value is out of range or an array index outside the array bounds is requested from the library.
 */
class LIBMPDPP_PUBLIC_API RangeError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
    using std::runtime_error::operator=;

    virtual ~RangeError() = default;
};

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_EXCEPTIONS_HH_*/
