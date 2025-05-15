#ifndef _BBC_PARSE_DASH_MPD_STREAM_OPERATIONS_HH_
#define _BBC_PARSE_DASH_MPD_STREAM_OPERATIONS_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: conversion functions
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

//#include "libmpd++/macros.hh"

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::optional<T> &ot)
{
    if (ot) {
        os << ot.value();
    } else {
        os << "[no value]";
    }
    return os;
}

//LIBMPDPP_NAMESPACE_BEGIN


//LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /* _BBC_PARSE_DASH_MPD_STREAM_OPERATIONS_HH_ */
