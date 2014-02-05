# Component: sfdpgen
#####################################################
# Description:
# ------------
#	 Cmake Input File for sfdpgen
#####################################################

project( sfdpgen )

set (	SRCS
	#${GRAPHVIZSRC_DIRS}/lib/sfdpgen/layout_similarity.c
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/LinkedList.c
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/LinkedList.h
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/Multilevel.c
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/Multilevel.h
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/post_process.c
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/post_process.h
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/PriorityQueue.c
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/PriorityQueue.h
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/QuadTree.c
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/QuadTree.h
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/sfdp.h
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/sfdpinit.c
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/sfdpinternal.h
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/sparse_solve.c
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/sparse_solve.h
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/spring_electrical.c
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen/spring_electrical.h
	)

if ( GRAPHVIZ_VER_2_30_1 )
	list ( APPEND SRCS
		${GRAPHVIZSRC_DIRS}/lib/sfdpgen/stress_model.c
		${GRAPHVIZSRC_DIRS}/lib/sfdpgen/stress_model.h
		${GRAPHVIZSRC_DIRS}/lib/sfdpgen/uniform_stress.c
		${GRAPHVIZSRC_DIRS}/lib/sfdpgen/uniform_stress.h
	)
endif ( GRAPHVIZ_VER_2_30_1 )

add_library ( sfdpgen STATIC
			${SRCS}
			)
target_link_libraries ( sfdpgen
						common
						neatogen
						pack
	)
if ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( sfdpgen
		cgraph
		)
else ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( sfdpgen
		graph
		)
endif ( GRAPHVIZ_VER_2_30_1 )


