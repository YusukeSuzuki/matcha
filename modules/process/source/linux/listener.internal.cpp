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
#include "matcha/process/listener.hpp"
#include "matcha/process/port.hpp"
#include "matcha/process/bits/port_implementation_base.hpp"
#include "matcha/core/exception.hpp"
#include "listener.internal.hpp"

#include <iostream>

#include <unistd.h>

namespace matcha { namespace process {

listener::implementation::implementation() :
	epoll_fd_( epoll_create(default_epoll_size) )
{
	if(epoll_fd_ < 0)
	{
		throw( core::system_exception(MATCHA_EXCEPTION_WHERE.c_str(), errno) );
	}
}

listener::implementation::~implementation() noexcept
{
	close(epoll_fd_);
}

void
listener::implementation::add(std::shared_ptr<port> port)
{
	/// @note unstable
	
	epoll_event event = {};
	event.events = EPOLLIN;
	event.data.fd = port->implementation().get_fd();
	if( epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, port->implementation().get_fd(), &event) )
	{
		throw( core::system_exception(MATCHA_EXCEPTION_WHERE.c_str(), errno) );
	}

	fd_port_map_[port->implementation().get_fd()] = port;
}

void
listener::implementation::remove(std::shared_ptr<port> port)
{
	epoll_event event = {}; // for linux 2.6.9 or earlier

	if( epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, port->implementation().get_fd(), &event) )
	{
		throw( core::system_exception(MATCHA_EXCEPTION_WHERE.c_str(), errno) );
	}

	fd_port_map_.erase(port->implementation().get_fd());
}

std::vector< std::shared_ptr<port> >
listener::implementation::wait_for_events()
{
	/// @todo implement

	std::vector<epoll_event> events(fd_port_map_.size());
	int num = epoll_wait(epoll_fd_, &events[0], events.size(), -1);

	if(num < 0)
	{
		throw( core::system_exception(MATCHA_EXCEPTION_WHERE.c_str(), errno) );
	}

	std::vector< std::shared_ptr<port> > result;

	std::cout << MATCHA_EXCEPTION_WHERE << std::endl;
	std::cout << num << std::endl;

	while(num)
	{
		--num;
		std::cout << events[num].events << std::endl;
		if(events[num].events & EPOLLIN)
		{
			result.push_back(fd_port_map_[ events[num].data.fd ]);
		}

		if(events[num].events & EPOLLOUT)
		{
			result.push_back(fd_port_map_[ events[num].data.fd ]);
		}

		if(events[num].events & EPOLLRDHUP)
		{
			result.push_back(fd_port_map_[ events[num].data.fd ]);
		}

		if(events[num].events & EPOLLPRI)
		{
			result.push_back(fd_port_map_[ events[num].data.fd ]);
		}

		if(events[num].events & EPOLLERR)
		{
			result.push_back(fd_port_map_[ events[num].data.fd ]);
		}

		if(events[num].events & EPOLLHUP)
		{
			result.push_back(fd_port_map_[ events[num].data.fd ]);
		}

		if(events[num].events & EPOLLET)
		{
			result.push_back(fd_port_map_[ events[num].data.fd ]);
		}

		if(events[num].events & EPOLLONESHOT)
		{
			result.push_back(fd_port_map_[ events[num].data.fd ]);
		}
	}

	return result;
}

} // end of namespace process
} // end of namespace matcha

