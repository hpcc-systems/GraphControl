
# Component: graphrender
#####################################################
# Description:
# ------------
#	 Cmake Input File for graphrender
#####################################################

project( graphrender )

# *********************************************************************

include_directories (
	../graphdb
	../agg
	${AGGSRC_DIRS}/agg-2.4/include
	${AGGSRC_DIRS}/agg-2.4/font_freetype
	${FREETYPE_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	)

if(WIN32)
elseif(APPLE)
	include_directories (
		${CARBON_INCLUDE_DIR}
		${QT_INCLUDE_DIR}
		)
elseif(UNIX)
	include_directories (
		${GTK_INCLUDE_DIRS}
		)
endif()

# SRC *****************************************************************

set (	SRCS
	precompiled_headers.h
	precompiled_headers.cpp

	GraphRender.cpp
	GraphRender.h
	GraphBuffer.cpp
	GraphBuffer.h
	GraphHotItem.cpp
	GraphHotItem.h
	FontResolver.cpp
	FontResolver.h
	)

# Win *****************************************************************

set (	SRCS_WIN
	)

SOURCE_GROUP(Win FILES ${SRCS_WIN})

# OSX *****************************************************************

set (	SRCS_APPLE
	osx_pixel_map.cpp
	osx_pixel_map.h
	)

SOURCE_GROUP(OSX FILES ${SRCS_APPLE})

# X11 *****************************************************************

set (	SRCS_UNIX
	x11_pixel_map.h
	)

SOURCE_GROUP(X11 FILES ${SRCS_UNIX})

# *********************************************************************

if(WIN32)
    set_source_files_properties(${SRCS_APPLE} PROPERTIES HEADER_FILE_ONLY 1)
    set_source_files_properties(${SRCS_UNIX} PROPERTIES HEADER_FILE_ONLY 1)
elseif(APPLE)
    set_source_files_properties(${SRCS_WIN} PROPERTIES HEADER_FILE_ONLY 1)
    set_source_files_properties(${SRCS_UNIX} PROPERTIES HEADER_FILE_ONLY 1)
elseif(UNIX)
    set_source_files_properties(${SRCS_WIN} PROPERTIES HEADER_FILE_ONLY 1)
    set_source_files_properties(${SRCS_APPLE} PROPERTIES HEADER_FILE_ONLY 1)
endif()

# *********************************************************************

add_definitions(-D_UNICODE -DAGG_USE_FREETYPE -DAGG_USE_AGG2D -DAGG2D_USE_FREETYPE)

set(SOURCES ${SRCS} ${SRCS_WIN} ${SRCS_APPLE} ${SRCS_UNIX})
if (WITH_HPCC_RUNTIME)
	add_library ( graphrender SHARED ${SOURCES} )
else (WITH_HPCC_RUNTIME)
	add_library ( graphrender STATIC ${SOURCES} )
endif (WITH_HPCC_RUNTIME)
ADD_PRECOMPILED_HEADER(${PROJECT_NAME} "precompiled_headers.h" "precompiled_headers.cpp" SOURCES)

# *********************************************************************

target_link_libraries ( graphrender 
	graphdb 
	agg
	)
link_boost_library ( ${PROJECT_NAME} filesystem )

# *********************************************************************

if (WITH_HPCC_RUNTIME)
	install ( TARGETS graphrender RUNTIME DESTINATION bin LIBRARY DESTINATION lib )
endif (WITH_HPCC_RUNTIME)

