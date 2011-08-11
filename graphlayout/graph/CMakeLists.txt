# Component: graph
#####################################################
# Description:
# ------------
#	 Cmake Input File for graph
#####################################################

project( graph )

set (	SRCS
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph/agxbuf.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph/attribs.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph/edge.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph/graph.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph/graphio.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph/lexer.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph/node.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph/parser.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph/refstr.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph/trie.c
	)

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2
	)

#ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32 -DNONDLL)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( graph STATIC
			${SRCS}
			)
target_link_libraries ( graph
						cdt
	)


