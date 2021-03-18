from code_generator import *
from .sub_file_hdl import *
from .helpers import *

import glob
import os
import re

def generate__CMAKE_TREEDATA__common_ADDON_DEV_KIT_TXT(force):
  """
  This function generate the "cmake/treedata/common/addon_dev_kit.txt"
  by scan of related directories to use for addon interface build.
  """
  gen_file = 'cmake/treedata/common/addon_dev_kit.txt'

  print('  - Check for ' + gen_file)

  scan_dir = kodi_dir + 'xbmc/addons/kodi-dev-kit/include/kodi/**/CMakeLists.txt'

  cmakelists = glob.glob(scan_dir, recursive=True)
  parts = '# Auto generated ' + gen_file + '.\n'\
          '# See xbmc/addons/kodi-dev-kit/tools/code-generator.py.\n\n'
  for entry in cmakelists:
    cmake_dir = entry.replace(kodi_dir, '').replace('/CMakeLists.txt', '')
    with open(entry) as search:
      for line in search:
        line = line.rstrip()  # remove '\n' at end of line
        m = re.search('^ *core_add_devkit_header\((.*)\)', line)
        if m:
          parts += cmake_dir + ' addons_kodi-dev-kit_include_' + m.group(1) + '\n'
          break
  parts += 'xbmc/addons/kodi-dev-kit/src/shared devkit_shared # Hardcoded entry, edit script for change!\n'
  parts += 'xbmc/addons/kodi-dev-kit/src/addon kodidevkit # Hardcoded entry, edit script for change!\n'
  file = kodi_dir + gen_file
  if not os.path.isfile(file) or parts != open(file).read() or force:
    print('    - Generated new ' + gen_file)
    f = open(file, "w")
    f.write(parts)
    f.close()
