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
#ifndef __MATCAH_CL_INTERNAL_H_
#define __MATCAH_CL_INTERNAL_H_

#include "matcha/cl/cl.hpp"

#include <algorithm>

namespace matcha { namespace cl {

class device::implementation
{
public:
	implementation(cl_device_id id) :
		id_(id)
	{
	}

	~implementation() noexcept
	{
	}

	cl_device_id id() const
	{
		return id_;
	}

	static std::vector<cl_device_id> to_device_ids(
		const std::vector<device>& devices)
	{
		std::vector<cl_device_id> ids(devices.size());

		std::transform(devices.begin(), devices.end(),
			ids.begin(), [](const device& device) -> cl_device_id {
				return device.implementation_->id(); });

		return ids;
	}

	static cl_device_type to_device_type(device::type t)
	{
		switch(t)
		{
		case device::type::cpu: return CL_DEVICE_TYPE_CPU;
		case device::type::gpu: return CL_DEVICE_TYPE_GPU;
		case device::type::accelerator: return CL_DEVICE_TYPE_ACCELERATOR;
		case device::type::preset: return CL_DEVICE_TYPE_DEFAULT;
		}

		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), CL_INVALID_VALUE) );
	}

	static cl_device_type to_device_type(const std::set<device::type>& types)
	{
		if(types.empty())
		{
			throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), CL_INVALID_VALUE) );
		}

		return
			(types.count(device::type::cpu) ? CL_DEVICE_TYPE_CPU : 0) |
			(types.count(device::type::gpu) ? CL_DEVICE_TYPE_GPU: 0) |
			(types.count(device::type::accelerator) ? CL_DEVICE_TYPE_ACCELERATOR: 0) |
			(types.count(device::type::preset) ? CL_DEVICE_TYPE_DEFAULT: 0);
	}

	static cl_device_info to_device_info(device::info_name i)
	{
		#ifdef MATCHA_INFO_PARAMETER_TEMP_MACRO
		#error "macro error"
		#else
		#define MATCHA_INFO_PARAMETER_TEMP_MACRO(X,Y) \
			case device::info_name::X: return Y;

		switch(i)
		{
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			type, CL_DEVICE_TYPE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			vendor_id, CL_DEVICE_VENDOR_ID)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			max_compute_units, CL_DEVICE_MAX_COMPUTE_UNITS)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			max_work_item_dimentions, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			max_work_item_sizes, CL_DEVICE_MAX_WORK_ITEM_SIZES)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			max_work_group_size, CL_DEVICE_MAX_WORK_GROUP_SIZE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			preferred_vector_width_char, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			preferred_vector_width_short, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			preferred_vector_width_int, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			preferred_vector_width_long, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			preferred_vector_width_float, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			preferred_vector_width_double, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			preferred_vector_width_half, CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			native_vector_width_char, CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			native_vector_width_short, CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			native_vector_width_int, CL_DEVICE_NATIVE_VECTOR_WIDTH_INT)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			native_vector_width_long, CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			native_vector_width_float, CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			native_vector_width_double, CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			native_vector_width_half, CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			max_clock_frequency, CL_DEVICE_MAX_CLOCK_FREQUENCY)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			address_bits, CL_DEVICE_ADDRESS_BITS)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			max_mem_alloc_size, CL_DEVICE_MAX_MEM_ALLOC_SIZE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			image_support, CL_DEVICE_IMAGE_SUPPORT)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			max_read_image_args, CL_DEVICE_MAX_READ_IMAGE_ARGS)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			max_write_image_args, CL_DEVICE_MAX_WRITE_IMAGE_ARGS)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			image2d_max_width, CL_DEVICE_IMAGE2D_MAX_WIDTH)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			image2d_max_height, CL_DEVICE_IMAGE2D_MAX_HEIGHT)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			image3d_max_width, CL_DEVICE_IMAGE3D_MAX_WIDTH)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			image3d_max_height, CL_DEVICE_IMAGE3D_MAX_HEIGHT)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			image3d_max_depth, CL_DEVICE_IMAGE3D_MAX_DEPTH)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			max_samplers, CL_DEVICE_MAX_SAMPLERS)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			max_parameter_size, CL_DEVICE_MAX_PARAMETER_SIZE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			mem_base_addr_align, CL_DEVICE_MEM_BASE_ADDR_ALIGN)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			min_data_type_align_size, CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			single_fp_config, CL_DEVICE_SINGLE_FP_CONFIG)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			global_mem_cache_type, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			global_mem_cacheline_size, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			global_mem_cache_size, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			global_mem_size, CL_DEVICE_GLOBAL_MEM_SIZE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			max_constant_buffer_size, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			max_constant_args, CL_DEVICE_MAX_CONSTANT_ARGS)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			local_mem_type, CL_DEVICE_LOCAL_MEM_TYPE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			local_mem_size, CL_DEVICE_LOCAL_MEM_SIZE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			error_correction_support, CL_DEVICE_ERROR_CORRECTION_SUPPORT)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			host_unified_memory, CL_DEVICE_HOST_UNIFIED_MEMORY)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			profiling_timer_resolution, CL_DEVICE_PROFILING_TIMER_RESOLUTION)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			endian_little, CL_DEVICE_ENDIAN_LITTLE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			available, CL_DEVICE_AVAILABLE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			compiler_available, CL_DEVICE_COMPILER_AVAILABLE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			execution_capabilities, CL_DEVICE_EXECUTION_CAPABILITIES)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			queue_properties, CL_DEVICE_QUEUE_PROPERTIES)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			platform, CL_DEVICE_PLATFORM)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			name, CL_DEVICE_NAME)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			vendor, CL_DEVICE_VENDOR)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			driver_version, CL_DRIVER_VERSION)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			profile, CL_DEVICE_PROFILE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			version, CL_DEVICE_VERSION)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			opencl_c_version, CL_DEVICE_OPENCL_C_VERSION)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(
			extensions, CL_DEVICE_EXTENSIONS)
		}

		#undef MATCHA_INFO_PARAMETER_TEMP_MACRO
		#endif

		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), CL_INVALID_VALUE) );
	}

	operator cl_device_id() const
	{
		return id_;
	}

private:
	cl_device_id id_;
};

class platform::implementation
{
public:
	implementation(cl_platform_id id) :
	id_(id)
	{
	}

	cl_platform_id id() const
	{
		return id_;
	}

	static cl_platform_info to_platform_info(info_name info)
	{
		switch(info)
		{
		case info_name::profile:
			return CL_PLATFORM_PROFILE;
		case info_name::version:
			return CL_PLATFORM_VERSION;
		case info_name::name:
			return CL_PLATFORM_NAME;
		case info_name::vendor:
			return CL_PLATFORM_VENDOR;
		case info_name::extensions:
			return CL_PLATFORM_EXTENSIONS;
		}

		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), CL_INVALID_VALUE) );
	}

private:
	cl_platform_id id_;
};

class program::implementation
{
public:
	implementation();

	static cl_program_info to_program_info(program::info_name i)
	{
		#ifdef MATCHA_INFO_PARAMETER_TEMP_MACRO
		#error "macro error"
		#else
		#define MATCHA_INFO_PARAMETER_TEMP_MACRO(X,Y) \
			case program::info_name::X: return Y;

		switch(i)
		{
		MATCHA_INFO_PARAMETER_TEMP_MACRO(reference_count, CL_PROGRAM_REFERENCE_COUNT)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(context, CL_PROGRAM_CONTEXT)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(num_devices, CL_PROGRAM_NUM_DEVICES)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(devices, CL_PROGRAM_DEVICES)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(source, CL_PROGRAM_SOURCE)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(binary_sizes, CL_PROGRAM_BINARY_SIZES)
		MATCHA_INFO_PARAMETER_TEMP_MACRO(binaries, CL_PROGRAM_BINARIES)
		}

		#undef MATCHA_INFO_PARAMETER_TEMP_MACRO
		#endif

		throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), CL_INVALID_VALUE) );
	}

	cl_program program() const
	{
		return program_;
	}

	operator cl_program()
	{
		return program_;
	}

private:
	cl_program program_;
};

} // end of namespace Core
} // end of namespace Matcha

#endif
