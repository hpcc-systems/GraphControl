# Component: cgraph
#####################################################
# Description:
# ------------
#	 Cmake Input File for cgraph
#####################################################

project( cgraph ) 

set (	SRCS 
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/agerror.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/agxbuf.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/apply.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/attr.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/cgraph.def
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/edge.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/flatten.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/graph.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/id.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/imap.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/io.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/mem.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/node.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/obj.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/pend.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/rec.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/refstr.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/subg.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/utils.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph/write.c
	)

include_directories ( 
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common
	${GRAPHVIZ_INCLUDE_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( cgraph STATIC
			${SRCS} 
			)
target_link_libraries ( cgraph 
	)


