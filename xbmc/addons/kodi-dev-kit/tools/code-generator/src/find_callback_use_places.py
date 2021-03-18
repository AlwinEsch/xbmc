from code_generator import *
from .sub_file_hdl import *
from .helpers import *

import glob
import os
import re
import filecmp
import shutil

class found_callback_function:
  def __init__(self):
    api_call = ''
    complete = ''
    function_name = ''
    class_name = ''
    call_class = ''
    header = ''

def find_callback_use_places(options):
  print('  - Scanning for use places of callbacks in Kodi')

  ret_list = []

  search_dir = '{}xbmc'.format(kodi_dir)
  ignored_dir1 = '{}xbmc/addons/kodi-dev-kit'.format(kodi_dir)
  ignored_dir2 = '{}xbmc/addons/interface'.format(kodi_dir)
  scan_dir = search_dir + '/**/*.h'
  dirs = sorted(glob.glob(scan_dir, recursive=True))
  for path in dirs:
    if path.startswith(ignored_dir1) or path.startswith(ignored_dir2):
      continue

    with open(path) as f:
      file_text = f.read()
      f.close()

    if not '---AUTO_GEN_PARSE<CB:' in file_text:
      continue

    file_text2 = ''
    in_doc = False
    in_private = False
    for line in file_text.splitlines():
      line = line.strip()
      if line == '':
        continue
      if (line.startswith('class ') or line.startswith('struct ')) and line.endswith(';'):
        continue
      if line.startswith('#'):
        continue

      if '---AUTO_GEN_PARSE<CB:' in line:
        file_text2 += ' '.join(line.split()) + '\n'
        continue
      if line.startswith('//') or (line.startswith('/*') and line.endswith('*/')):
        continue
      if line.startswith('/*'):
        in_doc = True
        continue
      if in_doc:
        if line.endswith('*/'):
          in_doc = False
        continue
      if '//' in line:
        line = line.split('//')[0].strip()
      if '/*' in line and '*/' in line:
        line = line.split('/*')[0].rstrip() + line.split('*/')[-1].lstrip()
      if line == 'private:' or line == 'protected:':
        in_private = True
      if in_private and (line == 'public:' or line == '};'):
        in_private = False
      if in_private:
        continue
      file_text2 += ' '.join(line.split()) + ('\n' if not line.endswith(',') else '')

    last_count_type = []
    group_start = False
    prev_line = ''
    for line in file_text2.splitlines():
      found = False

      if not found:
        m = re.search('^(?:[ \t]*)namespace.*[ \t](.*[a-zA-Z0-9_])(?:[ \t]*)((?:{))?$', line)
        if m and m.group(1):
          last_count_type.append(['namespace', m.group(1)])
          found = True
          group_start = True

      if not found:
        m = re.search('^(?:[ \t]*)class[ \t]*([a-zA-Z0-9_]*).*?(;)?$', line)
        if m and m.group(1) and not m.group(2):
          last_count_type.append(['class', m.group(1)])
          found = True
          group_start = True

      if not found:
        m = re.search('^(?:[ \t]*)struct[ \t]*([a-zA-Z0-9_]*).*?(;)?$', line)
        if m and m.group(1) and not m.group(2):
          last_count_type.append(['struct', m.group(1)])
          found = True
          group_start = True

      if not found:
        if group_start and '{' in line and (len(last_count_type) == 0 or (last_count_type[-1][0] == 'namespace' or last_count_type[-1][0] == 'class' or last_count_type[-1][0] == 'struct')):
          group_start = False
          continue

        if '{' in line:
          last_count_type.append(['undefined', ''])
          found = True

      if '}' in line:
        del last_count_type[-1]

      m = re.search('\/\*---AUTO_GEN_PARSE<CB:([a-zA-Z0-9_]*)>---\*\/$', line)
      if m and m.group(1):
        found = found_callback_function()
        found.api_call = m.group(1)
        found.complete = prev_line.split(';')[-2].strip() if line.startswith('/*') else line
        found.header = path.replace(search_dir + '/', '')

        m = re.search('^.*\ (.*[a-zA-Z0-9_])(?:[\t ]*)\(', found.complete)
        if m and m.group(1):
          found.function_name = m.group(1)

        found.call_class = ''
        for entry in last_count_type:
          found.call_class += entry[1] + '::'
        if found.call_class.endswith('::'):
          found.call_class = found.call_class[:-2]

        ret_list.append(found)

      prev_line = line

  return ret_list
