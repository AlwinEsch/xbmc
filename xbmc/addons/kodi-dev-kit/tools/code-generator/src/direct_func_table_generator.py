from code_generator import *
from .sub_file_hdl import *
from .helpers import *

from hashlib import sha256

import glob
import os
import re
import filecmp
import shutil

class DirectFuncTableGenerator:
  def __init__(self, options):
    self.options = options
    self.api_list_init_code = []
    self.api_list_typedef = []
    self.api_list_struct = []

  def Generate(self):
    search_dir = '{}xbmc/addons/kodi-dev-kit/include/kodi/c-api/'.format(kodi_dir)
    scan_dir = search_dir + '/**/'

    highest_found_api = 0

    includes_h = ''
    includes_c = ''
    structs = ''
    dirs = sorted(glob.glob(scan_dir, recursive=True))
    for dir in dirs:
      source_dir = dir.replace(search_dir, '')

      src_parts = sorted(glob.glob(dir + '*.h', recursive=True))
      for src_part in src_parts:
        if not FileContainsInterfaceAPICalls(src_part):
          continue

        api_list_typedef = []
        api_list_struct = []
        api_list_init_code = []
        with open(src_part) as f:
          file_text = f.read()
          f.close()

        header_group_id = TranslatePathToCUsableString(src_part, search_dir)

        function_addon = ''
        for line in file_text.splitlines():
          if 'ATTR_DLL_EXPORT' in line \
             and not '#define' in line:
            line = line.strip()
            if line.startswith('//') or line.startswith('/*'):
              continue
            function_addon = line;
          elif function_addon != '':
            function_addon += line;
          if function_addon != '' and ';' in line:
            function_addon = " ".join(function_addon.split())

            scanner = RegexScanExport(function_addon, self.options)
            scanner.ScanFunction()

            if scanner.api_added > highest_found_api:
              highest_found_api = scanner.api_added;

            if scanner.api_added > highest_found_api:
              highest_found_api = scanner.api_added;

            func_values = ''
            current_value = 1
            for value in scanner.values:
              if value != '...':
                value_name = value.split()[-1].strip()
                value_type = value[:-len(value_name)].strip()
                if '[' in value_name:
                  value_type += '[' + value_name.split('[', 1)[-1]

                include = '#include "../{}"\n'.format(src_part.replace(search_dir, ''))
                check_type = value_type.replace('*', '').replace('[]', '').replace('const', '').strip()
                if not check_type in known_STANDARD_C_TYPES \
                   and check_type != 'char' \
                   and check_type != 'void':
                  if 'struct ' in value_type:
                    struct = '{};\n'.format(check_type)
                    if not struct in structs:
                      structs += struct
                  else:
                    if not include in includes_h:
                      includes_h += include
              else:
                value_name = ''
                value_type = '...'

              func_values += value_type + (', ' if current_value < len(scanner.values) else '')
              current_value += 1

            include = '#include "../{}"\n'.format(src_part.replace(search_dir, ''))
            check_type = scanner.retval.replace('*', '').replace('[]', '').replace('const', '').strip()
            if not check_type in known_STANDARD_C_TYPES \
                and check_type != 'char' \
                and check_type != 'void':
              if 'struct ' in scanner.retval:
                struct = '{};\n'.format(check_type)
                if not struct in structs:
                  structs += struct
              else:
                if not include in includes_h:
                  includes_h += include
            include_c = include.replace('"../', '"include/kodi/c-api/')
            if not include_c in includes_c and not include in includes_h:
              includes_c += include_c

            entry = ('  addonIfc->to_kodi.{}.{} = {};'
                     .format(header_group_id,
                             scanner.funcname,
                             scanner.funcname))
            api_list_init_code.append(entry)

            entry = ('typedef {}(ATTR_INT_APIENTRYP PFN_INT_{}_V{})({});'
                     .format(scanner.retval,
                             scanner.funcname.upper(),
                             scanner.api_added,
                             func_values))
            api_list_typedef.append(entry)

            entry = ('  PFN_INT_{}_V{} {};'
                     .format(scanner.funcname.upper(),
                             scanner.api_added,
                             scanner.funcname))
            api_list_struct.append(entry)
            function_addon = '';
            continue

        if api_list_struct and api_list_typedef:
          self.api_list_typedef.append('// {}'.format(src_part.replace(search_dir, '')))
          self.api_list_typedef += sorted(api_list_typedef)
          self.api_list_typedef.append('')

          self.api_list_struct.append('struct {}'.format(header_group_id))
          self.api_list_struct.append('{')
          self.api_list_struct.append('  void* thisClassHdl;')
          self.api_list_struct += sorted(api_list_struct)
          self.api_list_struct.append('};\n')

          code_struct = ''
          code_struct += '#ifndef ATTR_INT_APIENTRYP\n'
          code_struct += '#define ATTR_INT_APIENTRYP ATTR_APIENTRYP\n'
          code_struct += '#endif\n'
          code_struct += '\n'
          code_struct += '#ifndef ATTR_INT_DLL_EXPORT\n'
          code_struct += '#define ATTR_INT_DLL_EXPORT ATTR_DLL_EXPORT\n'
          code_struct += '#endif\n'
          code_struct += '\n'
          code_struct += '\n'.join(sorted(api_list_typedef))
          code_struct += '\n'
          code_struct += '\n'
          code_struct += 'struct directFunc_{}\n'.format(header_group_id)
          code_struct += '{\n'
          code_struct += '  void* thisClassHdl;\n'
          code_struct += '\n'.join(sorted(api_list_struct))
          code_struct += '\n};\n'
          code_struct += '\n'

          code_func = ''
          code_func += 'void CHdl_kodi_{}::Init(directFunc_Interface* addonIfc)\n'.format(header_group_id)
          code_func += '{\n'
          code_func += '\n'.join(sorted(api_list_init_code))
          code_func += '\n}\n'

          print(code_struct)
          exit()




          self.api_list_init_code.append('  // {}'.format(src_part.replace(search_dir, '')))
          self.api_list_init_code += sorted(api_list_init_code)
          self.api_list_init_code.append('')

    code_part = ''
    for entry in self.api_list_typedef:
      code_part += '  {}\n'.format(entry)

    code_part += '  struct direct_func_table\n'
    code_part += '  {\n'
    for entry in self.api_list_struct:
      code_part += '  {}\n'.format(entry)
    code_part += '  };\n'

    #print(code_part)

    #hashedWord = sha256(code_part.encode('utf-8')).hexdigest()

    #code_h = header_file_copyright
    #code_h += '\n'
    #code_h += '/* API_HASH<{}> */\n'.format(hashedWord)
    #code_h += '\n'
    #code_h += '#ifndef C_API_DL_API_{}_H\n'.format(self.api)
    #code_h += '#define C_API_DL_API_{}_H\n'.format(self.api)
    #code_h += '\n'
    #code_h += '#include "../addon_base.h"\n'
    #code_h += includes_h
    #code_h += '\n'
    #code_h += '#ifndef ATTR_DL_APIENTRYP\n'
    #code_h += '#define ATTR_DL_APIENTRYP ATTR_APIENTRYP\n'
    #code_h += '#endif\n'
    #code_h += '\n'
    #code_h += '#ifndef ATTR_DL_DLL_EXPORT\n'
    #code_h += '#define ATTR_DL_DLL_EXPORT ATTR_DLL_EXPORT\n'
    #code_h += '#endif\n'
    #code_h += '\n'
    #code_h += '#ifdef __cplusplus\n'
    #code_h += 'extern "C"\n'
    #code_h += '{\n'
    #code_h += '#endif /* __cplusplus */\n'
    #code_h += '\n'
    #code_h += '  struct kodi_api_{};\n'.format(self.api)
    #code_h += '\n'
    #code_h += '  ATTR_DL_DLL_EXPORT bool load_kodi_api_{}(struct kodi_api_{}* api);\n'.format(self.api, self.api)
    #code_h += '\n'
    #code_h += structs
    #code_h += '\n'
    #code_h += code_part
    #code_h += '\n'
    #code_h += '#ifdef __cplusplus\n'
    #code_h += '} /* extern "C" */\n'
    #code_h += '#endif /* __cplusplus */\n'
    #code_h += '\n'
    #code_h += '#endif /* C_API_DL_API_{}_H */\n'.format(self.api)

    #temp_file = './tmp/tmp-auto-gen.h'
    #os.makedirs(os.path.dirname(temp_file), exist_ok=True)
    #f = open(temp_file, "w")
    #f.write(code_h)
    #f.close()

    #os.system('clang-format -style=file -i ' + temp_file)

    #target_file = '{}xbmc/addons/kodi-dev-kit/include/kodi/c-api/dl/kodi_api_{}.h'.format(kodi_dir, self.api)
    #if self.options.force \
       #or not os.path.isfile(target_file) \
       #or not filecmp.cmp(target_file, temp_file):
      #print('    - Updating ' + target_file)
      #os.makedirs(os.path.dirname(target_file), exist_ok=True)
      #shutil.copyfile(temp_file, target_file)

    #code_c = header_file_copyright
    #code_c += '\n'
    #code_c += '/* API_HASH<{}> */\n'.format(hashedWord)
    #code_c += '\n'
    #code_c += '#include "include/kodi/c-api/dl/kodi_api_{}.h"\n'.format(self.api)
    #code_c += '\n'
    #code_c += includes_c
    #code_c += '\n'
    #code_c += 'ATTR_DL_DLL_EXPORT bool load_kodi_api_{}(struct kodi_api_{}* api)\n'.format(self.api, self.api)
    #code_c += '{\n'
    #code_c += '  if (api == NULL)\n'
    #code_c += '  {\n'
    #code_c += '    return false;\n'
    #code_c += '  }\n'
    #code_c += '\n'
    #code_c += '\n'.join(self.api_list_init_code)
    #code_c += '\n'
    #code_c += '  return true;\n'
    #code_c += '}\n'

    #temp_file = './tmp/tmp-auto-gen.c'
    #os.makedirs(os.path.dirname(temp_file), exist_ok=True)
    #f = open(temp_file, "w")
    #f.write(code_c)
    #f.close()

    #os.system('clang-format -style=file -i ' + temp_file)

    #target_file = '{}xbmc/addons/kodi-dev-kit/src/addon/api/dl/kodi_api_{}.c'.format(kodi_dir, self.api)
    #if self.options.force \
       #or not os.path.isfile(target_file) \
       #or not filecmp.cmp(target_file, temp_file):
      #print('    - Updating ' + target_file)
      #os.makedirs(os.path.dirname(target_file), exist_ok=True)
      #shutil.copyfile(temp_file, target_file)

    #return True if highest_found_api > self.api else False
