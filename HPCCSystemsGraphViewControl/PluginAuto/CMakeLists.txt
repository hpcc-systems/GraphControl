# Component: PluginCommon
#####################################################
# Description:
# ------------
#	 Cmake Input File for PluginCommon
#####################################################

project( PluginAuto ) 

set (	SRCS 
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginAuto/null/NullLogger.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginAuto/PluginInfo.cpp
	)

if (WIN32)
set (	OS_SRCS 
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginAuto/win/np_winmain.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginAuto/win/NpapiPluginWin.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginAuto/win/PluginWindowlessWin.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginAuto/win/PluginWindowWin.cpp

	${EXTERNALS_DIRECTORY}/firebreath/src/PluginAuto/win/axmain.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginAuto/win/axPluginObjects.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginAuto/win/FireBreathWin.cpp
	)
else (WIN32)
set (	OS_SRCS 
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginAuto/X11/np_x11main.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginAuto/X11/NpapiPluginX11.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginAuto/X11/PluginWindowX11.cpp
	)
endif (WIN32)

include_directories ( 
	..
	../gen
	)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif ()

add_library ( PluginAuto STATIC
	${SRCS} 
	${OS_SRCS} 
	)

if (WIN32)
    # psapi is needed to get the process info and check if WiX is calling
    # us; wish there was a better way to do this, but there doesn't seem to be
    target_link_libraries(${PROJECT_NAME} psapi)
endif()
