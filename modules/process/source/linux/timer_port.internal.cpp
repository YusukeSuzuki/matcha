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

#include "timer_port.internal.hpp"
#include "matcha/core/exception.hpp"

#include <unistd.h>
#include <sys/timerfd.h>

namespace matcha { namespace process {

timer_port::implementation::implementation() :
	port_implementation_base(),
	fd_( timerfd_create(CLOCK_REALTIME , 0) ),
	handler_( [](timer_port&, uint64_t) -> void {} )
{
	if(fd_ < 0)
	{
		throw( core::system_exception(MATCHA_EXCEPTION_WHERE.c_str(), errno) );
	}
}

timer_port::implementation::~implementation() noexcept
{
	close(fd_);
}

int
timer_port::implementation::get_fd()
{
	return fd_;
}

void
timer_port::implementation::start(long sec, long nanosec, bool is_interval)
{
	struct itimerspec t =
		{ {is_interval ? sec : 0, is_interval ? nanosec : 0}, {sec, nanosec}};
		
	if( timerfd_settime(fd_, 0, &t, nullptr) )
	{
		throw( core::system_exception(MATCHA_EXCEPTION_WHERE.c_str(), errno) );
	}
}

void
timer_port::implementation::stop()
{
}

uint64_t
timer_port::implementation::read()
{
	uint64_t res = 0;
	auto ret = ::read(fd_, &res, sizeof(res));
	if(ret < 0)
	{
		throw( core::system_exception(MATCHA_EXCEPTION_WHERE.c_str(), errno) );
	}
	else if(static_cast<decltype(res)>(ret) < res)
	{
		throw(core::none);
	}

	return res;
}

void
timer_port::implementation::send(timer_port& port, event& event)
{
	handler_(port, event.content().cast<uint64_t>());
}

void
timer_port::implementation::handler(const timer_port::handler_function& handler)
{
	handler_ = handler;
}

const timer_port::handler_function&
timer_port::implementation::handler() const
{
	return handler_;
}

} // end of namespace process
} // end of namespace matcha

