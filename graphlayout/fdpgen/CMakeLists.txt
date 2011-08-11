# Component: fdpgen
#####################################################
# Description:
# ------------
#	 Cmake Input File for fdpgen
#####################################################

project( fdpgen )

set (	SRCS
	${EXTERNALS_DIRECTORY}/graphviz2/lib/fdpgen/clusteredges.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/fdpgen/comp.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/fdpgen/dbg.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/fdpgen/fdpinit.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/fdpgen/grid.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/fdpgen/layout.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/fdpgen/tlayout.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/fdpgen/xlayout.c
	)

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/lib/fdpgen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pack
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc
	${EXTERNALS_DIRECTORY}/graphviz2/lib/parse
	${EXTERNALS_DIRECTORY}/graphviz2
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( fdpgen STATIC
			${SRCS}
			)
target_link_libraries ( fdpgen
						common
						graph
						neatogen
	)


