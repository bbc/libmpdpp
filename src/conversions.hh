#ifndef _BBC_PARSE_DASH_MPD_CONVERSIONS_HH_
#define _BBC_PARSE_DASH_MPD_CONVERSIONS_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: conversion functions
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPL?
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: [URL here].
 */
#include <chrono>
#include <regex>
#include <string>

#include "libmpd++/macros.hh"

LIBPARSEMPD_NAMESPACE_BEGIN

template <class Rep, class Period>
std::string format_duration(const std::chrono::duration<Rep,Period> &durn)
{   
    auto total_ms = std::chrono::milliseconds(durn).count();
    auto ms = total_ms % 1000;
    total_ms /= 1000;
    auto secs = total_ms % 60;
    total_ms /= 60;
    auto mins = total_ms % 60;
    total_ms /= 60;
    auto hours = total_ms;

    std::ostringstream oss;

    oss << "PT";
    if (hours != 0) {
        oss << hours << "H";
    }
    if (mins != 0) {
        oss << mins << "M";
    }
    if (secs != 0 || ms != 0) {
        oss << secs;
        if (ms != 0) {
            oss << "." << std::setw(3) << ms;
        }
        oss << "S";
    }
    return oss.str();
}

template<class Durn>
Durn str_to_duration(const std::string &str)
{
    Durn ret;
    static const std::regex durn_parse_regex("^P(?!$)(?:(\\d+)Y)?(?:(\\d+)M)?(?:(\\d+)W)?(?:(\\d+)D)?(?:T(?=\\d+(?:[HM]|(?:\\.\\d+)?S))(?:(\\d+)H)?(?:(\\d+)M)?(?:(\\d+(\\.\\d+)?)S)?)?$");
    std::smatch matches;
    if (std::regex_match(str, matches, durn_parse_regex)) {
        if (matches[1].matched) {
            ret += std::chrono::years(std::stol(matches[1]));
        }
        if (matches[2].matched) {
            ret += std::chrono::months(std::stol(matches[2]));
        }
        if (matches[3].matched) {
            ret += std::chrono::weeks(std::stol(matches[3]));
        }
        if (matches[4].matched) {
            ret += std::chrono::days(std::stol(matches[4]));
        }
        if (matches[5].matched) {
            ret += std::chrono::hours(std::stol(matches[5]));
        }
        if (matches[6].matched) {
            ret += std::chrono::minutes(std::stol(matches[6]));
        }
        if (matches[7].matched) {
            ret += std::chrono::milliseconds(static_cast<long int>(std::stod(matches[7])*1000));
        }
    }
    return ret;
}

LIBPARSEMPD_NAMESPACE_END
    
/* vim:ts=8:sts=4:sw=4:expandtab:
 */ 
#endif /* _BBC_PARSE_DASH_MPD_CONVERSIONS_HH_ */
