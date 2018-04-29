IF("${CMAKE_BUILD_TYPE}" MATCHES "^Debug")
ADD_DEFINITIONS("-DIMAGEMAP_DEBUG")
ENDIF("${CMAKE_BUILD_TYPE}" MATCHES "^Debug")

SET(imagemap_INCLUDES ${QJSON_INCLUDE_DIR})
SET(imagemap_SOURCES "containerimage.cpp"
                     "containersvg.cpp"
                     "container.cpp"
                     "loader.cpp"
                     "map.cpp")

SET(imagemap_LIBRARIES ${Qt5Svg_LIBRARIES})

INCLUDE_DIRECTORIES("../"
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Svg_INCLUDE_DIRS})
ADD_LIBRARY(imagemap STATIC ${imagemap_SOURCES})
