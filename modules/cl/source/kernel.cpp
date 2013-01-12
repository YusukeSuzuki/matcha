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
#include "kernel.internal.hpp"

namespace matcha { namespace cl {

kernel::kernel(program& program, const std::string& name) :
	implementation_( new implementation(program, name) )
{
}

kernel::kernel(const kernel& rhs) :
	implementation_( rhs.implementation_ )
{
}

kernel&
kernel::operator=(const kernel& rhs)
{
	this->implementation_ = rhs.implementation_;
	return *this;
}

kernel::kernel(const std::shared_ptr<implementation>& ptr) :
	implementation_(ptr)
{
}

std::vector<kernel>
kernel::create_kernels_in_program(program& program)
{
	cl_uint size = 0;

	if(auto err =
		clCreateKernelsInProgram(*program.implementation(), 0, nullptr, &size) )
	{
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	}

	std::vector<cl_kernel> kernels(size);

	if(!kernels.empty())
		if( auto err =
				clCreateKernelsInProgram(*program.implementation(), kernels.size(),
			&kernels[0], &size) )
		{
			throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
		}

	std::vector<kernel> result;

	for(auto i : kernels)
	{
		result.push_back( kernel(
			std::shared_ptr<typename kernel::implementation>(
				new typename kernel::implementation(i) ) ) );
	}

	return result;
}

kernel&
kernel::set_argument(unsigned int index, buffer& buffer)
{
	implementation_->set_argument(index, buffer);
	return *this;
}

} // end of namespace Core
} // end of namespace Matcha

