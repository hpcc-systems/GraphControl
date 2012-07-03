project( vpsc )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/vpsc/block.cpp
	${GRAPHVIZSRC_DIRS}/lib/vpsc/block.h
	${GRAPHVIZSRC_DIRS}/lib/vpsc/blocks.cpp
	${GRAPHVIZSRC_DIRS}/lib/vpsc/blocks.h
	${GRAPHVIZSRC_DIRS}/lib/vpsc/constraint.cpp
	${GRAPHVIZSRC_DIRS}/lib/vpsc/constraint.h
	${GRAPHVIZSRC_DIRS}/lib/vpsc/csolve_VPSC.cpp
	${GRAPHVIZSRC_DIRS}/lib/vpsc/csolve_VPSC.h
	${GRAPHVIZSRC_DIRS}/lib/vpsc/generate-constraints.cpp
	${GRAPHVIZSRC_DIRS}/lib/vpsc/generate-constraints.h
	${GRAPHVIZSRC_DIRS}/lib/vpsc/remove_rectangle_overlap.cpp
	${GRAPHVIZSRC_DIRS}/lib/vpsc/remove_rectangle_overlap.h
	${GRAPHVIZSRC_DIRS}/lib/vpsc/solve_VPSC.cpp
	${GRAPHVIZSRC_DIRS}/lib/vpsc/solve_VPSC.h
	${GRAPHVIZSRC_DIRS}/lib/vpsc/variable.cpp
	${GRAPHVIZSRC_DIRS}/lib/vpsc/variable.h
	)

include_directories (
	${GRAPHVIZSRC_DIRS}/lib/vpsc
	${GRAPHVIZSRC_DIRS}
	..
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( vpsc STATIC
			${SRCS}
			)
target_link_libraries ( vpsc
	)


