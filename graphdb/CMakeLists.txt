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
	precompiled_headers.cpp

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

if (WITH_HPCC_RUNTIME)
	add_library ( graphdb SHARED ${SRCS} )
else (WITH_HPCC_RUNTIME)
	add_library ( graphdb STATIC ${SRCS} )
endif (WITH_HPCC_RUNTIME)
ADD_PRECOMPILED_HEADER(${PROJECT_NAME} "precompiled_headers.h" "precompiled_headers.cpp" SRCS)

# *********************************************************************

target_link_libraries ( graphdb 
	graphlayout 
	expat 
	)
link_boost_library ( ${PROJECT_NAME} date_time )
link_boost_library ( ${PROJECT_NAME} system )

# *********************************************************************

if (WITH_HPCC_RUNTIME)
	install ( TARGETS graphdb RUNTIME DESTINATION bin LIBRARY DESTINATION lib )
endif (WITH_HPCC_RUNTIME)

