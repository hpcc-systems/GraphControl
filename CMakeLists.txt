project ( GraphControl )
cmake_minimum_required (VERSION 2.6)

set ( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/" ${CMAKE_MODULE_PATH})

IF ( WIN32 )
    SET ( EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/../bin" CACHE PATH "Location of BIN files" )
    SET ( LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/../bin" CACHE PATH "Location of LIB files" )
ELSE ( WIN32 )
    SET ( EXECUTABLE_OUTPUT_PATH "/usr/lib/mozilla/plugins" )
    SET ( LIBRARY_OUTPUT_PATH "/usr/lib/mozilla/plugins" )
ENDIF ( WIN32 )

MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
  IF(MSVC)
    GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
    SET(PrecompiledBinary "$(IntDir)/${PrecompiledBasename}.pch")
    SET(Sources ${${SourcesVar}})

    SET_SOURCE_FILES_PROPERTIES(${PrecompiledSource}
    				PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
    					OBJECT_OUTPUTS "${PrecompiledBinary}")
    SET_SOURCE_FILES_PROPERTIES(${Sources}
    				PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
    					OBJECT_DEPENDS "${PrecompiledBinary}") 
    # Add precompiled header to SourcesVar
    LIST(APPEND ${SourcesVar} ${PrecompiledSource})
    LIST(APPEND ${SourcesVar} ${PrecompiledHeader})
  ENDIF(MSVC)
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)

include ( "${CMAKE_SOURCE_DIR}/cmake/Modules/Externals.cmake" )


if (WIN32)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -FR -DFB_WIN=1 -DXP_WIN=1)
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
add_subdirectory (expat)
set_property(TARGET expat PROPERTY FOLDER "3rdParty")

add_subdirectory (graphlayout)
add_subdirectory (graphdb)
add_subdirectory (graphrender)
add_subdirectory (HPCCSystemsGraphViewControl)
#add_subdirectory (test)
