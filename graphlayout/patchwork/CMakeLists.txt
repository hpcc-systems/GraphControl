# Component: patchwork
#####################################################
# Description:
# ------------
#	 Cmake Input File for patchwork
#####################################################

project( patchwork )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/patchwork/patchwork.c
	${GRAPHVIZSRC_DIRS}/lib/patchwork/patchworkinit.c
	)

include_directories (
	${GRAPHVIZSRC_DIRS}/lib/patchwork
	${GRAPHVIZSRC_DIRS}/lib/common
	${GRAPHVIZSRC_DIRS}/lib/cgraph
	${GRAPHVIZSRC_DIRS}/lib/neatogen
	${GRAPHVIZSRC_DIRS}/lib/pack
	${GRAPHVIZSRC_DIRS}/lib/gvc
	${GRAPHVIZSRC_DIRS}/lib/gd
	${GRAPHVIZSRC_DIRS}/lib/cdt
	${GRAPHVIZSRC_DIRS}/lib/graph
	${GRAPHVIZSRC_DIRS}/lib/pathplan
	${GRAPHVIZSRC_DIRS}/lib/sparse
	${GRAPHVIZSRC_DIRS}/lib/fdpgen
	${GRAPHVIZSRC_DIRS}
	..
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( patchwork STATIC
			${SRCS}
			)
target_link_libraries ( patchwork
						common
						xdot
	)


