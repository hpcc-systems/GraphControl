project( gvortho )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/ortho/maze.c
	${GRAPHVIZSRC_DIRS}/lib/ortho/maze.h
	${GRAPHVIZSRC_DIRS}/lib/ortho/ortho.c
	${GRAPHVIZSRC_DIRS}/lib/ortho/ortho.h
	${GRAPHVIZSRC_DIRS}/lib/ortho/partition.c
	${GRAPHVIZSRC_DIRS}/lib/ortho/partition.h
	${GRAPHVIZSRC_DIRS}/lib/ortho/rawgraph.c
	${GRAPHVIZSRC_DIRS}/lib/ortho/rawgraph.h
	${GRAPHVIZSRC_DIRS}/lib/ortho/sgraph.c
	${GRAPHVIZSRC_DIRS}/lib/ortho/sgraph.h
	${GRAPHVIZSRC_DIRS}/lib/ortho/structures.h
	${GRAPHVIZSRC_DIRS}/lib/ortho/trap.h
	${GRAPHVIZSRC_DIRS}/lib/ortho/trapezoid.c
	)

if ( GRAPHVIZ_VER_2_30_1 )
	list ( APPEND SRCS
		${GRAPHVIZSRC_DIRS}/lib/ortho/fPQ.c
		${GRAPHVIZSRC_DIRS}/lib/ortho/fPQ.h
	)
else ( GRAPHVIZ_VER_2_30_1 )
	list ( APPEND SRCS
		${GRAPHVIZSRC_DIRS}/lib/ortho/intset.c
		${GRAPHVIZSRC_DIRS}/lib/ortho/intset.h
	)
endif ( GRAPHVIZ_VER_2_30_1 )

add_library ( gvortho STATIC
			${SRCS}
			)
target_link_libraries ( gvortho
	)


