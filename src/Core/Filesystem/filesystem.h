/*
    This file is part of Warzone 2100.
    Copyright (C) 2011  Warzone 2100 Project

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

#ifndef CORE_FILESYSTEM_H
#define CORE_FILESYSTEM_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QHash>

#include <Core/Filesystem/physfs_ext.h>

namespace FileSystem {

enum searchPathMode { mod_clean, mod_campaign, mod_multiplay, mod_override };

enum GAMEMOD_TYPE
{
    GAMEMOD_GLOBAL,     // Mod for both multiplay and campaign games.
    GAMEMOD_CAMPAIGN,   // Campaign only mod.
    GAMEMOD_MULTIPLAY   // Multiplay only mod.
};

typedef QHash<QString, QString> MOD_LIST;

/**
 * @brief Initalizes Physfs and creates the writedir.
 *
 * @param binpath       Application path - argv[0].
 * @param appSubDir     Subdirectory in platforms Userdir for the Physfs writedir.
 * @param cmdUserDir    User supplied userdir which overwrites the platform userdir and appSubDir.
 */
void init(const char* binpath, const char* appSubDir, const QString& cmdUserdir = QString());

/**
 * @brief Finds the application data and adds it to the search path.
 *
 * @param cmDataDir     User supplied data dir which overwrites ours.
 * @param fallbackDir   ?
 */
void scanDataDirs(const QString cmdDataDir = QString(), const QString fallbackDir = QString());

/**
 * @brief Rebuilds the PHYSFS searchPath with mode specific subdirs
 *
 * Priority:
 * maps > mods > base > base.wz
 *
 * @param mode      The Mode to rebuild to either mod_campaign or mod_multiplay.
 * @param force     Ignoring the internal state, force a rebuild.
 */
bool rebuildSearchPath( searchPathMode mode, bool force = false);

/**
 * @brief Loads all maps into the searchpath and sets the search mode to mod_multiplay.
 */
void loadMaps();

/**
 * @brief Appends the given map path to the search path, remove it with unloadMaps().
 */
void loadMap(const char *path);

/**
 * @brief Unloads all maps from the searchpath and resets the search mode.
 */
void unloadMaps();

bool loadMod(GAMEMOD_TYPE type, const char* mod, bool reloadList = false);
void unloadMods();
const MOD_LIST& getLoadedMods();

} // namespace FileSystem {

#endif //#ifndef CORE_FILESYSTEM_H