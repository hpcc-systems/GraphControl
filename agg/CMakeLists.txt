# Component: agg
#####################################################
# Description:
# ------------
#	 Cmake Input File for agg
#####################################################

project( agg ) 
cmake_minimum_required ( VERSION 2.8 )

if (WIN32)
set (	DEFS 
	)
else (WIN32)
set (	DEFS 
	)
endif (WIN32)

set (	SRCS 
	${AGGSRC_DIRS}/agg-2.4/src/agg_arc.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_arrowhead.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_bezier_arc.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_bspline.cpp
	#${AGGSRC_DIRS}/agg-2.4/src/agg_color_rgba.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_curves.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_embedded_raster_fonts.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_gsv_text.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_image_filters.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_line_aa_basics.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_line_profile_aa.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_rounded_rect.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_sqrt_tables.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_trans_affine.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_trans_double_path.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_trans_single_path.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_trans_warp_magnifier.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_vcgen_bspline.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_vcgen_contour.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_vcgen_dash.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_vcgen_markers_term.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_vcgen_smooth_poly1.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_vcgen_stroke.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_vpgen_clip_polygon.cpp
	#${AGGSRC_DIRS}/agg-2.4/src/agg_vpgen_clip_polyline.cpp
	${AGGSRC_DIRS}/agg-2.4/src/agg_vpgen_segmentator.cpp

	${AGGSRC_DIRS}/agg-2.4/font_freetype/agg_font_freetype.cpp
	#${AGGSRC_DIRS}/font_freetype/agg_font_freetype2.cpp

	agg2d.cpp
	)

	include_directories ( 
	${AGGSRC_DIRS}/agg-2.4/include
	${AGGSRC_DIRS}/agg-2.4/font_freetype

	${FREETYPE_INCLUDE_DIR_freetype2}
	${FREETYPE_INCLUDE_DIR_freetype2}/freetype
	)

set (	SRCS_OS
	#${AGGSRC_DIRS}/agg-2.4/src/platform/win32/agg_platform_support.cpp
	${AGGSRC_DIRS}/agg-2.4/src/platform/win32/agg_win32_bmp.cpp
	)

if (WIN32)
set (	SRCS_OS
	#${AGGSRC_DIRS}/agg-2.4/src/platform/win32/agg_platform_support.cpp
	${AGGSRC_DIRS}/agg-2.4/src/platform/win32/agg_win32_bmp.cpp
	)
else (WIN32)
set (	SRCS_OS
	)
endif (WIN32)

add_library ( agg STATIC
	${DEFS} 
	${SRCS} 
	${SRCS_OS} 
	)

ADD_DEFINITIONS( -D_UNICODE -DAGG_USE_FREETYPE;-DAGG_USE_AGG2D;-DAGG2D_USE_FREETYPE )

if (WIN32)
ADD_DEFINITIONS( -DAGG_EXPORTS -DCOMPILED_FROM_DSP )
else ()
ADD_DEFINITIONS( -DHAVE_BCOPY )
endif ()

if (WIN32)
target_link_libraries ( agg 
	${FREETYPE_LIBRARY}
)
endif (WIN32)
