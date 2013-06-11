# Component: graphlayout
#####################################################
# Description:
# ------------
#	 Cmake Input File for graphlayout
#####################################################

project(graphlayout)

set ( GRAPHLAYOUTSRC_DIRS ${CMAKE_CURRENT_SOURCE_DIR} )

if ( GRAPHVIZSRC_DIR MATCHES ".*2\\.30\\.1$")
	set ( GRAPHVIZ_VER_2_30_1 TRUE )
else ( GRAPHVIZSRC_DIR MATCHES ".*2\\.30\\.1$")
	set ( GRAPHVIZ_VER_2_30_1 FALSE )
endif ( GRAPHVIZSRC_DIR MATCHES ".*2\\.30\\.1$")

# *********************************************************************

include_directories (
	${GRAPHLAYOUTSRC_DIRS}
	${GRAPHVIZSRC_DIRS}
	${GRAPHVIZSRC_DIRS}/lib/pathplan
	${GRAPHVIZSRC_DIRS}/lib/common
	${GRAPHVIZSRC_DIRS}/lib/gvc
	${GRAPHVIZSRC_DIRS}/lib/dotgen
	${GRAPHVIZSRC_DIRS}/lib/neatogen
	${GRAPHVIZSRC_DIRS}/lib/fdpgen
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen
	${GRAPHVIZSRC_DIRS}/lib/cdt
	${GRAPHVIZSRC_DIRS}/lib/twopigen
	${GRAPHVIZSRC_DIRS}/lib/circogen
	${GRAPHVIZSRC_DIRS}/lib/sparse
	${GRAPHVIZSRC_DIRS}/lib/xdot
	${GRAPHVIZSRC_DIRS}/lib/gd
	${GRAPHVIZSRC_DIRS}/lib/pack
	${GRAPHVIZSRC_DIRS}/lib/vpsc
	${GRAPHVIZSRC_DIRS}/lib/patchwork
	${Boost_INCLUDE_DIRS}
	)

if ( GRAPHVIZ_VER_2_30_1 )
	include_directories (
		${GRAPHVIZSRC_DIRS}/lib/cgraph
		${GRAPHVIZSRC_DIRS}/lib/label
		${GRAPHVIZSRC_DIRS}/lib/ingraphs
		${GRAPHVIZSRC_DIRS}/lib/ortho
		${GRAPHVIZSRC_DIRS}/libltdl
		)
else ( GRAPHVIZ_VER_2_30_1 )
	include_directories (
		${GRAPHVIZSRC_DIRS}/lib/graph
		)
endif ( GRAPHVIZ_VER_2_30_1 )

# *********************************************************************

set (	SRCS
	precompiled_headers.h
	precompiled_headers.cpp

	libagraph.cpp
	libagraph.h
	libagraphsp.h

	compat.h
	config.h
	)

# *********************************************************************

add_definitions(-DHAVE_CONFIG_H -DHAVE_SETMODE)

if(WIN32)
  add_definitions(-DMSWIN32 -D_UNICODE)
elseif(APPLE)
elseif(UNIX)
endif()

if (WITH_HPCC_RUNTIME)
	add_library ( graphlayout SHARED ${SRCS} )
else (WITH_HPCC_RUNTIME)
	add_library ( graphlayout STATIC ${SRCS} )
endif (WITH_HPCC_RUNTIME)
ADD_PRECOMPILED_HEADER(${PROJECT_NAME} "precompiled_headers.h" "precompiled_headers.cpp" SRCS)

# *********************************************************************

add_subdirectory (gvc)
set_property(TARGET gvc PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (cdt)
set_property(TARGET cdt PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (circogen)
set_property(TARGET circogen PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (common)
set_property(TARGET common PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (dotgen)
set_property(TARGET dotgen PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (fdpgen)
set_property(TARGET fdpgen PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (sfdpgen)
set_property(TARGET sfdpgen PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (gvplugin_core)
set_property(TARGET gvplugin_core PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (gvplugin_dot_layout)
set_property(TARGET gvplugin_dot_layout PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (gvplugin_neato_layout)
set_property(TARGET gvplugin_neato_layout PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (neatogen)
set_property(TARGET neatogen PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (osage)
set_property(TARGET osage PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (pack)
set_property(TARGET pack PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (patchwork)
set_property(TARGET patchwork PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (pathplan)
set_property(TARGET pathplan PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (twopigen)
set_property(TARGET twopigen PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (sparse)
set_property(TARGET sparse PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (xdot)
set_property(TARGET xdot PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (vpsc)
set_property(TARGET vpsc PROPERTY FOLDER "3rdParty/Graphviz")

if ( GRAPHVIZ_VER_2_30_1 )
	add_subdirectory (cgraph)
	set_property(TARGET cgraph PROPERTY FOLDER "3rdParty/Graphviz")
	add_subdirectory (ingraphs)
	set_property(TARGET ingraphs PROPERTY FOLDER "3rdParty/Graphviz")
	add_subdirectory (label)
	set_property(TARGET label PROPERTY FOLDER "3rdParty/Graphviz")
	add_subdirectory (ortho)
	set_property(TARGET gvortho PROPERTY FOLDER "3rdParty/Graphviz")
	if ( WIN32 )
		add_subdirectory (stubs)
		set_property(TARGET gvortho PROPERTY FOLDER "3rdParty/Graphviz")
	endif ( WIN32 )
else ( GRAPHVIZ_VER_2_30_1 )
	add_subdirectory (graph)
	set_property(TARGET graph PROPERTY FOLDER "3rdParty/Graphviz")
endif ( GRAPHVIZ_VER_2_30_1 )

target_link_libraries ( graphlayout
	cdt
	circogen
	common
	dotgen
	fdpgen
	sfdpgen
	gvc
	gvplugin_core
	gvplugin_dot_layout
	gvplugin_neato_layout
	neatogen
	osage
	pack
	patchwork
	pathplan
	sparse
	twopigen
	xdot
	vpsc
	)

if ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( graphlayout
		cgraph
		gvortho
		ingraphs
		label
		)
	if ( WIN32 )
		target_link_libraries ( graphlayout
			gts
			glib-2.0
			ltdl
			xml2
			zdll
			)
	endif ( WIN32 )
else ( GRAPHVIZ_VER_2_30_1 )
	target_link_libraries ( graphlayout
		graph
		)
endif ( GRAPHVIZ_VER_2_30_1 )

link_boost_library ( ${PROJECT_NAME} thread )
link_boost_library ( ${PROJECT_NAME} system )
if (Boost_MAJOR_VERSION GREATER 0 AND Boost_MINOR_VERSION GREATER 47)
    link_boost_library( ${PROJECT_NAME} chrono)
endif ()


# *********************************************************************

if (WITH_HPCC_RUNTIME)
	install ( TARGETS graphlayout RUNTIME DESTINATION bin LIBRARY DESTINATION lib )
endif (WITH_HPCC_RUNTIME)

