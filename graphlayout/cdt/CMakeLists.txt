# Component: cdt
#####################################################
# Description:
# ------------
#	 Cmake Input File for cdt
#####################################################

project( cdt )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/cdt/dttree.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dtclose.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dtdisc.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dtextract.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dtflatten.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dthash.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dtlist.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dtmethod.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dtopen.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dtrenew.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dtrestore.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dtsize.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dtstat.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dtstrhash.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dtview.c
	${GRAPHVIZSRC_DIRS}/lib/cdt/dtwalk.c

	${GRAPHVIZSRC_DIRS}/lib/cdt/cdt.def
	)

include_directories (
	${GRAPHVIZSRC_DIRS}/lib/cdt
	${GRAPHVIZSRC_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( cdt STATIC
			${SRCS}
			)
target_link_libraries ( cdt
    )


