#/**********************************************************\ 
# Auto-generated X11 project definition file for the
# HPCC Systems Graph View Control project
#\**********************************************************/

# X11 template platform definition CMake file
# Included from ../CMakeLists.txt

# remember that the current source dir is the project root; this file is in X11/
file (GLOB PLATFORM RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    X11/[^.]*.cpp
    X11/[^.]*.h
    X11/[^.]*.cmake
    )

SOURCE_GROUP(X11 FILES ${PLATFORM})

# use this to add preprocessor definitions
add_definitions(
)

set (SOURCES
    ${SOURCES}
    ${PLATFORM}
    )

add_x11_plugin(${PROJECT_NAME} SOURCES)

# add library dependencies here; leave ${PLUGIN_INTERNAL_DEPS} there unless you know what you're doing!
target_link_libraries(${PROJECT_NAME}
    ${PLUGIN_INTERNAL_DEPS}
    )

install ( TARGETS ${PROJECT_NAME} DESTINATION  "." )

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    get_property(LIB64 GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS)
    if("${LIB64}" STREQUAL "TRUE")
        set(MOZILLA_PLUGINS_DIR "/usr/lib64/mozilla/plugins")
    else()
        set(MOZILLA_PLUGINS_DIR "/usr/lib/mozilla/plugins")
    endif()
    set(CMAKE_INSTALL_PREFIX "${MOZILLA_PLUGINS_DIR}" CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
