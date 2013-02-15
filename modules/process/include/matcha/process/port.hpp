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
#ifndef MATCHA_PROCESS_PORT_HPP__
#define MATCHA_PROCESS_PORT_HPP__

#include <matcha/core/optional.hpp>

#include <matcha/process/event.hpp>
#include <matcha/process/listener.hpp>

#include <matcha/process/bits/bits.hpp>

#include <memory>


namespace matcha {
	
extern template class core::optional<process::event>;

namespace process {

class os_specific_port_implementation;

class port
{
public:
	port();
	virtual ~port() noexcept;

	virtual os_specific_port_implementation& implementation() = 0;

	virtual core::optional<event> read() = 0;
	virtual void send(event& event) = 0;

	port& add_to_listener(listener& listener);

private:
	class implementation;
	std::shared_ptr<typename port::implementation> implementation_;

	friend bool operator ==(const port& lhs, const port& rhs);
	friend bool operator !=(const port& lhs, const port& rhs);
	friend bool operator <(const port& lhs, const port& rhs);
	friend bool operator <=(const port& lhs, const port& rhs);
	friend bool operator >(const port& lhs, const port& rhs);
	friend bool operator >=(const port& lhs, const port& rhs);
};

bool operator ==(const port& lhs, const port& rhs);
bool operator !=(const port& lhs, const port& rhs);
bool operator <(const port& lhs, const port& rhs);
bool operator <=(const port& lhs, const port& rhs);
bool operator >(const port& lhs, const port& rhs);
bool operator >=(const port& lhs, const port& rhs);

} // end of namespace process
} // end of namespace matcha

#endif
