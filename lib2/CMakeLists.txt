################################################################################
#    HPCC SYSTEMS software Copyright (C) 2012 HPCC Systems.
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
################################################################################

cmake_minimum_required(VERSION 2.8)

PROJECT(lib2)

if (APPLE)
	list(APPEND DYLIBS ${FREETYPE_LIBRARIES})

	foreach(dylib ${DYLIBS})
		get_filename_component(dylib_path ${dylib} REALPATH)
		install(PROGRAMS "${dylib_path}" DESTINATION "${FBSTRING_PluginName}.plugin/Contents/MacOS")
		get_filename_component(dylib_name_ext ${dylib_path} NAME)

		set(fixupCommand "${fixupCommand}\r\nexecute_process(COMMAND install_name_tool -change \"${dylib_path}\" \"@loader_path/${dylib_name_ext}\" \${file})")

		install(CODE "
			file(GLOB files \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/${FBSTRING_PluginName}.plugin/Contents/MacOS/*\")
			foreach(file \${files})
				${fixupCommand}
			endforeach ()
		")
	endforeach(dylib)
endif()
