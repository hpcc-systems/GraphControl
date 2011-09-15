# Component: ScriptingCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for ScriptingCore
#####################################################

project( ScriptingCore ) 

set (	SRCS 
	../gen/FireBreathWin.tlb.rule
	${FIREBREATHSRC_DIRS}/src/ScriptingCore/DOM/Document.cpp
	${FIREBREATHSRC_DIRS}/src/ScriptingCore/DOM/Element.cpp
	${FIREBREATHSRC_DIRS}/src/ScriptingCore/DOM/Node.cpp
	${FIREBREATHSRC_DIRS}/src/ScriptingCore/DOM/Window.cpp

	${FIREBREATHSRC_DIRS}/src/ScriptingCore/Util/JSFakeArray.cpp

	${FIREBREATHSRC_DIRS}/src/ScriptingCore/BrowserHost.cpp
	${FIREBREATHSRC_DIRS}/src/ScriptingCore/CrossThreadCall.cpp
	${FIREBREATHSRC_DIRS}/src/ScriptingCore/JSAPIImpl.cpp
	${FIREBREATHSRC_DIRS}/src/ScriptingCore/JSAPIAuto.cpp
	${FIREBREATHSRC_DIRS}/src/ScriptingCore/JSAPISimple.cpp
	${FIREBREATHSRC_DIRS}/src/ScriptingCore/JSAPIProxy.cpp
	${FIREBREATHSRC_DIRS}/src/ScriptingCore/JSArray.cpp
	${FIREBREATHSRC_DIRS}/src/ScriptingCore/JSEvent.cpp
	${FIREBREATHSRC_DIRS}/src/ScriptingCore/JSFunction.cpp

	${FIREBREATHSRC_DIRS}/src/ScriptingCore/URI.cpp
	${FIREBREATHSRC_DIRS}/src/ScriptingCore/utf8_tools.cpp

	${FIREBREATHSRC_DIRS}/src/ScriptingCore/variant.cpp
	)

if (WIN32)
set (	SRCS_OS
	)
else (WIN32)
set (	SRCS_OS
	#${FIREBREATHSRC_DIRS}/src/ScriptingCore/utf8.c
	)
endif (WIN32)

include_directories ( 
	..
	../gen
	${FIREBREATHSRC_DIRS}/src/ScriptingCore
	)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif ()

add_library ( ScriptingCore STATIC
	${SRCS} 
	${SRCS_OS}
	)

target_link_libraries(ScriptingCore
    #${CMAKE_THREAD_LIBS_INIT}
    )
