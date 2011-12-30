# Component: PluginCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for PluginCore
#####################################################

project( PluginCore ) 

set (	SRCS 
	#${FIREBREATHSRC_DIR}/src/PluginCore/Mac/PluginWindowMacQuickDraw.cpp

	${FIREBREATHSRC_DIR}/src/PluginCore/BrowserPlugin.cpp
	${FIREBREATHSRC_DIR}/src/PluginCore/BrowserStream.cpp
	${FIREBREATHSRC_DIR}/src/PluginCore/BrowserStreamManager.cpp
	${FIREBREATHSRC_DIR}/src/PluginCore/DefaultBrowserStreamHandler.cpp
	${FIREBREATHSRC_DIR}/src/PluginCore/FactoryBase.cpp
	${FIREBREATHSRC_DIR}/src/PluginCore/PluginCore.cpp
	#${FIREBREATHSRC_DIR}/src/PluginCore/PluginEvent.cpp
	${FIREBREATHSRC_DIR}/src/PluginCore/PluginEventSource.cpp
	#${FIREBREATHSRC_DIR}/src/PluginCore/PluginWindow.cpp
	${FIREBREATHSRC_DIR}/src/PluginCore/SimpleStreamHelper.cpp
	)

if (WIN32)
set (	OS_SRCS 
	${FIREBREATHSRC_DIR}/src/PluginCore/win/KeyCodesWin.cpp
	${FIREBREATHSRC_DIR}/src/PluginCore/win/WinMessageWindow.cpp
	)
else (WIN32)
set (	OS_SRCS 
	#${FIREBREATHSRC_DIR}/src/PluginCore/X11/PluginWindowX11.cpp
	)
endif (WIN32)

include_directories ( 
	..
	../gen
	${FIREBREATHSRC_DIR}/src/PluginCore
	${FIREBREATHSRC_DIR}/src/PluginCore/PluginEvents
	${FIREBREATHSRC_DIR}/src/ScriptingCore
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

