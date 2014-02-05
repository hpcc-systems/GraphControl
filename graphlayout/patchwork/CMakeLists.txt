# Component: patchwork
#####################################################
# Description:
# ------------
#	 Cmake Input File for patchwork
#####################################################

project( patchwork )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/patchwork/patchwork.c
	${GRAPHVIZSRC_DIRS}/lib/patchwork/patchworkinit.c
	)

if ( GRAPHVIZ_VER_2_30_1 )
	list ( APPEND SRCS
		${GRAPHVIZSRC_DIRS}/lib/patchwork/tree_map.c
	)
endif ( GRAPHVIZ_VER_2_30_1 )

add_library ( patchwork STATIC
			${SRCS}
			)
target_link_libraries ( patchwork
						common
						xdot
	)


