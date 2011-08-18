# Component: gd
#####################################################
# Description:
# ------------
#	 Cmake Input File for gd
#####################################################

project( gd ) 

set (	SRCS 
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd_gd.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd_gd2.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd_gif_in.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd_gif_out.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd_io.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd_io_dp.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd_io_file.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd_ss.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd_jpeg.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd_png.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd_security.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd_ss.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd_topal.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gd_wbmp.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gdcache.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gdfontg.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gdfontl.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gdfontmb.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gdfonts.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gdfontt.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gdft.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gdfx.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gdhelpers.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gdkanji.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gdtables.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/gdxpm.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd/wbmp.c
	)

include_directories ( 
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd
	${GRAPHVIZ_INCLUDE_DIRS}/third-party/include
	${GRAPHVIZ_INCLUDE_DIRS}/third-party/include/freetype2
	${GRAPHVIZ_INCLUDE_DIRS}
	)

# ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32 -DNONDLL)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( gd STATIC
			${SRCS} 
			)
target_link_libraries ( gd 
	)


