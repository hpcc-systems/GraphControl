#/**********************************************************\ 
# 
# Auto-generated CMakeLists.txt for the HPCC Systems Graph View Control project
#
#\**********************************************************/

# Written to work with cmake 2.6
cmake_minimum_required (VERSION 2.6)
set (CMAKE_BACKWARDS_COMPATIBILITY 2.6)

Project(${PLUGIN_NAME})

file (GLOB GENERAL RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    [^.]*.cpp
    [^.]*.h
    [^.]*.cmake
    )

message("${CMAKE_CURRENT_SOURCE_DIR}")
message("Boost:  ${Boost_INCLUDE_DIRS}")
include_directories(${PLUGIN_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}/../graphdb
	${CMAKE_CURRENT_SOURCE_DIR}/../graphrender
	)

# Generated files are stored in ${GENERATED} by the project configuration
SET_SOURCE_FILES_PROPERTIES(
    ${GENERATED}
    PROPERTIES
        GENERATED 1
    )

SOURCE_GROUP(Generated FILES
    ${GENERATED}
    )

SET( SOURCES
    ${GENERAL}
    ${GENERATED}
    )

# This will include Win/projectDef.cmake, X11/projectDef.cmake, Mac/projectDef 
# depending on the platform
include_platform()

set ( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${FB_PROJECTS_DIR}/cmake/Modules" )
include ( "${FB_PROJECTS_DIR}/cmake/Modules/Externals.cmake" )

add_subdirectory("${FB_PROJECTS_DIR}/agg" "agg")
set_property(TARGET agg PROPERTY FOLDER "3rdParty")
if(WIN32)
    add_definitions(-DXML_STATIC)
    add_subdirectory("${FB_PROJECTS_DIR}/expat" "expat")
    set_property(TARGET expat PROPERTY FOLDER "3rdParty")

    if (WITH_HPCC_RUNTIME)
        add_definitions(-DGRAPHLAYOUT_EXPORTS)
        add_definitions(-DGRAPHDB_EXPORTS)
        add_definitions(-DGRAPHRENDER_EXPORTS)
    else (WITH_HPCC_RUNTIME)
        add_definitions(-DGRAPHLAYOUT_STATIC)
        add_definitions(-DGRAPHDB_STATIC)
        add_definitions(-DGRAPHRENDER_STATIC)
    endif (WITH_HPCC_RUNTIME)
elseif(APPLE)
elseif(UNIX)
endif()

add_subdirectory ("${FB_PROJECTS_DIR}/graphlayout" "graphlayout")
add_subdirectory ("${FB_PROJECTS_DIR}/graphdb" "graphdb")
add_subdirectory ("${FB_PROJECTS_DIR}/graphrender" "graphrender")

target_link_libraries(${PROJECT_NAME}
	graphdb
	graphrender
	)
