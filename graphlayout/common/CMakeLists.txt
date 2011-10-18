# Component: common
#####################################################
# Description:
# ------------
#	 Cmake Input File for common
#####################################################

project( common )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/common/args.c
	${GRAPHVIZSRC_DIRS}/lib/common/arrows.c
	${GRAPHVIZSRC_DIRS}/lib/common/colxlate.c
	${GRAPHVIZSRC_DIRS}/lib/common/emit.c
	${GRAPHVIZSRC_DIRS}/lib/common/fontmetrics.c
	${GRAPHVIZSRC_DIRS}/lib/common/geom.c
	${GRAPHVIZSRC_DIRS}/lib/common/globals.c
	${GRAPHVIZSRC_DIRS}/lib/common/htmllex.c
	${GRAPHVIZSRC_DIRS}/lib/common/htmlparse.c
	${GRAPHVIZSRC_DIRS}/lib/common/htmltable.c
	${GRAPHVIZSRC_DIRS}/lib/common/input.c
	${GRAPHVIZSRC_DIRS}/lib/common/labels.c
	${GRAPHVIZSRC_DIRS}/lib/common/memory.c
	${GRAPHVIZSRC_DIRS}/lib/common/ns.c
	${GRAPHVIZSRC_DIRS}/lib/common/output.c
	${GRAPHVIZSRC_DIRS}/lib/common/pointset.c
	${GRAPHVIZSRC_DIRS}/lib/common/postproc.c
	${GRAPHVIZSRC_DIRS}/lib/common/psusershape.c
	${GRAPHVIZSRC_DIRS}/lib/common/routespl.c
	${GRAPHVIZSRC_DIRS}/lib/common/shapes.c
	${GRAPHVIZSRC_DIRS}/lib/common/splines.c
	${GRAPHVIZSRC_DIRS}/lib/common/timing.c
	${GRAPHVIZSRC_DIRS}/lib/common/utils.c
	)
	
if ( WIN32 )	
set (	SRCS_WIN32
	${GRAPHVIZSRC_DIRS}/lib/common/strcasecmp.c
	${GRAPHVIZSRC_DIRS}/lib/common/strncasecmp.c
	)
endif ( WIN32 )
	

include_directories (
	${GRAPHVIZSRC_DIRS}/lib/common
	${GRAPHVIZSRC_DIRS}/lib/cdt
	${GRAPHVIZSRC_DIRS}/lib/cgraph
	${GRAPHVIZSRC_DIRS}/lib/fdpgen
	${GRAPHVIZSRC_DIRS}/lib/pathplan
	${GRAPHVIZSRC_DIRS}/lib/gd
	${GRAPHVIZSRC_DIRS}/lib/graph
	${GRAPHVIZSRC_DIRS}/lib/gvc
	${GRAPHVIZSRC_DIRS}/lib/xdot
	${GRAPHVIZSRC_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( common STATIC
			${SRCS}
			${SRCS_WIN32}
			)
target_link_libraries ( common
						gvc
						graph
	)


