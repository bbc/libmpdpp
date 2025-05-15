##############################################################################
# DASH MPD parsing library in C++: regression testing meson build file
##############################################################################
# Copyright: (C) 2025 British Broadcasting Corporation
# Author(s): David Waring <david.waring2@bbc.co.uk>
# License: LGPLv3
#
# For full license terms please see the LICENSE file distributed with this
# library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
#

test_live_mpd = files('test_live.mpd')

segment_templates_exe = executable('segment_templates', 'segment_templates.cc', dependencies: [libmpdpp_dep], install: false)
test('segment_templates', segment_templates_exe)

segment_selection_exe = executable('segment_selection', 'segment_selection.cc', dependencies: [libmpdpp_dep], install: false)
test('segment_selection', segment_selection_exe, args: [test_live_mpd])
