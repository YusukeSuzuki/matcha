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

program::program(context& context, const std::vector<std::string>& sources) :
	implementation_( new typename program::implementation(context, sources) )
{
}

program::program(const program& rhs) :
	implementation_( new typename program::implementation(*rhs.implementation_) )
{
}

program&
program::operator=(const program& rhs)
{
	implementation_ = rhs.implementation_;
	return *this;
}

program::~program() noexcept
{
}

program&
program::build(const std::vector<device>& devices)
{
	std::vector<cl_device_id> ids = device::implementation::to_device_ids(devices);

	if(int err = clBuildProgram(
			implementation_->program(), ids.size(), &ids[0],  "", nullptr, nullptr) )
	{
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	}

	return *this;
}

std::vector<kernel>
program::create_all_kernels()
{
	return kernel::create_kernels_in_program(*this);
}

std::shared_ptr<typename program::implementation>
program::implementation()
{
	return implementation_;
}

const std::shared_ptr<typename program::implementation>
program::implementation() const
{
	return implementation_;
}

kernel
program::create_kernel(const std::string& name)
{
	return kernel(*this, name);
}

std::vector<kernel>
program::create_kernels(const std::vector<std::string>& names)
{
	std::vector<kernel> result;
	
	std::for_each(names.begin(), names.end(),
		[&result, this](const std::string& name) -> void
		{
			result.push_back( kernel(*this, name) );
		});

	return result;
}

namespace internal {

template<typename T>
inline auto get_info(cl_program program, cl_program_info info) -> T	
{
	static_assert(std::is_arithmetic<T>(), "type error");

	size_t size = 0;
	if(int err = clGetProgramInfo(program, info, 0, NULL, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	T result;
	if(int err = clGetProgramInfo(program, info, size, &result, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	return result;
}

template<>
inline auto get_info<std::string>(cl_program program, cl_program_info info) -> std::string
{
	size_t size = 0;
	if(int err = clGetProgramInfo(program, info, 0, NULL, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	std::vector<char> buf(size);
	if(int err = clGetProgramInfo(program, info, size, &buf[0], &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	return std::string(&buf[0]);
}

} // end of namespace internal

#ifdef MATCHA_PROGRAM_INFO_DEFINITION_TEMP_MACRO
#error "macro error"
#else
#define MATCHA_PROGRAM_INFO_DEFINITION_TEMP_MACRO(X) \
template<> \
auto program::info<program::info_name::X>() const -> \
	program::info_type<program::info_name::X>::type \
{ \
	return internal::get_info< program::info_type<program::info_name::X>::type >( \
		*implementation_, implementation::to_program_info(info_name::X) ); \
}

MATCHA_PROGRAM_INFO_DEFINITION_TEMP_MACRO( reference_count )
// MATCHA_PROGRAM_INFO_DEFINITION_TEMP_MACRO( context )
MATCHA_PROGRAM_INFO_DEFINITION_TEMP_MACRO( num_devices )
//MATCHA_PROGRAM_INFO_DEFINITION_TEMP_MACRO( devices )
MATCHA_PROGRAM_INFO_DEFINITION_TEMP_MACRO( source )
//MATCHA_PROGRAM_INFO_DEFINITION_TEMP_MACRO( binary_sizes )
//MATCHA_PROGRAM_INFO_DEFINITION_TEMP_MACRO( binaries )

#undef MATCHA_PROGRAM_INFO_DEFINITION_TEMP_MACRO
#endif

} // end of namespace Core
} // end of namespace Matcha

