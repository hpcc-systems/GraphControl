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

include_directories (
	${GRAPHVIZSRC_DIRS}/lib/sparse
	${GRAPHVIZSRC_DIRS}/lib/common
	${GRAPHVIZSRC_DIRS}
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


