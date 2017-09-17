#!/usr/bin/python

#
#      Copyright (C) 2016 Team KODI
#      http://kodi.tv
#
#  This Program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2, or (at your option)
#  any later version.
#
#  This Program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with KODI; see the file COPYING.  If not, see
#  <http://www.gnu.org/licenses/>.
#
#

from optparse import OptionParser
import os, sys, re, shutil

# cannot be loaded as a module
if __name__ != "__main__":
    sys.stderr.write('This file cannot be loaded as a module!')
    sys.exit()

# parse command-line options
disc = """
This utility rename the string 'api*' with new defined level number on all
files with path defined header source.

Is to have on a API level change all doxygen related documentation comments
with right number.

Example:
./rename-apilevel-number.py --source=../include/kodi/api3 --old_level=2 --new_level=3
"""

parser = OptionParser(description=disc)
parser.add_option('--source', dest='source', metavar='DIR',
                  help='the source folder where becomes scanned [required]')
#parser.add_option('--old_level', dest='old_level', metavar='NUMBER',
                  #help='old level number which becomes changes [required]')
#parser.add_option('--new_level', dest='new_level', metavar='NUMBER',
                  #help='new level number which becomes used [required]')
(options, args) = parser.parse_args()

## the header option is required
#if options.source is None or options.old_level is None or options.new_level is None:
    #parser.print_help(sys.stdout)
    #sys.exit()

#def replace_word(infile,old_word,new_word):
    #if not os.path.isfile(infile):
        #print ("Error on replace_word, not a regular file: " + infile)
        #sys.exit(1)

    #f1=open(infile,'r').read()
    #f2=open(infile,'w')
    #m=f1.replace(old_word,new_word)
    #f2.write(m)

#print 'Renaming on all files in "' + options.source + '" the text from "api' + options.old_level + '" to "api' + options.new_level + '"'

AddonToKodi_h_file_code = '';
AddonToKodi_h_file_code_include = '';

_simpletypes = {
    'void': ['void', ''],
    'void*': ['void*', 'nullptr'],
    'char*': ['char*', 'nullptr'],
    'int': ['int', '0'],
    'int32': ['int32', '0'],
    'uint32': ['uint32', '0'],
    'int64': ['int64', '0'],
    'uint64': ['uint64', '0'],
    'double': ['double', '0'],
    'float': ['float', '0'],
    'long': ['long', '0'],
    'unsigned long': ['unsigned long', '0'],
    'long long': ['long long', '0'],
    'size_t': ['size_t', '0'],
    'bool': ['bool', 'false'],
    'char': ['char', '0'],
    'char* const': ['char* const', 'nullptr'],
}

def find_interface(datafile, funcId):
  global AddonToKodi_h_file_code_include
  global AddonToKodi_h_file_code
  containsParts = False
  code = ''
  retcode = ''
  enum = ''
  found = ""
  funcName = ""
  retType = ""
  values = ""
  value = ""
  prevLine = ""
  ret = ""
  if not os.path.isfile(datafile):
    print ("Error on replace_word, not a regular file: " + datafile)
    sys.exit(1)
  ##print datafile
  f = open(datafile, "r")
  for line in f.readlines():
    line = line.rstrip('\n')
    if line.find("#define ADDON_EXE_IGNORE_THIS") != -1:
      return ''
    if found == "" and line.find("typedef struct AddonToKodiFuncTable") != -1:
      line = re.search(r"AddonToKodiFuncTable.*.", line).group(0)
      line = re.search(r"[//a-zA-Z0-9_-]+", line).group(0)
      code += '/* Interface: ' + line + ' */\n\n'
      AddonToKodi_h_file_code += '\n/* Interface: ' + line + ' */\n'
      found = line
      if containsParts == False:
        containsParts = True
        AddonToKodi_h_file_code_include += '#include "' + datafile.rsplit('include/kodi/',1)[1] + '"\n'
    elif len(found) > 0:
      if line.find("(*)") != -1:
        continue
      if line.find("(*") != -1 or prevLine != "":
        if prevLine == "":
          funcName = found + "__" + re.search(r"\(\*([^']+)\).*\(", line).group(1)
          retType = re.search(r"([^']+)\(\*.*\(", line).group(1)
          retType = retType.rstrip(' ')
          retType = retType.strip(' ')
        if line.endswith(','):
          prevLine += line
          continue

        values = re.search(r".+(;)", prevLine + line).group(0)
        values = re.search(r"\).\(*([^']+)*\)", values).group(1)
        enum += '  ' + funcName.upper() + ' = ' + str(funcId) + ',\n'
        prevLine = ""
        if not values:
          values = ""
        else:
          values = re.sub(r' {2,}' , ' ', values)

        AddonToKodi_h_file_code += 'extern ' + retType + ' ' + funcName + '(' + values + ');\n'

        code += '/* Warning: Auto generated code, do not change by hand! */\n'
        code += retType + ' ' + funcName + '(' + values + ')\n{\n'
        code += '  /* ID: ' + funcName.upper() + ' - ' + str(funcId) + ' */\n'
        if retType != 'void':
          if retType in _simpletypes.keys():
            code += '  ' + _simpletypes[retType][0] + ' retValue = ' + _simpletypes[retType][1] + ';\n'
          else:
            code += '  ' + retType + ' retValue;\n'
          code += '\n'
        code += '  try\n'
        code += '  {\n'
        code += '    CKODIAddon_InterProcess *session = CMain::m_threadMap.at(std::this_thread::get_id());\n'
        code += '    CRequestPacket vrp(' + funcName.upper() + ', session);\n'

        funcId += 1
        for value in values.split(', '):
          if value == "":
            continue

          paramValue = re.search(r"(.*) +(.*)", value).group(1)
          paramValue = paramValue.strip(' ')
          paramName = re.search(r"(.*) +(.*)", value).group(2)
          paramName = paramName.strip(' ')
          if (paramName.startswith('*')):
            paramName = paramName.replace('*', '')
            paramValue += '*'
          if paramValue == 'AEStreamHandle*':
            code += '    void* ' + paramName + '2 = reinterpret_cast<void*>(' + paramName + ');\n'
            code += '    vrp.push(API_VOID_PTR, &' + paramName + '2);\n'
          else:
            ret = paramValue.replace(" ", "_").upper()
            ret = ret.replace("*", "_PTR")
            code += '    vrp.push(API_' + ret + ', &' + paramName + ');\n'
            if ret.find("CONST_") == -1 and ret.find("VOID_") == -1:
              if ret.find("API_CHAR_PTR_PTR"):
                retcode = '    vresp->pop(API_' + ret + ', &' + paramName + ');\n' + retcode
              elif ret.find("BOOL_PTR") != -1 or ret.find("LONG_PTR") != -1 or ret.find("INT_PTR") != -1 or ret.find("FLOAT_PTR") != -1:
                retcode = '    vresp->pop(API_' + ret + ', &' + paramName + ');\n' + retcode







        code += '    uint32_t retCode;\n'
        code += '    P8PLATFORM::CLockObject lock(session->m_callMutex);\n'
        code += '    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));\n'
        code += '    if (!vresp)\n'
        code += '      throw API_ERR_BUFFER;\n'
        code += '    vresp->pop(API_UINT32_T, &retCode);\n'
        if retType != 'void':
          ret = retType.replace(" ", "_").upper()
          ret = ret.replace("*", "_PTR")
          code += '    vresp->pop(API_' + ret + ', &retValue);\n'
        code += retcode
        retcode = ''

        #if ret != "":
         # code += ret





        code += '  }\n'
        code += '  PROCESS_HANDLE_EXCEPTION;\n'

        if retType != 'void':
          code += '\n'
          if retType == 'char*':
            code += '  return retValue ? strdup(retValue) : retValue;\n'
          else:
            code += '  return retValue;\n'

        code += '}\n\n'
      elif line.find("}") != -1:
        found = ""
        funcId += 200
  AddonToKodi_h_file.write(enum)

  return code

code = ''
funcId = 0

shutil.copy('AddonToKodi.cpp.base', 'AddonToKodi.cpp')
AddonToKodi_cpp_file = open('AddonToKodi.cpp', 'a')
AddonToKodi_cpp_file.write('#include <iostream>\n\n')
AddonToKodi_cpp_file.write('#define PROCESS_HANDLE_EXCEPTION \\\n'
                 '  catch (const std::out_of_range& oor) \\\n'
                 '  { \\\n'
                 '    fprintf(stderr, "Binary AddOn - '+'%'+'s: Thread out of Range error: '+'%'+'s\\n", __FUNCTION__, oor.what()); \\\n'
                 '    std::cerr << __FUNCTION__ << " - Thread out of Range error: " << oor.what() << \'\\n\'; \\\n'
                 '    exit(1); \\\n'
                 '  } \\\n'
                 '  catch (uint32_t err) \\\n'
                 '  { \\\n'
                 '    kodi::Log(ADDON_LOG_ERROR, StringUtils::Format("Binary AddOn - '+'%'+'s: Addon received error after send of log entry to Kodi: '+'%'+'s", \\\n'
                 '                    __FUNCTION__, errorTranslator[err].errorName).c_str()); \\\n'
                 '  }\n\n')

shutil.copy('AddonToKodi.h.base', 'AddonToKodi.h')
AddonToKodi_h_file = open('AddonToKodi.h', 'a')
AddonToKodi_h_file.write('/* Warning: Auto generated code, do not change by hand! */\n\n')
AddonToKodi_h_file.write('typedef enum AddonToKodiInterfaceCalls\n{\n')

from os.path import join, getsize
for root, dirs, files in os.walk(options.source):
  for file in files:
    code += find_interface(root + '/' + file, funcId)
    funcId += 10000
AddonToKodi_cpp_file.write(code)

AddonToKodi_h_file.write('}AddonToKodiInterfaceCalls;\n\n')
AddonToKodi_h_file.write(AddonToKodi_h_file_code_include)
AddonToKodi_h_file.write(AddonToKodi_h_file_code)
