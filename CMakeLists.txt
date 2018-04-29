project(qmlfrontend)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12 FATAL_ERROR)

# Turn on automatic invocation of the MOC
set(CMAKE_AUTOMOC ON)

#add extra search paths for libraries and includes
set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE STRING "Directory where lib will install")
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "The directory the headers are installed in")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# X11
set(X11_FOUND 0)
find_package(X11)
if(${X11_FOUND})
    add_definitions("-DWZ_WS_X11")
    if (!${X11_Xrandr_FOUND})
        message(FATAL_ERROR "Found X11 but not xrandr")
    endif()
endif()

# PhysFS
find_package(PhysFS 2 REQUIRED)

SET(QT_MODULES Core Gui Widgets Svg Qml Quick Network)
if (${X11_FOUND})
    list(APPEND QT_MODULES X11Extras)
endif()

# QT
find_package(Qt5 COMPONENTS ${QT_MODULES} REQUIRED)
if (Qt5_POSITION_INDEPENDENT_CODE)
    add_definitions(-fPIC)
    SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

function(check_private_headers_exist module private_includes_var)
  message(STATUS "Checking whether private include directories for module ${module} exist")
  foreach(_dir ${private_includes_var})
    if(NOT EXISTS "${_dir}")
      message(FATAL_ERROR "The private include directory ${_dir} for module ${module} do not exist! Please make sure your Qt5 installation contains private headers.\nThe required directories:\n  ${private_includes_var}")
    endif()
  endforeach()
endfunction()
check_private_headers_exist("Qt5Core" "${Qt5Core_PRIVATE_INCLUDE_DIRS}")

IF("${CMAKE_BUILD_TYPE}" MATCHES "^Rel.*")
    ADD_DEFINITIONS("-DQT_NO_DEBUG")
else()
    ADD_DEFINITIONS("-DDEBUG")
ENDIF()

# use sane compile flags
#add_definitions(
#  -DQT_USE_QSTRINGBUILDER
#  -DQT_NO_CAST_TO_ASCII
#  -DQT_NO_CAST_FROM_ASCII
#  -DQT_STRICT_ITERATORS
#  -DQT_NO_URL_CAST_FROM_STRING
#  -DQT_NO_CAST_FROM_BYTEARRAY
#  -DQT_NO_SIGNALS_SLOTS_KEYWORDS
#  -DQT_USE_FAST_OPERATOR_PLUS
#)

# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Core_DEFINITIONS}
                ${Qt5Gui_DEFINITIONS}
                ${Qt5Widgets_DEFINITIONS}
                ${Qt5Svg_DEFINITIONS}
                ${Qt5Qml_DEFINITIONS}
                ${Qt5Quick_DEFINITIONS}
                ${Qt5Network_DEFINITIONS})

if (${X11_FOUND})
    add_definitions(${Qt5X11Extras_DEFINITIONS})
endif()

set(QMLFRONTEND_INCLUDES ${CMAKE_SOURCE_DIR}
                         ${CMAKE_SOURCE_DIR}/src
                         ${Qt5Core_INCLUDE_DIRS}
                         ${Qt5Core_PRIVATE_INCLUDE_DIRS}
                         ${Qt5Gui_INCLUDE_DIRS}
                         ${Qt5Widgets_INCLUDE_DIRS}
                         ${Qt5Svg_INCLUDE_DIRS}
                         ${Qt5Qml_INCLUDE_DIRS}
                         ${Qt5Quick_INCLUDE_DIRS}
                         ${Qt5Network_INCLUDE_DIRS})

if (${X11_FOUND})
    list(APPEND QMLFRONTEND_INCLUDES ${Qt5X11Extras_INCLUDE_DIRS} ${X11_INCLUDE_DIR})
endif()

set(QMLFRONTEND_LIBRARIES ${PHYSFS_LIBRARY}
                          ${Qt5Core_LIBRARIES}
                          ${Qt5Gui_LIBRARIES}
                          ${Qt5Widgets_LIBRARIES}
                          ${Qt5Svg_LIBRARIES}
                          ${Qt5Qml_LIBRARIES}
                          ${Qt5Quick_LIBRARIES}
                          ${Qt5Network_LIBRARIES})

if (${X11_FOUND})
  list(APPEND QMLFRONTEND_LIBRARIES ${Qt5X11Extras_LIBRARIES} ${X11_Xrandr_LIB})
endif()


add_subdirectory(lib/WzLog)
add_subdirectory(lib/Imagemap)
add_subdirectory(src)
add_subdirectory(data)
#add_subdirectory(tools/extractmap)
