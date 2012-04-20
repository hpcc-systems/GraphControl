
# Component: npHPCCSystemsGraphViewControl
#####################################################
# Description:
# ------------
#	 Cmake Input File for npHPCCSystemsGraphViewControl
#####################################################

project( HPCCSystemsGraphViewControl )

# *********************************************************************

include_directories (
	gen
	../graphdb
	../graphrender
	${WTL_INCLUDE_DIR}/include
	${Boost_INCLUDE_DIRS}
	${AGGSRC_DIRS}/agg-2.4/include
	${FIREBREATH_INCLUDE_DIRS}
	)

if(WIN32)
elseif(APPLE)
elseif(UNIX)
include_directories (
	${GTK_INCLUDE_DIRS}
	)
endif()

# SRC *****************************************************************

set (	SRCS
	precompiled_headers.h

	Factory.cpp

	HPCCSystemsGraphViewControl.cpp
	HPCCSystemsGraphViewControl.h
	HPCCSystemsGraphViewControlAPI.cpp
	HPCCSystemsGraphViewControlAPI.h

	DotViewCommon.cpp
	DotViewCommon.h

	Version.h
	Version.cpp

	../config.h

	../npHPCCSystemsGraphViewControl.inf
	../install.rdf

	gen/FBControl.htm
#	index.htm
	)

# Win *****************************************************************

set (	SRCS_WIN
	gen/FBControl.rgs
	gen/FireBreathWin.def
	gen/firebreathWin.rc
	gen/FireBreathWin.rgs
	gen/FireBreathWin.idl

	DotViewWin.cpp
	DotViewWin.h
	)
set (	SRCS_WIN_NO_PRECOMPILED_HEADERS
	gen/FireBreathWin_i.c
	)

SOURCE_GROUP(Win FILES ${SRCS_WIN} ${SRCS_WIN_NO_PRECOMPILED_HEADERS})

# OSX *****************************************************************

set (	SRCS_APPLE
	)

SOURCE_GROUP(OSX FILES ${SRCS_APPLE})

# X11 *****************************************************************

set (	SRCS_UNIX
	DotViewX11.cpp
	DotViewX11.h
	)

SOURCE_GROUP(X11 FILES ${SRCS_UNIX})

# *********************************************************************

set (	SRCS_CMAKE
	../cmake/Modules/Externals.cmake
	../cmake/Modules/Utils.cmake
	../cmake/Modules/FindAGGSRC.cmake
	../cmake/Modules/FindFIREBREATH.cmake
	../cmake/Modules/FindGRAPHVIZSRC.cmake
	../cmake/Modules/FindWTL.cmake
	../README
	)

SOURCE_GROUP(CMake FILES ${SRCS_CMAKE})

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

add_definitions(-DUNICODE -D_UNICODE)

if(WIN32)
	add_definitions(-DHPCCSYSTEMSGRAPHVIEWCONTROL_EXPORTS)
elseif(APPLE)
elseif(UNIX)
endif()

set(SOURCES ${SRCS} ${SRCS_WIN} ${SRCS_APPLE} ${SRCS_UNIX} ${SRCS_CMAKE})
ADD_MSVC_PRECOMPILED_HEADER("precompiled_headers.h" "precompiled_headers.cpp" SOURCES)
add_library(HPCCSystemsGraphViewControl SHARED ${SOURCES} ${SRCS_WIN_NO_PRECOMPILED_HEADERS})

# *********************************************************************

if(WIN32)
elseif(APPLE)
elseif(UNIX)
	set(NPAPI_LINK_FLAGS "-Wl,--discard-all -Wl,-Bsymbolic -Wl,-z,defs -Wl")
endif()
set_target_properties ("HPCCSystemsGraphViewControl" PROPERTIES
       OUTPUT_NAME npHPCCSystemsGraphViewControl
       PROJECT_LABEL "HPCCSystemsGraphViewControl"
       LINK_FLAGS "${NPAPI_LINK_FLAGS}"
       PREFIX ""
	)

add_subdirectory(PluginAuto)
set_property(TARGET PluginAuto PROPERTY FOLDER "3rdParty/FireBreath Generated")

#  Libraries added twice to resolve circular references on linux (when using static linking).
target_link_libraries( HPCCSystemsGraphViewControl
	graphdb
	graphrender
	${FIREBREATH_LIBRARIES}
	PluginAuto
	${FIREBREATH_LIBRARIES}
	PluginAuto
	${Boost_LIBRARIES}
	)

if(WIN32)
	target_link_libraries( HPCCSystemsGraphViewControl
		wininet
		)
elseif(APPLE)
elseif(UNIX)
    set(LIBDL_LIBRARIES dl)
	target_link_libraries( HPCCSystemsGraphViewControl
		${GTK_LIBRARIES}
		${LIBDL_LIBRARIES}
		${CMAKE_THREAD_LIBS_INIT}
		)
endif()

# *********************************************************************

INSTALL(TARGETS HPCCSystemsGraphViewControl 
	RUNTIME DESTINATION bin COMPONENT PLUGIN
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
)
