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

#include "matcha/core/exception.hpp"

#include <cstring>

namespace matcha { namespace math {

static const std::size_t memory_alignment_i = 16;

static matrix_data* create_matrix_data_i(const matrix_header matrix_header_a)
{
	assert(matrix_header_a.rows > 0 && matrix_header_a.cols > 0 &&
		matrix_header_a.channels > 0 && matrix_header_a.channels < 5);

	assert( (
		static_cast<type_id_t>(matrix_header_a.type) == type_id<  int8_t>() ||
		static_cast<type_id_t>(matrix_header_a.type) == type_id< uint8_t>() ||
		static_cast<type_id_t>(matrix_header_a.type) == type_id< int16_t>() ||
		static_cast<type_id_t>(matrix_header_a.type) == type_id<uint16_t>() ||
		static_cast<type_id_t>(matrix_header_a.type) == type_id< int32_t>() ||
		static_cast<type_id_t>(matrix_header_a.type) == type_id<uint32_t>() ||
		static_cast<type_id_t>(matrix_header_a.type) == type_id< int64_t>() ||
		static_cast<type_id_t>(matrix_header_a.type) == type_id<uint64_t>() ||
		static_cast<type_id_t>(matrix_header_a.type) == type_id<  double>() ||
		static_cast<type_id_t>(matrix_header_a.type) == type_id<   float>() ) );

	matrix_data* result =
		static_cast<matrix_data*>( malloc(sizeof(matrix_data) ) );
	result->header = matrix_header_a;
	result->header.alignment = memory_alignment_i;
	const std::size_t element_size =
		size_of_type(static_cast<type_id_t>(matrix_header_a.type)) * result->header.channels;
	result->header.row_size = element_size * result->header.cols;;
	result->header.data_size = result->header.row_size * result->header.rows;

	if( int err = posix_memalign(&result->data, memory_alignment_i, result->header.data_size) )
	{
		throw(core::system_exception(MATCHA_EXCEPTION_WHERE.c_str(), err));
	}

	return result;
}

static void release_matrix_data_i(matrix_data*& matrix_data_a)
{
	free(matrix_data_a->data);
	free(matrix_data_a);
	matrix_data_a = nullptr;
}

matrix_header create_matrix_header(
	uint32_t rows, uint32_t cols, int32_t type, uint32_t channels)
{
	assert( rows > 0 && cols > 0 && channels > 0 && channels < 5);

	assert( (
		static_cast<type_id_t>(type) == type_id<  int8_t>() ||
		static_cast<type_id_t>(type) == type_id< uint8_t>() ||
		static_cast<type_id_t>(type) == type_id< int16_t>() ||
		static_cast<type_id_t>(type) == type_id<uint16_t>() ||
		static_cast<type_id_t>(type) == type_id< int32_t>() ||
		static_cast<type_id_t>(type) == type_id<uint32_t>() ||
		static_cast<type_id_t>(type) == type_id< int64_t>() ||
		static_cast<type_id_t>(type) == type_id<uint64_t>() ||
		static_cast<type_id_t>(type) == type_id<  double>() ||
		static_cast<type_id_t>(type) == type_id<   float>() ) );

	matrix_header result = {rows, cols, type, channels, memory_alignment_i, 0};
	result.row_size =
		size_of_type(static_cast<type_id_t>(type)) * channels * cols;
	result.data_size = result.row_size * rows;

	return result;
}

matrix_base::matrix_base(const struct matrix_header& matrix_header_a) :
	data_( create_matrix_data_i(matrix_header_a), release_matrix_data_i)
{
}

matrix_base::matrix_base(matrix_base&& matrix_base) :
	data_( matrix_base.data_ )
{
}

matrix_base::~matrix_base() noexcept
{
}

matrix_base::matrix_base(const matrix_base& matrix_base) :
	data_( create_matrix_data_i(matrix_base.data_->header) )
{
	memcpy(data_->data, matrix_base.data_->data, matrix_base.data_->header.data_size);
}

matrix_base&
matrix_base::operator=(const matrix_base& matrix_base)
{
	if(this == &matrix_base)
	{
		return *this;
	}

	if(data_->header != matrix_base.data_->header)
	{
		data_->header = matrix_base.data_->header;
		free(data_->data);
		
		if( int err = posix_memalign(&data_->data, memory_alignment_i, data_->header.data_size) )
		{
			throw(core::system_exception(MATCHA_EXCEPTION_WHERE.c_str(), err));
		}
	}

	memcpy(data_->data, matrix_base.data_->data, data_->header.data_size);

	return *this;
}

} // end of namespace math
} // end of namespace matcha

