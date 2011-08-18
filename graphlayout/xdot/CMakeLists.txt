# Component: xdot
#####################################################
# Description:
# ------------
#	 Cmake Input File for xdot
#####################################################

project( xdot ) 

set (	SRCS 
	${GRAPHVIZ_INCLUDE_DIRS}/lib/xdot/xdot.c
	)

include_directories ( 
	${GRAPHVIZ_INCLUDE_DIRS}/lib/xdot
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt
	${GRAPHVIZ_INCLUDE_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( xdot STATIC
			${SRCS} 
			)
target_link_libraries ( xdot 
	)


