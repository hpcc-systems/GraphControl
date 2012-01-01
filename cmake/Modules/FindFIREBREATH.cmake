# - Try to find FireBreath
# Once done this will define
#  FIREBREATH_FOUND - System has FireBreath
#  FIREBREATH_INCLUDE_DIRS - The FireBreath include directories
#  FIREBREATH_LIBRARIES - The libraries needed to use FireBreath
#  FIREBREATH_DEFINITIONS - Compiler switches required for using FireBreath

find_path( FIREBREATH_DIR src/PluginCore/PluginCore.h
          HINTS ${FIREBREATH_ROOT} )

find_path( FIREBREATH_INCLUDE_DIR PluginCore/PluginCore.h
          HINTS ${FIREBREATH_DIR}
          PATH_SUFFIXES src )

set( FIREBREATH_SOURCE_DIR ${FIREBREATH_INCLUDE_DIR} )
set( FIREBREATH_INCLUDE_DIRS 
	${FIREBREATH_SOURCE_DIR}/3rdParty/gecko-sdk/includes 
	${FIREBREATH_SOURCE_DIR}/ActiveXCore
	${FIREBREATH_SOURCE_DIR}/NpapiCore
	${FIREBREATH_SOURCE_DIR}/ScriptingCore
	${FIREBREATH_SOURCE_DIR}/PluginCore
	${FIREBREATH_SOURCE_DIR}/PluginAuto
	${FIREBREATH_SOURCE_DIR}/config
	)

find_path(FIREBREATH_BUILD_DIR CMakeCache.txt
          HINTS ${FIREBREATH_ROOT} )

macro(_FIREBREATH_FINDLIB basename)
string(TOUPPER ${basename} basename_upper) 
if (WIN32)
find_library(FIREBREATH_${basename_upper}_LIBRARY_DEBUG ${basename}
             HINTS ${FIREBREATH_BUILD_DIR} 
			 PATH_SUFFIXES ${basename}/debug )

find_library(FIREBREATH_${basename_upper}_LIBRARY_RELEASE ${basename}
             HINTS ${FIREBREATH_BUILD_DIR} 
			 PATH_SUFFIXES ${basename}/release )
set(FIREBREATH_${basename_upper}_LIBRARY optimized ${FIREBREATH_${basename_upper}_LIBRARY_RELEASE} debug ${FIREBREATH_${basename_upper}_LIBRARY_DEBUG})
elseif(APPLE)
elseif(UNIX)
find_library(FIREBREATH_${basename_upper}_LIBRARY ${basename}/lib${basename}.a
             HINTS ${FIREBREATH_BUILD_DIR}
	     )
endif()
endmacro(_FIREBREATH_FINDLIB)

_FIREBREATH_FINDLIB(PluginCore)
_FIREBREATH_FINDLIB(NpapiCore)
_FIREBREATH_FINDLIB(ScriptingCore)
if (WIN32)
_FIREBREATH_FINDLIB(activexcore)
endif()

set(FIREBREATH_LIBRARY 
	${FIREBREATH_PLUGINCORE_LIBRARY} 
	${FIREBREATH_NPAPICORE_LIBRARY} 
	${FIREBREATH_SCRIPTINGCORE_LIBRARY} 
	${FIREBREATH_ACTIVEXCORE_LIBRARY} 
	)
set(FIREBREATH_LIBRARIES ${FIREBREATH_LIBRARY} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set FIREBREATH_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(FireBreath  DEFAULT_MSG
                                  FIREBREATH_LIBRARY FIREBREATH_INCLUDE_DIR)

mark_as_advanced(FIREBREATH_INCLUDE_DIR FIREBREATH_LIBRARY )
