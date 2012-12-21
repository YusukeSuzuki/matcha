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
#ifndef __MATCAH_CL_BITS_DEVICE_TEMPLATE_HPP_
#define __MATCAH_CL_BITS_DEVICE_TEMPLATE_HPP_

#include <set>

namespace matcha { namespace cl {

#ifdef MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO
#error "macro error"
#else
#define MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(X,Y) \
	template<> struct device::info_type<device::info_name::X> : \
		public core::type_container<Y>{}; \
	template<> auto device::info<device::info_name::X>() const -> \
		typename device::info_type<device::info_name::X>::type;

MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(type, std::set<device::type>)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(vendor_id, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(max_compute_units, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(max_work_item_dimentions, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(max_work_item_sizes, std::vector<size_t>)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(max_work_group_size, size_t)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(preferred_vector_width_char, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(preferred_vector_width_short, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(preferred_vector_width_int, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(preferred_vector_width_long, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(preferred_vector_width_float, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(preferred_vector_width_double, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(preferred_vector_width_half, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(native_vector_width_char, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(native_vector_width_short, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(native_vector_width_int, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(native_vector_width_long, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(native_vector_width_float, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(native_vector_width_double, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(native_vector_width_half, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(max_clock_frequency, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(address_bits, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(max_mem_alloc_size, unsigned long)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(image_support, bool)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(max_read_image_args, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(max_write_image_args, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(image2d_max_width, size_t)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(image2d_max_height, size_t)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(image3d_max_width, size_t)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(image3d_max_height, size_t)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(image3d_max_depth, size_t)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(max_samplers, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(max_parameter_size, size_t)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(mem_base_addr_align, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(min_data_type_align_size, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(single_fp_config, std::set<device::fp_config>)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(global_mem_cache_type, device::mem_cache_type)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(global_mem_cacheline_size, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(global_mem_cache_size, unsigned long)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(global_mem_size, unsigned long)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(max_constant_buffer_size, unsigned long)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(max_constant_args, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(local_mem_type, local_mem_type)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(error_correction_support, bool)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(host_unified_memory, bool)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(profiling_timer_resolution, size_t)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(endian_little, bool)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(available, bool)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(compiler_available, bool)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(execution_capabilities, std::set<exec_capability>)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(queue_properties, std::set<command_queue::property>)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(platform, platform)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(name, std::string)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(vendor, std::string)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(driver_version, std::string)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(profile, std::string)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(version, std::string)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(opencl_c_version, std::string)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(extensions, std::string)

#undef MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO
#endif

} // end of namespace Core
} // end of namespace Matcha

#endif

