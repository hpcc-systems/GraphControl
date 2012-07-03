# Component: gvplugin_core
#####################################################
# Description:
# ------------
#	 Cmake Input File for gvplugin_core
#####################################################

project( gvplugin_core )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/plugin/core/gvloadimage_core.c
	${GRAPHVIZSRC_DIRS}/plugin/core/gvplugin_core.c
	${GRAPHVIZSRC_DIRS}/plugin/core/gvplugin_core.def
	${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_dot.c
	${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_fig.c
	${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_map.c
	${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_ps.c
	${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_svg.c
	${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_tk.c
	${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_vml.c
	)

include_directories (
	${GRAPHVIZSRC_DIRS}/plugin/core
	#${GRAPHVIZSRC_DIRS}/plugin/libltdl
	#${GRAPHVIZSRC_DIRS}/lib/agutil
	#${GRAPHVIZSRC_DIRS}/windows/lib/cdt
	${GRAPHVIZSRC_DIRS}/lib/graph
	${GRAPHVIZSRC_DIRS}/lib/vpsc
	${GRAPHVIZSRC_DIRS}/lib/vmalloc
	${GRAPHVIZSRC_DIRS}/lib/twopigen
	${GRAPHVIZSRC_DIRS}/lib/sparse
	${GRAPHVIZSRC_DIRS}/lib/sfio
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen
	${GRAPHVIZSRC_DIRS}/lib/rbtree
	${GRAPHVIZSRC_DIRS}/lib/pathplan
	${GRAPHVIZSRC_DIRS}/lib/common
	${GRAPHVIZSRC_DIRS}/lib/gvc
	${GRAPHVIZSRC_DIRS}/lib/cdt
	${GRAPHVIZSRC_DIRS}/lib/cgraph
	${GRAPHVIZSRC_DIRS}
	..
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


