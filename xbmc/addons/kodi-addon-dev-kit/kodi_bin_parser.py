#!/usr/bin/python

from date_util import *
from file_util import *
import os
import re
import shutil
import string
import sys
import textwrap
import time

#def notify(msg):
  #""" Display a message. """
  #sys.stdout.write('  NOTE: ' + msg + '\n')


#def wrap_text(text, indent='', maxchars=80):
  #""" Wrap the text to the specified number of characters. If
    #necessary a line will be broken and wrapped after a word.
    #"""
  #result = ''
  #lines = textwrap.wrap(text, maxchars - len(indent))
  #for line in lines:
    #result += indent + line + '\n'
  #return result

## regex for matching comment-formatted attributes
#_cre_attrib = '/\*--cef\(([A-Za-z0-9_ ,=:\n]{0,})\)--\*/'
## regex for matching class and function names
#_cre_cfname = '([A-Za-z0-9_]{1,})'
## regex for matching class and function names including path separators
#_cre_cfnameorpath = '([A-Za-z0-9_\/]{1,})'
## regex for matching function return values
#_cre_retval = '([A-Za-z0-9_<>:,\*\&]{1,})'
## regex for matching typedef value and name combination
#_cre_typedef = '([A-Za-z0-9_<>:,\*\&\s]{1,})'
## regex for matching function return value and name combination
#_cre_func = '([A-Za-z][A-Za-z0-9_<>:,\*\&\s]{1,})'
## regex for matching virtual function modifiers + arbitrary whitespace
#_cre_vfmod = '([\sA-Za-z0-9_]{0,})'
## regex for matching arbitrary whitespace
#_cre_space = '[\s]{1,}'
## regex for matching optional virtual keyword
#_cre_virtual = '(?:[\s]{1,}virtual){0,1}'

## Simple translation types. Format is:
##   'cpp_type' : ['capi_type', 'capi_default_value']
#_simpletypes = {
    #'void': ['void', ''],
    #'void*': ['void*', 'NULL'],
    #'int': ['int', '0'],
    #'int32': ['int32', '0'],
    #'uint32': ['uint32', '0'],
    #'int64': ['int64', '0'],
    #'uint64': ['uint64', '0'],
    #'double': ['double', '0'],
    #'float': ['float', '0'],
    #'long': ['long', '0'],
    #'unsigned long': ['unsigned long', '0'],
    #'long long': ['long long', '0'],
    #'size_t': ['size_t', '0'],
    #'bool': ['int', '0'],
    #'char': ['char', '0'],
    #'char* const': ['char* const', 'NULL'],
    #'cef_color_t': ['cef_color_t', '0'],
    #'cef_json_parser_error_t': ['cef_json_parser_error_t', 'JSON_NO_ERROR'],
    #'cef_plugin_policy_t': ['cef_plugin_policy_t', 'PLUGIN_POLICY_ALLOW'],
    #'CefCursorHandle': ['cef_cursor_handle_t', 'kNullCursorHandle'],
    #'CefCompositionUnderline': [
        #'cef_composition_underline_t', 'CefCompositionUnderline()'
    #],
    #'CefEventHandle': ['cef_event_handle_t', 'kNullEventHandle'],
    #'CefWindowHandle': ['cef_window_handle_t', 'kNullWindowHandle'],
    #'CefPoint': ['cef_point_t', 'CefPoint()'],
    #'CefRect': ['cef_rect_t', 'CefRect()'],
    #'CefSize': ['cef_size_t', 'CefSize()'],
    #'CefRange': ['cef_range_t', 'CefRange()'],
    #'CefDraggableRegion': ['cef_draggable_region_t', 'CefDraggableRegion()'],
    #'CefThreadId': ['cef_thread_id_t', 'TID_UI'],
    #'AddonProps_Game': ['AddonProps_Game', 'AddonProps_Game'],
    #'ADDON_HANDLE_STRUCT': ['void*', 'NULL'],
#}

#class obj_analysis:
  #""" Class representing an analysis of a data type value. """

  #def __init__(self, scopelist, value, named):
    #self.value = value
    #self.result_type = 'unknown'
    #self.result_value = None
    #self.result_default = None
    #self.ptr_type = None

    ## parse the argument string
    #partlist = string.split(string.strip(value))

    #if named == True:
      ## extract the name value
      #self.name = partlist[-1]
      #del partlist[-1]
    #else:
      #self.name = None

    #if len(partlist) == 0:
      #raise Exception('Invalid argument value: ' + value)

    ## check const status
    #if partlist[0] == 'const':
      #self.isconst = True
      #del partlist[0]
    #else:
      #self.isconst = False

    #if len(partlist) == 0:
      #raise Exception('Invalid argument value: ' + value)

    ## combine the data type
    #self.type = string.join(partlist, ' ')

    ## extract the last character of the data type
    #endchar = self.type[-1]

    ## check if the value is passed by reference
    #if endchar == '&':
      #self.isbyref = True
      #self.type = self.type[:-1]
    #else:
      #self.isbyref = False

    ## check if the value is passed by address
    #if endchar == '*':
      #self.isbyaddr = True
      #self.type = self.type[:-1]
    #else:
      #self.isbyaddr = False

    ## see if the value is directly identifiable
    #if self._check_advanced(self.type) == True:
      #return

    ## not identifiable, so look it up
    #translation = None
    #for scope in scopelist:
      #if not isinstance(scope, obj_header) \
          #and not isinstance(scope, obj_class):
        #raise Exception('Invalid scope object type')
      #translation = scope.get_alias_translation(self.type)
      #if not translation is None:
        #break

    #if translation is None:
      #raise Exception('Failed to translate type: ' + self.type)

    ## the translation succeeded so keep the result
    #self.result_type = translation.result_type
    #self.result_value = translation.result_value


  #def _check_advanced(self, value):
    ## check for vectors
    #if value.find('std::vector') == 0:
      #self.result_type = 'vector'
      #val = string.strip(value[12:-1])
      #self.result_value = [self._get_basic(val)]
      #self.result_value[0]['vector_type'] = val
      #return True

    ## check for maps
    #if value.find('std::map') == 0:
      #self.result_type = 'map'
      #vals = string.split(value[9:-1], ',')
      #if len(vals) == 2:
        #self.result_value = [
            #self._get_basic(string.strip(vals[0])),
            #self._get_basic(string.strip(vals[1]))
        #]
        #return True

    ## check for multimaps
    #if value.find('std::multimap') == 0:
      #self.result_type = 'multimap'
      #vals = string.split(value[14:-1], ',')
      #if len(vals) == 2:
        #self.result_value = [
            #self._get_basic(string.strip(vals[0])),
            #self._get_basic(string.strip(vals[1]))
        #]
        #return True

    ## check for basic types
    #basic = self._get_basic(value)
    #if not basic is None:
      #self.result_type = basic['result_type']
      #self.result_value = basic['result_value']
      #if 'ptr_type' in basic:
        #self.ptr_type = basic['ptr_type']
      #if 'result_default' in basic:
        #self.result_default = basic['result_default']
      #return True

    #return False

  #def _get_basic(self, value):
    ## check for string values
    #if value == "CefString":
      #return {'result_type': 'string', 'result_value': None}

    ## check for simple direct translations
    #if value in _simpletypes.keys():
      #return {
          #'result_type': 'simple',
          #'result_value': _simpletypes[value][0],
          #'result_default': _simpletypes[value][1],
      #}

    ## check if already a C API structure
    #if value[-2:] == '_t':
      #return {'result_type': 'structure', 'result_value': value}

    ## check for CEF reference pointers
    #p = re.compile('^CefRefPtr<(.*?)>$', re.DOTALL)
    #list = p.findall(value)
    #if len(list) == 1:
      #return {
          #'result_type': 'refptr',
          #'result_value': get_capi_name(list[0], True) + '*',
          #'ptr_type': list[0]
      #}

    ## check for CEF owned pointers
    #p = re.compile('^CefOwnPtr<(.*?)>$', re.DOTALL)
    #list = p.findall(value)
    #if len(list) == 1:
      #return {
          #'result_type': 'ownptr',
          #'result_value': get_capi_name(list[0], True) + '*',
          #'ptr_type': list[0]
      #}

    ## check for CEF raw pointers
    #p = re.compile('^CefRawPtr<(.*?)>$', re.DOTALL)
    #list = p.findall(value)
    #if len(list) == 1:
      #return {
          #'result_type': 'rawptr',
          #'result_value': get_capi_name(list[0], True) + '*',
          #'ptr_type': list[0]
      #}

    ## check for CEF structure types
    #if value[0:3] == 'Cef' and value[-4:] != 'List':
      #return {
          #'result_type': 'structure',
          #'result_value': get_capi_name(value, True)
      #}

    #return None

  #def __repr__(self):
    #return '(' + self.result_type + ') ' + str(self.result_value)

  #def has_name(self):
    #""" Returns true if a name value exists. """
    #return (not self.name is None)

  #def get_name(self):
    #""" Return the name. """
    #return self.name

  #def get_value(self):
    #""" Return the C++ value (type + name). """
    #return self.value

  #def get_type(self):
    #""" Return the C++ type. """
    #return self.type

  #def get_ptr_type(self):
    #""" Return the C++ class type referenced by a CefRefPtr. """
    #if self.is_result_vector() and self.is_result_vector_ptr():
      ## return the vector RefPtr type
      #return self.result_value[0]['ptr_type']
    ## return the basic RefPtr type
    #return self.ptr_type

  #def get_vector_type(self):
    #""" Return the C++ class type referenced by a std::vector. """
    #if self.is_result_vector():
      #return self.result_value[0]['vector_type']
    #return None

  #def is_const(self):
    #""" Returns true if the argument value is constant. """
    #return self.isconst

  #def is_byref(self):
    #""" Returns true if the argument is passed by reference. """
    #return self.isbyref

  #def is_byaddr(self):
    #""" Returns true if the argument is passed by address. """
    #return self.isbyaddr

  #def is_result_simple(self):
    #""" Returns true if this is a simple argument type. """
    #return (self.result_type == 'simple')

  #def get_result_simple_type_root(self):
    #""" Return the simple structure or basic type name. """
    #return self.result_value

  #def get_result_simple_type(self):
    #""" Return the simple type. """
    #result = ''
    #if self.is_const():
      #result += 'const '
    #result += self.result_value
    #if self.is_byaddr() or self.is_byref():
      #result += '*'
    #return result

  #def get_result_simple_default(self):
    #""" Return the default value fo the basic type. """
    #return self.result_default

  #def is_result_ptr(self):
    #""" Returns true if this is a *Ptr type. """
    #return self.is_result_refptr() or self.is_result_ownptr() or \
           #self.is_result_rawptr()

  #def get_result_ptr_type_root(self):
    #""" Return the *Ptr type structure name. """
    #return self.result_value[:-1]

  #def get_result_ptr_type(self, defined_structs=[]):
    #""" Return the *Ptr type. """
    #result = ''
    #if not self.result_value[:-1] in defined_structs:
      #result += 'struct _'
    #result += self.result_value
    #if self.is_byref() or self.is_byaddr():
      #result += '*'
    #return result

  #def get_result_ptr_type_prefix(self):
    #""" Returns the *Ptr type prefix. """
    #if self.is_result_refptr():
      #return 'ref'
    #if self.is_result_ownptr():
      #return 'own'
    #if self.is_result_rawptr():
      #return 'raw'
    #raise Exception('Not a pointer type')

  #def is_result_refptr(self):
    #""" Returns true if this is a RefPtr type. """
    #return (self.result_type == 'refptr')

  #def is_result_ownptr(self):
    #""" Returns true if this is a OwnPtr type. """
    #return (self.result_type == 'ownptr')

  #def is_result_rawptr(self):
    #""" Returns true if this is a RawPtr type. """
    #return (self.result_type == 'rawptr')

  #def is_result_struct(self):
    #""" Returns true if this is a structure type. """
    #return (self.result_type == 'structure')

  #def is_result_struct_enum(self):
    #""" Returns true if this struct type is likely an enumeration. """
    ## structure values that are passed by reference or address must be
    ## structures and not enumerations
    #if not self.is_byref() and not self.is_byaddr():
      #return True
    #return False

  #def get_result_struct_type(self, defined_structs=[]):
    #""" Return the structure or enumeration type. """
    #result = ''
    #is_enum = self.is_result_struct_enum()
    #if not is_enum:
      #if self.is_const():
        #result += 'const '
      #if not self.result_value in defined_structs:
        #result += 'struct _'
    #result += self.result_value
    #if not is_enum:
      #result += '*'
    #return result

  #def is_result_string(self):
    #""" Returns true if this is a string type. """
    #return (self.result_type == 'string')

  #def get_result_string_type(self):
    #""" Return the string type. """
    #if not self.has_name():
      ## Return values are string structs that the user must free. Use
      ## the name of the structure as a hint.
      #return 'cef_string_userfree_t'
    #elif not self.is_const() and (self.is_byref() or self.is_byaddr()):
      ## Parameters passed by reference or address. Use the normal
      ## non-const string struct.
      #return 'cef_string_t*'
    ## Const parameters use the const string struct.
    #return 'const cef_string_t*'

  #def is_result_vector(self):
    #""" Returns true if this is a vector type. """
    #return (self.result_type == 'vector')

  #def is_result_vector_string(self):
    #""" Returns true if this is a string vector. """
    #return self.result_value[0]['result_type'] == 'string'

  #def is_result_vector_simple(self):
    #""" Returns true if this is a string vector. """
    #return self.result_value[0]['result_type'] == 'simple'

  #def is_result_vector_ptr(self):
    #""" Returns true if this is a *Ptr vector. """
    #return self.is_result_vector_refptr() or \
           #self.is_result_vector_ownptr() or \
           #self.is_result_vector_rawptr()

  #def get_result_vector_ptr_type_prefix(self):
    #""" Returns the *Ptr type prefix. """
    #if self.is_result_vector_refptr():
      #return 'ref'
    #if self.is_result_vector_ownptr():
      #return 'own'
    #if self.is_result_vector_rawptr():
      #return 'raw'
    #raise Exception('Not a pointer type')

  #def is_result_vector_refptr(self):
    #""" Returns true if this is a RefPtr vector. """
    #return self.result_value[0]['result_type'] == 'refptr'

  #def is_result_vector_ownptr(self):
    #""" Returns true if this is a OwnPtr vector. """
    #return self.result_value[0]['result_type'] == 'ownptr'

  #def is_result_vector_rawptr(self):
    #""" Returns true if this is a RawPtr vector. """
    #return self.result_value[0]['result_type'] == 'rawptr'

  #def get_result_vector_type_root(self):
    #""" Return the vector structure or basic type name. """
    #return self.result_value[0]['result_value']

  #def get_result_vector_type(self, defined_structs=[]):
    #""" Return the vector type. """
    #if not self.has_name():
      #raise Exception('Cannot use vector as a return type')

    #type = self.result_value[0]['result_type']
    #value = self.result_value[0]['result_value']

    #result = {}
    #if type == 'string':
      #result['value'] = 'cef_string_list_t'
      #result['format'] = 'single'
      #return result

    #if type == 'simple':
      #str = value
      #if self.is_const():
        #str += ' const'
      #str += '*'
      #result['value'] = str
    #elif type == 'refptr' or type == 'ownptr' or type == 'rawptr':
      #str = ''
      #if not value[:-1] in defined_structs:
        #str += 'struct _'
      #str += value
      #if self.is_const():
        #str += ' const'
      #str += '*'
      #result['value'] = str
    #else:
      #raise Exception('Unsupported vector type: ' + type)

    ## vector values must be passed as a value array parameter
    ## and a size parameter
    #result['format'] = 'multi-arg'
    #return result

  #def is_result_map(self):
    #""" Returns true if this is a map type. """
    #return (self.result_type == 'map' or self.result_type == 'multimap')

  #def is_result_map_single(self):
    #""" Returns true if this is a single map type. """
    #return (self.result_type == 'map')

  #def is_result_map_multi(self):
    #""" Returns true if this is a multi map type. """
    #return (self.result_type == 'multimap')

  #def get_result_map_type(self, defined_structs=[]):
    #""" Return the map type. """
    #if not self.has_name():
      #raise Exception('Cannot use map as a return type')
    #if self.result_value[0]['result_type'] == 'string' \
        #and self.result_value[1]['result_type'] == 'string':
      #if self.result_type == 'map':
        #return {'value': 'cef_string_map_t', 'format': 'single'}
      #elif self.result_type == 'multimap':
        #return {'value': 'cef_string_multimap_t', 'format': 'multi'}
    #raise Exception('Only mappings of strings to strings are supported')

  #def get_capi(self, defined_structs=[]):
    #""" Format the value for the C API. """
    #result = ''
    #format = 'single'
    #if self.is_result_simple():
      #result += self.get_result_simple_type()
    #elif self.is_result_ptr():
      #result += self.get_result_ptr_type(defined_structs)
    #elif self.is_result_struct():
      #result += self.get_result_struct_type(defined_structs)
    #elif self.is_result_string():
      #result += self.get_result_string_type()
    #elif self.is_result_map():
      #resdict = self.get_result_map_type(defined_structs)
      #if resdict['format'] == 'single' or resdict['format'] == 'multi':
        #result += resdict['value']
      #else:
        #raise Exception('Unsupported map type')
    #elif self.is_result_vector():
      #resdict = self.get_result_vector_type(defined_structs)
      #if resdict['format'] != 'single':
        #format = resdict['format']
      #result += resdict['value']

    #if self.has_name():
      #result += ' ' + self.get_name()

    #return {'format': format, 'value': result}

#class obj_typedef:
  #""" Class representing a typedef statement. """

  #def __init__(self, parent, filename, value, alias):
    #if not isinstance(parent, obj_header) \
        #and not isinstance(parent, obj_class):
      #raise Exception('Invalid parent object type')

    #self.parent = parent
    #self.filename = filename
    #self.alias = alias
    #self.value = self.parent.get_analysis(value, False)

  #def __repr__(self):
    #return 'typedef ' + self.value.get_type() + ' ' + self.alias + ';'

  #def get_file_name(self):
    #""" Return the C++ header file name. """
    #return self.filename

  #def get_capi_file_name(self):
    #""" Return the CAPI header file name. """
    #return get_capi_file_name(self.filename)

  #def get_alias(self):
    #""" Return the alias. """
    #return self.alias

  #def get_value(self):
    #""" Return an analysis of the value based on the class or header file
        #definition context.
        #"""
    #return self.value

  #def get_types(self, list):
    #""" Return a dictionary mapping data types to analyzed values. """
    #name = self.value.get_type()
    #if not name in list:
      #list[name] = self.value

#class obj_header:
  #""" Class representing a C++ header file. """

  #def __init__(self):
    #self.filenames = []
    #self.typedefs = []
    #self.funcs = []
    #self.classes = []
    #self.root_directory = None

  #def set_root_directory(self, root_directory):
    #""" Set the root directory. """
    #self.root_directory = root_directory

  #def add_directory(self, directory, excluded_files=[]):
    #""" Add all header files from the specified directory. """
    #files = get_files(os.path.join(directory, '*.h'))
    #for file in files:
      #if len(excluded_files) == 0 or \
          #not os.path.split(file)[1] in excluded_files:
        #self.add_file(file)

  #def add_file(self, filepath):
    #""" Add a header file. """

    #if self.root_directory is None:
      #filename = os.path.split(filepath)[1]
    #else:
      #filename = os.path.relpath(filepath, self.root_directory)
      #filename = filename.replace('\\', '/')

    ## read the input file into memory
    #self.add_data(filename, read_file(filepath))

  #def add_data(self, filename, data):
    #""" Add header file contents. """

    #added = False

    ## remove space from between template definition end brackets
    #data = data.replace("> >", ">>")

    ## extract global typedefs
    #p = re.compile('\ntypedef' + _cre_space + _cre_typedef + ';',
                   #re.MULTILINE | re.DOTALL)
    #list = p.findall(data)
    #if len(list) > 0:
      ## build the global typedef objects
      #for value in list:
        #pos = value.rfind(' ')
        #if pos < 0:
          #raise Exception('Invalid typedef: ' + value)
        #alias = value[pos + 1:].strip()
        #value = value[:pos].strip()
        #self.typedefs.append(obj_typedef(self, filename, value, alias))

    ## extract global functions
    #p = re.compile('\n' + _cre_attrib + '\n' + _cre_func + '\((.*?)\)',
                   #re.MULTILINE | re.DOTALL)
    #list = p.findall(data)
    #if len(list) > 0:
      #added = True

      ## build the global function objects
      #for attrib, retval, argval in list:
        #comment = get_comment(data, retval + '(' + argval + ');')
        #validate_comment(filename, retval, comment)
        #self.funcs.append(
            #obj_function(self, filename, attrib, retval, argval, comment))

    ## extract includes
    #p = re.compile('\n#include \"include/' + _cre_cfnameorpath + '.h')
    #includes = p.findall(data)

    ## extract forward declarations
    #p = re.compile('\nclass' + _cre_space + _cre_cfname + ';')
    #forward_declares = p.findall(data)

    ## extract classes
    #p = re.compile('\n' + _cre_attrib + '\nclass' + _cre_space + _cre_cfname +
                   #_cre_space + ':' + _cre_space + 'public' + _cre_virtual +
                   #_cre_space + _cre_cfname + _cre_space + '{(.*?)\n};',
                   #re.MULTILINE | re.DOTALL)
    #list = p.findall(data)
    #if len(list) > 0:
      #added = True

      ## build the class objects
      #for attrib, name, parent_name, body in list:
        ## Style may place the ':' on the next line.
        #comment = get_comment(data, name + ' :')
        #if len(comment) == 0:
          #comment = get_comment(data, name + "\n")
        #validate_comment(filename, name, comment)
        #self.classes.append(
            #obj_class(self, filename, attrib, name, parent_name, body, comment,
                      #includes, forward_declares))

    ## extract empty classes
    #p = re.compile('\n' + _cre_attrib + '\nclass' + _cre_space + _cre_cfname +
                   #_cre_space + ':' + _cre_space + 'public' + _cre_virtual +
                   #_cre_space + _cre_cfname + _cre_space + '{};',
                   #re.MULTILINE | re.DOTALL)
    #list = p.findall(data)
    #if len(list) > 0:
      #added = True

      ## build the class objects
      #for attrib, name, parent_name in list:
        ## Style may place the ':' on the next line.
        #comment = get_comment(data, name + ' :')
        #if len(comment) == 0:
          #comment = get_comment(data, name + "\n")
        #validate_comment(filename, name, comment)
        #self.classes.append(
            #obj_class(self, filename, attrib, name, parent_name, "", comment,
                      #includes, forward_declares))

    #if added:
      ## a global function or class was read from the header file
      #self.filenames.append(filename)

  #def __repr__(self):
    #result = ''

    #if len(self.typedefs) > 0:
      #strlist = []
      #for cls in self.typedefs:
        #strlist.append(str(cls))
      #result += string.join(strlist, "\n") + "\n\n"

    #if len(self.funcs) > 0:
      #strlist = []
      #for cls in self.funcs:
        #strlist.append(str(cls))
      #result += string.join(strlist, "\n") + "\n\n"

    #if len(self.classes) > 0:
      #strlist = []
      #for cls in self.classes:
        #strlist.append(str(cls))
      #result += string.join(strlist, "\n")

    #return result

  #def get_file_names(self):
    #""" Return the array of header file names. """
    #return self.filenames

  #def get_typedefs(self):
    #""" Return the array of typedef objects. """
    #return self.typedefs

  #def get_funcs(self, filename=None):
    #""" Return the array of function objects. """
    #if filename is None:
      #return self.funcs
    #else:
      ## only return the functions in the specified file
      #res = []
      #for func in self.funcs:
        #if func.get_file_name() == filename:
          #res.append(func)
      #return res

  #def get_classes(self, filename=None):
    #""" Return the array of class objects. """
    #if filename is None:
      #return self.classes
    #else:
      ## only return the classes in the specified file
      #res = []
      #for cls in self.classes:
        #if cls.get_file_name() == filename:
          #res.append(cls)
      #return res

  #def get_class(self, classname, defined_structs=None):
    #""" Return the specified class or None if not found. """
    #for cls in self.classes:
      #if cls.get_name() == classname:
        #return cls
      #elif not defined_structs is None:
        #defined_structs.append(cls.get_capi_name())
    #return None

  #def get_class_names(self):
    #""" Returns the names of all classes in this object. """
    #result = []
    #for cls in self.classes:
      #result.append(cls.get_name())
    #return result

  #def get_base_class_name(self, classname):
    #""" Returns the base (root) class name for |classname|. """
    #cur_cls = self.get_class(classname)
    #while True:
      #parent_name = cur_cls.get_parent_name()
      #if is_base_class(parent_name):
        #return parent_name
      #else:
        #parent_cls = self.get_class(parent_name)
        #if parent_cls is None:
          #break
      #cur_cls = self.get_class(parent_name)
    #return None

  #def get_types(self, list):
    #""" Return a dictionary mapping data types to analyzed values. """
    #for cls in self.typedefs:
      #cls.get_types(list)

    #for cls in self.classes:
      #cls.get_types(list)

  #def get_alias_translation(self, alias):
    #""" Return a translation of alias to value based on typedef
            #statements. """
    #for cls in self.typedefs:
      #if cls.alias == alias:
        #return cls.value
    #return None

  #def get_analysis(self, value, named=True):
    #""" Return an analysis of the value based the header file context. """
    #return obj_analysis([self], value, named)

  #def get_defined_structs(self):
    #""" Return a list of already defined structure names. """
    #return [
        #'cef_print_info_t', 'cef_window_info_t', 'cef_base_ref_counted_t',
        #'cef_base_scoped_t'
    #]

  #def get_capi_translations(self):
    #""" Return a dictionary that maps C++ terminology to C API terminology.
        #"""
    ## strings that will be changed in C++ comments
    #map = {
        #'class': 'structure',
        #'Class': 'Structure',
        #'interface': 'structure',
        #'Interface': 'Structure',
        #'true': 'true (1)',
        #'false': 'false (0)',
        #'empty': 'NULL',
        #'method': 'function'
    #}

    ## add mappings for all classes and functions
    #funcs = self.get_funcs()
    #for func in funcs:
      #map[func.get_name() + '()'] = func.get_capi_name() + '()'

    #classes = self.get_classes()
    #for cls in classes:
      #map[cls.get_name()] = cls.get_capi_name()

      #funcs = cls.get_virtual_funcs()
      #for func in funcs:
        #map[func.get_name() + '()'] = func.get_capi_name() + '()'

      #funcs = cls.get_static_funcs()
      #for func in funcs:
        #map[func.get_name() + '()'] = func.get_capi_name() + '()'

    #return map

if __name__ == "__main__":
  import pprint
  import sys

  # verify that the correct number of command-line arguments are provided
  if len(sys.argv) != 2:
    sys.stderr.write('Usage: ' + sys.argv[0] + ' <directory>')
    sys.exit()

  pp = pprint.PrettyPrinter(indent=4)

  # create the header object
  #header = obj_header()
  #header.add_directory(sys.argv[1])

  ## output the type mapping
  #types = {}
  #header.get_types(types)
  #pp.pprint(types)
  #sys.stdout.write('\n')

  ## output the parsed C++ data
  #sys.stdout.write(str(header))
