# - Try to find AGG
# Once done this will define
#  AGGSRCSRC_FOUND - System has AGGSRC Sources
#  AGGSRC_DIRS - The AGGSRC Source directories

find_path(AGGSRC_DIR agg-2.4/include/agg_pixfmt_gray.h
          HINTS ${AGGSRC_ROOT} )

set(AGGSRC_DIRS ${AGGSRC_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set AGGSRC_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(AGGSRC DEFAULT_MSG
                                  AGGSRC_DIR)

mark_as_advanced( AGGSRC_DIRS )
