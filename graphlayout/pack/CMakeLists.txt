# Component: pack
#####################################################
# Description:
# ------------
#	 Cmake Input File for pack
#####################################################

project( pack )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/pack/ccomps.c
	${GRAPHVIZSRC_DIRS}/lib/pack/pack.c
	)

add_library ( pack STATIC
			${SRCS}
			)
target_link_libraries ( pack
						common
						xdot
	)


