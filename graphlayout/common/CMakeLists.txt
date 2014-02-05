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

if ( GRAPHVIZ_VER_2_30_1 )
	list ( APPEND SRCS
		${GRAPHVIZSRC_DIRS}/lib/common/ellipse.c
		${GRAPHVIZSRC_DIRS}/lib/common/intset.c
		${GRAPHVIZSRC_DIRS}/lib/common/intset.h
		${GRAPHVIZSRC_DIRS}/lib/common/taper.c
	)
endif ( GRAPHVIZ_VER_2_30_1 )
	
if ( WIN32 )	
set (	SRCS_WIN32
	${GRAPHVIZSRC_DIRS}/lib/common/strcasecmp.c
	${GRAPHVIZSRC_DIRS}/lib/common/strncasecmp.c
	)
endif ( WIN32 )

add_library ( common STATIC
			${SRCS}
			${SRCS_WIN32}
			)
target_link_libraries ( common
						gvc
						pathplan
	)
if ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( common
		cgraph
		label
		)
else ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( common
		graph
		)
endif ( GRAPHVIZ_VER_2_30_1 )

