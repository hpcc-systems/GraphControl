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
	${GRAPHVIZSRC_DIRS}/lib/agraph/graph.c
	${GRAPHVIZSRC_DIRS}/lib/agraph/id.c
	${GRAPHVIZSRC_DIRS}/lib/agraph/imap.c
	${GRAPHVIZSRC_DIRS}/lib/agraph/io.c
	${GRAPHVIZSRC_DIRS}/lib/agraph/mem.c
	${GRAPHVIZSRC_DIRS}/lib/agraph/node.c
	${GRAPHVIZSRC_DIRS}/lib/agraph/obj.c
	${GRAPHVIZSRC_DIRS}/lib/agraph/pend.c
	${GRAPHVIZSRC_DIRS}/lib/agraph/rec.c
	${GRAPHVIZSRC_DIRS}/lib/agraph/refstr.c
	${GRAPHVIZSRC_DIRS}/lib/agraph/scan.c
	${GRAPHVIZSRC_DIRS}/lib/agraph/subg.c
	${GRAPHVIZSRC_DIRS}/lib/agraph/utils.c
	${GRAPHVIZSRC_DIRS}/lib/agraph/write.c
	)

include_directories ( 
	#${GRAPHVIZSRC_DIRS}/lib/agraph
	#${GRAPHVIZSRC_DIRS}/lib/cdt
	${GRAPHVIZSRC_DIRS}
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
