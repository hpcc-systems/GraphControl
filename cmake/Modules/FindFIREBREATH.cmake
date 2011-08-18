# - Try to find FIREBREATH
# Once done this will define
#  FIREBREATH_FOUND - System has FIREBREATH
#  FIREBREATH_INCLUDE_DIRS - The FIREBREATH include directories
#  FIREBREATH_LIBRARIES - The libraries needed to use FIREBREATH
#  FIREBREATH_DEFINITIONS - Compiler switches required for using FIREBREATH

find_path(FIREBREATH_INCLUDE_DIR src/plugincore/plugincore.h
          HINTS ${FIREBREATH_ROOT} )

set(FIREBREATH_INCLUDE_DIRS ${FIREBREATH_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set FIREBREATH_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(FIREBREATH DEFAULT_MSG
                                  FIREBREATH_INCLUDE_DIR)

mark_as_advanced( FIREBREATH_INCLUDE_DIR )
