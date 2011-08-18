# Component: ActiveXCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for ActiveXCore
#####################################################

project( ActiveXCore ) 

set (	SRCS 
	../gen/FireBreathWin.tlb.rule
	${FIREBREATH_INCLUDE_DIRS}/src/ActiveXCore/AXDOM/Document.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ActiveXCore/AXDOM/Element.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ActiveXCore/AXDOM/Node.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ActiveXCore/AXDOM/Window.cpp

	${FIREBREATH_INCLUDE_DIRS}/src/ActiveXCore/ActiveXBrowserHost.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ActiveXCore/IDispatchAPI.cpp

	${FIREBREATH_INCLUDE_DIRS}/src/ActiveXCore/axstream.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ActiveXCore/axstream_impl.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ActiveXCore/axutil.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ActiveXCore/FBControl.cpp
	#../gen/FireBreathWin_i.c
	#../gen/FireBreathWin.tlb
	#${FIREBREATH_INCLUDE_DIRS}/src/ActiveXCore/FBControl.bmp
	)

include_directories ( 
	..
	../gen
	${FIREBREATH_INCLUDE_DIRS}/src/3rdParty/gecko-sdk/includes
	${FIREBREATH_INCLUDE_DIRS}/src/ActiveXCore
	${FIREBREATH_INCLUDE_DIRS}/src/NpapiCore
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCore
	${FIREBREATH_INCLUDE_DIRS}/src/PluginCommon
	)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif ()

add_library ( ActiveXCore STATIC
	${SRCS} 
	)

