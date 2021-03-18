from code_generator import *
from .sub_file_hdl import *
from .helpers import *

import glob
import os
import re

def generate__SOURCE__xbmc_addons_interface_api_out_kodi_ALL_FILES(force):
  """
  This function generate automatic code inside xbmc/addons/interface/api_out
  """
  print('  - Generate files in xbmc/addons/interface/api_out')

