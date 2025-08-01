/***********************************************************************************
 * DASH MPD parsing library in C++: Example program to read and write an MPD
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

#include "libmpd++/MPD.hh"

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
              << std::endl
              << "Pretty print MPD:" << std::endl
              << mpd << std::endl
              << "Compact form:" << std::endl
              << MPD::compact << mpd << std::endl;

    return 0;
}
