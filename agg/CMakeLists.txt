# Component: agg
#####################################################
# Description:
# ------------
#	 Cmake Input File for agg
#####################################################

project( agg ) 

# *********************************************************************

include_directories ( 
	${AGGSRC_DIRS}/agg-2.4/include
	${AGGSRC_DIRS}/agg-2.4/font_freetype

	${FREETYPE_INCLUDE_DIRS}
	)

if(WIN32)
elseif(APPLE)
	include_directories (
		${CARBON_INCLUDE_DIR}
		${QT_INCLUDE_DIR}
		)
elseif(UNIX)
endif()


# *********************************************************************

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

# Win *****************************************************************

set (	SRCS_WIN
	${AGGSRC_DIRS}/agg-2.4/src/platform/win32/agg_win32_bmp.cpp
	)

SOURCE_GROUP(Win FILES ${SRCS_WIN})

# OSX *****************************************************************

set (	SRCS_APPLE
	${AGGSRC_DIRS}/agg-2.4/src/platform/mac/agg_mac_pmap.cpp
	#${AGGSRC_DIRS}/agg-2.4/src/platform/mac/agg_platform_support.cpp
	)

SOURCE_GROUP(OSX FILES ${SRCS_APPLE})

# X11 *****************************************************************

set (	SRCS_UNIX
	)

SOURCE_GROUP(X11 FILES ${SRCS_UNIX})

# *********************************************************************

if(WIN32)
    set_source_files_properties(${SRCS_APPLE} PROPERTIES HEADER_FILE_ONLY 1)
    set_source_files_properties(${SRCS_UNIX} PROPERTIES HEADER_FILE_ONLY 1)
elseif(APPLE)
    set_source_files_properties(${SRCS_WIN} PROPERTIES HEADER_FILE_ONLY 1)
    set_source_files_properties(${SRCS_WIN_NO_PRECOMPILED_HEADERS} PROPERTIES HEADER_FILE_ONLY 1)
    set_source_files_properties(${SRCS_UNIX} PROPERTIES HEADER_FILE_ONLY 1)
elseif(UNIX)
    set_source_files_properties(${SRCS_WIN} PROPERTIES HEADER_FILE_ONLY 1)
    set_source_files_properties(${SRCS_WIN_NO_PRECOMPILED_HEADERS} PROPERTIES HEADER_FILE_ONLY 1)
    set_source_files_properties(${SRCS_APPLE} PROPERTIES HEADER_FILE_ONLY 1)
endif()

# *********************************************************************

add_definitions(-D_UNICODE -DAGG_USE_FREETYPE -DAGG_USE_AGG2D -DAGG2D_USE_FREETYPE)

if(WIN32)
	add_definitions(-DAGG_EXPORTS -DCOMPILED_FROM_DSP)
elseif(APPLE)
elseif(UNIX)
	add_definitions(-DHAVE_BCOPY)
endif()

# *********************************************************************

set(SOURCES ${SRCS} ${SRCS_WIN} ${SRCS_APPLE} ${SRCS_UNIX})
add_library(agg SHARED ${SOURCES})

# *********************************************************************

target_link_libraries ( agg 
	${FREETYPE_LIBRARY}
	)

if(WIN32)
elseif(APPLE)
target_link_libraries ( agg 
	${CARBON_FRAMEWORK}
	)
elseif(UNIX)
endif()


# *********************************************************************
