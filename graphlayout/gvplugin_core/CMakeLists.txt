# Component: gvplugin_core
#####################################################
# Description:
# ------------
#	 Cmake Input File for gvplugin_core
#####################################################

project( gvplugin_core )

set (	SRCS
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/core/gvloadimage_core.c
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/core/gvplugin_core.c
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/core/gvplugin_core.def
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/core/gvrender_core_dot.c
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/core/gvrender_core_fig.c
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/core/gvrender_core_map.c
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/core/gvrender_core_ps.c
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/core/gvrender_core_svg.c
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/core/gvrender_core_tk.c
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/core/gvrender_core_vml.c
	)

include_directories (
	${GRAPHVIZ_INCLUDE_DIRS}/plugin/core
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

add_library ( gvplugin_core STATIC
			${SRCS}
			)
target_link_libraries ( gvplugin_core
						common
						graph
						xdot
	)


