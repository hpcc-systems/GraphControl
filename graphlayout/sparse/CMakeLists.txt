# Component: osage
#####################################################
# Description:
# ------------
#	 Cmake Input File for osage
#####################################################

project( sparse )

set (	SRCS
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sparse/SparseMatrix.c
	)

include_directories (
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sparse
	${GRAPHVIZ_INCLUDE_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( sparse STATIC
			${SRCS}
			)
target_link_libraries ( sparse
	)


