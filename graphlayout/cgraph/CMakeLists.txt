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
	${GRAPHVIZSRC_DIRS}/lib/cgraph/flatten.c
	${GRAPHVIZSRC_DIRS}/lib/cgraph/graph.c
	${GRAPHVIZSRC_DIRS}/lib/cgraph/id.c
	${GRAPHVIZSRC_DIRS}/lib/cgraph/imap.c
	${GRAPHVIZSRC_DIRS}/lib/cgraph/io.c
	${GRAPHVIZSRC_DIRS}/lib/cgraph/mem.c
	${GRAPHVIZSRC_DIRS}/lib/cgraph/node.c
	${GRAPHVIZSRC_DIRS}/lib/cgraph/obj.c
	${GRAPHVIZSRC_DIRS}/lib/cgraph/pend.c
	${GRAPHVIZSRC_DIRS}/lib/cgraph/rec.c
	${GRAPHVIZSRC_DIRS}/lib/cgraph/refstr.c
	${GRAPHVIZSRC_DIRS}/lib/cgraph/subg.c
	${GRAPHVIZSRC_DIRS}/lib/cgraph/utils.c
	${GRAPHVIZSRC_DIRS}/lib/cgraph/write.c
	)

include_directories ( 
	${GRAPHVIZSRC_DIRS}/lib/cgraph
	${GRAPHVIZSRC_DIRS}/lib/cdt
	${GRAPHVIZSRC_DIRS}/lib/common
	${GRAPHVIZSRC_DIRS}
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


