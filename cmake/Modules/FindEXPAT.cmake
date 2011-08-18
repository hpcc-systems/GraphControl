# - Try to find EXPAT
# Once done this will define
#  EXPAT_FOUND - System has EXPAT
#  EXPAT_INCLUDE_DIRS - The EXPAT include directories
#  EXPAT_LIBRARIES - The libraries needed to use EXPAT
#  EXPAT_DEFINITIONS - Compiler switches required for using EXPAT

find_path(EXPAT_INCLUDE_DIR lib/expat.h
          HINTS ${EXPAT_ROOT} )

set(EXPAT_INCLUDE_DIRS ${EXPAT_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set EXPAT_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(EXPAT DEFAULT_MSG
                                  EXPAT_INCLUDE_DIR)

mark_as_advanced( EXPAT_INCLUDE_DIR )
