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
	${AGG_INCLUDE_DIRS}/src/agg_arc.cpp
	${AGG_INCLUDE_DIRS}/src/agg_arrowhead.cpp
	${AGG_INCLUDE_DIRS}/src/agg_bezier_arc.cpp
	${AGG_INCLUDE_DIRS}/src/agg_bspline.cpp
	#${AGG_INCLUDE_DIRS}/src/agg_color_rgba.cpp
	${AGG_INCLUDE_DIRS}/src/agg_curves.cpp
	${AGG_INCLUDE_DIRS}/src/agg_embedded_raster_fonts.cpp
	${AGG_INCLUDE_DIRS}/src/agg_gsv_text.cpp
	${AGG_INCLUDE_DIRS}/src/agg_image_filters.cpp
	${AGG_INCLUDE_DIRS}/src/agg_line_aa_basics.cpp
	${AGG_INCLUDE_DIRS}/src/agg_line_profile_aa.cpp
	${AGG_INCLUDE_DIRS}/src/agg_rounded_rect.cpp
	${AGG_INCLUDE_DIRS}/src/agg_sqrt_tables.cpp
	${AGG_INCLUDE_DIRS}/src/agg_trans_affine.cpp
	${AGG_INCLUDE_DIRS}/src/agg_trans_double_path.cpp
	${AGG_INCLUDE_DIRS}/src/agg_trans_single_path.cpp
	${AGG_INCLUDE_DIRS}/src/agg_trans_warp_magnifier.cpp
	${AGG_INCLUDE_DIRS}/src/agg_vcgen_bspline.cpp
	${AGG_INCLUDE_DIRS}/src/agg_vcgen_contour.cpp
	${AGG_INCLUDE_DIRS}/src/agg_vcgen_dash.cpp
	${AGG_INCLUDE_DIRS}/src/agg_vcgen_markers_term.cpp
	${AGG_INCLUDE_DIRS}/src/agg_vcgen_smooth_poly1.cpp
	${AGG_INCLUDE_DIRS}/src/agg_vcgen_stroke.cpp
	${AGG_INCLUDE_DIRS}/src/agg_vpgen_clip_polygon.cpp
	#${AGG_INCLUDE_DIRS}/src/agg_vpgen_clip_polyline.cpp
	${AGG_INCLUDE_DIRS}/src/agg_vpgen_segmentator.cpp

	${AGG_INCLUDE_DIRS}/font_freetype/agg_font_freetype.cpp
	#${AGG_INCLUDE_DIRS}/font_freetype/agg_font_freetype2.cpp

	${AGG_INCLUDE_DIRS}/agg2d/agg2d.cpp
	)

	include_directories ( 
	${AGG_INCLUDE_DIRS}/include
	${AGG_INCLUDE_DIRS}/font_freetype
	${AGG_INCLUDE_DIRS}/agg2d

	${FREETYPE_INCLUDE_DIR_freetype2}
	${FREETYPE_INCLUDE_DIR_freetype2}/freetype
	)

set (	SRCS_OS
	#${AGG_INCLUDE_DIRS}/src/platform/win32/agg_platform_support.cpp
	${AGG_INCLUDE_DIRS}/src/platform/win32/agg_win32_bmp.cpp
	)

if (WIN32)
set (	SRCS_OS
	#${AGG_INCLUDE_DIRS}/src/platform/win32/agg_platform_support.cpp
	${AGG_INCLUDE_DIRS}/src/platform/win32/agg_win32_bmp.cpp
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
ADD_DEFINITIONS( -D_USRDLL -DAGG_EXPORTS -DCOMPILED_FROM_DSP )
else ()
ADD_DEFINITIONS( -DHAVE_BCOPY )
endif ()

if (WIN32)
target_link_libraries ( agg 
	${FREETYPE_LIBRARY}
)
endif (WIN32)
