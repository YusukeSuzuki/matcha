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
#ifndef __MATCAH_CL_BUFFER_INTERNAL_HPP_
#define __MATCAH_CL_BUFFER_INTERNAL_HPP_

#include "matcha/cl/cl.hpp"

#include <algorithm>

namespace matcha { namespace cl {

class buffer::implementation
{
public:
	implementation(
		context& context, const std::set<buffer::flag>& flags, size_t size) :
		mem_( clCreateBuffer(context, flags, size, nullptr) )
	{
	}

	implementation(
		context& context, const std::set<buffer::flag>& flags,
		size_t size, void* host_ptr) :
		mem_( clCreateBuffer(context, flags, size, host_ptr) )
	{
	}

	static cl_mem_flags to_mem_flags(const std::set<buffer::flag>& flags)
	{
		cl_mem_flags result = 0;
		for(auto i : flags)
		{
			#define MATCHA_TEMP_BUFFER_FLAG_MACRO(x,y) \
				case buffer::flag::x:  result = result | y; break;
				
			switch(i)
			{
				MATCHA_TEMP_BUFFER_FLAG_MACRO(read_write, CL_MEM_READ_WRITE)
				MATCHA_TEMP_BUFFER_FLAG_MACRO(write_only, CL_MEM_WRITE_ONLY)
				MATCHA_TEMP_BUFFER_FLAG_MACRO(read_only, CL_MEM_READ_ONLY)
				MATCHA_TEMP_BUFFER_FLAG_MACRO(use_host_ptr, CL_MEM_USE_HOST_PTR)
				MATCHA_TEMP_BUFFER_FLAG_MACRO(alloc_host_ptr, CL_MEM_ALLOC_HOST_PTR)
				MATCHA_TEMP_BUFFER_FLAG_MACRO(copy_host_ptr, CL_MEM_COPY_HOST_PTR)
			}
			#undef MATCHA_TEMP_BUFFER_FLAG_MACRO
		}
		return result;
	}

	static cl_mem clCreateBuffer(
		context& context, const std::set<buffer::flag>& flags,
		size_t size, void* host_ptr)
	{
		cl_int err;
		auto mem = ::clCreateBuffer(*context.implementation(),
			to_mem_flags(flags), size, host_ptr, &err);

		if(err) throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );

		return mem;
	}

	::cl_mem& mem()
	{
		return mem_;
	}

	const ::cl_mem& mem() const
	{
		return mem_;
	}

	operator ::cl_mem()
	{
		return mem_;
	}

private:
	::cl_mem mem_;
};



} // end of namespace Core
} // end of namespace Matcha

#endif
