project( ingraphs )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/ingraphs/ingraphs.c
	)

add_library ( ingraphs STATIC
			${SRCS}
			)
target_link_libraries ( ingraphs
	)


