# Component: patchwork
#####################################################
# Description:
# ------------
#	 Cmake Input File for patchwork
#####################################################

project( patchwork )

set (	SRCS
	${EXTERNALS_DIRECTORY}/graphviz2/lib/patchwork/patchwork.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/patchwork/patchworkinit.c
	)

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/lib/patchwork
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pack
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sparse
	${EXTERNALS_DIRECTORY}/graphviz2
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


