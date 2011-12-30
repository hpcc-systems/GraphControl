# Component: ActiveXCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for ActiveXCore
#####################################################

project( ActiveXCore ) 

include_directories ( 
	..
	../gen
	${FIREBREATHSRC_DIR}/src/3rdParty/gecko-sdk/includes
	${FIREBREATHSRC_DIR}/src/ActiveXCore
	${FIREBREATHSRC_DIR}/src/NpapiCore
	${FIREBREATHSRC_DIR}/src/ScriptingCore
	${FIREBREATHSRC_DIR}/src/PluginCore
	${FIREBREATHSRC_DIR}/src/PluginCommon

	${Boost_INCLUDE_DIRS}
	)

set (	SRCS 
	../gen/FireBreathWin.tlb.rule
	${FIREBREATHSRC_DIR}/src/ActiveXCore/AXDOM/Document.cpp
	${FIREBREATHSRC_DIR}/src/ActiveXCore/AXDOM/Element.cpp
	${FIREBREATHSRC_DIR}/src/ActiveXCore/AXDOM/Window.cpp

	${FIREBREATHSRC_DIR}/src/ActiveXCore/ActiveXBrowserHost.cpp
	${FIREBREATHSRC_DIR}/src/ActiveXCore/IDispatchAPI.cpp

	${FIREBREATHSRC_DIR}/src/ActiveXCore/axstream.cpp
	${FIREBREATHSRC_DIR}/src/ActiveXCore/axstream_impl.cpp
	${FIREBREATHSRC_DIR}/src/ActiveXCore/axutil.cpp
	${FIREBREATHSRC_DIR}/src/ActiveXCore/FBControl.cpp

	${FIREBREATHSRC_DIR}/src/ActiveXCore/precompiled_headers.h
	${FIREBREATHSRC_DIR}/src/ActiveXCore/precompiled_headers.cpp
	)

ADD_PRECOMPILED_HEADER(ActiveXCore "${FIREBREATHSRC_DIR}/src/ActiveXCore/precompiled_headers.h" "${FIREBREATHSRC_DIR}/src/ActiveXCore/precompiled_headers.cpp" SOURCES)

add_library ( ActiveXCore STATIC
	${SRCS} 
	)

