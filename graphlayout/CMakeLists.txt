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

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common
#	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc
	${EXTERNALS_DIRECTORY}/graphviz2/lib/dotgen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/fdpgen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sfdpgen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2/lib/twopigen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/circogen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sparse
	${EXTERNALS_DIRECTORY}/graphviz2/lib/xdot
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sparse
	${EXTERNALS_DIRECTORY}/graphviz2
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


