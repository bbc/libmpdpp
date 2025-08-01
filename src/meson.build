##############################################################################
# DASH MPD parsing library in C++: library meson build file
##############################################################################
# Copyright: (C) 2025 British Broadcasting Corporation
# Author(s): David Waring <david.waring2@bbc.co.uk>
# License: LGPLv3
#
# For full license terms please see the LICENSE file distributed with this
# library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
#

pkg = import('pkgconfig')

cpp = meson.get_compiler('cpp')
if cpp.has_function_attribute('visibility:default')
    add_project_arguments('-DHAVE_VISIBILITY=1', language: ['cpp'])
endif

libxml_dep = dependency('libxml++-3.0', required: false)
if not libxml_dep.found()
    libxml_dep = dependency('libxml++-4.0', required: false)
    if not libxml_dep.found()
        libxml_dep = dependency('libxml++-5.0', fallback: ['libxmlplusplus', 'xmlxx_own_dep'])
        if not libxml_dep.found()
            error('This build requires libxml++ version 3.0, 4.0 or 5.0')
        endif
    endif
endif
glibmm_dep = dependency('glibmm-2.4', required: true)

libmpdpp_private_inc_dir = include_directories('.')
libmpdpp_srcs = files('''
AdaptationSet.cc
BaseURL.cc
Codecs.cc
constants.hh
ContentComponent.cc
ContentPopularityRate.cc
ContentProtection.cc
conversions.cc
conversions.hh
DecomposedURL.cc
DecomposedURL.hh
Descriptor.cc
EventStream.cc
ExtendedBandwidth.cc
FailoverContent.cc
FrameRate.cc
InitializationSet.cc
Label.cc
LeapSecondInformation.cc
Metrics.cc
MPD.cc
MultipleSegmentBase.cc
PatchLocation.cc
Period.cc
Preselection.cc
ProducerReferenceTime.cc
ProgramInformation.cc
RandomAccess.cc
Ratio.cc
Representation.cc
RepresentationBase.cc
Resync.cc
RFC6838ContentType.cc
SAP.cc
SegmentAvailability.cc
SegmentBase.cc
SegmentList.cc
SegmentTemplate.cc
SegmentTimeline.cc
SegmentURL.cc
ServiceDescription.cc
SingleRFC7233Range.cc
stream_ops.hh
SubRepresentation.cc
Subset.cc
Switching.cc
UIntVWithID.cc
URI.cc
URL.cc
XLink.cc
'''.split())

project_name = meson.project_name()
project_version = meson.project_version()
project_version_num_and_flag = project_version.split('-')
project_version_num = project_version_num_and_flag[0]
if project_version_num_and_flag.length() > 1
    project_version_flag = project_version_num_and_flag[1]
else
    project_version_flag = ''
endif
project_version_arr = project_version_num.split('.')
project_version_major = project_version_arr[0].to_int()
project_version_minor = project_version_arr[1].to_int()
project_version_micro = project_version_arr[2].to_int()

project_config = configuration_data()
project_config.set_quoted('PROJECT_VERSION_STR', project_version, description: 'Project version full string')
project_config.set('PROJECT_VERSION_MAJOR', project_version_major, description: 'Project major version integer')
project_config.set('PROJECT_VERSION_MINOR', project_version_minor, description: 'Project minor version integer')
project_config.set('PROJECT_VERSION_MICRO', project_version_micro, description: 'Project micro version integer')
project_config.set_quoted('PROJECT_NAME', project_name, description: 'Project name')
project_config.set_quoted('PROJECT_VERSION_FLAG', project_version_flag, description: 'Project version instance flag')

libmpdpp_config_h = configure_file(configuration: project_config, output: 'config.hh', macro_name: '_LIBMPDPP_CONFIG_HH_', output_format: 'c', install: false)

libmpdpp_so_ver = project_version_arr[0]
libmpdpp_ver = project_version_num
libmpdpp = both_libraries('mpd++', libmpdpp_srcs + [libmpdpp_config_h],
               version: libmpdpp_ver,
               soversion: libmpdpp_so_ver,
               dependencies: [libxml_dep, glibmm_dep],
               cpp_args: ['-DBUILD_LIBMPDPP'],
               install: true,
               include_directories: [libmpdpp_inc_dir, libmpdpp_private_inc_dir],
               gnu_symbol_visibility: 'hidden',
)

pkg.generate(libmpdpp)

libmpdpp_dep = declare_dependency(dependencies: [libxml_dep, glibmm_dep], link_with: [libmpdpp], include_directories: [libmpdpp_inc_dir])
