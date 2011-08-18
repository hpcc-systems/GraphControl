# Component: agraph
#####################################################
# Description:
# ------------
#	 Cmake Input File for agraph
#####################################################

project( agraph ) 

set (	SRCS 
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/agerror.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/apply.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/attr.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/edge.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/flatten.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/grammar.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/graph.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/id.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/imap.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/io.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/mem.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/node.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/obj.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/pend.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/rec.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/refstr.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/scan.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/subg.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/utils.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph/write.c
	)

include_directories ( 
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agraph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt
	${GRAPHVIZ_INCLUDE_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( agraph STATIC
			${SRCS} 
			)
target_link_libraries ( agraph 
	)
