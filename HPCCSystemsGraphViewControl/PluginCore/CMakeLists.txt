# Component: PluginCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for PluginCore
#####################################################

project( PluginCore ) 

set (	SRCS 
	#${FIREBREATHSRC_DIRS}/src/PluginCore/Mac/PluginWindowMacQuickDraw.cpp

	${FIREBREATHSRC_DIRS}/src/PluginCore/BrowserPlugin.cpp
	${FIREBREATHSRC_DIRS}/src/PluginCore/BrowserStream.cpp
	${FIREBREATHSRC_DIRS}/src/PluginCore/BrowserStreamManager.cpp
	${FIREBREATHSRC_DIRS}/src/PluginCore/DefaultBrowserStreamHandler.cpp
	${FIREBREATHSRC_DIRS}/src/PluginCore/FactoryBase.cpp
	${FIREBREATHSRC_DIRS}/src/PluginCore/PluginCore.cpp
	#${FIREBREATHSRC_DIRS}/src/PluginCore/PluginEvent.cpp
	${FIREBREATHSRC_DIRS}/src/PluginCore/PluginEventSource.cpp
	#${FIREBREATHSRC_DIRS}/src/PluginCore/PluginWindow.cpp
	${FIREBREATHSRC_DIRS}/src/PluginCore/SimpleStreamHelper.cpp
	)

if (WIN32)
set (	OS_SRCS 
	${FIREBREATHSRC_DIRS}/src/PluginCore/win/KeyCodesWin.cpp
	${FIREBREATHSRC_DIRS}/src/PluginCore/win/WinMessageWindow.cpp
	)
else (WIN32)
set (	OS_SRCS 
	#${FIREBREATHSRC_DIRS}/src/PluginCore/X11/PluginWindowX11.cpp
	)
endif (WIN32)

include_directories ( 
	..
	../gen
	${FIREBREATHSRC_DIRS}/src/PluginCore
	${FIREBREATHSRC_DIRS}/src/PluginCore/PluginEvents
	${FIREBREATHSRC_DIRS}/src/ScriptingCore
	)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif ()

add_library ( PluginCore STATIC
	${SRCS} 
	${OS_SRCS} 
	)

add_dependencies (PluginCore
	NpapiCore
	)

target_link_libraries(PluginCore
	NpapiCore
	)

