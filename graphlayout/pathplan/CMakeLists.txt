# Component: pathplan
#####################################################
# Description:
# ------------
#	 Cmake Input File for pathplan
#####################################################

project( pathplan )

set (	SRCS
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan/cvt.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan/inpoly.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan/route.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan/shortest.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan/shortestpth.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan/solvers.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan/triang.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan/util.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan/visibility.c
	)

include_directories (
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph
	${GRAPHVIZ_INCLUDE_DIRS}
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


