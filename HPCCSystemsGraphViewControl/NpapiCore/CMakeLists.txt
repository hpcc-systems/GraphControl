# Component: NpapiCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for NpapiCore
#####################################################

project( NpapiCore ) 

set (	SRCS 
	${FIREBREATHSRC_DIRS}/src/NpapiCore/NpapiBrowserHost.cpp
	${FIREBREATHSRC_DIRS}/src/NpapiCore/NpapiPlugin.cpp
	${FIREBREATHSRC_DIRS}/src/NpapiCore/NpapiPluginModule.cpp
	${FIREBREATHSRC_DIRS}/src/NpapiCore/NpapiPluginModule_NPP.cpp
	${FIREBREATHSRC_DIRS}/src/NpapiCore/NpapiStream.cpp
	${FIREBREATHSRC_DIRS}/src/NpapiCore/NpapiTypes.cpp

	${FIREBREATHSRC_DIRS}/src/NpapiCore/NPJavascriptObject.cpp
	${FIREBREATHSRC_DIRS}/src/NpapiCore/NPObjectAPI.cpp
	)

if (WIN32)
set (	OS_SRCS 
	${FIREBREATHSRC_DIRS}/src/NpapiCore/Win/NpapiBrowserHostAsyncWin.cpp
	)
else (WIN32)
set (	OS_SRCS 
	#${FIREBREATHSRC_DIRS}/src/NpapiCore/X11/NpapiCoreX11.cpp
	)
endif (WIN32)

include_directories ( 
	..
	../gen
	${FIREBREATHSRC_DIRS}/src/3rdParty/gecko-sdk/includes
	${FIREBREATHSRC_DIRS}/src/ActiveXPlugin
	${FIREBREATHSRC_DIRS}/src/NpapiCore
	${FIREBREATHSRC_DIRS}/src/ScriptingCore
	${FIREBREATHSRC_DIRS}/src/PluginCore
	)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif ()

add_library ( NpapiCore STATIC
	${SRCS} 
	${OS_SRCS} 
	)

if (UNIX)
    # Link with libdl on Mac and X11
    set(LIBDL_LIBRARIES dl)
endif()

target_link_libraries(NpapiCore
    #${CMAKE_THREAD_LIBS_INIT}
    ${LIBDL_LIBRARIES}
    )

target_link_libraries(NpapiCore
	PluginCore
	)



