#ifndef _BBC_PARSE_DASH_MPD_EXCEPTIONS_HH_
#define _BBC_PARSE_DASH_MPD_EXCEPTIONS_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: common library exceptions
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <exception>

LIBPARSEMPD_NAMESPACE_BEGIN

class LIBPARSEMPD_PUBLIC_API ParseError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
    using std::runtime_error::operator=;

    virtual ~ParseError() = default;
};

LIBPARSEMPD_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_EXCEPTIONS_HH_*/
