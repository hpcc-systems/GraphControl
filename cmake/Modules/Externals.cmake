#set ( AGG_ROOT "${EXTERNALS_DIRECTORY}/agg" )
find_package( AGGSRC )
if ( AGGSRC_FOUND )
else ( )
    MESSAGE( "AGG Sources not found:  " ${AGG_ROOT})
endif ( )

set ( EXPAT_ROOT "${EXTERNALS_DIRECTORY}/expat" )
find_package( EXPAT )
if ( EXPAT_FOUND )
else ( )
    MESSAGE( "EXPAT not found:  " ${EXPAT_ROOT})
endif ( )

#set ( FIREBREATH_SOURCE_DIR "${EXTERNALS_DIRECTORY}/firebreath" )
find_package( FIREBREATH )
if ( FIREBREATH_FOUND )
else ( )
    MESSAGE( "FIREBREATH Source/Build not found, set FIREBREATH_DIR & FIREBREATH_BUILD_DIR" )
endif ( )

#set ( GRAPHVIZSRC_ROOT "${EXTERNALS_DIRECTORY}/graphviz2" )
find_package( GRAPHVIZSRC )
if ( GRAPHVIZSRC_FOUND )
else ( )
    MESSAGE( "GRAPHVIZ Sources not found:  " ${GRAPHVIZSRC_ROOT})
endif ( )

IF (WIN32)
set ( WTL_ROOT "${EXTERNALS_DIRECTORY}/wtl" )
find_package( WTL )
if ( WTL_FOUND )
else ( )
    MESSAGE( "WTL libraries were not found:  " ${WTL_ROOT})
endif ( )
endif ( WIN32 )

IF (WIN32)
    SET(Boost_USE_STATIC_LIBS        ON)
    SET(Boost_USE_MULTITHREADED      ON)
    if (WITH_STATIC_RUNTIME)
		SET(Boost_USE_STATIC_RUNTIME    ON)
	else (WITH_STATIC_RUNTIME)
		SET(Boost_USE_STATIC_RUNTIME    OFF)
	endif (WITH_STATIC_RUNTIME)
ENDIF (WIN32)
SET( Boost_ADDITIONAL_VERSIONS "1.44" "1.43" "1.43.0" "1.42" "1.42.0" )
FIND_PACKAGE( Boost 1.44 COMPONENTS date_time thread filesystem serialization regex system )
IF( Boost_FOUND )
ELSE( Boost_FOUND )
    MESSAGE( "BOOST libraries were not found:  " ${BOOST_ROOT})
ENDIF( Boost_FOUND )

FIND_PACKAGE( Freetype )
IF( FREETYPE_FOUND )
ELSE( FREETYPE_FOUND )
    MESSAGE( "Freetype library was not found" )
ENDIF( FREETYPE_FOUND )

if(WIN32)
elseif(APPLE)
	find_path(CARBON_INCLUDE_DIR Carbon.h)
    find_library(CARBON_FRAMEWORK Carbon) 
	find_path(QT_INCLUDE_DIR QuickTime.h)
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(SYSCONFIG_FRAMEWORK SystemConfiguration)
    find_library(FOUNDATION_FRAMEWORK Foundation)
    find_library(APPLICATIONSERVICES_FRAMEWORK ApplicationServices)
    find_library(QUARTZCORE_FRAMEWORK QuartzCore)

    FIND_PACKAGE(X11)
    IF(X11_FOUND)  
        INCLUDE_DIRECTORIES(${X11_INCLUDE_DIRS})
        LINK_LIBRARIES(${X11_LIBRARIES})
    ENDIF(X11_FOUND)

	find_package(PkgConfig)
	# GTK is required for XEmbed to work
	if (NOT GTK_INCLUDE_DIRS)
		pkg_check_modules(GTK REQUIRED gtk+-2.0)
		set (GTK_INCLUDE_DIRS ${GTK_INCLUDE_DIRS} CACHE INTERNAL "GTK include dirs")
		set (GTK_LIBRARIES ${GTK_LIBRARIES} CACHE INTERNAL "GTK include dirs")
		set (GTK_LIBRARY_DIRS ${GTK_LIBRARY_DIRS} CACHE INTERNAL "GTK include dirs")
		set (GTK_LDFLAGS ${GTK_LDFLAGS} CACHE INTERNAL "GTK include dirs")
	endif()
elseif(UNIX)
    FIND_PACKAGE( Threads )

	find_package(PkgConfig)
	# GTK is required for XEmbed to work
	if (NOT GTK_INCLUDE_DIRS)
		pkg_check_modules(GTK REQUIRED gtk+-2.0)
		set (GTK_INCLUDE_DIRS ${GTK_INCLUDE_DIRS} CACHE INTERNAL "GTK include dirs")
		set (GTK_LIBRARIES ${GTK_LIBRARIES} CACHE INTERNAL "GTK include dirs")
		set (GTK_LIBRARY_DIRS ${GTK_LIBRARY_DIRS} CACHE INTERNAL "GTK include dirs")
		set (GTK_LDFLAGS ${GTK_LDFLAGS} CACHE INTERNAL "GTK include dirs")
	endif()

    IF( THREADS_FOUND )
    ELSE( THREADS_FOUND )
        MESSAGE( "Threads library was not found" )
    ENDIF( THREADS_FOUND )
endif()
