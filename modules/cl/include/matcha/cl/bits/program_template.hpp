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
#ifndef __MATCAH_CL_BITS_PROGRAM_TEMPLATE_HPP_
#define __MATCAH_CL_BITS_PROGRAM_TEMPLATE_HPP_

#include <set>

namespace matcha { namespace cl {

#ifdef MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO
#error "macro error"
#else
#define MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(X,Y) \
	template<> struct program::info_type<program::info_name::X> : \
		public core::type_container<Y>{}; \
	template<> auto program::info<program::info_name::X>() const -> \
		typename program::info_type<program::info_name::X>::type;

MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(reference_count, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(context, context)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(num_devices, unsigned int)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(devices, std::vector<device>)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(source, std::string)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(binary_sizes, std::vector<size_t>)
MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO(binaries, std::vector<unsigned char>)

#undef MATCHA_INFO_NAME_DECRARATION_TEMP_MACRO
#endif

} // end of namespace Core
} // end of namespace Matcha

#endif


