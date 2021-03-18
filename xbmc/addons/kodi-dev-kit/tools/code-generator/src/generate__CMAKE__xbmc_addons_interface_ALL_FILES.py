from code_generator import *
from .sub_file_hdl import *
from .helpers import *

import glob
import os
import re

def generate__CMAKE__xbmc_addons_interface_ALL_FILES(force):
  """
  This function generate the "CMakeLists.txt" in xbmc/addons/interface
  and sub dirs by scan of available files
  """
  print('  - Generate CMakeLists.txt files in xbmc/addons/interface dirs')

  scan_dir = kodi_dir + 'xbmc/addons/interface/**/'

  found = False
  dirs = glob.glob(scan_dir, recursive=True)
  for dir in dirs:
    source_dir = dir.replace(kodi_dir, '')
    print('    - Check for ' + source_dir + 'CMakeLists.txt')

    # Scan for *.cpp
    source_entry = []
    src_parts = sorted(glob.glob(dir + '*.cpp', recursive=False))
    for src_part in src_parts:
      with open(src_part) as search:
        for line in search:
          line = line.rstrip()  # remove '\n' at end of line
          m = re.search('^\/\*---AUTO_GEN_PARSE<\$\$(.*):(.*)>---\*\/', line)
          if m:
            if m.group(1) == 'CORE_SYSTEM_NAME':
              for entry in m.group(2).split(","):
                source_entry.append('$<$<STREQUAL:${CORE_SYSTEM_NAME},' + entry + '>:' + src_part.replace(dir, '') + '>')
              found = True
              break
      if not found:
        source_entry.append(src_part.replace(dir, ''))
      found = False

    cmake_src_text = 'set(SOURCES\n'
    for entry in source_entry:
      cmake_src_text += '  ' + entry + '\n'
    cmake_src_text += ')'

    # Scan for *.h
    header_entry = []
    src_parts = sorted(glob.glob(dir + '*.h', recursive=False))
    for src_part in src_parts:
      with open(src_part) as search:
        for line in search:
          line = line.rstrip()  # remove '\n' at end of line
          m = re.search('^\/\*---AUTO_GEN_PARSE<\$\$(.*):(.*)>---\*\/', line)
          if m:
            if m.group(1) == 'CORE_SYSTEM_NAME':
              for entry in m.group(2).split(","):
                header_entry.append('$<$<STREQUAL:${CORE_SYSTEM_NAME},' + entry + '>:' + src_part.replace(dir, '') + '>')
              found = True
              break
      if not found:
        header_entry.append(src_part.replace(dir, ''))
      found = False

    cmake_hdr_text = 'set(HEADERS\n'
    for entry in header_entry:
      cmake_hdr_text += '  ' + entry + '\n'
    cmake_hdr_text += ')'

    # Generate cmake sub part name
    cmake_part = source_dir.lstrip('xbmc/').replace('/', '_').rstrip('_')

    # Make final CMakeLists.txt
    cmake_file = '# Auto generated CMakeLists.txt.\n'\
                 '# See xbmc/addons/kodi-dev-kit/tools/code-generator.py.\n'\
                 '\n'\
                 + cmake_src_text + '\n' +\
                 '\n'\
                 + cmake_hdr_text + '\n'\
                 '\n'\
                 'if(NOT ENABLE_STATIC_LIBS OR SOURCES)\n'\
                 '  core_add_library(' + cmake_part + ')\n'\
                 'endif()\n'

    file = dir + 'CMakeLists.txt'
    if not os.path.isfile(file) or cmake_file != open(file).read() or force:
      print('      - Generated new ' + source_dir + 'CMakeLists.txt')
      f = open(file, "w")
      f.write(cmake_file)
      f.close()
