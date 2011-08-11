# Component: PluginWindow
#####################################################
# Description:
# ------------
#	 Cmake Input File for PluginWindow
#####################################################

project( PluginWindow ) 

set (	SRCS 
	)

if (WIN32)
set (	OS_SRCS 
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginWindow/Win/KeyCodesWin.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginWindow/Win/PluginWindowWin.cpp
	)
else (WIN32)
set (	OS_SRCS 
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginWindow/X11/PluginWindowX11.cpp
	)
endif (WIN32)

include_directories ( 
	..
	#../gen
	#${EXTERNALS_DIRECTORY}/firebreath/src/PluginWindow
	#${EXTERNALS_DIRECTORY}/firebreath/src/PluginWindow/PluginEvents
	#${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore
	)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif ()

add_library ( PluginWindow STATIC
	${SRCS} 
	${OS_SRCS} 
	)

