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
#ifndef MATCHA_PROCESS_SOCKET_PORT_HPP__
#define MATCHA_PROCESS_SOCKET_PORT_HPP__

#include <matcha/process/port.hpp>

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace matcha { namespace process {

class socket_port : port
{
public:
	socket_port() = delete;
	socket_port(uint32_t address, uint16_t port);

	virtual ~socket_port() noexcept;

	virtual os_specific_port_implementation& implementation();
	virtual core::optional<event> read();
	virtual void send(event& event);

	using handler_function =
		std::function<void(socket_port&, std::vector<uint8_t>& data)>;

	socket_port& handler(const socket_port::handler_function& handler);
	const handler_function& handler() const;

	socket_port& write(std::vector<uint8_t>& data);
	socket_port& write(std::string& data);

private:
	class implementation;
	std::shared_ptr<typename socket_port::implementation> implementation_;
};

/*
class listen_port : public socket_port
{
public:
	listen_port& handle(event& event);

private:
	class implementation;
	std::shared_ptr<typename listen_port::implementation> implementation_;
};
*/

} // end of namespace process
} // end of namespace matcha

#endif
