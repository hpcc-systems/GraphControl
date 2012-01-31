project ( GraphControl )
cmake_minimum_required (VERSION 2.6)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/" ${CMAKE_MODULE_PATH})

##################################################################

# Build tag generation

set ( HPCC_MAJOR 6 )
set ( HPCC_MINOR 0 )
set ( HPCC_POINT 4 )
set ( HPCC_BUILD 6 )
set ( HPCC_VERSION ${HPCC_MAJOR}.${HPCC_MINOR}.${HPCC_POINT}.${HPCC_BUILD} )

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
  )

configure_file (
  "${PROJECT_SOURCE_DIR}/install.rdf.in"
  "${PROJECT_SOURCE_DIR}/install.rdf"
  )

configure_file (
  "${PROJECT_SOURCE_DIR}/npHPCCSystemsGraphViewControl.inf.in"
  "${PROJECT_SOURCE_DIR}/npHPCCSystemsGraphViewControl.inf"
  )
##################################################################

option(WITH_DYNAMIC_MSVC_RUNTIME "Build with dynamic MSVC runtime (/MD)" OFF)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Location of BIN files")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Location of LIB files")
if (WIN32)
elseif(APPLE)
elseif(UNIX)
	option(WITH_BUILD_TARGET_IN_PLUGINS_FOLDER "Build directly into mozilla/plugins" OFF)
	if (WITH_BUILD_TARGET_IN_PLUGINS_FOLDER)
      set(EXECUTABLE_OUTPUT_PATH "/usr/lib/mozilla/plugins")
      set(LIBRARY_OUTPUT_PATH "/usr/lib/mozilla/plugins")
	endif()
endif()

include ( "${CMAKE_SOURCE_DIR}/cmake/Modules/Utils.cmake" )
include ( "${CMAKE_SOURCE_DIR}/cmake/Modules/Externals.cmake" )

if (WIN32)
	add_definitions(-DFB_WIN=1 -DXP_WIN=1 -D_CRT_SECURE_NO_WARNINGS)
    if (WITH_DYNAMIC_MSVC_RUNTIME)
        message(STATUS "Building with dynamic MSVC runtime")
	else (WITH_DYNAMIC_MSVC_RUNTIME)
        message(STATUS "Building with static MSVC runtime")
		add_definitions(-DSTATIC_LIB)
	endif (WITH_DYNAMIC_MSVC_RUNTIME)
    foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
            CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
	    if (WITH_DYNAMIC_MSVC_RUNTIME)
		    if(${flag_var} MATCHES "/MT")
			    string(REGEX REPLACE "/MT" "/MD" ${flag_var} "${${flag_var}}")
			endif()
		else()
		    if(${flag_var} MATCHES "/MD")
			    string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
			endif()
		endif()
    endforeach(flag_var)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D BOOST_ALL_NO_LIB=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D BOOST_ALL_NO_LIB=1")
elseif(APPLE)
	add_definitions(-DFB_MACOSX=1)
elseif(UNIX)
	add_definitions(-DFB_X11=1 -DXP_UNIX=1)
	find_package(PkgConfig)

	# GTK is required for XEmbed to work
	if (NOT GTK_INCLUDE_DIRS)
		pkg_check_modules(GTK REQUIRED gtk+-2.0)
		set (GTK_INCLUDE_DIRS ${GTK_INCLUDE_DIRS} CACHE INTERNAL "GTK include dirs")
		set (GTK_LIBRARIES ${GTK_LIBRARIES} CACHE INTERNAL "GTK include dirs")
		set (GTK_LIBRARY_DIRS ${GTK_LIBRARY_DIRS} CACHE INTERNAL "GTK include dirs")
		set (GTK_LDFLAGS ${GTK_LDFLAGS} CACHE INTERNAL "GTK include dirs")
	endif()

	set(gecko_defs -DXP_UNIX)
    set(fPIC_flag "-fPIC")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${gecko_defs} ${fPIC_flag}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${gecko_defs} ${fPIC_flag}")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(agg)
set_property(TARGET agg PROPERTY FOLDER "3rdParty")
if(WIN32)
	add_definitions(-DXML_STATIC)
	add_subdirectory(expat)
	set_property(TARGET expat PROPERTY FOLDER "3rdParty")
elseif(APPLE)
elseif(UNIX)
endif()

add_subdirectory (graphlayout)
add_subdirectory (graphdb)
add_subdirectory (graphrender)
add_subdirectory (HPCCSystemsGraphViewControl)

if(WIN32)
elseif(APPLE)
elseif(UNIX)
endif()
