IF("${CMAKE_BUILD_TYPE}" MATCHES "^Debug")
ADD_DEFINITIONS("-DIMAGEMAP_DEBUG")
ENDIF("${CMAKE_BUILD_TYPE}" MATCHES "^Debug")

find_package(QJSON REQUIRED)

SET(imagemap_INCLUDES ${QJSON_INCLUDE_DIR})
SET(imagemap_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/lib/Imagemap/containerimage.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/lib/Imagemap/containersvg.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/lib/Imagemap/container.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/lib/Imagemap/loader.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/lib/Imagemap/map.cpp")

SET(imagemap_LIBRARIES ${QT_QTSVG_LIBRARY}
                       ${QJSON_LIBRARIES})