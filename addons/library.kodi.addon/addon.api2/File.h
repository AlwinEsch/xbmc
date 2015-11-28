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

#include "definations.h"
#include "internal/libKODI_addon_FileHead.h"
#include "internal/libKODI_addon_Internal.h"

namespace AddOnLIB
{
namespace V2
{
  class CAddOnLib_File
  {
  public:
    /*!
     * @brief Open the file with filename via KODI's CFile. Needs to be closed by calling CloseFile() when done.
     * @param strFileName The filename to open.
     * @param flags The flags to pass. Documented in KODI's File.h
     * @return A handle for the file, or NULL if it couldn't be opened.
     */
    static void* OpenFile(const std::string& strFileName, unsigned int flags);

    /*!
     * @brief Open the file with filename via KODI's CFile in write mode. Needs to be closed by calling CloseFile() when done.
     * @param strFileName The filename to open.
     * @param bOverWrite True to overwrite, false otherwise.
     * @return A handle for the file, or NULL if it couldn't be opened.
     */
    static void* OpenFileForWrite(const std::string& strFileName, bool bOverWrite);

    /*!
     * @brief Read from an open file.
     * @param file The file handle to read from.
     * @param lpBuf The buffer to store the data in.
     * @param uiBufSize The size of the buffer.
     * @return number of successfully read bytes if any bytes were read and stored in
     *         buffer, zero if no bytes are available to read (end of file was reached)
     *         or undetectable error occur, -1 in case of any explicit error
     */
    static ssize_t ReadFile(void* file, void* lpBuf, size_t uiBufSize);

    /*!
     * @brief Read a string from an open file.
     * @param file The file handle to read from.
     * @param szLine The buffer to store the data in.
     * @param iLineLength The size of the buffer.
     * @return True when a line was read, false otherwise.
     */
    static bool ReadFileString(void* file, char *szLine, int iLineLength);

    /*!
     * @brief Write to a file opened in write mode.
     * @param file The file handle to write to.
     * @param lpBuf The data to write.
     * @param uiBufSize Size of the data to write.
     * @return number of successfully written bytes if any bytes were written,
     *         zero if no bytes were written and no detectable error occur,
     *         -1 in case of any explicit error
     */
    static ssize_t WriteFile(void* file, const void* lpBuf, size_t uiBufSize);

    /*!
     * @brief Flush buffered data.
     * @param file The file handle to flush the data for.
     */
    static void FlushFile(void* file);

    /*!
     * @brief Seek in an open file.
     * @param file The file handle to see in.
     * @param iFilePosition The new position.
     * @param iWhence Seek argument. See stdio.h for possible values.
     * @return The new position.
     */
    static int64_t SeekFile(void* file, int64_t iFilePosition, int iWhence);

    /*!
     * @brief Truncate a file to the requested size.
     * @param file The file handle to truncate.
     * @param iSize The new max size.
     * @return New size?
     */
    static int TruncateFile(void* file, int64_t iSize);

    /*!
     * @brief The current position in an open file.
     * @param file The file handle to get the position for.
     * @return The requested position.
     */
    static int64_t GetFilePosition(void* file);

    /*!
     * @brief Get the file size of an open file.
     * @param file The file to get the size for.
     * @return The requested size.
     */
    static int64_t GetFileLength(void* file);

    /*!
     * @brief Close an open file.
     * @param file The file handle to close.
     */
    static void CloseFile(void* file);

    /*!
     * @brief Get the chunk size for an open file.
     * @param file the file handle to get the size for.
     * @return The requested size.
     */
    static int GetFileChunkSize(void* file);

    /*!
     * @brief Check if a file exists.
     * @param strFileName The filename to check.
     * @param bUseCache Check in file cache.
     * @return true if the file exists false otherwise.
     */
    static bool FileExists(const std::string& strFileName, bool bUseCache);

    /*!
     * @brief Reads file status.
     * @param strFileName The filename to read the status from.
     * @param buffer The file status is written into this buffer.
     * @return The file status was successfully read.
     */
    static int StatFile(const std::string& strFileName, struct __stat64* buffer);

    /*!
     * @brief Deletes a file.
     * @param strFileName The filename to delete.
     * @return The file was successfully deleted.
     */
    static bool DeleteFile(const std::string& strFileName);
  }; /* class CAddOnLib_File */

}; /* namespace V2 */
}; /* namespace AddOnLIB */
#include "internal/libKODI_addon_FileFunc.h"
