
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
		/Developer/Headers/FlatCarbon
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

	x11_pixel_map.h
	)

# *********************************************************************

add_definitions(-D_UNICODE -DAGG_USE_FREETYPE -DAGG_USE_AGG2D -DAGG2D_USE_FREETYPE)

if(WIN32)
	add_definitions(-DGRAPHRENDER_EXPORTS)
elseif(APPLE)
elseif(UNIX)
endif()

ADD_MSVC_PRECOMPILED_HEADER("precompiled_headers.h" "precompiled_headers.cpp" SRCS)
if(WIN32)
	add_library ( graphrender STATIC ${SRCS} )
elseif(APPLE)
	add_library ( graphrender SHARED ${SRCS} )
elseif(UNIX)
	add_library ( graphrender SHARED ${SRCS} )
endif()

# *********************************************************************

target_link_libraries ( graphrender 
	graphdb 
	agg
	)

# *********************************************************************
