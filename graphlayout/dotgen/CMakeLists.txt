# Component: dotgen
#####################################################
# Description:
# ------------
#	 Cmake Input File for dotgen
#####################################################

project( dotgen )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/dotgen/acyclic.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/aspect.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/class1.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/class2.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/cluster.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/compound.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/conc.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/decomp.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/dotinit.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/dotsplines.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/fastgr.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/flat.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/mincross.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/position.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/rank.c
	${GRAPHVIZSRC_DIRS}/lib/dotgen/sameport.c
	)

add_library ( dotgen STATIC
			${SRCS}
			)
target_link_libraries ( dotgen
						common
						xdot
						neatogen
	)
if ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( dotgen
		cgraph
		)
else ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( dotgen
		graph
		)
endif ( GRAPHVIZ_VER_2_30_1 )


