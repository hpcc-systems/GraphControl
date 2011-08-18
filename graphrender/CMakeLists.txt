
# Component: graphrender
#####################################################
# Description:
# ------------
#	 Cmake Input File for graphrender
#####################################################

project( graphrender )

set (	SRCS
	GraphRender.cpp
	GraphRender.h
	GraphBuffer.cpp
	GraphBuffer.h
	GraphHotItem.cpp
	GraphHotItem.h

	x11_pixel_map.h
	platform.h
	)

if (WIN32)
set (	SRCS_OS
	)
else (WIN32)
set (	SRCS_OS
	)
endif (WIN32)

include_directories (
	gen
	../graphdb
	${AGG_INCLUDE_DIRS}/include
	${AGG_INCLUDE_DIRS}/agg2d
	${AGG_INCLUDE_DIRS}/font_freetype
	)

if (WIN32)
    INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})
    LINK_LIBRARIES(${FREETYPE_LIBRARIES})
else (WIN32)
include_directories (
	${GTK_INCLUDE_DIRS}
	)
endif (WIN32)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif (Boost_FOUND)

add_library ( graphrender SHARED ${SRCS} )

ADD_DEFINITIONS( -D_UNICODE -DAGG_USE_FREETYPE -DAGG_USE_AGG2D -DAGG2D_USE_FREETYPE )

if (WIN32)
ADD_DEFINITIONS( -D_USRDLL -DGRAPHRENDER_EXPORTS )
else ()
endif ()

add_dependencies ( graphrender 
	graphdb 
	agg
	)

target_link_libraries ( graphrender 
	graphdb 
	agg
	)

