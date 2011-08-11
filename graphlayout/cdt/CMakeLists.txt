# Component: cdt
#####################################################
# Description:
# ------------
#	 Cmake Input File for cdt
#####################################################

project( cdt )

set (	SRCS
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dttree.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dtclose.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dtdisc.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dtextract.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dtflatten.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dthash.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dtlist.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dtmethod.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dtopen.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dtrenew.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dtrestore.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dtsize.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dtstat.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dtstrhash.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dtview.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/dtwalk.c

	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt/cdt.def
	)

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2
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


