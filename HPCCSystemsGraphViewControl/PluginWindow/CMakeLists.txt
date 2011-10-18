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
	${FIREBREATHSRC_DIRS}/src/PluginWindow/Win/KeyCodesWin.cpp
	${FIREBREATHSRC_DIRS}/src/PluginWindow/Win/PluginWindowWin.cpp
	)
else (WIN32)
set (	OS_SRCS 
	${FIREBREATHSRC_DIRS}/src/PluginWindow/X11/PluginWindowX11.cpp
	)
endif (WIN32)

include_directories ( 
	..
	#../gen
	#${FIREBREATHSRC_DIRS}/src/PluginWindow
	#${FIREBREATHSRC_DIRS}/src/PluginWindow/PluginEvents
	#${FIREBREATHSRC_DIRS}/src/ScriptingCore
	)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif ()

add_library ( PluginWindow STATIC
	${SRCS} 
	${OS_SRCS} 
	)

