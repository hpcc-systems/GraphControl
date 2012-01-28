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
	${FIREBREATH_CURRENT_SOURCE_DIR}/Win/axmain.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/Win/axPluginObjects.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/Win/dllmain.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/Win/FireBreathWin.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/Win/np_winmain.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/Win/NpapiPluginWin.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/Win/PluginWindowlessWin.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/Win/PluginWindowWin.cpp
	)

SOURCE_GROUP(Win FILES ${SRCS_WIN})

# OSX *****************************************************************

set (	SRCS_APPLE
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/NpapiPluginMac.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/PluginEventMac.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/PluginWindowMac.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/FactoryDummiesMac.cpp
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/PluginEventMac.cpp
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/NpapiPluginMac.mm
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/PluginWindowMac.mm
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/np_macmain.cpp
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/PluginWindowMacCG.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/PluginWindowMacCG.cpp
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/KeyCodesCarbon.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/KeyCodesCarbon.cpp
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/PluginEventMacCarbon.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/PluginEventMacCarbon.cpp
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/KeyCodesCocoa.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/KeyCodesCocoa.cpp
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/PluginEventMacCocoa.h
		${FIREBREATH_CURRENT_SOURCE_DIR}/Mac/PluginEventMacCocoa.mm
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
