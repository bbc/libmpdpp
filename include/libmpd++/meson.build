##############################################################################
# DASH MPD parsing library in C++: include directory meson build file
##############################################################################
# Copyright: (C) 2025 British Broadcasting Corporation
# Author(s): David Waring <david.waring2@bbc.co.uk>
# License: LGPLv3
#
# For full license terms please see the LICENSE file distributed with this
# library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
#

libmpdpp_public_hdrs = files('''
libmpd++.hh
AdaptationSet.hh
BaseURL.hh
Codecs.hh
ContentComponent.hh
ContentPopularityRate.hh
ContentProtection.hh
Descriptor.hh
EventStream.hh
exceptions.hh
ExtendedBandwidth.hh
FailoverContent.hh
FrameRate.hh
InitializationSet.hh
Label.hh
LeapSecondInformation.hh
macros.hh
Metrics.hh
MPD.hh
MultipleSegmentBase.hh
PatchLocation.hh
Period.hh
Preselection.hh
ProgramInformation.hh
RandomAccess.hh
Ratio.hh
Representation.hh
RepresentationBase.hh
Resync.hh
RFC6838ContentType.hh
SAP.hh
SegmentAvailability.hh
SegmentBase.hh
SegmentList.hh
SegmentTemplate.hh
SegmentTimeline.hh
SegmentURL.hh
ServiceDescription.hh
SingleRFC7233Range.hh
Subset.hh
SubRepresentation.hh
Switching.hh
UIntVWithID.hh
URI.hh
URL.hh
XLink.hh
'''.split())

install_headers(libmpdpp_public_hdrs, subdir: 'libmpd++')
