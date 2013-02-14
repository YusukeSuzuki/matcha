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

#include "socket_port.internal.hpp"
#include "matcha/core/exception.hpp"

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

namespace matcha { namespace process {

socket_port::implementation::implementation(uint32_t address, uint16_t port) :
	os_specific_port_implementation(),
	fd_( socket(AF_INET, SOCK_STREAM, 0) ),
	handler_( [](socket_port&, std::vector<uint8_t>&) -> void {} )
{
	if(fd_ < 0)
	{
		throw( core::system_exception(MATCHA_EXCEPTION_WHERE.c_str(), errno) );
	}
}

socket_port::implementation::~implementation() noexcept
{
	::close(fd_);
}

int
socket_port::implementation::get_fd()
{
	return fd_;
}

void
socket_port::implementation::handler(
	const socket_port::handler_function& handler)
{
	handler_ = handler;
}

const socket_port::handler_function&
socket_port::implementation::handler() const
{
	return handler_;
}

void
socket_port::implementation::write(const std::vector<uint8_t>& data)
{
	if( ::write(fd_, &data[0], data.size() * sizeof(uint8_t)) < 0 )
	{
		throw( core::system_exception(MATCHA_EXCEPTION_WHERE.c_str(), errno) );
	}
}

void
socket_port::implementation::write(const std::string& data)
{
	if(
		::write(fd_, data.c_str(), data.length() * sizeof(std::string::value_type)) < 0 )
	{
		throw( core::system_exception(MATCHA_EXCEPTION_WHERE.c_str(), errno) );
	}
}

} // end of namespace process
} // end of namespace matcha

