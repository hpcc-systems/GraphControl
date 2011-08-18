# Component: ScriptingCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for ScriptingCore
#####################################################

project( ScriptingCore ) 

set (	SRCS 
	../gen/FireBreathWin.tlb.rule
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/DOM/Document.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/DOM/Element.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/DOM/Node.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/DOM/Window.cpp

	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/Util/JSFakeArray.cpp

	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/BrowserHost.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/CrossThreadCall.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/JSAPIImpl.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/JSAPIAuto.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/JSAPISimple.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/JSAPIProxy.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/JSArray.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/JSEvent.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/JSFunction.cpp

	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/URI.cpp
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/utf8_tools.cpp

	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/variant.cpp
	)

if (WIN32)
set (	SRCS_OS
	)
else (WIN32)
set (	SRCS_OS
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore/utf8.c
	)
endif (WIN32)

include_directories ( 
	..
	../gen
	${FIREBREATH_INCLUDE_DIRS}/src/ScriptingCore
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
