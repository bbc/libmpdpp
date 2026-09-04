/*****************************************************************************
 * DASH MPD parsing library in C++: SegmentTimeline segment selection tests
 *****************************************************************************
 * Copyright: (C) 2026 British Broadcasting Corporation
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */
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
std::filesystem::path g_test_mpd;

// The presentation under test: availabilityStartTime 2026-01-01T00:00:00Z, twenty 5 s segments
// addressed by SegmentTimeline, @timeShiftBufferDepth 120 s, no MPD@availabilityEndTime.
static const auto k_ast = std::chrono::system_clock::time_point(
        std::chrono::sys_days{std::chrono::January/1/2026}.time_since_epoch());

static MPD::time_type at(int seconds) { return k_ast + std::chrono::seconds(seconds); }

bool test_initialise()
{
    std::ifstream in_file(g_test_mpd);
    g_mpd = new MPD(in_file, std::string("file:") + g_test_mpd.string());
    g_mpd->selectAllRepresentations();
    return g_mpd->selectedRepresentations().size() == 1;
}

/* A query must not be answered with a segment that became available before it.
 *
 * MPD::selectedSegmentAvailability() is documented as returning "the next segments available on or
 * after query_time". Segment availability start time for a dynamic presentation is defined in
 * ISO/IEC 23009-1 clause 5.3.9.5, third paragraph, as the sum of MPD@availabilityStartTime, the
 * PeriodStart of the containing Period, the MPD start time of the segment and its MPD duration.
 * Segment 20 here has an MPD start time of 95 s and a duration of 5 s, so it becomes available
 * 100 s after availabilityStartTime and is the answer to any query in (95 s, 100 s].
 */
bool test_timeline_query_returns_a_later_segment()
{
    bool ret = true;
    auto list = g_mpd->selectedSegmentAvailability(at(95));
    if (list.size() != 1) {
        std::cerr << "expected 1 segment, got " << list.size() << ". ";
        return false;
    }
    const auto &sa = list.front();
    if (sa.availabilityStartTime() < at(95)) {
        std::cerr << "returned a segment that became available at " << sa.availabilityStartTime()
                  << ", before the query time. ";
        ret = false;
    }
    if (sa.availabilityStartTime() != at(100)) {
        std::cerr << "expected availability start 100 s after availabilityStartTime, got "
                  << sa.availabilityStartTime() << ". ";
        ret = false;
    }
    return ret;
}

/* A segment of a dynamic presentation has an availability end time even when the MPD carries no
 * MPD@availabilityEndTime.
 *
 * ISO/IEC 23009-1 clause 5.3.9.5, fourth paragraph, defines it as the segment's availability start
 * time plus its MPD duration plus @timeShiftBufferDepth for the Representation. Here that is
 * 100 s + 5 s + 120 s = 225 s after availabilityStartTime.
 */
bool test_timeline_availability_end_time()
{
    bool ret = true;
    auto list = g_mpd->selectedSegmentAvailability(at(95));
    if (list.empty()) return false;
    const auto &sa = list.front();
    if (!sa.hasAvailabilityEndTime()) {
        std::cerr << "no availability end time, though the MPD declares @timeShiftBufferDepth. ";
        return false;
    }
    if (sa.availabilityEndTime().value() != at(225)) {
        std::cerr << "expected availability end 225 s after availabilityStartTime, got "
                  << sa.availabilityEndTime().value() << ". ";
        ret = false;
    }
    return ret;
}

bool test_finalise()
{
    delete g_mpd;
    g_mpd = nullptr;
    return true;
}

int main(int argc, char *argv[])
{
    int result = 0;

    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " <test MPD>" << std::endl;
        return 2;
    }
    g_test_mpd = argv[1];

    static const std::vector< std::pair< std::string, std::function<bool()> > > tests = {
        { "Initialise", test_initialise },
        { "SegmentTimeline query returns a segment available on or after the query time",
          test_timeline_query_returns_a_later_segment },
        { "SegmentTimeline segment has an availability end time from @timeShiftBufferDepth",
          test_timeline_availability_end_time },
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
