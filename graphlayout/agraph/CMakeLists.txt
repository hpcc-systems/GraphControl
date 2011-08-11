# Component: agraph
#####################################################
# Description:
# ------------
#	 Cmake Input File for agraph
#####################################################

project( agraph ) 

set (	SRCS 
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/agerror.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/apply.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/attr.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/edge.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/flatten.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/grammar.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/graph.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/id.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/imap.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/io.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/mem.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/node.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/obj.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/pend.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/rec.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/refstr.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/scan.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/subg.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/utils.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph/write.c
	)

include_directories ( 
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agraph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2
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
