# Component: PluginAuto
#####################################################
# Description:
# ------------
#	 Cmake Input File for PluginAuto
#####################################################

project( PluginAuto ) 

# *********************************************************************

include_directories ( 
	..
	../gen
	${Boost_INCLUDE_DIRS}
	)

# SRC *****************************************************************

set( FIREBREATH_CURRENT_SOURCE_DIR ${FIREBREATH_SOURCE_DIR}/PluginAuto ) 
set (	SRCS 
	${FIREBREATH_CURRENT_SOURCE_DIR}/precompiled_headers.h
	${FIREBREATH_CURRENT_SOURCE_DIR}/null/NullLogger.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/PluginInfo.cpp
	)

# Win *****************************************************************

set (	SRCS_WIN
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/axmain.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/axPluginObjects.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/dllmain.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/FireBreathWin.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/np_winmain.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/NpapiPluginWin.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/PluginWindowlessWin.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/win/PluginWindowWin.cpp
	)

SOURCE_GROUP(Win FILES ${SRCS_WIN})

# OSX *****************************************************************

set (	SRCS_APPLE
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/NpapiPluginMac.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/PluginEventMac.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/PluginWindowMac.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/FactoryDummiesMac.cpp
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/PluginEventMac.cpp
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/NpapiPluginMac.mm
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/PluginWindowMac.mm
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/np_macmain.cpp
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/PluginWindowMacCG.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/PluginWindowMacCG.cpp
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/KeyCodesCarbon.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/KeyCodesCarbon.cpp
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/PluginEventMacCarbon.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/PluginEventMacCarbon.cpp
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/KeyCodesCocoa.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/KeyCodesCocoa.cpp
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/PluginEventMacCocoa.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/mac/PluginEventMacCocoa.mm
	)

SOURCE_GROUP(OSX FILES ${SRCS_APPLE})

# X11 *****************************************************************

set (	SRCS_UNIX
	${FIREBREATH_CURRENT_SOURCE_DIR}/X11/np_x11main.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/X11/NpapiPluginX11.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/X11/PluginWindowX11.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/X11/KeyCodesX11.cpp
	)

SOURCE_GROUP(X11 FILES ${SRCS_UNIX})

# *********************************************************************

if(WIN32)
    set_source_files_properties(${SRCS_APPLE} PROPERTIES HEADER_FILE_ONLY 1)
    set_source_files_properties(${SRCS_UNIX} PROPERTIES HEADER_FILE_ONLY 1)
elseif(APPLE)
    set_source_files_properties(${SRCS_WIN} PROPERTIES HEADER_FILE_ONLY 1)
    set_source_files_properties(${SRCS_WIN_NO_PRECOMPILED_HEADERS} PROPERTIES HEADER_FILE_ONLY 1)
    set_source_files_properties(${SRCS_UNIX} PROPERTIES HEADER_FILE_ONLY 1)
elseif(UNIX)
    set_source_files_properties(${SRCS_WIN} PROPERTIES HEADER_FILE_ONLY 1)
    set_source_files_properties(${SRCS_WIN_NO_PRECOMPILED_HEADERS} PROPERTIES HEADER_FILE_ONLY 1)
    set_source_files_properties(${SRCS_APPLE} PROPERTIES HEADER_FILE_ONLY 1)
endif()

# *********************************************************************

set(SOURCES ${SRCS} ${SRCS_WIN} ${SRCS_APPLE} ${SRCS_UNIX})
ADD_MSVC_PRECOMPILED_HEADER("precompiled_headers.h" "${FIREBREATH_CURRENT_SOURCE_DIR}/precompiled_headers.cpp" SOURCES)
add_library(PluginAuto STATIC ${SOURCES})

# *********************************************************************

if(WIN32)
    # psapi is needed to get the process info and check if WiX is calling
    # us; wish there was a better way to do this, but there doesn't seem to be
    target_link_libraries(${PROJECT_NAME} 
		psapi
		)
elseif(APPLE)
elseif(UNIX)
endif()

# *********************************************************************
