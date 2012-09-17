project ( GraphControl )
cmake_minimum_required (VERSION 2.6)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/" ${CMAKE_MODULE_PATH})

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
	set ( ARCH64BIT 1 )
else ()
	set ( ARCH64BIT 0 )
endif ()
message ("-- 64bit architecture is ${ARCH64BIT}")
##################################################################

# Build tag generation

set ( HPCC_MAJOR 6 )
set ( HPCC_MINOR 8 )
set ( HPCC_POINT 5 )
set ( HPCC_BUILD 0 )
set ( HPCC_VERSION ${HPCC_MAJOR}.${HPCC_MINOR}.${HPCC_POINT}.${HPCC_BUILD} )

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
  )

configure_file (
  "${PROJECT_SOURCE_DIR}/install.rdf.in"
  "${PROJECT_SOURCE_DIR}/install.rdf"
  )

configure_file (
  "${PROJECT_SOURCE_DIR}/npHPCCSystemsGraphViewControl.inf.in"
  "${PROJECT_SOURCE_DIR}/npHPCCSystemsGraphViewControl.inf"
  )
##################################################################

option(WITH_STATIC_RUNTIME "Build with static runtimes" OFF)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Location of BIN files")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Location of LIB files")
if (WIN32)
elseif(APPLE)
elseif(UNIX)
	option(WITH_BUILD_TARGET_IN_PLUGINS_FOLDER "Build directly into $HOME/.mozilla/plugins" OFF)
	if (WITH_BUILD_TARGET_IN_PLUGINS_FOLDER)
		set(EXECUTABLE_OUTPUT_PATH "~/.mozilla/plugins")
		set(LIBRARY_OUTPUT_PATH "~/.mozilla/plugins")
	endif()
endif()

include ( "${CMAKE_SOURCE_DIR}/cmake/Modules/Utils.cmake" )
include ( "${CMAKE_SOURCE_DIR}/cmake/Modules/Externals.cmake" )

if (WIN32)
	add_definitions(-DFB_WIN=1 -DXP_WIN=1 -D_CRT_SECURE_NO_WARNINGS)
    if (WITH_STATIC_RUNTIME)
        message("-- Building with static runtimes")
		add_definitions(-DSTATIC_LIB)
	else (WITH_STATIC_RUNTIME)
        message("-- Building with dynamic runtimes")
	endif (WITH_STATIC_RUNTIME)
    foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
            CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
	    if (WITH_STATIC_RUNTIME)
		    if(${flag_var} MATCHES "/MD")
			    string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
			endif()
		else()
		    if(${flag_var} MATCHES "/MT")
			    string(REGEX REPLACE "/MT" "/MD" ${flag_var} "${${flag_var}}")
			endif()
		endif()
    endforeach(flag_var)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D BOOST_ALL_NO_LIB=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D BOOST_ALL_NO_LIB=1")
elseif(APPLE)
	add_definitions(-DFB_MACOSX=1)
elseif(UNIX)
	add_definitions(-DFB_X11=1 -DXP_UNIX=1)
	find_package(PkgConfig)

	# GTK is required for XEmbed to work
	if (NOT GTK_INCLUDE_DIRS)
		pkg_check_modules(GTK REQUIRED gtk+-2.0)
		set (GTK_INCLUDE_DIRS ${GTK_INCLUDE_DIRS} CACHE INTERNAL "GTK include dirs")
		set (GTK_LIBRARIES ${GTK_LIBRARIES} CACHE INTERNAL "GTK include dirs")
		set (GTK_LIBRARY_DIRS ${GTK_LIBRARY_DIRS} CACHE INTERNAL "GTK include dirs")
		set (GTK_LDFLAGS ${GTK_LDFLAGS} CACHE INTERNAL "GTK include dirs")
	endif()

	set(gecko_defs -DXP_UNIX)
    set(fPIC_flag "-fPIC")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${gecko_defs} ${fPIC_flag}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${gecko_defs} ${fPIC_flag}")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(agg)
set_property(TARGET agg PROPERTY FOLDER "3rdParty")
if(WIN32)
	add_definitions(-DXML_STATIC)
	add_subdirectory(expat)
	set_property(TARGET expat PROPERTY FOLDER "3rdParty")
elseif(APPLE)
elseif(UNIX)
endif()

if(WIN32)
elseif(APPLE)
elseif(UNIX)
	set(PLUGIN_DIRECTORY "lib/mozilla/plugins" CACHE STRING "Directory to install Firefox plugin to")
endif()

##################################################################

add_subdirectory (graphlayout)
add_subdirectory (graphdb)
add_subdirectory (graphrender)
add_subdirectory (HPCCSystemsGraphViewControl)

##################################################################

if(WIN32)
	set ( CPACK_SOURCE_GENERATOR NSIS )
	if ( NOT WITH_STATIC_RUNTIME )
		include ( InstallRequiredSystemLibraries )
		INSTALL(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
		DESTINATION ${CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION}
		COMPONENT PLUGIN)
	endif ( NOT WITH_STATIC_RUNTIME )
elseif(APPLE)
elseif(UNIX)
  set ( CPACK_SOURCE_GENERATOR DEB )
endif()

set ( CPACK_RPM_COMPONENT_INSTALL )
set ( CPACK_COMPONENTS_ALL PLUGIN )
set ( CPACK_COMPONENT_PLUGIN_DISPLAY_NAME "Graph Control" )
set ( CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\hpccsystems.com" )
set ( CPACK_PACKAGE_CONTACT "HPCCSystems <ossdevelopment@lexisnexis.com>" )
set ( CPACK_PACKAGE_NAME "hpccsystems-graphcontrol")
set ( CPACK_PACKAGE_VENDOR "HPCC Systems" )
if ( ${ARCH64BIT} EQUAL 1 )
  set ( CPACK_NSIS_DISPLAY_NAME "Graph Control x64" )
else ()
  set ( CPACK_NSIS_DISPLAY_NAME "Graph Control" )
endif ()
set ( CPACK_PACKAGE_VERSION_MAJOR ${HPCC_MAJOR} )
set ( CPACK_PACKAGE_VERSION_MINOR ${HPCC_MINOR} )
set ( CPACK_PACKAGE_VERSION_PATCH "${HPCC_POINT}.${HPCC_BUILD}" )
set ( CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}" )
set ( CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/Liscence.txt" )
set ( CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README" )
set ( CPACK_PACKAGE_DESCRIPTION_SUMMARY "Browser plugin graph viewer." )
set ( CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_VENDOR}\\\\${CPACK_NSIS_DISPLAY_NAME} ${CPACK_PACKAGE_VERSION}")
set ( CPACK_PACKAGE_INSTALL_REGISTRY_KEY "${CPACK_NSIS_DISPLAY_NAME} ${CPACK_PACKAGE_VERSION}")
set ( CPACK_NSIS_DEFINES "
  !define MUI_STARTMENUPAGE_DEFAULTFOLDER \\\"${CPACK_PACKAGE_VENDOR}\\\\${CPACK_NSIS_DISPLAY_NAME}\\\"
  !define MUI_FINISHPAGE_NOAUTOCLOSE
  ")

if(WIN32)
	if ( ${ARCH64BIT} EQUAL 1 )
		SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "  
		ExecWait '\\\"$SYSDIR\\\\regsvr32.exe\\\" /s \\\"$INSTDIR\\\\${PLUGIN_DIRECTORY}\\\\npHPCCSystemsGraphViewControl.dll\\\"'
	")
		SET(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "  
		ExecWait '\\\"$SYSDIR\\\\regsvr32.exe\\\" /s /u \\\"$INSTDIR\\\\${PLUGIN_DIRECTORY}\\\\npHPCCSystemsGraphViewControl.dll\\\"'
	")
	else ()
		SET(CPACK_NSIS_DISPLAY_NAME "Graph Control")
		SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "  
			RegDLL '$INSTDIR\\\\${PLUGIN_DIRECTORY}\\\\npHPCCSystemsGraphViewControl.dll'
	")
	SET(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "  
		UnRegDLL '$INSTDIR\\\\${PLUGIN_DIRECTORY}\\\\npHPCCSystemsGraphViewControl.dll'
	")
	endif ()
	add_custom_target(SIGN 
		COMMAND signtool sign /f "${CMAKE_SOURCE_DIR}/hpcc_code_signing.pfx" /p "${PFX_PASSWORD}" /t "http://timestamp.verisign.com/scripts/timstamp.dll" "${CPACK_PACKAGE_NAME}*${CPACK_PACKAGE_VERSION}*.exe"
		COMMENT "Digital Signature"
	)
	add_dependencies(SIGN PACKAGE)
	set_property(TARGET SIGN PROPERTY FOLDER "CMakePredefinedTargets")
elseif(APPLE)
elseif(UNIX)
endif()

INCLUDE(CPack)

##################################################################

if(WIN32)
elseif(APPLE)
elseif(UNIX)
endif()
