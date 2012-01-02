
# Component: npHPCCSystemsGraphViewControl
#####################################################
# Description:
# ------------
#	 Cmake Input File for npHPCCSystemsGraphViewControl
#####################################################

project( HPCCSystemsGraphViewControl )

set (	SRCS
	precompiled_headers.h

	Factory.cpp

	HPCCSystemsGraphViewControl.cpp
	HPCCSystemsGraphViewControl.h
	HPCCSystemsGraphViewControlAPI.cpp
	HPCCSystemsGraphViewControlAPI.h

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
	gen/firebreathWin.idl

	DotViewWin.cpp
	DotViewWin.h
	)
set (	SRCS_NO_PRECOMPILED_HEADERS
	gen/FireBreathWin_i.c
	)
else (WIN32)
set (	SRCS_OS
	x11_pixel_map.cpp
	x11_pixel_map.h

	DotViewX11.cpp
	DotViewX11.h
	)
endif (WIN32)

include_directories (
	gen
	../graphdb
	../graphrender

	${FIREBREATH_INCLUDE_DIRS}
	
	${WTL_INCLUDE_DIR}/include
	
	${AGGSRC_DIRS}/agg-2.4/include
	${Boost_INCLUDE_DIRS}
	)

if (WIN32)
else (WIN32)
include_directories (
	${GTK_INCLUDE_DIRS}
	)
endif (WIN32)

ADD_DEFINITIONS( -DUNICODE -D_UNICODE )

if (WIN32)
	ADD_DEFINITIONS( -DHPCCSYSTEMSGRAPHVIEWCONTROL_EXPORTS)
else ()
endif ()

#if (WIN32)
#add_subdirectory ( ActiveXCore )
#set_property(TARGET ActiveXCore  PROPERTY FOLDER "3rdParty/Firebreath Core")
#endif (WIN32)
#add_subdirectory ( NpapiCore )
#set_property(TARGET NpapiCore  PROPERTY FOLDER "3rdParty/Firebreath Core")
#add_subdirectory ( PluginCore )
#set_property(TARGET PluginCore  PROPERTY FOLDER "3rdParty/Firebreath Core")
add_subdirectory ( PluginAuto )
set_property(TARGET PluginAuto  PROPERTY FOLDER "3rdParty/Firebreath Core")
#add_subdirectory ( ScriptingCore )
#set_property(TARGET ScriptingCore  PROPERTY FOLDER "3rdParty/Firebreath Core")

IF( FREETYPE_FOUND )
    INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})
    LINK_LIBRARIES(${FREETYPE_LIBRARIES})
ENDIF ()


set ( SOURCES ${SRCS} ${SRCS_OS} )
ADD_MSVC_PRECOMPILED_HEADER("precompiled_headers.h" "precompiled_headers.cpp" SOURCES)
add_library ( HPCCSystemsGraphViewControl SHARED ${SOURCES} ${SRCS_NO_PRECOMPILED_HEADERS})

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
	PluginAuto
	)

target_link_libraries( HPCCSystemsGraphViewControl
	graphdb
	graphrender
	${FIREBREATH_LIBRARIES}
	PluginAuto
	${FIREBREATH_LIBRARIES}
	PluginAuto
	${Boost_LIBRARIES}
	)

if (WIN32)
	target_link_libraries( HPCCSystemsGraphViewControl
		wininet
		)
else (WIN32)
    set(LIBDL_LIBRARIES dl)
	target_link_libraries( HPCCSystemsGraphViewControl
		${GTK_LIBRARIES}
		${LIBDL_LIBRARIES}
		${CMAKE_THREAD_LIBS_INIT}
		)
endif (WIN32)

if ( WIN32 )	
else ( WIN32 )	
install ( TARGETS HPCCSystemsGraphViewControl DESTINATION lib/mozilla/plugins )
endif ( WIN32 )	
