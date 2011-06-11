// Copyright (c) 2010, Razvan Petru
// Copyright (c) 2011, Rene Jochum
// All rights reserved.

// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice, this
//   list of conditions and the following disclaimer in the documentation and/or other
//   materials provided with the distribution.
// * The name of the contributors may not be used to endorse or promote products
//   derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.

#include "Logger.h"
#include "LoggerDest.h"

// QT
#include <QtCore/QtGlobal>
#include <QtCore/QMutex>
#include <QtCore/QList>
#include <QtCore/QDateTime>
#include <QtCore/QStringList>
#include <QtCore/QDebug>

// LOG_POUP
#include <QtGui/QMessageBox>

// stdlib
#include <cassert>
#include <cstdlib>
#include <stdexcept>

namespace WzLog {

typedef QList<Destination*> DestinationList;

static const QString fmtDateTime("hh:mm:ss");

class LoggerImpl
{
public:
    LoggerImpl()
    {
        // This MUST be in the same order as the Levels Enum!
        levelNames.append("ALL");
        levelStatus.append(false);

        levelNames.append("TRACE");
        levelStatus.append(false);

        levelNames.append("DEBUG");
        levelStatus.append(false);

        levelNames.append("INFO");
        levelStatus.append(true);

        levelNames.append("WARN");
        levelStatus.append(true);

        levelNames.append("ERROR");
        levelStatus.append(true);

        levelNames.append("FATAL");
        levelStatus.append(true);

        // Last of "levels" for setLevelStatus
        levelNames.append("NEVER");
        levelStatus.append(false);

        levelNames.append("POPUP");
        levelStatus.append(true);
    }

    int addLoggingLevel(const QString& name, bool status)
    {
        if (levelNames.contains(name))
        {
            int index = levelNames.indexOf(name);
            levelStatus[index] = status;
            return index;
        }

        QMutexLocker lock(&logMutex);
        levelNames.append(name);
        levelStatus.append(levelStatus.at(LOG_ALL) ? true : status);

        return levelNames.indexOf(name);
    }

    QMutex             logMutex;
    QStringList        levelNames;
    QList<bool>        levelStatus;
    DestinationList    destList;
};

Logger::Logger() :
    d(new LoggerImpl)
{
}

Logger::~Logger()
{
    delete d;
}

void Logger::addDestination(Destination* destination)
{
    assert(destination);
    d->destList.push_back(destination);
}

int Logger::addLoggingLevel(const QString& name, bool status)
{
    return d->addLoggingLevel(name, status);
}

int Logger::getLoggingLevel(const QString& name)
{
    return d->levelNames.indexOf(name);
}

void Logger::setLevelStatus(const QString& name, bool status)
{
    int level = getLoggingLevel(name);
    if (level == -1) {
        return;
    }

    setLevelStatus(level, status);
}

void Logger::setLevelStatus(int level, bool status)
{
    assert(d->levelStatus.size() >= level);

    QMutexLocker lock(&d->logMutex);

    if (level == LOG_ALL)
    {
        for (int i=0; i < d->levelStatus.size(); i++)
        {
            d->levelStatus[i] = true;
        }

        return;
    }
    else if (level < LOG_NEVER)
    {
        for (int i=level; i < LOG_NEVER; i++)
        {
            d->levelStatus[i] = true;
        }

        return;
    }

    d->levelStatus[level] = status;
}

bool Logger::checkLevel(int level)
{
    if (d->levelStatus.size() <= level)
    {
        assert(d->levelStatus.size() <= level);
        return false;
    }
    return d->levelStatus[level];
}

void Logger::Helper::sprintf(const char* cformat, ...)
{
    va_list ap;

    va_start(ap, cformat);
        buffer.vsprintf(cformat, ap);
    va_end(ap);
}

//! creates the complete log message and passes it to the logger
void Logger::Helper::writeToLog()
{
    Logger& logger = Logger::instance();

    // Remove quotes, FIXME: There should be a better way to do this.
    if (buffer.startsWith("\"") && buffer.endsWith("\" "))
    {
        buffer.remove(0, 1).chop(2);
    }

    const QString completeMessage(QString("%1 |%2: %3 %4")
        .arg(logger.d->levelNames.at(level), -8)
        .arg(QDateTime::currentDateTime().toString(fmtDateTime))
        .arg(QString("[%1]").arg(function), -20)
        .arg(buffer)
    );

    if (level == LOG_POPUP)
    {
        QMessageBox msgBox(
            QMessageBox::Warning,
            "Warzone has detected a problem.",
            QString("A non fatal error has occurred.\n\n%1\n\n").arg(buffer)
        );
        msgBox.exec();
    }

    QMutexLocker lock(&logger.d->logMutex);
    logger.write(completeMessage);
}

Logger::Helper::~Helper()
{
    try
    {
        writeToLog();
    }
    catch(std::exception& e)
    {
        // you shouldn't throw exceptions from a sink
        Q_UNUSED(e);
        assert(!"exception in logger helper destructor!");
        throw;
    }
}

//! sends the message to all the destinations
void Logger::write(const QString& message)
{
    foreach(Destination* d, d->destList)
    {
        if (!d)
        {
            assert(!"null log destination");
            continue;
        }

        d->write(message);
    }
}

} // namespace WzLog {