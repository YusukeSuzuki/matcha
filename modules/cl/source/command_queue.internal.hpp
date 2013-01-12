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
#ifndef __MATCAH_CL_COMMAND_QUEUE_INTERNAL_HPP_
#define __MATCAH_CL_COMMAND_QUEUE_INTERNAL_HPP_

#include "matcha/cl/cl.hpp"

#include "kernel.internal.hpp"
#include "event.internal.hpp"

#include <algorithm>

namespace matcha { namespace cl {

class command_queue::implementation
{
public:
	implementation(context& context, device& device,
		const std::set<command_queue::property>& properties)
	{
		cl_int err = 0;
		command_queue_ = clCreateCommandQueue(
			*context.implementation(), *device.implementation(),
			to_queue_properties(properties), &err);

		if(err) throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	}

	static cl_command_queue_properties
	to_queue_properties(
		const std::set<command_queue::property>& properties)
	{
		cl_command_queue_properties result = 0;

		for(auto i : properties)
		{
			#define MATCHA_TEMP_COMMAND_QUEUE_PROPERTIES_MACRO(x,y) \
				case command_queue::property::x: result = result | y; break;

			switch(i)
			{
				MATCHA_TEMP_COMMAND_QUEUE_PROPERTIES_MACRO(
					out_of_order_exec_mode_enable, CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE)
				MATCHA_TEMP_COMMAND_QUEUE_PROPERTIES_MACRO(
					profiling_enable, CL_QUEUE_PROFILING_ENABLE)
			}

			#undef MATCHA_TEMP_COMMAND_QUEUE_PROPERTIES_MACRO
		}

		return result;
	}

	cl_event enqueue_nd_range(kernel& kernel, size_t worksize)
	{
		cl_event result;
		size_t offsets[1] = {0};
		size_t workesizes[1] = {worksize};

		if(auto err = clEnqueueNDRangeKernel(
			command_queue_, *kernel.implementation_, 1, offsets, workesizes,
			nullptr, 0, nullptr, &result) )
		{
			throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
		}

		return result;
	}

	cl_event enqueue_read(
		buffer& buffer, bool block_read, size_t offset, size_t size_in_bytes,
		void* out_ptr, const std::vector<event>& wait_list)
	{
		cl_event result;

		std::vector<cl_event> wait_events(
			event::implementation::to_cl_events(wait_list) );

		if(auto err = clEnqueueReadBuffer(
			command_queue_, *buffer.implementation_, static_cast<cl_bool>(block_read),
			offset, size_in_bytes, out_ptr, wait_events.size(), &wait_events[0], &result) )
		{
			throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
		}

		return result;
	}

	void wait_for(const std::vector<event>& wait_list)
	{
		if(auto err = clWaitForEvents(wait_list.size(),
				&event::implementation::to_cl_events(wait_list)[0]) )
		{
			throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
		}
	}

private:
	cl_command_queue command_queue_;
};

} // end of namespace Core
} // end of namespace Matcha

#endif
