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

std::vector<platform>
platform::get()
{
	cl_uint num_platforms = 0;

	if(cl_int errornumber = clGetPlatformIDs(0, nullptr, &num_platforms))
	{
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), errornumber) );
	}

	std::vector<cl_platform_id> ids(num_platforms);

	if(cl_int errornumber = clGetPlatformIDs(num_platforms, &ids[0], NULL))
	{
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), errornumber) );
	}

	std::vector<platform> platforms;

	for(auto id : ids)
	{
		platforms.push_back(
			platform(std::shared_ptr<implementation>( new implementation(id) )) );
	}

	return std::move(platforms);
}

platform::platform(std::shared_ptr<platform::implementation> a_implementation) :
	implementation_(a_implementation)
{
}

platform::~platform() noexcept
{
}

std::string
platform::info(platform::info_name param)
{
	size_t size = 0;

	if( cl_int errornumber = clGetPlatformInfo(
		this->implementation_->id(), implementation::to_platform_info(param),
		0, NULL, &size) )
	{
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), errornumber) );
	}

	std::vector<char> buf(size);

	if( cl_int errornumber = clGetPlatformInfo(
		this->implementation_->id(), implementation::to_platform_info(param),
		size, &buf[0], NULL) )
	{
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), errornumber) );
	}

	return std::string(&buf[0]);
}

std::vector<device>
platform::devices(device::type t)
{
	cl_uint num_devices = 0;

	if(cl_int errornumber = clGetDeviceIDs(
		implementation_->id(), device::implementation::to_device_type(t),
		0, nullptr, &num_devices) )
	{
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), errornumber) );
	}

	std::vector<cl_device_id> ids(num_devices);

	if(cl_int errornumber = clGetDeviceIDs(
		implementation_->id(), device::implementation::to_device_type(t),
		num_devices, &ids[0], nullptr) )
	{
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), errornumber) );
	}

	std::vector<device> devices;

	for(auto id : ids)
	{
		devices.push_back( device(std::shared_ptr<device::implementation>(
			new device::implementation(id) ) ) );
	}

	return std::move(devices);
}

} // end of namespace Core
} // end of namespace Matcha


