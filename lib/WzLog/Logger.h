// Copyright (c) 2010, Razvan Petru
// Copyright (C) 2011, Jochum Rene
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

#ifndef WZLOG_LOGGER_H
#define WZLOG_LOGGER_H

#include <QtCore/QString>
#include <QtCore/QtDebug>

// This MUST be in the same order as in the LoggerImpl initalizer!
enum LEVELS {
    LOG_ALL = 0,        // Will automaticaly enable levels higher than this.
    LOG_TRACE,          // -""-, but not custom levels.
    LOG_DEBUG,          // -""-
    LOG_INFO,           // -""-, enabled by default.
    LOG_WARN,           // -""-, enabled by default.
    LOG_ERROR,          // -""-, enabled by default.
    LOG_FATAL,          // -""-, enabled by default.
    LOG_NEVER,          // Special: Needs to be last for setLevelStatus.
    LOG_POPUP           // Special: Shows a popup window
};

namespace WzLog {

class Destination;

class LoggerImpl; // d pointer
class Logger
{
public:
   static Logger& instance()
   {
      static Logger staticLog;
      return staticLog;
   }

    //! Adds a log message destination. Don't add null destinations.
    void addDestination(Destination* destination);
    //! Dynamicaly add another level.
    int addLoggingLevel(const QString& name, bool status = false);
    //! Return the identifier of a level
    int getLoggingLevel(const QString& name);

    //! Enable/disable logging for this level.
    void setLevelStatus(int level, bool status = false);
    void setLevelStatus(const QString& name, bool status = false);

    //! Returns if the given level is enabled
    bool checkLevel(int level);

    //! Enable/disable the input buffer
    void setInputBuffer(bool state);

    //! The helper forwards the streaming to QDebug and builds the final
    //! log message.
    class Helper
    {
    public:
        explicit Helper(int logLevel, const char* callerFunc) :
            level(logLevel),
            function(callerFunc),
            qtDebug(&buffer) {}
        ~Helper();
        QDebug& stream(){ return qtDebug; }
        void sprintf(const char* cformat, ...);

    private:
        void writeToLog();

        int level;
        QString function;
        int line;
        QString buffer;
        QDebug qtDebug;
    };

private:
   Logger();
   Logger(const Logger&);
   Logger& operator=(const Logger&);
   ~Logger();

   void write(const QString &level, const QString &function, const QString &message);

   LoggerImpl* d;
}; // class Logger

} // namespace WzLog {

#endif // WZLOG_LOGGER_H
