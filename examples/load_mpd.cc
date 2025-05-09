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
    free(abs_path);

    std::cout << "MPD is live?: " << (mpd.isLive()?"true":"false") << std::endl
              << "Pretty print MPD:" << std::endl
              << mpd << std::endl
              << "Compact form:" << std::endl
              << MPD::compact << mpd << std::endl;

    return 0;
}
