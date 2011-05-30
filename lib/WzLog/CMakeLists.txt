SET(wzlog_SOURCES "LoggerDest.cpp"
                  "Logger.cpp"
                  "Log.cpp")

SET(wzlog_LIBRARIES ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

ADD_LIBRARY(wzlog STATIC ${wzlog_SOURCES})