# - Try to find GRAPHVIZ
# Once done this will define
#  GRAPHVIZSRC_FOUND - System has GRAPHVIZ Sources
#  GRAPHVIZSRC_DIRS - The GRAPHVIZ Source directories

find_path(GRAPHVIZSRC_DIR config.h
          HINTS ${GRAPHVIZSRC_ROOT} )

set(GRAPHVIZSRC_DIRS ${GRAPHVIZSRC_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set GRAPHVIZ_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(GRAPHVIZSRC DEFAULT_MSG
                                  GRAPHVIZSRC_DIR)

mark_as_advanced( GRAPHVIZSRC_DIRS )
