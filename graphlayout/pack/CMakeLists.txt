# Component: pack
#####################################################
# Description:
# ------------
#	 Cmake Input File for pack
#####################################################

project( pack )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/pack/ccomps.c
	${GRAPHVIZSRC_DIRS}/lib/pack/pack.c
	)

include_directories (
	${GRAPHVIZSRC_DIRS}/lib/pack
	${GRAPHVIZSRC_DIRS}/lib/common
	${GRAPHVIZSRC_DIRS}/lib/cgraph
	${GRAPHVIZSRC_DIRS}/lib/pathplan
	${GRAPHVIZSRC_DIRS}/lib/graph
	${GRAPHVIZSRC_DIRS}/lib/cdt
	${GRAPHVIZSRC_DIRS}/lib/neatogen
	${GRAPHVIZSRC_DIRS}/lib/gvc
	${GRAPHVIZSRC_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( pack STATIC
			${SRCS}
			)
target_link_libraries ( pack
						common
						xdot
	)


