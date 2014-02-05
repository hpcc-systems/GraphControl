# Component: pathplan
#####################################################
# Description:
# ------------
#	 Cmake Input File for pathplan
#####################################################

project( pathplan )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/pathplan/cvt.c
	${GRAPHVIZSRC_DIRS}/lib/pathplan/inpoly.c
	${GRAPHVIZSRC_DIRS}/lib/pathplan/route.c
	${GRAPHVIZSRC_DIRS}/lib/pathplan/shortest.c
	${GRAPHVIZSRC_DIRS}/lib/pathplan/shortestpth.c
	${GRAPHVIZSRC_DIRS}/lib/pathplan/solvers.c
	${GRAPHVIZSRC_DIRS}/lib/pathplan/triang.c
	${GRAPHVIZSRC_DIRS}/lib/pathplan/util.c
	${GRAPHVIZSRC_DIRS}/lib/pathplan/visibility.c
	)

add_library ( pathplan STATIC
			${SRCS}
			)
target_link_libraries ( pathplan
	)


