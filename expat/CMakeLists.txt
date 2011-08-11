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
	${EXTERNALS_DIRECTORY}/expat/lib/libexpatw.def
	)
else (WIN32)
set (	DEFS 
	)
endif (WIN32)

set (	SRCS 
	${EXTERNALS_DIRECTORY}/expat/lib/xmlparse.c
	${EXTERNALS_DIRECTORY}/expat/lib/xmlrole.c
	${EXTERNALS_DIRECTORY}/expat/lib/xmltok.c
	${EXTERNALS_DIRECTORY}/expat/lib/xmltok_impl.c
	${EXTERNALS_DIRECTORY}/expat/lib/xmltok_ns.c

	${EXTERNALS_DIRECTORY}/expat/lib/amigaconfig.h
	${EXTERNALS_DIRECTORY}/expat/lib/ascii.h
	${EXTERNALS_DIRECTORY}/expat/lib/asciitab.h
	${EXTERNALS_DIRECTORY}/expat/lib/expat.h
	${EXTERNALS_DIRECTORY}/expat/lib/expat_external.h
	${EXTERNALS_DIRECTORY}/expat/lib/iasciitab.h
	${EXTERNALS_DIRECTORY}/expat/lib/internal.h
	${EXTERNALS_DIRECTORY}/expat/lib/latin1tab.h
	${EXTERNALS_DIRECTORY}/expat/lib/macconfig.h
	${EXTERNALS_DIRECTORY}/expat/lib/nametab.h
	${EXTERNALS_DIRECTORY}/expat/lib/utf8tab.h
	${EXTERNALS_DIRECTORY}/expat/lib/watcomconfig.h
	${EXTERNALS_DIRECTORY}/expat/lib/winconfig.h
	${EXTERNALS_DIRECTORY}/expat/lib/xmlrole.h
	${EXTERNALS_DIRECTORY}/expat/lib/xmltok.h
	${EXTERNALS_DIRECTORY}/expat/lib/xmltok_impl.h	
	)

	include_directories ( 
	${EXTERNALS_DIRECTORY}/expat/lib
	)

add_library ( expat SHARED 
	${DEFS} 
	${SRCS} 
	)

ADD_DEFINITIONS( -D_UNICODE -DXML_UNICODEXXX )

if (WIN32)
ADD_DEFINITIONS( -D_USRDLL -DEXPAT_EXPORTS -DCOMPILED_FROM_DSP )
else ()
ADD_DEFINITIONS( -DHAVE_BCOPY )
endif ()

target_link_libraries ( expat )
