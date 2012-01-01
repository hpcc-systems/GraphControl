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

include_directories (
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen
	${GRAPHVIZSRC_DIRS}/lib/common
	${GRAPHVIZSRC_DIRS}/lib/cgraph
	${GRAPHVIZSRC_DIRS}/lib/neatogen
	${GRAPHVIZSRC_DIRS}/lib/gd
	${GRAPHVIZSRC_DIRS}/lib/cdt
	${GRAPHVIZSRC_DIRS}/lib/graph
	${GRAPHVIZSRC_DIRS}/lib/pathplan
	${GRAPHVIZSRC_DIRS}/lib/pack
	${GRAPHVIZSRC_DIRS}/lib/gvc
	${GRAPHVIZSRC_DIRS}/lib/sparse
	${GRAPHVIZSRC_DIRS}/lib/ingraphs
	${GRAPHVIZSRC_DIRS}
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


