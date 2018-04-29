CMAKE_MINIMUM_REQUIRED(VERSION 3.8.2)

project(qmlfrontend)

# Turn on automatic invocation of the MOC
set(CMAKE_AUTOMOC ON)

# compile in debug mode
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
      "Choose the type of build, options are: None Debug Debug2 Debug3 Release RelWithDebInfo MinSizeRel."
      FORCE)
endif ()

IF("${CMAKE_BUILD_TYPE}" MATCHES "^Rel.*")
  ADD_DEFINITIONS("-DQT_NO_DEBUG_OUTPUT")
ENDIF()

#add extra search paths for libraries and includes
set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE STRING "Directory where lib will install")
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "The directory the headers are installed in")

# QT
find_package(Qt5 COMPONENTS Core Gui Widgets Svg Qml Quick Network OpenGL REQUIRED)
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

# Ugly OS-X Fix, should find a better way.
IF(${CMAKE_SYSTEM_NAME} MATCHES "^Darwin")
	SET(QT_QTCORE_LIBRARY "-framework QtCore")
ENDIF()

IF("${CMAKE_BUILD_TYPE}" MATCHES "^Rel.*")
    ADD_DEFINITIONS("-DQT_NO_DEBUG")
ENDIF()

# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Core_DEFINITIONS}
                ${Qt5Gui_DEFINITIONS}
                ${Qt5Widgets_DEFINITIONS}
                ${Qt5Svg_DEFINITIONS}
                ${Qt5Qml_DEFINITIONS}
                ${Qt5Quick_DEFINITIONS}
                ${Qt5Network_DEFINITIONS}
                ${Qt5OpenGL_DEFINITIONS})

set(QMLFRONTEND_INCLUDES ${CMAKE_SOURCE_DIR}
                         ${CMAKE_SOURCE_DIR}/src
                         ${Qt5Core_INCLUDE_DIRS}
                         ${Qt5Core_PRIVATE_INCLUDE_DIRS}
                         ${Qt5Gui_INCLUDE_DIRS}
                         ${Qt5Widgets_INCLUDE_DIRS}
                         ${Qt5Svg_INCLUDE_DIRS}
                         ${Qt5Qml_INCLUDE_DIRS}
                         ${Qt5Quick_INCLUDE_DIRS}
                         ${Qt5Network_INCLUDE_DIRS}
                         ${Qt5OpenGL_INCLUDE_DIRS})

add_subdirectory(lib/WzLog)
add_subdirectory(lib/Imagemap)
add_subdirectory(src)
add_subdirectory(data)
#add_subdirectory(tools/extractmap)
