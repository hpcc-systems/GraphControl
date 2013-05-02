#/**********************************************************\ 
# 
# Auto-generated CMakeLists.txt for the HPCC Systems Graph View Control project
#
#\**********************************************************/

# Written to work with cmake 2.6
cmake_minimum_required (VERSION 2.6)
set (CMAKE_BACKWARDS_COMPATIBILITY 2.6)

Project ( ${PLUGIN_NAME} )

SET ( EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin/HPCCSystemsGraphViewControl" CACHE PATH "Location of BIN files" )
SET ( LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin/HPCCSystemsGraphViewControl" CACHE PATH "Location of LIB files" )

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
add_definitions( -DBOOST_ALL_NO_LIB )

add_subdirectory ("${FB_PROJECTS_DIR}/graphlayout" "graphlayout")
add_subdirectory ("${FB_PROJECTS_DIR}/graphdb" "graphdb")
add_subdirectory ("${FB_PROJECTS_DIR}/graphrender" "graphrender")
if (APPLE)
    add_subdirectory ("${FB_PROJECTS_DIR}/lib2" "lib2")
endif (APPLE)

target_link_libraries(${PROJECT_NAME}
    graphdb
    graphrender
    )
link_boost_library ( ${PROJECT_NAME} system )
link_boost_library ( ${PROJECT_NAME} date_time )
link_boost_library ( ${PROJECT_NAME} filesystem )
link_boost_library ( ${PROJECT_NAME} regex )

##############################################
# Build tag generation

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set ( ARCH64BIT 1 )
else ()
    set ( ARCH64BIT 0 )
endif ()
message ("-- 64bit architecture is ${ARCH64BIT}")

set(projname ${HPCC_PROJECT})
set(majorver ${HPCC_MAJOR})
set(minorver ${HPCC_MINOR})
set(point ${HPCC_POINT})
if ( "${HPCC_MATURITY}" STREQUAL "release" )
    set(stagever "${HPCC_SEQUENCE}")
else()
    set(stagever "${HPCC_MATURITY}${HPCC_SEQUENCE}")
endif()
set(version ${majorver}.${minorver}.${point})

IF ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set( stagever "${stagever}-Debug" )
ENDIF ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
##############################################

####  CPACK  ####
if ( WIN32 AND WITH_DYNAMIC_MSVC_RUNTIME )
    include ( InstallRequiredSystemLibraries )
endif ( WIN32 AND WITH_DYNAMIC_MSVC_RUNTIME )

set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}_${FB_PLATFORM_ARCH_NAME}")

set ( CPACK_PACKAGE_VENDOR "HPCC Systems" )
set ( CPACK_PACKAGE_NAME "hpccsystems-graphcontrol" )
SET(CPACK_PACKAGE_VERSION_MAJOR ${majorver})
SET(CPACK_PACKAGE_VERSION_MINOR ${minorver})
SET(CPACK_PACKAGE_VERSION_PATCH ${point}${stagever})
set ( CPACK_PACKAGE_DESCRIPTION_SUMMARY "HPCC Systems Graph Control." )

set ( CPACK_PACKAGE_CONTACT "HPCCSystems <ossdevelopment@lexisnexis.com>" )
set ( CPACK_DEBIAN_PACKAGE_MAINTAINER "HPCCSystems <ossdevelopment@lexisnexis.com>" )
set ( CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-dev (>=1.46.0), libboost-system-dev (>=1.46.0), libboost-thread-dev (>=1.46.0), libboost-filesystem-dev (>=1.46.0)")

set ( CPACK_RESOURCE_FILE_LICENSE "${FB_PROJECTS_DIR}/License.txt" )
set ( CPACK_RESOURCE_FILE_README "${FB_PROJECTS_DIR}/CPackReadMe.txt" )


set ( CPACK_RPM_PACKAGE_VERSION "${projname}")
SET(CPACK_RPM_PACKAGE_RELEASE "${version}${stagever}")
if ( ${ARCH64BIT} EQUAL 1 )
    set ( CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
else( ${ARCH64BIT} EQUAL 1 )
    set ( CPACK_RPM_PACKAGE_ARCHITECTURE "i386")
endif ( ${ARCH64BIT} EQUAL 1 )
set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}-${CPACK_RPM_PACKAGE_ARCHITECTURE}")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(CPACK_STRIP_FILES TRUE)
endif()
if ( APPLE OR WIN32)
    set ( CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_RPM_PACKAGE_VERSION}-${version}-${stagever}${CPACK_SYSTEM_NAME}" )
elseif ( UNIX )
    EXECUTE_PROCESS (
                COMMAND ${FB_PROJECTS_DIR}/cmake_utils/distrocheck.sh
                    OUTPUT_VARIABLE packageManagement
                        ERROR_VARIABLE  packageManagement
                )
    EXECUTE_PROCESS (
                COMMAND ${FB_PROJECTS_DIR}/cmake_utils/getpackagerevisionarch.sh
                    OUTPUT_VARIABLE packageRevisionArch
                        ERROR_VARIABLE  packageRevisionArch
                )
    EXECUTE_PROCESS (
                COMMAND ${FB_PROJECTS_DIR}/cmake_utils/getpackagerevisionarch.sh --noarch
                    OUTPUT_VARIABLE packageRevision
                        ERROR_VARIABLE  packageRevision
                )

    message ( "-- Auto Detecting Packaging type")
    message ( "-- distro uses ${packageManagement}, revision is ${packageRevisionArch}" )

    if ( "${packageManagement}" STREQUAL "DEB" )
        set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_RPM_PACKAGE_VERSION}-${version}-${stagever}${packageRevisionArch}")
    elseif ( "${packageManagement}" STREQUAL "RPM" )
        set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_RPM_PACKAGE_VERSION}-${version}-${stagever}.${packageRevisionArch}")
    else()
        set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_RPM_PACKAGE_VERSION}_${version}-${stagever}${CPACK_SYSTEM_NAME}")
    endif ()
endif ()
MESSAGE ("-- Current release version is ${CPACK_PACKAGE_FILE_NAME}")

###
## Run file configuration to set build tag along with install lines for generated
## config files.
###
set( BUILD_TAG "${CPACK_RPM_PACKAGE_VERSION}_${version}-${stagever}")
if (USE_GIT_DESCRIBE OR CHECK_GIT_TAG)
    FETCH_GIT_TAG (${CMAKE_SOURCE_DIR} ${CPACK_RPM_PACKAGE_VERSION}_${version} GIT_BUILD_TAG)
    message ("-- Git tag is '${GIT_BUILD_TAG}'")
    if (NOT "${GIT_BUILD_TAG}" STREQUAL "${BUILD_TAG}")
        if (CHECK_GIT_TAG)
            message(FATAL_ERROR "Git tag '${GIT_BUILD_TAG}' does not match source version '${BUILD_TAG}'" )
        else()
            if(NOT "${GIT_BUILD_TAG}" STREQUAL "") # probably means being built from a tarball...
                set( BUILD_TAG "${BUILD_TAG}[${GIT_BUILD_TAG}]")
            endif()
        endif()
    endif()
endif()
message ("-- Build tag is '${BUILD_TAG}'")
if (NOT "${BASE_BUILD_TAG}" STREQUAL "")
    set(BASE_BUILD_TAG "${BUILD_TAG}")
endif()
message ("-- Base build tag is '${BASE_BUILD_TAG}'")

if ( UNIX )
    set ( CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} )
elseif ( WIN32 )
    set( DIR_NAME "HPCCSystems" )
    set( version ${HPCC_MAJOR}.${HPCC_MINOR}.${HPCC_POINT} )
    set ( CPACK_PACKAGE_INSTALL_DIRECTORY "${DIR_NAME}\\\\${version}\\\\graphcontrol" )
    set ( CPACK_PACKAGE_INSTALL_REGISTRY_KEY "graphcontrol_${version}" )
    set ( CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL "ON" )
    set ( CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\hpccsystems.com" )
    set ( CPACK_NSIS_CONTACT ${CPACK_PACKAGE_CONTACT} )
    set ( CPACK_PACKAGE_INSTALL_PLUGINFILE "bin\\\\npHPCCSystemsGraphViewControl.dll")
    if ( "${FB_PLATFORM_ARCH_NAME}" EQUAL "x86_64" )
        SET ( CPACK_NSIS_DISPLAY_NAME "Graph Control x64" )
        list ( APPEND CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
            ExecWait '\\\"$SYSDIR\\\\regsvr32.exe\\\" /s \\\"$INSTDIR\\\\${CPACK_PACKAGE_INSTALL_PLUGINFILE}\\\"'
        " )
        list ( APPEND CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
            ExecWait '\\\"$SYSDIR\\\\regsvr32.exe\\\" /s /u \\\"$INSTDIR\\\\${CPACK_PACKAGE_INSTALL_PLUGINFILE}\\\"'
        " )
    else ()
        SET ( CPACK_NSIS_DISPLAY_NAME "Graph Control" )
        list ( APPEND CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
            RegDLL '$INSTDIR\\\\${CPACK_PACKAGE_INSTALL_PLUGINFILE}'
        " )
        list ( APPEND CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
            UnRegDLL '$INSTDIR\\\\${CPACK_PACKAGE_INSTALL_PLUGINFILE}'
        " )
    endif ()
    set ( CPACK_NSIS_DEFINES "
        !define MUI_STARTMENUPAGE_DEFAULTFOLDER \\\"${CPACK_PACKAGE_VENDOR}\\\\${version}\\\\${CPACK_NSIS_DISPLAY_NAME}\\\"
        !define MUI_FINISHPAGE_NOAUTOCLOSE
    ")

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
