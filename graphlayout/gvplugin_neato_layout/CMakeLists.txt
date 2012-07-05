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

include_directories (
	${GRAPHVIZSRC_DIRS}/plugin/neato_layout
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


