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

include(CMakeMacro.cmake NO_POLICY_SCOPE)

add_subdirectory (core)
#add_subdirectory (utilities)
add_subdirectory (process)
add_subdirectory (math)
add_subdirectory (image)
#add_subdirectory (image_io)
add_subdirectory (cl)
#add_subdirectory (process)
#add_subdirectory (device)
#add_subdirectory (experimental)
#add_subdirectory (opencl)
#add_subdirectory (math.opencl)
#add_subdirectory (image.opencl)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Yusuke Suzuki")
include(CPack)

