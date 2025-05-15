##############################################################################
# DASH MPD parsing library in C++: example programs meson build file
##############################################################################
# Copyright: (C) 2025 British Broadcasting Corporation
# Author(s): David Waring <david.waring2@bbc.co.uk>
# License: LGPLv3
#
# For full license terms please see the LICENSE file distributed with this
# library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
#

dump_mpd_srcs = files('''
dump_mpd.cc
'''.split())

load_mpd_srcs = files('''
load_mpd.cc
'''.split())

dump_mpd_exe = executable('dump_mpd', dump_mpd_srcs, dependencies: [libmpdpp_dep], install: true, install_dir: get_option('datadir') / meson.project_name() + '-' + meson.project_version() / 'bin')

load_mpd_exe = executable('load_mpd', load_mpd_srcs, dependencies: [libmpdpp_dep], install: true, install_dir: get_option('datadir') / meson.project_name() + '-' + meson.project_version() / 'bin')
