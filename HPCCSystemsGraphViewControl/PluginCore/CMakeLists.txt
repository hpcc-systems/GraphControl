# Component: PluginCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for PluginCore
#####################################################

project( PluginCore ) 

set (	SRCS 
	#${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/Mac/PluginWindowMacQuickDraw.cpp

	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/BrowserPlugin.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/BrowserStream.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/BrowserStreamManager.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/DefaultBrowserStreamHandler.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/FactoryBase.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/PluginCore.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/PluginEvent.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/PluginEventSource.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/PluginWindow.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/SimpleStreamHelper.cpp
	)

if (WIN32)
set (	OS_SRCS 
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/win/KeyCodesWin.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/win/WinMessageWindow.cpp
	)
else (WIN32)
set (	OS_SRCS 
	#${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/X11/PluginWindowX11.cpp
	)
endif (WIN32)

include_directories ( 
	..
	../gen
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore/PluginEvents
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore
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

