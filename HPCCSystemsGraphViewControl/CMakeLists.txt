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
	${CMAKE_CURRENT_SOURCE_DIR}/../libs/graphdb
	${CMAKE_CURRENT_SOURCE_DIR}/../libs/graphrender
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

message("EXECUTABLE_OUTPUT_PATH  ${EXECUTABLE_OUTPUT_PATH}")
if ( WIN32 )
target_link_libraries(${PROJECT_NAME}
	${Boost_LIBRARIES}
	${CMAKE_BINARY_DIR}/bin/HPCCSystemsGraphViewControl/Release/graphdb.lib
	${CMAKE_BINARY_DIR}/bin/HPCCSystemsGraphViewControl/Release/graphrender.lib
    )
elseif ( APPLE )
IF ( "${CMAKE_GENERATOR}" STREQUAL "Unix Makefiles" )
	target_link_libraries(${PROJECT_NAME}
		${CMAKE_BINARY_DIR}/bin/HPCCSystemsGraphViewControl/libgraphdb.dylib
		${CMAKE_BINARY_DIR}/bin/HPCCSystemsGraphViewControl/libgraphrender.dylib
		)
ELSE ()
	target_link_libraries(${PROJECT_NAME}
		${CMAKE_BINARY_DIR}/bin/HPCCSystemsGraphViewControl/Release/libgraphdb.dylib
		${CMAKE_BINARY_DIR}/bin/HPCCSystemsGraphViewControl/Release/libgraphrender.dylib
		)
ENDIF ()
elseif ( UNIX )
target_link_libraries(${PROJECT_NAME}
	${CMAKE_BINARY_DIR}/bin/HPCCSystemsGraphViewControl/libgraphdb.so
	${CMAKE_BINARY_DIR}/bin/HPCCSystemsGraphViewControl/libgraphrender.so
    )
endif()
