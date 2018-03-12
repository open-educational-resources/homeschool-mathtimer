cmake_minimum_required(VERSION 2.8)
project(math-timer CXX C)
set(PROJECT_NAME math-timer)
set(VERSION "0.0.1")
set(DATE "Mar 12, 2018")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(SHORT_DESC "Math program to test skills")
set(LONG_DESC "Beat the clock to complete various math problems before time runs out!")
set(AUTHOR "israeldahl")
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
     message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()
if(NOT EXISTS "/etc/debian_version")
	set(result false)
else()
	set(result true)
endif()
# Packages we need
if(result)
	## Because Launchpad's build system is really weird!
    MESSAGE("Using Debian based release")
	FIND_PACKAGE(FLTK REQUIRED NO_MODULE)
else()
	 FIND_PACKAGE(FLTK REQUIRED)
endif()
FIND_PACKAGE(X11 REQUIRED)
#Because NixOS does things differently
string(COMPARE EQUAL "${FLTK_FLUID_EXECUTABLE}" "" fluid_result)
## Because Launchpad's build system is really weird!
IF(fluid_result)
    # Try to detect full path anyway
    EXECUTE_PROCESS(COMMAND which fluid OUTPUT_VARIABLE FLTK_FLUID_EXECUTABLE OUTPUT_STRIP_TRAILING_WHITESPACE)
    IF(NOT EXISTS "${FLTK_FLUID_EXECUTABLE}")
        MESSAGE(FATAL_ERROR "Please install the fluid binary which is part of FLTK.")
    ENDIF()
ENDIF()
#Because NixOS does things differently
string(COMPARE EQUAL "${FLTK_INCLUDE_DIR}" "" fltk_result)
## Because Launchpad's build system is really weird!
IF( fltk_result)
    # Try to detect full path anyway
    set(FLTK_INCLUDE_DIR "/usr/include")
    IF(NOT EXISTS "${FLTK_INCLUDE_DIR}")
        MESSAGE(FATAL_ERROR "Please install the FLTK header files which is part of FLTK.")
    ENDIF()
ENDIF()
# Don't need OpenGL or the Fluid plugin, since I export the source from FLUID
set(FLTK_SKIP_OPENGL True)
set(FLTK_SKIP_FLUID True)

include(AddFileDependencies)
include(CheckIncludeFiles)
include(FindPkgConfig)
INCLUDE_DIRECTORIES("${FLTK_INCLUDE_DIR}"
		    "${X11_INCLUDE_DIR}"
		    "${X11_Xpm_INCLUDE_PATH}"
            "${CMAKE_SOURCE_DIR}/include")
set(SOURCES src/common.cpp src/fltkfunctions.cpp)
## install things in /usr
set(CMAKE_INSTALL_PREFIX "/usr")
file(RELATIVE_PATH LIB_DIR_RELATIVE "/${BIN_DIR}" "/${LIB_DIR}")
#Configure Man page
#configure_file("data/math-timer.1.in" "math-timer.1")
#set(CMAKE_BUILD_TYPE "RELEASE")
#set(CMAKE_CONFIGURATION_TYPE "RELEASE")
## Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Os -finline-small-functions -finline-functions-called-once -fno-unwind-tables -fno-asynchronous-unwind-tables -s")
#Because NixOS does things differently
string(COMPARE EQUAL "${X11_INCLUDE_DIR}" "" x11_result)
if( x11_result )
    MESSAGE(FATAL_ERROR "X11 headers are not found")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX_COMMON_HAS_X=true")
endif()
install(FILES data/math-timer.desktop DESTINATION share/applications)
install(FILES data/distributor-logo.png DESTINATION share/pixmaps)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -fvar-tracking -DDEBUG=true -DCOMMON_XMLOUT=true")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finline-small-functions -ffunction-sections -fdata-sections -fmerge-all-constants -fomit-frame-pointer -fno-unwind-tables -fno-asynchronous-unwind-tables -Os -std=c++0x -finline-functions-called-once -s -DQUIET_ERROR=true")
add_library(mathtimer STATIC ${SOURCES})
set(ALL_LIBS mathtimer ${X11_LIBRARIES} ${X11_X11_LIB} ${X11_Xpm_LIB} ${FLTK_LIBRARIES})
## Because Launchpad's build system is really weird!
if(result)
	set(ALL_LIBS ${ALL_LIBS} fltk_SHARED fltk_images_SHARED)
endif()
add_executable(math-timer src/math-timer.cxx)
TARGET_LINK_LIBRARIES(math-timer mathtimer ${ALL_LIBS})

## install the man file
#install(FILES math-timer.1 DESTINATION share/man/man1/ PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
install(TARGETS math-timer mathtimer RUNTIME DESTINATION bin ARCHIVE DESTINATION lib)
