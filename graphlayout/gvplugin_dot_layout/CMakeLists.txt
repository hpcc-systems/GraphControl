# Component: gvplugin_dot_layout
#####################################################
# Description:
# ------------
#	 Cmake Input File for gvplugin_dot_layout
#####################################################

project( gvplugin_dot_layout )

set (	SRCS
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/dot_layout/gvlayout_dot_layout.c
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/dot_layout/gvplugin_dot_layout.c
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/dot_layout/gvplugin_dot_layout.def
	)

include_directories (
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/dot_layout
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/libltdl
	${GRAPHVIZ_INCLUDE_DIRS}/lib/agutil
	${GRAPHVIZ_INCLUDE_DIRS}/windows/lib/cdt
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/vpsc
	${GRAPHVIZ_INCLUDE_DIRS}/lib/vmalloc
	${GRAPHVIZ_INCLUDE_DIRS}/lib/twopigen
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sparse
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfio
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sfdpgen
	${GRAPHVIZ_INCLUDE_DIRS}/lib/rbtree
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph
	${GRAPHVIZ_INCLUDE_DIRS}
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


