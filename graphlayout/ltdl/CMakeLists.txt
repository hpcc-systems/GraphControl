project( ltdl )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/libltdl/ltdl.c
	)

include_directories (
	${GRAPHVIZSRC_DIRS}/libltdl/libltdl
	${GRAPHVIZSRC_DIRS}/libltdl/loaders
	${GRAPHVIZSRC_DIRS}/libltdl/m4
	${GRAPHVIZSRC_DIRS}/libltdl
	${GRAPHVIZSRC_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( ltdl STATIC
			${SRCS}
			)
target_link_libraries ( ltdl
	)


