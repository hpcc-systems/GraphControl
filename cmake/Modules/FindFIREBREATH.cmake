# - Try to find FireBreath
# Once done this will define
#  FIREBREATH_FOUND - System has FireBreath
#  FIREBREATH_INCLUDE_DIRS - The FireBreath include directories
#  FIREBREATH_LIBRARIES - The libraries needed to use FireBreath
#  FIREBREATH_DEFINITIONS - Compiler switches required for using FireBreath

find_path(FIREBREATH_SOURCE_DIR PluginCore/PluginCore.h
          HINTS ${FIREBREATH_DIR}
          PATH_SUFFIXES src )

set(FIREBREATH_INCLUDE_DIR ${FIREBREATH_SOURCE_DIR} )
set(FIREBREATH_INCLUDE_DIRS 
	${FIREBREATH_SOURCE_DIR}/3rdParty/gecko-sdk/includes 
	${FIREBREATH_SOURCE_DIR}/ActiveXCore
	${FIREBREATH_SOURCE_DIR}/NpapiCore
	${FIREBREATH_SOURCE_DIR}/ScriptingCore
	${FIREBREATH_SOURCE_DIR}/PluginCore
	${FIREBREATH_SOURCE_DIR}/PluginAuto
	${FIREBREATH_SOURCE_DIR}/config
	)

macro(_FIREBREATH_FINDLIB basename)
string(TOUPPER ${basename} basename_upper) 
find_library(FIREBREATH_${basename_upper}_LIBRARY_DEBUG ${basename}
             HINTS ${FIREBREATH_BUILD_DIR} 
			 PATH_SUFFIXES ${basename}/debug )

find_library(FIREBREATH_${basename_upper}_LIBRARY_RELEASE ${basename}
             HINTS ${FIREBREATH_BUILD_DIR} 
			 PATH_SUFFIXES ${basename}/release )
set(FIREBREATH_${basename_upper}_LIBRARY optimized ${FIREBREATH_${basename_upper}_LIBRARY_RELEASE} debug ${FIREBREATH_${basename_upper}_LIBRARY_DEBUG})
endmacro(_FIREBREATH_FINDLIB)

_FIREBREATH_FINDLIB(plugincore)
_FIREBREATH_FINDLIB(npapicore)
_FIREBREATH_FINDLIB(scriptingcore)
_FIREBREATH_FINDLIB(activexcore)

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
