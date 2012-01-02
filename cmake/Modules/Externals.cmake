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
    MESSAGE( "FIREBREATHC Source/Build not found, set FIREBREATH_DIR & FIREBREATH_BUILD_DIR" )
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
    if (WITH_DYNAMIC_MSVC_RUNTIME)
		SET(Boost_USE_STATIC_RUNTIME    OFF)
	else (WITH_DYNAMIC_MSVC_RUNTIME)
		SET(Boost_USE_STATIC_RUNTIME    ON)
	endif (WITH_DYNAMIC_MSVC_RUNTIME)
ENDIF (WIN32)
SET( Boost_ADDITIONAL_VERSIONS "1.44" "1.43" "1.43.0" "1.42" "1.42.0" )
FIND_PACKAGE( Boost 1.44 COMPONENTS date_time thread graph serialization regex system )
IF( Boost_FOUND )
ELSE( Boost_FOUND )
    MESSAGE( "BOOST libraries were not found:  " ${BOOST_ROOT})
ENDIF( Boost_FOUND )

FIND_PACKAGE( Freetype )
IF( FREETYPE_FOUND )
ELSE( FREETYPE_FOUND )
    MESSAGE( "Freetype library was not found" )
ENDIF( FREETYPE_FOUND )

IF (WIN32)
ELSE (WIN32)
    FIND_PACKAGE( Threads )
    IF( THREADS_FOUND )
    ELSE( THREADS_FOUND )
        MESSAGE( "Threads library was not found" )
    ENDIF( THREADS_FOUND )
ENDIF (WIN32)