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
#ifndef MATCHA_PROCESS_SOCKET_PORT_INTERNAL_HPP__
#define MATCHA_PROCESS_SOCKET_PORT_INTERNAL_HPP__

#include "matcha/process/socket_port.hpp"
#include "matcha/process/bits/bits.linux.hpp"

namespace matcha { namespace process {

class socket_port::implementation : public os_specific_port_implementation
{
public:
	implementation() = delete;
	implementation(uint32_t address, uint16_t port);

	virtual ~implementation() noexcept;

	virtual int get_fd();

	void handler(const socket_port::handler_function& handler);
	const socket_port::handler_function& handler() const;

	void write(const std::vector<uint8_t>& data);
	void write(const std::string& data);

private:
	int fd_;
	socket_port::handler_function handler_;
};

} // end of namespace process
} // end of namespace matcha

#endif
