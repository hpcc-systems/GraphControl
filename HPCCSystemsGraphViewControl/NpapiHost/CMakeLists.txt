# Component: NpapiHost
#####################################################
# Description:
# ------------
#	 Cmake Input File for NpapiHost
#####################################################

project( NpapiHost ) 

set (	SRCS 
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiHost/NpapiHost.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiHost/NpBrowserHostFuncs.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiHost/NpResourceHostFuncs.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiHost/NpRuntimeHostFuncs.cpp
	)

include_directories ( 
	..
	../gen
	${FIREBREATH_INCLUDE_DIRS}/src/3rdParty/gecko-sdk/includes
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiHost
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiCore
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore
	)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif ()

add_library ( NpapiHost STATIC
	${SRCS} 
	)

