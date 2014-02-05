# Component: osage
#####################################################
# Description:
# ------------
#	 Cmake Input File for osage
#####################################################

project( sparse )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/sparse/SparseMatrix.c
	)

if ( GRAPHVIZ_VER_2_30_1 )
	list ( APPEND SRCS
		${GRAPHVIZSRC_DIRS}/lib/sparse/BinaryHeap.c
		${GRAPHVIZSRC_DIRS}/lib/sparse/general.c
		${GRAPHVIZSRC_DIRS}/lib/sparse/IntStack.c
	)
endif ( GRAPHVIZ_VER_2_30_1 )

add_library ( sparse STATIC
			${SRCS}
			)
target_link_libraries ( sparse
	)


