# Component: gvplugin_dot_layout
#####################################################
# Description:
# ------------
#	 Cmake Input File for gvplugin_dot_layout
#####################################################

project( gvplugin_dot_layout )

set (	SRCS
	${EXTERNALS_DIRECTORY}/graphviz2/plugin/dot_layout/gvlayout_dot_layout.c
	${EXTERNALS_DIRECTORY}/graphviz2/plugin/dot_layout/gvplugin_dot_layout.c
	${EXTERNALS_DIRECTORY}/graphviz2/plugin/dot_layout/gvplugin_dot_layout.def
	)

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/plugin/dot_layout
	${EXTERNALS_DIRECTORY}/graphviz2/plugin/libltdl
	${EXTERNALS_DIRECTORY}/graphviz2/lib/agutil
	${EXTERNALS_DIRECTORY}/graphviz2/windows/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/vpsc
	${EXTERNALS_DIRECTORY}/graphviz2/lib/vmalloc
	${EXTERNALS_DIRECTORY}/graphviz2/lib/twopigen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sparse
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfio
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/rbtree
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph
	${EXTERNALS_DIRECTORY}/graphviz2
	)

#ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32 -DNONDLL)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( gvplugin_dot_layout STATIC
			${SRCS}
			)
target_link_libraries ( gvplugin_dot_layout
						dotgen
	)


