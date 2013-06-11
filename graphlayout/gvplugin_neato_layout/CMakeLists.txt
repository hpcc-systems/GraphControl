# Component: gvplugin_neato_layout
#####################################################
# Description:
# ------------
#	 Cmake Input File for gvplugin_neato_layout
#####################################################

project( gvplugin_neato_layout )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/plugin/neato_layout/gvlayout_neato_layout.c
	${GRAPHVIZSRC_DIRS}/plugin/neato_layout/gvplugin_neato_layout.c
	${GRAPHVIZSRC_DIRS}/plugin/neato_layout/gvplugin_neato_layout.def
	)

add_library ( gvplugin_neato_layout STATIC
			${SRCS}
			)
target_link_libraries ( gvplugin_neato_layout
						common
						neatogen
						osage
						patchwork
						circogen
						twopigen
						sfdpgen
						fdpgen
	)


