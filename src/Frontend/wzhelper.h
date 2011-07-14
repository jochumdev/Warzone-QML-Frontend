#ifndef FRONTEND_WZHELPER_H
#define FRONTEND_WZHELPER_H

#include "QtCore"

namespace Frontend
{

class WzHelper : public QObject
{
    Q_OBJECT
public:
    WzHelper(const QString &configfile);

    Q_INVOKABLE void log(const QString& message);

    Q_INVOKABLE QString tr(const QString&, const QString& domain = QString());
    Q_INVOKABLE QString tr(const QString& singular, const QString& plural, int n, const QString& domain = QString());

    Q_INVOKABLE QVariantMap getMapList(int techLevel);
    Q_INVOKABLE void loadMap(const QString &path);

    Q_INVOKABLE void setConfigValue(const QString&, const QVariant&);
    Q_INVOKABLE const QVariant getConfigValue(const QString&);

private:
    QSettings *m_settings;
};

} // namespace Frontend


#endif // FRONTEND_WZHELPER_H