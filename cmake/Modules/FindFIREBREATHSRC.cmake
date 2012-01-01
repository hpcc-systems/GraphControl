# - Try to find LibXml2
# Once done this will define
#  FIREBREATHSRC_FOUND - System has LibXml2
#  FIREBREATHSRC_INCLUDE_DIRS - The LibXml2 include directories
#  FIREBREATHSRC_LIBRARIES - The libraries needed to use LibXml2
#  FIREBREATHSRC_DEFINITIONS - Compiler switches required for using LibXml2

find_path (		FIREBREATHSRC_INCLUDE_DIR	
				PluginCore/PluginCore.h	
				HINTS ${FIREBREATHSRC_DIR} 
				PATH_SUFFIXES src )

set(FIREBREATHSRC_INCLUDE_DIRS ${FIREBREATHSRC_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set FIREBREATHSRC_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(FIREBREATHSRC DEFAULT_MSG FIREBREATHSRC_INCLUDE_DIR)

mark_as_advanced(FIREBREATHSRC_INCLUDE_DIRS )
