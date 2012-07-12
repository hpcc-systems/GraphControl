# Component: gd
#####################################################
# Description:
# ------------
#	 Cmake Input File for gd
#####################################################

project( gd ) 

set (	SRCS 
	${GRAPHVIZSRC_DIRS}/lib/gd/gd.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gd_gd.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gd_gd2.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gd_gif_in.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gd_gif_out.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gd_io.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gd_io_dp.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gd_io_file.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gd_ss.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gd_jpeg.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gd_png.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gd_security.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gd_ss.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gd_topal.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gd_wbmp.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gdcache.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gdfontg.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gdfontl.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gdfontmb.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gdfonts.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gdfontt.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gdft.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gdfx.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gdhelpers.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gdkanji.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gdtables.c
	${GRAPHVIZSRC_DIRS}/lib/gd/gdxpm.c
	${GRAPHVIZSRC_DIRS}/lib/gd/wbmp.c
	)

include_directories ( 
	${GRAPHVIZSRC_DIRS}/lib/gd
	#${GRAPHVIZSRC_DIRS}/third-party/include
	${GRAPHVIZSRC_DIRS}/third-party/include/freetype2
	${GRAPHVIZSRC_DIRS}
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


