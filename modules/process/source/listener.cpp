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
#include "listener.internal.hpp"

namespace matcha { namespace process {

listener::listener() :
	implementation_( new listener::implementation() )
{
}

listener::~listener() noexcept
{
}

listener&
listener::add(std::shared_ptr<port> port)
{
	implementation_->add(port);
	return *this;
}

listener&
listener::remove(std::shared_ptr<port> port)
{
	implementation_->remove(port);
	return *this;
}

std::vector<std::shared_ptr<port>>
listener::wait_for_events()
{
	return implementation_->wait_for_events();
}

} // end of namespace process
} // end of namespace matcha

