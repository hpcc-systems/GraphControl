# Component: graphdb
#####################################################
# Description:
# ------------
#	 Cmake Input File for graphdb
#####################################################

project( graphdb ) 

set (	SRCS 
	precompiled_headers.h
	GraphCluster.cpp
	GraphCluster.h
	GraphDB.cpp
	GraphDB.h
	GraphEdge.cpp
	GraphEdge.h
	GraphGraph.cpp
	GraphGraph.h
	GraphItem.cpp
	GraphItem.h
	GraphVertex.cpp
	GraphVertex.h
	GraphvizLayout.cpp
	GraphvizLayout.h
	util.cpp
	util.h
	SaxParser.cpp
	SaxParser.h
	SvgParser.cpp
	SvgParser.h
	XgmmlParser.cpp
	XgmmlParser.h
	XmlParser.cpp
	XmlParser.h
	DotParser.cpp
	DotParser.h
	SvgShapes.cpp
	SvgShapes.h
	DotShapes.cpp
	DotShapes.h
	Platform.h
	targetver.h
	Unknown.cpp
	Unknown.h
	)

include_directories ( 
	../graphlayout
	${EXPAT_INCLUDE_DIRS}/lib
	${Boost_INCLUDE_DIRS}
	)

if (WIN32)
set (	SRCS 
	${SRCS}
	GraphDB.rc 
	)
endif ()

ADD_MSVC_PRECOMPILED_HEADER("precompiled_headers.h" "precompiled_headers.cpp" SRCS)
if (WITH_DYNAMIC_MSVC_RUNTIME)
	add_library ( graphdb SHARED ${SRCS} )
else (WITH_DYNAMIC_MSVC_RUNTIME)
	add_library ( graphdb STATIC ${SRCS} )
endif (WITH_DYNAMIC_MSVC_RUNTIME)

ADD_DEFINITIONS( -D_UNICODE -DXML_UNICODEXXX )

if (WIN32)
ADD_DEFINITIONS( -DGRAPHDB_EXPORTS )
else ()
endif ()

add_dependencies ( graphdb 
	graphlayout 
	#expat 
	)

target_link_libraries ( graphdb 
	graphlayout 
	expat 
	${Boost_LIBRARIES}
	)
	
if ( WIN32 )	
else ( WIN32 )	
install ( TARGETS graphdb DESTINATION lib/mozilla/plugins )
endif ( WIN32 )	

