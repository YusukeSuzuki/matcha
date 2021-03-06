/*
 * Matcha Robotics Application Framework
 *
 * Copyright (C) 2011 Yusuke Suzuki 
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "matcha/process/socket_port.hpp"
#include "socket_port.internal.hpp"

namespace matcha { namespace process {

socket_port::socket_port(uint32_t address, uint16_t port) :
	implementation_( new typename socket_port::implementation(address, port) )
{
}

socket_port::~socket_port() noexcept
{
}

os_specific_port_implementation&
socket_port::implementation()
{
	return *implementation_;
}

core::optional<event>
socket_port::read()
{
	return core::none;
}

void
socket_port::send(event& event)
{
}

} // end of namespace process
} // end of namespace matcha

