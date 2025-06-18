#ifndef _BBC_PARSE_DASH_MPD_CONVERSIONS_HH_
#define _BBC_PARSE_DASH_MPD_CONVERSIONS_HH_
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
#include <chrono>
#include <list>
#include <regex>
#include <sstream>
#include <string>

#include "libmpd++/macros.hh"

LIBMPDPP_NAMESPACE_BEGIN

template <class Rep, class Period>
std::string format_duration(const std::chrono::duration<Rep,Period> &durn)
{
    auto total_ms = std::chrono::duration_cast<std::chrono::milliseconds>(durn).count();
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
    if ((hours == 0 && mins == 0) || secs != 0 || ms != 0) {
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
    Durn ret = Durn();
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

template<typename T>
std::list<T> str_to_list(const std::string &attr_val, char sep = ',')
{
    std::list<T> ret;
    std::string::size_type start_pos = 0;
    for (auto pos = attr_val.find_first_of(sep); pos != std::string::npos; start_pos = pos+1, pos = attr_val.find_first_of(sep, start_pos)) {
        auto val = attr_val.substr(start_pos, pos - start_pos);
        if (!val.empty()) {
            ret.push_back(T(val));
        }
    }
    auto val = attr_val.substr(start_pos);
    if (!val.empty()) {
        ret.push_back(T(val));
    }
    return ret;
}

template<>
std::list<unsigned int> str_to_list<unsigned int>(const std::string &attr_val, char sep);

LIBMPDPP_NAMESPACE_END

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /* _BBC_PARSE_DASH_MPD_CONVERSIONS_HH_ */
