#/**********************************************************\ 
# Auto-generated Mac project definition file for the
# HPCC Systems Graph View Control project
#\**********************************************************/

# Mac template platform definition CMake file
# Included from ../CMakeLists.txt

# remember that the current source dir is the project root; this file is in Mac/
file (GLOB PLATFORM RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    Mac/[^.]*.cpp
    Mac/[^.]*.h
    Mac/[^.]*.cmake
    )

# use this to add preprocessor definitions
add_definitions(
    
)


SOURCE_GROUP(Mac FILES ${PLATFORM})

set (SOURCES
    ${SOURCES}
    ${PLATFORM}
    )

set(PLIST "Mac/bundle_template/Info.plist")
set(STRINGS "Mac/bundle_template/InfoPlist.strings")
set(LOCALIZED "Mac/bundle_template/Localized.r")

add_mac_plugin(${PROJECT_NAME} ${PLIST} ${STRINGS} ${LOCALIZED} SOURCES)

# add library dependencies here; leave ${PLUGIN_INTERNAL_DEPS} there unless you know what you're doing!
target_link_libraries(${PROJECT_NAME}
    ${PLUGIN_INTERNAL_DEPS}
    )

# Copy plugin to Plug-Ins directory:
function(releasePlugin projectName pathToPlugin releaseDirectory)
 ADD_CUSTOM_COMMAND(
 TARGET ${PROJECT_NAME}
 POST_BUILD
 COMMAND mkdir -p ${releaseDirectory}/${projectName}.plugin
 )
 ADD_CUSTOM_COMMAND( TARGET ${PROJECT_NAME}
 POST_BUILD
 COMMAND cp -pr ${pathToPlugin} ${releaseDirectory}
 )
endfunction()
 
# Current output
set(PBIN "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${PROJECT_NAME}.plugin")
 
# Uncomment one of the following releasePlugin() calls to install the plugin
  
# Copy plugin to ~/Library/Internet Plug-Ins (single user)
# releasePlugin("${PROJECT_NAME}" "${PBIN}" "~/Library/Internet Plug-Ins")
 
# Copy plugin to /Library/Internet Plug-Ins (all users)
# releasePlugin("${PROJECT_NAME}" "${PBIN}" "/Library/Internet Plug-Ins")
