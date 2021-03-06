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
#include "matcha/cl/cl.hpp"

#include "internal.hpp"

namespace matcha { namespace cl {

context::context(const std::vector<device>& devices, callback_function callback) :
	implementation_( new typename context::implementation(devices, callback) )
{
}

context::context(const std::vector<device>& devices) :
	implementation_( new typename context::implementation(devices) )
{
}

context::context(device::type type, callback_function callback) :
	implementation_( new typename context::implementation(type, callback) )
{
}

context::context(device::type type) :
	implementation_( new typename context::implementation(type) )
{
}

std::shared_ptr<typename context::implementation>
context::implementation()
{
	return this->implementation_;
}

program
context::create_program(const std::vector<std::string>& sources)
{
	return program(*this, sources);
}

} // end of namespace Core
} // end of namespace Matcha

