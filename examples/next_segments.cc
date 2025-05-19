/***********************************************************************************
 * DASH MPD parsing library in C++: Example program to dump next available segments
 ***********************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
#include <limits.h>
#include <stdlib.h>

#include <chrono>
#include <fstream>
#include <iostream>

#include "libmpd++/libmpd++.hh"

LIBMPDPP_NAMESPACE_USING_ALL;

int main(int argc, char *argv[])
{
    std::ifstream ifs(argv[1]);
    char *abs_path = realpath(argv[1], nullptr);
    MPD mpd(ifs, std::string("file://") + abs_path);
    mpd.selectAllRepresentations();
    free(abs_path);

    std::cout << "MPD is live?: " << (mpd.isLive()?"true":"false") << std::endl
              << "Contains " << mpd.selectedRepresentations().size() << " Representations" << std::endl
              << std::endl << std::endl;

    SegmentAvailability::time_type now = std::chrono::system_clock::now();

    auto init_segments = mpd.selectedInitializationSegments(now);
    if (!init_segments.empty()) {
        std::cout << "There are " << init_segments.size() << " unique initialization segments:" << std::endl;
        for (auto &sa : init_segments) {
            std::cout << "     " << sa << std::endl;
        }
	std::cout << std::endl;
    }

    auto media_segments = mpd.selectedSegmentAvailability(now);
    std::cout << "There are " << media_segments.size() << " media segments available on or after " << now << ":" << std::endl;
    for (auto &sa : media_segments) {
        std::cout << "     " << sa << std::endl;
    }

    return 0;
}
