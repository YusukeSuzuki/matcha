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

set(the_target "constants.compile")
project (${the_target})

enable_testing()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../include")

file(GLOB test_srcs "*.cpp")
add_executable(${the_target} ${test_srcs})

set(BUILD_FLAGS "")
if(CMAKE_COMPILER_IS_GNUCXX)
	set(BUILD_FLAGS "${BUILD_FLAGS} -std=c++0x -Wall -Werror -fpermissive -g")
endif()

set_source_files_properties(SOURCE ${the_target}.cpp PROPERTES COMPILE_FLAGS ${BUILD_FLAGS})

target_link_libraries(constants.compile matcha_math)
add_test(${the_target} ${CMAKE_CURRENT_BINARY_DIR}/${the_target})

