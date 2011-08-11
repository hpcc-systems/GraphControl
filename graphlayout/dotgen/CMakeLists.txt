# Component: dotgen
#####################################################
# Description:
# ------------
#	 Cmake Input File for dotgen
#####################################################

project( dotgen )

set (	SRCS
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/acyclic.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/aspect.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/class1.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/class2.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/cluster.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/compound.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/conc.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/decomp.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/dotinit.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/dotsplines.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/fastgr.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/flat.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/mincross.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/position.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/rank.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen/sameport.c
	)

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc
	${EXTERNALS_DIRECTORY}/graphviz2
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


