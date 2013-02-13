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
#ifndef MATCHA_PROCESS_TIMER_PORT_HPP__
#define MATCHA_PROCESS_TIMER_PORT_HPP__

#include <matcha/process/port.hpp>

#include <cstdint>
#include <ctime>
#include <functional>
#include <memory>

namespace matcha { namespace process {

class timer_port : public port
{
public:
	timer_port();
	virtual ~timer_port() noexcept;

	static std::shared_ptr<timer_port> create();

	virtual core::optional<event> read();
	virtual void send(event& event);
	virtual port_implementation_base& implementation();

	using handler_function = std::function<void(timer_port&, uint64_t expiration)>;

	timer_port& handler(const timer_port::handler_function& handler);
	const handler_function& handler() const;

	timer_port& start(long sec, long nanosec, bool is_interval);
	timer_port& stop();

private:
	class implementation;
	std::shared_ptr<typename timer_port::implementation> implementation_;
};

} // end of namespace process
} // end of namespace matcha

#endif
