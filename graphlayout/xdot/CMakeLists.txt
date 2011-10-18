# Component: xdot
#####################################################
# Description:
# ------------
#	 Cmake Input File for xdot
#####################################################

project( xdot ) 

set (	SRCS 
	${GRAPHVIZSRC_DIRS}/lib/xdot/xdot.c
	)

include_directories ( 
	${GRAPHVIZSRC_DIRS}/lib/xdot
	${GRAPHVIZSRC_DIRS}/lib/common
	${GRAPHVIZSRC_DIRS}/lib/cgraph
	${GRAPHVIZSRC_DIRS}/lib/cdt
	${GRAPHVIZSRC_DIRS}
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


