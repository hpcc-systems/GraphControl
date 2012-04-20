
# Component: graphrender
#####################################################
# Description:
# ------------
#	 Cmake Input File for graphrender
#####################################################

project( graphrender )

# *********************************************************************

include_directories (
	gen
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
		${GTK_INCLUDE_DIRS}
		)
elseif(UNIX)
	include_directories (
		${GTK_INCLUDE_DIRS}
		)
endif()

# SRC *****************************************************************

set (	SRCS
	precompiled_headers.h

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

if(WIN32)
	add_definitions(-DGRAPHRENDER_EXPORTS)
elseif(APPLE)
elseif(UNIX)
endif()

set(SOURCES ${SRCS} ${SRCS_WIN} ${SRCS_APPLE} ${SRCS_UNIX})
ADD_MSVC_PRECOMPILED_HEADER("precompiled_headers.h" "precompiled_headers.cpp" SOURCES)
if (WITH_STATIC_RUNTIME)
	add_library ( graphrender STATIC ${SOURCES} )
else (WITH_STATIC_RUNTIME)
	add_library ( graphrender SHARED ${SOURCES} )
endif (WITH_STATIC_RUNTIME)

# *********************************************************************

target_link_libraries ( graphrender 
	graphdb 
	agg
	)

# *********************************************************************

INSTALL(TARGETS graphrender 
	RUNTIME DESTINATION bin COMPONENT PLUGIN
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
)
