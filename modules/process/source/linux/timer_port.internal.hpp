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
#ifndef MATCHA_PROCESS_TIMER_PORT_INTERNAL_HPP__
#define MATCHA_PROCESS_TIMER_PORT_INTERNAL_HPP__

#include "matcha/process/timer_port.hpp"
#include "matcha/process/bits/port_implementation_base.hpp"

namespace matcha { namespace process {

class timer_port::implementation : public port_implementation_base
{
public:
	implementation();
	virtual ~implementation() noexcept;

	void handler(const timer_port::handler_function& handler);
	const timer_port::handler_function& handler() const;

	void start(long sec, long nanosec, bool is_interval);

	void send(timer_port& port, event& event);
	void stop();

	uint64_t read();

	virtual int get_fd();

private:
	int fd_;
	timer_port::handler_function handler_;
};

} // end of namespace process
} // end of namespace matcha

#endif
