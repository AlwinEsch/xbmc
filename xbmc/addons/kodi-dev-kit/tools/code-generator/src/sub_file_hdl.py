#!/usr/bin/env python3

def read_file(name, normalize=True):
  """ Read a file. """
  try:
    with open(name, 'r', encoding='utf-8') as f:
      # read the data
      data = f.read()
      if normalize:
        # normalize line endings
        data = data.replace("\r\n", "\n")
      return data
  except IOError as e:
    (errno, strerror) = e.args
    sys.stderr.write('Failed to read file ' + name + ': ' + strerror)
    raise

def write_file(name, data):
  """ Write a file. """
  try:
    with open(name, 'w', encoding='utf-8') as f:
      # write the data
      if sys.version_info.major == 2:
        f.write(data.decode('utf-8'))
      else:
        f.write(data)
  except IOError as e:
    (errno, strerror) = e.args
    sys.stderr.write('Failed to write file ' + name + ': ' + strerror)
    raise
