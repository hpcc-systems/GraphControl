# Component: libagraph
#####################################################
# Description:
# ------------
#	 Cmake Input File for libagraph
#####################################################

project( graphlayout )

set (	SRCS
	libagraph.cpp
	libagraph.h
	libagraphsp.h
	platform.h
	)

if (WIN32)
set (	SRCS 
	${SRCS}
	GraphLayout.rc
	)
endif ()

include_directories (
	${GRAPHVIZSRC_DIRS}/lib/graph
	${GRAPHVIZSRC_DIRS}/lib/pathplan
	${GRAPHVIZSRC_DIRS}/lib/common
#	${GRAPHVIZSRC_DIRS}/lib/cgraph
	${GRAPHVIZSRC_DIRS}/lib/pathplan
	${GRAPHVIZSRC_DIRS}/lib/gvc
	${GRAPHVIZSRC_DIRS}/lib/dotgen
	${GRAPHVIZSRC_DIRS}/lib/neatogen
	${GRAPHVIZSRC_DIRS}/lib/fdpgen
	${GRAPHVIZSRC_DIRS}/lib/sfdpgen
	${GRAPHVIZSRC_DIRS}/lib/graph
	${GRAPHVIZSRC_DIRS}/lib/cdt
	${GRAPHVIZSRC_DIRS}/lib/twopigen
	${GRAPHVIZSRC_DIRS}/lib/circogen
	${GRAPHVIZSRC_DIRS}/lib/sparse
	${GRAPHVIZSRC_DIRS}/lib/xdot
	${GRAPHVIZSRC_DIRS}/lib/gd
	${GRAPHVIZSRC_DIRS}/lib/sparse
	${GRAPHVIZSRC_DIRS}
	)

if (WIN32)
	ADD_DEFINITIONS( -D_USRDLL -DLIBAGRAPH_EXPORTS -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
#	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32)
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

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

add_library ( graphlayout SHARED ${SRCS} )

if (WIN32)
else (WIN32)
endif (WIN32)

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
	)

if ( WIN32 )	
else ( WIN32 )	
install ( TARGETS graphlayout DESTINATION lib/mozilla/plugins )
endif ( WIN32 )	
