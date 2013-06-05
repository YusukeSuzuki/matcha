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

#include <ostream>
#include <cassert>

namespace matcha { namespace math { namespace easy_expression {

template<typename T>
T for_out(T t)
{
	return t;
}

uint32_t for_out(uint8_t t)
{
	return t;
}

uint32_t for_out(int8_t t)
{
	return t;
}

template<typename T>
void out_i(std::ostream& out, const matrix_data& data)
{
	const uint8_t* ptr = static_cast<const uint8_t*>(data.data);

	out << "[" << std::endl;

	for(uint32_t r = 0; r < data.header.rows; ++r)
	{
		const T* cur_ptr =
			static_cast<const T*>( static_cast<const void*>( ptr ) );

		out << "  [";

		for(uint32_t c = 0; c < data.header.cols; ++c)
		{
			if(data.header.channels > 1) out << "[";

			for(uint32_t ch = 0; ch < data.header.channels; ++ch)
			{
				out << for_out(*cur_ptr);

				if(data.header.channels - ch - 1) out << ", ";

				++cur_ptr;
			}

			if(data.header.channels > 1) out << "]";

			if(data.header.cols - c - 1) out << ",";
		}

		out << "]";

		if(data.header.rows - r - 1) out << ",";
	 
		out << std::endl;

		ptr += data.header.row_size;
	}

	out << "]" << std::endl;
}

std::ostream& operator << (std::ostream& out, const matrix_base& m)
{
	assert( is_supported_type( static_cast<type_id_t>( m.data_->header.type) ) );

	#define MATCHA_LOCAL_CASE_MACRO_TEMP(T) \
		case type_id<T>(): out_i<T>(out, *m.data_); break;

	switch( static_cast<type_id_t>(m.data_->header.type) )
	{
	MATCHA_MATH_TYPES_DECL_ALL(MATCHA_LOCAL_CASE_MACRO_TEMP)
	default:
		break;
	}

	#undef MATCHA_LOCAL_CASE_MACRO_TEMP

	return out;
}

std::ostream& operator << (std::ostream& out, const scalar_base& s)
{
	out << "[";
	for(std::size_t i = 0; i < s.dims; ++i)
	{
		#define MATCHA_LOCAL_CASE_MACRO_TEMP(T) \
			case type_id<T>(): out << static_cast<T*>(s.data)[i] ; break;

		switch( s.type )
		{
		MATCHA_MATH_TYPES_DECL_ALL(MATCHA_LOCAL_CASE_MACRO_TEMP)
		default:
			break;
		}

		#undef MATCHA_LOCAL_CASE_MACRO_TEMP

		if(i < (s.dims - 1) ) out << ", ";
	}

	out << "]";

	return out;
}

} // end of namespace easy_expression
} // end of namespace math
} // end of namespace matcha

