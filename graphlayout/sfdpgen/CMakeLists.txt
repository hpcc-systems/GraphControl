# Component: sfdpgen
#####################################################
# Description:
# ------------
#	 Cmake Input File for sfdpgen
#####################################################

project( sfdpgen )

set (	SRCS
	#${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/layout_similarity.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/LinkedList.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/LinkedList.h
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/Multilevel.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/Multilevel.h
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/post_process.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/post_process.h
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/PriorityQueue.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/PriorityQueue.h
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/QuadTree.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/QuadTree.h
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/sfdp.h
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/sfdpinit.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/sfdpinternal.h
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/sparse_solve.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/sparse_solve.h
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/spring_electrical.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen/spring_electrical.h
	)

include_directories (
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pack
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc
	${GRAPHVIZ_INCLUDE_DIRS}/lib/parse
	${GRAPHVIZ_INCLUDE_DIRS}/lib/ingraphs
	${GRAPHVIZ_INCLUDE_DIRS}
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


