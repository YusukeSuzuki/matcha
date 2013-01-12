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
#include "buffer.internal.hpp"

namespace matcha { namespace cl {

buffer::buffer(context& context, const std::set<buffer::flag>& flags, size_t size) :
	implementation_( new typename buffer::implementation(context, flags, size) )
{
}

buffer::buffer(context& context, const std::set<buffer::flag>& flags, 
	size_t size, void* host_ptr) :
	implementation_(
		new typename buffer::implementation(context, flags, size, host_ptr) )
{
}

std::shared_ptr<typename buffer::implementation>
buffer::implementation()
{
	return implementation_;
}

const std::shared_ptr<typename buffer::implementation>
buffer::implementation() const
{
	return implementation_;
}

} // end of namespace Core
} // end of namespace Matcha

