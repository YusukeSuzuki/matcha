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

