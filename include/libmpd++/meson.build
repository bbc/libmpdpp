##############################################################################
# DASH MPD parsing library in C++: include directory meson build file
##############################################################################
# Copyright: (C) 2025 British Broadcasting Corporation
# Author(s): David Waring <david.waring2@bbc.co.uk>
# License: LGPL?
#
# For full license terms please see the LICENSE file distributed with this
# library or refer to: [URL here].
#

libparsempd_public_hdrs = files('''
Accessibility.hh
AdaptationSet.hh
BaseURL.hh
ContentComponent.hh
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
Rating.hh
RatioType.hh
Role.hh
Representation.hh
RFC6838ContentType.hh
Sap.hh
SegmentBase.hh
SegmentList.hh
SegmentTemplate.hh
SegmentTimeline.hh
SegmentType.hh
SegmentURL.hh
ServiceDescription.hh
SingleRFC7233Range.hh
Subset.hh
SubRepresentation.hh
UIntVWithID.hh
Viewpoint.hh
URI.hh
URL.hh
XLink.hh
'''.split())

install_headers(libparsempd_public_hdrs, subdir: 'libmpd++')
