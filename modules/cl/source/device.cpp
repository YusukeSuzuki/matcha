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

device::device(std::shared_ptr<device::implementation> a_implementation) :
	implementation_(a_implementation)
{
}

device::~device() noexcept
{
}

template<>
auto device::info<device::info_name::type>() const ->
	device::info_type<device::info_name::type>::type
{
	size_t size = 0;

	if(int err = clGetDeviceInfo(
		*implementation_, implementation::to_device_info(info_name::type),
		0, NULL, &size) )
	{
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	}

	cl_device_type type = CL_DEVICE_TYPE_DEFAULT;	

	if(int err = clGetDeviceInfo(
		*implementation_, implementation::to_device_info(info_name::type),
		size, &type, &size) )
	{
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	}

	std::set<device::type> result;

	if(type & CL_DEVICE_TYPE_DEFAULT) result.insert(device::type::preset);
	if(type & CL_DEVICE_TYPE_CPU) result.insert(device::type::cpu);
	if(type & CL_DEVICE_TYPE_GPU) result.insert(device::type::gpu);
	if(type & CL_DEVICE_TYPE_ACCELERATOR) result.insert(device::type::accelerator);

	return std::move(result);
}

namespace internal {

template<typename T>
inline auto get_info(cl_device_id id, cl_device_info info) -> T	
{
	static_assert(std::is_arithmetic<T>(), "type error");

	size_t size = 0;
	if(int err = clGetDeviceInfo(id, info, 0, NULL, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	T result;
	if(int err = clGetDeviceInfo(id, info, size, &result, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	return result;
}

template<>
inline auto get_info<bool>(cl_device_id id, cl_device_info info) -> bool
{
	size_t size = 0;
	if(int err = clGetDeviceInfo(id, info, 0, NULL, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	cl_bool result;
	if(int err = clGetDeviceInfo(id, info, size, &result, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	return result == CL_TRUE;
}

template<>
inline auto get_info<std::string>(cl_device_id id, cl_device_info info) -> std::string
{
	size_t size = 0;
	if(int err = clGetDeviceInfo(id, info, 0, NULL, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	std::vector<char> buf(size);
	if(int err = clGetDeviceInfo(id, info, size, &buf[0], &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	return std::string(&buf[0]);
}

template<>
inline auto get_info<std::vector<size_t>>(cl_device_id id, cl_device_info info) -> std::vector<size_t>
{
	size_t size = 0;
	if(int err = clGetDeviceInfo(id, info, 0, NULL, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	std::vector<size_t> buf(size);
	if(int err = clGetDeviceInfo(id, info, size, &buf[0], &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	return std::move(buf);
}

template<>
inline auto get_info<std::set<device::fp_config>>(cl_device_id id, cl_device_info info) -> std::set<device::fp_config>
{
	size_t size = 0;
	if(int err = clGetDeviceInfo(id, info, 0, NULL, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	cl_device_fp_config config;
	if(int err = clGetDeviceInfo(id, info, size, &config, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );

	std::set<device::fp_config> result;

	if(config & CL_FP_DENORM)
			result.insert(device::fp_config::denorm);
	if(config & CL_FP_INF_NAN)
			result.insert(device::fp_config::inf_nan);
	if(config & CL_FP_ROUND_TO_NEAREST)
		result.insert(device::fp_config::round_to_nearest);
	if(config & CL_FP_ROUND_TO_ZERO)
		result.insert(device::fp_config::round_to_zero);
	if(config & CL_FP_ROUND_TO_INF)
		result.insert(device::fp_config::round_to_inf);
	if(config & CL_FP_FMA)
		result.insert(device::fp_config::fma);
	if(config & CL_FP_SOFT_FLOAT)
		result.insert(device::fp_config::soft_float);
	return std::move(result);
}

template<>
inline auto get_info<device::mem_cache_type>(cl_device_id id, cl_device_info info) -> device::mem_cache_type 
{
	size_t size = 0;
	if(int err = clGetDeviceInfo(id, info, 0, NULL, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );

	cl_device_mem_cache_type config;

	if(int err = clGetDeviceInfo(id, info, size, &config, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );

	switch(config)
	{
	case CL_NONE: return device::mem_cache_type::none;
	case CL_READ_ONLY_CACHE: return device::mem_cache_type::read_only;
	case CL_READ_WRITE_CACHE: return device::mem_cache_type::read_write;
	default:
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), CL_INVALID_VALUE) );
	}

	throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), CL_INVALID_VALUE) );

	return device::mem_cache_type::none;
}

template<>
inline auto get_info<device::local_mem_type>(cl_device_id id, cl_device_info info) -> device::local_mem_type
{
	size_t size = 0;
	if(int err = clGetDeviceInfo(id, info, 0, NULL, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );

	cl_device_local_mem_type config;

	if(int err = clGetDeviceInfo(id, info, size, &config, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );

	switch(config)
	{
	case CL_LOCAL: return device::local_mem_type::local;
	case CL_GLOBAL: return device::local_mem_type::global;
	default:
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), CL_INVALID_VALUE) );
	}

	throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), CL_INVALID_VALUE) );

	return device::local_mem_type::local;
}

template<>
inline auto get_info<std::set<device::exec_capability>>(cl_device_id id, cl_device_info info) -> std::set<device::exec_capability>
{
	size_t size = 0;
	if(int err = clGetDeviceInfo(id, info, 0, NULL, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	cl_device_exec_capabilities config;
	if(int err = clGetDeviceInfo(id, info, size, &config, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );

	std::set<device::exec_capability> result;

	if(config & CL_EXEC_KERNEL) result.insert(device::exec_capability::kernel);
	if(config & CL_EXEC_NATIVE_KERNEL) result.insert(device::exec_capability::native_kernel);

	return std::move(result);
}

template<>
inline auto get_info<std::set<command_queue::property>>(cl_device_id id, cl_device_info info) -> std::set<command_queue::property>
{
	size_t size = 0;
	if(int err = clGetDeviceInfo(id, info, 0, NULL, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	cl_device_exec_capabilities config;
	if(int err = clGetDeviceInfo(id, info, size, &config, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );

	std::set<command_queue::property> result;

	if(config & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE) result.insert(command_queue::property::out_of_order_exec_mode_enable);
	if(config & CL_QUEUE_PROFILING_ENABLE) result.insert(command_queue::property::profiling_enable);

	return std::move(result);
}

} // end of namespace internal

#ifdef MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO
#error "macro error"
#else
#define MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO(X) \
template<> \
auto device::info<device::info_name::X>() const -> \
	device::info_type<device::info_name::X>::type \
{ \
	return internal::get_info< device::info_type<device::info_name::X>::type >( \
		*implementation_, implementation::to_device_info(info_name::X) ); \
}

MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( vendor_id )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( max_compute_units )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( max_work_item_dimentions )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( max_work_item_sizes )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( max_work_group_size )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( preferred_vector_width_char )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( preferred_vector_width_short )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( preferred_vector_width_int )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( preferred_vector_width_long )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( preferred_vector_width_float )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( preferred_vector_width_double )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( preferred_vector_width_half )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( native_vector_width_char )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( native_vector_width_short )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( native_vector_width_int )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( native_vector_width_long )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( native_vector_width_float )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( native_vector_width_double )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( native_vector_width_half )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( max_clock_frequency )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( address_bits )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( max_mem_alloc_size )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( image_support )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( max_read_image_args )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( max_write_image_args )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( image2d_max_width )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( image2d_max_height )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( image3d_max_width )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( image3d_max_height )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( image3d_max_depth )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( max_samplers )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( max_parameter_size )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( mem_base_addr_align )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( min_data_type_align_size )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( single_fp_config )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( global_mem_cache_type )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( global_mem_cache_size )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( global_mem_size )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( max_constant_buffer_size )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( max_constant_args )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( local_mem_type )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( error_correction_support )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( host_unified_memory )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( profiling_timer_resolution )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( endian_little )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( available )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( compiler_available )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( execution_capabilities )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( name )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( vendor )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( version )
MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO( profile )

#undef MATCHA_DEVICE_INFO_DEFINITION_TEMP_MACRO
#endif

template<>
auto device::info<device::info_name::platform>() const -> platform
{
	size_t size = 0;
	if(int err = clGetDeviceInfo(
		*implementation_, implementation::to_device_info(info_name::platform),
		0, NULL, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );
	cl_platform_id config;
	if(int err = clGetDeviceInfo(
		*implementation_, implementation::to_device_info(info_name::platform),
		size, &config, &size) )
		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), err) );

	return platform( std::shared_ptr<platform::implementation>( 
		new platform::implementation(config) ) );
}

} // end of namespace Core
} // end of namespace Matcha

