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
	${EXTERNALS_DIRECTORY}/agg/src/agg_arc.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_arrowhead.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_bezier_arc.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_bspline.cpp
	#${EXTERNALS_DIRECTORY}/agg/src/agg_color_rgba.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_curves.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_embedded_raster_fonts.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_gsv_text.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_image_filters.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_line_aa_basics.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_line_profile_aa.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_rounded_rect.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_sqrt_tables.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_trans_affine.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_trans_double_path.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_trans_single_path.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_trans_warp_magnifier.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_vcgen_bspline.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_vcgen_contour.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_vcgen_dash.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_vcgen_markers_term.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_vcgen_smooth_poly1.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_vcgen_stroke.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_vpgen_clip_polygon.cpp
	#${EXTERNALS_DIRECTORY}/agg/src/agg_vpgen_clip_polyline.cpp
	${EXTERNALS_DIRECTORY}/agg/src/agg_vpgen_segmentator.cpp

	${EXTERNALS_DIRECTORY}/agg/font_freetype/agg_font_freetype.cpp
	#${EXTERNALS_DIRECTORY}/agg/font_freetype/agg_font_freetype2.cpp

	${EXTERNALS_DIRECTORY}/agg/agg2d/agg2d.cpp
	)

	include_directories ( 
	${EXTERNALS_DIRECTORY}/agg/include
	${EXTERNALS_DIRECTORY}/agg/font_freetype
	${EXTERNALS_DIRECTORY}/agg/agg2d

	${EXTERNALS_DIRECTORY}/freetype2/include
	${EXTERNALS_DIRECTORY}/freetype2/include/freetype
	)

set (	SRCS_OS
	#${EXTERNALS_DIRECTORY}/agg/src/platform/win32/agg_platform_support.cpp
	${EXTERNALS_DIRECTORY}/agg/src/platform/win32/agg_win32_bmp.cpp
	)

if (WIN32)
set (	SRCS_OS
	#${EXTERNALS_DIRECTORY}/agg/src/platform/win32/agg_platform_support.cpp
	${EXTERNALS_DIRECTORY}/agg/src/platform/win32/agg_win32_bmp.cpp
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
	${EXTERNALS_DIRECTORY}/freetype2/objs/win32/vc2008/freetype239MT_D.lib
)
endif (WIN32)
