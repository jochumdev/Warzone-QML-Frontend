SET(wzlog_SOURCES "Logger.cpp"
                  "LoggerDest.cpp")

SET(wzlog_LIBRARIES ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

ADD_LIBRARY(wzlog STATIC ${wzlog_SOURCES})