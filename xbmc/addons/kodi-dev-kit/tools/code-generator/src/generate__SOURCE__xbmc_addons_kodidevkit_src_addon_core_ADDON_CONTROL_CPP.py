from code_generator import *
from .sub_file_hdl import *
from .helpers import *

import glob
import os
import re

def generate__SOURCE__xbmc_addons_kodidevkit_src_addon_core_ADDON_CONTROL_CPP(force):
  """
  This function generate automatic code inside xbmc/addons/kodi-dev-kit/src/addon/core/addon_control.cpp.

  Currently it set there the include to all interface parts and his class creations.
  Work code insde must be edited by hand.
  """
  base_dir = 'xbmc/addons/kodi-dev-kit/src/addon/'
  file_name = base_dir + 'core/addon_control.cpp'
  print('  - Generate auto code in ' + file_name)

  scan_dir = kodi_dir + base_dir + 'api/**/'

  CONTROL_SOURCE_INCLUDE = ''
  CONTROL_CLASS_CREATION = ''
  CONTROL_CLASS_CREATION_2 = ''
  for dir in sorted(glob.glob(scan_dir, recursive=True)):
    # Scan for used headers
    src_parts = sorted(glob.glob(dir + '*.h', recursive=False))
    for src_part in src_parts:
      src_part = src_part.replace(kodi_dir + base_dir, '')
      CONTROL_SOURCE_INCLUDE += '#include "' + src_part + '"\n'

      f = open(src_part.replace('api/', '../../include/kodi/c-api/'), 'r')
      data = f.read()
      f.close()
      if not 'ATTR_APIENTRYP' in data:
        continue

      src_part = src_part.replace('api/', '').replace('-', '').replace('/', '_').replace('.', '_')
      CONTROL_CLASS_CREATION += '  CHdl_kodi_{}* {} = new CHdl_kodi_{}(m_ifc);\n'.format(src_part, src_part, src_part)
      CONTROL_CLASS_CREATION += '  m_handlers[funcGroup_{}] = {};\n'.format(src_part, src_part)

      CONTROL_CLASS_CREATION_2 += '    {}->InitDirect(&m_ifc->direct->to_addon.{});\n'.format(src_part, src_part, src_part)

  source_file = ''
  f = open(kodi_dir + file_name, 'r')
  data = f.read()
  start_1 = False
  start_2 = False
  for line in data.splitlines():
    # Header include
    if '---AUTO_GEN_PARSE<CONTROL_SOURCE_INCLUDE>---' in line:
      source_file += line + '\n'
      source_file += '/* Code below autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator.py */\n'
      start_1 = True
    elif '---AUTO_GEN_PARSE<CONTROL_SOURCE_INCLUDE_END>---' in line:
      source_file += CONTROL_SOURCE_INCLUDE
      source_file += line + '\n'
      start_1 = False
    elif start_1:
      continue
    # Class creation
    elif '---AUTO_GEN_PARSE<CONTROL_CLASS_CREATION>---' in line:
      source_file += line + '\n'
      source_file += '  /* Code below autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator.py */\n'
      start_2 = True
    elif '---AUTO_GEN_PARSE<CONTROL_CLASS_CREATION_END>---' in line:
      source_file += CONTROL_CLASS_CREATION
      source_file += '\n'
      source_file += '  if (m_ifc->direct != nullptr)\n'
      source_file += '  {\n'
      source_file += CONTROL_CLASS_CREATION_2
      source_file += '  }\n'
      source_file += line + '\n'
      start_2 = False
    elif start_2:
      continue
    else:
      source_file += line + '\n'

  if start_1 or start_2:
    print('ERROR: Needed CONTROL_CLASS_CREATION_END or CONTROL_SOURCE_INCLUDE_END not present in' + file_name)
    exit()

  if source_file != data or force:
    print('    - Updating ' + file_name)
    f = open(kodi_dir + file_name, "w")
    f.write(source_file)
    f.close()
