# Component: osage
#####################################################
# Description:
# ------------
#	 Cmake Input File for osage
#####################################################

project( osage )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/osage/osageinit.c
	)

add_library ( osage STATIC
			${SRCS}
			)
target_link_libraries ( osage
						common
						neatogen
	)


