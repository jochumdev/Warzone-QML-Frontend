#ifndef WZLOG_LOG_H
#define WZLOG_LOG_H

#include "Logger.h"
#include "LoggerDest.h"

#include <QtCore/QStringList>

namespace WzLog {

void init(const QStringList* logLevels = 0);

} // namespace WzLog {

#define debug(level, cformat, ...) \
  if (!WzLog::Logger::instance().checkLevel(level)){} \
  else WzLog::Logger::Helper(level, __func__).sprintf(cformat, __VA_ARGS__)

#define wzLog(level) \
   if (!WzLog::Logger::instance().checkLevel(level)){} \
   else WzLog::Logger::Helper(level, __func__).stream()

#endif // WZLOG_LOG_H