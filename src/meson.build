##############################################################################
# DASH MPD parsing library in C++: library meson build file
##############################################################################
# Copyright: (C) 2025 British Broadcasting Corporation
# Author(s): David Waring <david.waring2@bbc.co.uk>
# License: LGPL?
#
# For full license terms please see the LICENSE file distributed with this
# library or refer to: [URL here].
#

pkg = import('pkgconfig')

cpp = meson.get_compiler('cpp')
if cpp.has_function_attribute('visibility:default')
    add_project_arguments('-DHAVE_VISIBILITY=1', language: ['cpp'])
endif

libxml_dep = dependency('libxml++-3.0', required: true)

libparsempd_private_inc_dir = include_directories('.')
libparsempd_srcs = files('''
AdaptationSet.cc
BaseURL.cc
ContentProtection.cc
Descriptor.cc
InitializationSet.cc
LeapSecondInformation.cc
Metrics.cc
MPD.cc
PatchLocation.cc
Period.cc
ProgramInformation.cc
Representation.cc
ServiceDescription.cc
UIntVWithID.cc
URI.cc
URL.cc
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

libparsempd_config_h = configure_file(configuration: project_config, output: 'config.hh', macro_name: '_LIBPARSEMPD_CONFIG_HH_', output_format: 'c', install: false)

libparsempd = both_libraries('mpd++', libparsempd_srcs + [libparsempd_config_h],
               dependencies: [libxml_dep],
               cpp_args: ['-DBUILD_LIBPARSEMPD'],
               install: true,
               include_directories: [libparsempd_inc_dir, libparsempd_private_inc_dir],
               gnu_symbol_visibility: 'hidden',
)

pkg.generate(libparsempd)

libparsempd_dep = declare_dependency(dependencies: [libxml_dep], link_with: [libparsempd], include_directories: [libparsempd_inc_dir])
