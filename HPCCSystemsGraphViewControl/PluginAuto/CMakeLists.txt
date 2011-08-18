# Component: PluginCommon
#####################################################
# Description:
# ------------
#	 Cmake Input File for PluginCommon
#####################################################

project( PluginAuto ) 

set (	SRCS 
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/null/NullLogger.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/PluginInfo.cpp
	)

if (WIN32)
set (	OS_SRCS 
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/win/np_winmain.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/win/NpapiPluginWin.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/win/PluginWindowlessWin.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/win/PluginWindowWin.cpp

	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/win/axmain.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/win/axPluginObjects.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/win/FireBreathWin.cpp
	)
else (WIN32)
set (	OS_SRCS 
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/X11/np_x11main.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/X11/NpapiPluginX11.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/PluginAuto/X11/PluginWindowX11.cpp
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
