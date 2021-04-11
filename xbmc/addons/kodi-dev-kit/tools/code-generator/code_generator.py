#!/usr/bin/env python3

global kodi_dir
global force
kodi_dir = "../../../../../"

from src.interface_code_generator import *
from src.find_callback_use_places import *
from src.library_dl_generator import *
from src.generate__SOURCE__xbmc_addons_kodidevkit_src_shared_DIRECTDATA_H import generate__SOURCE__xbmc_addons_kodidevkit_src_shared_DIRECTDATA_H
from src.generate__SOURCE__xbmc_addons_kodidevkit_src_shared_SHAREDGROUPS_H import *
from src.generate__SOURCE__xbmc_addons_kodidevkit_src_shared_INSTANCES_H import *
from src.generate__SOURCE__xbmc_addons_kodidevkit_src_shared_kodi_ALL_FILES import *
from src.generate__SOURCE__xbmc_addons_kodidevkit_src_addon_api_in_kodi_ALL_FILES import *
from src.generate__SOURCE__xbmc_addons_kodidevkit_src_addon_api_out_kodi_ALL_FILES import *
from src.generate__SOURCE__xbmc_addons_interface_api_in_kodi_ALL_FILES import *
from src.generate__SOURCE__xbmc_addons_interface_api_out_kodi_ALL_FILES import *
from src.generate__SOURCE__xbmc_addons_kodidevkit_src_addon_core_ADDON_CONTROL_CPP import *
from src.generate__SOURCE__xbmc_addons_interface_INTERFACE_CPP_H import *
from src.generate__SOURCE__xbmc_addons_interface_api_ALL_FILES import *

from src.generate__CMAKE__xbmc_addons_kodidevkit_include_kodi_ALL_FILES import *
from src.generate__CMAKE__xbmc_addons_kodidevkit_src_shared_CMAKELISTS_TXT import *
from src.generate__CMAKE__xbmc_addons_kodidevkit_src_addon_ALL_FILES import *
from src.generate__CMAKE__xbmc_addons_interface_ALL_FILES import *
from src.generate__CMAKE_TREEDATA__common_ADDON_DEV_KIT_TXT import *
from src.generate__CMAKE_TREEDATA__common_ADDON_INTERFACE_TXT import *

from optparse import OptionParser
import glob
import io
import os
import re
import sys

#===============================================================================
def GenerateSourceParts(options, data):
  print('.-------------------------------------------------------------------------------')
  print('· Generate source code parts ...')

  # Generate xbmc/addons/kodi-dev-kit/src/shared/DirectData.h
  generate__SOURCE__xbmc_addons_kodidevkit_src_shared_DIRECTDATA_H(options)

  ## Generate automatic code inside xbmc/addons/interface/interface.cpp and .h
  generate__SOURCE__xbmc_addons_interface_INTERFACE_CPP_H(options.force)

  ## Generate automatic code inside xbmc/addons/kodi-dev-kit/src/addon/core/addon_control.cpp
  generate__SOURCE__xbmc_addons_kodidevkit_src_addon_core_ADDON_CONTROL_CPP(options.force)

  # This generate automatic code inside xbmc/addons/kodi-dev-kit/src/shared/Instances.h
  generate__SOURCE__xbmc_addons_kodidevkit_src_shared_INSTANCES_H(options)

  # Update xbmc/addons/kodi-dev-kit/src/shared/SharedGroups.h
  generate__SOURCE__xbmc_addons_kodidevkit_src_shared_SHAREDGROUPS_H(options.force)












  ## This generate all automatic code inside xbmc/addons/kodi-dev-kit/src/shared/kodi/
  #generate__SOURCE__xbmc_addons_kodidevkit_src_shared_kodi_ALL_FILES(options.force)

  ## Generate automatic code inside xbmc/addons/kodi-dev-kit/src/addon/api_in
  #generate__SOURCE__xbmc_addons_kodidevkit_src_addon_api_in_kodi_ALL_FILES(options.force)

  ## Generate automatic code inside xbmc/addons/kodi-dev-kit/src/addon/api_out
  #generate__SOURCE__xbmc_addons_kodidevkit_src_addon_api_out_kodi_ALL_FILES(options.force)

  ## Generate automatic code inside xbmc/addons/interface/api_in
  #generate__SOURCE__xbmc_addons_interface_api_in_kodi_ALL_FILES(options.force)

  ## Generate automatic code inside xbmc/addons/interface/api_out
  #generate__SOURCE__xbmc_addons_interface_api_out_kodi_ALL_FILES(options.force)


  ## Generate or update all files in xbmc/addons/interface/api
  ## WARNING This must be called last as it scan other created dirs
  #generate__SOURCE__xbmc_addons_interface_api_ALL_FILES(options.force)

#===============================================================================
def GenerateCMakeParts(options):
  print('.-------------------------------------------------------------------------------')
  print('· Generate cmake parts ...')

  # Generate all the "CMakeLists.txt" files in xbmc/addons/kodi-dev-kit/include/kodi
  generate__CMAKE__xbmc_addons_kodidevkit_include_kodi_ALL_FILES(options.force)

  # Generate the "CMakeLists.txt" in xbmc/addons/kodi-dev-kit/src/shared
  generate__CMAKE__xbmc_addons_kodidevkit_src_shared_CMAKELISTS_TXT(options.force)

  # Generate all the "CMakeLists.txt" files in xbmc/addons/kodi-dev-kit/src/addon
  generate__CMAKE__xbmc_addons_kodidevkit_src_addon_ALL_FILES(options.force)

  # This call generate the "CMakeLists.txt" in xbmc/addons/interface
  generate__CMAKE__xbmc_addons_interface_ALL_FILES(options.force)

  # Generate Kodi's cmake system related include files to find related parts
  generate__CMAKE_TREEDATA__common_ADDON_DEV_KIT_TXT(options.force)
  generate__CMAKE_TREEDATA__common_ADDON_INTERFACE_TXT(options.force)

#===============================================================================
def print_error(msg):
  print('Error: %s\nSee --help for usage.' % msg)

#===============================================================================
if __name__ == "__main__":
  # parse command-line options
  disc = """
  This utility autogenerate the interface between Kodi and addon.
  """
  parser = OptionParser(description=disc)
  parser.add_option(
      '-f',
      '--force',
      action='store_true',
      dest='force',
      default=False,
      help='force the generation of auto code')
  parser.add_option(
      '-d',
      '--debug',
      action='store_true',
      dest='debug',
      default=False,
      help='Add debug indendifiers to generated files')
  (options, args) = parser.parse_args()

  print('Auto generation of addon interface code started ...')

  if os.path.isdir('./tmp'):
    shutil.rmtree('./tmp')

  GetHighestUsedAPI() # Init it
  ScanAllHdlVoidPointer()
  ScanAllEnums()

  callbacks = find_callback_use_places(options)
  data = interface_code_generator(options, callbacks)

  api = 1
  while True:
    dl_gen = LibraryDLGenerator(options, api)
    if not dl_gen.Generate():
      break
    api += 1

  #-----------------------------------------------------------------------------
  # Source code generation
  data = ''
  GenerateSourceParts(options, data)

  ##-----------------------------------------------------------------------------
  # CMake generation
  #GenerateCMakeParts(options)



#ScanAllHdlVoidPointer(kodi_dir)
#ScanAllFunctionAutoGenHelp(kodi_dir)

#generate__SOURCE__xbmc_addons_kodidevkit_src_shared_kodi_ALL_FILES(kodi_dir, force)
####generate__SOURCE__xbmc_addons_kodidevkit_src_shared_kodi_addoninstance_INSTANCES_H(kodi_dir, force)
#generate__SOURCE__xbmc_addons_kodidevkit_src_addon_api_in__ALL_FILES(kodi_dir, force)








#generate__SOURCE__xbmc_addons_kodidevkit_src_addon_core_addon_control_cpp(kodi_dir, force)
#generate__SOURCE__xbmc_addons_interface_api(kodi_dir, force)
#generate__SOURCE__api_autogen(kodi_dir, force)

##generate__SOURCE__xbmc_addons_kodidevkit_src_shared_kodi(kodi_dir, force)


