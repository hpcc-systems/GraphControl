# Component: NpapiCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for NpapiCore
#####################################################

project( NpapiCore ) 

set (	SRCS 
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiCore/NpapiBrowserHost.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiCore/NpapiPlugin.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiCore/NpapiPluginModule.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiCore/NpapiPluginModule_NPP.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiCore/NpapiStream.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiCore/NpapiTypes.cpp

	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiCore/NPJavascriptObject.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiCore/NPObjectAPI.cpp
	)

if (WIN32)
set (	OS_SRCS 
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiCore/Win/NpapiBrowserHostAsyncWin.cpp
	)
else (WIN32)
set (	OS_SRCS 
	#${EXTERNALS_DIRECTORY}/firebreath/src/NpapiCore/X11/NpapiCoreX11.cpp
	)
endif (WIN32)

include_directories ( 
	..
	../gen
	${EXTERNALS_DIRECTORY}/firebreath/src/3rdParty/gecko-sdk/includes
	${EXTERNALS_DIRECTORY}/firebreath/src/ActiveXPlugin
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiCore
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore
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



