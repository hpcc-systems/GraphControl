# - Try to find FIREBREATH
# Once done this will define
#  FIREBREATHSRC_FOUND - System has FIREBREATH
#  FIREBREATHSRC_DIRS - The FIREBREATH Source directories

find_path(FIREBREATHSRC_DIR src/plugincore/plugincore.h
          HINTS ${FIREBREATHSRC_ROOT} )

set(FIREBREATHSRC_DIRS ${FIREBREATHSRC_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set FIREBREATH_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(FIREBREATHSRC DEFAULT_MSG
                                  FIREBREATHSRC_DIR)

mark_as_advanced( FIREBREATHSRC_DIRS )
