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

enable_testing()

set(MATCHA_OSX FALSE)
set(MATCHA_WIN32 FALSE)
set(MATCHA_LINUX FALSE)

if(APPLE)
	set(MATCHA_OSX TRUE)
	add_definitions(-DMATCHA_OSX)
elseif(WIN32)
	set(MATCHA_WIN32 TRUE)
	add_definitions(-DMATCHA_WIN32)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	set(MATCHA_LINUX TRUE)
	add_definitions(-DMATCHA_LINUX)
else()
	message(FATAL_ERROR "Unsupported OS")
endif()

add_subdirectory (modules)

