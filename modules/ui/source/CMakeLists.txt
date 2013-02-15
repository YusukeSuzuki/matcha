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

matcha_project_decraration(ui)

file(GLOB lib_srcs "*.cpp")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

file(GLOB sys_lib_srcs "gtk3/*.cpp")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtk3)
include_directories(${GTK3_INCLUDE_DIRS})

set(lib_external stdc++ msgpack pthread ${GTK3_LIBRARIES})
matcha_library_definition(ui core)

