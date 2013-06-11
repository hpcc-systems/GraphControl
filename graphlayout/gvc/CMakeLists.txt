# Component: gvc
#####################################################
# Description:
# ------------
#	 Cmake Input File for gvc
#####################################################

project( gvc )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/gvc/gvc.c
	${GRAPHVIZSRC_DIRS}/lib/gvc/gvconfig.c
	${GRAPHVIZSRC_DIRS}/lib/gvc/gvcontext.c
	${GRAPHVIZSRC_DIRS}/lib/gvc/gvdevice.c
	${GRAPHVIZSRC_DIRS}/lib/gvc/gvevent.c
	${GRAPHVIZSRC_DIRS}/lib/gvc/gvjobs.c
	${GRAPHVIZSRC_DIRS}/lib/gvc/gvlayout.c
	${GRAPHVIZSRC_DIRS}/lib/gvc/gvloadimage.c
	${GRAPHVIZSRC_DIRS}/lib/gvc/gvplugin.c
	${GRAPHVIZSRC_DIRS}/lib/gvc/gvrender.c
	${GRAPHVIZSRC_DIRS}/lib/gvc/gvtextlayout.c
	${GRAPHVIZSRC_DIRS}/lib/gvc/gvusershape.c
	#${GRAPHVIZSRC_DIRS}/lib/gvc/no_demand_loading.c
	)

if ( WIN32 )
set (	WIN32_SRCS
	${GRAPHVIZSRC_DIRS}/lib/gvc/regex_win32.c
	)
endif ( WIN32 )

add_library ( gvc STATIC
			${SRCS}
			${WIN32_SRCS}
			)
target_link_libraries ( gvc
						common
						cdt
	)
if ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( gvc
		cgraph
		)
else ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( gvc
		graph
		)
endif ( GRAPHVIZ_VER_2_30_1 )


