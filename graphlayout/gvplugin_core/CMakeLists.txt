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
	${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_dot.c
	${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_fig.c
	${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_map.c
	${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_ps.c
	${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_svg.c
	${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_tk.c
	${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_vml.c

	${GRAPHVIZSRC_DIRS}/plugin/core/gvplugin_core.def
	)

if ( GRAPHVIZ_VER_2_30_1 )
	list ( APPEND SRCS
		${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_pic.c
		${GRAPHVIZSRC_DIRS}/plugin/core/gvrender_core_pov.c
	)
endif ( GRAPHVIZ_VER_2_30_1 )

add_library ( gvplugin_core STATIC
			${SRCS}
			)
target_link_libraries ( gvplugin_core
						common
						xdot
	)
if ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( gvplugin_core
		cgraph
		)
else ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( gvplugin_core
		graph
		)
endif ( GRAPHVIZ_VER_2_30_1 )


