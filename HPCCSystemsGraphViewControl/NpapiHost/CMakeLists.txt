# Component: NpapiHost
#####################################################
# Description:
# ------------
#	 Cmake Input File for NpapiHost
#####################################################

project( NpapiHost ) 

set (	SRCS 
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiHost/NpapiHost.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiHost/NpBrowserHostFuncs.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiHost/NpResourceHostFuncs.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiHost/NpRuntimeHostFuncs.cpp
	)

include_directories ( 
	..
	../gen
	${EXTERNALS_DIRECTORY}/firebreath/src/3rdParty/gecko-sdk/includes
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiHost
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiCore
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore
	)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif ()

add_library ( NpapiHost STATIC
	${SRCS} 
	)

