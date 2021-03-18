from code_generator import *
from .sub_file_hdl import *
from .helpers import *

import glob
import os

def generate__SOURCE__xbmc_addons_kodidevkit_src_shared_INSTANCES_H(force):
  """
  This function generate automatic code inside xbmc/addons/kodi-dev-kit/src/shared/Instances.h
  """
  print('  - Generate file xbmc/addons/kodi-dev-kit/src/shared/Instances.h')

  target_file = kodi_dir + 'xbmc/addons/kodi-dev-kit/src/shared/Instances.h'
  if not os.path.exists(target_file):
    print('FATAL: File ' + target_file + 'not exists!')
    exit()

  USED_INCLUDES = ''
  USED_UNIONS  = '    uint32_t dummy;\n'

  search_dir = kodi_dir + 'xbmc/addons/kodi-dev-kit/src/shared/api/'
  scan_dir = search_dir + '**/'

  dirs = sorted(glob.glob(scan_dir, recursive=True))
  for dir in dirs:
    src_parts = sorted(glob.glob(dir + '*.h', recursive=False))
    for src_part in src_parts:

      with open(src_part, 'r') as f:
        file_text = f.read()
        f.close()

      found = ''
      for line in file_text.splitlines():
        if 'union KODI_' in line:
          found = line

      if not found:
        continue

      USED_INCLUDES += '#include "src/shared/api/' + src_part.replace(search_dir, '') + '"\n'
      name = src_part.replace(search_dir, 'kodi_').replace('.h', '').replace('/', '_').replace('addon-instance', 'addon')
      print(name)
      #exit()
      USED_UNIONS += '    {} {};\n'.format(found, found.replace('union ', '').replace('_FUNC_UNION', '').lower())

  f = open(target_file, 'r')
  data = f.read()
  f.close()
  is_set_1 = False
  is_set_2 = False
  start_1 = False
  start_2 = False
  file_text = ''
  for line in data.splitlines():
    if '/*---AUTO_GEN_PARSE<USED_INCLUDES>---*/' in line:
      start_1 = True
    elif '/*---AUTO_GEN_PARSE<USED_INCLUDES_END>---*/' in line:
      is_set_1 = False
      start_1 = False
    elif start_1 and not is_set_1:
      file_text += USED_INCLUDES
      is_set_1 = True
      continue

    if '/*---AUTO_GEN_PARSE<USED_UNIONS>---*/' in line:
      start_2 = True
    elif '/*---AUTO_GEN_PARSE<USED_UNIONS_END>---*/' in line:
      is_set_2 = False
      start_2 = False
    elif start_2 and not is_set_2:
      file_text += USED_UNIONS
      is_set_2 = True
      continue

    if not is_set_1 and not is_set_2:
      file_text += line + '\n';

  if file_text != data or force:
    print('    - Updating ' + target_file.replace(kodi_dir, ''))
    f = open(target_file, "w")
    f.write(file_text)
    f.close()
    os.system('clang-format -style=file -i ' + target_file)
