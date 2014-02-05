# Component: twopigen
#####################################################
# Description:
# ------------
#	 Cmake Input File for twopigen
#####################################################

project( twopigen )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/twopigen/circle.c
	${GRAPHVIZSRC_DIRS}/lib/twopigen/twopiinit.c
	)

add_library ( twopigen STATIC
			${SRCS}
			)
target_link_libraries ( twopigen
						common
						neatogen
						pack
	)


