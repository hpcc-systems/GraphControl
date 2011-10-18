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

include_directories (
	${GRAPHVIZSRC_DIRS}/lib/circogen
	${GRAPHVIZSRC_DIRS}/lib/common
	${GRAPHVIZSRC_DIRS}/lib/cgraph
	${GRAPHVIZSRC_DIRS}/lib/neatogen
	${GRAPHVIZSRC_DIRS}/lib/gvc
	${GRAPHVIZSRC_DIRS}/lib/pack
	${GRAPHVIZSRC_DIRS}/lib/gd
	${GRAPHVIZSRC_DIRS}/lib/cdt
	${GRAPHVIZSRC_DIRS}/lib/graph
	${GRAPHVIZSRC_DIRS}/lib/pathplan
	${GRAPHVIZSRC_DIRS}/lib/sparse
	${GRAPHVIZSRC_DIRS}
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


