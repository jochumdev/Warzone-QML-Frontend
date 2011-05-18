file(GLOB_RECURSE qmlfrontendSources "*.c" "*.cpp")
file(GLOB_RECURSE qmlfrontendHeaders "*.h" "*.hpp")

SET(qmlfrontend_SRCS ${qmlfrontendSources} main.cpp)

#QT4_AUTOMOC(${qmlfrontend_SRCS} ${QMLFRONTEND_INCLUDES})
INCLUDE_DIRECTORIES(${QMLFRONTEND_INCLUDES})

ADD_EXECUTABLE(viewer ${qmlfrontend_SRCS} ${imagemap_SOURCE})
TARGET_LINK_LIBRARIES(viewer ${OPENGL_gl_LIBRARY} ${QT_CORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSVG_LIBRARY} ${QT_QTDECLARATIVE_LIBRARY} ${QT_QTOPENGL_LIBRARY} ${QJSON_LIBRARIES})
