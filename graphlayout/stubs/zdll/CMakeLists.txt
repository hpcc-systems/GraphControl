project( zdll )

set (	SRCS
	../dummy.cpp
	)

add_library ( zdll STATIC
			${SRCS}
			)
