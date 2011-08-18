# Component: common
#####################################################
# Description:
# ------------
#	 Cmake Input File for common
#####################################################

project( common )

set (	SRCS
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/args.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/arrows.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/colxlate.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/emit.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/fontmetrics.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/geom.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/globals.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/htmllex.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/htmlparse.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/htmltable.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/input.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/labels.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/memory.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/ns.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/output.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/pointset.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/postproc.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/psusershape.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/routespl.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/shapes.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/splines.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/strcasecmp.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/strncasecmp.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/timing.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common/utils.c
	)

include_directories (
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/fdpgen
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc
	${GRAPHVIZ_INCLUDE_DIRS}/lib/xdot
	${GRAPHVIZ_INCLUDE_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( common STATIC
			${SRCS}
			)
target_link_libraries ( common
						gvc
						graph
	)


