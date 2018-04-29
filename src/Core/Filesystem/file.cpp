/*
    This file is part of Warzone 2100.
    Copyright (C) 1999-2004  Eidos Interactive
    Copyright (C) 2005-2011  Warzone 2100 Project

    Warzone 2100 is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Warzone 2100 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Warzone 2100; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

/*
 * Frame.c
 *
 * Initialisation and shutdown for the framework library.
 *
 * Includes a basic windows message loop.
 *
 */
#include <src/Core/Framework/frame.h>
#include "file.h"

// Logging
#include <lib/WzLog/Logger.h>

// For LOG_FS
#include "filesystem.h"

PHYSFS_file* openLoadFile(const char* fileName, bool hard_fail)
{
    PHYSFS_file* fileHandle = PHYSFS_openRead(fileName);
    wzLog(LOG_NEVER) << QString("Reading...[directory: %1] %2").arg(PHYSFS_getRealDir(fileName)).arg(fileName);
    if (!fileHandle)
    {
        if (hard_fail)
        {
            ASSERT(!"unable to open file", "file %s could not be opened: %s", fileName, WZ_PHYSFS_getLastError());
        }
        else
        {
            wzLog(LOG_FS) << QString("optional file %1 could not be opened: %2").arg(fileName).arg(WZ_PHYSFS_getLastError());
        }
    }

    return fileHandle;
}

/***************************************************************************
  Load the file with name pointed to by pFileName into a memory buffer.
  If AllocateMem is true then the memory is allocated ... else it is
  already in allocated in ppFileData, and the max size is in pFileSize
  ... this is adjusted to the actual loaded file size.

  If hard_fail is true, we will assert and report on failures.
***************************************************************************/
static bool loadFile2(const char *pFileName, char **ppFileData, uint32_t *pFileSize,
                      bool AllocateMem, bool hard_fail)
{
    PHYSFS_file *pfile;
    PHYSFS_sint64 filesize;
    PHYSFS_sint64 length_read;

    pfile = openLoadFile(pFileName, hard_fail);
    if (!pfile)
    {
        return false;
    }

    filesize = PHYSFS_fileLength(pfile);

    //debug(LOG_WZ, "loadFile2: %s opened, size %i", pFileName, filesize);

    if (AllocateMem)
    {
        // Allocate a buffer to store the data and a terminating zero
        *ppFileData = (char*)malloc(filesize + 1);
        if (*ppFileData == NULL)
        {
            wzLog(LOG_ERROR) << QString("loadFile2: Out of memory loading %1").arg(pFileName);
            assert(false);
            return false;
        }
    }
    else
    {
        if (filesize > *pFileSize)
        {
            wzLog(LOG_ERROR) << QString("loadFile2: No room for file %1, buffer is too small! Got: %2 Need: %3").arg(pFileName).arg(*pFileSize).arg((long)filesize);
            assert(false);
            return false;
        }
        assert(*ppFileData != NULL);
    }

    /* Load the file data */
    length_read = WZ_PHYSFS_readBytes(pfile, *ppFileData, filesize);
    if (length_read != filesize)
    {
        if (AllocateMem)
        {
            free(*ppFileData);
            *ppFileData = NULL;
        }

        wzLog(LOG_ERROR) << QString("Reading %1 short: %2").arg(pFileName).arg(WZ_PHYSFS_getLastError());
        assert(false);
        return false;
    }

    if (!PHYSFS_close(pfile))
    {
        if (AllocateMem)
        {
            free(*ppFileData);
            *ppFileData = NULL;
        }

        wzLog(LOG_ERROR) << QString("Error closing %1: %2").arg(pFileName).arg(WZ_PHYSFS_getLastError());
        assert(false);
        return false;
    }

    // Add the terminating zero
    *((*ppFileData) + filesize) = 0;

    // always set to correct size
    *pFileSize = filesize;

    return true;
}

PHYSFS_file* openSaveFile(const char* fileName)
{
    PHYSFS_file* fileHandle = PHYSFS_openWrite(fileName);
    if (!fileHandle)
    {
        const char *found = PHYSFS_getRealDir(fileName);

        wzLog(LOG_ERROR) << QString("%1 could not be opened: %2").arg(fileName).arg(WZ_PHYSFS_getLastError());
        if (found)
        {
            wzLog(LOG_ERROR) << QString("%1 found as %2").arg(fileName).arg(found);
        }

        assert(!"openSaveFile: couldn't open file for writing");
        return NULL;
    }

    return fileHandle;
}

/***************************************************************************
    Save the data in the buffer into the given file.
***************************************************************************/
bool saveFile(const char *pFileName, const char *pFileData, uint32_t fileSize)
{
    PHYSFS_file *pfile;
    PHYSFS_uint32 size = fileSize;

    wzLog(LOG_FS) << QString("We are to write (%1) of size %2").arg(pFileName).arg(fileSize);
    pfile = openSaveFile(pFileName);
    if (!pfile)
    {
        ASSERT(false, "Couldn't save file %s (%s)?", pFileName, WZ_PHYSFS_getLastError());
        return false;
    }

    if (WZ_PHYSFS_writeBytes(pfile, pFileData, size) != size)
    {
        wzLog(LOG_ERROR) << QString("%1 could not write: %2").arg(pFileName).arg(WZ_PHYSFS_getLastError());
        assert(false);
        return false;
    }
    if (!PHYSFS_close(pfile))
    {
        wzLog(LOG_ERROR) << QString("Error closing %1: %2").arg(pFileName).arg(WZ_PHYSFS_getLastError());
        assert(false);
        return false;
    }

    if (PHYSFS_getRealDir(pFileName) == NULL)
    {
        // weird
        wzLog(LOG_ERROR) << QString("PHYSFS_getRealDir(%1) returns NULL (%2)?!").arg(pFileName).arg(WZ_PHYSFS_getLastError());
    }
    else
    {
        wzLog(LOG_FS) << QString("Successfully wrote to %1%2%3 with %4 bytes").arg(PHYSFS_getRealDir(pFileName)).arg(PHYSFS_getDirSeparator()).arg(pFileName).arg(size);
    }
    return true;
}

bool loadFile(const char *pFileName, char **ppFileData, uint32_t *pFileSize)
{
    return loadFile2(pFileName, ppFileData, pFileSize, true, true);
}

// load a file from disk into a fixed memory buffer
bool loadFileToBuffer(const char *pFileName, char *pFileBuffer, uint32_t bufferSize, uint32_t *pSize)
{
    *pSize = bufferSize;
    return loadFile2(pFileName, &pFileBuffer, pSize, false, true);
}

// as above but returns quietly if no file found
bool loadFileToBufferNoError(const char *pFileName, char *pFileBuffer, uint32_t bufferSize, uint32_t *pSize)
{
    *pSize = bufferSize;
    return loadFile2(pFileName, &pFileBuffer, pSize, false, false);
}
