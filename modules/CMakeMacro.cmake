# Matcha Robotics Application Framework
#
# Copyright (C) 2011 Yusuke Suzuki 
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.

cmake_minimum_required(VERSION 2.6)

# --------------------------------------------------------------------------------

macro (matcha_header_install_definition name)
	file(GLOB headers "include/matcha/${name}/*.hpp")
	install(FILES ${headers} DESTINATION "include/matcha/${name}")
	if(EXISTS "include/matcha/${name}/bits")
		file(GLOB bits_headers "include/matcha/${name}/bits/*.hpp")
		install(FILES ${bits_headers} DESTINATION "include/matcha/${name}/bits")
	endif()
endmacro()

# --------------------------------------------------------------------------------

macro (matcha_project_decraration name)
	set(the_target "matcha_${name}")
	project(${the_target})
endmacro()

# --------------------------------------------------------------------------------
macro (matcha_library_definition name)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
	include_directories(${CMAKE_CURRENT_BINARY_DIR}/../include)

	foreach(d ${ARGN})
		include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../${d}/include)
	endforeach()

	add_library(${the_target} SHARED ${lib_srcs} ${ext_lib_srcs})

	set(BUILD_FLAGS "")
	if(CMAKE_COMPILER_IS_GNUCXX)
		set(BUILD_FLAGS "${BUILD_FLAGS} -std=c++0x -Wall -Werror -g")
	endif()

	set_source_files_properties(SOURCE ${lib_srcs} PROPERTES COMPILE_FLAGS ${BUILD_FLAGS})
	set_source_files_properties(SOURCE ${ext_lib_srcs} PROPERTES COMPILE_FLAGS ${BUILD_FLAGS})
	set_target_properties(${the_target} PROPERTIES VERSION 1.0.0 SOVERSION 1)

	foreach(d ${lib_external})
		target_link_libraries(${the_target} ${d})
	endforeach()

	foreach(d ${ARGN})
		target_link_libraries(${the_target} matcha_${d})
	endforeach()

	install(TARGETS ${the_target} DESTINATION lib PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
endmacro()

