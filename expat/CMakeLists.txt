# Component: expat
#####################################################
# Description:
# ------------
#	 Cmake Input File for expat
#####################################################

project( expat ) 
cmake_minimum_required ( VERSION 2.8 )

if (WIN32)
set (	DEFS 
	${EXPAT_INCLUDE_DIRS}/lib/libexpatw.def
	)
else (WIN32)
set (	DEFS 
	)
endif (WIN32)

set (	SRCS 
	${EXPAT_INCLUDE_DIRS}/lib/xmlparse.c
	${EXPAT_INCLUDE_DIRS}/lib/xmlrole.c
	${EXPAT_INCLUDE_DIRS}/lib/xmltok.c
	${EXPAT_INCLUDE_DIRS}/lib/xmltok_impl.c
	${EXPAT_INCLUDE_DIRS}/lib/xmltok_ns.c

	${EXPAT_INCLUDE_DIRS}/lib/amigaconfig.h
	${EXPAT_INCLUDE_DIRS}/lib/ascii.h
	${EXPAT_INCLUDE_DIRS}/lib/asciitab.h
	${EXPAT_INCLUDE_DIRS}/lib/expat.h
	${EXPAT_INCLUDE_DIRS}/lib/expat_external.h
	${EXPAT_INCLUDE_DIRS}/lib/iasciitab.h
	${EXPAT_INCLUDE_DIRS}/lib/internal.h
	${EXPAT_INCLUDE_DIRS}/lib/latin1tab.h
	${EXPAT_INCLUDE_DIRS}/lib/macconfig.h
	${EXPAT_INCLUDE_DIRS}/lib/nametab.h
	${EXPAT_INCLUDE_DIRS}/lib/utf8tab.h
	${EXPAT_INCLUDE_DIRS}/lib/winconfig.h
	${EXPAT_INCLUDE_DIRS}/lib/xmlrole.h
	${EXPAT_INCLUDE_DIRS}/lib/xmltok.h
	${EXPAT_INCLUDE_DIRS}/lib/xmltok_impl.h	
	)

	include_directories ( 
	${EXPAT_INCLUDE_DIRS}/lib
	)

add_library ( expat STATIC 
	${DEFS} 
	${SRCS} 
	)

ADD_DEFINITIONS( -D_UNICODE -DXML_UNICODEXXX )

if (WIN32)
ADD_DEFINITIONS( -DEXPAT_EXPORTS -DCOMPILED_FROM_DSP )
else ()
ADD_DEFINITIONS( -DHAVE_BCOPY )
endif ()

target_link_libraries ( expat )
