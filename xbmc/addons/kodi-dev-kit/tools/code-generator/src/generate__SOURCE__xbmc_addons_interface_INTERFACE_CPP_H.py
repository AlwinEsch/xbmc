from code_generator import *
from .sub_file_hdl import *
from .helpers import *

import glob
import os

def generate__SOURCE__xbmc_addons_interface_INTERFACE_CPP_H(force):
  print('  - Generate part changes in xbmc/addons/interface/Interface.cpp and xbmc/addons/interface/Interface.h')

  base_dir_cpp = kodi_dir + 'xbmc/addons/interface/Interface.cpp'
  base_dir_h = kodi_dir + 'xbmc/addons/interface/Interface.h'

  if not os.path.exists(base_dir_cpp):
    print('ERROR: Needed ' + base_dir_cpp + ' not present!')
    exit()
  if not os.path.exists(base_dir_h):
    print('ERROR: Needed ' + base_dir_h + ' not present!')
    exit()

  src_list_include = ""
  src_list_set1 = ""
  src_list_set2 = ""
  hdr_list_set1 = ""
  hdr_list_set2 = ""
  search_dir = kodi_dir + 'xbmc/addons/interface/api/'
  scan_dir = search_dir + '**/'

  dirs = sorted(glob.glob(scan_dir, recursive=True))
  for dir in dirs:
    source_dir = dir.replace(search_dir, '')

    src_parts = sorted(glob.glob(dir + '*.h', recursive=False))
    for src_part in src_parts:
      src_list_include += '#include "api/{}"\n'.format(src_part.replace(search_dir, ''))
      part_name = src_part.replace(search_dir, '').replace('.', '_').replace('/', '_').replace('-', '')
      src_list_set1 += '  kodi_{} = new CHdl_kodi_{}(*this);\n'.format(part_name, part_name)
      src_list_set1 += '  m_handlers[funcGroup_{}] = kodi_{};\n'.format(part_name, part_name)

      src_list_set2 += ('    kodi_{}->InitDirect(&m_directIfc->to_kodi.{}, &m_directIfc->to_addon.{});\n'
                        .format(part_name, part_name, part_name))

      hdr_list_set1 += 'class CHdl_kodi_{};\n'.format(part_name, part_name)
      hdr_list_set2 += '  CHdl_kodi_{}* kodi_{};\n'.format(part_name, part_name)

  new_code = ''
  with open(base_dir_cpp) as f:
    data = f.read()
    f.close()

  INTERFACE_CPP_SET_INCLUDE = False
  INTERFACE_CPP_H_SET = False
  for line in data.splitlines():
    if not INTERFACE_CPP_SET_INCLUDE and not INTERFACE_CPP_H_SET:
      new_code += line + '\n'

    if '/*---AUTO_GEN_PARSE<INTERFACE_CPP_SET_INCLUDE>---*/' in line:
      INTERFACE_CPP_SET_INCLUDE = True

    if '/*---AUTO_GEN_PARSE<INTERFACE_CPP_SET_INCLUDE_END>---*/' in line:
      INTERFACE_CPP_SET_INCLUDE = False
      new_code += src_list_include
      new_code += line + '\n'

    if '/*---AUTO_GEN_PARSE<INTERFACE_CPP_H_SET>---*/' in line:
      INTERFACE_CPP_H_SET = True

    if '/*---AUTO_GEN_PARSE<INTERFACE_CPP_H_SET_END>---*/' in line:
      INTERFACE_CPP_H_SET = False
      new_code += src_list_set1
      new_code += '\n'
      new_code += '  if (m_directIfc != nullptr)\n'
      new_code += '  {\n'
      new_code += '{}'.format(src_list_set2)
      new_code += '  }\n'
      new_code += line + '\n'

  if data != new_code or force:
    print('    - Updating {}'.format(base_dir_cpp.replace(kodi_dir, '')))
    f = open(base_dir_cpp, "w")
    f.write(new_code)
    f.close()
    #os.system('clang-format -style=file -i ' + base_dir_cpp)

  new_code = ''
  with open(base_dir_h) as f:
    data = f.read()
    f.close()

  INTERFACE_CPP_H_SET1 = False
  INTERFACE_CPP_H_SET2 = False
  for line in data.splitlines():
    if not INTERFACE_CPP_H_SET1 and not INTERFACE_CPP_H_SET2:
      new_code += line + '\n'

    if '/*---AUTO_GEN_PARSE<INTERFACE_CPP_H_SET1>---*/' in line:
      INTERFACE_CPP_H_SET1 = True

    if '/*---AUTO_GEN_PARSE<INTERFACE_CPP_H_SET1_END>---*/' in line:
      INTERFACE_CPP_H_SET1 = False
      new_code += hdr_list_set1
      new_code += line + '\n'

    if '/*---AUTO_GEN_PARSE<INTERFACE_CPP_H_SET2>---*/' in line:
      INTERFACE_CPP_H_SET2 = True

    if '/*---AUTO_GEN_PARSE<INTERFACE_CPP_H_SET2_END>---*/' in line:
      INTERFACE_CPP_H_SET2 = False
      new_code += hdr_list_set2
      new_code += line + '\n'

  if data != new_code or force:
    print('    - Updating {}'.format(base_dir_h.replace(kodi_dir, '')))
    f = open(base_dir_h, "w")
    f.write(new_code)
    f.close()
    #os.system('clang-format -style=file -i ' + base_dir_h)
