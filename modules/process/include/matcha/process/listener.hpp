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
#ifndef MATCHA_PROCESS_LISTENER_HPP__
#define MATCHA_PROCESS_LISTENER_HPP__

#include <memory>

namespace matcha { namespace process {

class listener
{
public:
	listener();
	virtual ~listener() noexcept;

private:
	class implementation;

	std::unique_ptr<implementation> implementation_;
};


} // end of namespace process
} // end of namespace matcha

#endif
