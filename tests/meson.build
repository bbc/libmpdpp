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


segment_templates_exe = executable('segment_templates', 'segment_templates.cc', dependencies: [libparsempd_dep], install: false)
test('segment_templates', segment_templates_exe)
