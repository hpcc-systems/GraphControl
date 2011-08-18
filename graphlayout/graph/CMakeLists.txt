# Component: graph
#####################################################
# Description:
# ------------
#	 Cmake Input File for graph
#####################################################

project( graph )

set (	SRCS
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph/agxbuf.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph/attribs.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph/edge.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph/graph.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph/graphio.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph/lexer.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph/node.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph/parser.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph/refstr.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph/trie.c
	)

include_directories (
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt
	${GRAPHVIZ_INCLUDE_DIRS}
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


