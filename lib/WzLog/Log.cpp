#include "Log.h"

#include "QtCore/QStringList"

namespace WzLog {

void init(const QStringList* logLevels)
{
    // Create the logger instance and get a reference to it.
    Logger& logger = Logger::instance();
    logger.setLevelStatus(LOG_TRACE);
    Destination* debugDestination = new DebugOutputDestination();
    logger.addDestination(debugDestination);

    if (logLevels != 0)
    {
        // Add and enable the given levels.
        for (int i=0;i<logLevels->count(); i++)
        {
            logger.addLoggingLevel(logLevels->at(i).toUtf8().constData(), true);
        }
    }
}

} // namespace WzLog {