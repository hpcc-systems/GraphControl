# Component: cdt
#####################################################
# Description:
# ------------
#	 Cmake Input File for cdt
#####################################################

project( cdt )

set (	SRCS
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dttree.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dtclose.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dtdisc.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dtextract.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dtflatten.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dthash.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dtlist.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dtmethod.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dtopen.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dtrenew.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dtrestore.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dtsize.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dtstat.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dtstrhash.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dtview.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/dtwalk.c

	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt/cdt.def
	)

include_directories (
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt
	${GRAPHVIZ_INCLUDE_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( cdt STATIC
			${SRCS}
			)
target_link_libraries ( cdt
    )


