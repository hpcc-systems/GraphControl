# Component: cgraph
#####################################################
# Description:
# ------------
#	 Cmake Input File for cgraph
#####################################################

project( cgraph ) 

set (	SRCS 
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/agerror.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/agxbuf.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/apply.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/attr.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/cgraph.def
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/edge.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/flatten.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/graph.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/id.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/imap.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/io.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/mem.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/node.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/obj.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/pend.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/rec.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/refstr.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/subg.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/utils.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph/write.c
	)

include_directories ( 
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common
	${EXTERNALS_DIRECTORY}/graphviz2
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


