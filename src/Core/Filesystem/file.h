/*
	This file is part of Warzone 2100.
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
#ifndef __CORE_FILESYSTEM_FILE_H__
#define __CORE_FILESYSTEM_FILE_H__

#include <physfs.h>

#define PHYSFS_APPEND 1
#define PHYSFS_PREPEND 0

// Detect the version of PhysFS
#if PHYSFS_VER_MAJOR > 2 || (PHYSFS_VER_MAJOR == 2 && PHYSFS_VER_MINOR >= 1)
    #define WZ_PHYSFS_2_1_OR_GREATER
#elif (PHYSFS_VER_MAJOR == 2 && PHYSFS_VER_MINOR == 0)
    #define WZ_PHYSFS_2_0_OR_GREATER
#else
    #error WZ requires PhysFS 2.0+
#endif

#if defined(WZ_PHYSFS_2_1_OR_GREATER)
    #define WZ_PHYSFS_getLastError() \
        PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())
#else
    #define WZ_PHYSFS_getLastError() \
        PHYSFS_getLastError()
#endif

static inline int WZ_PHYSFS_unmount (const char * oldDir)
{
#if defined(WZ_PHYSFS_2_1_OR_GREATER)
    return PHYSFS_unmount(oldDir);
#else
    // PHYSFS_unmount is functionally equivalent to PHYSFS_removeFromSearchPath (the vocabulary just changed)
    return PHYSFS_removeFromSearchPath(oldDir);
#endif
}

static inline int WZ_PHYSFS_mount(const char *newDir, int appendToPath)
{
#if defined(WZ_PHYSFS_2_1_OR_GREATER)
    return PHYSFS_mount(newDir, NULL, appendToPath);
#else
    // PHYSFS_mount is functionally equivalent to PHYSFS_addToSearchPath
    return PHYSFS_addToSearchPath(newDir, appendToPath);
#endif
}

// NOTE: This uses PHYSFS_uint32 for `len` because PHYSFS_read takes a PHYSFS_uint32 objCount
static inline PHYSFS_sint64 WZ_PHYSFS_readBytes (PHYSFS_File * handle, void * buffer, PHYSFS_uint32 len)
{
#if defined(WZ_PHYSFS_2_1_OR_GREATER)
    return PHYSFS_readBytes(handle, buffer, len);
#else
    return PHYSFS_read(handle, buffer, 1, len);
#endif
}


// NOTE: This uses PHYSFS_uint32 for `len` because PHYSFS_write takes a PHYSFS_uint32 objCount
static inline PHYSFS_sint64 WZ_PHYSFS_writeBytes (PHYSFS_File * handle, const void * buffer, PHYSFS_uint32 len)
{
#if defined(WZ_PHYSFS_2_1_OR_GREATER)
    return PHYSFS_writeBytes(handle, buffer, len);
#else
    return PHYSFS_write(handle, buffer, 1, len);
#endif
}


/*! Open a file for reading */
extern PHYSFS_file* openLoadFile(const char* fileName, bool hard_fail);

/*! Open a file for writing */
extern PHYSFS_file* openSaveFile(const char* fileName);

/** Load the file with name pointed to by pFileName into a memory buffer. */
extern bool loadFile(const char *pFileName,		// The filename
              char **ppFileData,	// A buffer containing the file contents
              uint32_t *pFileSize);	// The size of this buffer

/** Save the data in the buffer into the given file */
extern bool saveFile(const char *pFileName, const char *pFileData, uint32_t fileSize);

/** Load a file from disk into a fixed memory buffer. */
extern bool loadFileToBuffer(const char *pFileName, char *pFileBuffer, uint32_t bufferSize, uint32_t *pSize);

/** Load a file from disk, but returns quietly if no file found. */
extern bool loadFileToBufferNoError(const char *pFileName, char *pFileBuffer, uint32_t bufferSize,
                             uint32_t *pSize);

#endif // __CORE_FILESYSTEM_FILE_H__
