project( glib-2.0 )

set (	SRCS
	../dummy.cpp
	)

add_library ( glib-2.0 STATIC
			${SRCS}
			)
