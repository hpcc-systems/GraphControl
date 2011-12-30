project ( GraphControl )
cmake_minimum_required (VERSION 2.6)

set ( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/" ${CMAKE_MODULE_PATH})

option(WITH_DYNAMIC_MSVC_RUNTIME "Build with dynamic MSVC runtime (/MD)" OFF)

IF ( WIN32 )
    SET ( EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Location of BIN files" )
    SET ( LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Location of LIB files" )
ELSE ( WIN32 )
    #SET ( EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Location of BIN files" )
    #SET ( LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Location of LIB files" )
    SET ( EXECUTABLE_OUTPUT_PATH "/usr/lib/mozilla/plugins" )
    SET ( LIBRARY_OUTPUT_PATH "/usr/lib/mozilla/plugins" )
ENDIF ( WIN32 )

MACRO(ADD_PRECOMPILED_HEADER PROJECT_NAME PrecompiledHeader PrecompiledSource SourcesVar)
    IF(MSVC)
        GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
        SET(__PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${PrecompiledBasename}.pch")

        SET_SOURCE_FILES_PROPERTIES(${PrecompiledSource}
            PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledBasename}.h\" /Fp\"${__PrecompiledBinary}\" -Zm160"
            OBJECT_OUTPUTS "${__PrecompiledBinary}")
        foreach(CURFILE ${${SourcesVar}})

            GET_FILENAME_COMPONENT(CURFILE_EXT ${CURFILE} EXT)
            GET_FILENAME_COMPONENT(CURFILE_NAME ${CURFILE} NAME)
            if (CURFILE_EXT STREQUAL ".cpp" AND NOT CURFILE_NAME STREQUAL PrecompiledBasename)
                SET_SOURCE_FILES_PROPERTIES(${CURFILE}
                    PROPERTIES COMPILE_FLAGS "/Yu\"${__PrecompiledBinary}\" /FI\"${__PrecompiledBinary}\" /Fp\"${__PrecompiledBinary}\" -Zm160"
                    OBJECT_DEPENDS "${__PrecompiledBinary}")  
            endif()

        endforeach()
        # Add precompiled header to SourcesVar
        LIST(APPEND ${SourcesVar} ${PrecompiledSource})
        LIST(APPEND ${SourcesVar} ${PrecompiledHeader})
    elseif (APPLE)
        # My tests aren't showing any advantage to turning this on for mac
        #message("Setting precompiled header ${PrecompiledHeader} on ${PROJECT_NAME}")
        #SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER YES)
        #SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${PrecompiledHeader}")
    endif()
ENDMACRO(ADD_PRECOMPILED_HEADER)

include ( "${CMAKE_SOURCE_DIR}/cmake/Modules/Externals.cmake" )

if (WIN32)
	ADD_DEFINITIONS(-DFB_WIN=1 -DXP_WIN=1)
    if (WITH_DYNAMIC_MSVC_RUNTIME)
        message(STATUS "Building with dynamic MSVC runtime")
	else (WITH_DYNAMIC_MSVC_RUNTIME)
        message(STATUS "Building with static MSVC runtime")
		ADD_DEFINITIONS( -DSTATIC_LIB )
	endif (WITH_DYNAMIC_MSVC_RUNTIME)
    foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
            CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
	    if (WITH_DYNAMIC_MSVC_RUNTIME)
		    if(${flag_var} MATCHES "/MT")
			    string(REGEX REPLACE "/MT" "/MD" ${flag_var} "${${flag_var}}")
			endif()
		else()
		    if(${flag_var} MATCHES "/MD")
			    string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
			endif()
		endif()
    endforeach(flag_var)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D BOOST_ALL_NO_LIB=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D BOOST_ALL_NO_LIB=1")
ELSE (WIN32)
	ADD_DEFINITIONS( -DFB_X11=1 -DXP_UNIX=1)
	find_package(PkgConfig)

	# GTK is required for XEmbed to work
	if (NOT GTK_INCLUDE_DIRS)
		pkg_check_modules(GTK REQUIRED gtk+-2.0)
		set (GTK_INCLUDE_DIRS ${GTK_INCLUDE_DIRS} CACHE INTERNAL "GTK include dirs")
		set (GTK_LIBRARIES ${GTK_LIBRARIES} CACHE INTERNAL "GTK include dirs")
		set (GTK_LIBRARY_DIRS ${GTK_LIBRARY_DIRS} CACHE INTERNAL "GTK include dirs")
		set (GTK_LDFLAGS ${GTK_LDFLAGS} CACHE INTERNAL "GTK include dirs")
	endif()

	SET ( gecko_defs -DXP_UNIX )
    SET ( fPIC_flag "-fPIC" )

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${gecko_defs} ${fPIC_flag}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${gecko_defs} ${fPIC_flag}")
ENDIF (WIN32)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory (agg)
set_property(TARGET agg PROPERTY FOLDER "3rdParty")
if ( WIN32 )
	ADD_DEFINITIONS( -DXML_STATIC )
	add_subdirectory (expat)
	set_property(TARGET expat PROPERTY FOLDER "3rdParty")
endif ( WIN32 )

add_subdirectory (graphlayout)
add_subdirectory (graphdb)
add_subdirectory (graphrender)
add_subdirectory (HPCCSystemsGraphViewControl)
#add_subdirectory (test)
