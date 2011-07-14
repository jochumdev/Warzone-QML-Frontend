// Qt Core
#include <QtCore/QHash>
#include <QtCore/QRegExp>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QFileInfo>

// Self
#include <Core/Map/levparser.h>

// Logging
#include <lib/WzLog/Log.h>

// For LOG_MAP
#include <Core/Map/map.h>

namespace Map {

enum LevelIdentType
{
    IDENT_TYPE_DATASET = 1,
    IDENT_TYPE_LEVEL,
};

enum LevelType
{
    LEVEL_PLAYERS = 1,
    LEVEL_TYPE,
    LEVEL_DATASET,
    LEVEL_GAME,
    LEVEL_DATA
};

static QHash<QString, int> levelIdentTokens;
static QHash<QString, int> levelTypeTokens;
static QString datasetDataKey = "data";

static QRegExp levelRx("([a-z]+)\\s*\"?([\\w-_/.]+)\"?");

inline QStringList readLevLine(QIODevice* io)
{
    char buff[1024];

    io->readLine(buff, sizeof(buff));
    QString line = QString::fromUtf8(buff);
    //Skip empty lines and comments
    if (line.isEmpty() ||
        line.at(0) == QChar('\n') ||
        line.at(0) == QChar('/') ||
        line.at(1) == QChar('*'))
    {
        return QStringList();
    }

    int pos = levelRx.indexIn(line);
    if (pos == -1)
    {
        return QStringList();
    }

    return levelRx.capturedTexts();
}

static qint64 parseDataset(QIODevice* io, QStringList& dataset, qint64 line)
{
    for (;;)
    {
        QStringList data = readLevLine(io);
        line++;

        if (data.isEmpty())
        {
            break;
        }

        if (data.at(1) == datasetDataKey)
        {
            dataset.append(data.at(2));
        }
        else
        {
            wzLog(WzLog::LOG_ERROR) << QString("Line %1, unknown dataset token: %2")
                                            .arg(line).arg(data.at(1));
            return -1;
        }
    }

    return line;
}

static qint64 parseLevel(QIODevice* io, MapData& level, qint64 line)
{
    for (;;)
    {
        QStringList data = readLevLine(io);
        line++;

        if (data.isEmpty())
        {
            break;
        }

        int tokenId = levelTypeTokens.value(data.at(1));
        switch((LevelType)tokenId)
        {
            case LEVEL_PLAYERS:
                level.players = data.at(2).toInt();
            break;
            case LEVEL_TYPE:
                level.type = data.at(2).toInt();
            break;
            case LEVEL_DATASET:
                level.dataset = data.at(2);
            break;
            case LEVEL_GAME:
                level.game = data.at(2);
            break;
            case LEVEL_DATA:
                level.dataFiles.append(data.at(2));
            break;
            default:
                wzLog(WzLog::LOG_ERROR) << QString("Line %1, unknown level token: %2")
                                                    .arg(line).arg(data.at(1));
        }
    }

    return line;
}

// FIXME: This should be static somewhere.
LevParser::LevParser()
{
    // Needs to be in exact the same order as the enum LevelIdentType
    if (levelIdentTokens.isEmpty())
    {
        levelIdentTokens.insert("campaign", 1);
        levelIdentTokens.insert("level", 2);
    }

    // Needs to be in exact the same order as the enum LevelType
    if (levelTypeTokens.isEmpty())
    {
        levelTypeTokens.insert("players", 1);
        levelTypeTokens.insert("type", 2);
        levelTypeTokens.insert("dataset", 3);
        levelTypeTokens.insert("game", 4);
        levelTypeTokens.insert("data", 5);
    }
}

bool LevParser::parse(QString &filename, const char* path)
{
    qint64 line = 0;

    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        // Failed to open file
        wzLog(WzLog::LOG_ERROR) << QString("Failed to open %1")
                                        .arg(filename);
        return false;
    }

    wzLog(LOG_MAP) << QString("Parsing %1").arg(filename);

    while (!file.atEnd())
    {
        QStringList data = readLevLine(&file);
        line++;

        if (data.isEmpty())
        {
            continue;
        }

        int tokenId = levelIdentTokens.value(data.at(1));
        if (tokenId == 0)
        {
            // Invalid Token received.
            continue;
        }

        QStringList dataset;
        MapData level;
        switch((LevelIdentType)tokenId)
        {
            case IDENT_TYPE_DATASET:
                line = parseDataset(&file, dataset, line);
                if (line == -1) {
                    return false;
                }
                datasets.insert(data.at(2), dataset);
            break;

            case IDENT_TYPE_LEVEL:
                line = parseLevel(&file, level, line);
                if (line == -1) {
                    return false;
                }
                level.path = path;
                level.file = QFileInfo(filename).fileName();

                maps.insert(data.at(2), level);
            break;
            default:
                qDebug() << QString("Line %1, unknown token: %2")
                                .arg(line).arg(data.at(1));
                return false;
        }
    }

    return true;
}

} // namespace Map {
