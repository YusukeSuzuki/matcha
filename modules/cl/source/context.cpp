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

class context::implementation
{
public:
	implementation(
		const std::vector<device>& devices, context::callback_function callback) :
		callback_(callback)
	{
		std::vector<cl_device_id> ids(devices.size());

		{
			auto id = ids.begin();
			for(auto device : devices)
			{
				*id = device.implementation_->id();
				++id;
			}
		}

		cl_int success = 0;

		context_ =
			clCreateContext(NULL, devices.size(), &ids[0],
			callback_base, this, &success);

		if(!success) throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), success) );
	}

	implementation(device::type type, context::callback_function callback) :
		callback_(callback)
	{
		cl_int success = 0;
		context_ = clCreateContextFromType(
			NULL, device::implementation::to_device_type(type),
			callback_base, this, &success);

		if(!success) throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), success) );
	}

	/// to preserve
	void retain()
	{
		if(int err = clRetainContext(context_))
			throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	}

	/// to preserve
	void release()
	{
		if(int err = clReleaseContext(context_))
			throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	}

	static void callback_base(
		const char* errinfo, const void* private_info, size_t cb, void* user_data)
	{
		static_cast<implementation*>(user_data)->callback_(
			std::string(errinfo), private_info, cb);
	}

private:
	cl_context context_;
	context::callback_function callback_;
};

context::context(const std::vector<device>& devices, callback_function callback) :
	implementation_( new context::implementation(devices, callback) )
{
}

context::context(device::type type, callback_function callback) :
	implementation_( new context::implementation(type, callback) )
{
}


} // end of namespace Core
} // end of namespace Matcha

