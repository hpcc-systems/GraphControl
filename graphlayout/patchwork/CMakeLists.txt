# Component: patchwork
#####################################################
# Description:
# ------------
#	 Cmake Input File for patchwork
#####################################################

project( patchwork )

set (	SRCS
	${GRAPHVIZ_INCLUDE_DIRS}/lib/patchwork/patchwork.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/patchwork/patchworkinit.c
	)

include_directories (
	${GRAPHVIZ_INCLUDE_DIRS}/lib/patchwork
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pack
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sparse
	${GRAPHVIZ_INCLUDE_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( patchwork STATIC
			${SRCS}
			)
target_link_libraries ( patchwork
						common
						xdot
	)


