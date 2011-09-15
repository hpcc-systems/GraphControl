# Component: fdpgen
#####################################################
# Description:
# ------------
#	 Cmake Input File for fdpgen
#####################################################

project( fdpgen )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/clusteredges.c
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/comp.c
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/dbg.c
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/fdpinit.c
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/grid.c
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/layout.c
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/tlayout.c
	${GRAPHVIZSRC_DIRS}/lib/fdpgen/xlayout.c
	)

include_directories (
	${GRAPHVIZSRC_DIRS}/lib/fdpgen
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
	${GRAPHVIZSRC_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( fdpgen STATIC
			${SRCS}
			)
target_link_libraries ( fdpgen
						common
						graph
						neatogen
	)


