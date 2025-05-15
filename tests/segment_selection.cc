#include <limits.h>
#include <stdlib.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>

#include "libmpd++/libmpd++.hh"

using namespace std::literals::chrono_literals;
LIBMPDPP_NAMESPACE_USING_ALL;

MPD *g_mpd = nullptr;
std::filesystem::path g_test_live_mpd;

bool test_initialise()
{
    
    std::ifstream in_file(g_test_live_mpd);
    g_mpd = new MPD(in_file, std::string("file:") + g_test_live_mpd.string());

    g_mpd->selectAllRepresentations();

    auto selected_reps = g_mpd->selectedRepresentations();
    if (selected_reps.size() != 5) {
        std::cerr << "expected 5 representations, got " << selected_reps.size() << "." << std::endl;
        return false;
    }

    return true;
}

bool test_initialization_segments()
{
    bool ret = true;
    if (!g_mpd) return false;
    auto init_list = g_mpd->selectedInitializationSegments();
    if (init_list.size() != 5) {
        std::cerr << "expected 5 initialization segments, got " << init_list.size() << "." << std::endl;
        for (auto &sa : init_list) {
            std::cerr << "    " << sa.availabilityStartTime() << ": " << sa.segmentURL() << std::endl;
        }
        return false;
    }

    for (const auto &sa : init_list) {
        if (sa.availabilityStartTime() != g_mpd->availabilityStartTime().value()) {
            std::cerr << "expected availabilityStartTime to equal MPD@availabilityStartTime (" << g_mpd->availabilityStartTime().value() << "), got " << sa.availabilityStartTime() << "." << std::endl;
            ret = false;
        }

        if (sa.segmentURL() != "https://example.com/cmaf-uk/x=3/i=urn:example:live_channel/v=pv14/b=5070016/segment.init" &&
            sa.segmentURL() != "https://example.com/cmaf-uk/x=3/i=urn:example:live_channel/v=pv10/b=1604032/segment.init" &&
            sa.segmentURL() != "https://example.com/cmaf-uk/x=3/i=urn:example:live_channel/v=pv8/b=827008/segment.init" &&
            sa.segmentURL() != "https://example.com/cmaf-uk/x=3/i=urn:example:live_channel/v=pv13/b=2812032/segment.init" &&
            sa.segmentURL() != "https://example.com/cmaf-uk/x=3/i=urn:example:live_channel/a=pa4/b=128000/segment.init") {
            std::cerr << "expected URL of \"https://example.com/cmaf-uk/x=3/i=urn:example:live_channel/v=pv{8,10,13,14}/b={827008,1604032,2812032,5070016}/segment.init\" or \"https://example.com/cmaf-uk/x=3/i=urn:example:live_channel/a=pa4/b=128000/segment.init\", got \"" << sa.segmentURL() << "\"." << std::endl;
            ret = false;
        }

        if (sa.availabilityStartTime() != SegmentAvailability::time_type(std::chrono::sys_days(std::chrono::January/1/1970) + 1min)) {
            std::cerr << "expected availabilityStartTime of 1970-01-01 00:01:00.000000000, got " << sa.availabilityStartTime() << "." << std::endl;
            ret = false;
        }

        if (sa.hasAvailabilityEndTime()) {
            std::cerr << "expected no availabilityEndTime, got " << sa.availabilityEndTime().value() << "." << std::endl;
            ret = false;
        }

        if (sa.segmentDuration() != 0s) {
            std::cerr << "expected media duration of 0s, got " << sa.segmentDuration() << "." << std::endl;
            ret = false;
        }

        if (!ret) break;
    }

    return ret;
}

bool test_media_segments()
{
    bool ret = true;
    if (!g_mpd) return false;

    auto now = std::chrono::system_clock::now();
    auto media_list = g_mpd->selectedSegmentAvailability(now);
    if (media_list.size() != 5) {
        std::cerr << "expected 5 media segments, got " << media_list.size() << "." << std::endl;
        for (auto &sa : media_list) {
            std::cerr << "    " << sa.availabilityStartTime() << ": " << sa.segmentURL() << std::endl;
        }
        return false;
    }

    std::cerr << "Next media segments on or after: " << now << std::endl;
    for (auto &sa : media_list) {
        std::cerr << "    " << sa << std::endl;
    }

    return ret;
}

bool test_finalise()
{
    if (g_mpd) delete g_mpd;
    return true;
}

int main(int argc, char *argv[])
{
    int result = 0;
    
    g_test_live_mpd = argv[1];

    static const std::vector< std::pair< std::string, std::function<bool()> > > tests = {
        { "Initialise", test_initialise },
        { "Check initialization segment querying", test_initialization_segments },
        { "Check media segment querying", test_media_segments },
        { "Finish", test_finalise }
    };

    for (const auto &test : tests) {
        std::cout << test.first << ": ";
        try {
            if ((test.second)()) {
                std::cout << "passed";
            } else {
                result = 1;
                std::cout << "failed";
            }
        } catch (const std::exception &ex) {
            result = 1;
            std::cout << "failed (exception): " << ex.what();
        }
        std::cout << std::endl;
    }

    return result;
}

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
