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
#include "matcha/core/any.hpp"
#include "matcha/process/port.hpp"
#include "matcha/process/timer_port.hpp"
#include "timer_port.internal.hpp"

namespace matcha { namespace process {

timer_port::timer_port() : port(),
	implementation_( new typename timer_port::implementation() )
{
}

timer_port::~timer_port() noexcept
{
}

std::shared_ptr<timer_port>
timer_port::create()
{
	return std::shared_ptr<timer_port>( new timer_port() );
}

timer_port&
timer_port::start(long sec, long nanosec, bool is_interval)
{
	implementation_->start(sec, nanosec, is_interval);
	return *this;
}

timer_port&
timer_port::stop()
{
	implementation_->stop();
	return *this;
}

void
timer_port::send(event& event)
{
	implementation_->send(*this, event);
}

core::optional<event>
timer_port::read()
{
	try
	{
		return event( core::any( implementation_->read() ) );
	}
	catch( core::none_t& n )
	{
		return n;
	}
}

os_specific_port_implementation&
timer_port::implementation()
{
	return *implementation_;
}

timer_port&
timer_port::handler(const timer_port::handler_function& handler)
{
	implementation_->handler(handler);
	return *this;
}

const timer_port::handler_function&
timer_port::handler() const
{
	return implementation_->handler();
}

} // end of namespace process
} // end of namespace matcha

