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
	set(the_target_static "matcha_${name}_static")
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
	add_library(${the_target_static} STATIC ${lib_srcs} ${ext_lib_srcs})


	set(BUILD_FLAGS "")
	if(CMAKE_COMPILER_IS_GNUCXX)
		set(BUILD_FLAGS "${BUILD_FLAGS} -std=c++0x -Wall -Werror -g")
	endif()
	if(CMAKE_CXX_COMPILER MATCHES ".*clang\\+\\+.*")
		set(BUILD_FLAGS "${BUILD_FLAGS} -std=c++0x -Wall -Werror -g")
	endif()

	set_source_files_properties(SOURCE ${lib_srcs} PROPERTIES COMPILE_FLAGS ${BUILD_FLAGS})
	set_source_files_properties(SOURCE ${ext_lib_srcs} PROPERTIES COMPILE_FLAGS ${BUILD_FLAGS})
	set_target_properties(${the_target} PROPERTIES VERSION 1.0.0 SOVERSION 1)
	set_target_properties(${the_target_static} PROPERTIES OUTPUT_NAME "${the_target}")

	foreach(d ${lib_external})
		target_link_libraries(${the_target} ${d})
		target_link_libraries(${the_target_static} ${d})
	endforeach()

	foreach(d ${ARGN})
		target_link_libraries(${the_target} matcha_${d})
		target_link_libraries(${the_target_static} matcha_${d})
	endforeach()

	install(TARGETS ${the_target} DESTINATION lib PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
	install(TARGETS ${the_target_static} DESTINATION lib PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
endmacro()

# --------------------------------------------------------------------------------
macro (matcha_test_definition name)
	set(the_target "${name}")
	project (${the_target})

	enable_testing()

	foreach(d ${ARGN})
		include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../${d}/include)
	endforeach()

	file(GLOB test_srcs "${the_target}.cpp")
	add_executable(${the_target} ${test_srcs})

	set(BUILD_FLAGS "")
	if(CMAKE_COMPILER_IS_GNUCXX)
		set(BUILD_FLAGS "${BUILD_FLAGS} -std=c++0x -Wall -Werror -fpermissive -g")
	endif()
	if(CMAKE_CXX_COMPILER MATCHES ".*clang\\+\\+.*")
		set(BUILD_FLAGS "${BUILD_FLAGS} -std=c++0x -Wall -Werror -g")
	endif()

	set_source_files_properties(
		SOURCE ${test_srcs} PROPERTES COMPILE_FLAGS ${BUILD_FLAGS})

	foreach(d ${ARGN})
		target_link_libraries(${the_target} matcha_${d})
	endforeach()

	target_link_libraries(${the_target} boost_unit_test_framework)

	add_test(${the_target} ${CMAKE_CURRENT_BINARY_DIR}/${the_target})
endmacro()

