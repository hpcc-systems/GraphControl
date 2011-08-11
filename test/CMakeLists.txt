# Component: test
#####################################################
# Description:
# ------------
#	 Cmake Input File for test
#####################################################

project( test ) 

set (	SRCS 
	test.cpp
	)

include_directories ( 
	../graphdb
	../graphrender
	${EXTERNALS_DIRECTORY}/agg/include
	)

if (WIN32)
else  (WIN32)
if (GTK_FOUND)
	include_directories ( ${GTK_INCLUDE_DIRS} )
else (GTK_FOUND)
	message("GTK Not Found")
endif (GTK_FOUND)
endif (WIN32)

if (Boost_FOUND)
	include_directories ( ${Boost_INCLUDE_DIRS}	)
	link_directories ( ${Boost_LIBRARY_DIRS} )
endif ()

ADD_DEFINITIONS( -D_UNICODE )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")

add_executable ( test ${SRCS} )
add_dependencies (test 
	graphdb 
	graphrender
	)

target_link_libraries( test 
	graphdb 
	graphrender
	)

if (WIN32)
else  (WIN32)
if (GTK_FOUND)
target_link_libraries( test
	${GTK_LIBRARIES}
	)
else (GTK_FOUND)
	message("GTK Not Found")
endif (GTK_FOUND)
endif (WIN32)

