
# Component: graphrender
#####################################################
# Description:
# ------------
#	 Cmake Input File for graphrender
#####################################################

project( graphrender )

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

if (WIN32)
set (	SRCS 
	${SRCS}
	)
endif ()

include_directories (
	gen
	../graphdb
	../agg
	${AGGSRC_DIRS}/agg-2.4/include
	${AGGSRC_DIRS}/agg-2.4/font_freetype
	${Boost_INCLUDE_DIRS}
	)

if (WIN32)
    INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})
    LINK_LIBRARIES(${FREETYPE_LIBRARIES})
else (WIN32)
include_directories (
	${GTK_INCLUDE_DIRS}
	)
endif (WIN32)

ADD_MSVC_PRECOMPILED_HEADER("precompiled_headers.h" "precompiled_headers.cpp" SRCS)
if (WIN32)
	add_library ( graphrender STATIC ${SRCS} )
else (WIN32)
	add_library ( graphrender SHARED ${SRCS} )
endif (WIN32)

ADD_DEFINITIONS( -D_UNICODE -DAGG_USE_FREETYPE -DAGG_USE_AGG2D -DAGG2D_USE_FREETYPE )

if (WIN32)
ADD_DEFINITIONS( -DGRAPHRENDER_EXPORTS )
else ()
endif ()

add_dependencies ( graphrender 
	graphdb 
	agg
	)

target_link_libraries ( graphrender 
	graphdb 
	agg
	#${Boost_LIBRARIES}
	)

if ( WIN32 )	
else ( WIN32 )	
install ( TARGETS graphrender DESTINATION lib/mozilla/plugins )
endif ( WIN32 )	
