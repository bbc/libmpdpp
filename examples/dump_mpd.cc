#include <chrono>
#include <iostream>
#include "libmpd++/MPD.hh"

using namespace std::literals::chrono_literals;

LIBPARSEMPD_NAMESPACE_USING_ALL;

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
