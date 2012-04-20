# Component: graphdb
#####################################################
# Description:
# ------------
#	 Cmake Input File for graphdb
#####################################################

project( graphdb ) 

# *********************************************************************

include_directories ( 
	../graphlayout
	${EXPAT_INCLUDE_DIRS}/lib
	${Boost_INCLUDE_DIRS}
	)

# *********************************************************************

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
	targetver.h
	Unknown.cpp
	Unknown.h
	)

# *********************************************************************

add_definitions(-D_UNICODE)

if(WIN32)
	add_definitions(-DGRAPHDB_EXPORTS)
elseif(APPLE)
elseif(UNIX)
endif()

ADD_MSVC_PRECOMPILED_HEADER("precompiled_headers.h" "precompiled_headers.cpp" SRCS)
if (WITH_STATIC_RUNTIME)
	add_library ( graphdb STATIC ${SRCS} )
else (WITH_STATIC_RUNTIME)
	add_library ( graphdb SHARED ${SRCS} )
endif (WITH_STATIC_RUNTIME)

# *********************************************************************

target_link_libraries ( graphdb 
	graphlayout 
	expat 
	${Boost_LIBRARIES}
	)

# *********************************************************************

INSTALL(TARGETS graphdb 
	RUNTIME DESTINATION bin COMPONENT PLUGIN
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
)
