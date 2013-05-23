find_package(PhysFS 2 REQUIRED)

find_path(WZ_BUILD_DIR config.h
        HINTS "${CMAKE_SOURCE_DIR}/../.."
        DOC "Path to directory containing the config.h file created by warzone's build configuration step")

file(GLOB_RECURSE qmlfrontendSources "*.c" "*.cpp")
file(GLOB_RECURSE qmlfrontendHeaders "*.h" "*.hpp")

SET(qmlfrontend_SRCS main.cpp ${qmlfrontendSources})

INCLUDE_DIRECTORIES(${QMLFRONTEND_INCLUDES} ${PHYSFS_INCLUDE_DIR} ${qtgame_INCLUDES})

QT4_WRAP_CPP(QMLFRONTEND_MOC_FILES ${qmlfrontendHeaders})

ADD_EXECUTABLE(viewer ${qmlfrontend_SRCS} ${QMLFRONTEND_MOC_FILES})
TARGET_LINK_LIBRARIES(viewer wzlog
                             imagemap
                             ${PHYSFS_LIBRARY}
                             ${QT_QTCORE_LIBRARY}
                             ${QT_QTGUI_LIBRARY}
                             ${QT_QTSVG_LIBRARY}
                             ${QT_QTDECLARATIVE_LIBRARY}
                             ${QT_QTNETWORK_LIBRARY}
                             ${QT_QTOPENGL_LIBRARY}
                             ${QJSON_LIBRARIES})