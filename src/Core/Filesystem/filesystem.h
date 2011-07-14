#ifndef CORE_FILESYSTEM_H
#define CORE_FILESYSTEM_H

#include <QtCore/QString>
#include <QtCore/QStringList>

#include <Core/Filesystem/physfs_ext.h>

namespace FileSystem {

enum searchPathMode { mod_clean, mod_campaign, mod_multiplay, mod_override };

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
 * @brief Unloads all maps from the searchpath and resets the search mode.
 */
void unloadMaps();

void clearOverrides();

void setOverrideMods(const QString& modlist);
QString& getModList();

void setOverrideMap(QString map, int maxPlayers);

} // namespace FileSystem {

#endif //#ifndef CORE_FILESYSTEM_H