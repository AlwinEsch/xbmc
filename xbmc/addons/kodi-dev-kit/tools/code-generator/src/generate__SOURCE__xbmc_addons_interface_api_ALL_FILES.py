from code_generator import *
from .sub_file_hdl import *
from .helpers import *

import glob
import os

def generate__SOURCE__xbmc_addons_interface_api_ALL_FILES(force):
  """
  This function generate dirs and files in xbmc/addons/interface/api.

  They are used only to make use in Kodi cleaner as the in and out not need to
  include separate, also can the user add some hand edited code to there.
  """
  print('  - Generate dirs and files in xbmc/addons/interface/api/')

  # If new generate his dir
  target_dir = kodi_dir + 'xbmc/addons/interface/api/'
  if not os.path.exists(target_dir):
    os.makedirs(target_dir)

  search_dir = kodi_dir + 'xbmc/addons/interface/api_in/'
  dirs = sorted(glob.glob(search_dir + '**/', recursive=True))
  for dir in dirs:
    src_parts = sorted(glob.glob(dir + '*.h', recursive=False))

    # If new generate his dir
    target = dir.replace('/api_in/', '/api/')
    if not os.path.exists(target):
      os.makedirs(target)

    for src_part in src_parts:
      source_file = target_dir + src_part.replace(search_dir, '')

      src = header_file_copyright
      src += '#pragma once\n'
      src += '\n'
      src += '#include "' + src_part.replace(kodi_dir + 'xbmc/', '') + '"\n'

      src_part = src_part.replace('/api_in/', '/api_out/')
      if os.path.exists(src_part):
        src += '#include "' + src_part.replace(kodi_dir + 'xbmc/', '') + '"\n'

      src += '\n'
      src += '/* Code below becomes on auto generation reused, hand edited parts should included here */\n'
      src += '/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD>---*/\n'

      hand_edited = ''
      if os.path.exists(source_file):
        f = open(source_file, 'r')
        data = f.read()
        start = False
        for line in data.splitlines():
          if '/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD>---*/' in line:
            start = True
          elif '/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_END>---*/' in line:
            start = False
          elif start:
            hand_edited += line + '\n'

      src += hand_edited
      src += '/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_END>---*/\n'

      if not os.path.isfile(source_file) or src != open(source_file).read() or force:
        print('    - Generated new or updated ' + source_file.replace(kodi_dir, ''))
        f = open(source_file, 'w')
        f.write(src)
        f.close()
        os.system('clang-format -style=file -i ' + source_file)

