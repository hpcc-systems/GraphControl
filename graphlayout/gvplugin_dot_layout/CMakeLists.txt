# Component: gvplugin_dot_layout
#####################################################
# Description:
# ------------
#	 Cmake Input File for gvplugin_dot_layout
#####################################################

project( gvplugin_dot_layout )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/plugin/dot_layout/gvlayout_dot_layout.c
	${GRAPHVIZSRC_DIRS}/plugin/dot_layout/gvplugin_dot_layout.c
	${GRAPHVIZSRC_DIRS}/plugin/dot_layout/gvplugin_dot_layout.def
	)

add_library ( gvplugin_dot_layout STATIC
			${SRCS}
			)
target_link_libraries ( gvplugin_dot_layout
						dotgen
	)


