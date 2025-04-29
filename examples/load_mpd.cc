#include <chrono>
#include <fstream>
#include <iostream>
#include "libmpd++/MPD.hh"

LIBPARSEMPD_NAMESPACE_USING_ALL;

int main(int argc, char *argv[])
{
    std::ifstream ifs(argv[1]);
    MPD mpd(ifs);

    std::cout << "Pretty print MPD:" << std::endl
              << mpd << std::endl
              << "Compact form:" << std::endl
              << MPD::compact << mpd << std::endl;

    return 0;
}
