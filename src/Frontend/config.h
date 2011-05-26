#ifndef CORE_CONFIG_H
#define CORE_CONFIG_H

#include "QtCore"

class Config : public QObject
{
    Q_OBJECT
public:
    Config(const QString &configfile);

    Q_INVOKABLE void setValue(const QString &name, const QVariant &value);
    Q_INVOKABLE const QVariant getValue(const QString &name);

private:
    QSettings *m_settings;
};

#endif // CORE_CONFIG_H