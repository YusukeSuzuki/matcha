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
#ifndef __MATCAH_CL_KERNEL_INTERNAL_HPP_
#define __MATCAH_CL_KERNEL_INTERNAL_HPP_

#include "matcha/cl/cl.hpp"

#include "buffer.internal.hpp"

#include <algorithm>

namespace matcha { namespace cl {

class kernel::implementation
{
public:
	implementation(const program& program, const std::string& name)
	{
		cl_int err = 0;

		kernel_ = clCreateKernel(
			*program.implementation(), name.c_str(), &err);

		if(err) throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	}

	implementation(cl_kernel kernel) : kernel_(kernel) {}

	void set_argument(unsigned int index, buffer& buffer)
	{
		if(int err = clSetKernelArg(
			kernel_, index, sizeof(cl_mem),
			&( buffer.implementation()->mem() )) )
		{
			throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
		}
	}

	void set_argument(unsigned int index, size_t size, void* ptr)
	{
		if(int err = clSetKernelArg(kernel_, index, size, ptr) )
		{
			throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
		}
	}

	operator cl_kernel()
	{
		return kernel_;
	}

private:
	cl_kernel kernel_;
};


} // end of namespace Core
} // end of namespace Matcha

#endif
