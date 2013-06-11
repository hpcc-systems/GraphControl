# Component: circogen
#####################################################
# Description:
# ------------
#	 Cmake Input File for circogen
#####################################################

project( circogen )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/circogen/block.c
	${GRAPHVIZSRC_DIRS}/lib/circogen/blockpath.c
	${GRAPHVIZSRC_DIRS}/lib/circogen/blocktree.c
	${GRAPHVIZSRC_DIRS}/lib/circogen/circpos.c
	${GRAPHVIZSRC_DIRS}/lib/circogen/circular.c
	${GRAPHVIZSRC_DIRS}/lib/circogen/circularinit.c
	${GRAPHVIZSRC_DIRS}/lib/circogen/deglist.c
	${GRAPHVIZSRC_DIRS}/lib/circogen/edgelist.c
	${GRAPHVIZSRC_DIRS}/lib/circogen/nodelist.c
	${GRAPHVIZSRC_DIRS}/lib/circogen/nodeset.c
	#${GRAPHVIZSRC_DIRS}/lib/circogen/stack.c
	)

add_library ( circogen STATIC
			${SRCS}
			)
target_link_libraries ( circogen
						common
						neatogen
						pack
	)
if ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( circogen
		cgraph
		)
else ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( circogen
		graph
		)
endif ( GRAPHVIZ_VER_2_30_1 )


