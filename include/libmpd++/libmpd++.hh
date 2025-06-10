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
 * \ref com::bbc::libmpdpp::MPD "MPD" class, which can also parse and output the \ref com::bbc::libmpdpp::MPD "MPD" as %MPD XML
 * using the libxml++ library.
 *
 * @section mainBuilding Building the library
 *
 * Please see the @subpage gettingStarted "Getting started" page for details.
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

/** @page codeExamples libmpd++ - Example library usage
 *
 * Blah blah blah
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
#include "SegmentType.hh"
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
