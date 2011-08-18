# Component: circogen
#####################################################
# Description:
# ------------
#	 Cmake Input File for circogen
#####################################################

project( circogen )

set (	SRCS
	${GRAPHVIZ_INCLUDE_DIRS}/lib/circogen/block.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/circogen/blockpath.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/circogen/blocktree.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/circogen/circpos.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/circogen/circular.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/circogen/circularinit.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/circogen/deglist.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/circogen/edgelist.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/circogen/nodelist.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/circogen/nodeset.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/circogen/stack.c
	)

include_directories (
	${GRAPHVIZ_INCLUDE_DIRS}/lib/circogen
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pack
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

add_library ( circogen STATIC
			${SRCS}
			)
target_link_libraries ( circogen
						common
						graph
						neatogen
						pack
	)


