# Component: dotgen
#####################################################
# Description:
# ------------
#	 Cmake Input File for dotgen
#####################################################

project( dotgen )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/dotgen/acyclic.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/aspect.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/class1.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/class2.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/cluster.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/compound.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/conc.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/decomp.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/dotinit.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/dotsplines.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/fastgr.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/flat.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/mincross.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/position.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/rank.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/sameport.c
	)

include_directories (
	${GRAPHVIZSRC_DIRS}/lib/dotgen
	${GRAPHVIZSRC_DIRS}/lib/common
	${GRAPHVIZSRC_DIRS}/lib/cgraph
	${GRAPHVIZSRC_DIRS}/lib/gd
	${GRAPHVIZSRC_DIRS}/lib/cdt
	${GRAPHVIZSRC_DIRS}/lib/graph
	${GRAPHVIZSRC_DIRS}/lib/pathplan
	${GRAPHVIZSRC_DIRS}/lib/gvc
	${GRAPHVIZSRC_DIRS}/lib/ortho
	${GRAPHVIZSRC_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( dotgen STATIC
			${SRCS}
			)
target_link_libraries ( dotgen
						common
						graph
						xdot
						neatogen
	)


