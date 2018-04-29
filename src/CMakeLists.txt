find_package(PhysFS 2 REQUIRED)

find_path(WZ_BUILD_DIR config.h
        HINTS "${CMAKE_SOURCE_DIR}/../.."
        DOC "Path to directory containing the config.h file created by warzone's build configuration step")

file(GLOB_RECURSE qmlfrontendSources "*.c" "*.cpp")
file(GLOB_RECURSE qmlfrontendHeaders "*.h" "*.hpp")

SET(qmlfrontend_SRCS main.cpp ${qmlfrontendSources})

INCLUDE_DIRECTORIES(${QMLFRONTEND_INCLUDES} ${PHYSFS_INCLUDE_DIR})

QT5_WRAP_CPP(QMLFRONTEND_MOC_FILES ${qmlfrontendHeaders})

ADD_EXECUTABLE(viewer ${qmlfrontend_SRCS} ${QMLFRONTEND_MOC_FILES})
TARGET_LINK_LIBRARIES(viewer wzlog
                             imagemap
                             ${PHYSFS_LIBRARY}
                             ${Qt5Core_LIBRARIES}
                             ${Qt5Gui_LIBRARIES}
                             ${Qt5Widgets_LIBRARIES}
                             ${Qt5Svg_LIBRARIES}
                             ${Qt5Qml_LIBRARIES}
                             ${Qt5Quick_LIBRARIES}
                             ${Qt5Network_LIBRARIES}
                             ${Qt5OpenGL_LIBRARIES})
