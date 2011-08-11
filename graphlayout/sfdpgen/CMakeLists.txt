# Component: sfdpgen
#####################################################
# Description:
# ------------
#	 Cmake Input File for sfdpgen
#####################################################

project( sfdpgen )

set (	SRCS
	#${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/layout_similarity.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/LinkedList.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/LinkedList.h
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/Multilevel.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/Multilevel.h
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/post_process.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/post_process.h
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/PriorityQueue.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/PriorityQueue.h
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/QuadTree.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/QuadTree.h
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/sfdp.h
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/sfdpinit.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/sfdpinternal.h
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/sparse_solve.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/sparse_solve.h
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/spring_electrical.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen/spring_electrical.h
	)

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pack
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc
	${EXTERNALS_DIRECTORY}/graphviz2/lib/parse
	${EXTERNALS_DIRECTORY}/graphviz2/lib/ingraphs
	${EXTERNALS_DIRECTORY}/graphviz2
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( sfdpgen STATIC
			${SRCS}
			)
target_link_libraries ( sfdpgen
						common
						graph
						neatogen
						pack
	)


