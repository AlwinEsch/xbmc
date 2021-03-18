from code_generator import *
from .sub_file_hdl import *
from .helpers import *

from .generate__SOURCE__dev_kit_instance_construct import *

import glob
import os
import re
import filecmp
import shutil

ignored_structs = []

class APIEntryClass:
  def __init__(self, entries):
    self.entries = entries

class APIEntryFunction:
  def __init__(self):
    self.from_api = -1
    self.to_api = -1
    self.equal_ptr_from = -1
    self.equal_ptr_to = -1
    self.name = ''
    self.scan_code = None

class GroupData:
  def __init__(self, callbacks, options):
    self.callbacks = callbacks
    self.options = options
    self.header_group_id = ''
    self.interface_data_to_addon = []
    self.interface_data_to_kodi = []
    self.shared_structures = []
    self.shared_structures_other_file = []
    self.used_enums = []
    self.to_kodi_direct_func_table = []
    self.to_kodi_api_list_typedef = []
    self.to_addon_direct_func_table = []
    self.to_addon_api_list_typedef = []
    self.path = ''
    self.kodi_ifc_includes = []
    self.additional_addon_lib_includes = []
    self.additional_shared_includes = []
    self.independent_to_addon_api_structs = ''
    self.functions_equal_everywhere = []
    self.functions_api_list = []


    self.api_control_entries = []

    self.override_use_direct_api_only = False

    self.last_struct_scan_1 = ''
    self.last_struct_scan_2 = ''

  def GenerateToKodiInitDirectFunction(self):
    """
    Generate a function to use inside Kodi to set function addresses about
    direct calls from addon to Kodi.

    The function addresses are then used on addon dev kit library, due to
    creation together with Kodi and not accessed by addon direct can be
    parts here changed without destroy of addon API.

    The target source places are on *.cpp files on ./xbmc/addons/interface/api

    Returns:
      string: Code text of generated function.

    WARNING: This addresses are not usable inside independent sandbox api, only
    thought to use on direct loaded addon as dynamic library (e.g. needed on
    iOS or tvOS).

    Produced code example:
    ~~~~~~~~~~~~~~~~~
    void CHdl_kodi_addon_base_h::InitDirect(directFuncToKodi_addon_base_h* ifc)
    {
      ifc->thisClassHdl = this;
      // Unused "kodi_check_main_shared", done only in addon lib
      // Unused "kodi_init", done only in addon lib
      // Unused "kodi_deinit", done only in addon lib
      // Unused "kodi_process", done only in addon lib
      ifc->kodi_log = kodi_log;
      ifc->kodi_addon_get_lib_path = kodi_addon_get_lib_path;
      ...
    }
    ~~~~~~~~~~~~~~~~~
    """
    ret  = ('void CHdl_kodi_{}::InitDirect(directFuncToKodi_{}* ifcToKodi, directFuncToAddon_{}* ifcToAddon)\n'
            .format(self.header_group_id,
                    self.header_group_id,
                    self.header_group_id,
                    self.header_group_id))
    ret += '{\n'
    ret += '  ifcToKodi->thisClassHdl = this;\n'
    ret += '  m_ifcToAddon = ifcToAddon;\n'
    for data in self.interface_data_to_kodi:
      if not data.use_internal_only:
        ret += '  ifcToKodi->{} = {};\n'.format(data.funcname_ifc, data.funcname_ifc)
      else:
        ret += '  // Unused "{}", done only in addon lib\n'.format(data.funcname)
    ret += '}\n'
    return ret

  def GenerateToAddonInitDirectFunction(self):
    ret  = ('void CHdl_kodi_{}::InitDirect(directFuncToAddon_{}* ifcToAddon)\n'
            .format(self.header_group_id,
                    self.header_group_id,
                    self.header_group_id,
                    self.header_group_id))
    ret += '{\n'
    ret += '  ifcToAddon->thisClassHdl = this;\n'
    for data in self.interface_data_to_addon:
      ret += '  ifcToAddon->{} = {};\n'.format(data.funcname_ifc, data.funcname_ifc)
    ret += '}\n'
    return ret

  def GenerateToKodiDirectFuncTable(self):
    ret = '// Code here relates to direct API calls without use of shared mem from addon to Kodi.\n'
    ret += '//{{{\n'
    ret += '\n'
    ret += '\n'.join(sorted(self.to_kodi_api_list_typedef))
    ret += '\n'
    ret += '\n'
    ret += 'struct directFuncToKodi_{}\n'.format(self.header_group_id)
    ret += '{\n'
    ret += '  void* thisClassHdl;\n'
    ret += '\n'.join(sorted(self.to_kodi_direct_func_table))
    ret += '\n};\n'
    ret += '\n'
    ret += '//}}}\n'

    return ret

  def GenerateToAddonDirectFuncTable(self):
    ret = '// Code here relates to direct API calls without use of shared mem from Kodi to addon.\n'
    ret += '//{{{\n'
    ret += '\n'
    ret += '\n'.join(sorted(self.to_addon_api_list_typedef))
    ret += '\n'
    ret += '\n'
    ret += 'struct directFuncToAddon_{}\n'.format(self.header_group_id)
    ret += '{\n'
    ret += '  void* thisClassHdl;\n'
    ret += '\n'.join(sorted(self.to_addon_direct_func_table))
    ret += '\n};\n'
    ret += '\n'
    ret += '//}}}\n'

    return ret

  def GenerateIndependentAPIStructs(self):
    class APIEntry:
      def __init__(self, api_min, api_max, api_struct):
        self.api_min = api_min
        self.api_max = api_max
        self.api_struct = api_struct
        self.api_struct_with_note = []
        self.api_struct_with_note += self.api_struct
        self.api_equal = []

    if not FileContainsInterfaceAPICallsToAddon(self.path):
      return

    lowest_api = GetLowestUsedAPI()
    highest_api = GetHighestUsedAPI()

    function_kodi = ''
    scans = []
    with open(self.path, 'r') as f:
      file_text = f.read()
      f.close()

      for line in file_text.splitlines():
        if 'ATTR_APIENTRYP' in line \
            and not line.strip().startswith('#'):
          function_kodi = line;
        elif function_kodi != '':
          function_kodi += line;
        if function_kodi != '' and ';' in line:
          function_kodi = " ".join(function_kodi.split())

          scan = RegexScanImport(function_kodi, self.options)
          if not scan.ScanFunction(file_text):
            function_kodi = ''
            continue

          scans.append(scan)
          function_kodi = ''

      if len(scans) == 0:
        print('FATAL: File {} failed to get API typedefs!'.format(self.path))
        raise NameError('Dev kit scan failure')


      struct_name = '{}_FUNC'.format(scans[0].groupname.upper())

      found = 0
      in_doc = False
      in_else = None
      code = ''

      api_entries = []
      for i in range(highest_api-lowest_api+1):
        api_entries.append([])

      api_code_defs = []
      for line in file_text.splitlines():
        line = line.strip()
        if len(line) == 0 or line.startswith('//'):
          continue
        if line.startswith('/*'):
          in_doc = True
        if in_doc and line.endswith('*/'):
          in_doc = False
          continue
        if in_doc:
          continue

        if found == 2:
          if line.startswith('#if __KODI_API__ '):
            api_code_defs.append(line.replace('#if __KODI_API__ ', '').split())
            continue
          if line.startswith('#elif __KODI_API__ '):
            in_else = api_code_defs[-1]
            del api_code_defs[-1]
            api_code_defs.append(line.replace('#elif __KODI_API__ ', '').split())
            continue
          if line.startswith('#else'):
            in_else = api_code_defs[-1]
            del api_code_defs[-1]
            continue
          if line.startswith('#endif'):
            if in_else == None:
              del api_code_defs[-1]
            in_else = None
            continue

        if found == 0 and line.replace('typedef ', '').startswith('struct ' + struct_name):
          if '{' in line:
            found = 2
          else:
            found = 1
          continue
        if found == 1 and line.startswith('{'):
          found = 2
          continue
        if found == 2:
          if line.startswith('}'):
            break

          code += line
          if not ';' in line:
            continue

          code = " ".join(code.split())
          typedef = code.split()[0]

          scan_found = None
          for scan in scans:
            if scan.ifc_name_typdef == typedef:
              scan_found = scan
              break

          if scan_found == None:
            print('FATAL: In struct \'{}\' is \'{}\', but typedef \'{}\' not found!'.format(struct_name, code, typedef))
            print('       File {}'.format(src_part))
            raise NameError('Dev kit scan failure')

          for i in range(highest_api-lowest_api+1):
            api = i + lowest_api

            if scan_found.api_added < lowest_api:
              print('FATAL: In struct \'{}\' is \'{}\', but lower as lowest API {}!'.format(struct_name, code, lowest_api))
              print('       File {}'.format(src_part))
              raise NameError('Dev kit scan failure')

            if scan_found.api_added <= api:
              if len(api_code_defs) != 0:
                if api_code_defs[-1][0] == '>=' and api >= int(api_code_defs[-1][1]):
                  if in_else != None:
                    if in_else[0] == '>=' and api >= int(in_else[1]):
                      continue
                  api_entries[i].append(scan_found)
                elif api_code_defs[-1][0] == '<' and api < int(api_code_defs[-1][1]):
                  if in_else != None:
                    if in_else[0] == '<' and api < int(in_else[1]):
                      continue
                  api_entries[i].append(scan_found)
                elif api_code_defs[-1][0] == '==' and api == int(api_code_defs[-1][1]):
                  if in_else != None:
                    if in_else[0] == '==' and api == int(in_else[1]):
                      continue
                  api_entries[i].append(scan_found)
              elif in_else != None:
                if in_else[0] == '>=' and api < int(in_else[1]):
                  api_entries[i].append(scan_found)
                elif in_else[0] == '<' and api >= int(in_else[1]):
                  api_entries[i].append(scan_found)
                elif in_else[0] == '==' and api != int(in_else[1]):
                  api_entries[i].append(scan_found)
              else:
                api_entries[i].append(scan_found)

          code = ''

      #api = lowest_api
      #for i in range(highest_api-lowest_api+1):
        #print('------: {}'.format(lowest_api+i))
        #control_entries = []
        #for entry in api_entries[i]:
          #api_entry = APIEntryFunction()
          #api_entry.scan_code = entry

          #control_entries.append(api_entry)

          #print(entry.funcname)
          #print(' - ' + str(entry.api_added))
        #print()
        #self.api_control_entries.append(APIEntryClass(control_entries))
        #api += 1
      #exit()










      api = lowest_api
      api_last_min = lowest_api
      api_last_max = lowest_api
      api_struct_before = []
      api_structs = []
      number = 0
      for api_entry in api_entries:
        api_struct_current = []
        for entry in api_entry:
          api_struct_current.append('{} {};'.format(entry.ifc_name_typdef, entry.ifc_name_func))

        if api_struct_before != api_struct_current:
          if len(api_structs) > 0:
            api_last_min = api_structs[-1].api_min
            api_last_max = api_structs[-1].api_max
            api_structs[-1].api_max = api - 1

          api_structs.append(APIEntry(api, highest_api, api_struct_current))
          api_struct_before = api_struct_current
        api += 1

      for api_entry in api_structs:
        number = 0
        for struct_entry in api_entry.api_struct:
          equal_from = -1
          equal_to = -1
          for api_entry_2 in api_structs:
            if number < len(api_entry_2.api_struct) and api_entry_2.api_struct[number] == struct_entry:
              if equal_from < 0:
                equal_from = api_entry_2.api_min
              if equal_to < 0 or api_entry_2.api_max > equal_to:
                equal_to = api_entry_2.api_max
          api_entry.api_struct_with_note[number] += ' /*---AUTO<EQUAL_FROM_TO:{}_{}>---*/\n'.format(equal_from, equal_to)
          api_entry.api_equal.append([equal_from, equal_to])

          value_name = struct_entry.split()[1].replace(';', '')
          if equal_from == lowest_api and equal_to == highest_api and not value_name in self.functions_equal_everywhere:
            self.functions_equal_everywhere.append(value_name)

          number += 1

      api = lowest_api
      api_unions = []
      while api <= highest_api:
        min_api = -1
        max_api = -1
        last_struct = 0
        while len(api_structs) > last_struct:
          if api >= api_structs[last_struct].api_min and api_structs[last_struct].api_max <= api+1:
            min_api = api_structs[last_struct].api_min
            max_api = api_structs[last_struct].api_max
          last_struct += 1
        if min_api == -1:
          min_api = lowest_api
        if max_api == -1:
          max_api = highest_api

        api_unions.append('struct {}_V{}_TO_V{} v{};\n'.format(struct_name, min_api, max_api, api))

        api += 1

      code = ''
      for api_entry in api_structs:
        code += '\n/* API struct from {} to {} */\n'.format(api_entry.api_min, api_entry.api_max)
        code += 'typedef struct {}_V{}_TO_V{}\n'.format(struct_name, api_entry.api_min, api_entry.api_max)
        code += '{\n  '
        code += "  ".join(api_entry.api_struct_with_note)
        code += '} ' + '{}_V{}_TO_V{}'.format(struct_name, api_entry.api_min, api_entry.api_max) + ';\n'

      if code:
        code += '\nunion ' + struct_name + '_UNION\n'
        code += '{\n  '
        code += "  ".join(api_unions)
        code += '};\n'

      self.independent_to_addon_api_structs = code



      #print(code)

      #if struct_name == 'KODI_ADDON_VISUALIZATION_FUNC':
        #exit()

  def AddAdditionalAddonLibIncludes(self, include):
    if not include in self.additional_addon_lib_includes:
      self.additional_addon_lib_includes.append(include)

  def GetParentSharedTuples(self):
    if self.override_use_direct_api_only:
      return '/* NOTE: Ignored as direct api only is set! */\n'

    ret = ''
    for data in self.interface_data_to_kodi:
      ret += '// Original API call: ' + data.function_complete + '\n'
      ret += data.parent_addon_c_lib_function_shared_tuple_in + '\n'
      ret += data.parent_addon_c_lib_function_shared_tuple_out + '\n'
    return ret

  def GetChildSharedTuples(self):
    if self.override_use_direct_api_only:
      return '/* NOTE: Ignored as direct api only is set! */\n'

    ret = ''
    for data in self.interface_data_to_addon:
      ret += '// Original API call: ' + data.function_complete + '\n'
      ret += data.child_addon_c_lib_function_shared_tuple_in + '\n'
      ret += data.child_addon_c_lib_function_shared_tuple_out + '\n'
    return ret

  def GetSharedEnums(self):
    if self.override_use_direct_api_only:
      return ''

    enums_code = '\n' if len(self.used_enums) > 0 else ''
    for enum in self.used_enums:
      enums_code += '#ifndef MSGPACK_ADD_ENUM_' + enum + '\n'
      enums_code += '#define MSGPACK_ADD_ENUM_' + enum + '\n'
      enums_code += 'MSGPACK_ADD_ENUM(' + enum + ');\n'
      enums_code += '#endif\n'

    return enums_code

  def GetSharedStructures(self):
    if self.override_use_direct_api_only:
      return ''

    ret = ''
    if len(self.shared_structures):
      ret += '/* Confirm after autogen the correctness here! */\n'
      ret += '/*---AUTO_GEN_PARSE<DATA_STRUCTURES>---*/\n'
      for data in self.shared_structures:
        ret += '\n' + data[1]
      ret += '/*---AUTO_GEN_PARSE<DATA_STRUCTURES_END>---*/\n'
      ret += '\n'
    return ret

  def GetAddonCLibFunctionsShared(self):
    ret = ''
    for data in self.interface_data_to_kodi:
      ret += '\n' + data.parent_addon_c_lib_function_shared
    return ret

  def GetAddonCLibFunctionsDirect(self):
    ret = ''
    for data in self.interface_data_to_kodi:
      ret += '\n' + data.parent_addon_c_lib_function_direct
    return ret

  def GetAddonCLibFunctionsDirectPtr(self):
    ret = ''
    for data in self.interface_data_to_kodi:
      ret += data.parent_addon_c_lib_function_direct_ptr
    return ret

  def GetKodiSwitchCase(self):
    if not self.override_use_direct_api_only:
      ret = ''
      for data in self.interface_data_to_kodi:
        ret += data.parent_kodi_cpp_function_switch_case
      return ret
    else:
      return '    /* NOTE: Ignored as direct api only is set! */\n'

  def GetKodiSourcePart(self):
    ret = ''
    for data in self.interface_data_to_kodi:
      if data.parent_kodi_cpp_function_source:
        ret += '\n' + data.parent_kodi_cpp_function_source
    if not ret:
      ret = '/* NOTE: unused (no callbacks here) */\n'
    return ret

  def GetDevKitKodiToAddonSourcePart(self):
    ret = ''
    for data in self.interface_data_to_addon:
      if data.dev_kit_kodi_to_addon_source:
        ret += '\n' + data.dev_kit_kodi_to_addon_source
    if not ret:
      ret = '/* NOTE: unused (no functions from Kodi to addon here) */\n'
    return ret

  def GetKodiSourcePartChild(self):
    ret = ''
    for data in self.interface_data_to_addon:
      if data.child_kodi_cpp_function_source:
        ret += '\n' + data.child_kodi_cpp_function_source
    if not ret:
      ret = '/* NOTE: unused (no functions here) */\n'
    return ret

  def GetKodiParentHeaderPart(self):
    ret = ''
    for data in self.interface_data_to_kodi:
      if data.parent_kodi_cpp_function_header:
        ret += data.parent_kodi_cpp_function_header + '\n'
    return ret

  def GetKodiChildHeaderPart(self):
    ret = ''
    for data in self.interface_data_to_addon:
      if data.child_kodi_cpp_function_header:
        ret += data.child_kodi_cpp_function_header + '\n'
    return ret

  def GetDevKitKodiToAddonHeaderPart(self):
    ret = ''
    for data in self.interface_data_to_addon:
      if data.dev_kit_kodi_to_addon_header:
        ret += data.dev_kit_kodi_to_addon_header + '\n'
    return ret

  def GetKodiParentEnumList(self):
    ret  = 'typedef enum funcParent_' + self.header_group_id + ' : int\n'
    ret += '{\n'
    if len(self.interface_data_to_kodi) != 0 and not self.override_use_direct_api_only:
      for data in self.interface_data_to_kodi:
        ret += '  funcParent_' + data.funcname_ifc + ',\n'
    else:
      ret += '  funcParent_' + self.header_group_id + '_dummy\n'
    ret += '} funcParent_' + self.header_group_id + ';\n'
    return ret

  def GetKodiChildEnumList(self):
    ret  = 'typedef enum funcChild_' + self.header_group_id + ' : int\n'
    ret += '{\n'
    if len(self.interface_data_to_addon) != 0 and not self.override_use_direct_api_only:
      for data in self.interface_data_to_addon:
        ret += '  funcChild_' + data.funcname_ifc + ',\n'
    else:
      ret += '  funcChild_' + self.header_group_id + '_dummy\n'
    ret += '} funcChild_' + self.header_group_id + ';\n'
    return ret

  def KnownSharedStructure(self, struct_name):
    m = re.search('^.*?struct\ *([a-zA-Z[0-9_]*)', struct_name)
    if not m or not m.group(1):
      return False

    struct_name = m.group(1)

    # Defined in OS and set hard on SharedGroups.h
    if struct_name == 'tm':
      return True

    for entry, code, path in self.shared_structures + self.shared_structures_other_file:
      if entry == struct_name:
        return True
    return True

  def KnownSharedStructureWithClean(self, struct_name):
    m = re.search('^.*?struct\ *([a-zA-Z[0-9_]*)', struct_name)
    if not m or not m.group(1):
      return False

    struct_name = m.group(1)

    # Defined in OS and set hard on SharedGroups.h
    if struct_name == 'tm':
      return False

    for entry, code, path in self.shared_structures + self.shared_structures_other_file:
      if entry == struct_name and 'CleanCStructure' in code:
        return True
    return False

  def GenerateSharedStructure(self, struct_name):
    if self.override_use_direct_api_only:
      return True

    m = re.search('^.*?struct\ *([a-zA-Z[0-9_]*)', struct_name)
    if not m or not m.group(1):
      print('FATAL: Bad struct defined in ' + self.funcname)
      raise

    struct_name = m.group(1)

    # Defined in OS and set hard on SharedGroups.h
    if struct_name == 'tm':
      return True

    if struct_name in ignored_structs:
      return False

    for entry, code, path in self.shared_structures:
      if entry == struct_name:
        return True

    code_values = ''
    set_code = ''
    get_code = ''
    clean_code = ''
    msgpack = '  MSGPACK_DEFINE('

    current = 0
    c_struct = GetCStruct(struct_name)
    search_dir = '{}xbmc/addons/kodi-dev-kit/include/kodi/c-api/'.format(kodi_dir)
    target_dir = 'src/shared/api/'
    target_file = c_struct.path.replace(search_dir, target_dir)

    # Check the structure is in same c-api file, if not add it to "additional_shared_includes"
    # to scan on end and create shared include file separate for here
    if self.path != c_struct.path:
      path = '#include "{}"'.format(target_file)

      # Check include already used, if not add it to shared base header
      if not path in self.additional_shared_includes:
        self.additional_shared_includes.append('#include "{}"'.format(target_file))

      # Check now the structure already defined, if yes prevent add again
      for entry, code, path in self.shared_structures_other_file:
        if entry == struct_name:
          return True

      # Add here the additional structure to use in separate files
      self.shared_structures_other_file.append((struct_name, c_struct.code, target_file))
      return True

    previous_entry = ''
    for entry in c_struct.code:
      if len(entry.split()) > 1:
        m = re.search('^.*?enum\ *([a-zA-Z[0-9_]*)', entry)
        if m and m.group(1) and m.group(1) in known_ENUMS and m.group(1) not in self.used_enums:
          self.used_enums.append(m.group(1))

      m = re.search('^\ *([a-zA-Z[0-9_].*)\ ([a-zA-Z[0-9_]+).*\[ *([a-zA-Z[0-9_]+) *\].*\[ *([a-zA-Z[0-9_]+) *\];$', entry)
      if m and m.group(1) and m.group(2) and m.group(3) and m.group(4):
        name = m.group(2)
        is_string = 'char*' in m.group(1)
        is_struct = 'struct ' in m.group(1)
        if is_string:
          value_type = 'std::string{}'.format(' /* CheckAPIUse_GenShare (0001) */' if self.options.debug else '')
        elif is_struct:
          print('TODO 2')
          raise
        else:
          value_type = m.group(1)
        code_values += '  std::array<std::array<{}, {}>, {}> {};\n'.format(value_type, m.group(4), m.group(3), m.group(2))
        set_code += '    for (unsigned int i = 0; i < ' + m.group(3) + '; ++i)\n'
        set_code += '    {\n'
        set_code += '      for (unsigned int j = 0; j < ' + m.group(4) + '; ++j)\n'
        set_code += '      {\n'
        set_code += '        ' + m.group(2) + '[i][j] = ' + ('c_data->' + m.group(2) + '[i][j] ? ' if is_string else '') + 'c_data->' + m.group(2) + '[i][j]' +  (' : "";\n' if is_string else ';\n')
        set_code += '      }\n'
        set_code += '    }\n'
        get_code += '    for (unsigned int i = 0; i < ' + m.group(3) + '; ++i)\n'
        get_code += '    {\n'
        get_code += '      for (unsigned int j = 0; j < ' + m.group(4) + '; ++j)\n'
        get_code += '      {\n'
        if is_string:
          get_code += '        if (c_data->' + m.group(2) + '[i][j])\n'
          get_code += '          free(c_data->' + m.group(2) + '[i][j]);\n'
          get_code += '        c_data->' + m.group(2) + '[i][j] = strdup(' + m.group(2) + '[i][j].c_str());\n'
        else:
          get_code += '        c_data->' + m.group(2) + '[i][j] = ' + m.group(2) + '[i][j];\n'
        get_code += '      }\n'
        get_code += '    }\n'
      else:
        m = re.search('^\ *([a-zA-Z[0-9_].*)\ ([a-zA-Z[0-9_]+).*\[ *([a-zA-Z[0-9_]+) *\];$', entry)
        if m and m.group(1) and m.group(2) and m.group(3):
          name = m.group(2)
          is_string = 'char*' in m.group(1)
          is_struct = 'struct ' in m.group(1)
          if is_string:
            value_type = 'std::string{}'.format(' /* CheckAPIUse_GenShare (0002) */' if self.options.debug else '')
          elif is_struct:
            value_type = ('IFC_{}{}'
                          .format(m.group(1).replace('struct ', ''),
                                  ' /* CheckAPIUse_GenShare (0003) */' if self.options.debug else ''))
          else:
            value_type = ('{}{}'
                          .format(m.group(1),
                                  ' /* CheckAPIUse_GenShare (0004) */' if self.options.debug else ''))
          code_values += '  std::array<{}, {}> {};\n'.format(value_type, m.group(3), m.group(2))
          set_code += ('    memcpy({}.data(), c_data->{}, {});\n'
                        .format(m.group(2),
                                m.group(2),
                                m.group(3)))
          if is_string:
            get_code += '    for (unsigned int i = 0; i < ' + m.group(3) + '; ++i)\n'
            get_code += '    {\n'
            get_code += '      if (c_data->' + m.group(2) + '[i])\n'
            get_code += '        free(c_data->' + m.group(2) + '[i];\n'
            get_code += '      c_data->' + m.group(2) + '[i] = strdup(' + m.group(2) + '[i].c_str());\n'
            get_code += '    }\n'
          else:
            get_code += ('    memcpy(c_data->{}, {}.data(), {});\n'
                         .format(m.group(2),
                                 m.group(2),
                                 m.group(3)))
        else:
          #print(entry)
          name = entry.rstrip(';').split()[-1].strip()
          value = entry.replace(name, '').replace(';', '').strip()
          if value == 'const char*':
            code_values += '  std::string {};\n'.format(name)
            set_code += '    if (c_data->{})\n'.format(name)
            set_code += '      {} = c_data->{};\n'.format(name, name)
            get_code += '    c_data->{} = {}.c_str();\n'.format(name, name)
          elif value == 'char*':
            code_values += '  std::string {};\n'.format(name)
            set_code += '    if (c_data->{})\n'.format(name)
            set_code += '      {} = c_data->{};\n'.format(name, name)
            get_code += '    if (!{}.empty())\n'.format(name)
            get_code += '      c_data->{} = strdup({}.c_str());\n'.format(name, name)
            clean_code += '    if (c_data->{})\n'.format(name)
            clean_code += '    {\n'
            clean_code += '      free(c_data->{});\n'.format(name)
            clean_code += '      c_data->{} = nullptr;\n'.format(name)
            clean_code += '    }\n'
          elif ContainsHdlVoidPointer(value):
            code_values += '  PtrValue {};\n'.format(name)
            set_code += '    {} = PtrValue(c_data->{});\n'.format(name, name)
            get_code += '    c_data->{} = reinterpret_cast<{}>({});\n'.format(name, value, name)
          elif 'struct ' in value:
            if value != self.last_struct_scan_1 and value != self.last_struct_scan_2:
              self.last_struct_scan_2 = self.last_struct_scan_1
              self.last_struct_scan_1 = value
              if self.last_struct_scan_2 != self.last_struct_scan_1:
                self.GenerateSharedStructure(value)

            if value.count('*') == 1 and 'size_t ' in previous_entry:
              new_struct_name = value.replace('struct ', '').replace('*', ''.strip())
              code_values += '  std::vector<IFC_{}> {};\n'.format(new_struct_name, name)

              previous_value_name = previous_entry.split()[-1].strip().replace(';', '')

              set_code += '    if (c_data->{} && c_data->{} != 0)\n'.format(name, previous_value_name)
              set_code += '    {\n'
              set_code += '      for (size_t i = 0; i < c_data->{}; ++i)\n'.format(previous_value_name)
              set_code += '        {}.emplace_back(&c_data->{}[i]);\n'.format(name, name)
              set_code += '    }\n'

              get_code += '    if (!{}.empty())\n'.format(name)
              get_code += '    {\n'
              get_code += '      c_data->{} = static_cast<{}*>(malloc(sizeof({}) * {}.size()));\n'.format(name, new_struct_name, new_struct_name, name)
              get_code += '      for (size_t i = 0; i < {}.size(); ++i)\n'.format(name)
              get_code += '        {}[i].SetCStructure(&c_data->{}[i]);\n'.format(name, name)
              get_code += '    }\n'

              clean_code += '    if (c_data->{})\n'.format(name)
              clean_code += '    {\n'
              clean_code += '      IFC_{} helper;\n'.format(new_struct_name)
              clean_code += '      for (size_t i = 0; i < c_data->{}; ++i)\n'.format(previous_value_name)
              clean_code += '        helper.CleanCStructure(&c_data->{}[i]);\n'.format(name)
              clean_code += '      free(c_data->{});\n'.format(name)
              clean_code += '      c_data->{} = nullptr;\n'.format(name)
              clean_code += '    }\n'
            elif value.count('*') == 0:
              new_struct_name = value.replace('struct ', '')
              code_values += '  IFC_{}\n'.format(entry.replace('struct ', ''))
              set_code += '    {} = IFC_{}(&c_data->{});\n'.format(name, new_struct_name, name)
              get_code += '    {}.SetCStructure(&c_data->{});\n'.format(name, name)
              clean_code += '    IFC_{}::CleanCStructure(&c_data->{});\n'.format(new_struct_name, name)
            else:
              code_values += '  {}\n'.format(entry)
              set_code += '    {} = c_data->{};\n'.format(name, name)
              get_code += '    c_data->{} = {}; /* TODO!!! */\n'.format(name, name)
          else:
            code_values += '  {}\n'.format(entry)
            set_code += '    {} = c_data->{};\n'.format(name, name)
            get_code += '    c_data->{} = {};\n'.format(name, name)

      if not current:
        msgpack += name + (',\n' if len(c_struct.code) > 1 else '')
      else:
        msgpack += '                 ' + name + (',\n' if current < len(c_struct.code)-1 else '')
      current += 1

      previous_entry = entry

    if not code_values:
      return True

    clean_function = ''
    if clean_code != '':
       clean_function += """\

  static inline void CleanCStructure(""" + struct_name + """* c_data)
  {
    if (c_data == nullptr)
      return;

""" + clean_code + """\
  }
"""

    code = """\
struct IFC_""" + struct_name + """
{
  IFC_""" + struct_name + """() = default;
  IFC_""" + struct_name + """(const """ + struct_name + """* c_data)
  {
    if (c_data == nullptr)
      return;

""" +  set_code + """\
  }
""" + clean_function + """
  void SetCStructure(""" + struct_name + """* c_data)
  {
    if (c_data == nullptr)
      return;

""" +  get_code + """\
  }

""" +  code_values + """
""" + msgpack + """);
};
"""
    self.shared_structures.append((struct_name, code, target_file))
    return True

  def Generate__xbmc_addons_kodidevkit_src_shared_kodi_ALL_FILES(self, force):
    path = self.path.replace('{}xbmc/addons/kodi-dev-kit/'.format(kodi_dir), '')
    include_path = ''
    for i in range(path.count('/')):
      include_path += '../'
    include_path += path

    search_dir = '{}xbmc/addons/kodi-dev-kit/include/kodi/c-api/'.format(kodi_dir)
    target_dir = kodi_dir + 'xbmc/addons/kodi-dev-kit/src/shared/api/'
    target_file = self.path.replace(search_dir, target_dir)

    file_text = header_file_copyright + """\

#pragma once

#include "src/shared/SharedGroups.h"
#include \"""" + include_path + """\"
""" + '\n'.join(self.additional_shared_includes) + """\

#include <string>
#include <string.h>
#include <tuple>
#include <vector>
""" + self.independent_to_addon_api_structs + """\

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_1') + """\
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/
\
""" + self.GetSharedEnums() + """\

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_2') + """\
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

""" + self.GenerateToKodiDirectFuncTable() + """
""" + self.GenerateToAddonDirectFuncTable() + """
""" + self.GetSharedStructures() + """\
""" + self.GetKodiParentEnumList() + """\

// clang-format off
/*---AUTO_GEN_PARSE<FUNC_PARENT_TUPLES>---*/
""" + self.GetParentSharedTuples() + """\
/*---AUTO_GEN_PARSE<FUNC_PARENT_TUPLES_END>---*/
// clang-format on

//==============================================================================

""" + self.GetKodiChildEnumList() + """\

// clang-format off
/*---AUTO_GEN_PARSE<FUNC_CHILD_TUPLES>---*/
""" + self.GetChildSharedTuples() + """\
/*---AUTO_GEN_PARSE<FUNC_CHILD_TUPLES_END>---*/
// clang-format on

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
"""

    # Make now the creation and copy of file
    temp_file = target_file.replace('../../../../../xbmc/addons', './tmp')
    os.makedirs(os.path.dirname(temp_file), exist_ok=True)

    f = open(temp_file, "w")
    f.write(file_text)
    f.close()
    os.system('clang-format -style=file -i ' + temp_file)

    if force or not filecmp.cmp(target_file, temp_file):
      print('  - Updating ' + target_file)
      os.makedirs(os.path.dirname(target_file), exist_ok=True)
      shutil.copyfile(temp_file, target_file)

    return file_text

  def ScanStructureInsideAdditional(self, force, structure, include_path_of_searcher):
    c_struct = GetCStruct(structure)

    include = c_struct.path.replace('{}xbmc/addons/kodi-dev-kit/include/kodi/c-api/'.format(kodi_dir), 'src/shared/api/')
    include_path = ''
    for i in range(include.count('/')):
      include_path += '../'
    include_path += include

    self.shared_structures_other_file.append((structure, c_struct.code, include))

    return include_path, (structure, c_struct.code, include)

  def Generate__xbmc_addons_kodidevkit_src_shared_kodi_ALL_FILES_additional(self, force):
    additional_shared_includes = []
    for entry in self.additional_shared_includes:
      target_file = '{}xbmc/addons/kodi-dev-kit/{}'.format(kodi_dir, entry.replace('#include ', '').replace('"', ''))
      temp_file = target_file.replace('{}xbmc/addons/kodi-dev-kit'.format(kodi_dir), './tmp')

      include = target_file.replace('{}xbmc/addons/kodi-dev-kit/src/shared/api/'.format(kodi_dir), 'include/kodi/c-api/')
      include_path_complete = target_file.replace('src/shared/api/', 'include/kodi/c-api/')

      include_path = ''
      for i in range(include.count('/')):
        include_path += '../'
      include_path += include

      # Check already exist
      if os.path.isfile(temp_file):
        continue

      struct_code = ''
      for struct_name, code, path in self.shared_structures_other_file:
        if not path in target_file or FileContainsInterfaceAPICalls(include_path_complete):
          continue

        current = 0
        used_enums = []
        enums_code = ''
        set_code = ''
        get_code = ''
        clean_code = ''
        clean_function = ''
        code_values = ''
        msgpack = '  MSGPACK_DEFINE('

        previous_entry = ''
        for entry in code:
          if len(entry.split()) > 1:
            m = re.search('^.*?enum\ *([a-zA-Z[0-9_]*)', entry)
            if m and m.group(1) and m.group(1) in known_ENUMS and m.group(1) not in used_enums:
              used_enums.append(m.group(1))

          m = re.search('^\ *([a-zA-Z[0-9_].*)\ ([a-zA-Z[0-9_]+).*\[ *([a-zA-Z[0-9_]+) *\].*\[ *([a-zA-Z[0-9_]+) *\];$', entry)
          if m and m.group(1) and m.group(2) and m.group(3) and m.group(4):
            name = m.group(2)
            is_string = 'char*' in m.group(1)
            is_struct = 'struct ' in m.group(1)
            if is_string:
              value_type = 'std::string'
            elif is_struct:
              print('TODO 1')
              raise
            else:
              value_type = m.group(1)
            code_values += '  std::array<std::array<{}, {}>, {}> {};\n'.format(value_type, m.group(4), m.group(3), m.group(2))
            set_code += '    for (unsigned int i = 0; i < ' + m.group(3) + '; ++i)\n'
            set_code += '    {\n'
            set_code += '      for (unsigned int j = 0; j < ' + m.group(4) + '; ++j)\n'
            set_code += '      {\n'
            set_code += '        ' + m.group(2) + '[i][j] = ' + ('c_data->' + m.group(2) + '[i][j] ? ' if is_string else '') + 'c_data->' + m.group(2) + '[i][j]' +  (' : "";\n' if is_string else ';\n')
            set_code += '      }\n'
            set_code += '    }\n'
            get_code += '    for (unsigned int i = 0; i < ' + m.group(3) + '; ++i)\n'
            get_code += '    {\n'
            get_code += '      for (unsigned int j = 0; j < ' + m.group(4) + '; ++j)\n'
            get_code += '      {\n'
            if is_string:
              get_code += '        if (c_data->' + m.group(2) + '[i][j])\n'
              get_code += '          free(c_data->' + m.group(2) + '[i][j]);\n'
              get_code += '        c_data->' + m.group(2) + '[i][j] = strdup(' + m.group(2) + '[i][j].c_str());\n'
            else:
              get_code += '        c_data->' + m.group(2) + '[i][j] = ' + m.group(2) + '[i][j];\n'
            get_code += '      }\n'
            get_code += '    }\n'
          else:
            m = re.search('^\ *([a-zA-Z[0-9_].*)\ ([a-zA-Z[0-9_]+).*\[ *([a-zA-Z[0-9_]+) *\];$', entry)
            if m and m.group(1) and m.group(2) and m.group(3):
              name = m.group(2)
              is_string = 'char*' in m.group(1)
              is_struct = 'struct ' in m.group(1)
              if is_string:
                value_type = 'std::string'
              elif is_struct:
                struct = m.group(1).replace('struct ', '')
                include = self.ScanStructureInsideAdditional(force, struct, include_path_complete)[0]
                value_type = 'IFC_{}'.format(struct)
                include = '#include "{}"\n'.format(include)
                if not include in additional_shared_includes:
                  additional_shared_includes.append(include)
              else:
                value_type = m.group(1)
              code_values += '  std::array<{}, {}> {};\n'.format(value_type, m.group(3), m.group(2))
              set_code += ('    memcpy({}.data(), c_data->{}, {});\n'
                           .format(m.group(2),
                                   m.group(2),
                                   m.group(3)))
              if is_string:
                get_code += '    for (unsigned int i = 0; i < ' + m.group(3) + '; ++i)\n'
                get_code += '    {\n'
                get_code += '      if (c_data->' + m.group(2) + '[i])\n'
                get_code += '        free(c_data->' + m.group(2) + '[i];\n'
                get_code += '      c_data->' + m.group(2) + '[i] = strdup(' + m.group(2) + '[i].c_str());\n'
                get_code += '    }\n'
              else:
                get_code += ('    memcpy(c_data->{}, {}.data(), {});\n'
                             .format(m.group(2),
                                     m.group(2),
                                     m.group(3)))
            else:
              #print(entry)
              name = entry.rstrip(';').split()[-1].strip()
              value = entry.replace(name, '').replace(';', '').strip()
              if value == 'const char*':
                code_values += '  std::string {};\n'.format(name)
                set_code += '    if (c_data->{})\n'.format(name)
                set_code += '      {} = c_data->{};\n'.format(name, name)
                get_code += '    c_data->{} = {}.c_str();\n'.format(name, name)
              elif value == 'char*':
                code_values += '  std::string {};\n'.format(name)
                set_code += '    if (c_data->{})\n'.format(name)
                set_code += '      {} = c_data->{};\n'.format(name, name)
                get_code += '    if (!{}.empty())\n'.format(name)
                get_code += '      c_data->{} = strdup({}.c_str());\n'.format(name, name)
                clean_code += '    if (c_data->{})\n'.format(name)
                clean_code += '    {\n'
                clean_code += '      free(c_data->{});\n'.format(name)
                clean_code += '      c_data->{} = nullptr;\n'.format(name)
                clean_code += '    }\n'
              elif ContainsHdlVoidPointer(value):
                code_values += '  PtrValue {};\n'.format(name)
                set_code += '    {} = PtrValue(c_data->{});\n'.format(name, name)
                get_code += '    c_data->{} = reinterpret_cast<{}>({});\n'.format(name, value, name)
              elif 'struct ' in value:
                raise
              else:
                code_values += '  {}\n'.format(entry)
                set_code += '    {} = c_data->{};\n'.format(name, name)
                get_code += '    c_data->{} = {};\n'.format(name, name)

          if not current:
            msgpack += name + (',\n' if len(code) > 1 else '')
          else:
            msgpack += '                 ' + name + (',\n' if current < len(code)-1 else '')
          current += 1

          previous_entry = entry

        if not code_values:
          continue

        clean_function = ''
        if clean_code != '':
          clean_function += """\

  static inline void CleanCStructure(""" + struct_name + """* c_data)
  {
    if (c_data == nullptr)
      return;

""" + clean_code + """\
  }
"""

        code = """\
struct IFC_""" + struct_name + """
{
  IFC_""" + struct_name + """() = default;
  IFC_""" + struct_name + """(const """ + struct_name + """* c_data)
  {
    if (c_data == nullptr)
      return;

""" +  set_code + """\
  }
""" + clean_function + """
  void SetCStructure(""" + struct_name + """* c_data)
  {
    if (c_data == nullptr)
      return;

""" +  get_code + """\
  }

""" +  code_values + """
""" + msgpack + """);
};
"""

        struct_code += """\
struct IFC_""" + struct_name + """
{
  IFC_""" + struct_name + """() = default;
  IFC_""" + struct_name + """(const """ + struct_name + """* c_data)
  {
    if (c_data == nullptr)
      return;

""" +  set_code + """\
  }
""" + clean_function + """
  void SetCStructure(""" + struct_name + """* c_data)
  {
    if (c_data == nullptr)
      return;

""" +  get_code + """\
  }

""" +  code_values + """
""" + msgpack + """);
};

"""
        enums_code += '\n' if len(used_enums) > 0 else ''
        for enum in used_enums:
          enums_code += '#ifndef MSGPACK_ADD_ENUM_' + enum + '\n'
          enums_code += '#define MSGPACK_ADD_ENUM_' + enum + '\n'
          enums_code += 'MSGPACK_ADD_ENUM(' + enum + ');\n'
          enums_code += '#endif\n'

        file_text = header_file_copyright + """\

#pragma once

#include "src/shared/SharedGroups.h"
#include \"""" + include_path + """\"
""" + '\n'.join(additional_shared_includes) + """\

#include <string>
#include <string.h>
#include <tuple>
#include <vector>

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_1') + """\
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/
""" + enums_code + """\

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

""" + struct_code + """\
/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_2') + """\
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
"""

        # Make now the creation and copy of file
        os.makedirs(os.path.dirname(temp_file), exist_ok=True)

        f = open(temp_file, "w")
        f.write(file_text)
        f.close()
        os.system('clang-format -style=file -i ' + temp_file)

        if force or not os.path.isfile(target_file) or not filecmp.cmp(target_file, temp_file):
          print('  - Updating ' + target_file)
          os.makedirs(os.path.dirname(target_file), exist_ok=True)
          shutil.copyfile(temp_file, target_file)

  def Generate__xbmc_addons_kodidevkit_src_addon_api_ALL_FILES_CPP(self, force):
    path = self.path.replace('{}xbmc/addons/kodi-dev-kit/'.format(kodi_dir), '')
    include_path = ''
    for i in range(path.count('/')):
      include_path += '../'
    include_path += path

    search_dir = '{}xbmc/addons/kodi-dev-kit/include/kodi/c-api/'.format(kodi_dir)
    target_dir = kodi_dir + 'xbmc/addons/kodi-dev-kit/src/addon/api/'
    target_file = self.path.replace(search_dir, target_dir).replace('.h', '.cpp')

    additional_includes = ''
    for include in self.additional_addon_lib_includes:
      additional_includes += '{}\n'.format(include)

    file_text = header_file_copyright + """
#include \"""" + os.path.basename(self.path) + """\"
""" + additional_includes + """\

// Shared API
#include "src/shared/Instances.h"

// Lib code
#include "core/addon_control.h"

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_1') + """\
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

using namespace KODI::ADDONS::INTERFACE;
using namespace KODI_ADDON::INTERNAL;

namespace KODI_ADDON
{
namespace INTERNAL
{

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_2') + """\
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

""" + self.GenerateToAddonInitDirectFunction()

    if len(self.GetDevKitKodiToAddonHeaderPart()) > 0:
      file_text += '\n'
      file_text += '#ifndef KODI_INHIBIT_SHARED\n'
      file_text += 'bool CHdl_kodi_{}::HandleMessage(int funcGroup,\n'.format(self.header_group_id)
      spaces = MakeSpaces('bool CHdl_kodi_' + self.header_group_id + '::HandleMessage')
      file_text += spaces + 'int func,\n'
      file_text += spaces + 'const msgpack::unpacked& in,\n'
      file_text += spaces + 'msgpack::sbuffer& out)\n'
      file_text += '{\n'
      file_text += '  if (funcGroup != funcGroup_{})\n'.format(self.header_group_id)
      file_text += '    return false;\n'
      file_text += '\n'
      file_text += '  switch (func)\n'
      file_text += '  {\n'
      if not self.override_use_direct_api_only:
        for data in self.interface_data_to_addon:
          file_text += data.child_addon_c_lib_function_switch_case
      else:
        file_text += '    /* NOTE: Ignored as direct api only is set! */\n'
      file_text += '    default:\n'
      file_text += '      break;\n'
      file_text += '  }\n'
      file_text += '  return false;\n'
      file_text += '}\n'
      file_text += '#endif /* !KODI_INHIBIT_SHARED */\n'

    file_text += """
/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_3') + """\
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3_END>---*/

""" + self.GetDevKitKodiToAddonSourcePart() + """\

} /* namespace INTERNAL */
} /* namespace KODI_ADDON */
"""

    for data in self.interface_data_to_kodi:
      file_text += '\n'
      file_text += data.parent_addon_c_lib_function_shared

    file_text += """
/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_4>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_4') + """\
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_4_END>---*/
"""

    # Make now the creation and copy of file
    temp_file = target_file.replace('../../../../../xbmc/addons', './tmp')
    os.makedirs(os.path.dirname(temp_file), exist_ok=True)

    f = open(temp_file, "w")
    f.write(file_text)
    f.close()
    os.system('clang-format -style=file -i ' + temp_file)

    if force or not filecmp.cmp(target_file, temp_file):
      print('  - Updating ' + target_file)
      os.makedirs(os.path.dirname(target_file), exist_ok=True)
      shutil.copyfile(temp_file, target_file)

    return file_text

  def Generate__xbmc_addons_kodidevkit_src_addon_api_ALL_FILES_H(self, force):
    path = self.path.replace('{}xbmc/addons/kodi-dev-kit/'.format(kodi_dir), '')

    search_dir = '{}xbmc/addons/kodi-dev-kit/include/kodi/c-api/'.format(kodi_dir)
    target_dir = kodi_dir + 'xbmc/addons/kodi-dev-kit/src/addon/api/'
    target_file = self.path.replace(search_dir, target_dir)

    if len(self.GetDevKitKodiToAddonHeaderPart()) > 0:
      handle_message = """\
#ifndef KODI_INHIBIT_SHARED
  bool HandleMessage(int funcGroup,
                     int func,
                     const msgpack::unpacked& in,
                     msgpack::sbuffer& out) override;
#endif /* !KODI_INHIBIT_SHARED */

"""
      callbacks = '\n'
      callbacks += '  // Calls from Kodi to addon\n'
      callbacks += self.GetDevKitKodiToAddonHeaderPart()
    else:
      handle_message = ''
      callbacks = ''

    file_text = header_file_copyright + """
#pragma once

#include "core/IMsgHdl.h"
#include "src/shared/api/""" + target_file.replace(target_dir, '').replace('.cpp', '.h')  + """"

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_1') + """\
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

struct directFuncToAddon_""" + self.header_group_id + """;
struct directFuncToKodi_""" + self.header_group_id + """;

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */

namespace KODI_ADDON
{
namespace INTERNAL
{

class ATTR_DLL_LOCAL CHdl_kodi_""" + self.header_group_id + """ : public IMsgHdl
{
public:
  CHdl_kodi_""" + self.header_group_id + """(AddonIfc* ifc) : IMsgHdl(ifc) {}

  void InitDirect(KODI::ADDONS::INTERFACE::directFuncToAddon_""" + self.header_group_id + """* ifcToAddon);

""" + handle_message + """\
  /* Code below becomes on auto generation reused, hand edited parts should included here */
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_2') + """\
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/
""" + callbacks + """\
};

} /* namespace INTERNAL */
} /* namespace KODI_ADDON */
"""

    # Make now the creation and copy of file
    temp_file = target_file.replace('../../../../../xbmc/addons', './tmp')
    os.makedirs(os.path.dirname(temp_file), exist_ok=True)

    f = open(temp_file, "w")
    f.write(file_text)
    f.close()
    os.system('clang-format -style=file -i ' + temp_file)

    if force or not filecmp.cmp(target_file, temp_file):
      print('  - Updating ' + target_file)
      os.makedirs(os.path.dirname(target_file), exist_ok=True)
      shutil.copyfile(temp_file, target_file)

    return file_text

  #-------------------------------------------------------------------------------------------------

  def Generate__xbmc_addons_interface_api_ALL_FILES_CPP(self, force):
    path = self.path.replace('{}xbmc/addons/kodi-dev-kit/'.format(kodi_dir), '')

    search_dir = '{}xbmc/addons/kodi-dev-kit/include/kodi/c-api/'.format(kodi_dir)
    target_dir = '{}xbmc/addons/interface/api/'.format(kodi_dir)
    target_file = self.path.replace(search_dir, target_dir).replace('.h', '.cpp')

    function_name = 'bool CHdl_kodi_{}::HandleMessage'.format(self.header_group_id)

    file_text = header_file_copyright + """
#include \"""" + os.path.basename(self.path) + """\"

// Shared API
#include \"addons/kodi-dev-kit/""" + path.replace('include/kodi/c-api/', 'src/shared/api/') + """\"

// Kodi
#include "addons/interface/RunningProcess.h"
#include "utils/log.h"
"""
    for include in self.kodi_ifc_includes:
      file_text += '#include "{}"\n'.format(include)

    file_text += """\

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_1') + """\
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_2') + """\
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

""" + self.GenerateToKodiInitDirectFunction() + """\

""" + function_name + """(int funcGroup,
"""
    spaces = MakeSpaces(function_name)
    file_text += '{}int func,\n'.format(spaces)
    file_text += '{}const msgpack::unpacked& in,\n'.format(spaces)
    file_text += '{}msgpack::sbuffer& out)\n'.format(spaces)
    file_text += """\
{
  if (funcGroup != funcGroup_""" + self.header_group_id + """)
    return false;

  switch (func)
  {
""" + self.GetKodiSwitchCase() + """\
    default:
      CLog::Log(LOGERROR,
                "CHdl_kodi_""" + self.header_group_id + """::{}: addon called with unknown function id '{}' on group '""" + self.header_group_id + """'",
                __func__, func);
  }

  return false;
}

// Function calls from Kodi to addon
""" + self.GetKodiSourcePartChild() + """
// Callbacks from addon to Kodi
""" + self.GetKodiSourcePart() + """
/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_3') + """\
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3_END>---*/

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
"""

    # Make now the creation and copy of file
    temp_file = target_file.replace('../../../../../xbmc/addons', './tmp')
    os.makedirs(os.path.dirname(temp_file), exist_ok=True)

    f = open(temp_file, "w")
    f.write(file_text)
    f.close()
    os.system('clang-format -style=file -i ' + temp_file)

    if force or not filecmp.cmp(target_file, temp_file):
      print('  - Updating ' + target_file)
      os.makedirs(os.path.dirname(target_file), exist_ok=True)
      shutil.copyfile(temp_file, target_file)

    return file_text

  #-------------------------------------------------------------------------------------------------

  def Generate__xbmc_addons_interface_api_ALL_FILES_H(self, force):
    path = self.path.replace('{}xbmc/addons/kodi-dev-kit/'.format(kodi_dir), '')

    search_dir = '{}xbmc/addons/kodi-dev-kit/include/kodi/c-api/'.format(kodi_dir)
    target_dir = '{}xbmc/addons/interface/api/'.format(kodi_dir)
    target_file = self.path.replace(search_dir, target_dir)

    file_text = header_file_copyright + """
#pragma once

#include "addons/interface/IMsgHdl.h"

// API include
#include \"addons/kodi-dev-kit/""" + path + """\"

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_1') + """\
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

struct directFuncToAddon_""" + self.header_group_id + """;
struct directFuncToKodi_""" + self.header_group_id + """;

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_2') + """\
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

class CHdl_kodi_""" + self.header_group_id + """ : public IMsgHdl
{
public:
  CHdl_kodi_""" + self.header_group_id + """(CInterface& interface) : IMsgHdl(interface) { }

  void InitDirect(directFuncToKodi_""" + self.header_group_id + """* ifcToKodi,
                  directFuncToAddon_""" + self.header_group_id + """* ifcToAddon);

  // To handle callbacks from addon by shared sandbox API (static functions below in private becomes used)
  bool HandleMessage(int funcGroup,
                     int func,
                     const msgpack::unpacked& in,
                     msgpack::sbuffer& out) override;

  /* Code below becomes on auto generation reused, hand edited parts should included here */
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_3') + """\
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3_END>---*/

  // Function calls from Kodi to addon
""" + self.GetKodiChildHeaderPart() + """\

private:
  /* Code below becomes on auto generation reused, hand edited parts should included here */
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_4>---*/
""" + CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_4') + """\
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_4_END>---*/

  // Callbacks from addon to Kodi
""" + self.GetKodiParentHeaderPart() + """\

  directFuncToAddon_""" + self.header_group_id + """* m_ifcToAddon{nullptr};
};

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
"""

    # Make now the creation and copy of file
    temp_file = target_file.replace('../../../../../xbmc/addons', './tmp')
    os.makedirs(os.path.dirname(temp_file), exist_ok=True)

    f = open(temp_file, "w")
    f.write(file_text)
    f.close()
    os.system('clang-format -style=file -i ' + temp_file)

    if force or not filecmp.cmp(target_file, temp_file):
      print('  - Updating ' + target_file)
      os.makedirs(os.path.dirname(target_file), exist_ok=True)
      shutil.copyfile(temp_file, target_file)

    return file_text


#===============================================================================

class InterfaceDataParent:
  def __init__(self, callbacks, options):
    self.callbacks = callbacks
    self.options = options

    self.use_internal_only = False
    self.header_group_id = ''
    self.function_complete = ''
    self.retval = ''
    self.funcname = ''
    self.funcname_ifc = ''
    self.values = []
    self.api_added = -1
    self.api_deprecated = -1

    self.parent_addon_c_lib_function_shared = ''
    self.parent_addon_c_lib_function_shared_tuple_in = ''
    self.parent_addon_c_lib_function_shared_tuple_in_list = []
    self.parent_addon_c_lib_function_shared_tuple_out = ''
    self.parent_addon_c_lib_function_shared_tuple_out_list = []
    self.parent_addon_c_lib_function_direct = ''
    self.parent_addon_c_lib_function_direct_ptr = ''
    self.parent_kodi_cpp_function_switch_case = ''
    self.parent_kodi_cpp_function_source = ''
    self.parent_kodi_cpp_function_header = ''

    self.group_data = None # The Parent class GroupData
    self.search_dir = '{}xbmc/addons/kodi-dev-kit/include/kodi/c-api/'.format(kodi_dir)

  def RegexScanFunction(self, function):
    regex_code = '^(?:[ \t]*)?ATTR_DLL_EXPORT[ \t]*(.*)[ \t](kodi.+?)(?=\()\((.*?)(?=\);|\). *__).+?(?:__(DEPRECATED|INTRODUCED)_IN_KODI\(([0-9]+)\))?.(?:__(DEPRECATED|INTRODUCED)_IN_KODI\(([0-9]+)\))(?:[ \t]*);$'
    m = re.search(regex_code, function)
    if not m or not m.group(1) or not m.group(2) or not m.group(3) and not m.group(4) and not m.group(6):
      if not function.startswith('#define'):
        print('ERROR: Function \'' + function + '\' not match wanted API!')
      return False
      #raise

    self.retval = m.group(1)
    self.funcname = m.group(2)
    self.values = []
    for value in m.group(3).split(', '):
      if value.strip() != '':
        self.values.append(value.strip())

    self.api_added = -1
    self.api_deprecated = -1
    if m.group(4) and m.group(4) == 'INTRODUCED':
      self.api_added = int(m.group(5))
    elif m.group(4) and m.group(4) == 'DEPRECATED':
      self.api_deprecated = int(m.group(5))
    if m.group(6) and m.group(6) == 'INTRODUCED':
      self.api_added = int(m.group(7))
    elif m.group(6) and m.group(6) == 'DEPRECATED':
      self.api_deprecated = int(m.group(7))

    self.funcname_ifc = '{}_v{}'.format(self.funcname, self.api_added)
    return True

  def ContainsOutOnIn(self):
    for value in self.values:
      if not 'const' in value and ('*' in value or '[' in value):
        return True
    return False

  def GenerateSharedTuples(self, file_text):
    class CheckAPIUse:
      def __init__(self, parent, cnt, value, value_list):
        self.parent = parent
        self.cnt = cnt
        self.value = value
        self.done = False

        check_error = CheckCorrectFunctionValue(value)
        if check_error:
          print('FATAL: Function "{}" not contains valid values (ERROR: {})'.format(parent.function_complete, check_error))
          raise

        self.value_name = value.split()[-1].strip()
        self.value_type = value[:-len(self.value_name)].strip()

        self.msgpack_in_value = ''
        self.msgpack_out_value = ''
        self.function_value = ''

        if '...' in self.value:
          self.msgpack_in_value = ''
          self.msgpack_out_value = ''
          self.done = True
          return

        m = re.search('^[\t ]*(?:const[\t ]*)?([a-zA-Z0-9_]*)[\t ]*\*[\t ]*(?:const[\t ]*)?\*', self.value)
        if m and m.group(1) and m.group(1) in known_STANDARD_C_TYPES and 'size_t' in value_list[cnt+1] and 'size_t' in value_list[cnt+2]:
          if 'const ' in self.value or 'const*' in self.value:
            self.msgpack_in_value = 'std::vector<std::vector<{}>>'.format(m.group(1))
            self.msgpack_out_value = ''
            self.done = True
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataParent::GenerateSharedTuples'.format(parent.function_complete))
            raise
          return

        # Fixed array way 1 e.g. "enum AudioEngineChannel info[][AUDIOENGINE_CH_MAX]"
        m = re.search('^((?:const{1,}))(?:[\t ]*)?(.*)\ ([a-z0-9A-Z_]*?)(?!\*)?\[([a-z0-9A-Z_]*?)\]\[([a-z0-9A-Z_]*?)\]$', value)
        if m and m.group(2) and m.group(3) and not m.group(4) and m.group(5):
          self.value_type = m.group(2).strip()
          used_type = ''
          if self.value_type == 'char':
            used_type = 'std::array<std::string, {}>'.format(m.group(5))
          elif self.value_type.startswith('struct ') and self.value_type.count('*') == 1 and parent.group_data.GenerateSharedStructure(self.value_type):
            used_type = 'std::array<IFC_{}, {}>'.format(self.value_type.replace('struct ', '').replace('*', ''), m.group(5))
          elif CheckKnownEnum(self.value_type):
            self.value_type = self.value_type.replace('enum ', '')
            if self.value_type.replace('*', '') not in parent.group_data.used_enums:
              parent.group_data.used_enums.append(self.value_type.replace('*', ''))
            used_type = 'std::array<{}, {}>'.format(self.value_type.replace('enum ', '').replace('*', ''), m.group(5))
          else:
            used_type = 'std::array<{}, {}>'.format(self.value_type, m.group(5))

          if m.group(1):
            self.msgpack_in_value = used_type
            self.msgpack_out_value = ''
          else:
            self.msgpack_in_value = ''
            self.msgpack_out_value = used_type
          self.done = True
          return

        # Fixed array way 2 e.g. "enum AudioEngineChannel (*info)[AUDIOENGINE_CH_MAX]"
        m = re.search('^((?:const{1,}))(?:[\t ]*)?(.*)\ ?(.*)\ \(\*([a-z0-9A-Z_]*?)\)\[([a-z0-9A-Z_]*?)\]$', value)
        if m and m.group(2) and m.group(3) and m.group(4):
          self.value_type = m.group(2).strip()
          used_type = ''
          if self.value_type == 'char':
            used_type = 'std::array<std::string, {}>'.format(m.group(5))
          elif self.value_type.startswith('struct ') and self.value_type.count('*') == 1 and parent.group_data.GenerateSharedStructure(self.value_type):
            used_type = 'std::array<IFC_{}, {}>'.format(self.value_type.replace('struct ', '').replace('*', ''), m.group(4))
          elif CheckKnownEnum(self.value_type):
            self.value_type = self.value_type.replace('enum ', '')
            if self.value_type.replace('*', '') not in parent.group_data.used_enums:
              parent.group_data.used_enums.append(self.value_type.replace('*', ''))
            used_type = 'std::array<{}, {}>'.format(self.value_type.replace('enum ', '').replace('*', ''), m.group(4))
          else:
            used_type = 'std::array<{}, {}>'.format(self.value_type, m.group(4))

          if m.group(1):
            self.msgpack_in_value = used_type
            self.msgpack_out_value = ''
          else:
            self.msgpack_in_value = ''
            self.msgpack_out_value = used_type
          self.done = True
          return

        # Fixed array way 3 e.g. "enum AudioEngineChannel info[AUDIOENGINE_CH_MAX]"
        m = re.search('^((?:const{1,}))\ ?(.*)\ ([a-z0-9A-Z_]*?)\[([a-z0-9A-Z_]*?)\]$', value)
        if m and m.group(2) and m.group(3) and m.group(4):
          self.value_type = m.group(2).strip()
          used_type = ''
          if self.value_type == 'char':
            used_type = 'std::array<std::string, {}>'.format(m.group(5))
          elif self.value_type.startswith('struct ') and self.value_type.count('*') == 1 and parent.group_data.GenerateSharedStructure(self.value_type):
            used_type = 'std::array<IFC_{}, {}>'.format(self.value_type.replace('struct ', '').replace('*', ''), m.group(4))
          elif CheckKnownEnum(self.value_type):
            self.value_type = self.value_type.replace('enum ', '')
            if self.value_type.replace('*', '') not in parent.group_data.used_enums:
              parent.group_data.used_enums.append(self.value_type.replace('*', ''))
            used_type = 'std::array<{}, {}>'.format(self.value_type.replace('enum ', '').replace('*', ''), m.group(4))
          else:
            used_type = 'std::array<{}, {}>'.format(self.value_type, m.group(4))

          if m.group(1):
            self.msgpack_in_value = used_type
            self.msgpack_out_value = ''
          else:
            self.msgpack_in_value = ''
            self.msgpack_out_value = used_type
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_6 (tuple) (parent)
        if self.value_type == 'const char*':
          if '[]' in self.value_name and self.value_name.count('[]') == 1:
            if len(value_list) > 1:
              i = 0
              while i+cnt < len(value_list)-1:
                if 'size_t' in value_list[i+cnt+1]:
                  self.msgpack_in_value = ('std::vector<std::string>{}'
                                          .format(' /* CheckAPIUse_WAY_6b (0006) */' if parent.options.debug else ''))
                  self.msgpack_out_value = ''
                  self.done = True
                  break
                if '[]' in value_list[i+cnt+1] and value_list[i+cnt+1].count('[]') == 1:
                  i += 1
                  continue

                print('FATAL (6b, 0006): Function:')
                print('       "{}"'.format(parent.function_complete))
                print('       Not supported on InterfaceDataParent::GenerateSharedTuples!')
                print('       Need to set second value of "{}" as "size_t".'.format(self.value))
                exit(1)
          else:
            self.msgpack_in_value = ('std::string{}'
                                     .format(' /* CheckAPIUse_WAY_6a (0006) */' if parent.options.debug else ''))
            self.msgpack_out_value = ''
            self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_7 (tuple) (parent)
        if self.value_type == 'char**':
          self.msgpack_in_value = ''
          self.msgpack_out_value = 'std::string'
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_8_1 (tuple) (parent)
        if self.value_type == 'char***' \
           or (self.value_type == 'char**' \
               and '[]' in self.value_name \
               and self.value_name.count('[]') == 1):
          if len(value_list) > 1 \
              and cnt < len(value_list)-1 \
              and 'size_t*' in value_list[cnt+1]:
            self.msgpack_in_value = ''
            self.msgpack_out_value = ('std::vector<std::string>{}'
                                       .format(' /* CheckAPIUse_WAY_8_1 (0006) */' if parent.options.debug else ''))
            self.done = True
          else:
            print('FATAL: Function:')
            print('       "{}"'.format(parent.function_complete))
            print('       Not supported on InterfaceDataParent::GenerateSharedTuples!')
            print('       Need to set second value of "{}" as "size_t".'.format(self.value))
            exit(1)
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_8 - For msgParent__IN/OUT_ on kodi-dev-kit/src/shared/api
        if self.value_type == 'char*' \
           and 'size_t' in value_list[cnt+1]:
          self.msgpack_in_value = ''
          self.msgpack_out_value = 'std::string'
          self.done = True
          return

        # CheckAPIUse_WAY_9
        if self.value_type in known_STANDARD_C_PTR_TYPES \
           and cnt < len(value_list)-1 \
           and 'size_t' in value_list[cnt+1]:
          self.msgpack_in_value = ''
          self.msgpack_out_value = ('std::vector<{}>{}'
                                    .format(self.value_type.replace('*', ''),
                                            ' /* CheckAPIUse_WAY_9 (0006) */' if parent.options.debug else ''))
          self.done = True
          return

        # CheckAPIUse_WAY_10
        if self.value_type in known_STANDARD_C_TYPES \
           and '[]' in self.value_name \
           and self.value_name.count('[]') == 1 \
           and cnt < len(value_list)-1 \
           and 'size_t' in value_list[cnt+1]:
          self.msgpack_in_value = ('std::vector<{}>{}'
                                    .format(self.value_type,
                                            ' /* CheckAPIUse_WAY_10 (0006) */' if parent.options.debug else ''))
          self.msgpack_out_value = ('std::vector<{}>{}'
                                    .format(self.value_type,
                                            ' /* CheckAPIUse_WAY_10 (0006) */' if parent.options.debug else ''))
          self.done = True
          return

        # CheckAPIUse_WAY_11
        if self.value_type in known_STANDARD_C_TYPES:
          self.msgpack_in_value = ('{}{}'
                                   .format(self.value_type,
                                           ' /* CheckAPIUse_WAY_11 (0006) */' if parent.options.debug else ''))
          self.msgpack_out_value = ''
          self.done = True
          return

        if ContainsHdlVoidPointer(self.value_type):
          self.msgpack_in_value = 'PtrValue'
          self.msgpack_out_value = ''
          self.done = True
          return

        if self.value_type.replace('const ', '') in known_STANDARD_C_PTR_TYPES \
           and cnt < len(value_list)-1 \
           and 'size_t' in value_list[cnt+1]:
          self.msgpack_in_value = ('std::vector<{}>{}'
                                   .format(self.value_type.replace('*', '').replace('const ', ''),
                                           ' /* CheckAPIUse_WAY_11 (0006) */' if parent.options.debug else ''))
          self.msgpack_out_value = ''
          self.done = True
          return

        if self.value_type in known_STANDARD_C_PTR_TYPES:
          self.msgpack_in_value = self.value_type.replace('*', '')
          self.msgpack_out_value = self.value_type.replace('*', '')
          self.done = True
          return

        if CheckKnownEnum(self.value_type):
          self.value_type = self.value_type.replace('enum ', '')
          if self.value_type.replace('*', '') not in parent.group_data.used_enums:
            parent.group_data.used_enums.append(self.value_type.replace('*', ''))

          if not '*' in self.value_type:
            self.msgpack_in_value = self.value_type
          elif '*' in self.value_type and self.value_type.count('*') == 1 and not 'const' in self.value_type:
            value = self.value_type.replace('*', '')
            self.msgpack_in_value = value
            self.msgpack_out_value = value
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataParent::GenerateSharedTuples'.format(parent.function_complete))
            raise
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_15 - For msgParent__IN/OUT_ on kodi-dev-kit/src/shared/api
        if self.value_type.startswith('struct ') \
           and self.value_type.count('*') == 1 \
           and parent.group_data.GenerateSharedStructure(self.value_type):
          value_type = self.value_type.replace('struct ', '').replace('*', '').strip()
          if value_type == 'tm':
            self.msgpack_in_value = 'IFC_{}'.format(value_type)
          else:
            self.msgpack_in_value = ''
          self.msgpack_out_value = 'IFC_{}'.format(value_type)
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_16 - For msgParent__IN/OUT_ on kodi-dev-kit/src/shared/api
        if self.value_type.startswith('const struct ') and self.value_type.count('*') == 1 and parent.group_data.GenerateSharedStructure(self.value_type):
          self.msgpack_in_value = 'IFC_{}'.format(self.value_type.replace('const struct ', '').replace('*', '').strip())
          self.msgpack_out_value = ''
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_17 - For msgParent__IN/OUT_ on kodi-dev-kit/src/shared/api
        if self.value_type.startswith('struct ') \
              and self.value_type.count('*') == 2 \
              and 'size_t*' in value_list[cnt+1] \
              and parent.group_data.GenerateSharedStructure(self.value_type):
          self.msgpack_in_value = ''
          self.msgpack_out_value = 'std::vector<IFC_{}>'.format(self.value_type.replace('struct ', '').replace('*', '').strip())
          self.done = True
          return

        self.done = False

    if self.group_data.override_use_direct_api_only:
      return True

    if '---AUTO_GEN_PARSE<OVERRIDE;USE_INTERNAL={}>---'.format(self.funcname) in file_text:
      self.parent_addon_c_lib_function_shared_tuple_in = '/* NOTE: msgParent__IN_{} - Override active to use inside dev-kit library only */'.format(self.funcname)
      self.parent_addon_c_lib_function_shared_tuple_out = '/* NOTE: msgParent_OUT_{} - Override active to use inside dev-kit library only */'.format(self.funcname)
      self.use_internal_only = True
      return True

    haveIn = len(self.values) != 0
    haveOut = self.ContainsOutOnIn() or self.retval != 'void'

    cnt = 0
    tuple_in_values = ''
    tuple_out_values = ''
    api_use_list = []
    for value in self.values:
      apiUse = CheckAPIUse(self, cnt, value, self.values)
      api_use_list.append(apiUse)
      cnt += 1

      if apiUse.done:
        tuple_in_values += apiUse.msgpack_in_value + (', ' if apiUse.msgpack_in_value else '')
        tuple_out_values += apiUse.msgpack_out_value + (', ' if apiUse.msgpack_out_value else '')
      else:
        tuple_in_values += 'NEED_TODO_VALUES33('+value+')' + (', ' if apiUse.msgpack_in_value else '')
        tuple_out_values += '????NEED_TODO_VALUES!!!!' + (', ' if apiUse.msgpack_in_value else '')

    while tuple_in_values.endswith(', '):
      tuple_in_values = tuple_in_values[:-2]
    while tuple_out_values.endswith(', '):
      tuple_out_values = tuple_out_values[:-2]

    tuple_in = 'typedef std::tuple<'
    tuple_out = 'typedef std::tuple<'

    ret_value = ''
    if self.retval == 'char*':
      ret_value += 'std::string'
    elif self.retval in known_STANDARD_C_TYPES:
      ret_value += self.retval
    elif self.retval in known_VOID_PTR_DEFINES:
      ret_value += 'PtrValue'
    elif CheckKnownEnum(self.retval) and self.retval.count('*') == 0:
      ret_value += self.retval.replace('enum ', '')
    elif self.retval == 'char**' \
          and len(self.values) > 0 \
          and api_use_list[-1].value_type == 'size_t*' \
          and (not api_use_list[-2].value_type in known_STANDARD_C_PTR_TYPES if len(self.values) > 1 else True):
      ret_value += 'std::vector<std::string>'
    elif self.retval != 'void':
      ret_value += 'NEED_TODO_VALUES23'

    if ret_value:
      self.parent_addon_c_lib_function_shared_tuple_out_list.append(ret_value)
      tuple_out += ret_value

    if self.ContainsOutOnIn():
      tuple_out += (', ' if ret_value else '')

    self.parent_addon_c_lib_function_shared_tuple_in_list = tuple_in_values.split(', ') if tuple_in_values != '' else []
    self.parent_addon_c_lib_function_shared_tuple_out_list = tuple_out_values.split(', ') if tuple_out_values != '' else []

    tuple_in += tuple_in_values
    if tuple_in == 'typedef std::tuple<':
      tuple_in += 'DummyValue'
    tuple_out += tuple_out_values
    if tuple_out == 'typedef std::tuple<':
      tuple_out += 'DummyValue'

    tuple_in += '> msgParent__IN_' + self.funcname_ifc + ('; /* Autogenerated */' if not 'NEED_TODO_VALUES' in tuple_in else '; /* Need hand edit here, remove this note text after change! */')
    tuple_out += '> msgParent_OUT_' + self.funcname_ifc + ('; /* Autogenerated */' if not 'NEED_TODO_VALUES' in tuple_out else '; /* Need hand edit here, remove this note text after change! */')

    self.parent_addon_c_lib_function_shared_tuple_in = tuple_in
    self.parent_addon_c_lib_function_shared_tuple_out = tuple_out

    return True

  def GenerateToKodiDirectFuncTable(self, file_text):
    if '---AUTO_GEN_PARSE<OVERRIDE;USE_INTERNAL={}>---'.format(self.funcname) in file_text:
      self.group_data.to_kodi_direct_func_table.append('  /* Function "{}" only used inside dev-kit library only */'.format(self.funcname))
      return True

    func_values = ''
    current_value = 1
    for value in self.values:
      if value != '...':
        value_name = value.split()[-1].strip()
        value_type = value[:-len(value_name)].strip()
        if '[' in value_name:
          value_type += '[' + value_name.split('[', 1)[-1]
      else:
        value_name = ''
        value_type = '...'

      func_values += value_type + (', ' if current_value < len(self.values) else '')
      current_value += 1

    entry = ('typedef {}(ATTR_INT_APIENTRYP PFN_INT_{}_V{})(void*{});'
              .format(self.retval,
                      self.funcname.upper(),
                      self.api_added,
                      ', ' + func_values if len(func_values) > 0 else ''))
    self.group_data.to_kodi_api_list_typedef.append(entry)

    entry = ('  PFN_INT_{}_V{} {};'
              .format(self.funcname.upper(),
                      self.api_added,
                      self.funcname_ifc))
    self.group_data.to_kodi_direct_func_table.append(entry)

    return True


  def GenerateAddonSourceCFunctionDirectFuncPtr(self):
    code = '  typedef ' + self.retval + '(ATTR_APIENTRYP PFN_CB_' + self.funcname.upper() + '_V' + str(self.api_added) + ')(void*, '
    current_value = 0
    for value in self.values:
      if value == '...' or value == '': # TODO
        continue

      code += value.replace(value.split()[-1], '').strip()
      current_value += 1
      if current_value < len(self.values):
        code += ', '
    if code.endswith(', '):
      code = code[:-2]
    code += ');\n'

    self.parent_addon_c_lib_function_direct_ptr = code

    return True

  # Log ID: 0003
  def GenerateAddonSourceCFunctionSharedCode(self, code, file_text):
    class CheckAPIUse:
      def __init__(self, parent, cnt_in, cnt_out, value, value_list, ignored_count):
        self.parent = parent
        self.cnt_in = cnt_in
        self.cnt_out = cnt_out
        self.value = value
        self.additional_code_1 = ''
        self.additional_code_2 = ''
        self.additional_code_3 = ''
        self.additional_code_4 = ''
        self.ignore_next = True
        self.ignored_count = ignored_count
        self.done = False

        self.value_name = value.split()[-1].strip()
        self.value_type = value[:-len(self.value_name)].strip()

        self.msgpack_in_value = ''
        self.msgpack_out_value = ''
        self.function_value = ''

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_1
        if '...' in self.value:
          if cnt_in > 0 and len(value_list) > 1 and 'const char*' in value_list[cnt_in-1]:
            parent.group_data.AddAdditionalAddonLibIncludes('#include "include/kodi/tools/StringUtils.h"')
            name_before = value_list[cnt_in-1].split()[-1].strip()
            self.additional_code_1  = '  va_list args;{}\n'.format(' /* CheckAPIUse_WAY_1 (0003) */' if parent.options.debug else '')
            self.additional_code_1 += '  va_start(args, {});{}\n'.format(name_before, ' /* CheckAPIUse_WAY_1 (0003) */' if parent.options.debug else '')
            self.additional_code_1 += '  const std::string cpp_{} = kodi::tools::StringUtils::FormatV({}, args);{}\n'.format(name_before, name_before, ' /* CheckAPIUse_WAY_1 (0003) */' if parent.options.debug else '')
            self.additional_code_1 += '  va_end(args);{}\n'.format(' /* CheckAPIUse_WAY_1 (0003) */' if parent.options.debug else '')

            self.msgpack_in_value = ''
            self.msgpack_out_value = ''
            self.done = True
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataParent::GenerateAddonSourceCFunctionSharedCode'.format(parent.function_complete))
            raise
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_2
        m = re.search('^[\t ]*(?:const[\t ]*)?([a-zA-Z0-9_]*)[\t ]*\*[\t ]*(?:const[\t ]*)?\*', self.value)
        if m and m.group(1) and m.group(1) in known_STANDARD_C_TYPES and 'size_t' in value_list[cnt_in+1] and 'size_t' in value_list[cnt_in+2]:
          if 'const ' in self.value or 'const*' in self.value:
            size_1_name = value_list[cnt_in+1].split()[-1].strip()
            size_2_name = value_list[cnt_in+2].split()[-1].strip()
            self.additional_code_1  = '  std::vector<std::vector<{}>> ifc_{};{}\n'.format(m.group(1), self.value_name, ' /* CheckAPIUse_WAY_2 (0003) */' if parent.options.debug else '')
            self.additional_code_1 += '  ifc_{}.resize({});{}\n'.format(self.value_name, size_1_name, ' /* CheckAPIUse_WAY_2 (0003) */' if parent.options.debug else '')
            self.additional_code_1 += '  for (size_t i = 0; i < {}; ++i){}\n'.format(size_1_name, ' /* CheckAPIUse_WAY_2 (0003) */' if parent.options.debug else '')
            self.additional_code_1 += '    ifc_{}[i] = std::vector<{}>({}[i], {}[i] + {});{}\n'.format(self.value_name, m.group(1), self.value_name, self.value_name, size_2_name, ' /* CheckAPIUse_WAY_2 (0003) */' if parent.options.debug else '')
            self.msgpack_in_value = 'ifc_{}{}'.format(self.value_name, ' /* CheckAPIUse_WAY_2 (0003) */' if parent.options.debug else '')
            self.msgpack_out_value = ''
            self.done = True
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataParent::GenerateAddonSourceCFunctionSharedCode'.format(parent.function_complete))
            raise
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_3
        # Fixed array way 1 e.g. "enum AudioEngineChannel info[][AUDIOENGINE_CH_MAX]"
        m = re.search('^((?:const{1,}))(?:[\t ]*)?(.*)\ ([a-z0-9A-Z_]*?)(?!\*)?\[([a-z0-9A-Z_]*?)\]\[([a-z0-9A-Z_]*?)\]$', value)
        if m and m.group(2) and m.group(3) and not m.group(4) and m.group(5):
          self.value_type = m.group(2).strip()
          used_type = ''
          if self.value_type == 'char':
            used_type = 'std::array<std::string, {}>'.format(m.group(5))
          elif self.value_type.startswith('struct ') and self.value_type.count('*') == 1 and parent.group_data.GenerateSharedStructure(self.value_type):
            used_type = 'std::array<IFC_{}, {}>'.format(self.value_type.replace('struct ', '').replace('*', ''), m.group(5))
          elif CheckKnownEnum(self.value_type):
            self.value_type = self.value_type.replace('enum ', '')
            if self.value_type.replace('*', '') not in parent.group_data.used_enums:
              parent.group_data.used_enums.append(self.value_type.replace('*', ''))
            used_type = 'std::array<{}, {}>'.format(self.value_type.replace('enum ', '').replace('*', ''), m.group(5))
          else:
            used_type = 'std::array<{}, {}>'.format(self.value_type, m.group(5))

          if m.group(1):
            self.msgpack_in_value = used_type
            self.msgpack_out_value = ''
          else:
            self.msgpack_in_value = ''
            self.msgpack_out_value = used_type
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_4
        # Fixed array way 2 e.g. "enum AudioEngineChannel (*info)[AUDIOENGINE_CH_MAX]"
        m = re.search('^((?:const{1,}))(?:[\t ]*)?(.*)\ ?(.*)\ \(\*([a-z0-9A-Z_]*?)\)\[([a-z0-9A-Z_]*?)\]$', value)
        if m and m.group(2) and m.group(3) and m.group(4):
          self.value_type = m.group(2).strip()
          used_type = ''
          if self.value_type == 'char':
            used_type = 'std::array<std::string, {}>'.format(m.group(5))
          elif self.value_type.startswith('struct ') and self.value_type.count('*') == 1 and parent.group_data.GenerateSharedStructure(self.value_type):
            used_type = 'std::array<IFC_{}, {}>'.format(self.value_type.replace('struct ', '').replace('*', ''), m.group(4))
          elif CheckKnownEnum(self.value_type):
            self.value_type = self.value_type.replace('enum ', '')
            if self.value_type.replace('*', '') not in parent.group_data.used_enums:
              parent.group_data.used_enums.append(self.value_type.replace('*', ''))
            used_type = 'std::array<{}, {}>'.format(self.value_type.replace('enum ', '').replace('*', ''), m.group(4))
          else:
            used_type = 'std::array<{}, {}>'.format(self.value_type, m.group(4))

          if m.group(1):
            self.msgpack_in_value = used_type
            self.msgpack_out_value = ''
          else:
            self.msgpack_in_value = ''
            self.msgpack_out_value = used_type
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_5
        # Fixed array way 3 e.g. "enum AudioEngineChannel info[AUDIOENGINE_CH_MAX]"
        m = re.search('^((?:const{1,}))\ ?(.*)\ ([a-z0-9A-Z_]*?)\[([a-z0-9A-Z_]*?)\]$', value)
        if m and m.group(2) and m.group(3) and m.group(4):
          self.value_type = m.group(2).strip()
          used_type = ''
          if self.value_type == 'char':
            used_type = 'std::array<std::string, {}>'.format(m.group(5))
          elif self.value_type.startswith('struct ') and self.value_type.count('*') == 1 and parent.group_data.GenerateSharedStructure(self.value_type):
            used_type = 'std::array<IFC_{}, {}>'.format(self.value_type.replace('struct ', '').replace('*', ''), m.group(4))
          elif CheckKnownEnum(self.value_type):
            self.value_type = self.value_type.replace('enum ', '')
            if self.value_type.replace('*', '') not in parent.group_data.used_enums:
              parent.group_data.used_enums.append(self.value_type.replace('*', ''))
            used_type = 'std::array<{}, {}>'.format(self.value_type.replace('enum ', '').replace('*', ''), m.group(4))
          else:
            used_type = 'std::array<{}, {}>'.format(self.value_type, m.group(4))

          if m.group(1):
            self.msgpack_in_value = used_type
            self.msgpack_out_value = ''
          else:
            self.msgpack_in_value = ''
            self.msgpack_out_value = used_type
          self.done = True
          return

        # NOTE CONFIRMED_YES (1)
        # CheckAPIUse_WAY_6 (shared call, addon lib) (parent)
        if self.value_type == 'const char*':
          if '[]' in self.value_name and self.value_name.count('[]') == 1:
            if len(value_list) > 1:
              i = 0
              while i+cnt_in < len(value_list)-1:
                if 'size_t' in value_list[i+cnt_in+1]:
                  parent.group_data.AddAdditionalAddonLibIncludes('#include <string>')
                  parent.group_data.AddAdditionalAddonLibIncludes('#include <vector>')
                  self.value_name = self.value_name.replace('[]', '')
                  self.additional_code_1  = ('  std::vector<std::string> cpp_{};{}\n'
                                            .format(self.value_name,
                                                    ' /* CheckAPIUse_WAY_6c (0003) */' if parent.options.debug else ''))
                  self.additional_code_1 += ('  cpp_{}.reserve({});{}\n'
                                            .format(self.value_name,
                                                    value_list[i+cnt_in+1].split()[-1].strip(),
                                                    ' /* CheckAPIUse_WAY_6c (0003) */' if parent.options.debug else ''))
                  self.additional_code_1 += ('  for (size_t i = 0; i < {}; ++i){}\n'
                                            .format(value_list[i+cnt_in+1].split()[-1].strip(),
                                                    ' /* CheckAPIUse_WAY_6c (0003) */' if parent.options.debug else ''))
                  self.additional_code_1 += ('  {\n')
                  self.additional_code_1 += ('      cpp_{}.emplace_back({}[i] != nullptr ? {}[i] : "");{}\n'
                                            .format(self.value_name,
                                                    self.value_name,
                                                    self.value_name,
                                                    ' /* CheckAPIUse_WAY_6c (0003) */' if parent.options.debug else ''))
                  self.additional_code_1 += ('  }\n')
                  self.msgpack_in_value = ('cpp_{}{}'
                                          .format(self.value_name,
                                                  ' /* CheckAPIUse_WAY_6c (0003) */' if parent.options.debug else ''))
                  self.msgpack_out_value = ''
                  self.done = True
                  break
                if '[]' in value_list[i+cnt_in+1] and value_list[i+cnt_in+1].count('[]') == 1:
                  i += 1
                  continue

                print('FATAL (6b, 0003): Function:')
                print('       "{}"'.format(parent.function_complete))
                print('       Not supported on InterfaceDataParent::GenerateAddonSourceCFunctionSharedCode!')
                print('       Need to set second value of "{}" as "size_t".'.format(self.value))
                exit(1)
          elif len(value_list) > 1 \
               and cnt_in < len(value_list)-1 \
               and '...' in value_list[cnt_in+1]:
            self.msgpack_in_value = ('cpp_{}{}'
                                     .format(self.value_name,
                                             ' /* CheckAPIUse_WAY_6a (0003) */' if parent.options.debug else ''))
            self.msgpack_out_value = ''
          else:
            self.msgpack_in_value = ('{}{}'
                                     .format(self.value_name,
                                             ' /* CheckAPIUse_WAY_6b (0003) */' if parent.options.debug else ''))
            self.msgpack_out_value = ''
          self.done = True
          return

        # NOTE CONFIRMED_YES (1)
        # CheckAPIUse_WAY_7
        if self.value_type == 'char**':
          self.msgpack_in_value = ''
          self.msgpack_out_value = '  *{} = strdup(std::get<{}>(t).c_str());{}\n'.format(self.value_name, self.cnt_out, ' /* CheckAPIUse_WAY_7 (0003) */' if parent.options.debug else '')
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_8_1 (addon lib) (parent)
        if self.value_type == 'char***' \
           or (self.value_type == 'char**' \
               and '[]' in self.value_name \
               and self.value_name.count('[]') == 1):
          if len(value_list) > 1 \
              and cnt_in < len(value_list)-1 \
              and 'size_t*' in value_list[cnt_in+1]:
            self.value_name = self.value_name.replace('[]', '')
            self.msgpack_in_value = ''
            self.msgpack_out_value = ('const std::vector<std::string>& cpp_{} = std::get<{}>(t);{}\n'
                                       .format(self.value_name,
                                               self.cnt_out,
                                               ' /* CheckAPIUse_WAY_8_1 (0003) */' if parent.options.debug else ''))
            self.additional_code_4 += ('  assert(cpp_{}.size() == *{});{}'
                                       .format(self.value_name,
                                               value_list[cnt_in+1].split()[-1].strip(),
                                               ' /* CheckAPIUse_WAY_8_1 (0003) */' if parent.options.debug else ''))
            self.additional_code_4 += ('  if (!cpp_{}.empty())\n'
                                       .format(self.value_name))
            self.additional_code_4 += ('  {\n')
            self.additional_code_4 += ('    *{} = static_cast<char**>(malloc(*{} * sizeof(char*)));{}\n'
                                       .format(self.value_name,
                                               value_list[cnt_in+1].split()[-1].strip(),
                                               ' /* CheckAPIUse_WAY_8_1 (0003) */' if parent.options.debug else ''))
            self.additional_code_4 += ('    for (size_t i = 0; i < *{}; ++i){}\n'
                                       .format(value_list[cnt_in+1].split()[-1].strip(),
                                               ' /* CheckAPIUse_WAY_8_1 (0003) */' if parent.options.debug else ''))
            self.additional_code_4 += ('      (*{})[i] = strdup(cpp_{}[i].c_str());{}\n'
                                       .format(self.value_name,
                                               self.value_name,
                                               ' /* CheckAPIUse_WAY_8_1 (0003) */' if parent.options.debug else ''))
            self.additional_code_4 += ('  }\n')
            self.additional_code_4 += ('  else\n')
            self.additional_code_4 += ('  {\n')
            self.additional_code_4 += ('    *{} = nullptr;\n'
                                       .format(self.value_name,
                                               ' /* CheckAPIUse_WAY_8_1 (0003) */' if parent.options.debug else ''))
            self.additional_code_4 += ('  }\n')

            self.done = True
          else:
            print('FATAL (8_1, 0003): Function:')
            print('       "{}"'.format(parent.function_complete))
            print('       Not supported on InterfaceDataParent::GenerateSharedTuples!')
            print('       Need to set second value of "{}" as "size_t".'.format(self.value))
            exit(1)
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_8
        if self.value_type == 'char*' \
           and self.cnt_in-self.ignored_count+1 < len(parent.values) \
           and 'size_t' in value_list[self.cnt_in+self.ignored_count+1]:
          self.msgpack_in_value = ''
          self.msgpack_out_value = ('  strncpy({}, std::get<{}>(t).c_str(), {});{}'
                                    .format(self.value_name,
                                            self.cnt_out,
                                            value_list[cnt_in+1].split()[-1].strip(),
                                            ' /* CheckAPIUse_WAY_8 (0003) */' if parent.options.debug else ''))
          self.done = True
          return

        # CheckAPIUse_WAY_9
        if self.value_type in known_STANDARD_C_TYPES \
           and '[]' in self.value_name \
           and self.value_name.count('[]') == 1 \
           and cnt_in < len(value_list)-1 \
           and 'size_t' in value_list[cnt_in+1]:
          size_value = value_list[cnt_in+ignored_count+1].split()[-1].strip()
          value_name = self.value_name.replace('[]', '')
          self.msgpack_in_value = ('std::vector<{}>({}, {} + {}){}'
                                   .format(self.value_type,
                                           value_name,
                                           value_name,
                                           size_value,
                                           ' /* CheckAPIUse_WAY_9 (0003) */' if parent.options.debug else ''))
          self.msgpack_out_value = ('std::memcpy({}, std::get<{}>(t).data(), sizeof({}) * {});{}'
                                    .format(value_name,
                                            cnt_out,
                                            self.value_type,
                                            size_value,
                                            ' /* CheckAPIUse_WAY_9 (0003) */' if parent.options.debug else ''))
          self.ignored_count += 1
          self.ignore_next = True
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_10
        if self.value_type in known_STANDARD_C_TYPES:
          self.msgpack_in_value = ('{}{}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_10 (0003) */' if parent.options.debug else ''))
          self.msgpack_out_value = ''
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_11
        if self.value_type in known_STANDARD_C_PTR_TYPES \
              and cnt_in < len(value_list)-1 \
              and 'size_t' in value_list[cnt_in+1] \
              and self.value_type.count('*') == 1:
          size_value = value_list[cnt_in+ignored_count+1].split()[-1].strip()
          self.msgpack_in_value = ''
          self.msgpack_out_value = ('std::memcpy({}, std::get<{}>(t).data(), sizeof({}) * {});{}'
                                    .format(self.value_name,
                                            cnt_out,
                                            self.value_type.replace('*', ''),
                                            size_value,
                                            ' /* CheckAPIUse_WAY_10 (0003) */' if parent.options.debug else ''))
          self.ignore_next = True
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_11
        if self.value_type.replace('const ', '') in known_STANDARD_C_PTR_TYPES \
              and cnt_in < len(value_list)-1 \
              and 'size_t' in value_list[cnt_in+1] \
              and self.value_type.count('*') == 1:
          size_value = value_list[cnt_in+ignored_count+1].split()[-1].strip()
          self.msgpack_in_value = ('std::vector<{}>({}, {} + {}){}'
                                   .format(self.value_type.replace('*', '').replace('const ', ''),
                                           self.value_name,
                                           self.value_name,
                                           size_value,
                                           ' /* CheckAPIUse_WAY_11 (0003) */' if parent.options.debug else ''))
          self.msgpack_out_value = ''
          self.ignore_next = True
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_12
        if ContainsHdlVoidPointer(self.value_type):
          self.msgpack_in_value = ('PtrValue({}){}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_12 (0003) */' if parent.options.debug else ''))
          self.msgpack_out_value = ''
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_13 - e.g. 'bool* ret'
        if self.value_type.replace('const ', '') in known_STANDARD_C_PTR_TYPES:
          if self.value_type.count('*') == 1:
            self.msgpack_in_value = '*{}{}'.format(self.value_name, ' /* CheckAPIUse_WAY_13 (0003) */' if parent.options.debug else '')
            self.msgpack_out_value = '  *{} = std::get<{}>(t);{}\n'.format(self.value_name, self.cnt_out, ' /* CheckAPIUse_WAY_13 (0003) */' if parent.options.debug else '')
            self.done = True
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataParent::GenerateSharedTuples (on CheckAPIUse_WAY_13)'.format(parent.function_complete))
            exit(1)
          return

        # WARNING CONFIRMED_NO (14a 1)
        # CheckAPIUse_WAY_14
        # If yes, handle enum - e.g. 'enum NAME value' or 'enum NAME* ret'
        if CheckKnownEnum(self.value_type):
          self.value_type = self.value_type.replace('enum ', '')

          # Add enum to used list (if not present)
          check_value = self.value_type.replace('*', '').strip()
          if check_value not in parent.group_data.used_enums:
            parent.group_data.used_enums.append(check_value)

          # If normal value add to input
          if not '*' in self.value_type:
            self.msgpack_in_value = ('{}{}'
                                     .format(self.value_name,
                                             ' /* CheckAPIUse_WAY_14a (0003) */' if parent.options.debug else ''))
          elif '*' in self.value_type and self.value_type.count('*') == 1 and not 'const' in self.value_type:
            self.msgpack_in_value = ('*{}{}'
                                     .format(self.value_name,
                                             ' /* CheckAPIUse_WAY_14b (0003) */' if parent.options.debug else ''))
            self.msgpack_out_value = ('*{} = std::get<{}>(t);{}'
                                      .format(self.value_name,
                                              self.cnt_out,
                                              ' /* CheckAPIUse_WAY_14b (0003) */' if parent.options.debug else ''))
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataParent::GenerateSharedTuples (on CheckAPIUse_WAY_14)'.format(parent.function_complete))
            raise
          self.done = True
          return

        # NOTE CONFIRMED_YES (1)
        # CheckAPIUse_WAY_15
        if self.value_type.startswith('struct ') \
              and self.value_type.count('*') == 1 \
              and parent.group_data.GenerateSharedStructure(self.value_type):
          struct_name = self.value_type.replace('struct ', '').replace('*', '').strip()

          if struct_name == 'tm':
            self.msgpack_in_value = ('{}{}'
                                     .format(self.value_name,
                                             ' /* CheckAPIUse_WAY_15 (0003) */' if parent.options.debug else ''))
          self.msgpack_out_value = ('std::get<{}>(t).SetCStructure({});{}'
                                    .format(self.cnt_out,
                                            self.value_name,
                                            ' /* CheckAPIUse_WAY_15 (0003) */' if parent.options.debug else ''))
          self.done = True
          return

        # NOTE CONFIRMED_YES (1)
        # CheckAPIUse_WAY_16
        if self.value_type.startswith('const struct ') \
              and self.value_type.count('*') == 1 \
              and parent.group_data.GenerateSharedStructure(self.value_type):
          self.msgpack_in_value = ('{}{}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_16 (0003) */' if parent.options.debug else ''))
          self.msgpack_out_value = ''
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_17
        if self.value_type.startswith('struct ') \
              and self.value_type.count('*') == 2 \
              and cnt_in+ignored_count < len(value_list)-1 \
              and 'size_t*' in value_list[cnt_in+ignored_count+1] \
              and parent.group_data.GenerateSharedStructure(self.value_type):
          ifc_struct_name = self.value_type.replace('*', '').replace('struct ', '')
          self.msgpack_in_value = ''
          self.msgpack_out_value = ('std::vector<IFC_{}>& ifc_{} = std::get<{}>(t);'
                                    .format(ifc_struct_name,
                                            self.value_name,
                                            cnt_out))
          self.additional_code_4 = ('  *{} = static_cast<{}>(malloc(sizeof({}) * ifc_{}.size()));{}\n'
                                    .format(self.value_name,
                                            self.value_type.replace('**', '*').replace('struct ', ''),
                                            ifc_struct_name,
                                            self.value_name,
                                            ' /* CheckAPIUse_WAY_17 (0003) */' if parent.options.debug else ''))
          self.additional_code_4 += ('  for (size_t i = 0; i < ifc_{}.size(); ++i)\n'
                                     .format(self.value_name))
          self.additional_code_4 += ('     ifc_{}[i].SetCStructure(&(*{})[i]);\n'
                                     .format(self.value_name,
                                             self.value_name))
          self.done = True
          return

        self.done = False

    if '---AUTO_GEN_PARSE<OVERRIDE;USE_INTERNAL={}>---'.format(self.funcname) in file_text:
      code += '  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}>---*/\n'.format(self.funcname_ifc.upper())
      target_file = self.group_data.path.replace(self.search_dir, '{}xbmc/addons/kodi-dev-kit/src/addon/api/'.format(kodi_dir)).replace('.h', '.cpp')
      code_work = CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_{}'.format(self.funcname_ifc.upper()))
      if code_work:
        code += code_work
      else:
        code += '#warning Function "{}" must be set by hand.\n'.format(self.function_complete)
      code += '  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}_END>---*/\n'.format(self.funcname_ifc.upper())
      code += '}\n'
      self.parent_addon_c_lib_function_shared = code
      return

    # Check code generation
    #{{{
    check_code = ''
    for value in self.values:
      if '*' in value or '[]' in value or ContainsHdlVoidPointer(value):
        check_code += '{} == nullptr || '.format(value.split()[-1].replace('[]', ''))
    if check_code.endswith(' || '):
      check_code = check_code[:-4]
    if check_code != '':
      check_code  = '  if ({})\n'.format(check_code)
      check_code += '    return{};\n'.format(GetDefaultReturn(self.retval, self.function_complete, file_text))
    if check_code != '':
      code += check_code + '\n'
    #}}}

    if not self.group_data.override_use_direct_api_only:
      code += '#ifndef KODI_INHIBIT_SHARED\n'
      code += '  if (!AddonIfc::g_ifc->direct_used)\n'
      code += '  {\n'

      if self.retval == 'void' and not len(self.values):
        code += '    AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(funcGroup_' + self.header_group_id + ', funcParent_' + self.funcname_ifc + ');\n'
        code += '    return;\n'
      else:
        haveIn = len(self.values) != 0
        haveOut = self.ContainsOutOnIn() or self.retval != 'void'

        outOnIn = ''
        additional_code_2 = ''
        additional_code_3 = ''
        additional_code_4 = ''
        if haveIn:
          current = 0
          cnt = 1 if self.retval != 'void' else 0

          in_values = ''

          count_in = 0
          count_out = 1 if self.retval != 'void' else 0
          ignored_count = 0
          api_use_list = []
          for value in self.values:
            apiUse = CheckAPIUse(self, count_in, count_out, value, self.values, ignored_count)
            api_use_list.append(apiUse)
            ignored_count = apiUse.ignored_count

            count_in += 1

            value_type = value.replace(value.split()[-1], '').strip()
            current += 1
            current_name = value.split()[-1].strip()
            if apiUse.done:
              value_name = apiUse.msgpack_in_value + (', ' if apiUse.msgpack_in_value else '')
              if apiUse.msgpack_out_value:
                outOnIn += apiUse.msgpack_out_value
                count_out += 1

              code += apiUse.additional_code_1
              if apiUse.additional_code_2:
                additional_code_2 += apiUse.additional_code_2
              if apiUse.additional_code_3:
                additional_code_3 += apiUse.additional_code_3
              if apiUse.additional_code_4:
                additional_code_4 += apiUse.additional_code_4

            else:
              value_name = 'TODO1aa!!!!!!!' + ', '
              outOnIn += '???TODO!!!!!!!'
            in_values += value_name

          if in_values.endswith(', '):
            in_values = in_values[:-2]

          haveIn = in_values != ''

          code += '    msgpack::sbuffer in;\n' if haveIn else ''
          code += '    msgpack::sbuffer out;\n' if haveOut else ''
          code += '    msgpack::pack(in, msgParent__IN_{}({}));\n'.format(self.funcname_ifc, in_values) if haveIn else ''
        else:
          code += '    msgpack::sbuffer out;\n' if haveOut else ''


        if haveIn and haveOut:
          code += '  if (!AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(funcGroup_' + self.header_group_id + ', funcParent_' + self.funcname_ifc + ', in, out))\n'
          code += '    return' + GetDefaultReturn(self.retval, self.function_complete, file_text) + ';\n'
        elif haveIn and not haveOut:
          code += '  AddonIfc::g_ifc->control->GetThreadIfc()->SendMessage(funcGroup_' + self.header_group_id + ', funcParent_' + self.funcname_ifc + ', in);\n'
        else:
          code += '  if (!AddonIfc::g_ifc->control->GetThreadIfc()->SendMessageOnlyGetReturn(funcGroup_' + self.header_group_id + ', funcParent_' + self.funcname_ifc + ', out))\n'
          code += '    return' + GetDefaultReturn(self.retval, self.function_complete, file_text) + ';\n'

        if haveOut:
          code += '  msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());\n'
          code += '  msgParent_OUT_' + self.funcname_ifc + ' t = ident.get().as<decltype(t)>();\n'
          code += '\n'

          code += additional_code_3

          if self.ContainsOutOnIn():
            code += outOnIn

          code += additional_code_4

          if self.retval == 'char*':
            code += '  return strdup(std::get<0>(t).c_str());{}\n'.format(' /* Return_WAY_1 (0003) */' if self.options.debug else '')
          elif self.retval in known_STANDARD_C_TYPES:
            code += '  return std::get<0>(t);{}\n'.format(' /* Return_WAY_2 (0003) */' if self.options.debug else '')
          elif CheckKnownEnum(self.retval):
            code += '  return std::get<0>(t);{}\n'.format(' /* Return_WAY_3 (0003) */' if self.options.debug else '')
          elif ContainsHdlVoidPointer(self.retval):
            code += '  return reinterpret_cast<{}>(std::get<0>(t));{}\n'.format(self.retval, ' /* Return_WAY_4 (0003) */' if self.options.debug else '')
          elif self.retval == 'char**' \
              and len(self.values) > 0 \
              and api_use_list[-1].value_type == 'size_t*' \
              and (not api_use_list[-2].value_type in known_STANDARD_C_PTR_TYPES if len(self.values) > 1 else True):
            code += '  const std::vector<std::string>& values = std::get<0>(t);\n'
            code += '  char** ret = static_cast<char**>(malloc(sizeof(char*) * values.size()));\n'
            code += '  for (size_t i = 0; i < *{}; ++i)\n'.format(api_use_list[-1].value_name)
            code += '  {\n'
            code += '    ret[i] = strdup(values[i].c_str());\n'
            code += '  }\n'
            code += '  return ret;{}\n'.format(' /* Return_WAY_4 (0003) */' if self.options.debug else '')
          elif self.retval != 'void':
            code += '  return TODO_RET;\n'
          else:
            code += '  return;\n'
        else:
          code += '  return;\n'

      code += '  }\n'
      code += '#endif /* !KODI_INHIBIT_SHARED */\n'
      code += '\n'

    func_values = ''
    current_value = 1
    for value in self.values:
      if value != '...':
        value_name = value.split()[-1].strip()
        value_type = value[:-len(value_name)].strip()
        if '[' in value_name:
          value_type += '[' + value_name.split('[', 1)[-1]
          value_name = value_name.split('[', 1)[0].strip()
      else:
        value_name = ''
        value_type = '...'
        continue
      func_values += ', {}'.format(value_name)
      current_value += 1

    code += ('  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.{};\n'
             .format(self.header_group_id))
    code += ('  {}auto_gen_group.{}(auto_gen_group.thisClassHdl{});\n'
             .format('return ' if self.retval != 'void' else '',
                     self.funcname_ifc,
                     func_values))

    code += '}\n'
    self.parent_addon_c_lib_function_shared = code

  def GenerateAddonSourceCFunctionDirectCode(self, code, file_text):
    if '---AUTO_GEN_PARSE<OVERRIDE;USE_INTERNAL={}>---'.format(self.funcname) in file_text:
      code += '  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}>---*/\n'.format(self.funcname.upper())
      target_file = self.group_data.path.replace(self.search_dir, '{}xbmc/addons/kodi-dev-kit/src/addon/api/'.format(kodi_dir)).replace('.h', '.cpp')
      code_work = CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_{}'.format(self.funcname.upper()))
      if code_work:
        code += code_work
      else:
        code += '#warning Function "{}" must be set by hand.\n'.format(self.function_complete)
      code += '  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}_END>---*/\n'.format(self.funcname.upper())
      code += '}\n'
      self.parent_addon_c_lib_function_direct = code
      return

    retval = ''
    if self.retval != 'void':
      retval += 'return '

    code += '  void* kodiPtr = AddonIfc::g_ifc->direct.' + self.header_group_id + '->kodiPtr;\n'
    code += '  ' + retval + 'AddonIfc::g_ifc->direct.' + self.header_group_id + '->' + self.funcname + '(kodiPtr, '
    current_value = 0
    for value in self.values:
      if value == '...' or value == '': # TODO
        continue
      code += value.split()[-1]
      current_value += 1
      if current_value < len(self.values):
        code += ', '
    if code.endswith(', '):
      code = code[:-2]
    code += ');\n'
    code += '}\n'

    self.parent_addon_c_lib_function_direct = code

  def GenerateAddonSourceCFunction(self, file_text):
    code = 'ATTR_DLL_EXPORT {} {}('.format(self.retval, self.funcname)

    current_value = 1
    for value in self.values:
      code += value + (', ' if current_value < len(self.values) else '')
      current_value += 1

    code += ')\n'
    code += '{\n'
    code += '  // Original API call: {}\n'.format(self.function_complete)
    if not self.group_data.override_use_direct_api_only:
      code += '  // Tuple in:          {}\n'.format(self.parent_addon_c_lib_function_shared_tuple_in)
      code += '  // Tuple out:         {}\n'.format(self.parent_addon_c_lib_function_shared_tuple_out)
      code += '\n'

    self.GenerateAddonSourceCFunctionSharedCode(code, file_text)
    self.GenerateAddonSourceCFunctionDirectCode(code, file_text)
    if not '---AUTO_GEN_PARSE<OVERRIDE;USE_INTERNAL={}>---'.format(self.funcname) in file_text:
      self.GenerateAddonSourceCFunctionDirectFuncPtr()

    return True

  def GenerateKodiSourceCPPFunction(self, file_text):
    if '---AUTO_GEN_PARSE<OVERRIDE;USE_INTERNAL={}>---'.format(self.funcname) in file_text:
      return True

    target_file = self.group_data.path.replace(self.search_dir, '{}xbmc/addons/interface/api/'.format(kodi_dir)).replace('.h', '.cpp')


    values = ''
    current_value = 1
    for value in self.values:
      values += value + (', ' if current_value < len(self.values) else '')
      current_value += 1

    code = ''
    code += '{} CHdl_kodi_{}::{}(void* thisClassHdl{})\n'.format(self.retval, self.header_group_id, self.funcname_ifc, ', ' + values if values != '' else '')
    code += '{\n'
    code += '  auto thisClass = reinterpret_cast<' + 'CHdl_kodi_{}*>(thisClassHdl);\n'.format(self.header_group_id)
    code += '  if (thisClass == nullptr)\n'
    code += '    return{};\n'.format(GetDefaultReturn(self.retval, self.function_complete, file_text))
    code += '\n'
    code += '  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}>---*/\n'.format(self.funcname.upper())

    # Check presence of hand edited part, if not make note code about
    code_work = CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_{}'.format(self.funcname.upper()))
    if not code_work or '#warning Function' in code_work or '// AUTOGENERATED - Used by ' in code_work:
      code_work = ''
      for entry in self.callbacks:
        if entry.api_call == self.funcname:
          code_work += '// AUTOGENERATED - Used by class "{}" with "{}" on "{}".\n'.format(entry.call_class, entry.complete, entry.header)
          code_work += '\n'
          code_work += '  {}* cb = static_cast<{}*>({});'.format(entry.call_class, entry.call_class, self.values[0].split()[-1])

          value_types = ''
          current_value = 1
          for value in self.values:
            current_value += 1
            if current_value <= 2:
              continue
            name = value.split()[-1]
            value_types += name + (', ' if current_value-1 < len(self.values) else '')


          caller = ''
          if self.retval != 'void':
            if self.retval == 'char*':
              if not caller:
                m = re.search('^(?:const)?\ *(std\:\:string)', entry.complete)
                if m and m.group(1):
                  caller += '  return strdup(cb->{}({}).c_str());'.format(entry.function_name, value_types)
              if not caller:
                m = re.search('^(const[\t ]*char[\t ]*\*)', entry.complete)
                if m and m.group(1):
                  caller += '  return strdup(cb->{}({}));'.format(entry.function_name, value_types)
            elif self.retval == 'const char*':
              if not caller:
                m = re.search('^(?:const)?\ *(std\:\:string)', entry.complete)
                if m and m.group(1):
                  caller += '  return cb->{}({});'.format(entry.function_name, value_types)
              if not caller:
                m = re.search('^(const[\t ]*char[\t ]*\*)', entry.complete)
                if m and m.group(1):
                  caller += '  return cb->{}({});'.format(entry.function_name, value_types)
            if not caller:
              caller += '  return cb->{}({});'.format(entry.function_name, value_types)
          else:
            caller += '  cb->{}({});'.format(entry.function_name, value_types)
          code_work += caller

          if not entry.header in self.group_data.kodi_ifc_includes:
            self.group_data.kodi_ifc_includes.append(entry.header)

          break

      if not code_work:
        code_work  = '  // Code below must be set manually by hand to make work to Kodi\n'
        code_work += '\n'
        if self.ContainsOutOnIn() or self.retval != 'void':
          if self.retval == 'char*':
            code_work += '  std::string str; // Autogen example added code, set to required one!!!\n'
            code_work += '\n'
            code_work += '  return strdup(str.c_str());\n'
          else:
            code_work += '  return{};\n'.format(GetDefaultReturn(self.retval, self.function_complete, file_text))
        code_work += '#warning Function "CHdl_kodi_{}::{}" must be set by hand. Alternatively add /*---AUTO_GEN_PARSE<CB:{}>---*/ on back of target function in header to find on scan.\n'.format(self.header_group_id, self.funcname, self.funcname)

    if code_work.endswith('\n\n'):
      code_work = code_work[:-1]

    code += code_work
    code += '\n'
    code += '  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}_END>---*/\n'.format(self.funcname.upper())
    code += '}\n'

    self.parent_kodi_cpp_function_source = code
    self.parent_kodi_cpp_function_header = ('  static {} {}(void* thisClassHdl{}); // Added with API {}\n'
                                            .format(self.retval,
                                                    self.funcname_ifc,
                                                    ', ' + values if values != '' else '',
                                                    self.api_added))

    return True

  # Log ID: 0001
  def GenerateKodiSourceCPPSwitchCase(self, file_text):
    class CheckAPIUse:
      def __init__(self, parent, cnt, cnt_out, value, value_list, ignored_count):
        self.parent = parent
        self.cnt = cnt
        self.cnt_out = cnt_out
        self.value = value
        self.additional_code_1 = ''
        self.additional_code_2 = ''
        self.additional_code_3 = ''
        self.additional_code_4 = ''
        self.ignore_next = False
        self.ignored_count = ignored_count

        self.value_name = value.split()[-1].strip()
        self.value_type = value[:-len(self.value_name)].strip()

        self.msgpack_in_value = ''
        self.msgpack_out_value = ''
        self.function_value = ''
        self.done = False

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_1
        if '...' in self.value:
          self.msgpack_in_value = ''
          self.msgpack_out_value = ''
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_2
        m = re.search('^[\t ]*(?:const[\t ]*)?([a-zA-Z0-9_]*)[\t ]*\*[\t ]*(?:const[\t ]*)?\*', self.value)
        if m and m.group(1) and m.group(1) in known_STANDARD_C_TYPES and 'size_t' in value_list[cnt+1] and 'size_t' in value_list[cnt+2]:
          if 'const ' in self.value or 'const*' in self.value:
            size_1_name = value_list[cnt+2].split()[-1].strip()
            size_2_name = value_list[cnt+2].split()[-1].strip()
            self.msgpack_in_value  = 'std::vector<std::vector<{}>>& ifc_{} = std::get<{}>(t);{}'.format(m.group(1), self.value_name, self.cnt-self.ignored_count, ' /* CheckAPIUse_WAY_2 (0001) */' if parent.options.debug else '')
            self.function_value = '{}{}'.format(self.value_name, ' /* CheckAPIUse_WAY_2 (0001) */' if parent.options.debug else '')
            self.additional_code_2 = '      {}** {} = new {}*[ifc_{}.size()];{}'.format(m.group(1), self.value_name, m.group(1),
                                                                                        self.value_name, ' /* CheckAPIUse_WAY_2 (0001) */' if parent.options.debug else '')
            self.additional_code_2 += '      for (size_t i = 0; i < ifc_{}.size(); ++i){}'.format(self.value_name, ' /* CheckAPIUse_WAY_2 (0001) */' if parent.options.debug else '')
            self.additional_code_2 += '        {}[i] = ifc_{}[i].data();{}'.format(self.value_name, self.value_name, ' /* CheckAPIUse_WAY_2 (0001) */' if parent.options.debug else '')
            self.additional_code_4 = '      delete[] {};{}\n'.format(self.value_name, ' /* CheckAPIUse_WAY_2 (0001) */' if parent.options.debug else '')
            self.done = True
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataParent::GenerateKodiSourceCPPSwitchCase'.format(parent.function_complete))
            raise
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_2
        # Fixed array way 1 e.g. "enum AudioEngineChannel info[][AUDIOENGINE_CH_MAX]"
        #regex_code = '^((?:const{1,}))?(.*)\ ([a-z0-9A-Z_]*?)(?!\*)?\[([a-z0-9A-Z_]*?)\]\[([a-z0-9A-Z_]*?)\]$'
        #m = re.search(regex_code, value)
        #if m and m.group(2) and m.group(3) and not m.group(4) and m.group(5):
          #self.msgpack_in_value = 'ifc_{}'.format(m.group(3))
          #self.msgpack_out_value = 'memcpy(*{}, std::get<{}>(t).data(), sizeof({}) * {});'.format(m.group(3), cnt_out, self.value_type.replace('*', ''), m.group(5))
          #self.additional_code_1  = '  std::array<{}, {}> ifc_{};\n'.format(self.value_type, m.group(5), m.group(3))
          #self.additional_code_1 += '  std::memcpy(ifc_{}.data(), *{}, sizeof({}) * {});\n'.format(m.group(3), m.group(3), self.value_type.replace('*', ''), m.group(5))
        #elif cnt == 0 and (self.value_type.replace('const ', '') == self.parent.groupname.upper() + '_HDL') and self.value_type.replace('const ', '') in known_VOID_PTR_DEFINES:
          #self.msgpack_in_value = 'PtrValue({})'.format(self.value_name)
          #return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_6 (target call, Kodi side) (parent)
        if self.value_type == 'const char*':
          if '[]' in self.value_name and self.value_name.count('[]') == 1:
            if len(value_list) > 1:
              i = 0
              while i+cnt < len(value_list)-1:
                if 'size_t' in value_list[i+cnt+1]:
                  parent.group_data.AddAdditionalAddonLibIncludes('#include <string>')
                  parent.group_data.AddAdditionalAddonLibIncludes('#include <vector>')
                  self.value_name = self.value_name.replace('[]', '')
                  self.function_value = ('{}.data(){}'
                                        .format(self.value_name,
                                                ' /* CheckAPIUse_WAY_6c (0001) */' if parent.options.debug else ''))
                  self.msgpack_in_value = ('const std::vector<std::string>& cpp_{} = std::get<{}>(t);{}'
                                          .format(self.value_name,
                                                  self.cnt-self.ignored_count,
                                                  ' /* CheckAPIUse_WAY_6c (0001) */' if parent.options.debug else ''))
                  self.additional_code_2 += ('\n')
                  self.additional_code_2 += ('  std::vector<const char*> {};{}\n'
                                            .format(self.value_name,
                                                    ' /* CheckAPIUse_WAY_6c (0001) */' if parent.options.debug else ''))
                  self.additional_code_2 += ('  {}.reserve({});{}\n'
                                            .format(self.value_name,
                                                    value_list[i+cnt+1].split()[-1].strip(),
                                                    ' /* CheckAPIUse_WAY_6c (0001) */' if parent.options.debug else ''))
                  self.additional_code_2 += ('  for (size_t i = 0; i < {}; ++i){}\n'
                                            .format(value_list[i+cnt+1].split()[-1].strip(),
                                                    ' /* CheckAPIUse_WAY_6c (0001) */' if parent.options.debug else ''))
                  self.additional_code_2 += ('  {\n')
                  self.additional_code_2 += ('      {}.emplace_back(cpp_{}[i].c_str());{}\n'
                                            .format(self.value_name,
                                                    self.value_name,
                                                    ' /* CheckAPIUse_WAY_6c (0001) */' if parent.options.debug else ''))
                  self.additional_code_2 += ('  }\n')
                  self.additional_code_2 += ('  assert(cpp_{}.size() == {});\n'
                                            .format(self.value_name,
                                                    value_list[i+cnt+1].split()[-1].strip()))
                  self.additional_code_2 += ('\n')
                  self.msgpack_out_value = ''
                  self.done = True
                  break
                if '[]' in value_list[i+cnt+1] and value_list[i+cnt+1].count('[]') == 1:
                  i += 1
                  continue

                print('FATAL (6c, 0001): Function:')
                print('       "{}"'.format(parent.function_complete))
                print('       Not supported on InterfaceDataParent::GenerateAddonSourceCFunctionSharedCode!')
                print('       Need to set second value of "{}" as "size_t".'.format(self.value))
                exit(1)
          else:
            self.function_value = ('{}.c_str(){}'
                                    .format(self.value_name,
                                            ' /* CheckAPIUse_WAY_6a (0001) */' if parent.options.debug else ''))
            self.msgpack_in_value = ('const std::string& {} = std::get<{}>(t);{}'
                                    .format(self.value_name,
                                            self.cnt-self.ignored_count,
                                            ' /* CheckAPIUse_WAY_6a (0001) */' if parent.options.debug else ''))
            self.msgpack_out_value = ''
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_7
        if self.value_type == 'char**':
          self.msgpack_in_value = 'char* {} = nullptr;{}'.format(self.value_name, ' /* CheckAPIUse_WAY_7 (0001) */' if parent.options.debug else '')
          self.function_value = '&{}{}'.format(self.value_name, ' /* CheckAPIUse_WAY_7 (0001) */' if parent.options.debug else '')
          self.msgpack_out_value = '{} ? {} : ""{}'.format(self.value_name, self.value_name, ' /* CheckAPIUse_WAY_7 (0001) */' if parent.options.debug else '')
          self.additional_code_4  = '      if ({}){}\n'.format(self.value_name, ' /* CheckAPIUse_WAY_7 (0001) */' if parent.options.debug else '')
          self.additional_code_4 += '        free({});{}\n'.format(self.value_name, ' /* CheckAPIUse_WAY_7 (0001) */' if parent.options.debug else '')
          self.ignored_count += 1
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_8
        if self.value_type == 'char*' \
           and self.cnt-self.ignored_count+1 < len(parent.values) \
           and 'size_t' in value_list[self.cnt+self.ignored_count+1]:
          size_value = value_list[cnt+ignored_count+1].split()[-1].strip()
          self.msgpack_in_value = ('std::string {};{}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_8 (0001) */' if parent.options.debug else ''))
          self.additional_code_2 = ('      {}.reserve({});{}'
                                    .format(self.value_name,
                                            size_value,
                                            ' /* CheckAPIUse_WAY_8 (0001) */' if parent.options.debug else ''))
          self.function_value = ('&{}[0]'
                                 .format(self.value_name,
                                         ' /* CheckAPIUse_WAY_8 (0001) */' if parent.options.debug else ''))
          self.msgpack_out_value = ('{}{}'
                                    .format(self.value_name,
                                            ' /* CheckAPIUse_WAY_8 (0001) */' if parent.options.debug else ''))
          self.ignored_count += 1
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_8_1 (shared call to addon, Kodi side) (parent)
        if self.value_type == 'char***' \
           or (self.value_type == 'char**' \
               and '[]' in self.value_name \
               and self.value_name.count('[]') == 1):
          if len(value_list) > 1 \
              and cnt_in < len(value_list)-1 \
              and 'size_t*' in value_list[cnt_in+1]:
            size_value = value_list[cnt+ignored_count+1].split()[-1].strip()
            self.value_name = self.value_name.replace('[]', '')
            self.msgpack_in_value = ('char** {} = nullptr;{}'
                                    .format(self.value_name,
                                            ' /* CheckAPIUse_WAY_8_1 (0001) */' if parent.options.debug else ''))
            self.function_value = ('&{}{}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_8_1 (0001) */' if parent.options.debug else ''))
            self.additional_code_3  = ('      std::vector<std::string> cpp_{};{}\n'
                                       .format(self.value_name,
                                               ' /* CheckAPIUse_WAY_8 (0001) */' if parent.options.debug else ''))
            self.additional_code_3 += ('      cpp_{}.reserve({});{}\n'
                                       .format(self.value_name,
                                               size_value,
                                               ' /* CheckAPIUse_WAY_8 (0001) */' if parent.options.debug else ''))
            self.additional_code_3 += ('      if ({})\n'
                                       .format(self.value_name))
            self.additional_code_3 += ('      {\n')
            self.additional_code_3 += ('        for (size_t i = 0; i < {}; ++i){}\n'
                                       .format(size_value,
                                              ' /* CheckAPIUse_WAY_8 (0001) */' if parent.options.debug else ''))
            self.additional_code_3 += ('        {\n')
            self.additional_code_3 += ('          if ({}[i])\n'
                                       .format(self.value_name))
            self.additional_code_3 += ('          {\n')
            self.additional_code_3 += ('            cpp_{}.emplace_back({}[i]);\n'
                                       .format(self.value_name,
                                               self.value_name,
                                               ' /* CheckAPIUse_WAY_8 (0001) */' if parent.options.debug else ''))
            self.additional_code_3 += ('            free({}[i]);\n'
                                       .format(self.value_name))
            self.additional_code_3 += ('          }\n')
            self.additional_code_3 += ('          else\n')
            self.additional_code_3 += ('          {\n')
            self.additional_code_3 += ('            cpp_{}.emplace_back("");{}\n'
                                       .format(self.value_name,
                                               ' /* CheckAPIUse_WAY_8 (0001) */' if parent.options.debug else ''))
            self.additional_code_3 += ('          }\n')
            self.additional_code_3 += ('        }\n')
            self.additional_code_3 += ('        free({});\n'
                                       .format(self.value_name))
            self.additional_code_3 += ('      }\n')
            self.msgpack_out_value = ('cpp_{}{}'
                                     .format(self.value_name,
                                             ' /* CheckAPIUse_WAY_8 (0001) */' if parent.options.debug else ''))
            self.ignored_count += 1
            self.done = True
          else:
            print('FATAL: Function:')
            print('       "{}"'.format(parent.function_complete))
            print('       Not supported on InterfaceDataParent::GenerateKodiSourceCPPSwitchCase!')
            print('       Need to set second value of "{}" as "size_t".'.format(self.value))
            exit(1)
          return

        # CheckAPIUse_WAY_9
        if self.value_type in known_STANDARD_C_TYPES \
           and '[]' in self.value_name \
           and self.value_name.count('[]') == 1 \
           and cnt < len(value_list)-1 \
           and 'size_t' in value_list[cnt+1]:
          value_name = self.value_name.replace('[]', '')
          self.msgpack_in_value = ('std::vector<{}>& {} = std::get<{}>(t);{}'
                                   .format(self.value_type.replace('*', '').replace('const ', ''),
                                           value_name,
                                           self.cnt-self.ignored_count,
                                           ' /* CheckAPIUse_WAY_9 (0001) */' if parent.options.debug else ''))
          self.function_value = ('{}.data(){}'
                                 .format(value_name,
                                         ' /* CheckAPIUse_WAY_9 (0001) */' if parent.options.debug else ''))
          self.msgpack_out_value = ('{}{}'
                                    .format(value_name,
                                            ' /* CheckAPIUse_WAY_11 (0001) */' if parent.options.debug else ''))
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_10
        if self.value_type in known_STANDARD_C_TYPES:
          self.function_value = '{}{}'.format(self.value_name, ' /* CheckAPIUse_WAY_10 (0001) */' if parent.options.debug else '')
          self.msgpack_in_value = '{} {} = std::get<{}>(t);{}'.format(self.value_type, self.value_name, self.cnt-self.ignored_count, ' /* CheckAPIUse_WAY_10 (0001) */' if parent.options.debug else '')
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_11
        if self.value_type in known_STANDARD_C_PTR_TYPES \
              and cnt+ignored_count < len(value_list)-1 \
              and 'size_t' in value_list[cnt+ignored_count+1] \
              and self.value_type.count('*') == 1:
          self.msgpack_in_value = ''
          self.additional_code_2  = ('      std::vector<{}> {}({});{}'
                                     .format(self.value_type.replace('*', ''),
                                             self.value_name,
                                             value_list[cnt+ignored_count+1].split()[-1].strip(),
                                             ' /* CheckAPIUse_WAY_11 (0001) */' if parent.options.debug else ''))
          self.function_value = ('{}.data(){}'
                                 .format(self.value_name,
                                         ' /* CheckAPIUse_WAY_11 (0001) */' if parent.options.debug else ''))
          self.msgpack_out_value = ('{}{}'
                                    .format(self.value_name,
                                            ' /* CheckAPIUse_WAY_11 (0001) */' if parent.options.debug else ''))
          self.ignored_count += 1
          self.ignore_next = True
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_11
        if self.value_type.replace('const ', '') in known_STANDARD_C_PTR_TYPES \
              and cnt+ignored_count < len(value_list)-1 \
              and 'size_t' in value_list[cnt+ignored_count+1] \
              and self.value_type.count('*') == 1:
          self.msgpack_in_value = ('const std::vector<{}>& {} = std::get<{}>(t);{}'
                                   .format(self.value_type.replace('*', '').replace('const ', ''),
                                           self.value_name,
                                           self.cnt-self.ignored_count,
                                           ' /* CheckAPIUse_WAY_11 (0001) */' if parent.options.debug else ''))
          self.function_value = ('{}.data(){}'
                                 .format(self.value_name,
                                         ' /* CheckAPIUse_WAY_11 (0001) */' if parent.options.debug else ''))
          if not 'const ' in self.value_type:
            self.ignored_count += 1
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_12
        if ContainsHdlVoidPointer(self.value_type):
          self.function_value = '{}{}'.format(self.value_name, ' /* CheckAPIUse_WAY_12 (0001) */' if parent.options.debug else '')
          self.msgpack_in_value = '{} {} = reinterpret_cast<{}>(std::get<{}>(t));{}'.format(self.value_type, self.value_name, self.value_type, self.cnt-self.ignored_count, ' /* CheckAPIUse_WAY_12 (0001) */' if parent.options.debug else '')
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_13
        if self.value_type.replace('const ', '') in known_STANDARD_C_PTR_TYPES:
          if self.value_type.count('*') == 1:
            self.msgpack_in_value = '{} {} = std::get<{}>(t);{}'.format(self.value_type.replace('*', ''), self.value_name, self.cnt-self.ignored_count, ' /* CheckAPIUse_WAY_13 (0001) */' if parent.options.debug else '')
            self.function_value = '&{}{}'.format(self.value_name, ' /* CheckAPIUse_WAY_13 (0001) */' if parent.options.debug else '')
            if not 'const ' in self.value_type:
              self.msgpack_out_value = '{}{}'.format(self.value_name, ' /* CheckAPIUse_WAY_13 (0001) */' if parent.options.debug else '')
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataChild::GenerateKodiSourceCPPSwitchCase (on CheckAPIUse_WAY_13)'.format(parent.function_complete))
            exit(1)
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_14
        if CheckKnownEnum(self.value_type):
          if self.value_type.count('*') == 0:
            self.msgpack_in_value = ('{} {} = std::get<{}>(t);{}'
                                     .format(self.value_type,
                                             self.value_name,
                                             self.cnt-self.ignored_count,
                                             ' /* CheckAPIUse_WAY_14a (0001) */' if parent.options.debug else ''))
            self.function_value = ('{}{}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_14a (0001) */' if parent.options.debug else ''))
          elif self.value_type.count('*') == 1:
            self.msgpack_in_value = ('{} {} = std::get<{}>(t);{}'
                                     .format(self.value_type.replace('*', ''),
                                             self.value_name,
                                             self.cnt-self.ignored_count,
                                             ' /* CheckAPIUse_WAY_14a (0001) */' if parent.options.debug else ''))
            self.function_value = ('&{}{}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_14b (0001) */' if parent.options.debug else ''))
            if not 'const ' in self.value_type:
              self.msgpack_out_value = ('{}{}'
                                        .format(self.value_name,
                                                ' /* CheckAPIUse_WAY_14b (0001) */' if parent.options.debug else ''))
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataChild::GenerateKodiSourceCPPSwitchCase (on CheckAPIUse_WAY_14)'.format(parent.function_complete))
            exit(1)
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_15
        if self.value_type.startswith('struct ') \
              and self.value_type.count('*') == 1 \
              and parent.group_data.KnownSharedStructure(self.value_type):
          struct_name = self.value_type.replace('struct ', '').replace('*', '').strip()

          if struct_name == 'tm':
            self.additional_code_1 = ('      {} {};{}'
                                      .format(struct_name,
                                              self.value_name,
                                              ' /* CheckAPIUse_WAY_15 (0001) */' if parent.options.debug else ''))
            self.msgpack_in_value = ('std::get<{}>(t).SetCStructure(&{});{}'
                                    .format(self.cnt-self.ignored_count,
                                            self.value_name,
                                            ' /* CheckAPIUse_WAY_15 (0001) */' if parent.options.debug else ''))
          else:
            self.ignored_count += 1
            self.msgpack_in_value = ('{} {};{}'
                                    .format(self.value_type.replace('*', ''),
                                            self.value_name,
                                            ' /* CheckAPIUse_WAY_15 (0001) */' if parent.options.debug else ''))

          self.function_value = ('&{}{}'
                                 .format(self.value_name,
                                         ' /* CheckAPIUse_WAY_15 (0001) */' if parent.options.debug else ''))
          self.msgpack_out_value = ('&{}{}'
                                    .format(self.value_name,
                                            ' /* CheckAPIUse_WAY_15 (0001) */' if parent.options.debug else ''))

          shared_struct = self.value_type.replace('*', '')
          if parent.group_data.KnownSharedStructureWithClean(shared_struct):
            self.additional_code_4 += ('     IFC_{}::CleanCStructure(&{});\n'
                                       .format(shared_struct.replace('struct ', ''),
                                               self.value_name))
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_16
        if self.value_type.startswith('const struct ') and self.value_type.count('*') == 1 and parent.group_data.KnownSharedStructure(self.value_type):
          struct_name = self.value_type.replace('*', '').replace('const struct ', '')
          self.additional_code_1 = ('      {} {};{}'
                                    .format(struct_name,
                                            self.value_name,
                                            ' /* CheckAPIUse_WAY_16 (0001) */' if parent.options.debug else ''))
          self.msgpack_in_value = ('std::get<{}>(t).SetCStructure(&{});{}'
                                   .format(self.cnt-self.ignored_count,
                                           self.value_name,
                                           ' /* CheckAPIUse_WAY_16 (0001) */' if parent.options.debug else ''))
          self.function_value = '&{}{}'.format(self.value_name, ' /* CheckAPIUse_WAY_16 (0001) */' if parent.options.debug else '')
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_17 - For xbmc/addons/interface/api/*
        if self.value_type.startswith('struct ') \
              and self.value_type.count('*') == 2 \
              and self.cnt-self.ignored_count+1 < len(parent.values) \
              and 'size_t*' in value_list[self.cnt-self.ignored_count+1] \
              and parent.group_data.GenerateSharedStructure(self.value_type):

          self.ignored_count += 1
          struct_name = self.value_type.replace('**', '').replace('struct ', '')
          size_name = value_list[cnt+ignored_count+1].split()[-1].strip()
          self.msgpack_in_value = '{} {} = nullptr;{}'.format(self.value_type.replace('**', '*'), self.value_name, ' /* CheckAPIUse_WAY_17 (0001) */' if parent.options.debug else '')
          self.function_value = '&{}{}'.format(self.value_name, ' /* CheckAPIUse_WAY_17 (0001) */' if parent.options.debug else '')
          self.msgpack_out_value = 'ifc_{}'.format(self.value_name)
          self.additional_code_3 = ('    std::vector<IFC_{}> ifc_{};{}\n'
                                    .format(struct_name,
                                            self.value_name,
                                            ' /* CheckAPIUse_WAY_17 (0001) */' if parent.options.debug else ''))
          self.additional_code_3 += '    if ({})\n'.format(self.value_name)
          self.additional_code_3 += '    {\n'
          self.additional_code_3 += '      ifc_{}.reserve({});\n'.format(self.value_name, size_name)
          self.additional_code_3 += '      for (size_t i = 0; i < {}; ++i)\n'.format(size_name)
          self.additional_code_3 += '      {\n'
          self.additional_code_3 += '        ifc_{}.emplace_back(&{}[i]);'.format(self.value_name, self.value_name)
          self.additional_code_3 += '        ifc_{}[i].CleanCStructure(&{}[i]);'.format(self.value_name, self.value_name)
          self.additional_code_3 += '      }\n'
          self.additional_code_3 += '      free({});\n'.format(self.value_name)
          self.additional_code_3 += '    }\n'
          self.done = True
          return

        self.function_value = 'TODO1 ({})'.format(self.value_type)
        self.msgpack_in_value = 'TODO2'

    if self.group_data.override_use_direct_api_only:
      return True

    # Check function contains in and/or out
    haveIn = len(self.values) != 0
    haveOut = self.ContainsOutOnIn() or self.retval != 'void'

    # Generate the initial first part of function
    code  = '    case funcParent_{}:\n'.format(self.funcname_ifc)
    code += '    {\n'
    code += '      // Original API call: {}\n'.format(self.function_complete)
    code += '      // Tuple in:          {}\n'.format(self.parent_addon_c_lib_function_shared_tuple_in)
    code += '      // Tuple out:         {}\n'.format(self.parent_addon_c_lib_function_shared_tuple_out)

    if '---AUTO_GEN_PARSE<OVERRIDE;USE_INTERNAL={}>---'.format(self.funcname) in file_text:
      return True

    # Check it have "in" and/or "return" values, if no go easy way and add the single line to code
    if not haveIn and not haveOut:
      code += '      {}(this);\n'.format(self.funcname_ifc)
    else:
      if haveIn:
        code += '      msgParent__IN_{} t = in.get().as<decltype(t)>();\n'.format(self.funcname_ifc)

      cnt_in = 0
      cnt_out = 1 if self.retval != 'void' else 0
      ignored_count = 0

      in_values = ''
      out_values = ''
      function_values = ''
      additional_code_1 = ''
      additional_code_2 = ''
      additional_code_3 = ''
      additional_code_4 = ''
      ignore_next = False
      api_use_list = []
      for value in self.values:
        apiUse = CheckAPIUse(self, cnt_in, cnt_out, value, self.values, ignored_count)
        api_use_list.append(apiUse)
        cnt_in += 1

        #if not apiUse.ignore_next:
          #ignore_next = True
        #elif ignore_next:
          #ignore_next = False
          #continue

        ignored_count = apiUse.ignored_count

        #if apiUse.msgpack_in_value:
          #in_values += '      {}\n'.format(apiUse.msgpack_in_value)
        #if apiUse.msgpack_out_value:
          #cnt_out += 1
          #out_values += '      {}\n'.format(apiUse.msgpack_out_value)

        if apiUse.additional_code_1:
          code += apiUse.additional_code_1
        if apiUse.additional_code_2:
          additional_code_2 += apiUse.additional_code_2
        if apiUse.additional_code_3:
          additional_code_3 += apiUse.additional_code_3
        if apiUse.additional_code_4:
          additional_code_4 += apiUse.additional_code_4

        in_values += '      {}\n'.format(apiUse.msgpack_in_value)

        if apiUse.function_value:
          function_values += ', {}'.format(apiUse.function_value)
        if apiUse.msgpack_out_value:
          cnt_out += 1
          out_values += apiUse.msgpack_out_value + ', '

      if out_values.endswith(', '):
        out_values = out_values[:-2]

      return_value = ''
      if self.retval == 'char*':
        return_value = 'auto_gen_ret ? auto_gen_ret : ""{}'.format(' /* Return_WAY_1 (0001) */' if self.options.debug else '')
      elif self.retval in known_STANDARD_C_TYPES:
        return_value = 'auto_gen_ret{}'.format(' /* Return_WAY_2 (0001) */' if self.options.debug else '')
      elif CheckKnownEnum(self.retval):
        return_value = 'auto_gen_ret{}'.format(' /* Return_WAY_3 (0001) */' if self.options.debug else '')
      elif ContainsHdlVoidPointer(self.retval):
        return_value = 'PtrValue(auto_gen_ret){}\n'.format(' /* Return_WAY_4 (0001) */' if self.options.debug else '')
      elif self.retval != 'void':
        return_value = 'auto_gen_ret{}'.format(self.retval, ' /* Return_WAY_5 (undefined) (0001) */' if self.options.debug else '')

      code += in_values
      code += additional_code_2
      code += '      {}{}(this{});\n'.format('{} auto_gen_ret = '.format(self.retval) if return_value else '', self.funcname_ifc, function_values)
      code += additional_code_3
      if self.retval == 'char**' \
          and len(self.values) > 0 \
          and api_use_list[-1].value_type == 'size_t*' \
          and (not api_use_list[-2].value_type in known_STANDARD_C_PTR_TYPES if len(self.values) > 1 else True):
        code += '      std::vector<std::string> auto_gen_ret_cpp;\n'
        code += '      if (auto_gen_ret)\n'
        code += '      {\n'
        code += '        auto_gen_ret_cpp.reserve({});\n'.format(api_use_list[-1].value_name)
        code += '        for (size_t i = 0; i < {}; ++i)\n'.format(api_use_list[-1].value_name)
        code += '        {\n'
        code += '          if (auto_gen_ret[i])\n'
        code += '          {\n'
        code += '            auto_gen_ret_cpp.emplace_back(auto_gen_ret[i]);\n'
        code += '            free(auto_gen_ret[i]);\n'
        code += '          }\n'
        code += '        }\n'
        code += '        free(auto_gen_ret);\n'
        code += '      }\n'
        return_value = 'auto_gen_ret_cpp{}'.format(' /* Return_WAY_6 (0001) */' if self.options.debug else '')
      if out_values or return_value:
        code += '      msgpack::pack(out, msgParent_OUT_{}({}{}));\n'.format(self.funcname_ifc, return_value, (', ' if return_value else '') + out_values if out_values else '')
        if '*' in self.retval:
          if self.retval.count('*') == 1:
            code += '      if (auto_gen_ret)\n'
            code += '        free(auto_gen_ret);\n'
          elif self.retval == 'char**' \
                and len(self.values) > 0 \
                and api_use_list[-1].value_type == 'size_t*' \
                and (not api_use_list[-2].value_type in known_STANDARD_C_PTR_TYPES if len(self.values) > 1 else True):
            pass
          else:
            code += '      TODO3;\n'

      code += additional_code_4


    code += '      return true;\n'
    code += '    }\n'

    self.parent_kodi_cpp_function_switch_case = code

    return True

#===============================================================================

class InterfaceDataChild:
  def __init__(self, callbacks, options):
    self.callbacks = callbacks
    self.options = options
    self.header_group_id = ''
    self.function_complete = ''
    self.retval = ''
    self.funcname = ''
    self.funcname_ifc = ''
    self.groupname = ''
    self.values = []
    self.api_added = -1
    self.api_deprecated = -1
    self.ifc_name_func = ''
    self.ifc_name_typdef = ''

    self.child_addon_c_lib_function_shared = ''
    self.child_addon_c_lib_function_shared_tuple_in = ''
    self.child_addon_c_lib_function_shared_tuple_in_list = []
    self.child_addon_c_lib_function_shared_tuple_out = ''
    self.child_addon_c_lib_function_shared_tuple_out_list = []
    self.child_addon_c_lib_function_direct = ''
    self.child_addon_c_lib_function_direct_ptr = ''
    self.child_addon_c_lib_function_switch_case = ''
    self.child_kodi_cpp_function_source = ''
    self.child_kodi_cpp_function_header = ''
    self.dev_kit_kodi_to_addon_source = ''
    self.dev_kit_kodi_to_addon_header = ''

    self.group_data = None # The Parent class GroupData
    self.search_dir = '{}xbmc/addons/kodi-dev-kit/include/kodi/c-api/'.format(kodi_dir)

  def RegexScanFunction(self, function, file_text):
    regex_code = '^typedef\ *(.*)\ ?\(\ *ATTR_APIENTRYP PFN_(.+?)\_V([0-9])\)(?=\()\((.*?)(?=\);|\) *__).+?(|(?:__(DEPRECATED|INTRODUCED)_IN_KODI\(([0-9]+)\))?.(?:__(DEPRECATED|INTRODUCED)_IN_KODI\(([0-9]+)\)));$'
    m = re.search(regex_code, function)
    if not m or not m.group(1) or not m.group(2) or not m.group(3):
      print('ERROR: Function \'' + function + '\' not match wanted API!')
      return False

    self.retval = m.group(1)
    self.funcname = m.group(2).lower()
    self.api_added = int(m.group(3))
    self.values = []
    for value in m.group(4).split(', '):
      if value.strip() != '':
        self.values.append(value.strip())

    self.api_deprecated = -1
    if m.group(6) and m.group(6) == 'INTRODUCED':
      self.api_added = int(m.group(7))
    elif m.group(6) and m.group(6) == 'DEPRECATED':
      self.api_deprecated = int(m.group(7))
    if m.group(8) and m.group(8) == 'INTRODUCED':
      self.api_added = int(m.group(9))
    elif m.group(8) and m.group(8) == 'DEPRECATED':
      self.api_deprecated = int(m.group(9))

    self.ifc_name_typdef = 'PFN_{}_V{}'.format(m.group(2), self.api_added)
    for line in file_text.splitlines():
      m = re.search('^\ *' + self.ifc_name_typdef + '\ *([a-z0-9_].*)\;', line)
      if m and m.group(1):
        self.ifc_name_func = m.group(1)
        break

    if self.ifc_name_func != '':
      self.groupname = self.funcname.replace('_' + self.ifc_name_func, '')
    if not self.groupname:
      print('FATAL: Can\'t get groupname and function name for:')
      print('       \'{}\''.format(function))
      print('       Have you defined the use of typedef inside function structure?')
      raise

    self.funcname_ifc = '{}_v{}'.format(self.funcname, self.api_added)

    return True

  def ContainsOutOnIn(self):
    for value in self.values:
      if not 'const' in value and ('*' in value or '[' in value):
        return True
    return False

  # Log ID: 0002
  def GenerateSharedTuples(self, file_text):
    class CheckAPIUse:
      def __init__(self, parent, cnt, value, value_list):
        self.parent = parent
        self.cnt = cnt
        self.value = value
        self.done = False

        check_error = CheckCorrectFunctionValue(value)
        if check_error:
          print('FATAL: Function "{}" not contains valid values (ERROR: {})'.format(parent.function_complete, check_error))
          raise

        self.value_name = value.split()[-1].strip()
        self.value_type = value[:-len(self.value_name)].strip()

        self.msgpack_in_value = ''
        self.msgpack_out_value = ''
        self.function_value = ''

        if '...' in self.value:
          self.msgpack_in_value = ''
          self.msgpack_out_value = ''
          self.done = True
          return

        m = re.search('^[\t ]*(?:const[\t ]*)?([a-zA-Z0-9_]*)[\t ]*\*[\t ]*(?:const[\t ]*)?\*', self.value)
        if m and m.group(1) and m.group(1) in known_STANDARD_C_TYPES and 'size_t' in value_list[cnt+1] and 'size_t' in value_list[cnt+2]:
          if 'const ' in self.value or 'const*' in self.value:
            self.msgpack_in_value = 'std::vector<std::vector<{}>>'.format(m.group(1))
            self.msgpack_out_value = ''
            self.done = True
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataParent::GenerateSharedTuples'.format(parent.function_complete))
            raise
          return

        # Fixed array way 1 e.g. "enum AudioEngineChannel info[][AUDIOENGINE_CH_MAX]"
        regex_code = '^((?:const{1,}))?(.*)\ ([a-z0-9A-Z_]*?)(?!\*)?\[([a-z0-9A-Z_]*?)\]\[([a-z0-9A-Z_]*?)\]$'
        m = re.search(regex_code, value)
        if m and m.group(2) and m.group(3) and not m.group(4) and m.group(5):
          self.value_type = m.group(2).strip()
          if self.value_type == 'const char*':
            self.value_type = 'std::string'
          elif self.value_type.startswith('const struct ') and self.value_type.count('*') == 1:
            self.value_type = 'IFC_' + self.value_type.replace('const struct ', '').replace('*', '').strip()
          elif self.value_type.startswith('struct') and self.value_type.count('*') == 1:
            #tuple_in_list.append('IFC_' + self.value_type.replace('struct ', '').replace('*', '').strip())
            self.value_type = 'IFC_' + self.value_type.replace('struct ', '').replace('*', '').strip()
          elif CheckKnownEnum(self.value_type):
            self.value_type = self.value_type.replace('enum ', '')
            if self.value_type not in self.parent.group_data.used_enums:
              self.parent.group_data.used_enums.append(self.value_type)
          elif not self.value_type in known_STANDARD_C_TYPES:
            self.value_type = 'NEED_TODO_VALUES /* place 1 (0002) */'

          used_type = 'std::array<' + self.value_type + ', ' + m.group(5) + '>'
          self.msgpack_in_value = used_type
          if not m.group(1):
            self.msgpack_out_value = used_type
          self.done = True
          return

        # Fixed array way 2 e.g. "enum AudioEngineChannel (*info)[AUDIOENGINE_CH_MAX]"
        regex_code = '^((?:const{1,}))?(.*)\ \(\*([a-z0-9A-Z_]*?)\)\[([a-z0-9A-Z_]*?)\]$'
        m = re.search(regex_code, value)
        if m and m.group(2) and m.group(3) and m.group(4):
          self.value_type = m.group(2).strip()
          if self.value_type == 'const char*':
            self.value_type = 'std::string'
          elif self.value_type.startswith('const struct ') and self.value_type.count('*') == 1:
            self.value_type = 'IFC_' + self.value_type.replace('const struct ', '').replace('*', '').strip()
          elif self.value_type.startswith('struct') and self.value_type.count('*') == 1:
            #tuple_in_list.append('IFC_' + self.value_type.replace('struct ', '').replace('*', '').strip())
            self.value_type = 'IFC_' + self.value_type.replace('struct ', '').replace('*', '').strip()
          elif CheckKnownEnum(self.value_type):
            self.value_type = self.value_type.replace('enum ', '')
            if self.value_type not in self.parent.group_data.used_enums:
              self.parent.group_data.used_enums.append(self.value_type)
          elif not self.value_type in known_STANDARD_C_TYPES:
            self.value_type = 'NEED_TODO_VALUES /* place 2 (0002) */'

          used_type = 'std::array<' + self.value_type + ', ' + m.group(4) + '>'
          self.msgpack_in_value = used_type
          if not m.group(1):
            self.msgpack_out_value = used_type
          self.done = True
          return

        # Fixed array way 3 e.g. "enum AudioEngineChannel info[AUDIOENGINE_CH_MAX]"
        regex_code = '^((?:const{1,}))?(.*)\ ([a-z0-9A-Z_]*?)\[([a-z0-9A-Z_]*?)\]$'
        m = re.search(regex_code, value)
        if m and m.group(2) and m.group(3) and m.group(4):
          self.msgpack_in_value = 'ifc_{}'.format(m.group(3))
          self.value_type = m.group(2).strip()
          if self.value_type == 'const char*':
            self.value_type = 'std::string'
          elif self.value_type.startswith('const struct ') and self.value_type.count('*') == 1:
            self.value_type = 'IFC_' + self.value_type.replace('const struct ', '').replace('*', '').strip()
          elif self.value_type.startswith('struct') and self.value_type.count('*') == 1:
            #tuple_in_list.append('IFC_' + self.value_type.replace('struct ', '').replace('*', '').strip())
            self.value_type = 'IFC_' + self.value_type.replace('struct ', '').replace('*', '').strip()
          elif CheckKnownEnum(self.value_type):
            self.value_type = self.value_type.replace('enum ', '')
            if self.value_type not in self.parent.group_data.used_enums:
              self.parent.group_data.used_enums.append(self.value_type)
          elif not self.value_type in known_STANDARD_C_TYPES:
            self.value_type = 'NEED_TODO_VALUES /* place 2 (0002) */'

          used_type = 'std::array<' + self.value_type + ', ' + m.group(4) + '>'
          self.msgpack_in_value = used_type
          if not m.group(1):
            self.msgpack_out_value = used_type
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_6 (tuple) (parent)
        if self.value_type == 'const char*':
          if '[]' in self.value_name and self.value_name.count('[]') == 1:
            if len(value_list) > 1:
              i = 0
              while i+cnt < len(value_list)-1:
                if 'size_t' in value_list[i+cnt+1]:
                  self.msgpack_in_value = ('std::vector<std::string>{}'
                                          .format(' /* CheckAPIUse_WAY_6b (0006) */' if parent.options.debug else ''))
                  self.msgpack_out_value = ''
                  self.done = True
                  break
                if '[]' in value_list[i+cnt+1] and value_list[i+cnt+1].count('[]') == 1:
                  i += 1
                  continue

                print('FATAL (6b, 0006): Function:')
                print('       "{}"'.format(parent.function_complete))
                print('       Not supported on InterfaceDataParent::GenerateSharedTuples!')
                print('       Need to set second value of "{}" as "size_t".'.format(self.value))
                exit(1)
          else:
            self.msgpack_in_value = ('std::string{}'
                                     .format(' /* CheckAPIUse_WAY_6a (0006) */' if parent.options.debug else ''))
            self.msgpack_out_value = ''
            self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_7 (tuple) (parent)
        if self.value_type == 'char**':
          self.msgpack_in_value = ''
          self.msgpack_out_value = 'std::string'
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_8_1 (tuple) (parent)
        if self.value_type == 'char***' \
           or (self.value_type == 'char**' \
               and '[]' in self.value_name \
               and self.value_name.count('[]') == 1):
          if len(value_list) > 1 \
              and cnt < len(value_list)-1 \
              and 'size_t*' in value_list[cnt+1]:
            self.msgpack_in_value = ''
            self.msgpack_out_value = ('std::vector<std::string>{}'
                                       .format(' /* CheckAPIUse_WAY_8_1 (0006) */' if parent.options.debug else ''))
            self.done = True
          else:
            print('FATAL: Function:')
            print('       "{}"'.format(parent.function_complete))
            print('       Not supported on InterfaceDataParent::GenerateSharedTuples!')
            print('       Need to set second value of "{}" as "size_t".'.format(self.value))
            exit(1)
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_8 - For msgParent__IN/OUT_ on kodi-dev-kit/src/shared/api
        if self.value_type == 'char*' \
           and 'size_t' in value_list[cnt+1]:
          self.msgpack_in_value = ''
          self.msgpack_out_value = 'std::string'
          self.done = True
          return

        # CheckAPIUse_WAY_9
        if self.value_type in known_STANDARD_C_PTR_TYPES \
           and cnt < len(value_list)-1 \
           and 'size_t' in value_list[cnt+1]:
          self.msgpack_in_value = ''
          self.msgpack_out_value = ('std::vector<{}>{}'
                                    .format(self.value_type.replace('*', ''),
                                            ' /* CheckAPIUse_WAY_9 (0006) */' if parent.options.debug else ''))
          self.done = True
          return

        # CheckAPIUse_WAY_10
        if self.value_type in known_STANDARD_C_TYPES \
           and '[]' in self.value_name \
           and self.value_name.count('[]') == 1 \
           and cnt < len(value_list)-1 \
           and 'size_t' in value_list[cnt+1]:
          self.msgpack_in_value = ('std::vector<{}>{}'
                                    .format(self.value_type,
                                            ' /* CheckAPIUse_WAY_10 (0006) */' if parent.options.debug else ''))
          self.msgpack_out_value = ('std::vector<{}>{}'
                                    .format(self.value_type,
                                            ' /* CheckAPIUse_WAY_10 (0006) */' if parent.options.debug else ''))
          self.done = True
          return

        # CheckAPIUse_WAY_11
        if self.value_type in known_STANDARD_C_TYPES:
          self.msgpack_in_value = ('{}{}'
                                   .format(self.value_type,
                                           ' /* CheckAPIUse_WAY_11 (0006) */' if parent.options.debug else ''))
          self.msgpack_out_value = ''
          self.done = True
          return

        if ContainsHdlVoidPointer(self.value_type):
          self.msgpack_in_value = 'PtrValue'
          self.msgpack_out_value = ''
          self.done = True
          return

        if self.value_type.replace('const ', '') in known_STANDARD_C_PTR_TYPES \
           and cnt < len(value_list)-1 \
           and 'size_t' in value_list[cnt+1]:
          self.msgpack_in_value = ('std::vector<{}>{}'
                                   .format(self.value_type.replace('*', '').replace('const ', ''),
                                           ' /* CheckAPIUse_WAY_11 (0006) */' if parent.options.debug else ''))
          self.msgpack_out_value = ''
          self.done = True
          return

        if self.value_type in known_STANDARD_C_PTR_TYPES:
          self.msgpack_in_value = self.value_type.replace('*', '')
          self.msgpack_out_value = self.value_type.replace('*', '')
          self.done = True
          return

        if CheckKnownEnum(self.value_type):
          self.value_type = self.value_type.replace('enum ', '')
          if self.value_type.replace('*', '') not in parent.group_data.used_enums:
            parent.group_data.used_enums.append(self.value_type.replace('*', ''))

          if not '*' in self.value_type:
            self.msgpack_in_value = self.value_type
          elif '*' in self.value_type and self.value_type.count('*') == 1 and not 'const' in self.value_type:
            value = self.value_type.replace('*', '')
            self.msgpack_in_value = value
            self.msgpack_out_value = value
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataParent::GenerateSharedTuples'.format(parent.function_complete))
            raise
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_15 - For msgParent__IN/OUT_ on kodi-dev-kit/src/shared/api
        if self.value_type.startswith('struct ') \
           and self.value_type.count('*') == 1 \
           and parent.group_data.GenerateSharedStructure(self.value_type):
          value_type = self.value_type.replace('struct ', '').replace('*', '').strip()
          if value_type == 'tm':
            self.msgpack_in_value = 'IFC_{}'.format(value_type)
          else:
            self.msgpack_in_value = ''
          self.msgpack_out_value = 'IFC_{}'.format(value_type)
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_16 - For msgParent__IN/OUT_ on kodi-dev-kit/src/shared/api
        if self.value_type.startswith('const struct ') and self.value_type.count('*') == 1 and parent.group_data.GenerateSharedStructure(self.value_type):
          self.msgpack_in_value = 'IFC_{}'.format(self.value_type.replace('const struct ', '').replace('*', '').strip())
          self.msgpack_out_value = ''
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_17 - For msgParent__IN/OUT_ on kodi-dev-kit/src/shared/api
        if self.value_type.startswith('struct ') \
              and self.value_type.count('*') == 2 \
              and 'size_t*' in value_list[cnt+1] \
              and parent.group_data.GenerateSharedStructure(self.value_type):
          self.msgpack_in_value = ''
          self.msgpack_out_value = 'std::vector<IFC_{}>'.format(self.value_type.replace('struct ', '').replace('*', '').strip())
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_18 - For msgParent__IN/OUT_ on kodi-dev-kit/src/shared/api
        if self.value_type.startswith('struct ') \
              and self.value_name.count('[]') == 1 \
              and 'size_t*' in value_list[cnt+1] \
              and parent.group_data.GenerateSharedStructure(self.value_type):
          self.msgpack_in_value = 'std::vector<IFC_{}>'.format(self.value_type.replace('struct ', '').strip())
          self.msgpack_out_value = 'std::vector<IFC_{}>'.format(self.value_type.replace('struct ', '').strip())
          self.done = True
          return

        self.done = False

    if self.group_data.override_use_direct_api_only:
      return True

    if '---AUTO_GEN_PARSE<OVERRIDE;USE_INTERNAL={}>---'.format(self.funcname_ifc) in file_text:
      self.parent_addon_c_lib_function_shared_tuple_in = '/* NOTE: msgChild__IN_{} - Override active to use inside dev-kit library only */'.format(self.funcname_ifc)
      self.parent_addon_c_lib_function_shared_tuple_out = '/* NOTE: msgChild_OUT_{} - Override active to use inside dev-kit library only */'.format(self.funcname_ifc)
      return True
    if '---AUTO_GEN_PARSE<OVERRIDE;USE_HAND_MAKE={}>---'.format(self.funcname_ifc) in file_text:
      msgChild__IN_ = 'msgChild__IN_{}'.format(self.funcname_ifc)
      msgChild_OUT_ = 'msgChild_OUT_{}'.format(self.funcname_ifc)
      found_in = False
      found_Out = False

      search_dir = '{}xbmc/addons/kodi-dev-kit/include/kodi/c-api/'.format(kodi_dir)
      target_dir = kodi_dir + 'xbmc/addons/kodi-dev-kit/src/shared/api/'
      target_file = self.group_data.path.replace(search_dir, target_dir)
      with open(target_file) as f:
        target_text = f.read()
        f.close()

      for line in target_text.splitlines():
        if msgChild__IN_ in line or msgChild_OUT_ in line:
          m = re.search('typedef std::tuple<(.*)> (msgChild__IN_.*?);', line)
          if m and m.group(1) and m.group(2) == msgChild__IN_:
            self.child_addon_c_lib_function_shared_tuple_in_list = m.group(1).split(', ')
            self.child_addon_c_lib_function_shared_tuple_in = line
            found_in = True
          m = re.search('typedef std::tuple<(.*)> (msgChild_OUT_.*?);', line)
          if m and m.group(1) and m.group(2) == msgChild_OUT_:
            self.child_addon_c_lib_function_shared_tuple_out = line
            found_Out = True
          if found_in and found_Out:
            break

      if not found_in:
        self.child_addon_c_lib_function_shared_tuple_in = 'typedef std::tuple<DummyValue> {}; /* OVERRIDE;USE_HAND_MAKE used, set this by hand */'.format(msgChild__IN_)
      else:
        for entry in self.child_addon_c_lib_function_shared_tuple_in_list:
          if CheckKnownEnum(entry):
            entry = entry.replace('enum ', '')
            if entry.replace('*', '') not in self.group_data.used_enums:
              self.group_data.used_enums.append(entry)
      if not found_Out:
        self.child_addon_c_lib_function_shared_tuple_out = 'typedef std::tuple<DummyValue> {}; /* OVERRIDE;USE_HAND_MAKE used, set this by hand */'.format(msgChild_OUT_)
      else:
        for entry in self.child_addon_c_lib_function_shared_tuple_out_list:
          if CheckKnownEnum(entry):
            entry = entry.replace('enum ', '')
            if entry.replace('*', '') not in self.group_data.used_enums:
              self.group_data.used_enums.append(entry)
      return True

    haveIn = len(self.values) != 0
    haveOut = self.ContainsOutOnIn() or self.retval != 'void'

    cnt = 0
    tuple_in_values = ''
    tuple_out_values = ''
    api_use_list = []
    for value in self.values:
      apiUse = CheckAPIUse(self, cnt, value, self.values)
      api_use_list.append(apiUse)
      cnt += 1

      if apiUse.done:
        tuple_in_values += apiUse.msgpack_in_value + (', ' if apiUse.msgpack_in_value else '')
        tuple_out_values += apiUse.msgpack_out_value + (', ' if apiUse.msgpack_out_value else '')
      else:
        tuple_in_values += 'NEED_TODO_VALUES22('+value+')' + (', ' if apiUse.msgpack_in_value else '')
        tuple_out_values += '????NEED_TODO_VALUES!!!!' + (', ' if apiUse.msgpack_in_value else '')

    while tuple_in_values.endswith(', '):
      tuple_in_values = tuple_in_values[:-2]
    while tuple_out_values.endswith(', '):
      tuple_out_values = tuple_out_values[:-2]

    tuple_in = 'typedef std::tuple<'
    tuple_out = 'typedef std::tuple<'

    ret_value = ''
    if self.retval == 'char*':
      ret_value += 'std::string'
    elif self.retval in known_STANDARD_C_TYPES:
      ret_value += self.retval
    elif self.retval in known_VOID_PTR_DEFINES:
      ret_value += 'PtrValue'
    elif CheckKnownEnum(self.retval) and self.retval.count('*') == 0:
      ret_value += self.retval.replace('enum ', '')
    elif self.retval == 'char**' \
          and len(self.values) > 0 \
          and api_use_list[-1].value_type == 'size_t*' \
          and (not api_use_list[-2].value_type in known_STANDARD_C_PTR_TYPES if len(self.values) > 1 else True):
      ret_value += 'std::vector<std::string>'
    elif self.retval != 'void':
      ret_value += 'NEED_TODO_VALUES23'

    if ret_value:
      self.child_addon_c_lib_function_shared_tuple_out_list.append(ret_value)
      tuple_out += ret_value

    if self.ContainsOutOnIn():
      tuple_out += (', ' if ret_value else '')

    self.child_addon_c_lib_function_shared_tuple_in_list += tuple_in_values.split(', ') if tuple_in_values != '' else []
    self.child_addon_c_lib_function_shared_tuple_out_list += tuple_out_values.split(', ') if tuple_out_values != '' else []

    tuple_in += tuple_in_values
    if tuple_in == 'typedef std::tuple<':
      tuple_in += 'DummyValue'
    tuple_out += tuple_out_values
    if tuple_out == 'typedef std::tuple<':
      tuple_out += 'DummyValue'

    tuple_in += '> msgChild__IN_' + self.funcname_ifc + ('; /* Autogenerated */' if not 'NEED_TODO_VALUES' in tuple_in else '; /* Need hand edit here, remove this note text after change! */')
    tuple_out += '> msgChild_OUT_' + self.funcname_ifc + ('; /* Autogenerated */' if not 'NEED_TODO_VALUES' in tuple_out else '; /* Need hand edit here, remove this note text after change! */')

    self.child_addon_c_lib_function_shared_tuple_in = tuple_in
    self.child_addon_c_lib_function_shared_tuple_out = tuple_out

    return True

  def GenerateToAddonDirectFuncTable(self, file_text):
    if '---AUTO_GEN_PARSE<OVERRIDE;USE_INTERNAL={}>---'.format(self.funcname_ifc) in file_text:
      self.group_data.to_addon_direct_func_table.append('  /* Function "{}" only used inside dev-kit library only */'.format(self.funcname))
      return True

    values = []
    retval = ''
    if '---AUTO_GEN_PARSE<OVERRIDE;USE_HAND_MAKE={}>---'.format(self.funcname_ifc) in file_text:
      scan_file = self.group_data.path.replace(self.search_dir, '{}xbmc/addons/interface/api/'.format(kodi_dir))

      file_text = CodeGetField_AUTO_GEN_PARSE(scan_file, 'HAND_EDITED_FIELD={}'.format(self.funcname_ifc.upper()))
      file_text = ' '.join(file_text.replace('\n', ' ').split(';')[0].split()).replace('( ', '(')
      m = re.search('(.*)[ \t](kodi.+?)(?=\()\((.*?)\)', file_text)
      if m and m.group(1) and m.group(2) and m.group(3):
        values = m.group(3).split(', ')
        retval = m.group(1)
      else:
        print('FATAL: Failed to scan "{}" on GenerateToAddonDirectFuncTable').format(file_text)
        raise
    else:
      values = self.values
      retval = self.retval

    func_values = ''
    current_value = 1
    for value in values:
      if value != '...':
        value_name = value.split()[-1].strip()
        value_type = value[:-len(value_name)].strip()
        if '[' in value_name:
          value_type += '[' + value_name.split('[', 1)[-1]
      else:
        value_name = ''
        value_type = '...'

      func_values += value_type + (', ' if current_value < len(values) else '')
      current_value += 1

    entry = ('typedef {}(ATTR_INT_APIENTRYP PFN_INT_{}_V{})(void*{});'
              .format(retval,
                      self.funcname.upper(),
                      self.api_added,
                      ', ' + func_values if len(func_values) > 0 else ''))
    self.group_data.to_addon_api_list_typedef.append(entry)

    entry = ('  PFN_INT_{}_V{} {};'
              .format(self.funcname.upper(),
                      self.api_added,
                      self.funcname_ifc))
    self.group_data.to_addon_direct_func_table.append(entry)

    return True

  def GenerateAddonSourceSwitchCase(self, file_text):
    class CheckAPIUse:
      def __init__(self, parent, cnt, value, value_list, ignored_count):
        self.parent = parent
        self.cnt = cnt
        self.value = value
        self.set_call = ''
        self.set_static = False
        self.set_override = ''
        self.additional_code_1 = ''
        self.additional_code_2 = ''
        self.additional_code_3 = ''
        self.additional_code_4 = ''
        self.ignore_next = False
        self.return_value = ''
        self.ignored_count = ignored_count

        self.value_name = value.split()[-1].strip()
        self.value_type = value[:-len(self.value_name)].strip()

        self.done = False

        self.msgpack_in_value = ''
        self.function_value = ''
        self.msgpack_out_value = ''
        self.no_in = False

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_1
        if '...' in self.value:
          self.msgpack_in_value = ''
          self.msgpack_out_value = ''
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_2
        m = re.search('^[\t ]*(?:const[\t ]*)?([a-zA-Z0-9_]*)[\t ]*\*[\t ]*(?:const[\t ]*)?\*', self.value)
        if m and m.group(1) \
             and m.group(1) in known_STANDARD_C_TYPES \
             and self.cnt-self.ignored_count+2 < len(parent.values) \
             and 'size_t' in value_list[self.cnt-self.ignored_count+1] \
             and 'size_t' in value_list[self.cnt-self.ignored_count+2]:
          if 'const ' in self.value or 'const*' in self.value:
            size_1_name = value_list[self.cnt-self.ignored_count+1].split()[-1].strip()
            size_2_name = value_list[self.cnt-self.ignored_count+2].split()[-1].strip()
            self.msgpack_in_value = 'std::vector<std::vector<{}>>& ifc_{} = std::get<{}>(t);{}'.format(m.group(1), self.value_name, self.cnt-self.ignored_count, ' /* CheckAPIUse_WAY_2 (0004) */' if parent.options.debug else '')
            self.function_value = '{}{}'.format(self.value_name, ' /* CheckAPIUse_WAY_2 (0004) */' if parent.options.debug else '')
            self.additional_code_2 = '      {}** {} = new {}*[ifc_{}.size()];{}'.format(m.group(1), self.value_name, m.group(1),
                                                                                        self.value_name, ' /* CheckAPIUse_WAY_2 (0004) */' if parent.options.debug else '')
            self.additional_code_2 += '      for (size_t i = 0; i < ifc_{}.size(); ++i){}'.format(self.value_name, ' /* CheckAPIUse_WAY_2 (0004) */' if parent.options.debug else '')
            self.additional_code_2 += '        {}[i] = ifc_{}[i].data();{}'.format(self.value_name, self.value_name, ' /* CheckAPIUse_WAY_2 (0004) */' if parent.options.debug else '')
            self.additional_code_4 = '      delete[] {};{}\n'.format(self.value_name, ' /* CheckAPIUse_WAY_2 (0004) */' if parent.options.debug else '')
            self.done = True
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataParent::GenerateKodiSourceCPPSwitchCase'.format(parent.function_complete))
            raise
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_3
        # Fixed array way 1 e.g. "enum AudioEngineChannel info[][AUDIOENGINE_CH_MAX]"
        regex_code = '^((?:const{1,}))?(.*)\ ([a-z0-9A-Z_]*?)(?!\*)?\[([a-z0-9A-Z_]*?)\]\[([a-z0-9A-Z_]*?)\]$'
        m = re.search(regex_code, value)
        if m and m.group(2) and m.group(3) and not m.group(4) and m.group(5):
          self.value_type = m.group(2).strip()
          if self.value_type == 'const char*':
            self.value_type = 'std::string'
          elif self.value_type.startswith('const struct ') and self.value_type.count('*') == 1:
            self.value_type = 'IFC_' + self.value_type.replace('const struct ', '').replace('*', '').strip()
          elif self.value_type.startswith('struct') and self.value_type.count('*') == 1:
            #tuple_in_list.append('IFC_' + value_type.replace('struct ', '').replace('*', '').strip())
            self.value_type = 'IFC_' + self.value_type.replace('struct ', '').replace('*', '').strip()
          elif CheckKnownEnum(self.value_type):
            self.value_type = value_type.replace('enum ', '')
            if self.value_type.replace('*', '') not in parent.group_data.used_enums:
              parent.group_data.used_enums.append(self.value_type.replace('*', ''))
          elif not self.value_type in known_STANDARD_C_TYPES:
            self.value_type = 'NEED_TODO_VALUES /* CheckAPIUse_WAY_3 (0004) */'

          self.msgpack_in_value = ('std::array<{}, {}>& {} = std::get<{}>(t);{}'
                                   .format(self.value_type,
                                           m.group(5),
                                           m.group(3),
                                           cnt-ignored_count,
                                           ' /* CheckAPIUse_WAY_3 (0004) */' if parent.options.debug else ''))
          self.function_value = ('{}.data(){}'
                                 .format(m.group(3),
                                         ' /* CheckAPIUse_WAY_3 (0004) */' if parent.options.debug else ''))
          self.msgpack_out_value = '{}{}'.format(m.group(3), ' /* CheckAPIUse_WAY_5 (0004) */' if parent.options.debug else '')
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_4
        # Fixed array way 2 e.g. "enum AudioEngineChannel (*info)[AUDIOENGINE_CH_MAX]"
        regex_code = '^((?:const{1,}))?(.*)\ \(\*([a-z0-9A-Z_]*?)\)\[([a-z0-9A-Z_]*?)\]$'
        m = re.search(regex_code, value)
        if m and m.group(2) and m.group(3) and m.group(4):
          self.value_type = m.group(2).strip()
          if self.value_type == 'const char*':
            self.value_type = 'std::string'
          elif self.value_type.startswith('const struct ') and self.value_type.count('*') == 1:
            self.value_type = 'IFC_' + self.value_type.replace('const struct ', '').replace('*', '').strip()
          elif self.value_type.startswith('struct') and self.value_type.count('*') == 1:
            #tuple_in_list.append('IFC_' + value_type.replace('struct ', '').replace('*', '').strip())
            self.value_type = 'IFC_' + self.value_type.replace('struct ', '').replace('*', '').strip()
          elif CheckKnownEnum(self.value_type):
            self.value_type = self.value_type.replace('enum ', '')
            if self.value_type.replace('*', '') not in parent.group_data.used_enums:
              parent.group_data.used_enums.append(self.value_type.replace('*', ''))
          elif not self.value_type in known_STANDARD_C_TYPES:
            self.value_type = 'NEED_TODO_VALUES /* CheckAPIUse_WAY_4 (0004) */'

          self.msgpack_in_value = ('std::array<{}, {}>& {} = std::get<{}>(t);{}'
                                   .format(self.value_type,
                                           m.group(4),
                                           m.group(3),
                                           cnt-ignored_count,
                                           ' /* CheckAPIUse_WAY_4 (0004) */' if parent.options.debug else ''))
          self.function_value = ('{}.data(){}'
                                 .format(m.group(3),
                                         ' /* CheckAPIUse_WAY_4 (0004) */' if parent.options.debug else ''))
          self.msgpack_out_value = '{}{}'.format(m.group(3), ' /* CheckAPIUse_WAY_4 (0004) */' if parent.options.debug else '')
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_5
        # Fixed array way 3 e.g. "enum AudioEngineChannel info[AUDIOENGINE_CH_MAX]"
        regex_code = '^((?:const{1,}))?(.*)\ ([a-z0-9A-Z_]*?)\[([a-z0-9A-Z_]*?)\]$'
        m = re.search(regex_code, value)
        if m and m.group(2) and m.group(3) and m.group(4):
          self.value_type = m.group(2).strip()
          if self.value_type == 'const char*':
            self.value_type = 'std::string'
          elif self.value_type.startswith('const struct ') and self.value_type.count('*') == 1:
            self.value_type = 'IFC_' + self.value_type.replace('const struct ', '').replace('*', '').strip()
          elif self.value_type.startswith('struct') and self.value_type.count('*') == 1:
            #tuple_in_list.append('IFC_' + value_type.replace('struct ', '').replace('*', '').strip())
            self.value_type = 'IFC_' + self.value_type.replace('struct ', '').replace('*', '').strip()
          elif CheckKnownEnum(self.value_type):
            self.value_type = self.value_type.replace('enum ', '')
            if self.value_type.replace('*', '') not in parent.group_data.used_enums:
              parent.group_data.used_enums.append(self.value_type.replace('*', ''))
          elif not self.value_type in known_STANDARD_C_TYPES:
            self.value_type = 'NEED_TODO_VALUES /* CheckAPIUse_WAY_5 (0004) */'

          self.msgpack_in_value = ('std::array<{}, {}>& {} = std::get<{}>(t);{}'
                                   .format(self.value_type,
                                           m.group(4),
                                           m.group(3),
                                           cnt-ignored_count,
                                           ' /* CheckAPIUse_WAY_5 (0004) */' if parent.options.debug else ''))
          self.function_value = ('{}.data(){}'
                                 .format(m.group(3),
                                         ' /* CheckAPIUse_WAY_5 (0004) */' if parent.options.debug else ''))
          self.msgpack_out_value = '{}{}'.format(m.group(3), ' /* CheckAPIUse_WAY_5 (0004) */' if parent.options.debug else '')
          self.done = True
          return

        if cnt == 0:
          if self.value_type.replace('const ', '') == self.parent.groupname.upper() + '_HDL' \
             and ContainsHdlVoidPointer(self.value_type):
            self.function_value = 'auto_gen_hdl'
            self.done = True
            return
          if self.value_type.replace('const ', '') == self.parent.groupname.upper() + '_HDL*' \
             and self.value_type.replace('const ', '').replace('*', '') in known_VOID_PTR_DEFINES:
            self.msgpack_in_value = '{} auto_gen_hdl = nullptr;'.format(self.value_type.replace('*', ''))
            self.function_value = '&auto_gen_hdl'
            self.msgpack_out_value = 'PtrValue(auto_gen_hdl)'
            self.no_in = True
            self.done = True
            return
        else:
          #if self.value_type.replace('const ', '') == self.parent.groupname.upper() + '_HDL' \
             #and self.value_type.replace('const ', '') in known_VOID_PTR_DEFINES:
            #self.msgpack_in_value = ('{} hdl = {}(std::get<{}>(t));'
                                     #.format(self.value_type,
                                             #self.value_type,
                                             #self.cnt-self.ignored_count,
                                             #))
            #self.function_value = self.value_name
            #self.done = True
            #return
          if self.value_type.replace('const ', '') == self.parent.groupname.upper() + '_HDL*' \
             and self.value_type.replace('const ', '').replace('*', '') in known_VOID_PTR_DEFINES:
            self.done = True
            return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_6 (target call, Addon side) (child)
        if self.value_type == 'const char*':
          if '[]' in self.value_name and self.value_name.count('[]') == 1:
            if len(value_list) > 1:
              i = 0
              while i+cnt < len(value_list)-1:
                if 'size_t' in value_list[i+cnt+1]:
                  parent.group_data.AddAdditionalAddonLibIncludes('#include <string>')
                  parent.group_data.AddAdditionalAddonLibIncludes('#include <vector>')
                  self.value_name = self.value_name.replace('[]', '')
                  self.function_value = ('{}.data(){}'
                                        .format(self.value_name,
                                                ' /* CheckAPIUse_WAY_6c (0004) */' if parent.options.debug else ''))
                  self.msgpack_in_value = ('const std::vector<std::string>& cpp_{} = std::get<{}>(t);{}'
                                          .format(self.value_name,
                                                  i+self.cnt-self.ignored_count,
                                                  ' /* CheckAPIUse_WAY_6c (0004) */' if parent.options.debug else ''))
                  self.additional_code_2 += ('\n')
                  self.additional_code_2 += ('  std::vector<const char*> {};{}\n'
                                            .format(self.value_name,
                                                    ' /* CheckAPIUse_WAY_6c (0004) */' if parent.options.debug else ''))
                  self.additional_code_2 += ('  {}.reserve({});{}\n'
                                            .format(self.value_name,
                                                    value_list[i+cnt+1].split()[-1].strip(),
                                                    ' /* CheckAPIUse_WAY_6c (0004) */' if parent.options.debug else ''))
                  self.additional_code_2 += ('  for (size_t i = 0; i < {}; ++i){}\n'
                                            .format(value_list[i+cnt+1].split()[-1].strip(),
                                                    ' /* CheckAPIUse_WAY_6c (0004) */' if parent.options.debug else ''))
                  self.additional_code_2 += ('  {\n')
                  self.additional_code_2 += ('      {}.emplace_back(cpp_{}[i].c_str());{}\n'
                                            .format(self.value_name,
                                                    self.value_name,
                                                    ' /* CheckAPIUse_WAY_6c (0004) */' if parent.options.debug else ''))
                  self.additional_code_2 += ('  }\n')
                  self.additional_code_2 += ('  assert(cpp_{}.size() == {});\n'
                                            .format(self.value_name,
                                                    value_list[i+cnt+1].split()[-1].strip()))
                  self.additional_code_2 += ('\n')
                  self.msgpack_out_value = ''
                  self.done = True
                  break
                if '[]' in value_list[i+cnt+1] and value_list[i+cnt+1].count('[]') == 1:
                  i += 1
                  continue

                print('FATAL (6c, 0004): Function:')
                print('       "{}"'.format(parent.function_complete))
                print('       Not supported on InterfaceDataParent::GenerateSharedTuples!')
                print('       Need to set second value of "{}" as "size_t".'.format(self.value))
                exit(1)
          else:
            self.function_value = ('{}.c_str(){}'
                                    .format(self.value_name,
                                            ' /* CheckAPIUse_WAY_6a (0004) */' if parent.options.debug else ''))
            self.msgpack_in_value = ('const std::string& {} = std::get<{}>(t);{}'
                                    .format(self.value_name,
                                            self.cnt-self.ignored_count,
                                            ' /* CheckAPIUse_WAY_6a (0004) */' if parent.options.debug else ''))
            self.msgpack_out_value = ''
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_7
        if self.value_type == 'char**':
          self.msgpack_in_value = 'char* {} = nullptr;'.format(self.value_name, ' /* CheckAPIUse_WAY_6 (0004) */' if parent.options.debug else '')
          self.function_value = '&{}{}'.format(self.value_name, ' /* CheckAPIUse_WAY_6 (0004) */' if parent.options.debug else '')
          self.msgpack_out_value = '{} ? {} : ""{}'.format(self.value_name, self.value_name, ' /* CheckAPIUse_WAY_6 (0004) */' if parent.options.debug else '')
          self.additional_code_4  = '      if ({}){}\n'.format(self.value_name, ' /* CheckAPIUse_WAY_6 (0004) */' if parent.options.debug else '')
          self.additional_code_4 += '        free({});{}'.format(self.value_name, ' /* CheckAPIUse_WAY_6 (0004) */' if parent.options.debug else '')
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_8

        if self.value_type == 'char*' \
           and self.cnt-self.ignored_count+1 < len(parent.values) \
           and 'size_t' in value_list[self.cnt+self.ignored_count+1]:
          self.msgpack_in_value = ('std::string {};{}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_8 (0004) */' if parent.options.debug else ''))
          self.additional_code_2 = ('      {}.reserve({});{}'
                                    .format(self.value_name,
                                            value_list[cnt+ignored_count+1].split()[-1].strip(),
                                            ' /* CheckAPIUse_WAY_8 (0004) */' if parent.options.debug else ''))
          self.function_value = ('&{}[0]'
                                 .format(self.value_name,
                                         ' /* CheckAPIUse_WAY_8 (0004) */' if parent.options.debug else ''))
          self.msgpack_out_value = ('{}{}'
                                    .format(self.value_name,
                                            ' /* CheckAPIUse_WAY_8 (0004) */' if parent.options.debug else ''))
          self.ignored_count += 1
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_8_1 (shared call to addon, Kodi side) (parent)
        if self.value_type == 'char***' \
           or (self.value_type == 'char**' \
               and '[]' in self.value_name \
               and self.value_name.count('[]') == 1):
          if len(value_list) > 1 \
              and cnt_in < len(value_list)-1 \
              and 'size_t*' in value_list[cnt_in+1]:
            size_value = value_list[cnt+ignored_count+1].split()[-1].strip()
            self.value_name = self.value_name.replace('[]', '')
            self.msgpack_in_value = ('char** {} = nullptr;{}'
                                    .format(self.value_name,
                                            ' /* CheckAPIUse_WAY_8_1 (0004) */' if parent.options.debug else ''))
            self.function_value = ('&{}{}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_8_1 (0004) */' if parent.options.debug else ''))
            self.additional_code_3  = ('      std::vector<std::string> cpp_{};{}\n'
                                       .format(self.value_name,
                                               ' /* CheckAPIUse_WAY_8 (0004) */' if parent.options.debug else ''))
            self.additional_code_3 += ('      cpp_{}.reserve({});{}\n'
                                       .format(self.value_name,
                                               size_value,
                                               ' /* CheckAPIUse_WAY_8 (0004) */' if parent.options.debug else ''))
            self.additional_code_3 += ('      if ({})\n'
                                       .format(self.value_name))
            self.additional_code_3 += ('      {\n')
            self.additional_code_3 += ('        for (size_t i = 0; i < {}; ++i){}\n'
                                       .format(size_value,
                                              ' /* CheckAPIUse_WAY_8 (0004) */' if parent.options.debug else ''))
            self.additional_code_3 += ('        {\n')
            self.additional_code_3 += ('          if ({}[i])\n'
                                       .format(self.value_name))
            self.additional_code_3 += ('          {\n')
            self.additional_code_3 += ('            cpp_{}.emplace_back({}[i]);\n'
                                       .format(self.value_name,
                                               self.value_name,
                                               ' /* CheckAPIUse_WAY_8 (0004) */' if parent.options.debug else ''))
            self.additional_code_3 += ('            free({}[i]);\n'
                                       .format(self.value_name))
            self.additional_code_3 += ('          }\n')
            self.additional_code_3 += ('          else\n')
            self.additional_code_3 += ('          {\n')
            self.additional_code_3 += ('            cpp_{}.emplace_back("");{}\n'
                                       .format(self.value_name,
                                               ' /* CheckAPIUse_WAY_8 (0004) */' if parent.options.debug else ''))
            self.additional_code_3 += ('          }\n')
            self.additional_code_3 += ('        }\n')
            self.additional_code_3 += ('        free({});\n'
                                       .format(self.value_name))
            self.additional_code_3 += ('      }\n')
            self.msgpack_out_value = ('cpp_{}{}'
                                     .format(self.value_name,
                                             ' /* CheckAPIUse_WAY_8 (0004) */' if parent.options.debug else ''))
            self.ignored_count += 1
            self.done = True
          else:
            print('FATAL: Function:')
            print('       "{}"'.format(parent.function_complete))
            print('       Not supported on InterfaceDataParent::GenerateKodiSourceCPPSwitchCase!')
            print('       Need to set second value of "{}" as "size_t".'.format(self.value))
            exit(1)
          return

        # CheckAPIUse_WAY_10
        if self.value_type in known_STANDARD_C_TYPES \
           and '[]' in self.value_name \
           and self.value_name.count('[]') == 1 \
           and cnt < len(value_list)-1 \
           and 'size_t' in value_list[cnt+1]:
          self.msgpack_in_value = 'TODO!!!2222222'
          self.additional_code_2  = ('std::vector<{}> {}({});{}'
                                     .format(self.value_type.replace('*', ''),
                                             self.value_name,
                                             value_list[cnt+ignored_count+1].split()[-1].strip(),
                                             ' /* CheckAPIUse_WAY_10 (0004) */' if parent.options.debug else ''))
          self.function_value = ('{}.data(){}'
                                 .format(self.value_name,
                                         ' /* CheckAPIUse_WAY_10 (0004) */' if parent.options.debug else ''))
          self.msgpack_out_value = ('{}{}'
                                    .format(self.value_name,
                                            ' /* CheckAPIUse_WAY_10 (0004) */' if parent.options.debug else ''))
          self.ignored_count += 1
          self.ignore_next = True
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_11
        if self.value_type in known_STANDARD_C_TYPES:
          self.msgpack_in_value = ('{} {} = std::get<{}>(t);{}'
                                   .format(self.value_type,
                                           self.value_name,
                                           self.cnt-self.ignored_count,
                                           ' /* CheckAPIUse_WAY_9 (0004) */' if parent.options.debug else ''))
          self.function_value = ('{}{}'
                                 .format(self.value_name,
                                         ' /* CheckAPIUse_WAY_9 (0004) */' if parent.options.debug else ''))
          self.msgpack_out_value = ''
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_12
        if self.value_type in known_STANDARD_C_PTR_TYPES \
              and cnt+ignored_count < len(value_list)-1 \
              and 'size_t' in value_list[cnt+ignored_count+1] \
              and self.value_type.count('*') == 1:
          self.msgpack_in_value = ''
          self.additional_code_2  = ('std::vector<{}> {}({});{}'
                                     .format(self.value_type.replace('*', ''),
                                             self.value_name,
                                             value_list[cnt+ignored_count+1].split()[-1].strip(),
                                             ' /* CheckAPIUse_WAY_10 (0004) */' if parent.options.debug else ''))
          self.function_value = ('{}.data(){}'
                                 .format(self.value_name,
                                         ' /* CheckAPIUse_WAY_10 (0004) */' if parent.options.debug else ''))
          self.msgpack_out_value = ('{}{}'
                                    .format(self.value_name,
                                            ' /* CheckAPIUse_WAY_10 (0004) */' if parent.options.debug else ''))
          self.ignored_count += 1
          self.ignore_next = True
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_11
        if self.value_type.replace('const ', '') in known_STANDARD_C_PTR_TYPES \
              and cnt+ignored_count < len(value_list)-1 \
              and 'size_t' in value_list[cnt+ignored_count+1] \
              and self.value_type.count('*') == 1:
          self.msgpack_in_value = ('const std::vector<{}>& {} = std::get<{}>(t);{}'
                                   .format(self.value_type.replace('*', '').replace('const ', ''),
                                           self.value_name,
                                           self.cnt-self.ignored_count,
                                           ' /* CheckAPIUse_WAY_11 (0004) */' if parent.options.debug else ''))
          self.function_value = ('{}.data(){}'
                                 .format(self.value_name,
                                         ' /* CheckAPIUse_WAY_11 (0004) */' if parent.options.debug else ''))
          if not 'const ' in self.value_type:
            self.ignored_count += 1
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_12
        if ContainsHdlVoidPointer(self.value_type):
          if self.value_type == 'KODI_OWN_HDL':
            self.function_value = ('auto_gen_hdl{}'.format(' /* CheckAPIUse_WAY_12 (0004) */' if parent.options.debug else ''))
          else:
            self.function_value = ('{}{}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_12 (0004) */' if parent.options.debug else ''))
            self.msgpack_in_value = ('{} {} = reinterpret_cast<{}>(std::get<{}>(t));{}'
                                     .format(self.value_type,
                                             self.value_name,
                                             self.value_type,
                                             self.cnt-self.ignored_count,
                                             ' /* CheckAPIUse_WAY_12 (0004) */' if parent.options.debug else ''))
          self.done = True
          return


        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_12b
        if (ContainsHdlVoidPointer(self.value_type.replace('*', '')) \
              and self.value_type.count('*') == 1):
          self.msgpack_in_value = ('{} {} = nullptr;{}'
                                   .format(self.value_type.replace('*', ''),
                                           self.value_name,
                                           ' /* CheckAPIUse_WAY_12b (0005) */' if parent.options.debug else ''))
          self.function_value = ('&{}{}'
                                  .format(self.value_name,
                                          ' /* CheckAPIUse_WAY_12 (0004) */' if parent.options.debug else ''))
          self.msgpack_out_value = ('*{} = reinterpret_cast<{}>(std::get<{}>(t));{}'
                                    .format(self.value_name,
                                            self.value_type.replace('*', ''),
                                            self.cnt-self.ignored_count,
                                            ' /* CheckAPIUse_WAY_12b (0005) */' if parent.options.debug else ''))
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_13
        if self.value_type.replace('const ', '') in known_STANDARD_C_PTR_TYPES:
          if self.value_type.count('*') == 1:
            self.msgpack_in_value = ('{} {} = std::get<{}>(t);{}'
                                     .format(self.value_type.replace('*', ''),
                                             self.value_name,
                                             self.cnt-self.ignored_count,
                                             ' /* CheckAPIUse_WAY_13 (0004) */' if parent.options.debug else ''))
            self.function_value = ('&{}{}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_13 (0004) */' if parent.options.debug else ''))
            if not 'const ' in self.value_type:
              self.msgpack_out_value = ('{}{}'
                                        .format(self.value_name,
                                                ' /* CheckAPIUse_WAY_13 (0004) */' if parent.options.debug else ''))
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataParent::GenerateKodiSourceCPPSwitchCase (on CheckAPIUse_WAY_13)'.format(parent.function_complete))
            exit(1)
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_14
        if CheckKnownEnum(self.value_type):
          if self.value_type.count('*') == 0:
            self.msgpack_in_value = ('{} {} = std::get<{}>(t);{}'
                                     .format(self.value_type,
                                             self.value_name,
                                             self.cnt-self.ignored_count,
                                             ' /* CheckAPIUse_WAY_14a (0004) */' if parent.options.debug else ''))
            self.function_value = ('{}{}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_14a (0004) */' if parent.options.debug else ''))
          elif self.value_type.count('*') == 1:
            self.msgpack_in_value = ('{} {} = std::get<{}>(t);{}'
                                     .format(self.value_type.replace('*', ''),
                                             self.value_name,
                                             self.cnt-self.ignored_count,
                                             ' /* CheckAPIUse_WAY_14a (0004) */' if parent.options.debug else ''))
            self.function_value = ('&{}{}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_14b (0004) */' if parent.options.debug else ''))
            if not 'const ' in self.value_type:
              self.msgpack_out_value = ('{}{}'
                                        .format(self.value_name,
                                                ' /* CheckAPIUse_WAY_14b (0004) */' if parent.options.debug else ''))
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataParent::GenerateKodiSourceCPPSwitchCase (on CheckAPIUse_WAY_14)'.format(parent.function_complete))
            exit(1)
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_15
        if self.value_type.startswith('struct ') \
           and self.value_type.count('*') == 1 \
           and parent.group_data.KnownSharedStructure(self.value_type):
          struct_name = self.value_type.replace('struct ', '').replace('*', '').strip()

          if struct_name == 'tm':
            self.additional_code_1 = ('      {} {};{}'
                                      .format(struct_name,
                                              self.value_name,
                                              ' /* CheckAPIUse_WAY_15 (0001) */' if parent.options.debug else ''))
            self.msgpack_in_value = ('std::get<{}>(t).SetCStructure(&{});{}'
                                    .format(self.cnt-self.ignored_count,
                                            self.value_name,
                                            ' /* CheckAPIUse_WAY_15 (0001) */' if parent.options.debug else ''))
          else:
            self.ignored_count += 1
            self.msgpack_in_value = ('{} {};{}'
                                    .format(self.value_type.replace('*', ''),
                                            self.value_name,
                                            ' /* CheckAPIUse_WAY_15 (0001) */' if parent.options.debug else ''))

          self.function_value = ('&{}{}'
                                 .format(self.value_name,
                                         ' /* CheckAPIUse_WAY_15 (0001) */' if parent.options.debug else ''))
          self.msgpack_out_value = ('&{}{}'
                                    .format(self.value_name,
                                            ' /* CheckAPIUse_WAY_15 (0001) */' if parent.options.debug else ''))

          shared_struct = self.value_type.replace('*', '')
          if parent.group_data.KnownSharedStructureWithClean(shared_struct):
            self.additional_code_4 += ('     IFC_{}::CleanCStructure(&{});\n'
                                       .format(shared_struct.replace('struct ', ''),
                                               self.value_name))
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_16
        if self.value_type.startswith('const struct ') and self.value_type.count('*') == 1 and parent.group_data.KnownSharedStructure(self.value_type):
          struct_name = self.value_type.replace('*', '').replace('const struct ', '')
          self.additional_code_1 = '      {} {};{}'.format(struct_name, self.value_name, ' /* CheckAPIUse_WAY_16 (0004) */' if parent.options.debug else '')
          self.msgpack_in_value = 'std::get<{}>(t).SetCStructure(&{});{}'.format(self.cnt-self.ignored_count, self.value_name, ' /* CheckAPIUse_WAY_16 (0004) */' if parent.options.debug else '')
          self.function_value = '&{}{}'.format(self.value_name, ' /* CheckAPIUse_WAY_16 (0004) */' if parent.options.debug else '')
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_17 - For xbmc/addons/interface/api/*
        if self.value_type.startswith('struct ') \
              and self.value_type.count('*') == 2 \
              and self.cnt-self.ignored_count+1 < len(parent.values) \
              and 'size_t*' in value_list[self.cnt-self.ignored_count+1] \
              and parent.group_data.GenerateSharedStructure(self.value_type):

          self.ignored_count += 1
          struct_name = self.value_type.replace('**', '').replace('struct ', '')
          size_name = value_list[cnt+ignored_count+1].split()[-1].strip()
          self.msgpack_in_value = '{} {} = nullptr;{}'.format(self.value_type.replace('**', '*'), self.value_name, ' /* CheckAPIUse_WAY_17 (0004) */' if parent.options.debug else '')
          self.function_value = '&{}{}'.format(self.value_name, ' /* CheckAPIUse_WAY_17 (0004) */' if parent.options.debug else '')
          self.msgpack_out_value = 'ifc_{}'.format(self.value_name)
          self.additional_code_3 = ('    std::vector<IFC_{}> ifc_{};{}\n'
                                    .format(struct_name,
                                            self.value_name,
                                            ' /* CheckAPIUse_WAY_17 (0004) */' if parent.options.debug else ''))
          self.additional_code_3 += '    if ({})\n'.format(self.value_name)
          self.additional_code_3 += '    {\n'
          self.additional_code_3 += '      ifc_{}.reserve({});\n'.format(self.value_name, size_name)
          self.additional_code_3 += '      for (size_t i = 0; i < {}; ++i)\n'.format(size_name)
          self.additional_code_3 += '      {\n'
          self.additional_code_3 += '        ifc_{}.emplace_back(&{}[i]);'.format(self.value_name, self.value_name)
          self.additional_code_3 += '        ifc_{}[i].CleanCStructure(&{}[i]);'.format(self.value_name, self.value_name)
          self.additional_code_3 += '      }\n'
          self.additional_code_3 += '      free({});\n'.format(self.value_name)
          self.additional_code_3 += '    }\n'
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_18 - For msgParent__IN/OUT_ on kodi-dev-kit/src/shared/api
        if self.value_type.startswith('struct ') \
              and self.value_name.count('[]') == 1 \
              and 'size_t*' in value_list[cnt+1] \
              and parent.group_data.GenerateSharedStructure(self.value_type):
          value_name = self.value_name.replace('[]', '')

          self.msgpack_in_value = ('std::vector<IFC_{}>& ifc_{} = std::get<{}>(t);{}'
                                    .format(self.value_type.replace('struct ', ''),
                                            value_name,
                                            self.cnt-self.ignored_count,
                                            ' /* CheckAPIUse_WAY_18 (0004) */' if parent.options.debug else ''))
          self.additional_code_2 = ('      std::vector<{}> {}({});{}\n'
                                     .format(self.value_type,
                                             value_name,
                                             value_list[cnt+ignored_count+1].split()[-1].strip(),
                                             ' /* CheckAPIUse_WAY_18 (0004) */' if parent.options.debug else ''))
          self.additional_code_2 += ('      for (size_t i = 0; i < {}; ++i)\n'
                                     .format(value_list[cnt+ignored_count+1].split()[-1].strip()))
          self.additional_code_2 += ('      {\n')
          self.additional_code_2 += ('        ifc_{}[i].SetCStructure(&{}[i]);\n'
                                     .format(value_name, value_name))
          self.additional_code_2 += ('      }\n')
          self.function_value = ('{}.data(){}'
                                 .format(value_name,
                                         ' /* CheckAPIUse_WAY_18 (0004) */' if parent.options.debug else ''))
          self.additional_code_3 = ('      for (size_t i = 0; i < {}; ++i)\n'
                                     .format(value_list[cnt+ignored_count+1].split()[-1].strip()))
          self.additional_code_3 += ('      {\n')
          self.additional_code_3 += ('        ifc_{}[i] = IFC_{}(&{}[i]);\n'
                                     .format(value_name,
                                             self.value_type.replace('struct ', ''),
                                             value_name))
          self.additional_code_3 += ('      }\n')
          self.msgpack_out_value = ('ifc_{}{}'
                                    .format(value_name,
                                            ' /* CheckAPIUse_WAY_18 (0004) */' if parent.options.debug else ''))
          self.done = True
          return

    if self.group_data.override_use_direct_api_only:
      return True

    code  = '    case funcChild_{}:\n'.format(self.funcname_ifc)
    code += '    {\n'
    code += '      // Original API call: {}\n'.format(self.function_complete)
    code += '      // Tuple in:          {}\n'.format(self.child_addon_c_lib_function_shared_tuple_in)
    code += '      // Tuple out:         {}\n'.format(self.child_addon_c_lib_function_shared_tuple_out)
    code += '\n'

    if '---AUTO_GEN_PARSE<OVERRIDE;USE_HAND_MAKE={}>---'.format(self.funcname_ifc) in file_text:
      code += '  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}>---*/\n'.format(self.funcname_ifc.upper())
      target_file = (self.group_data.path.replace(self.search_dir,
                                                  '{}xbmc/addons/kodi-dev-kit/src/addon/api/'.format(kodi_dir)).replace('.h', '.cpp'))
      code_work = CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_{}'.format(self.funcname_ifc.upper()))
      if code_work:
        code += code_work
      else:
        code += '#warning USE_HAND_MAKE set for function "{}" and must be set by hand.\n'.format(self.function_complete)
      code += '      /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}_END>---*/\n'.format(self.funcname_ifc.upper())
      code += '      return true;\n'
      code += '    }\n'
      self.child_addon_c_lib_function_switch_case = code
      return True

    count = 0
    function_values = []
    msgpack_in_values = []
    msgpack_out_values = []
    additional_code_1 = ''
    additional_code_2 = ''
    additional_code_3 = ''
    additional_code_4 = ''
    no_in = False
    ignored_count = 0

    default_ret = GetDefaultReturn(self.retval, self.function_complete, file_text)
    if default_ret:
      return_value = ''
      if self.retval == 'char*':
        return_value = 'auto_gen_ret ? auto_gen_ret : ""{}'.format(' /* Return_WAY_1 (0004) */' if self.options.debug else '')
      elif self.retval in known_STANDARD_C_TYPES:
        return_value = 'auto_gen_ret{}'.format(' /* Return_WAY_2 (0004) */' if self.options.debug else '')
      elif CheckKnownEnum(self.retval):
        return_value = 'auto_gen_ret{}'.format(' /* Return_WAY_3 (0004) */' if self.options.debug else '')
      elif ContainsHdlVoidPointer(self.retval):
        return_value = 'PtrValue(auto_gen_ret){}\n'.format(' /* Return_WAY_4 (0004) */' if self.options.debug else '')
      elif self.retval != 'void':
        return_value = 'auto_gen_ret{}'.format(self.retval, ' /* Return_WAY_5 (undefined) (0004) */' if self.options.debug else '')
      msgpack_out_values.append(return_value)

    for value in self.values:
      apiUse = CheckAPIUse(self, count, value, self.values, ignored_count)
      ignored_count = apiUse.ignored_count
      count += 1

      if apiUse.done:
        if apiUse.no_in:
          no_in = True
        if apiUse.msgpack_in_value:
          msgpack_in_values.append(apiUse.msgpack_in_value)
        if apiUse.msgpack_out_value:
          msgpack_out_values.append(apiUse.msgpack_out_value)

        if apiUse.additional_code_1:
          additional_code_1 += apiUse.additional_code_1
        if apiUse.additional_code_2:
          additional_code_2 += apiUse.additional_code_2
        if apiUse.additional_code_3:
          additional_code_3 += apiUse.additional_code_3
        if apiUse.additional_code_4:
          additional_code_4 += apiUse.additional_code_4
        if apiUse.function_value:
          function_values.append(apiUse.function_value)

    if not no_in:
      code += '      msgChild__IN_{} t = in.get().as<decltype(t)>();\n'.format(self.funcname_ifc)
      code += '      KODI_ADDON_HDL auto_gen_hdl = reinterpret_cast<KODI_ADDON_HDL>(std::get<0>(t));\n'

    for value in additional_code_1:
      code += '{}'.format(value)
    for value in msgpack_in_values:
      code += '      {}'.format(value)
    for value in additional_code_2:
      code += '{}'.format(value)

    code += ('      {}{}(this{}{});\n'.format('{} auto_gen_ret = '.format(self.retval) if default_ret else '',
                                                         self.funcname_ifc,
                                                         ', ' if len(function_values) > 0 else '',
                                                         ', '.join(function_values)))
    code += '\n'

    for value in additional_code_3:
      code += '{}'.format(value)
    if len(self.child_addon_c_lib_function_shared_tuple_out_list) != 0 and \
       not self.child_addon_c_lib_function_shared_tuple_out_list[0] == 'DummyValue':
      code += ('      msgpack::pack(out, msgChild_OUT_{}({}));\n'.format(self.funcname_ifc,
                                                                         ', '.join(msgpack_out_values)))
    for value in additional_code_4:
      code += '{}'.format(value)

    code += '      return true;\n'
    code += '    }\n'

    self.child_addon_c_lib_function_switch_case = code

    return True

  def GenerateKodiSourceCPPFunction(self, file_text):
    """
    Generate source for ./xbmc/addons/interface/api/*.cpp.
    """
    class CheckAPIUse:
      def __init__(self, parent, cnt_in, cnt_out, value, value_list, ignored_count):
        self.parent = parent
        self.cnt_in = cnt_in
        self.cnt_out = cnt_out
        self.value = value
        self.ignored_count = ignored_count;
        self.additional_code_1 = ''
        self.additional_code_2 = ''
        self.additional_code_3 = ''
        self.additional_code_4 = ''
        self.ignore_next = False

        self.value_name = value.split()[-1].strip()
        self.value_type = value[:-len(self.value_name)].strip()

        self.msgpack_in_value = ''
        self.msgpack_out_value = ''

        # Fixed array way 1 e.g. "enum AudioEngineChannel info[][AUDIOENGINE_CH_MAX]"
        regex_code = '^((?:const{1,}))?(.*)\ ([a-z0-9A-Z_]*?)(?!\*)?\[([a-z0-9A-Z_]*?)\]\[([a-z0-9A-Z_]*?)\]$'
        m = re.search(regex_code, value)
        if m and m.group(2) and m.group(3) and not m.group(4) and m.group(5):
          self.msgpack_in_value = 'ifc_{}'.format(m.group(3))
          self.msgpack_out_value = 'std::memcpy(*{}, std::get<{}>(t).data(), sizeof({}) * {});'.format(m.group(3), cnt_out, self.value_type.replace('*', ''), m.group(5))
          self.additional_code_1  = '  std::array<{}, {}> ifc_{};\n'.format(self.value_type, m.group(5), m.group(3))
          self.additional_code_1 += '  std::memcpy(ifc_{}.data(), *{}, sizeof({}) * {});\n'.format(m.group(3), m.group(3), self.value_type.replace('*', ''), m.group(5))
          self.done = True
          return

        # Fixed array way 2 e.g. "enum AudioEngineChannel (*info)[AUDIOENGINE_CH_MAX]"
        regex_code = '^((?:const{1,}))?(.*)\ \(\*([a-z0-9A-Z_]*?)\)\[([a-z0-9A-Z_]*?)\]$'
        m = re.search(regex_code, value)
        if m and m.group(2) and m.group(3) and m.group(4):
          self.msgpack_in_value = 'ifc_{}'.format(m.group(3))
          self.msgpack_out_value = 'std::memcpy(*{}, std::get<{}>(t).data(), sizeof({}) * {});'.format(m.group(3), cnt_out, self.value_type.replace('*', ''), m.group(4))
          self.additional_code_1  = '  std::array<{}, {}> ifc_{};\n'.format(self.value_type, m.group(4), m.group(3))
          self.additional_code_1 += '  std::memcpy(ifc_{}.data(), *{}, sizeof({}) * {});\n'.format(m.group(3), m.group(3), self.value_type.replace('*', ''), m.group(4))
          self.done = True
          return

        # Fixed array way 3 e.g. "enum AudioEngineChannel info[AUDIOENGINE_CH_MAX]"
        regex_code = '^((?:const{1,}))?(.*)\ ([a-z0-9A-Z_]*?)\[([a-z0-9A-Z_]*?)\]$'
        m = re.search(regex_code, value)
        if m and m.group(2) and m.group(3) and m.group(4):
          self.msgpack_in_value = 'ifc_{}'.format(m.group(3))
          self.msgpack_out_value = 'std::memcpy({}, std::get<{}>(t).data(), sizeof({}) * {});'.format(m.group(3), cnt_out, self.value_type.replace('*', ''), m.group(4))
          self.additional_code_1  = '  std::array<{}, {}> ifc_{};\n'.format(self.value_type, m.group(4), m.group(3))
          self.additional_code_1 += '  std::memcpy(ifc_{}.data(), {}, sizeof({}) * {});\n'.format(m.group(3), m.group(3), self.value_type.replace('*', ''), m.group(4))
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_6 (shared call to addon, Kodi side) (child)
        if self.value_type == 'const char*':
          if '[]' in self.value_name and self.value_name.count('[]') == 1:
            if len(value_list) > 1 \
               and cnt_in < len(value_list)-1 \
               and 'size_t' in value_list[cnt_in+1]:
              parent.group_data.AddAdditionalAddonLibIncludes('#include <string>')
              parent.group_data.AddAdditionalAddonLibIncludes('#include <vector>')
              self.value_name = self.value_name.replace('[]', '')
              self.additional_code_1  = ('  std::vector<std::string> cpp_{};{}\n'
                                         .format(self.value_name,
                                                 ' /* CheckAPIUse_WAY_6c (0005) */' if parent.options.debug else ''))
              self.additional_code_1 += ('  cpp_{}.reserve({});{}\n'
                                         .format(self.value_name,
                                                 value_list[cnt_in+1].split()[-1].strip(),
                                                 ' /* CheckAPIUse_WAY_6c (0005) */' if parent.options.debug else ''))
              self.additional_code_1 += ('  for (size_t i = 0; i < {}; ++i){}\n'
                                         .format(value_list[cnt_in+1].split()[-1].strip(),
                                                 ' /* CheckAPIUse_WAY_6c (0005) */' if parent.options.debug else ''))
              self.additional_code_1 += ('  {\n')
              self.additional_code_1 += ('      cpp_{}.emplace_back({}[i] != nullptr ? {}[i] : "");{}\n'
                                         .format(self.value_name,
                                                 self.value_name,
                                                 self.value_name,
                                                 ' /* CheckAPIUse_WAY_6c (0005) */' if parent.options.debug else ''))
              self.additional_code_1 += ('  }\n')
              self.msgpack_in_value = ('cpp_{}{}'
                                       .format(self.value_name,
                                               ' /* CheckAPIUse_WAY_6c (0005) */' if parent.options.debug else ''))
              self.msgpack_out_value = ''
              self.done = True
            else:
              print('FATAL: Function:')
              print('       "{}"'.format(parent.function_complete))
              print('       Not supported on InterfaceDataChild::GenerateKodiSourceCPPFunction!')
              print('       Need to set second value of "{}" as "size_t".'.format(self.value))
              exit(1)
          elif len(value_list) > 1 \
               and cnt_in < len(value_list)-1 \
               and '...' in value_list[cnt_in+1]:
            self.msgpack_in_value = ('cpp_{}{}'
                                     .format(self.value_name,
                                             ' /* CheckAPIUse_WAY_6a (0005) */' if parent.options.debug else ''))
            self.msgpack_out_value = ''
          else:
            self.msgpack_in_value = ('{}{}'
                                     .format(self.value_name,
                                             ' /* CheckAPIUse_WAY_6b (0005) */' if parent.options.debug else ''))
            self.msgpack_out_value = ''
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_7 (shared call to addon, Kodi side) (child)
        if self.value_type == 'char**':
          self.msgpack_in_value = ''
          self.msgpack_out_value = ('  *{} = strdup(std::get<{}>(t).c_str());{}'
                                    .format(self.value_name,
                                            self.cnt_out,
                                            ' /* CheckAPIUse_WAY_7 (0005) */' if parent.options.debug else ''))
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_8_1 (shared call to addon, Kodi side) (child)
        if self.value_type == 'char***' \
           or (self.value_type == 'char**' \
               and '[]' in self.value_name \
               and self.value_name.count('[]') == 1):
          if len(value_list) > 1 \
              and cnt_in < len(value_list)-1 \
              and 'size_t*' in value_list[cnt_in+1]:
            self.value_name = self.value_name.replace('[]', '')
            self.msgpack_in_value = ''
            self.msgpack_out_value = ('const std::vector<std::string>& cpp_{} = std::get<{}>(t);{}\n'
                                       .format(self.value_name,
                                               self.cnt_out,
                                               ' /* CheckAPIUse_WAY_8_1 (0005) */' if parent.options.debug else ''))
            self.additional_code_4 += ('  assert(cpp_{}.size() == *{});{}'
                                       .format(self.value_name,
                                               value_list[cnt_in+1].split()[-1].strip(),
                                               ' /* CheckAPIUse_WAY_8_1 (0005) */' if parent.options.debug else ''))
            self.additional_code_4 += ('  if (!cpp_{}.empty())\n'
                                       .format(self.value_name))
            self.additional_code_4 += ('  {\n')
            self.additional_code_4 += ('    *{} = static_cast<char**>(malloc(*{} * sizeof(char*)));{}\n'
                                       .format(self.value_name,
                                               value_list[cnt_in+1].split()[-1].strip(),
                                               ' /* CheckAPIUse_WAY_8_1 (0005) */' if parent.options.debug else ''))
            self.additional_code_4 += ('    for (size_t i = 0; i < *{}; ++i){}\n'
                                       .format(value_list[cnt_in+1].split()[-1].strip(),
                                               ' /* CheckAPIUse_WAY_8_1 (0005) */' if parent.options.debug else ''))
            self.additional_code_4 += ('      (*{})[i] = strdup(cpp_{}[i].c_str());{}\n'
                                       .format(self.value_name,
                                               self.value_name,
                                               ' /* CheckAPIUse_WAY_8_1 (0005) */' if parent.options.debug else ''))
            self.additional_code_4 += ('  }\n')
            self.additional_code_4 += ('  else\n')
            self.additional_code_4 += ('  {\n')
            self.additional_code_4 += ('    *{} = nullptr;\n'
                                       .format(self.value_name,
                                               ' /* CheckAPIUse_WAY_8_1 (0005) */' if parent.options.debug else ''))
            self.additional_code_4 += ('  }\n')

            self.done = True
          else:
            print('FATAL: Function:')
            print('       "{}"'.format(parent.function_complete))
            print('       Not supported on InterfaceDataChild::GenerateKodiSourceCPPFunction!')
            print('       Need to set second value of "{}" as "size_t".'.format(self.value))
            exit(1)
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_8
        if self.value_type == 'char*' \
           and self.cnt_in-self.ignored_count+1 < len(parent.values) \
           and 'size_t' in value_list[self.cnt_in+self.ignored_count+1]:
          self.msgpack_in_value = ''
          self.msgpack_out_value = ('  strncpy({}, std::get<{}>(t).c_str(), {});{}'
                                    .format(self.value_name,
                                            self.cnt_out,
                                            value_list[cnt_in+1].split()[-1].strip(),
                                            ' /* CheckAPIUse_WAY_8 (0005) */' if parent.options.debug else ''))
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_9
        if self.value_type in known_STANDARD_C_TYPES:
          self.msgpack_in_value = ('{}{}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_9 (0005) */' if parent.options.debug else ''))
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_10
        if self.value_type in known_STANDARD_C_PTR_TYPES \
              and cnt_in+ignored_count < len(value_list)-1 \
              and 'size_t' in value_list[cnt_in+ignored_count+1] \
              and self.value_type.count('*') == 1:
          size_value = value_list[cnt_in+ignored_count+1].split()[-1].strip()
          self.msgpack_in_value = ''
          self.msgpack_out_value = ('std::memcpy({}, std::get<{}>(t).data(), sizeof({}) * {});{}'
                                    .format(self.value_name,
                                            cnt_out,
                                            self.value_type.replace('*', ''),
                                            size_value,
                                            ' /* CheckAPIUse_WAY_10 (0005) */' if parent.options.debug else ''))
          self.ignore_next = True
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_11
        if self.value_type.replace('const ', '') in known_STANDARD_C_PTR_TYPES \
              and cnt_in+ignored_count < len(value_list)-1 \
              and 'size_t' in value_list[cnt_in+ignored_count+1] \
              and self.value_type.count('*') == 1:
          size_value = value_list[cnt_in+ignored_count+1].split()[-1].strip()
          self.msgpack_in_value = ('std::vector<{}>({}, {} + {}){}'
                                   .format(self.value_type.replace('*', '').replace('const ', ''),
                                           self.value_name,
                                           self.value_name,
                                           size_value,
                                           ' /* CheckAPIUse_WAY_11 (0005) */' if parent.options.debug else ''))
          self.ignore_next = True
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_12
        if ContainsHdlVoidPointer(self.value_type):
          self.msgpack_in_value = ('PtrValue({}){}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_12 (0005) */' if parent.options.debug else ''))
          self.msgpack_out_value = ''
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_12b
        if (ContainsHdlVoidPointer(self.value_type.replace('*', '')) \
              and self.value_type.count('*') == 1):
          self.msgpack_in_value = ''
          self.msgpack_out_value = ('*{} = reinterpret_cast<{}>(std::get<{}>(t));{}'
                                    .format(self.value_name,
                                            self.value_type.replace('*', ''),
                                            self.cnt_out,
                                            ' /* CheckAPIUse_WAY_12b (0005) */' if parent.options.debug else ''))
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_13 - e.g. 'bool* ret'
        if self.value_type.replace('const ', '') in known_STANDARD_C_PTR_TYPES:
          if self.value_type.count('*') == 1:
            self.msgpack_in_value = ('*{}{}'
                                     .format(self.value_name,
                                             ' /* CheckAPIUse_WAY_13 (0005) */' if parent.options.debug else ''))
            self.msgpack_out_value = ('*{} = std::get<{}>(t);{}'
                                      .format(self.value_name,
                                              self.cnt_out,
                                              ' /* CheckAPIUse_WAY_13 (0005) */' if parent.options.debug else ''))
            self.done = True
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataParent::GenerateKodiSourceCPPFunction (on CheckAPIUse_WAY_13)'.format(parent.function_complete))
            exit(1)
          return

        # WARNING CONFIRMED_NO (14a 1)
        # CheckAPIUse_WAY_14
        # If yes, handle enum - e.g. 'enum NAME value' or 'enum NAME* ret'
        if CheckKnownEnum(self.value_type):
          self.value_type = self.value_type.replace('enum ', '')

          # Add enum to used list (if not present)
          check_value = self.value_type.replace('*', '').strip()
          if check_value not in parent.group_data.used_enums:
            parent.group_data.used_enums.append(check_value)

          # If normal value add to input
          if not '*' in self.value_type:
            self.msgpack_in_value = ('{}{}'
                                     .format(self.value_name,
                                             ' /* CheckAPIUse_WAY_14a (0005) */' if parent.options.debug else ''))
          elif '*' in self.value_type and self.value_type.count('*') == 1 and not 'const' in self.value_type:
            self.msgpack_in_value = ('*{}{}'
                                     .format(self.value_name,
                                             ' /* CheckAPIUse_WAY_14b (0005) */' if parent.options.debug else ''))
            self.msgpack_out_value = ('*{} = std::get<{}>(t);{}'
                                      .format(self.value_name,
                                              self.cnt_out,
                                              ' /* CheckAPIUse_WAY_14b (0005) */' if parent.options.debug else ''))
          else:
            print('FATAL: Function "{}" Not supported on InterfaceDataParent::GenerateKodiSourceCPPFunction (on CheckAPIUse_WAY_14)'.format(parent.function_complete))
            raise
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_15
        if self.value_type.startswith('struct ') and self.value_type.count('*') == 1 and parent.group_data.GenerateSharedStructure(self.value_type):
          self.msgpack_in_value = ''
          self.msgpack_out_value = ('std::get<{}>(t).SetCStructure({});{}'
                                    .format(self.cnt_out,
                                            self.value_name,
                                            ' /* CheckAPIUse_WAY_15 (0005) */' if parent.options.debug else ''))
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_16
        if self.value_type.startswith('const struct ') and self.value_type.count('*') == 1 and parent.group_data.GenerateSharedStructure(self.value_type):
          self.msgpack_in_value = ('{}{}'
                                   .format(self.value_name,
                                           ' /* CheckAPIUse_WAY_16 (0005) */' if parent.options.debug else ''))
          self.msgpack_out_value = ''
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_17
        if self.value_type.startswith('struct ') \
              and self.value_type.count('*') == 2 \
              and cnt_in+ignored_count < len(value_list)-1 \
              and 'size_t*' in value_list[cnt_in+ignored_count+1] \
              and parent.group_data.GenerateSharedStructure(self.value_type):
          ifc_struct_name = self.value_type.replace('*', '').replace('struct ', '')
          self.msgpack_in_value = ''
          self.msgpack_out_value = ('std::vector<IFC_{}>& ifc_{} = std::get<{}>(t);'
                                    .format(ifc_struct_name,
                                            self.value_name,
                                            self.cnt_out))
          self.additional_code_4 = ('  *{} = static_cast<{}>(malloc(sizeof({}) * ifc_{}.size()));{}\n'
                                    .format(self.value_name,
                                            self.value_type.replace('**', '*').replace('struct ', ''),
                                            ifc_struct_name,
                                            self.value_name,
                                            ' /* CheckAPIUse_WAY_17 (0005) */' if parent.options.debug else ''))
          self.additional_code_4 += ('  for (size_t i = 0; i < ifc_{}.size(); ++i)\n'
                                     .format(self.value_name))
          self.additional_code_4 += ('     ifc_{}[i].SetCStructure(&(*{})[i]);\n'
                                     .format(self.value_name,
                                             self.value_name))
          self.done = True
          return

        # WARNING CONFIRMED_NO
        # CheckAPIUse_WAY_18 - For msgParent__IN/OUT_ on kodi-dev-kit/src/shared/api
        if self.value_type.startswith('struct ') \
              and self.value_name.count('[]') == 1 \
              and 'size_t*' in value_list[cnt_in+1] \
              and parent.group_data.GenerateSharedStructure(self.value_type):
          value_name = self.value_name.replace('[]', '')
          ifc_value_type = 'IFC_{}'.format(self.value_type.replace('struct ', ''))

          self.additional_code_1 = ('      std::vector<{}> ifc_{}(*{});{}\n'
                                     .format(ifc_value_type,
                                             value_name,
                                             value_list[cnt_in+ignored_count+1].split()[-1].strip(),
                                             ' /* CheckAPIUse_WAY_18 (0005) */' if parent.options.debug else ''))
          self.additional_code_1 += ('      for (size_t i = 0; i < *{}; ++i)\n'
                                     .format(value_list[cnt_in+ignored_count+1].split()[-1].strip()))
          self.additional_code_1 += ('      {\n')
          self.additional_code_1 += ('        ifc_{}[i] = {}(&{}[i]);{}\n'
                                     .format(value_name,
                                             ifc_value_type,
                                             value_name,
                                             ' /* CheckAPIUse_WAY_18 (0005) */' if parent.options.debug else ''))
          self.additional_code_1 += ('      }\n')
          self.msgpack_in_value = ('ifc_{}{}'
                                   .format(value_name,
                                           ' /* CheckAPIUse_WAY_18 (0005) */' if parent.options.debug else ''))
          self.msgpack_out_value = ('std::vector<{}>& ifc_out_{} = std::get<{}>(t);{}'
                                    .format(ifc_value_type,
                                            value_name,
                                            self.cnt_out,
                                            ' /* CheckAPIUse_WAY_18 (0005) */' if parent.options.debug else ''))
          self.additional_code_4 = ('      for (size_t i = 0; i < *{}; ++i)\n'
                                     .format(value_list[cnt_in+ignored_count+1].split()[-1].strip()))
          self.additional_code_4 += ('      {\n')
          self.additional_code_4 += ('        ifc_out_{}[i].SetCStructure(&{}[i]);\n'
                                     .format(value_name,
                                             value_name))
          self.additional_code_4 += ('      }\n')
          self.done = True
          return

        self.done = False

    # Generate value string line to add in function
    func_values = ''
    current_value = 1
    for value in self.values:
      func_values += value + (', ' if current_value < len(self.values) else '')
      current_value += 1

    if '---AUTO_GEN_PARSE<OVERRIDE;USE_HAND_MAKE={}>---'.format(self.funcname_ifc) in file_text:
      target_file = self.group_data.path.replace(self.search_dir, '{}xbmc/addons/interface/api/'.format(kodi_dir)).replace('.h', '.cpp')
      code_work = CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD={}'.format(self.funcname_ifc.upper()))

      code = '  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD={}>---*/\n'.format(self.funcname_ifc.upper())
      if code_work:
        code += code_work
      else:
        code += 'void CHdl_kodi_{}::{}()\n'.format(self.header_group_id, self.funcname_ifc)
        code += '{\n'
        code += '  // This function is set by "OVERRIDE;USE_HAND_MAKE" and must be complete set here and other places by hand!!!\n'
        code += '#warning Function "{}" must be complete set by hand.\n'.format(self.function_complete)
        code += '}\n'
      code += '  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD={}_END>---*/\n'.format(self.funcname_ifc.upper())
      self.child_kodi_cpp_function_source = code


      target_file = target_file.replace('.cpp', '.h')
      code_work = CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD={}'.format(self.funcname_ifc.upper()))

      code = '  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD={}>---*/\n'.format(self.funcname_ifc.upper())
      if code_work:
        code += code_work
      else:
        code += '  void {}(); // This function is set by "OVERRIDE;USE_HAND_MAKE"!!!\n'.format(self.funcname_ifc)
      code += '  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD={}_END>---*/\n'.format(self.funcname_ifc.upper())
      self.child_kodi_cpp_function_header = code

      return True


    # Check function contains in and/or out
    haveIn = len(self.values) != 0
    haveOut = self.ContainsOutOnIn() or self.retval != 'void'

    # Generate the initial first part of function
    code = ''
    code += '{} CHdl_kodi_{}::{}({})\n'.format(self.retval, self.header_group_id, self.funcname_ifc, func_values)
    code += '{\n'
    code += '  // Original API call: {}\n'.format(self.function_complete)
    if not self.group_data.override_use_direct_api_only:
      code += '  // Tuple in:          {}\n'.format(self.child_addon_c_lib_function_shared_tuple_in)
      code += '  // Tuple out:         {}\n'.format(self.child_addon_c_lib_function_shared_tuple_out)
    code += '\n'

    if not self.group_data.override_use_direct_api_only:
      code += '#ifndef KODI_INHIBIT_SHARED\n'
      code += '  if (!m_interface.m_directDll)\n'
      code += '  {\n'
      # Check it have "in" and/or "return" values, if no go easy way and add the single line to code
      if not haveIn and not haveOut:
        code += '  m_process->SendMessage(funcGroup_{}, funcChild_{});\n'.format(self.header_group_id, self.funcname_ifc)
        code += '  return;\n'
      else:
        code += '  msgpack::sbuffer in;\n' if haveIn else ''
        code += '  msgpack::sbuffer out;\n' if haveOut else ''

        # If have input start to create his msgpack stream value
        if haveIn:
          cnt_in = 0
          cnt_out = 1 if self.retval != 'void' else 0
          ignored_cnt = 0

          in_values = ''
          out_values = ''
          additional_code_1 = ''
          additional_code_2 = ''
          additional_code_3 = ''
          additional_code_4 = ''
          for value in self.values:
            apiUse = CheckAPIUse(self, cnt_in, cnt_out, value, self.values, ignored_cnt)
            cnt_in += 1

            if apiUse.msgpack_in_value:
              in_values += apiUse.msgpack_in_value + ', '
            if apiUse.msgpack_out_value:
              cnt_out += 1
              out_values += '  {}\n'.format(apiUse.msgpack_out_value)

            if apiUse.additional_code_1:
              code += apiUse.additional_code_1
            if apiUse.additional_code_2:
              additional_code_2 += apiUse.additional_code_2
            if apiUse.additional_code_3:
              additional_code_3 += apiUse.additional_code_3
            if apiUse.additional_code_4:
              additional_code_4 += apiUse.additional_code_4

          # Remove possible wrong added ', '
          while in_values.endswith(', '):
            in_values = in_values[:-2]
          if in_values != '':
            code += '  msgpack::pack(in, msgChild__IN_{}({}));\n'.format(self.funcname_ifc, in_values)
          else:
            haveIn = False

        if haveIn and haveOut:
          code += '  if (!m_process->SendMessage(funcGroup_{}, funcChild_{}, in, out))\n'.format(self.header_group_id, self.funcname_ifc)
          code += '    return{};\n'.format(GetDefaultReturn(self.retval, self.function_complete, file_text))
        elif haveIn and not haveOut:
          code += '  m_process->SendMessage(funcGroup_{}, funcChild_{}, in);\n'.format(self.header_group_id, self.funcname_ifc)
          code += '  return;\n'
        else:
          code += '  if (!m_process->SendMessageOnlyGetReturn(funcGroup_{}, funcChild_{}, out))\n'.format(self.header_group_id, self.funcname_ifc)
          code += '    return{};\n'.format(GetDefaultReturn(self.retval, self.function_complete, file_text))

        if additional_code_2:
          code += additional_code_2

        if haveOut:
          code += '  msgpack::unpacked ident = msgpack::unpack(out.data(), out.size());\n'
          code += '  msgChild_OUT_' + self.funcname_ifc + ' t = ident.get().as<decltype(t)>();\n'

          if additional_code_3:
            code += additional_code_3
          code += out_values
          if additional_code_4:
            code += additional_code_4

          if self.retval == 'char*':
            code += '  return strdup(std::get<0>(t).c_str());\n'
          elif self.retval in known_STANDARD_C_TYPES:
            code += '  return std::get<0>(t);\n'
          elif CheckKnownEnum(self.retval) and not '*' in self.retval:
            code += '  return std::get<0>(t);\n'
            retval = self.retval.replace('enum ', '')
            if retval not in self.group_data.used_enums:
              self.group_data.used_enums.append(retval)
          elif self.retval.replace('const ', '') == self.groupname.upper() + '_HDL' and self.retval.replace('const ', '') in known_VOID_PTR_DEFINES:
            code += '  return reinterpret_cast<{}>(std::get<0>(t));\n'.format(self.retval.replace('const ', ''))
          elif self.retval.replace('const ', '') in known_VOID_PTR_DEFINES:
            code += '  return reinterpret_cast<{}>(std::get<0>(t));\n'.format(self.retval.replace('const ', ''))
          elif self.retval != 'void':
            code += '  return TODO\n'
            print('FATAL: Not supported return value by "{}" on GenerateKodiSourceCPPFunction call!'.format(self.function_complete))
            #exit(1)
          else:
            code += '  return;\n'
      code += '  }\n'
      code += '#endif /* !KODI_INHIBIT_SHARED */\n'
      code += '\n'

    self.child_kodi_cpp_function_header = '  {} {}({}); // Added with API {}\n'.format(self.retval, self.funcname_ifc, func_values, self.api_added)

    func_values = ''
    current_value = 1
    for value in self.values:
      if value != '...':
        value_name = value.split()[-1].strip()
        value_type = value[:-len(value_name)].strip()
        if '[' in value_name:
          value_type += '[' + value_name.split('[', 1)[-1]
          value_name = value_name.split('[', 1)[0].strip()
      else:
        value_name = ''
        value_type = '...'
        continue
      func_values += ', {}'.format(value_name)
      current_value += 1

    code += ('  {}m_ifcToAddon->{}(m_ifcToAddon->thisClassHdl{});\n'
             .format('return ' if self.retval != 'void' else '',
                     self.funcname_ifc,
                     func_values))
    code += '}\n'

    self.child_kodi_cpp_function_source = code

    return True

  def GenerateDevKitSourceCPPFunction(self, file_text):
    class CheckAPIUse:
      def __init__(self, parent, cnt, value, value_list):
        self.parent = parent
        self.cnt = cnt
        self.value = value
        self.set_call = ''
        self.set_static = False
        self.set_override = ''
        self.additional_code_1 = ''
        self.additional_code_2 = ''
        self.additional_code_3 = ''
        self.additional_code_4 = ''
        self.ignore_next = False
        self.return_value = ''

        self.value_name = value.split()[-1].strip()
        self.value_type = value[:-len(self.value_name)].strip()
        if '[' in self.value_name:
          self.value_type += '[' + self.value_name.split('[', 1)[-1]
          self.value_name = self.value_name.split('[', 1)[0].strip()

        self.done = False

        self.msgpack_in_value = ''
        self.function_value = ''
        self.msgpack_out_value = ''

        if value == '...':
          self.value_name = ''
          self.value_type = '...'
          self.done = True
          return

        if cnt == 0 \
           and (self.value_type.replace('const ', '') == self.parent.groupname.upper() + '_HDL') \
           and self.value_type.replace('const ', '') in known_VOID_PTR_DEFINES:
          self.value_name = 'union_data->hdl'
          self.done = True
          return

    if not IsHighestUsedFunctionVersion(self.group_data.path, self.funcname, self.ifc_name_func, self.api_added):
      return False

    target_file = (self.group_data.path.replace(self.search_dir,
                                                '{}xbmc/addons/kodi-dev-kit/src/addon/api/'
                                                .format(kodi_dir)).replace('.h', '.cpp'))

    values = []
    retval = ''
    code_override = ''
    if self.funcname == 'kodi_addon_create_instance':
      code = Generate_kodi_addon_instance_construct(self.options)

      code_override += '/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}_2>---*/\n'.format(self.funcname_ifc.upper())
      if code.create_code:
        code_override += code.create_code + '\n'
      else:
        code_override += '  {} auto_gen_ret ={};\n'.format(retval, default_ret) if default_ret else ''
        code_override += '#warning USE_HAND_MAKE set for function "{}" and must be set by hand.\n'.format(self.function_complete)
        code_override += '  return auto_gen_ret;\n' if default_ret else ''
      code_override += '/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}_2_END>---*/\n'.format(self.funcname_ifc.upper())
    elif self.funcname == 'kodi_addon_destroy_instance':
      code = Generate_kodi_addon_instance_construct(self.options)

      code_override += '/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}_2>---*/\n'.format(self.funcname_ifc.upper())
      if code.destroy_code:
        code_override += code.destroy_code + '\n'
      else:
        code_override += '  {} auto_gen_ret ={};\n'.format(retval, default_ret) if default_ret else ''
        code_override += '#warning USE_HAND_MAKE set for function "{}" and must be set by hand.\n'.format(self.function_complete)
        code_override += '  return auto_gen_ret;\n' if default_ret else ''
      code_override += '/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}_2_END>---*/\n'.format(self.funcname_ifc.upper())

    if '---AUTO_GEN_PARSE<OVERRIDE;USE_HAND_MAKE={}>---'.format(self.funcname_ifc) in file_text:
      scan_file = self.group_data.path.replace(self.search_dir, '{}xbmc/addons/interface/api/'.format(kodi_dir))

      file_text = CodeGetField_AUTO_GEN_PARSE(scan_file, 'HAND_EDITED_FIELD={}'.format(self.funcname_ifc.upper()))
      file_text = ' '.join(file_text.replace('\n', ' ').split(';')[0].split()).replace('( ', '(')
      m = re.search('(.*)[ \t](kodi.+?)(?=\()\((.*?)\)', file_text)
      if m and m.group(1) and m.group(2) and m.group(3):
        values = m.group(3).split(', ')
        retval = m.group(1)
      else:
        print('FATAL: Failed to scan "{}" on GenerateToAddonDirectFuncTable').format(file_text)
        raise

      print(scan_file)
      print(file_text)
      default_ret = GetDefaultReturn(retval, self.function_complete, file_text, scan_file)

      if not code_override:
        code_override += '/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}_2>---*/\n'.format(self.funcname_ifc.upper())
        code_work = CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_{}_2'.format(self.funcname_ifc.upper()))
        if code_work:
          code_override += code_work
        else:
          code_override += '  {} auto_gen_ret ={};\n'.format(retval, default_ret) if default_ret else ''
          code_override += '#warning USE_HAND_MAKE set for function "{}" and must be set by hand.\n'.format(self.function_complete)
          code_override += '  return auto_gen_ret;\n' if default_ret else ''
        code_override += '/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}_2_END>---*/\n'.format(self.funcname_ifc.upper())
    else:
      values = self.values
      retval = self.retval

    func_values = ''
    current_value = 1
    for value in values:
      if value != '...':
        value_name = value.split()[-1].strip()
        value_type = value[:-len(value_name)].strip()
        if '[' in value_name:
          value_type += '[' + value_name.split('[', 1)[-1]
      else:
        value_name = ''
        value_type = '...'

      func_values += value_type + (', ' if current_value < len(values) else '')
      current_value += 1

    void_ptr_value_name = values[0].split()[-1]

    lowest_api = GetLowestUsedAPI()
    highest_api = GetHighestUsedAPI()

    cnt_in = 0
    value_names = []
    for value in values:
      apiUse = CheckAPIUse(self, cnt_in, value, values)
      cnt_in += 1

      if apiUse.value_name:
        value_names.append(apiUse.value_name)

    code = ('{} CHdl_kodi_{}::{}(void* thisClassHdl{}{}) // Added with API {}\n'
            .format(retval,
                    self.header_group_id,
                    self.funcname_ifc,
                    ', ' if len(values) > 0 else '',
                    ', '.join(values),
                    self.api_added))
    code += '{\n'
    code += '  auto thisClass = reinterpret_cast<' + 'CHdl_kodi_{}*>(thisClassHdl);\n'.format(self.header_group_id)
    code += '  if (thisClass == nullptr)\n'
    code += '    return{};\n'.format(GetDefaultReturn(self.retval, self.function_complete, file_text))
    code += '\n'
    if code_override:
      code += code_override
    else:
      default_ret = GetDefaultReturn(retval, self.function_complete, file_text)


      code += '  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>({});\n'.format(void_ptr_value_name)
      code += '  {} auto_gen_ret ={};\n'.format(self.retval, default_ret) if default_ret else ''

      #checker = self.group_data.CheckToAddonFunctionAPI(self.group_data, self.groupname, self.ifc_name_func)
      if self.ifc_name_func in self.group_data.functions_equal_everywhere:
        code += '      if (union_data->types.{}.v{}.{})\n'.format(self.groupname, 1, self.ifc_name_func)
        code += '      {\n'
        code += ('      {}union_data->types.{}.v{}.{}({});\n'
                .format('auto_gen_ret = ' if default_ret else '',
                        self.groupname,
                        1,
                        self.ifc_name_func,
                        ', '.join(value_names)))
        code += '      }\n'
      else:
        code += '  switch (AddonIfc::g_ifc->api)\n'
        code += '  {\n'
        auto_gen_parse_added = False
        for i in range(highest_api, lowest_api, -1):
          api = i

          if api > self.api_added:
            code += '    case __KODI_API_{}__:\n'.format(api)
          elif api == self.api_added:
            code += '    case __KODI_API_{}__:\n'.format(api)
            code += '    {\n'
            code += '      if (union_data->types.{}.v{}.{})\n'.format(self.groupname, api, self.ifc_name_func)
            code += '      {\n'
            code += ('      {}union_data->types.{}.v{}.{}({});\n'
                    .format('auto_gen_ret = ' if default_ret else '',
                            self.groupname,
                            api,
                            self.ifc_name_func,
                            ', '.join(value_names)))
            code += '      }\n'
            code += '      break;\n'
            code += '    }\n'
          elif not auto_gen_parse_added:
            auto_gen_parse_added = True
            for i in range(self.api_added-1, lowest_api-1, -1):
              code += '    case __KODI_API_{}__:\n'.format(i)
              if not IsLowerToUsedFunctionVersion(self.group_data.path, self.funcname, self.ifc_name_func, i):
                code += '    {\n'
                code += '/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}_API_{}_BACKWARD>---*/\n'.format(self.funcname_ifc.upper(), i)
                code_work = CodeGetField_AUTO_GEN_PARSE(target_file, 'HAND_EDITED_FIELD_{}_API_{}_BACKWARD'.format(self.funcname_ifc.upper(), i))
                if code_work:
                  code += code_work
                else:
                  code += '\n#warning USE_HAND_MAKE set for function and must be set by hand for backward compatibility.\n\n'
                code += '/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_{}_API_{}_BACKWARD_END>---*/\n'.format(self.funcname_ifc.upper(), i)
                code += '      break;\n'
                code += '    }\n'
        code += '    default:\n'
        code += '      break;\n'
        code += '  }\n'
      code += '  return auto_gen_ret;\n' if default_ret else ''
    code += '}\n'

    self.dev_kit_kodi_to_addon_source = code
    self.dev_kit_kodi_to_addon_header = ('  static {} {}(void* thisClassHdl{}{}); // Added with API {}\n'
                                         .format(retval,
                                                 self.funcname_ifc,
                                                 ', ' if len(values) > 0 else '',
                                                 ', '.join(values),
                                                 self.api_added))

    for entry in self.callbacks:
      if entry.api_call == self.funcname_ifc and not entry.header in self.group_data.kodi_ifc_includes:
        self.group_data.kodi_ifc_includes.append(entry.header)

    return True

  def IsToAddonFunctionEqualToAllAPI(self):
    return True


#===============================================================================

def interface_code_generator(options, callbacks):
  """
  This function generate automatic code and store in list for further use
  """
  print('  - Scanning interface to autogenerate code')

  search_dir = '{}xbmc/addons/kodi-dev-kit/include/kodi/c-api/'.format(kodi_dir)
  scan_dir = search_dir + '**/'

  with open('./ignored_api_structs.txt') as f:
    file_text = f.read()
    f.close()
    for line in file_text.splitlines():
      if line:
        ignored_structs.append(line)

  print(scan_dir)

  ret = []
  dirs = sorted(glob.glob(scan_dir, recursive=True))
  for dir in dirs:
    source_dir = dir.replace(search_dir, '')

    src_parts = sorted(glob.glob(dir + '*.h', recursive=True))
    for src_part in src_parts:
      if not FileContainsInterfaceAPICalls(src_part):
        continue

      header_group_id = TranslatePathToCUsableString(src_part, search_dir)

      with open(src_part) as f:
        file_text = f.read()
        f.close()

      group_data = GroupData(callbacks, options)
      group_data.header_group_id = header_group_id
      group_data.path = src_part
      group_data.GenerateIndependentAPIStructs()

      if '---AUTO_GEN_PARSE<OVERRIDE;USE_DIRECT_API_ONLY>---' in file_text:
        group_data.override_use_direct_api_only = True

      function_addon = ''
      function_kodi = ''
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
          data = InterfaceDataParent(callbacks, options)

          function_addon = " ".join(function_addon.split())

          data.header_group_id = header_group_id
          data.function_complete = function_addon
          data.group_data = group_data

          if not data.RegexScanFunction(function_addon) or \
                 IsIgnoredFunction(data.funcname) or \
             not data.GenerateSharedTuples(file_text) or \
             not data.GenerateToKodiDirectFuncTable(file_text) or \
             not data.GenerateAddonSourceCFunction(file_text) or \
             not data.GenerateKodiSourceCPPFunction(file_text) or \
             not data.GenerateKodiSourceCPPSwitchCase(file_text):
            function_addon = '';
            continue

          group_data.interface_data_to_kodi.append(data)
          function_addon = '';

        if 'ATTR_APIENTRYP' in line \
            and not line.strip().startswith('#'):
          function_kodi = line;
        elif function_kodi != '':
          function_kodi += line;
        if function_kodi != '' and ';' in line:
          data = InterfaceDataChild(callbacks, options)

          function_kodi = " ".join(function_kodi.split())

          data.header_group_id = header_group_id
          data.function_complete = function_kodi
          data.group_data = group_data

          if not data.RegexScanFunction(function_kodi, file_text) or \
                 IsIgnoredFunction(data.funcname) or \
             not data.GenerateSharedTuples(file_text) or \
             not data.GenerateToAddonDirectFuncTable(file_text) or \
             not data.GenerateDevKitSourceCPPFunction(file_text) or \
             not data.GenerateKodiSourceCPPFunction(file_text) or \
             not data.GenerateAddonSourceSwitchCase(file_text):
             #not data.GenerateAddonSourceCFunction() or \
             #not data.GenerateKodiSourceCPPFunction() or \
            function_kodi = '';
            continue

          group_data.interface_data_to_addon.append(data)
          function_kodi = '';

      ret.append(group_data)


  #confirmed = [ 'kodi_network_get_user_agent' ]
  for group in ret:
    #if group.header_group_id != 'addoninstance_imagedecoder_h':
      #continue
    #for entry in group.interface_data_to_kodi:
      #if entry.funcname in confirmed:
        #continue
      #print('\n\n=======================================================================================')
      #print(entry.funcname)
      #print('---------------------------------------------------------------------------------------')
      #print('| parent_addon_c_lib_function_shared\n\n')
      #print(entry.parent_addon_c_lib_function_shared)
      #print('---------------------------------------------------------------------------------------')
      #print('| parent_addon_c_lib_function_shared_tuple_...\n\n')
      #print(entry.parent_addon_c_lib_function_shared_tuple_in)
      #print(entry.parent_addon_c_lib_function_shared_tuple_out)
      #print('---------------------------------------------------------------------------------------')
      #print('| parent_addon_c_lib_function_direct\n\n')
      #print(entry.parent_addon_c_lib_function_direct)
      #print('---------------------------------------------------------------------------------------')
      #print('| parent_addon_c_lib_function_direct_ptr\n\n')
      #print(entry.parent_addon_c_lib_function_direct_ptr)
      #print('---------------------------------------------------------------------------------------')
      #print('| parent_kodi_cpp_function_switch_case\n\n')
      #print(entry.parent_kodi_cpp_function_switch_case)
      #print('---------------------------------------------------------------------------------------')
      #print('| parent_kodi_cpp_function_source\n\n')
      #print(entry.parent_kodi_cpp_function_source)
      #print('---------------------------------------------------------------------------------------')
      #print('| parent_kodi_cpp_function_header\n\n')
      #print(entry.parent_kodi_cpp_function_header)
      #print('##')

    #print('---------------------------------------------------------------------------------------')
    #print('| shared_structures...\n\n')
    #for struct in group.shared_structures:
      #print(struct[1])

    #print('=======================================================================================')
    group.Generate__xbmc_addons_kodidevkit_src_shared_kodi_ALL_FILES(True)
    #print('=======================================================================================')
    group.Generate__xbmc_addons_kodidevkit_src_addon_api_ALL_FILES_CPP(True)
    #print('=======================================================================================')
    group.Generate__xbmc_addons_kodidevkit_src_addon_api_ALL_FILES_H(True)
    #print('=======================================================================================')
    group.Generate__xbmc_addons_interface_api_ALL_FILES_CPP(True)
    #print('=======================================================================================')
    group.Generate__xbmc_addons_interface_api_ALL_FILES_H(True)
    #print('=======================================================================================')
    group.Generate__xbmc_addons_kodidevkit_src_shared_kodi_ALL_FILES_additional(True)

  #def GetSharedTuples(self):   HAND_EDIT_ALLOW
  #def GetAddonCLibFunctionsShared(self):   HAND_EDIT_ALLOW
  #def GetAddonCLibFunctionsDirect(self):
  #def GetAddonCLibFunctionsDirectPtr(self):
  #def GetKodiSwitchCase(self):   HAND_EDIT_ALLOW
  #def GetKodiSourcePart(self):
  #def GetKodiParentHeaderPart(self):
  #group.GetKodiParentEnumList()

  return ret
