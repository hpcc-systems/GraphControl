# Component: graphdb
#####################################################
# Description:
# ------------
#	 Cmake Input File for graphdb
#####################################################

project( graphdb ) 

set (	SRCS 
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
	SvgShapes.cpp
	SvgShapes.h
	Platform.h
	targetver.h
	Unknown.cpp
	Unknown.h
	)

	include_directories ( 
	../graphlayout
	${EXPAT_INCLUDE_DIRS}/lib
	)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif (Boost_FOUND)

add_library ( graphdb SHARED ${SRCS} )

ADD_DEFINITIONS( -D_UNICODE -DXML_UNICODEXXX )

if (WIN32)
ADD_DEFINITIONS( -D_USRDLL -DGRAPHDB_EXPORTS )
else ()
endif ()

add_dependencies ( graphdb 
	graphlayout 
	expat 
	)

target_link_libraries ( graphdb 
	graphlayout 
	expat 
	${Boost_LIBRARIES}	
	)
