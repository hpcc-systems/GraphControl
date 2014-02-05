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

add_library ( xdot STATIC
			${SRCS} 
			)
target_link_libraries ( xdot 
	)


