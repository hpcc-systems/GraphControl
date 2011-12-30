
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
set (	SRCS 
	${SRCS}
	GraphRender.rc
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

if (WITH_DYNAMIC_MSVC_RUNTIME)
	add_library ( graphrender SHARED ${SRCS} )
else (WITH_DYNAMIC_MSVC_RUNTIME)
	add_library ( graphrender STATIC ${SRCS} )
endif (WITH_DYNAMIC_MSVC_RUNTIME)

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
