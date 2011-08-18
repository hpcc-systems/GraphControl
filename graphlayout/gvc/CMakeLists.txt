# Component: gvc
#####################################################
# Description:
# ------------
#	 Cmake Input File for gvc
#####################################################

project( gvc )

set (	SRCS
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc/gvc.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc/gvconfig.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc/gvcontext.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc/gvdevice.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc/gvevent.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc/gvjobs.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc/gvlayout.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc/gvloadimage.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc/gvplugin.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc/gvrender.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc/gvtextlayout.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc/gvusershape.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc/no_demand_loading.c
	)

include_directories (
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph
	${GRAPHVIZ_INCLUDE_DIRS}/third-party/include
	${GRAPHVIZ_INCLUDE_DIRS}
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


