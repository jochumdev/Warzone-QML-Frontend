SET(wzlog_SOURCES "Logger.cpp"
                  "LoggerDest.cpp")

SET(wzlog_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES})

INCLUDE_DIRECTORIES(${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Widgets_INCLUDE_DIRS})
ADD_LIBRARY(wzlog STATIC ${wzlog_SOURCES})
