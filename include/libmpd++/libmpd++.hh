#ifndef _BBC_PARSE_DASH_MPD_LIBMPDPP_HH_
#define _BBC_PARSE_DASH_MPD_LIBMPDPP_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: main meson build file
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */

/** @mainpage libmpd++ - DASH MPD parsing and manipulation library in C++
 *
 * @section intro Introduction
 *
 * This library provides a model of the %MPD file structure as documented in ISO 23009-1:2022. The model hierarchy starts with the
 * @ref com::bbc::libmpdpp::MPD "MPD" class, which can also parse and output the @ref com::bbc::libmpdpp::MPD "MPD" as %MPD XML
 * using the libxml++ library.
 *
 * @section mainBuilding Building the library
 *
 * Please see the @subpage gettingStarted "Getting started" page for details.
 *
 * @section mainArchitecture Library design
 *
 * Please see the @subpage overview "Overview" page for a high level look at how this library is intended to work.
 *
 * @section mainUsing Using the library
 *
 * Please see the codeExamples "Example code" page for details examples of using this library
 *
 */

/** @page gettingStarted libmpd++ - Getting started
 *
 * @section prerequisites Installing the prerequisites
 *
 * Mandatory prerequisites:
 * - GCC C++ compiler v14 or higher
 * - glibmm 2.4
 * - libxml++ 3.0 or higher
 * - meson
 * - ninja
 * 
 * Optional dependencies:
 * - doxygen
 * - Graphviz
 * - plantuml
 *
 * The library makes use of the libxml++ library to provide C++ libxml2 bindings.
 * You can also optionally install Doxygen and the GNU Graphviz tools to recreate this documentation.
 *
 * For RedHat based distributions the following command will install the mandatory dependencies:
 * @code{.sh}
 * sudo dnf install libxml++30-devel glibmm2.4-devel meson ninja-build gcc-c++ git
 * @endcode
 *
 * ...and the optional dependencies:
 * @code{.sh}
 * sudo dnf install graphviz doxygen plantuml java-latest-openjdk-headless ccache
 * @endcode
 *
 * For Debian based distributions the following command will install the mandatory dependencies:
 * @code{.sh}
 * sudo apt install libxml++-dev glibmm-dev meson ninja gcc gcc-c++ git
 * @endcode
 *
 * ...and the optional dependencies:
 * @code{.sh}
 * sudo apt install graphviz doxygen plantuml openjdk-headless ccache
 * @endcode
 *
 * @section download Downloading the source
 *
 * The source can be fetched from the main repository at https://github.com/bbc/libmpdpp.
 *
 * For example:
 * @code{.sh}
 * git clone https://github.com/bbc/libmpdpp.git ~/libmpdpp
 * @endcode
 *
 * @section building Building the library
 *
 * Building the library is handled by the meson and ninja build tools.
 *
 * @code{.sh}
 * cd ~/libmpdpp
 * meson setup build
 * ninja -C build
 * @endcode
 *
 * @section installing Installing the library
 *
 * Installation of the library is handled by meson.
 *
 * @code{.sh}
 * cd ~/libmpdpp
 * sudo meson install -C build --no-rebuild
 * @endcode
 *
 * @section buildingDocs Building the library documentation
 *
 * This documentation can be built using ninja if the optional doxygen and graphviz tools have been installed (see the
 * @ref prerequisites "Installing the prerequisites" section for details).
 *
 * @code{.sh}
 * cd ~/libmpdpp
 * ninja -C build docs
 * @endcode
 */

/** @page overview libmpd++ - Library high level overview
 *
 * @section overviewIntro Introduction
 *
 * The libmpd++ library is a C++ class library for parsing, manipulating, querying and outputting %DASH %MPD %XML documents.
 *
 * The library can parse an %MPD from a variety of sources such as a memory block or file. The library also allows the creation of
 * new %MPDs in a programatic fashion.
 *
 * The %MPD is modelled by a set of classes which can contain the various values held by an %MPD in within its hierarchy of
 * elements. This allows the %MPD to be programatically traversed and modified easily in a C++ program.
 *
 * The top level of the %MPD model is an @ref com::bbc::libmpdpp::MPD "MPD" object.
 *
 * The %MPD model can also be queried to find a set of next available media segments or the initialization segments for the
 * %Representations in the %MPD. This is done by marking Representations in the model as selected and then using the query methods
 * on the @ref com::bbc::libmpdpp::MPD "MPD" object to obtain a list of next segments or the availability of the initialization
 * segments.
 *
 * The %MPD that is modelled can be output as a %DASH %MPD %XML string. This can be in either a compact form for communication, or
 * as a formatted (pretty) form with extra whitespace for readability.
 *
 * @section overviewQuerying Using the query methods
 *
 * As mentioned above, the %MPD model provides methods at various levels to mark
 * @ref com::bbc::libmpdpp::Representation "Representations" as selected. There are also some query methods on the
 * @ref com::bbc::libmpdpp::MPD "MPD" object,
 * @ref com::bbc::libmpdpp::MPD::selectedSegmentAvailability() "selectedSegmentAvailability()" and
 * @ref com::bbc::libmpdpp::MPD::selectedInitializationSegments() "selectedInitializationSegments()", which will use the selected
 * %Representations of the current @ref com::bbc::libmpdpp::Period "Period" to perform a query for the next available media
 * segments or the initialization segments respectively.
 *
 * Individual @ref com::bbc::libmpdpp::Representation "Representations" can be selected by using the selection methods in the
 * @ref com::bbc::libmpdpp::AdaptationSet "AdaptationSet" class. These methods allow individual %Representations to be selected or
 * deselected, or the selection to be changed to a new %Representation. This is useful for playback where only the segments from the
 * currently selected %Representations, in the %AdaptationSets which are in use, are required.
 *
 * For broadcast/multicast operations, where all %Representations are needed at the same time, the
 * @ref com::bbc::libmpdpp::MPD "MPD", @ref com::bbc::libmpdpp::Period "Period" and
 * @ref com::bbc::libmpdpp::AdaptationSet "AdaptationSet" classes all provide selectAllRepresentations() and
 * deselectAllRepresentations() methods to select all the @ref com::bbc::libmpdpp::Representation "Representations" below that
 * object's level.
 *
 * Both media segment and initialization segment queries will return a set of
 * @ref com::bbc::libmpdpp::SegmentAvailability "SegmentAvailability" objects which contain the resolved segment URL and
 * availability start time for that segment. They may also contain an availability end time, if one is provided in the %MPD. For
 * media segments, the segment duration is also returned to assist in scheduling of the next query.
 */

/** @page codeExamples libmpd++ - Example library usage
 *
 * To read an MPD from a named file:
 * @code{.cpp}
 * #include <string>
 * #include <libmpd++/libmpd++.hh>
 *
 * LIBMPDPP_NAMESPACE_USING_ALL;
 *
 *   .
 *   .
 *   .
 *
 * {
 *     const std::string filename("/path/to/manifest.mpd");
 *     const std::string original_url("https://example.com/media/manifest.mpd");
 *     MPD mpd(filename, original_url);
 * }
 * @endcode
 *
 * To read from an input stream:
 * @code{.cpp}
 * #include <fstream>
 * #include <string>
 * #include <libmpd++/libmpd++.hh>
 *
 * LIBMPDPP_NAMESPACE_USING_ALL;
 *
 *   .
 *   .
 *   .
 *
 * {
 *     std::ifstream infile("/path/to/manifest.mpd");
 *     const std::string original_url("https://example.com/media/manifest.mpd");
 *     MPD mpd(infile, original_url);
 * }
 * @endcode
 *
 * To read from memory:
 * @code{.cpp}
 * #include <string>
 * #include <vector>
 * #include <libmpd++/libmpd++.hh>
 *
 * LIBMPDPP_NAMESPACE_USING_ALL;
 *
 *   .
 *   .
 *   .
 *
 * {
 *     std::string mpd_text("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
 *         "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\" type=\"dynamic\" minBufferTime=\"PT10S\"\n"
 *         "     profiles=\"urn:dvb:dash:profile:dvb-dash:isoff-ext-live:2014\">\n"
 *         "  <Period id=\"1\" start=\"PT0S\"/>\n"
 *         "</MPD>\n"
 *     );
 *     std::vector<char> mpd_vec(mpd_text.data(), mpd_text.data() + mpd_text.size());
 *     const std::string original_url("https://example.com/media/manifest.mpd");
 *     MPD mpd(mpd_vec, original_url);
 * }
 * @endcode
 *
 * To create a new MPD:
 * @code{.cpp}
 * #include <chrono>
 * #include <libmpd++/libmpd++.hh>
 *
 * using namespace std::literals::chrono_literals;
 * LIBMPDPP_NAMESPACE_USING_ALL;
 *
 *  .
 *  .
 *  .
 *
 * {
 *     MPD mpd(3840ms, "urn:dvb:dash:profile:dvb-dash:2014", Period());
 * }
 * @endcode
 *
 * Output to a stream (compact XML form):
 * @code{.cpp}
 * #include <chrono>
 * #include <libmpd++/libmpd++.hh>
 *
 * using namespace std::literals::chrono_literals;
 * LIBMPDPP_NAMESPACE_USING_ALL;
 *
 *  .
 *  .
 *  .
 *
 * {
 *     MPD mpd(3840ms, "urn:dvb:dash:profile:dvb-dash:2014", Period());
 *
 *     std::cout << MPD::compact << mpd;
 * }
 * @endcode
 *
 * Output to a stream (pretty XML form):
 * @code{.cpp}
 * #include <chrono>
 * #include <libmpd++/libmpd++.hh>
 *
 * using namespace std::literals::chrono_literals;
 * LIBMPDPP_NAMESPACE_USING_ALL;
 *
 *  .
 *  .
 *  .
 *
 * {
 *     MPD mpd(3840ms, "urn:dvb:dash:profile:dvb-dash:2014", Period());
 *
 *     std::cout << mpd << std::endl; // pretty output is the default if MPD::compact has not previsouly been used in the stream
 *
 *     // if MPD::compact has been used previously then MPD::pretty can be use to change back to pretty format
 *     std::cout << MPD::compact;
 *     std::cout << MPD::pretty << mpd << std::endl;
 * }
 * @endcode
 */

#include "macros.hh"

#include "AdaptationSet.hh"
#include "BaseURL.hh"
#include "Codecs.hh"
#include "ContentComponent.hh"
#include "ContentPopularityRate.hh"
#include "ContentProtection.hh"
#include "Descriptor.hh"
#include "EventStream.hh"
#include "exceptions.hh"
#include "ExtendedBandwidth.hh"
#include "FailoverContent.hh"
#include "FrameRate.hh"
#include "InitializationSet.hh"
#include "Label.hh"
#include "LeapSecondInformation.hh"
#include "Metrics.hh"
#include "MPD.hh"
#include "MultipleSegmentBase.hh"
#include "PatchLocation.hh"
#include "Period.hh"
#include "Preselection.hh"
#include "ProducerReferenceTime.hh"
#include "ProgramInformation.hh"
#include "RandomAccess.hh"
#include "Ratio.hh"
#include "RepresentationBase.hh"
#include "Representation.hh"
#include "Resync.hh"
#include "RFC6838ContentType.hh"
#include "SAP.hh"
#include "SegmentAvailability.hh"
#include "SegmentBase.hh"
#include "SegmentList.hh"
#include "SegmentTemplate.hh"
#include "SegmentTimeline.hh"
#include "SegmentURL.hh"
#include "ServiceDescription.hh"
#include "SingleRFC7233Range.hh"
#include "SubRepresentation.hh"
#include "Subset.hh"
#include "Switching.hh"
#include "UIntVWithID.hh"
#include "URI.hh"
#include "URL.hh"
#include "XLink.hh"

/** @namespace com::bbc::libmpdpp
 * The libmpd++ namespace
 *
 * This namespace contains all main classes that are part of libmpd++.
 */

#endif /* _BBC_PARSE_DASH_MPD_LIBMPDPP_HH_ */
