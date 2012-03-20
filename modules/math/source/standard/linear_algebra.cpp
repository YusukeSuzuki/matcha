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
#include "matcha/math/matrix.hpp"
#include "matcha/math/linear_algebra.hpp"
#include "matcha/core/exception.hpp"

#include "utilities_i.hpp"

#include <cassert>

namespace matcha { namespace math {

template<typename T>
void add_i(
	const matrix_data& a, const matrix_data& b, matrix_data& c)
{
	for(std::size_t i = 0;
		i < (a.header.rows * a.header.cols * a.header.channels); ++i)
	{
		static_cast<T*>(c.data)[i] =
			static_cast<const T*>(a.data)[i] + static_cast<const T*>(b.data)[i];
	}
}

void add(const matrix_base& a, const matrix_base& b, matrix_base& c)
{
	assert( tri_equal(a.rows(), b.rows(), c.rows() ) );
	assert( tri_equal(a.cols(), b.cols(), c.cols() ) );
	assert( tri_equal(a.channels(), b.channels(), c.channels() ) );
	assert( tri_equal(
		a.matrix_header().type, b.matrix_header().type, c.matrix_header().type ) );

	#define MATCHA_LOCAL_CASE_MACRO_TEMP(T) \
		case type_id<T>(): \
			add_i<T>( *a.data_, *b.data_, *c.data_ ); \
			break;

	switch( static_cast<type_id_t>(a.matrix_header().type) )
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
		assert(false && "invalid type");
	}

	#undef MATCHA_LOCAL_CASE_MACRO_TEMP
}


} // end of namespace math
} // end of namespace matcha

