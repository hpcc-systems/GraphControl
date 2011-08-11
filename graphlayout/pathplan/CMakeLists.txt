# Component: pathplan
#####################################################
# Description:
# ------------
#	 Cmake Input File for pathplan
#####################################################

project( pathplan )

set (	SRCS
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan/cvt.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan/inpoly.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan/route.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan/shortest.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan/shortestpth.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan/solvers.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan/triang.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan/util.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan/visibility.c
	)

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph
	${EXTERNALS_DIRECTORY}/graphviz2
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( pathplan STATIC
			${SRCS}
			)
target_link_libraries ( pathplan
	)


