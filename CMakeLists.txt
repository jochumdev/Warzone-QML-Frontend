CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

project(qmlfrontend)

# compile in debug mode
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Debug2 Debug3 Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF()

IF("${CMAKE_BUILD_TYPE}" MATCHES "^Rel.*")
  ADD_DEFINITIONS("-DQT_NO_DEBUG_OUTPUT")
ENDIF()

#add extra search paths for libraries and includes
set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE STRING "Directory where lib will install")
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "The directory the headers are installed in")

find_package(OpenGL REQUIRED)

# QT
set(QT_USE_IMPORTED_TARGETS TRUE)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

# Ugly OS-X Fix, should find a better way.
IF(${CMAKE_SYSTEM_NAME} MATCHES "^Darwin")
	SET(QT_CORE_LIBRARY "-framework QtCore")
ELSE()
	SET(QT_CORE_LIBRARY ${QT_QTCORE_LIBRARY})
ENDIF()

IF("${CMAKE_BUILD_TYPE}" MATCHES "^Rel.*")
    ADD_DEFINITIONS("-DQT_NO_DEBUG")
ENDIF()

##
########### from spring rts ################
##
# This would produce the maximum on warnings
#set(DEBUG_WARNINGS "-Wall -Wconversion")
# This should produce a sane amount of warnings
set(DEBUG_WARNINGS "-Wall -Wno-sign-compare")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsingle-precision-constant -frounding-math")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${IEEE_FP_FLAG} -pipe -fno-strict-aliasing ${VISIBILITY_HIDDEN} ${VISIBILITY_INLINES_HIDDEN}")
add_definitions(-DSTREFLOP_SSE)
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
ENDIF ()
set(CMAKE_CXX_FLAGS_DEBUG "${CXX_FLAGS_DEBUG_ADDITIONAL} -O1 ${DEBUG_WARNINGS} -DDEBUG -D_DEBUG -DNO_CATCH_EXCEPTIONS")
set(CMAKE_CXX_FLAGS_DEBUG2 "${CXX_FLAGS_DEBUG_ADDITIONAL} -O0 ${DEBUG_WARNINGS} -DDEBUG -D_DEBUG -DNO_CATCH_EXCEPTIONS")
set(CMAKE_CXX_FLAGS_DEBUG3 "${CXX_FLAGS_DEBUG_ADDITIONAL} -O0 ${DEBUG_WARNINGS} -DDEBUG -D_DEBUG -DNO_CATCH_EXCEPTIONS")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CXX_FLAGS_DEBUG_ADDITIONAL} -O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_PROFILE "-O2 -pg ${DEBUG_WARNINGS} -DNDEBUG")
set(CMAKE_MODULE_LINKER_FLAGS_PROFILE "-pg")
set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "-pg")
if (STABS_DEBUG_SYMBOLS)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gstabs")
    set(CMAKE_CXX_FLAGS_DEBUG2 "${CMAKE_CXX_FLAGS_DEBUG2} -gstabs")
    set(CMAKE_CXX_FLAGS_DEBUG3 "${CMAKE_CXX_FLAGS_DEBUG3} -gstabs")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -gstabs")
ELSE ()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb1")
    set(CMAKE_CXX_FLAGS_DEBUG2 "${CMAKE_CXX_FLAGS_DEBUG2} -ggdb2")
    set(CMAKE_CXX_FLAGS_DEBUG3 "${CMAKE_CXX_FLAGS_DEBUG3} -ggdb3")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -g")
ENDIF ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(QMLFRONTEND_INCLUDES ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src ${OPENGL_INCLUDE_DIR} ${QT_INCLUDES})

include(lib/Imagemap/CMakeLists.txt)
add_subdirectory(src)
add_subdirectory(tools/extractmap)
