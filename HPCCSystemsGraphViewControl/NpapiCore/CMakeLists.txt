# Component: NpapiCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for NpapiCore
#####################################################

project( NpapiCore ) 

set (	SRCS 
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiCore/NpapiBrowserHost.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiCore/NpapiPlugin.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiCore/NpapiPluginModule.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiCore/NpapiPluginModule_NPP.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiCore/NpapiStream.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiCore/NpapiTypes.cpp

	${FIREBREATH_INCLUDE_DIRS}/src/NpapiCore/NPJavascriptObject.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiCore/NPObjectAPI.cpp
	)

if (WIN32)
set (	OS_SRCS 
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiCore/Win/NpapiBrowserHostAsyncWin.cpp
	)
else (WIN32)
set (	OS_SRCS 
	#${FIREBREATH_INCLUDE_DIRS}/src/NpapiCore/X11/NpapiCoreX11.cpp
	)
endif (WIN32)

include_directories ( 
	..
	../gen
	${FIREBREATH_INCLUDE_DIRS}/src/3rdParty/gecko-sdk/includes
	${FIREBREATH_INCLUDE_DIRS}/src/ActiveXPlugin
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiCore
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore
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



