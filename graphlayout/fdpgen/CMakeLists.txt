# Component: fdpgen
#####################################################
# Description:
# ------------
#	 Cmake Input File for fdpgen
#####################################################

project( fdpgen )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/clusteredges.c
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/comp.c
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/dbg.c
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/fdpinit.c
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/grid.c
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/layout.c
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/tlayout.c
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/xlayout.c
	)

add_library ( fdpgen STATIC
			${SRCS}
			)
target_link_libraries ( fdpgen
						common
						neatogen
	)
if ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( fdpgen
		cgraph
		)
else ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( fdpgen
		graph
		)
endif ( GRAPHVIZ_VER_2_30_1 )


