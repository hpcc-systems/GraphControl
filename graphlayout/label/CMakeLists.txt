project( label )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/label/index.c
	${GRAPHVIZSRC_DIRS}/lib/label/node.c
	#${GRAPHVIZSRC_DIRS}/lib/label/nrtmain.c
	${GRAPHVIZSRC_DIRS}/lib/label/rectangle.c
	${GRAPHVIZSRC_DIRS}/lib/label/split.q.c
	${GRAPHVIZSRC_DIRS}/lib/label/xlabels.c
	)

add_library ( label STATIC
			${SRCS}
			)
target_link_libraries ( label
	)
