# Component: gvc
#####################################################
# Description:
# ------------
#	 Cmake Input File for gvc
#####################################################

project( gvc )

set (	SRCS
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc/gvc.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc/gvconfig.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc/gvcontext.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc/gvdevice.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc/gvevent.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc/gvjobs.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc/gvlayout.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc/gvloadimage.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc/gvplugin.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc/gvrender.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc/gvtextlayout.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc/gvusershape.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc/no_demand_loading.c
	)

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph
	${EXTERNALS_DIRECTORY}/graphviz2/third-party/include
	${EXTERNALS_DIRECTORY}/graphviz2
	)

#ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32 -DNONDLL)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( gvc STATIC
			${SRCS}
			)
target_link_libraries ( gvc
						common
						cdt
						graph
	)


