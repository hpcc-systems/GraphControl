# Component: osage
#####################################################
# Description:
# ------------
#	 Cmake Input File for osage
#####################################################

project( sparse )

set (	SRCS
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sparse/SparseMatrix.c
	)

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sparse
	${EXTERNALS_DIRECTORY}/graphviz2
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


