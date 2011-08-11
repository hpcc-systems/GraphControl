# Component: ActiveXCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for ActiveXCore
#####################################################

project( ActiveXCore ) 

set (	SRCS 
	../gen/FireBreathWin.tlb.rule
	${EXTERNALS_DIRECTORY}/firebreath/src/ActiveXCore/AXDOM/Document.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ActiveXCore/AXDOM/Element.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ActiveXCore/AXDOM/Node.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ActiveXCore/AXDOM/Window.cpp

	${EXTERNALS_DIRECTORY}/firebreath/src/ActiveXCore/ActiveXBrowserHost.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ActiveXCore/IDispatchAPI.cpp

	${EXTERNALS_DIRECTORY}/firebreath/src/ActiveXCore/axstream.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ActiveXCore/axstream_impl.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ActiveXCore/axutil.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ActiveXCore/FBControl.cpp
	#../gen/FireBreathWin_i.c
	#../gen/FireBreathWin.tlb
	#${EXTERNALS_DIRECTORY}/firebreath/src/ActiveXCore/FBControl.bmp
	)

include_directories ( 
	..
	../gen
	${EXTERNALS_DIRECTORY}/firebreath/src/3rdParty/gecko-sdk/includes
	${EXTERNALS_DIRECTORY}/firebreath/src/ActiveXCore
	${EXTERNALS_DIRECTORY}/firebreath/src/NpapiCore
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCore
	${EXTERNALS_DIRECTORY}/firebreath/src/PluginCommon
	)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif ()

add_library ( ActiveXCore STATIC
	${SRCS} 
	)

