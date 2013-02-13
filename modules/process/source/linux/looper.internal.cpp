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
#include "matcha/process/looper.hpp"
#include "matcha/process/port.hpp"
#include "matcha/core/exception.hpp"
#include "looper.internal.hpp"

namespace matcha { namespace process {

looper::implementation::implementation(looper* looper) :
	looper_(looper),
	before_run_handler_( empty_handler )
{
}

looper::implementation::~implementation() noexcept
{
}

looper::before_run_handler_function&
looper::implementation::before_run_handler()
{
	return before_run_handler_;
}

void
looper::implementation::run()
{
	before_run_handler_(*looper_);

	for(;;)
	{
		auto ports = listener_.wait_for_events();

		for(auto& port : ports)
		{
			if(auto event = port->read())
			{
				port->send(*event);
			}
		}
	}
}

void
looper::implementation::quit()
{
}

matcha::process::listener&
looper::implementation::listener()
{
	return listener_;
}

const matcha::process::listener&
looper::implementation::listener() const
{
	return listener_;
}

} // end of namespace process
} // end of namespace matcha

