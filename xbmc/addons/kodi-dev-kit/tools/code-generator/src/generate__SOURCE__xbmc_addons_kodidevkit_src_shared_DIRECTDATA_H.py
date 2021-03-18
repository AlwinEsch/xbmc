from code_generator import *
from .sub_file_hdl import *
from .helpers import *

import glob
import os

def generate__SOURCE__xbmc_addons_kodidevkit_src_shared_DIRECTDATA_H(options):
  search_dir = '{}xbmc/addons/kodi-dev-kit/include/kodi/c-api/'.format(kodi_dir)
  target_dir = '{}xbmc/addons/kodi-dev-kit/src/shared/api/'.format(kodi_dir)
  scan_dir = search_dir + '/**/'

  code_include = []
  code_struct_to_kodi = []
  code_struct_to_addon = []
  dirs = sorted(glob.glob(scan_dir, recursive=True))
  for dir in dirs:
    source_dir = dir.replace(search_dir, '')
    src_parts = sorted(glob.glob(dir + '*.h', recursive=True))
    for src_part in src_parts:
      if not FileContainsInterfaceAPICalls(src_part):
        continue

      header_group_id = TranslatePathToCUsableString(src_part, search_dir)
      code_struct_to_kodi.append('  directFuncToKodi_{} {};'.format(header_group_id, header_group_id))
      code_struct_to_addon.append('  directFuncToAddon_{} {};'.format(header_group_id, header_group_id))
      code_include.append('#include "{}"'.format(src_part.replace(search_dir, 'src/shared/api/')))

  if len(code_struct_to_kodi) == 0:
    code_struct_to_kodi.append('  int dummyValue;')
  if len(code_struct_to_addon) == 0:
    code_struct_to_addon.append('  int dummyValue;')

  file_text = header_file_copyright + """\

/*
 * This header is used to allow direct api interface between addon and Kodi.
 * Becomes used in case the addon is loaded as dynamic lib and without use of
 * shared memory.
 *
 * This can be in case if higher performance needed or OS not support
 * independent apps (e.g. iOS/tvos)
 *
 * The structure defined here is only used between library and Kodi not used
 * inside addon itself, with this are changes here not critical.
 */

#pragma once

""" + '\n'.join(code_include) + """
#include "src/shared/api/processor.h"

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

struct DirectAddonIfcToKodi
{
""" + '\n'.join(code_struct_to_kodi) + """
};

struct DirectAddonIfcToAddon
{
""" + '\n'.join(code_struct_to_addon) + """
  directFuncToAddon_processor_h processor_h;
};

struct DirectAddonIfc
{
  DirectAddonIfcToKodi to_kodi;
  DirectAddonIfcToAddon to_addon;
};

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
"""

  # Make now the creation and copy of file
  target_file = '../../../../../xbmc/addons/kodi-dev-kit/src/shared/DirectData.h'
  temp_file = target_file.replace('../../../../../xbmc/addons', './tmp')
  os.makedirs(os.path.dirname(temp_file), exist_ok=True)

  f = open(temp_file, "w")
  f.write(file_text)
  f.close()
  os.system('clang-format -style=file -i ' + temp_file)

  if options.force \
     or not os.path.isfile(target_file) \
     or not filecmp.cmp(target_file, temp_file):
    print('  - Updating ' + target_file)
    os.makedirs(os.path.dirname(target_file), exist_ok=True)
    shutil.copyfile(temp_file, target_file)
