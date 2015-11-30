#pragma once
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

namespace AddOnLIB
{
namespace V2
{

  inline void* CAddOnLib_File::OpenFile(const std::string& strFileName, unsigned int flags)
  {
    return CAddonLib::g_libKODI_Internal->OpenFile(strFileName.c_str(), flags);
  }

  inline void* CAddOnLib_File::OpenFileForWrite(const std::string& strFileName, bool bOverWrite)
  {
    return CAddonLib::g_libKODI_Internal->OpenFileForWrite(strFileName.c_str(), bOverWrite);
  }

  inline ssize_t CAddOnLib_File::ReadFile(void* file, void* lpBuf, size_t uiBufSize)
  {
    return CAddonLib::g_libKODI_Internal->ReadFile(file, lpBuf, uiBufSize);
  }

  inline bool CAddOnLib_File::ReadFileString(void* file, char *szLine, int iLineLength)
  {
    return CAddonLib::g_libKODI_Internal->ReadFileString(file, szLine, iLineLength);
  }

  inline ssize_t CAddOnLib_File::WriteFile(void* file, const void* lpBuf, size_t uiBufSize)
  {
    return CAddonLib::g_libKODI_Internal->WriteFile(file, lpBuf, uiBufSize);
  }

  inline void CAddOnLib_File::FlushFile(void* file)
  {
     CAddonLib::g_libKODI_Internal->FlushFile(file);
  }

  inline int64_t CAddOnLib_File::SeekFile(void* file, int64_t iFilePosition, int iWhence)
  {
    return CAddonLib::g_libKODI_Internal->SeekFile(file, iFilePosition, iWhence);
  }

  inline int CAddOnLib_File::TruncateFile(void* file, int64_t iSize)
  {
    return CAddonLib::g_libKODI_Internal->TruncateFile(file, iSize);
  }

  inline int64_t CAddOnLib_File::GetFilePosition(void* file)
  {
    return CAddonLib::g_libKODI_Internal->GetFilePosition(file);
  }

  inline int64_t CAddOnLib_File::GetFileLength(void* file)
  {
    return CAddonLib::g_libKODI_Internal->GetFileLength(file);
  }

  inline void CAddOnLib_File::CloseFile(void* file)
  {
    CAddonLib::g_libKODI_Internal->CloseFile(file);
  }

  inline int CAddOnLib_File::GetFileChunkSize(void* file)
  {
    return CAddonLib::g_libKODI_Internal->GetFileChunkSize(file);
  }

  inline bool CAddOnLib_File::FileExists(const std::string& strFileName, bool bUseCache)
  {
    return CAddonLib::g_libKODI_Internal->FileExists(strFileName.c_str(), bUseCache);
  }

  inline int CAddOnLib_File::StatFile(const std::string& strFileName, struct __stat64* buffer)
  {
    return CAddonLib::g_libKODI_Internal->StatFile(strFileName.c_str(), buffer);
  }

  inline bool CAddOnLib_File::DeleteFile(const std::string& strFileName)
  {
    return CAddonLib::g_libKODI_Internal->DeleteFile(strFileName.c_str());
  }

}; /* namespace V2 */
}; /* namespace AddOnLIB */
