/*
 *      Copyright (C) 2015 Team KODI
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "AddonCB_Directory.h"
#include "AddonCallbacksAddon.h"

#include "FileItem.h"
#include "Util.h"
#include "filesystem/File.h"

using namespace XFILE;

namespace AddOnLIB
{
namespace V2
{

CAddonCB_File::CAddonCB_File()
{

}

void CAddonCB_File::Init(CB_AddOnLib *callbacks)
{
  callbacks->File.open_file            = CAddonCB_File::open_file;
  callbacks->File.open_file_for_write  = CAddonCB_File::open_file_for_write;
  callbacks->File.read_file            = CAddonCB_File::read_file;
  callbacks->File.read_file_string     = CAddonCB_File::read_file_string;
  callbacks->File.write_file           = CAddonCB_File::write_file;
  callbacks->File.flush_file           = CAddonCB_File::flush_file;
  callbacks->File.seek_file            = CAddonCB_File::seek_file;
  callbacks->File.truncate_file        = CAddonCB_File::truncate_file;
  callbacks->File.get_file_position    = CAddonCB_File::get_file_position;
  callbacks->File.get_file_length      = CAddonCB_File::get_file_length;
  callbacks->File.close_file           = CAddonCB_File::close_file;
  callbacks->File.get_file_chunk_size  = CAddonCB_File::get_file_chunk_size;
  callbacks->File.file_exists          = CAddonCB_File::file_exists;
  callbacks->File.stat_file            = CAddonCB_File::stat_file;
  callbacks->File.delete_file          = CAddonCB_File::delete_file;
  callbacks->File.get_file_md5         = CAddonCB_File::get_file_md5;
}

void* CAddonCB_File::open_file(
        void*                     hdl,
        const char*               strFileName,
        unsigned int              flags)
{
  CFile* file = new CFile;
  if (file->Open(strFileName, flags))
    return ((void*)file);

  delete file;
  return nullptr;
}

void* CAddonCB_File::open_file_for_write(
        void*                     hdl,
        const char*               strFileName,
        bool                      bOverwrite)
{
  CFile* file = new CFile;
  if (file->OpenForWrite(strFileName, bOverwrite))
    return ((void*)file);

  delete file;
  return nullptr;
}

ssize_t CAddonCB_File::read_file(
        void*                     hdl,
        void*                     file,
        void*                     lpBuf,
        size_t                    uiBufSize)
{
  CFile* cfile = (CFile*)file;
  if (!cfile)
    return 0;

  return cfile->Read(lpBuf, uiBufSize);
}

bool CAddonCB_File::read_file_string(
        void*                     hdl,
        void*                     file,
        char*                     szLine,
        int                       iLineLength)
{
  CFile* cfile = (CFile*)file;
  if (!cfile)
    return false;

  return cfile->ReadString(szLine, iLineLength);
}

ssize_t CAddonCB_File::write_file(
        void*                     hdl,
        void*                     file,
        const void*               lpBuf,
        size_t                    uiBufSize)
{
  CFile* cfile = (CFile*)file;
  if (!cfile)
    return -1;

  return cfile->Write(lpBuf, uiBufSize);
}

void CAddonCB_File::flush_file(
        void*                     hdl,
        void*                     file)
{
  CFile* cfile = (CFile*)file;
  if (cfile)
    cfile->Flush();
}

int64_t CAddonCB_File::seek_file(
        void*                     hdl,
        void*                     file,
        int64_t                   iFilePosition,
        int                       iWhence)
{
  CFile* cfile = (CFile*)file;
  if (!cfile)
    return 0;

  return cfile->Seek(iFilePosition, iWhence);
}

int CAddonCB_File::truncate_file(
        void*                     hdl,
        void*                     file,
        int64_t                   iSize)
{
  CFile* cfile = (CFile*)file;
  if (!cfile)
    return 0;

  return cfile->Truncate(iSize);
}

int64_t CAddonCB_File::get_file_position(
        void*                     hdl,
        void*                     file)
{
  CFile* cfile = (CFile*)file;
  if (!cfile)
    return 0;

  return cfile->GetPosition();
}

int64_t CAddonCB_File::get_file_length(
        void*                     hdl,
        void*                     file)
{
  CFile* cfile = (CFile*)file;
  if (!cfile)
    return 0;

  return cfile->GetLength();
}

void CAddonCB_File::close_file(
        void*                     hdl,
        void*                     file)
{
  CFile* cfile = (CFile*)file;
  if (cfile)
  {
    cfile->Close();
    delete cfile;
  }
}

int CAddonCB_File::get_file_chunk_size(
        void*                     hdl,
        void*                     file)
{
  CFile* cfile = (CFile*)file;
  if (!cfile)
    return 0;

  return cfile->GetChunkSize();
}

bool CAddonCB_File::file_exists(
        void*                     hdl,
        const char*               strFileName,
        bool                      bUseCache)
{
  return CFile::Exists(strFileName, bUseCache);
}

int CAddonCB_File::stat_file(
        void*                     hdl,
        const char*               strFileName,
        struct ::__stat64*          buffer)
{
  return CFile::Stat(strFileName, buffer);
}

bool CAddonCB_File::delete_file(
        void*                     hdl,
        const char*               strFileName)
{
  return CFile::Delete(strFileName);
}

char* CAddonCB_File::get_file_md5(
        void*                     hdl,
        const char*               strFileName)
{
  std::string string;
  if (strFileName != nullptr)
    string = CUtil::GetFileMD5(strFileName);
  else
    string = "";
  char* buffer = strdup(string.c_str());
  return buffer;
}

}; /* namespace V2 */
}; /* namespace AddOnLIB */
