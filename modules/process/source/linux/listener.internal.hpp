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
#ifndef MATCHA_PROCESS_LISTENER_INTERNAL_HPP__
#define MATCHA_PROCESS_LISTENER_INTERNAL_HPP__

#include "matcha/process/listener.hpp"

#include <map>
#include <tuple>

#include <sys/epoll.h>

namespace matcha { namespace process {

class listener::implementation
{
public:
	const int default_epoll_size = 32;

	implementation();
	virtual ~implementation() noexcept;

	void add(std::shared_ptr<port> port);
	void remove(std::shared_ptr<port> port);

	std::vector<std::shared_ptr<port>> wait_for_events();

private:
	int epoll_fd_;
	std::map<int, std::shared_ptr<port>> fd_port_map_;
};

} // end of namespace process
} // end of namespace matcha

#endif
