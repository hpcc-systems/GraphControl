# Component: gd
#####################################################
# Description:
# ------------
#	 Cmake Input File for gd
#####################################################

project( gd ) 

set (	SRCS 
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd_gd.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd_gd2.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd_gif_in.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd_gif_out.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd_io.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd_io_dp.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd_io_file.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd_ss.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd_jpeg.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd_png.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd_security.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd_ss.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd_topal.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gd_wbmp.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gdcache.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gdfontg.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gdfontl.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gdfontmb.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gdfonts.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gdfontt.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gdft.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gdfx.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gdhelpers.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gdkanji.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gdtables.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/gdxpm.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd/wbmp.c
	)

include_directories ( 
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd
	${EXTERNALS_DIRECTORY}/graphviz2/third-party/include
	${EXTERNALS_DIRECTORY}/graphviz2/third-party/include/freetype2
	${EXTERNALS_DIRECTORY}/graphviz2
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


