# Component: xdot
#####################################################
# Description:
# ------------
#	 Cmake Input File for xdot
#####################################################

project( xdot ) 

set (	SRCS 
	${EXTERNALS_DIRECTORY}/graphviz2/lib/xdot/xdot.c
	)

include_directories ( 
	${EXTERNALS_DIRECTORY}/graphviz2/lib/xdot
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2
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


