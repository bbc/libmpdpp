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
#include <list>
#include <string>

#include "libmpd++/macros.hh"

#include "conversions.hh"

LIBMPDPP_NAMESPACE_BEGIN

template<>
std::list<unsigned int> str_to_list<unsigned int>(const std::string &attr_val, char sep)
{
    std::list<unsigned int> ret;
    std::string::size_type start_pos = 0;
    for (auto pos = attr_val.find_first_of(sep); pos != std::string::npos; start_pos = pos+1, pos = attr_val.find_first_of(sep, start_pos)) {
        auto val = attr_val.substr(start_pos, pos - start_pos);
        if (!val.empty()) {
            ret.push_back(static_cast<unsigned int>(std::stoul(val)));
        }
    }
    auto val = attr_val.substr(start_pos);
    if (!val.empty()) {
        ret.push_back(static_cast<unsigned int>(std::stoul(val)));
    }
    return ret;
}

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
