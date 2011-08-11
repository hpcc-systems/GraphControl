# Component: circogen
#####################################################
# Description:
# ------------
#	 Cmake Input File for circogen
#####################################################

project( circogen )

set (	SRCS
	${EXTERNALS_DIRECTORY}/graphviz2/lib/circogen/block.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/circogen/blockpath.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/circogen/blocktree.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/circogen/circpos.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/circogen/circular.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/circogen/circularinit.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/circogen/deglist.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/circogen/edgelist.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/circogen/nodelist.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/circogen/nodeset.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/circogen/stack.c
	)

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/lib/circogen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pack
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sparse
	${EXTERNALS_DIRECTORY}/graphviz2
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


