# Component: NpapiHost
#####################################################
# Description:
# ------------
#	 Cmake Input File for NpapiHost
#####################################################

project( NpapiHost ) 

set (	SRCS 
	${FIREBREATHSRC_DIRS}/src/NpapiHost/NpapiHost.cpp
	${FIREBREATHSRC_DIRS}/src/NpapiHost/NpBrowserHostFuncs.cpp
	${FIREBREATHSRC_DIRS}/src/NpapiHost/NpResourceHostFuncs.cpp
	${FIREBREATHSRC_DIRS}/src/NpapiHost/NpRuntimeHostFuncs.cpp
	)

include_directories ( 
	..
	../gen
	${FIREBREATHSRC_DIRS}/src/3rdParty/gecko-sdk/includes
	${FIREBREATHSRC_DIRS}/src/NpapiHost
	${FIREBREATHSRC_DIRS}/src/NpapiCore
	${FIREBREATHSRC_DIRS}/src/ScriptingCore
	${FIREBREATHSRC_DIRS}/src/PluginCore
	)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif ()

add_library ( NpapiHost STATIC
	${SRCS} 
	)

