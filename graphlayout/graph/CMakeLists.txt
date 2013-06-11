# Component: graph
#####################################################
# Description:
# ------------
#	 Cmake Input File for graph
#####################################################

project( graph )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/graph/agxbuf.c
	${GRAPHVIZSRC_DIRS}/lib/graph/attribs.c
	${GRAPHVIZSRC_DIRS}/lib/graph/edge.c
	${GRAPHVIZSRC_DIRS}/lib/graph/graph.c
	${GRAPHVIZSRC_DIRS}/lib/graph/graphio.c
	${GRAPHVIZSRC_DIRS}/lib/graph/lexer.c
	${GRAPHVIZSRC_DIRS}/lib/graph/node.c
	${GRAPHVIZSRC_DIRS}/lib/graph/parser.c
	${GRAPHVIZSRC_DIRS}/lib/graph/refstr.c
	${GRAPHVIZSRC_DIRS}/lib/graph/trie.c
	)

add_library ( graph STATIC
			${SRCS}
			)
target_link_libraries ( graph
						cdt
	)


