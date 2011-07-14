// Self
#include <Core/Map/map.h>
#include <Core/Map/levparser.h>

// Logging
#include <lib/WzLog/Log.h>

// Filesystem
#include <Core/Filesystem/filesystem.h>

namespace Map {

const int LOG_MAP = WzLog::Logger::instance().addLoggingLevel("map", false);

static QVariantMap mlCampaignT1;
static QVariantMap mlCampaignT2;
static QVariantMap mlCampaignT3;
static QVariantMap mlSkirmishT1;
static QVariantMap mlSkirmishT2;
static QVariantMap mlSkirmishT3;

// Do we already have a map loaded?
static bool mapLoaded = false;

/**
 * @brief Removes the prepending "Sk-" and leading "-TX" from a mapname.
 *
 * @param in    Mapname to shorten.
 *
 * @return      result.
 */
static inline QString shortenMapname(const QString &in)
{
    QString out = in;

     // Remove "Sk-"
    if (out.startsWith("Sk-"))
    {
        out.remove(0, 3);
    }

     // Remove -T1|-T2|-T3
     if (out.right(3).left(2) == "-T")
     {
         out.chop(3);
     }

     return out;
}

/**
 * @brief Tries to find all map in the physfs searchpath and parses them.
 *
 * This loads gamedesc.lev and addon.lev first,
 * then it loads all zipped maps and parses all found .lev files.
 *
 * After that it inserts the maps into the accordings lists
 * (mlCampaign* and mlSkirmish*).
 */
static void buildMapList()
{
    char **filelist, **file;
    QString filePath;
    LevParser levParser;

    filePath = QString("wz::%1").arg("gamedesc.lev");
    levParser.parse(filePath, "");

    filePath = QString("wz::%1").arg("addon.lev");
    levParser.parse(filePath, "");

    // Load all maps into the searchpath.
    FileSystem::loadMaps();

    filelist = PHYSFS_enumerateFiles("");
    for (file = filelist; *file != NULL; ++file)
    {
        filePath = *file;

        if (filePath.endsWith(".addon.lev") || filePath.endsWith(".xplayers.lev"))
        {
            filePath = QString("wz::%1").arg(filePath);
            levParser.parse(filePath, PHYSFS_getRealDir(*file));
        }
    }
    PHYSFS_freeList(filelist);

    // Unload maps
    FileSystem::unloadMaps();

    QMapIterator<QString, MapData> i(levParser.maps);
    while (i.hasNext())
    {
        i.next();
        MapData map = i.value();

        QVariantMap data;
        data.insert("name", i.key()); // Full name of map.
        data.insert("players", map.players); // Max players.
        data.insert("path", map.path); // Filepath for physfs

        switch(static_cast<GAMETYPES>(map.type))
        {
            case GAMETYPE_CAMPAIGN_T1:
                mlCampaignT1.insert(shortenMapname(i.key()), data);
            break;
            case GAMETYPE_CAMPAIGN_T2:
                mlCampaignT2.insert(shortenMapname(i.key()), data);
            break;
            case GAMETYPE_CAMPAIGN_T3:
                mlCampaignT3.insert(shortenMapname(i.key()), data);
            break;
            case GAMETYPE_SKIRMISH_T1:
                mlSkirmishT1.insert(shortenMapname(i.key()), data);
            break;
            case GAMETYPE_SKIRMISH_T2:
                mlSkirmishT1.insert(shortenMapname(i.key()), data);
            break;
            case GAMETYPE_SKIRMISH_T3:
                mlSkirmishT1.insert(shortenMapname(i.key()), data);
            break;
            default:
                wzLog(WzLog::LOG_INFO) << QString("Unknown gameType %1 in %2, map %3")
                                            .arg(map.type).arg(map.file).arg(i.key());
        }
    }
}

QVariantMap& getList(GAMETYPES gameType)
{
    if (mlCampaignT1.isEmpty())
    {
        buildMapList();
    }

    switch(gameType)
    {
        case GAMETYPE_CAMPAIGN_T1:
            return mlCampaignT1;
        break;
        case GAMETYPE_CAMPAIGN_T2:
            return mlCampaignT2;
        break;
        case GAMETYPE_CAMPAIGN_T3:
            return mlCampaignT3;
        break;
        case GAMETYPE_SKIRMISH_T1:
            return mlSkirmishT1;
        break;
        case GAMETYPE_SKIRMISH_T2:
            return mlSkirmishT1;
        break;
        case GAMETYPE_SKIRMISH_T3:
            return mlSkirmishT1;
        break;
        default:
            wzLog(WzLog::LOG_ERROR) << QString("Unknown gameType %1").arg(gameType);
            return mlSkirmishT1;
    }

    return mlSkirmishT1;
}

void loadMap(const QString& path)
{
    if (path.isEmpty())
    {
        return;
    }

    if (mapLoaded)
    {
        FileSystem::unloadMaps();
    }

    FileSystem::loadMap(path.toUtf8().constData());

    mapLoaded = true;
}

} // namespace Map {