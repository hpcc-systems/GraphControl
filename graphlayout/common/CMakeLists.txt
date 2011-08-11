# Component: common
#####################################################
# Description:
# ------------
#	 Cmake Input File for common
#####################################################

project( common )

set (	SRCS
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/args.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/arrows.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/colxlate.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/emit.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/fontmetrics.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/geom.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/globals.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/htmllex.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/htmlparse.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/htmltable.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/input.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/labels.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/memory.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/ns.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/output.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/pointset.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/postproc.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/psusershape.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/routespl.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/shapes.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/splines.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/strcasecmp.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/strncasecmp.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/timing.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common/utils.c
	)

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/fdpgen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc
	${EXTERNALS_DIRECTORY}/graphviz2/lib/xdot
	${EXTERNALS_DIRECTORY}/graphviz2
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


