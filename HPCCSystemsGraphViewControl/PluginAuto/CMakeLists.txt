project( PluginAuto ) 

set( FIREBREATH_CURRENT_SOURCE_DIR ${FIREBREATH_SOURCE_DIR}/PluginAuto ) 
set (	SRCS 
	${FIREBREATH_CURRENT_SOURCE_DIR}/precompiled_headers.h
	${FIREBREATH_CURRENT_SOURCE_DIR}/null/NullLogger.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/PluginInfo.cpp
	)

if (WIN32)
set (	OS_SRCS 
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/dllmain.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/np_winmain.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/NpapiPluginWin.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/PluginWindowlessWin.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/PluginWindowWin.cpp

	${FIREBREATH_CURRENT_SOURCE_DIR}/win/axmain.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/axPluginObjects.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/FireBreathWin.cpp
	)
else (WIN32)
set (	OS_SRCS 
	${FIREBREATH_CURRENT_SOURCE_DIR}/X11/np_x11main.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/X11/NpapiPluginX11.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/X11/PluginWindowX11.cpp
	)
endif (WIN32)

include_directories ( 
	..
	../gen
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	)

set (SOURCES
	${SRCS} 
	${OS_SRCS} 
	)

ADD_MSVC_PRECOMPILED_HEADER("precompiled_headers.h" "${FIREBREATH_CURRENT_SOURCE_DIR}/precompiled_headers.cpp" SOURCES)
add_library ( PluginAuto STATIC ${SOURCES} )

if (WIN32)
    # psapi is needed to get the process info and check if WiX is calling
    # us; wish there was a better way to do this, but there doesn't seem to be
    target_link_libraries(${PROJECT_NAME} psapi)
endif()
