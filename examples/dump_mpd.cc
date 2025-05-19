/***********************************************************************************
 * DASH MPD parsing library in C++: Example program to create and write an MPD
 ***********************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <chrono>
#include <iostream>
#include "libmpd++/MPD.hh"

using namespace std::literals::chrono_literals;

LIBMPDPP_NAMESPACE_USING_ALL;

int main(int argc, char *argv[])
{
    MPD mpd(3840ms, "urn:dash:profile", Period());

    mpd.availabilityStartTime(std::chrono::system_clock::now());

    std::cout << "Pretty print MPD:" << std::endl
              << mpd << std::endl
              << "Compact form:" << std::endl
              << MPD::compact << mpd << std::endl;

    return 0;
}
