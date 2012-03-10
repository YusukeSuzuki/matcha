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

matcha_project_decraration(math)

file(GLOB lib_srcs "*.cpp")

set(Implementation "standard" CACHE STRING "math: Implementation(standard, amd64_sse4)")

if(${Implementation} STREQUAL "standard")
	file(GLOB ext_lib_srcs "standard/*.cpp")
elseif(${Implementation} STREQUAL "amd64_sse4")
	file(GLOB ext_lib_srcs "amd64_sse4/*.cpp")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -msse4")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -msse4")
else()
endif()

set(lib_external stdc++ m)
matcha_library_definition(math core)

