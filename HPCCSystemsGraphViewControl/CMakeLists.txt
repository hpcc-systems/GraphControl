#/**********************************************************\ 
# 
# Auto-generated CMakeLists.txt for the HPCC Systems Graph View Control project
#
#\**********************************************************/

# Written to work with cmake 2.6
cmake_minimum_required (VERSION 2.6)
set (CMAKE_BACKWARDS_COMPATIBILITY 2.6)

Project ( ${PLUGIN_NAME} )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/Version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Version.h )

file (GLOB GENERAL RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    [^.]*.cpp
    [^.]*.h
    [^.]*.cmake
    )

include_directories(${PLUGIN_INCLUDE_DIRS}
    ${GTK_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../graphdb
    ${CMAKE_CURRENT_SOURCE_DIR}/../graphrender
    )

# Generated files are stored in ${GENERATED} by the project configuration
SET_SOURCE_FILES_PROPERTIES(
    ${GENERATED}
    PROPERTIES
        GENERATED 1
    )

SOURCE_GROUP(Generated FILES
    ${GENERATED}
    )

SET( SOURCES
    ${GENERAL}
    ${GENERATED}
    )

# This will include Win/projectDef.cmake, X11/projectDef.cmake, Mac/projectDef 
# depending on the platform
include_platform()

macro(optional_append _list _cond _item)
  if(${_cond})
    set(${_list} ${${_list}} ${_item})
  endif(${_cond})
endmacro(optional_append _list _cond _item)

if(NOT CPACK_GENERATOR)
    if(WIN32)
        option(CPACK_BINARY_NSIS         "Enable to build NSIS packages" ON)
        option(CPACK_BINARY_ZIP          "Enable to build ZIP packages" OFF)
    elseif(APPLE)
        option(CPACK_BINARY_BUNDLE       "Enable to build OSX bundles" OFF)
        option(CPACK_BINARY_DRAGNDROP    "Enable to build OSX Drag And Drop package" OFF)
        option(CPACK_BINARY_PACKAGEMAKER "Enable to build PackageMaker packages" ON)
        option(CPACK_BINARY_OSXX11       "Enable to build OSX X11 packages" OFF)
    elseif(UNIX)
        option(CPACK_BINARY_DEB          "Enable to build Debian packages" ON)
        option(CPACK_BINARY_RPM          "Enable to build RPM packages" OFF)
    endif()

    optional_append(CPACK_GENERATOR  CPACK_BINARY_NSIS         NSIS)
    optional_append(CPACK_GENERATOR  CPACK_BINARY_ZIP          ZIP)

    optional_append(CPACK_GENERATOR  CPACK_BINARY_BUNDLE       Bundle)
    optional_append(CPACK_GENERATOR  CPACK_BINARY_DRAGNDROP    DragNDrop)
    optional_append(CPACK_GENERATOR  CPACK_BINARY_PACKAGEMAKER PackageMaker)
    optional_append(CPACK_GENERATOR  CPACK_BINARY_OSXX11       OSXX11)

    optional_append(CPACK_GENERATOR  CPACK_BINARY_DEB          DEB)
    optional_append(CPACK_GENERATOR  CPACK_BINARY_RPM          RPM)
endif(NOT CPACK_GENERATOR)

set ( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${FB_PROJECTS_DIR}/cmake/Modules" )
include ( "${FB_PROJECTS_DIR}/cmake/Modules/Externals.cmake" )

add_subdirectory("${FB_PROJECTS_DIR}/agg" "agg")
set_property(TARGET agg PROPERTY FOLDER "3rdParty")
if(WIN32)
    add_definitions(-DXML_STATIC)
    add_subdirectory("${FB_PROJECTS_DIR}/expat" "expat")
    set_property(TARGET expat PROPERTY FOLDER "3rdParty")

    if (WITH_HPCC_RUNTIME)
        add_definitions(-DGRAPHLAYOUT_EXPORTS)
        add_definitions(-DGRAPHDB_EXPORTS)
        add_definitions(-DGRAPHRENDER_EXPORTS)
    else (WITH_HPCC_RUNTIME)
        add_definitions(-DGRAPHLAYOUT_STATIC)
        add_definitions(-DGRAPHDB_STATIC)
        add_definitions(-DGRAPHRENDER_STATIC)
    endif (WITH_HPCC_RUNTIME)
elseif(APPLE)
elseif(UNIX)
endif()

add_subdirectory ("${FB_PROJECTS_DIR}/graphlayout" "graphlayout")
add_subdirectory ("${FB_PROJECTS_DIR}/graphdb" "graphdb")
add_subdirectory ("${FB_PROJECTS_DIR}/graphrender" "graphrender")

target_link_libraries(${PROJECT_NAME}
    graphdb
    graphrender
    )
link_boost_library ( ${PROJECT_NAME} system )
link_boost_library ( ${PROJECT_NAME} date_time )
link_boost_library ( ${PROJECT_NAME} filesystem )
link_boost_library ( ${PROJECT_NAME} regex )

####  CPACK  ####
set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}_${FB_PLATFORM_ARCH_NAME}")

if ( "${HPCC_MATURITY}" STREQUAL "release" )
    set ( stagever "${HPCC_SEQUENCE}" )
else ()
    set ( stagever "${HPCC_SEQUENCE}${HPCC_MATURITY}" )
endif ()

if ( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug" )
    set ( stagever "${stagever}-Debug" )
endif ( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug" )

set ( CPACK_PACKAGE_NAME "hpccsystems-graphcontrol" )
set ( CPACK_PACKAGE_VERSION_MAJOR ${HPCC_MAJOR} )
set ( CPACK_PACKAGE_VERSION_MINOR ${HPCC_MINOR} )
set ( CPACK_PACKAGE_VERSION_PATCH ${HPCC_POINT}-${stagever} )
set ( CPACK_PACKAGE_DESCRIPTION_SUMMARY "HPCC Systems Graph Control." )

set ( CPACK_PACKAGE_CONTACT "HPCCSystems <ossdevelopment@lexisnexis.com>" )
set ( CPACK_DEBIAN_PACKAGE_MAINTAINER "HPCCSystems <ossdevelopment@lexisnexis.com>" )
set ( CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-dev (>=1.46.0), libboost-system-dev (>=1.46.0), libboost-thread-dev (>=1.46.0), libboost-filesystem-dev (>=1.46.0)")

set ( CPACK_RESOURCE_FILE_LICENSE "${FB_PROJECTS_DIR}/License.txt" )
set ( CPACK_RESOURCE_FILE_README "${FB_PROJECTS_DIR}/CPackReadMe.txt" )

if ( UNIX )
    set ( CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} )
elseif ( WIN32 )
    if ( "${FB_PLATFORM_ARCH_NAME}" EQUAL "x86_64" )
        set ( CPACK_NSIS_DISPLAY_NAME "Graph Control x64" )
        SET ( CPACK_NSIS_EXTRA_INSTALL_COMMANDS "  
            ExecWait '\\\"$SYSDIR\\\\regsvr32.exe\\\" /s \\\"$INSTDIR\\\\${PLUGIN_DIRECTORY}\\\\npHPCCSystemsGraphViewControl.dll\\\"'
        " )
        SET ( CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "  
            ExecWait '\\\"$SYSDIR\\\\regsvr32.exe\\\" /s /u \\\"$INSTDIR\\\\${PLUGIN_DIRECTORY}\\\\npHPCCSystemsGraphViewControl.dll\\\"'
        " )
    else ()
        set ( CPACK_NSIS_DISPLAY_NAME "Graph Control" )
        SET ( CPACK_NSIS_DISPLAY_NAME "Graph Control")
        SET ( CPACK_NSIS_EXTRA_INSTALL_COMMANDS "  
            RegDLL '$INSTDIR\\\\${PLUGIN_DIRECTORY}\\\\npHPCCSystemsGraphViewControl.dll'
        " )
        SET ( CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "  
            UnRegDLL '$INSTDIR\\\\${PLUGIN_DIRECTORY}\\\\npHPCCSystemsGraphViewControl.dll'
        " )
    endif ()
    file(STRINGS "${FB_PROJECTS_DIR}/../sign/passphrase.txt" PFX_PASSWORD LIMIT_COUNT 1)

    add_custom_target(SIGN 
        COMMAND signtool sign /f "${FB_PROJECTS_DIR}/../sign/hpcc_code_signing.pfx" /p "${PFX_PASSWORD}" /t "http://timestamp.verisign.com/scripts/timstamp.dll" "${CMAKE_BINARY_DIR}/${CPACK_PACKAGE_NAME}*.exe"
        COMMENT "Digital Signature"
    )
    add_dependencies(SIGN PACKAGE)
    set_property(TARGET SIGN PROPERTY FOLDER "CMakePredefinedTargets")
endif ( )

include ( CPack )
####  #####  ####
