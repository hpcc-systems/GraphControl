
# Component: npHPCCSystemsGraphViewControl
#####################################################
# Description:
# ------------
#	 Cmake Input File for npHPCCSystemsGraphViewControl
#####################################################

project( HPCCSystemsGraphViewControl )

set (	SRCS
	Factory.cpp
	#GraphViewCtlView.cpp
	HPCCSystemsGraphViewControl.cpp
	HPCCSystemsGraphViewControlAPI.cpp

	DotViewCommon.cpp
	DotViewCommon.h

	gen/FBControl.htm
	)

if (WIN32)
set (	SRCS_OS
	gen/FBControl.rgs
	gen/FireBreathWin.def
	gen/firebreathWin.rc
	gen/firebreathWin.rgs

	gen/FireBreathWin_i.c
	gen/firebreathWin.idl

	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/win/dllmain.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/win/np_winmain.cpp

	DotViewWin.cpp
	DotViewWin.h
	)
else (WIN32)
set (	SRCS_OS
	x11_pixel_map.cpp

	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/X11/np_x11main.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/X11/NpapiPluginX11.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/X11/PluginWindowX11.cpp

	DotViewX11.cpp
	DotViewX11.h
	)
endif (WIN32)

include_directories (
	gen
	../graphdb
	../graphrender

	${FIREBREATH_INCLUDE_DIRS}/src/3rdParty/gecko-sdk/includes
	${FIREBREATH_INCLUDE_DIRS}/src/ActiveXCore
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiCore
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto
	${FIREBREATH_INCLUDE_DIRS}/src/config
	
	${WTL_INCLUDE_DIR}/include
	
	${AGG_INCLUDE_DIR}/include
	)

if (WIN32)
else (WIN32)
include_directories (
	${GTK_INCLUDE_DIRS}
	)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
endif (WIN32)

ADD_DEFINITIONS( -D_UNICODE )

if (WIN32)
	ADD_DEFINITIONS( -D_USRDLL -DHPCCSYSTEMSGRAPHVIEWCONTROL_EXPORTS)
else ()
endif ()

if (WIN32)
add_subdirectory ( ActiveXCore )
set_property(TARGET ActiveXCore  PROPERTY FOLDER "3rdParty/Firebreath Core")
endif (WIN32)
add_subdirectory ( NpapiCore )
set_property(TARGET NpapiCore  PROPERTY FOLDER "3rdParty/Firebreath Core")
add_subdirectory ( PluginCore )
set_property(TARGET PluginCore  PROPERTY FOLDER "3rdParty/Firebreath Core")
add_subdirectory ( PluginAuto )
set_property(TARGET PluginAuto  PROPERTY FOLDER "3rdParty/Firebreath Core")
add_subdirectory ( ScriptingCore )
set_property(TARGET ScriptingCore  PROPERTY FOLDER "3rdParty/Firebreath Core")

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif ()

IF( FREETYPE_FOUND )
    INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})
    LINK_LIBRARIES(${FREETYPE_LIBRARIES})
ENDIF ()

add_library ( HPCCSystemsGraphViewControl SHARED
	${SRCS}
	${SRCS_OS}
	)

if (UNIX)
set(NPAPI_LINK_FLAGS "-Wl,--discard-all -Wl,-Bsymbolic -Wl,-z,defs -Wl")
else (UNIX)
endif (UNIX)
set_target_properties ("HPCCSystemsGraphViewControl" PROPERTIES
       OUTPUT_NAME npHPCCSystemsGraphViewControl
       PROJECT_LABEL "HPCCSystemsGraphViewControl"
       LINK_FLAGS "${NPAPI_LINK_FLAGS}"
       PREFIX ""
	)

add_dependencies (HPCCSystemsGraphViewControl
	graphdb
	graphrender
	NpapiCore
	PluginCore
	PluginAuto
	ScriptingCore
	)

if (WIN32)
add_dependencies (HPCCSystemsGraphViewControl
	ActiveXCore
	)
endif (WIN32)

target_link_libraries( HPCCSystemsGraphViewControl
	graphdb
	graphrender
	NpapiCore
	PluginCore
	PluginAuto
	ScriptingCore
	)

if (WIN32)
target_link_libraries( HPCCSystemsGraphViewControl
	ActiveXCore
	)
else (WIN32)
target_link_libraries( HPCCSystemsGraphViewControl
	${GTK_LIBRARIES}
	)
endif (WIN32)
