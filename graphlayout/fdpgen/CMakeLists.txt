# Component: fdpgen
#####################################################
# Description:
# ------------
#	 Cmake Input File for fdpgen
#####################################################

project( fdpgen )

set (	SRCS
	${GRAPHVIZ_INCLUDE_DIRS}/lib/fdpgen/clusteredges.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/fdpgen/comp.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/fdpgen/dbg.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/fdpgen/fdpinit.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/fdpgen/grid.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/fdpgen/layout.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/fdpgen/tlayout.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/fdpgen/xlayout.c
	)

include_directories (
	${GRAPHVIZ_INCLUDE_DIRS}/lib/fdpgen
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pack
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc
	${GRAPHVIZ_INCLUDE_DIRS}/lib/parse
	${GRAPHVIZ_INCLUDE_DIRS}
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


