# Component: dotgen
#####################################################
# Description:
# ------------
#	 Cmake Input File for dotgen
#####################################################

project( dotgen )

set (	SRCS
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/acyclic.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/aspect.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/class1.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/class2.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/cluster.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/compound.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/conc.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/decomp.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/dotinit.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/dotsplines.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/fastgr.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/flat.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/mincross.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/position.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/rank.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen/sameport.c
	)

include_directories (
	${GRAPHVIZ_INCLUDE_DIRS}/lib/dotgen
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc
	${GRAPHVIZ_INCLUDE_DIRS}
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


