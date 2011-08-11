# Component: ScriptingCore
#####################################################
# Description:
# ------------
#	 Cmake Input File for ScriptingCore
#####################################################

project( ScriptingCore ) 

set (	SRCS 
	../gen/FireBreathWin.tlb.rule
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/DOM/Document.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/DOM/Element.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/DOM/Node.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/DOM/Window.cpp

	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/Util/JSFakeArray.cpp

	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/BrowserHost.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/CrossThreadCall.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/JSAPIImpl.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/JSAPIAuto.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/JSAPISimple.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/JSAPIProxy.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/JSArray.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/JSEvent.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/JSFunction.cpp

	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/URI.cpp
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/utf8_tools.cpp

	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/variant.cpp
	)

if (WIN32)
set (	SRCS_OS
	)
else (WIN32)
set (	SRCS_OS
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore/utf8.c
	)
endif (WIN32)

include_directories ( 
	..
	../gen
	${EXTERNALS_DIRECTORY}/firebreath/src/ScriptingCore
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
