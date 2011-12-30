# Component: ScriptingCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for ScriptingCore
#####################################################

project( ScriptingCore ) 

set( FIREBREATH_CURRENT_SOURCE_DIR ${FIREBREATHSRC_DIR}/src/ScriptingCore ) 

include_directories ( 
	..
	../gen
	${FIREBREATH_CURRENT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
	)

set (	SRCS 
	../gen/FireBreathWin.tlb.rule
	${FIREBREATH_CURRENT_SOURCE_DIR}/DOM/Document.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/DOM/Element.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/DOM/Node.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/DOM/Window.cpp

	${FIREBREATH_CURRENT_SOURCE_DIR}/Util/JSFakeArray.cpp

	${FIREBREATH_CURRENT_SOURCE_DIR}/BrowserHost.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/CrossThreadCall.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/JSAPIImpl.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/JSAPIAuto.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/JSAPISimple.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/JSAPIProxy.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/JSArray.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/JSEvent.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/JSFunction.cpp

	${FIREBREATH_CURRENT_SOURCE_DIR}/URI.cpp
	${FIREBREATH_CURRENT_SOURCE_DIR}/utf8_tools.cpp

	${FIREBREATH_CURRENT_SOURCE_DIR}/variant.cpp

	${FIREBREATH_CURRENT_SOURCE_DIR}/precompiled_headers.h
	${FIREBREATH_CURRENT_SOURCE_DIR}/precompiled_headers.cpp
	)

if (WIN32)
set (	SRCS_OS
	)
else (WIN32)
set (	SRCS_OS
	${FIREBREATH_CURRENT_SOURCE_DIR}/utf8.c
	)
endif (WIN32)

ADD_PRECOMPILED_HEADER(ActiveXCore "${FIREBREATH_CURRENT_SOURCE_DIR}/precompiled_headers.h" "${FIREBREATH_CURRENT_SOURCE_DIR}/precompiled_headers.cpp" SOURCES)
add_library ( ScriptingCore STATIC
	${SRCS} 
	${SRCS_OS}
	)

target_link_libraries(ScriptingCore
    #${CMAKE_THREAD_LIBS_INIT}
    )
