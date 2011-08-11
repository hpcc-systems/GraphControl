# Component: pack
#####################################################
# Description:
# ------------
#	 Cmake Input File for pack
#####################################################

project( pack )

set (	SRCS
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pack/ccomps.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pack/pack.c
	)

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pack
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc
	${EXTERNALS_DIRECTORY}/graphviz2
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


