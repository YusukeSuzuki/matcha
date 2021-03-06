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
static inline void fill_i(
	const T src[], std::size_t dims, T* dst, std::size_t elems)
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
	assert(src.type == static_cast<type_id_t>(dst.header().type) &&
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

	#undef MATCHA_LOCAL_CASE_MACRO_TEMP
}

template<typename T>
static inline void split_i(
	const matrix_base& src, matrix_base& dst, uint32_t channel)
{
	const std::size_t rows = src.rows();
	const std::size_t cols = src.cols();
	const std::size_t channels = src.channels();
	const std::size_t src_row_size = src.header().row_size;
	const std::size_t dst_row_size = dst.header().row_size;

	const T* src_row_cur = static_cast<const T*>(src.data_->data);
	T* dst_row_cur = static_cast<T*>(dst.data_->data);

	for(std::size_t row = 0; row < rows; ++row)
	{
		const T* src_cur = src_row_cur + channel;
		T* dst_cur = dst_row_cur;

		for(std::size_t col = 0; col < cols; ++col)
		{
			*dst_cur = *src_cur;
			++dst_cur;
			src_cur += channels;
		}

		src_row_cur += src_row_size / sizeof(T);
		dst_row_cur += dst_row_size / sizeof(T);
	}
}

void
split(const matrix_base& src, matrix_base& dst, uint32_t channel)
{
	assert(false && "not implemented");

	assert(channel < src.channels());
	assert(dst.channels() == 1);
	assert(src.rows() == dst.rows());
	assert(src.cols() == dst.cols());
	assert(src.header().type == dst.header().type);

	#define MATCHA_LOCAL_CASE_MACRO_TEMP(T) \
		case type_id<T>():  split_i<T>(src, dst, channel); break;

	switch( static_cast<type_id_t>(src.header().type) )
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
		assert(false && "dst invalid type");
	}

	#undef MATCHA_LOCAL_CASE_MACRO_TEMP
}

template<typename T>
static inline void make_identity_i(
	matrix_base& dst)
{
	const matrix_header header = dst.header();

	T* row_cur = static_cast<T*>(dst.data_->data);

	for(std::size_t row = 0; row < header.rows; ++row)
	{
		T* col_cur = row_cur;

		for(std::size_t col = 0; col < header.cols; ++col)
		{
			for(std::size_t channel = 0; channel < header.channels; ++channel)
			{
				*(col_cur + channel) = (row == col) ? T(1) : T(0);
			}

			col_cur += header.channels;
		}

		row_cur += header.row_size / sizeof(T);
	}
}

void
make_identity(matrix_base& dst)
{
	#define MATCHA_LOCAL_CASE_MACRO_TEMP(T) \
		case type_id<T>():  make_identity_i<T>( dst ); break;

	switch( static_cast<type_id_t>(dst.header().type) )
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
		assert(false && "dst invalid type");
	}

	#undef MATCHA_LOCAL_CASE_MACRO_TEMP
}

} // end of namespace math
} // end of namespace matcha

