#include "wzhelper.h"

#include "QtCore/QVariant"
#include "QtCore/QString"
#include "QtCore/QSettings"

// libc
#include <libintl.h>

// WzLog
#include <lib/WzLog/Log.h>

// Map list
#include <Core/Map/map.h>

using namespace Frontend;

const int LOG_FRONTEND = WzLog::Logger::instance().addLoggingLevel("frontend", false);

/**
 * Ment to be removed when integrated into warzone.
 */
WzHelper::WzHelper(const QString &configfile)
{
    m_settings = new QSettings(configfile, QSettings::IniFormat);
    if (m_settings->status() != QSettings::NoError)
    {
        qFatal("Failed to read config file %s", configfile.toUtf8().constData());
    }
}

Q_INVOKABLE void WzHelper::log(const QString& message)
{
    wzLog(LOG_FRONTEND) << message;
}

Q_INVOKABLE QString WzHelper::tr(const QString& text, const QString &domain)
{
    if (domain.isNull())
    {
        return QString::fromUtf8(dgettext(NULL, text.toUtf8().constData()));
    }
    else
    {
        return QString::fromUtf8(dgettext(domain.toUtf8().constData(),
                                          text.toUtf8().constData()));
    }

}

Q_INVOKABLE QString WzHelper::tr(const QString& singular, const QString &plural, int n, const QString &domain)
{
    if (domain.isNull())
    {
        return QString::fromUtf8(dngettext(NULL,
                                 singular.toUtf8().constData(),
                                 plural.toUtf8().constData(), n));
    }
    else
    {
        return QString::fromUtf8(dngettext(domain.toUtf8().constData(),
                                           singular.toUtf8().constData(),
                                           plural.toUtf8().constData(), n));
    }
}

Q_INVOKABLE QVariantMap WzHelper::getMapList(int techLevel)
{
    switch (techLevel)
    {
        case 1:
            return Map::getList(Map::GAMETYPE_SKIRMISH_T1);
        break;
        case 2:
            return Map::getList(Map::GAMETYPE_SKIRMISH_T2);
        break;
        case 3:
            return Map::getList(Map::GAMETYPE_SKIRMISH_T3);
        break;
    }

    return Map::getList(Map::GAMETYPE_SKIRMISH_T1);
}

/**
 * This would normaly call one of the thousands setters Warzone has.
 */
Q_INVOKABLE void WzHelper::setConfigValue(const QString& name, const QVariant& value)
{
    wzLog(LOG_FRONTEND) << "Setting:" << name << "=" << value.toString();

    // START: Audio Options
    if (name == "voicevol")
    {
        m_settings->setValue(name, value.toInt());
    }
    else if (name == "fxvol")
    {
        m_settings->setValue(name, value.toInt());
    }
    else if (name == "cdvol")
    {
        m_settings->setValue(name, value.toInt());
    }

    // START: Graphics Options
    else if (name == "fullscreen")
    {
        m_settings->setValue(name, value.toBool());
    }
    else if (name == "resolution")
    {
        QStringList wh = value.toString().split(" x ");
        m_settings->setValue("width", wh[0].toInt());
        m_settings->setValue("height", wh[1].toInt());
    }
    else if (name == "textureSize")
    {
        m_settings->setValue(name, value.toInt());
    }
    else if (name == "vsync")
    {
        m_settings->setValue(name, value.toBool());
    }
    else if (name == "fsaa")
    {
        m_settings->setValue(name, value.toInt());
    }

    // START: Game Options
    else if (name == "difficulty")
    {
        m_settings->setValue(name, value.toInt());
    }
    else if (name == "scroll")
    {
        m_settings->setValue(name, value.toInt());
    }
    else if (name == "colour")
    {
        m_settings->setValue(name, value.toInt());
    }
    else if (name == "language")
    {
        m_settings->setValue(name, value);
    }
    else if (name == "rotateRadar")
    {
        m_settings->setValue(name, value.toBool());
    }

    // START: Video Options
    else if (name == "FMVmode")
    {
        m_settings->setValue(name, value.toInt());
    }
    else if (name == "scanlines")
    {
        m_settings->setValue(name, value.toBool());
    }
    else if (name == "shake")
    {
        m_settings->setValue(name, value.toBool());
    }
    else if (name == "visfog")
    {
        m_settings->setValue(name, value.toBool());
    }
    else if (name == "subtitles")
    {
        m_settings->setValue(name, value.toBool());
    }
    else if (name == "shadows")
    {
        m_settings->setValue(name, value.toBool());
    }

    // START: Mouse Options
    else if (name == "mouseflip")
    {
        m_settings->setValue(name, value.toBool());
    }
    else if (name == "trapCursor")
    {
        m_settings->setValue(name, value.toBool());
    }
    else if (name == "RightClickOrders")
    {
        m_settings->setValue(name, value.toBool());
    }
    else if (name == "MiddleClickRotate")
    {
        m_settings->setValue(name, value.toBool());
    }

    // START: Hostgame Screen
    else if (name == "gameName")
    {
        m_settings->setValue(name, value.toString());
    }
    else if (name == "mapName")
    {
        m_settings->setValue(name, value.toString());
    }
    else if (name == "maxPlayers")
    {
        m_settings->setValue(name, value.toInt());
    }
    else if (name == "power")
    {
        // 400 = Low, 700 = Medium, 1000 = High
        m_settings->setValue(name, value.toInt());
    }
    else if (name == "base")
    {
        // 0 = No, 1 = Medium, 2 = Full
        m_settings->setValue(name, value.toInt());
    }
    else if (name == "fog")
    {
        m_settings->setValue(name, value.toBool());
    }
    else if (name == "alliance")
    {
        // 0 = No, 1 = Yes, 2 = Fixed
        m_settings->setValue(name, value.toInt());
    }
    else if (name == "playerName")
    {
        m_settings->setValue(name, value.toString());
    }


    else
    {
        wzLog(WzLog::LOG_ERROR) << "Unknown config value" << name;
    }
}

/**
 * This would normaly call one of the thousands getters Warzone has.
 */
Q_INVOKABLE const QVariant WzHelper::getConfigValue(const QString& name)
{
    // START: Audio Options
    if (name == "voicevol")
    {
        return m_settings->value(name).toInt();
    }
    else if (name == "fxvol")
    {
        return m_settings->value(name).toInt();
    }
    else if (name == "cdvol")
    {
        return m_settings->value(name).toInt();
    }

    // START: Graphics Options
    else if (name == "fullscreen")
    {
        return m_settings->value(name).toBool();
    }
    else if (name == "resolution")
    {
        return QString("%1 x %2").arg(m_settings->value("width").toString()).arg(m_settings->value("height").toString());
    }
    else if (name == "textureSize")
    {
        return m_settings->value(name).toString();
    }
    else if (name == "vsync")
    {
        return m_settings->value(name).toBool();
    }
    else if (name == "fsaa")
    {
        return m_settings->value(name).toInt();
    }

    // START: Game Options
    else if (name == "difficulty")
    {
        return m_settings->value(name).toInt();
    }
    else if (name == "scroll")
    {
        return m_settings->value(name).toInt();
    }
    else if (name == "colour")
    {
        return m_settings->value(name).toInt();
    }
    else if (name == "language")
    {
        return m_settings->value(name);
    }
    else if (name == "rotateRadar")
    {
        return m_settings->value(name).toBool();
    }

    // START: Video Options
    else if (name == "FMVmode")
    {
        return m_settings->value(name).toInt();
    }
    else if (name == "scanlines")
    {
        return m_settings->value(name).toBool();
    }
    else if (name == "shake")
    {
        return m_settings->value(name).toBool();
    }
    else if (name == "visfog")
    {
        return m_settings->value(name).toBool();
    }
    else if (name == "subtitles")
    {
        return m_settings->value(name).toBool();
    }
    else if (name == "shadows")
    {
        return m_settings->value(name).toBool();
    }

    // START: Mouse Options
    else if (name == "mouseflip")
    {
         return m_settings->value(name).toBool();
    }
    else if (name == "trapCursor")
    {
         return m_settings->value(name).toBool();
    }
    else if (name == "RightClickOrders")
    {
         return m_settings->value(name).toBool();
    }
    else if (name == "MiddleClickRotate")
    {
         return m_settings->value(name).toBool();
    }

    // START: Hostgame Screen
    else if (name == "gameName")
    {
        return m_settings->value(name).toString();
    }
    else if (name == "mapName")
    {
        return m_settings->value(name).toString();
    }
    else if (name == "maxPlayers")
    {
        return m_settings->value(name).toInt();
    }
    else if (name == "power")
    {
        // 400 = Low, 700 = Medium, 1000 = High
        return m_settings->value(name).toInt();
    }
    else if (name == "base")
    {
        // 0 = No, 1 = Medium, 2 = Full
        return m_settings->value(name).toInt();
    }
    else if (name == "fog")
    {
        return m_settings->value(name).toBool();
    }
    else if (name == "alliance")
    {
        // 0 = No, 1 = Yes, 2 = Fixed
        return m_settings->value(name).toInt();
    }
    else if (name == "playerName")
    {
        return m_settings->value(name, "Player").toString();
    }

    else
    {
        wzLog(WzLog::LOG_ERROR) << "Unknown config value" << name;
        return 0;
    }
}