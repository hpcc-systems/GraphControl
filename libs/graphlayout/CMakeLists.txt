# Component: graphlayout
#####################################################
# Description:
# ------------
#	 Cmake Input File for graphlayout
#####################################################

project(graphlayout)

# *********************************************************************

include_directories (
	${GRAPHVIZSRC_DIRS}/lib/graph
	${GRAPHVIZSRC_DIRS}/lib/pathplan
	${GRAPHVIZSRC_DIRS}/lib/common
#	${GRAPHVIZSRC_DIRS}/lib/agraph
#	${GRAPHVIZSRC_DIRS}/lib/cgraph
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
	${GRAPHVIZSRC_DIRS}
	${Boost_INCLUDE_DIRS}
	)

# *********************************************************************

set (	SRCS
	precompiled_headers.h

	libagraph.cpp
	libagraph.h
	libagraphsp.h
	)

# *********************************************************************

add_definitions(-DHAVE_CONFIG_H -DHAVE_SETMODE)
if(WIN32)
	add_definitions(-DLIBAGRAPH_EXPORTS -DMSWIN32 -D_UNICODE)
elseif(APPLE)
elseif(UNIX)
endif()

ADD_MSVC_PRECOMPILED_HEADER("precompiled_headers.h" "precompiled_headers.cpp" SRCS)
if (WITH_STATIC_RUNTIME)
	add_library ( graphlayout STATIC ${SRCS} )
else (WITH_STATIC_RUNTIME)
	add_library ( graphlayout SHARED ${SRCS} )
endif (WITH_STATIC_RUNTIME)

# *********************************************************************

add_subdirectory (gvc)
set_property(TARGET gvc PROPERTY FOLDER "3rdParty/Graphviz")
add_subdirectory (cdt)
set_property(TARGET cdt PROPERTY FOLDER "3rdParty/Graphviz")
#add_subdirectory (cgraph)
#set_property(TARGET cgraph PROPERTY FOLDER "3rdParty/Graphviz")
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
add_subdirectory (graph)
set_property(TARGET graph PROPERTY FOLDER "3rdParty/Graphviz")
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

target_link_libraries ( graphlayout
	cdt
#	cgraph
	circogen
	common
	dotgen
	fdpgen
	sfdpgen
	graph
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

# *********************************************************************

INSTALL(TARGETS graphlayout 
	RUNTIME DESTINATION bin COMPONENT PLUGIN
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
)
