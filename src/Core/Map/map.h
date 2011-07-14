// Qt Core
#include <QtCore/QVariantMap>

namespace Map {


enum GAMETYPES {
    GAMETYPE_CAMPAIGN_T1 = 12,
    GAMETYPE_CAMPAIGN_T2 = 15,
    GAMETYPE_CAMPAIGN_T3 = 16,
    GAMETYPE_SKIRMISH_T1 = 14,
    GAMETYPE_SKIRMISH_T2 = 18,
    GAMETYPE_SKIRMISH_T3 = 19
};

extern const int LOG_MAP;

/**
 * @brief Returns a list of maps for the given GAMETYPE.
 *
 * Returns a QVariantMap with found maps, current format:
 *
 * [(string)<short-mapname>: {name: (string)<long-mapname>,
 *                            players: (int)<max-players>,
 *                            path: (string)<zip-file-path>
 *                           },
 * ]
 *
 * @param gameType          Gametype to retreive maps for.
 *
 * @return                  QVariantMap.
 */
QVariantMap& getList(GAMETYPES gameType = GAMETYPE_SKIRMISH_T1);

} // namespace Map {