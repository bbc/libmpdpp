##############################################################################
# DASH MPD parsing library in C++: main meson build file
##############################################################################
# Copyright: (C) 2025 British Broadcasting Corporation
# Author(s): David Waring <david.waring2@bbc.co.uk>
# License: LGPLv3
#
# For full license terms please see the LICENSE file distributed with this
# library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
#

doxygen_exe = find_program('doxygen', required: false)

if doxygen_exe.found()
  dot_exe = find_program('dot', required: false)
  strip_paths = []
  libmpdpp_public_hdrs_split = libmpdpp_public_hdrs[0].full_path().split('/')
  i = libmpdpp_public_hdrs_split.length() - 1
  foreach p : libmpdpp_public_hdrs_split
    i = i - 1
    if i <= 0
      break
    endif
    strip_paths += p
  endforeach
  strip_paths = '/'.join(strip_paths)
  src_files = ''
  src_files_sep = ''
  foreach f : libmpdpp_public_hdrs
    src_files += src_files_sep + f.full_path()
    src_files_sep = ' '
  endforeach
  doxyfile_config = configuration_data({
    'SOURCE_FILES' : src_files,
    'STRIP_PATHS' : strip_paths,
    'OUTPUT_DIR' : meson.current_build_dir(),
    'HAVE_DOT' : 'NO',
    'DOT_PATH' : ''
  })
  if dot_exe.found()
    doxyfile_config.set('HAVE_DOT', 'YES')
    doxyfile_config.set('DOT_PATH', dot_exe.full_path())
  endif
  doxygen_configuration = configure_file(input: 'Doxyfile.in', output: 'Doxyfile', configuration: doxyfile_config)
  run_target('docs', command: [doxygen_exe, doxygen_configuration])
endif

