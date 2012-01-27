project( ingraphs )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/ingraphs/ingraphs.c
	)

include_directories (
	${GRAPHVIZSRC_DIRS}/lib/ingraphs
	${GRAPHVIZSRC_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( ingraphs STATIC
			${SRCS}
			)
target_link_libraries ( ingraphs
	)


