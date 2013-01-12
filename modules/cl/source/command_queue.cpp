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
#include "command_queue.internal.hpp"
#include "event.internal.hpp"

namespace matcha { namespace cl {

command_queue::command_queue(
	context& context, device& device, const std::set<property>& properties) :
	implementation_(
		new typename command_queue::implementation(context, device, properties) )
{
}

event
command_queue::enqueue_nd_range(kernel& kernel, size_t worksize)
{
	return
		event( std::shared_ptr<typename event::implementation>(
			new typename event::implementation(
				implementation_->enqueue_nd_range(kernel, worksize) ) ) );
}

event
command_queue::enqueue_read(
	buffer& buffer, bool block_read, size_t offset, size_t size_in_bytes,
	void* out_ptr, const std::vector<event>& wait_list)
{
	return
		event( std::shared_ptr<typename event::implementation>(
			new typename event::implementation(
				implementation_->enqueue_read(
					buffer, block_read, offset, size_in_bytes, out_ptr, wait_list) ) ) );
}

void
command_queue::wait_for(const std::vector<event>& wait_list)
{
	implementation_->wait_for(wait_list);
}

} // end of namespace Core
} // end of namespace Matcha

