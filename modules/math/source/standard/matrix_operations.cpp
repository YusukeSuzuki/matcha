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
#include "matcha/math/matrix_operations.hpp"
#include "matcha/math/types.hpp"
#include "matcha/core/exception.hpp"

#include <cassert>

namespace matcha { namespace math {

template<typename T>
void fill_i(const T src[], std::size_t dims, T* dst, std::size_t elems)
{
	for(std::size_t i = 0; i < elems; ++i)
	{
		for(std::size_t j = 0; j < dims; ++j, ++dst)
		{
			*dst = src[j];
		}
	}
}

void fill(const scalar_base& src, matrix_base& dst)
{
	assert(
		src.dims == dst.channels() && "src.dims must be equal to dst.channels()");
	assert(src.type == static_cast<type_id_t>(dst.matrix_header().type) &&
		"src.type must be equal to dst");

#define MATCHA_LOCAL_CASE_MACRO_TEMP(T) \
	case type_id<T>(): \
		fill_i( \
			static_cast<T*>(src.data), src.dims, \
			static_cast<T*>(dst.data_->data), dst.rows() * dst.cols()); \
		break;

	switch(src.type)
	{
	MATCHA_LOCAL_CASE_MACRO_TEMP(  int8_t)
	MATCHA_LOCAL_CASE_MACRO_TEMP( uint8_t)
	MATCHA_LOCAL_CASE_MACRO_TEMP( int16_t)
	MATCHA_LOCAL_CASE_MACRO_TEMP(uint16_t)
	MATCHA_LOCAL_CASE_MACRO_TEMP( int32_t)
	MATCHA_LOCAL_CASE_MACRO_TEMP(uint32_t)
	MATCHA_LOCAL_CASE_MACRO_TEMP( int64_t)
	MATCHA_LOCAL_CASE_MACRO_TEMP(uint64_t)
	MATCHA_LOCAL_CASE_MACRO_TEMP(   float)
	MATCHA_LOCAL_CASE_MACRO_TEMP(  double)
	default:
		assert(false && "src invalid type");
	}
}

} // end of namespace math
} // end of namespace matcha

