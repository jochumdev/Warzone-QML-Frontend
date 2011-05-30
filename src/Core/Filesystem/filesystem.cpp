#include <Core/Filesystem/filesystem.h>
#include <Core/Filesystem/physfs_ext.h>

// "wz::" handler
#include <Core/Filesystem/qphysfsenginehandler.h>

// QT
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QCoreApplication>

// Logging
#include <lib/WzLog/Log.h>

// For getPlatformUserDir
#if defined(QT_OS_WIN)
    #include <shlobj.h> /* For SHGetFolderPath */
#elif defined(QT_OS_MAC)
    #include <CoreServices/CoreServices.h>
#endif // WZ_OS_WIN

namespace FileSystem {

static QMap<unsigned int, QString> searchPathRegistry;

static QStringList global_mods;
static QStringList campaign_mods;
static QStringList multiplay_mods;

static bool use_override_mods = false;
static QStringList override_mods;

static bool use_override_map = false;
static QStringList override_map;

static QString     mod_list;
static QStringList loaded_mods;

static QVariantMap mapList;

// Registers the "wz::" Filesystem handler.
// FIXME: This is ugly as global
QPhysfsEngineHandler engine;

// Priority range for mods in searchPathRegistry.
const int PRIORITY_MOD_MIN = 100;
const int MAX_MODS = 99;
// Internal Map Priority to add/remove a map from the searchPathRegistry.
const int PRIORITY_MAP = 200;
// Game data starts a this priority.
const int PRIORITY_DATA = 300;

const int LOG_FS = WzLog::Logger::instance().addLoggingLevel("fs", false);

// Static Functions definitions.
static void getPlatformUserDir(QString& result, const char* appSubDir);
static void addLoadedMod(QString modname);
static void printSearchPath();
static void addSubdirs(const QString& basedir, const char* subdir, const bool appendToPath, const QStringList& checkList, bool addToModList);
static void removeSubdirs(const QString& basedir, const char* subdir);
static void registerSearchPath(QString path, unsigned int priority);

void init(const char* binpath, const char* appSubDir, const QString& cmdUserdir)
{
    QString tmpdir;

    PHYSFS_Version compiled;
    PHYSFS_Version linked;

    PHYSFS_init(binpath);

    PHYSFS_VERSION(&compiled);
    PHYSFS_getLinkedVersion(&linked);

     wzLog(LOG_FS) << QString("Compiled against PhysFS version: %1.%2.%3")
         .arg(compiled.major).arg(linked.minor).arg(linked.patch);
     wzLog(LOG_FS) << QString("Linked against PhysFS version: %1.%2.%3")
         .arg(linked.major).arg(linked.minor).arg(linked.patch);
    if (linked.major < 2)
    {
        wzLog(WzLog::LOG_FATAL) << "At least version 2 of PhysicsFS required!";
        exit(-1);
    }

    PHYSFS_permitSymbolicLinks(1);

    if (cmdUserdir.isEmpty())
    {
        getPlatformUserDir(tmpdir, appSubDir);
        if (!QFile::exists(tmpdir) && !QDir().mkdir(tmpdir))
        {
            wzLog(WzLog::LOG_FATAL) << QString("Error creating user directory \"%1\"").arg(tmpdir);
            exit(1);
        }
    }
    else
    {
        tmpdir = cmdUserdir;
        if (!tmpdir.endsWith(PHYSFS_getDirSeparator()))
        {
            tmpdir.append(PHYSFS_getDirSeparator());
        }

        wzLog(LOG_FS) << QString("Using custom configuration directory: %1").arg(tmpdir);

        if (!QFile::exists(tmpdir) && !QDir().mkdir(tmpdir))
        {
            wzLog(WzLog::LOG_FATAL) << QString("Error creating custom user directory \"%1\"").arg(tmpdir);
        }
    }

    if (!PHYSFS_setWriteDir(tmpdir.toUtf8().constData()))
    {
        wzLog(WzLog::LOG_FATAL) << QString("Error setting write directory to \"%1\": %2")
            .arg(tmpdir).arg(PHYSFS_getLastError());
        exit(1);
    }
}

void scanDataDirs(const QString cmdDataDir, const QString fallbackDir)
{
    QString basedir(PHYSFS_getBaseDir());
    QString separator(PHYSFS_getDirSeparator());
    if (basedir.lastIndexOf(separator) != -1)
    {
        // Trim ending '/', which getBaseDir always provides
        basedir.chop(separator.length());

        if (basedir.lastIndexOf(separator) != -1)
        {
            // Now remove the last directory
            basedir.resize(basedir.lastIndexOf(separator));
        }
    }

#ifdef QT_OS_MAC
    // version-independent location for video files
    registerSearchPath("/Library/Application Support/Warzone 2100/", 1);
#endif

    // Commandline supplied datadir
    if (!cmdDataDir.isEmpty())
    {
        registerSearchPath(cmdDataDir, 2);
    }

    // User's home dir
    registerSearchPath(PHYSFS_getWriteDir(), 3);

    // Data in source tree
    registerSearchPath(basedir + "/data/", PRIORITY_DATA);
    rebuildSearchPath(mod_multiplay, true);

    if ( !PHYSFS_exists("gamedesc.lev") )
    {
        // Relocation for AutoPackage
        registerSearchPath(basedir + "/share/warzone2100/", PRIORITY_DATA);
        rebuildSearchPath(mod_multiplay, true);

        if ( !PHYSFS_exists("gamedesc.lev") )
        {
            // Program dir
            registerSearchPath(PHYSFS_getBaseDir(), PRIORITY_DATA);
            rebuildSearchPath(mod_multiplay, true);

            if (!PHYSFS_exists("gamedesc.lev"))
            {
                // Guessed fallback default datadir on Unix
                registerSearchPath(fallbackDir, PRIORITY_DATA);
                rebuildSearchPath(mod_multiplay, true);
            }
        }
    }

#ifdef QT_OS_MAC
    if ( !PHYSFS_exists("gamedesc.lev") )
    {
        CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
        char resourcePath[PATH_MAX];
        if (CFURLGetFileSystemRepresentation( resourceURL, true,
                                               (UInt8 *) resourcePath,
                                               PATH_MAX))
        {
            chdir(resourcePath);
            registerSearchPath("data", 100);
            rebuildSearchPath(mod_multiplay, true);
        }
        else
        {
            wzLog(WzLog::LOG_ERROR) << "Could not change to resources directory.";
        }

        if (resourceURL != NULL)
        {
            CFRelease(resourceURL);
        }
    }
#endif

    /** Debugging and sanity checks **/

    printSearchPath();

    if (PHYSFS_exists("gamedesc.lev"))
    {
        wzLog(LOG_FS) << QString("gamedesc.lev found at %1").arg(PHYSFS_getRealDir("gamedesc.lev"));
    }
    else
    {
        wzLog(WzLog::LOG_FATAL) << "Could not find game data. Aborting.";
        exit(1);
    }
}

static void getPlatformUserDir(QString& result, const char* appSubDir)
{
#ifdef QT_OS_WIN
    wchar_t tmpWStr[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW( NULL, CSIDL_PERSONAL|CSIDL_FLAG_CREATE, NULL, SHGFP_TYPE_CURRENT, tmpWStr)))
    {
        result = QString::fromUtf16(tmpWStr);
    }
    else
#elifdef QT_OS_MAC
    FSRef fsref;
    OSErr error = FSFindFolder(kUserDomain, kApplicationSupportFolderType, false, &fsref);
    if (!error)
    {
        error = FSRefMakePath(&fsref, (UInt8 *) tmpstr, size);
    }
    if (!error)
    {
        result = QString(fsref);
    }
    else
#endif
    if (PHYSFS_getUserDir())
    {
        result = QString(PHYSFS_getUserDir());
    }
    else
    {
        result = QCoreApplication::instance()->applicationDirPath();
    }

    result.append(appSubDir).append(PHYSFS_getDirSeparator());
}

static void addLoadedMod(QString modname)
{
    if (modname.endsWith(".wz"))
    {
        modname.chop(3);
    }

    if (modname.endsWith(".cam") || modname.endsWith(".mod"))
    {
        modname.chop(4);
    }
    else if (modname.endsWith(".gmod"))
    {
        modname.chop(5);
    }

    if (!loaded_mods.contains(modname))
    {
        loaded_mods.append(modname);
    }
}

void clearOverrides()
{
    use_override_mods = false;
    override_mods.clear();

    use_override_map = false;
    override_map.clear();
}

static void printSearchPath()
{
    char ** i, ** searchPath;

    wzLog(LOG_FS) << QString("Search paths:");
    searchPath = PHYSFS_getSearchPath();
    for (i = searchPath; *i != NULL; i++)
    {
        wzLog(LOG_FS) << QString("    [%1]").arg(*i);
    }
    PHYSFS_freeList(searchPath);
}

/**
 * @brief Tries to mount a list of directories, found in /basedir/subdir/<list>.
 *
 * @param basedir Base directory
 * @param subdir A subdirectory of basedir
 * @param appendToPath Whether to append or prepend
 * @param checkList List of directories to check.
 * @param addToModList Add found mods to the modlist?
 */
static void addSubdirs(const QString& basedir, const char* subdir, const bool appendToPath, const QStringList& checkList, bool addToModList)
{
    //char buf[256];
    char** subdirlist = PHYSFS_enumerateFiles(subdir);
    char** i = subdirlist;

    while (*i != NULL)
    {
#ifdef DEBUG
        wzLog(WzLog::LOG_NEVER) << QString("Examining subdir: [%1]").arg(*i);
#endif // DEBUG
        if (*i[0] != '.' && (checkList.isEmpty() || checkList.contains(*i)))
        {
            QString tmpstr = QString("%1%2%3%4").arg(basedir).arg(subdir).arg(PHYSFS_getDirSeparator()).arg(*i);
#ifdef DEBUG
            wzLog(WzLog::LOG_NEVER) << QString("Adding [%1] to search path").arg(tmpstr);
#endif // DEBUG

            if (addToModList)
            {
                addLoadedMod(*i);
                //snprintf(buf, sizeof(buf), "mod: %s", *i);
                //addDumpInfo(buf);
            }

            PHYSFS_addToSearchPath(tmpstr.toUtf8().constData(), appendToPath);
        }
        i++;
    }
    PHYSFS_freeList(subdirlist);
}

static void removeSubdirs(const QString& basedir, const char* subdir)
{
    char ** subdirlist = PHYSFS_enumerateFiles(subdir);
    char ** i = subdirlist;

    while (*i != NULL)
    {
        QString tmpstr = QString("%1%2%3%4").arg(basedir).arg(subdir).arg(PHYSFS_getDirSeparator()).arg(*i);

        #ifdef DEBUG
            wzLog(WzLog::LOG_NEVER) << QString("Removing [%1] from search path").arg(tmpstr);
        #endif

        if (!PHYSFS_removeFromSearchPath(tmpstr.toUtf8().constData()))
        {
            #ifdef DEBUG    // spams a ton!
                wzLog(WzLog::LOG_NEVER) << QString("Couldn't remove %1 from search path because %2").arg(tmpstr).arg(PHYSFS_getLastError());
            #endif
        }

        i++;
    }
    PHYSFS_freeList(subdirlist);
}

bool rebuildSearchPath( searchPathMode mode, bool force)
{
    static searchPathMode current_mode = mod_clean;
    QString tmpstr;

    if (mode != current_mode || force ||
            (use_override_mods && override_mods != loaded_mods) || use_override_map)
    {
        if (mode != mod_clean)
        {
            rebuildSearchPath(mod_clean, false);
        }

        current_mode = mode;

        // Clear mods as we detect them now (again).
        mod_list.clear();
        loaded_mods.clear();

        switch ( mode )
        {
        case mod_clean:
            wzLog(LOG_FS) << QString("Cleaning up");

            foreach(QString path, searchPathRegistry)
            {
                #ifdef DEBUG
                    wzLog(LOG_FS) << QString("Removing [%1] from search path").arg(path);
                #endif

                // Remove maps and mods
                removeSubdirs(path, "maps");
                removeSubdirs(path, "mods/music");
                removeSubdirs(path, "mods/global");
                removeSubdirs(path, "mods/campaign");
                removeSubdirs(path, "mods/multiplay");
                removeSubdirs(path, "mods/autoload");

                // Remove multiplay patches
                tmpstr = path;
                tmpstr += "mp";
                PHYSFS_removeFromSearchPath(tmpstr.toUtf8().constData());
                tmpstr = path;
                tmpstr += "mp.wz";
                PHYSFS_removeFromSearchPath(tmpstr.toUtf8().constData());

                // Remove plain dir
                PHYSFS_removeFromSearchPath(path.toUtf8().constData());

                // Remove base files
                tmpstr = path;
                tmpstr += "base";
                PHYSFS_removeFromSearchPath(tmpstr.toUtf8().constData());
                tmpstr = path;
                tmpstr += "base.wz";
                PHYSFS_removeFromSearchPath(tmpstr.toUtf8().constData());

                // remove video search path as well
                tmpstr = path;
                tmpstr += "sequences.wz";
                PHYSFS_removeFromSearchPath(tmpstr.toUtf8().constData());
            } // foreach(QString path, searchPathRegistry)
            break;
        case mod_campaign:
            wzLog(LOG_FS) << "*** Switching to campaign mods ***";

            // Find and add sequences.wz first
            foreach(QString path, searchPathRegistry)
            {
                tmpstr = path;
                tmpstr += "sequences.wz";
                PHYSFS_addToSearchPath(tmpstr.toUtf8().constData(), PHYSFS_APPEND);
            }

            foreach(QString path, searchPathRegistry)
            {
                #ifdef DEBUG
                    wzLog(LOG_FS) << QString("Adding [%1] to search path").arg(path);
                #endif

                // Add global and campaign mods
                PHYSFS_addToSearchPath(path.toUtf8().constData(), PHYSFS_APPEND);
                addSubdirs(path, "mods/music", PHYSFS_APPEND, QStringList(), false );
                addSubdirs(path, "mods/global", PHYSFS_APPEND, use_override_mods?override_mods:global_mods, true );
                addSubdirs(path, "mods", PHYSFS_APPEND, use_override_mods?override_mods:global_mods, true );
                addSubdirs(path, "mods/autoload", PHYSFS_APPEND, use_override_mods?override_mods:QStringList(), true );
                addSubdirs(path, "mods/campaign", PHYSFS_APPEND, use_override_mods?override_mods:campaign_mods, true );
                if (!PHYSFS_removeFromSearchPath(path.toUtf8().constData()))
                {
                    wzLog(LOG_FS) << QString("* Failed to remove path %1 again").arg(path);
                }

                // Add plain dir
                // PHYSFS_addToSearchPath(path.toUtf8().constData(), PHYSFS_APPEND );

                // Add base files
                tmpstr = path;
                tmpstr += "base";
                if (PHYSFS_mount(tmpstr.toUtf8().constData(), NULL, PHYSFS_APPEND) == 0)
                {
                    tmpstr = path;
                    tmpstr += "base.wz";
                    PHYSFS_mount(tmpstr.toUtf8().constData(), NULL, PHYSFS_APPEND);
                }
            }
            break;
        case mod_multiplay:
            wzLog(LOG_FS) << "*** Switching to multiplay mods ***";

            // Find and add sequences.wz first
            foreach(QString path, searchPathRegistry)
            {
                tmpstr = path;
                tmpstr += "sequences.wz";
                PHYSFS_addToSearchPath(tmpstr.toUtf8().constData(), PHYSFS_APPEND);
            }

            foreach(QString path, searchPathRegistry)
            {
                #ifdef DEBUG
                    wzLog(LOG_FS) << QString("Adding [%1] to search path").arg(path);
                #endif

                // Add maps and global and multiplay mods
                PHYSFS_addToSearchPath(path.toUtf8().constData(), PHYSFS_APPEND);
                addSubdirs(path, "maps", PHYSFS_APPEND, use_override_map?override_map:QStringList(), false);
                addSubdirs(path, "mods/music", PHYSFS_APPEND, QStringList(), false);
                addSubdirs(path, "mods/global", PHYSFS_APPEND, use_override_mods?override_mods:global_mods, true);
                addSubdirs(path, "mods", PHYSFS_APPEND, use_override_mods?override_mods:global_mods, true);
                addSubdirs(path, "mods/autoload", PHYSFS_APPEND, use_override_mods?override_mods:QStringList(), true);
                addSubdirs(path, "mods/multiplay", PHYSFS_APPEND, use_override_mods?override_mods:multiplay_mods, true);
                if (!PHYSFS_removeFromSearchPath(path.toUtf8().constData()))
                {
                    wzLog(LOG_FS) << QString("* Failed to remove path %1 again").arg(path);
                }

                // Add multiplay patches
                tmpstr = path;
                tmpstr += "mp";
                if (PHYSFS_mount(tmpstr.toUtf8().constData(), NULL, PHYSFS_APPEND) == 0)
                {
                    tmpstr = path;
                    tmpstr += "mp.wz";
                    PHYSFS_mount(tmpstr.toUtf8().constData(), NULL, PHYSFS_APPEND);
                }

                // Add plain dir
                // PHYSFS_mount(path.toUtf8().constData(), NULL, PHYSFS_APPEND);

                // Add base files
                tmpstr = path;
                tmpstr += "base";
                if (PHYSFS_mount(tmpstr.toUtf8().constData(), NULL, PHYSFS_APPEND) == 0)
                {
                    tmpstr = path;
                    tmpstr += "base.wz";
                    PHYSFS_mount(tmpstr.toUtf8().constData(), NULL, PHYSFS_APPEND);
                }
            }
            break;
        default:
            wzLog(WzLog::LOG_ERROR) << QString("Can't switch to unknown mods %1").arg(mode);
            return false;
        }

        if ((use_override_mods || use_override_map) && mode != mod_clean)
        {
            if (use_override_mods && override_mods != loaded_mods)
            {
                wzLog(WzLog::LOG_POPUP) << QString().sprintf("The required mod could not be loaded: %s\n\nWarzone will try to load the game without it.", override_mods.join(", ").toUtf8().constData());
            }
            clearOverrides();
            current_mode = mod_override;
        }

        // User's home dir must be first so we allways see what we write
        PHYSFS_removeFromSearchPath(PHYSFS_getWriteDir());
        PHYSFS_addToSearchPath(PHYSFS_getWriteDir(), PHYSFS_PREPEND);

#ifdef DEBUG
        printSearchPath();
#endif // DEBUG
    }
    else if (use_override_mods)
    {
        // override mods are already the same as current mods, so no need to do anything
        clearOverrides();
    }
    return true;
}

/*!
 * Register searchPath above the path with next lower priority
 * For information about what can be a search path, refer to PhysFS documentation
 */
static void registerSearchPath(QString path, unsigned int priority)
{
    if (!path.endsWith(PHYSFS_getDirSeparator()))
    {
        path += PHYSFS_getDirSeparator();
    }

    wzLog(LOG_FS) << QString("Registering %1 at priority %2").arg(path).arg(priority);

    // Just insert if the registry is empty.
    if (searchPathRegistry.isEmpty())
    {
        searchPathRegistry.insert(priority, path);
        return;
    }

    // Insert if the priority does not exists.
    if (!searchPathRegistry.contains(priority))
    {
        searchPathRegistry.insert(priority, path);
        return;
    }

    // Increase the priority if it exists
    priority++;
    while (searchPathRegistry.contains(priority))
    {
        priority++;
    }
    // And finally insert it.
    searchPathRegistry.insert(priority, path);
    return;
}

/**
 * Splits the given string by ", " and adds the result to the
 * override_mods list.
 */
void setOverrideMods(const QString& modlist)
{
   override_mods.append(modlist.split(", "));
   use_override_mods = true;
}

QString& getModList()
{
    if (!mod_list.isEmpty())
    {
        return mod_list;
    }

    mod_list = loaded_mods.join(", ");
    return mod_list;
}

// QVariantMap& getMPMaps(bool rebuild = false)
// {
//     if (!mapList.isEmpty() && !rebuild)
//     {
//         return mapList;
//     }
//
//     mapList.clear();
//     rebuildSearchPath(mod_clean);
//
//     foreach(QString path, searchPathRegistry)
//     {
//         PHYSFS_mount(path.toUtf8().constData(), NULL, PHYSFS_APPEND);
//         addSubdirs(path, "maps", PHYSFS_APPEND, QStringList(), false);
//         if (!PHYSFS_removeFromSearchPath(path.toUtf8().constData()))
//         {
//             wzLog(LOG_FS) << QString("* Failed to remove path %1 again").arg(path);
//         }
//     }
// }
//
// bool addMapToSearchPath(QString& map)
// {
//     Transform "Sk-Rush-T2" into "4c-Rush.wz" so it can be matched by the map loader
//     if (map.startsWith("Sk-"))
//     {
//         map.remove(0, 3);
//     }
//
//     Remove -T1|-T2|-T3
//     if (map.right(3).left(2) == "-T")
//     {
//         map.chop(3);
//     }
//
//     map.prepend("%1c-").arg(maxPlayers);
//     map.append(".wz");
// }
//
// void removeMapFromSearchPath()
// {
//
// }


} // namespace FileSystem {