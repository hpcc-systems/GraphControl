# Component: PluginCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for PluginCore
#####################################################

project( PluginCore ) 

set (	SRCS 
	#${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/Mac/PluginWindowMacQuickDraw.cpp

	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/BrowserPlugin.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/BrowserStream.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/BrowserStreamManager.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/DefaultBrowserStreamHandler.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/FactoryBase.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/PluginCore.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/PluginEvent.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/PluginEventSource.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/PluginWindow.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/SimpleStreamHelper.cpp
	)

if (WIN32)
set (	OS_SRCS 
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/win/KeyCodesWin.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/win/WinMessageWindow.cpp
	)
else (WIN32)
set (	OS_SRCS 
	#${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/X11/PluginWindowX11.cpp
	)
endif (WIN32)

include_directories ( 
	..
	../gen
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore/PluginEvents
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore
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

