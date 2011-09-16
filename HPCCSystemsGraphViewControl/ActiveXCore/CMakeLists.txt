# Component: ActiveXCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for ActiveXCore
#####################################################

project( ActiveXCore ) 

set (	SRCS 
	../gen/FireBreathWin.tlb.rule
	${FIREBREATHSRC_DIRS}/src/ActiveXCore/AXDOM/Document.cpp
	${FIREBREATHSRC_DIRS}/src/ActiveXCore/AXDOM/Element.cpp
	#${FIREBREATHSRC_DIRS}/src/ActiveXCore/AXDOM/Node.cpp
	${FIREBREATHSRC_DIRS}/src/ActiveXCore/AXDOM/Window.cpp

	${FIREBREATHSRC_DIRS}/src/ActiveXCore/ActiveXBrowserHost.cpp
	${FIREBREATHSRC_DIRS}/src/ActiveXCore/IDispatchAPI.cpp

	${FIREBREATHSRC_DIRS}/src/ActiveXCore/axstream.cpp
	${FIREBREATHSRC_DIRS}/src/ActiveXCore/axstream_impl.cpp
	${FIREBREATHSRC_DIRS}/src/ActiveXCore/axutil.cpp
	${FIREBREATHSRC_DIRS}/src/ActiveXCore/FBControl.cpp
	#../gen/FireBreathWin_i.c
	#../gen/FireBreathWin.tlb
	#${FIREBREATHSRC_DIRS}/src/ActiveXCore/FBControl.bmp
	)

include_directories ( 
	..
	../gen
	${FIREBREATHSRC_DIRS}/src/3rdParty/gecko-sdk/includes
	${FIREBREATHSRC_DIRS}/src/ActiveXCore
	${FIREBREATHSRC_DIRS}/src/NpapiCore
	${FIREBREATHSRC_DIRS}/src/ScriptingCore
	${FIREBREATHSRC_DIRS}/src/PluginCore
	${FIREBREATHSRC_DIRS}/src/PluginCommon
	)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif ()

add_library ( ActiveXCore STATIC
	${SRCS} 
	)

