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

#include <iostream>
#include <cassert>

namespace matcha { namespace math {


// ----------------------------------------------------------------------
// add
// ----------------------------------------------------------------------
template<typename T>
static inline void add_i(
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

// ----------------------------------------------------------------------
// gemm
// ----------------------------------------------------------------------
template<typename T>
static inline void gemm_na_nb_i(
	const matrix_base& a, const matrix_base& b,
	const scalar_base& alpha, const scalar_base& beta,
	matrix_base& c)
{
	assert( a.cols() == b.rows() );
	assert( a.rows() == c.rows() );
	assert( b.cols() == c.cols() );

	using namespace std;

	const size_t cols = c.cols();
	const size_t rows = c.rows();
	const size_t a_cols = a.cols();
	const size_t channels = a.channels();
	const size_t a_row_size = a.matrix_header().row_size;
	const size_t b_row_size = b.matrix_header().row_size;
	const size_t c_row_size = c.matrix_header().row_size;

	const T* a_row_cur = static_cast<const T*>(a.data_->data);
	T* c_row_cur = static_cast<T*>(c.data_->data);

	for(size_t row = 0; row < rows; ++row)
	{
		const T* b_col_head_cur = static_cast<const T*>(b.data_->data);
		T* c_cur = c_row_cur;

		for(size_t col = 0; col < cols; ++col)
		{
			for(size_t channel = 0; channel < channels; ++channel)
			{
				*(c_cur + channel) *=
					static_cast<T*>(beta.data)[channel];
			}

			const T* a_cur = a_row_cur;
			const T* b_cur = static_cast<const T*>(b_col_head_cur);

			for(size_t a_col = 0; a_col < a_cols; ++a_col)
			{
				for(size_t channel = 0; channel < channels; ++channel)
				{
					*(c_cur + channel) +=
						static_cast<T*>(alpha.data)[channel] *
						*(a_cur + channel) * *(b_cur + channel);
				}

				a_cur += channels;
				b_cur += b_row_size / sizeof(T);
			}

			b_col_head_cur += channels;
			c_cur += channels;
		}

		a_row_cur += a_row_size / sizeof(T);
		c_row_cur += c_row_size / sizeof(T);
	}
}

template<typename T>
static void gemm_ta_nb_i(
	const matrix_base& a, const matrix_base& b,
	const scalar_base& alpha, const scalar_base& beta,
	matrix_base& c)
{
	assert( a.rows() == b.rows() );
	assert( a.cols() == b.cols() );
	assert( a.cols() == c.rows() );
	assert( a.rows() == c.cols() );

	using namespace std;

	const size_t cols = c.cols();
	const size_t rows = c.rows();
	const size_t a_rows = a.rows();
	const size_t channels = a.channels();
	const size_t a_row_size = a.matrix_header().row_size;
	const size_t b_row_size = b.matrix_header().row_size;
	const size_t c_row_size = c.matrix_header().row_size;
	const T* a_col_head = static_cast<T*>(a.data_->data);
	T* c_row_cur = static_cast<T*>(c.data_->data);

	for(size_t row = 0; row < rows; ++row)
	{
		const T* b_col_head_cur = static_cast<const T*>(b.data_->data);
		T* c_cur = c_row_cur;

		for(size_t col = 0; col < cols; ++col)
		{
			for(size_t channel = 0; channel < channels; ++channel)
			{
				*(c_cur + channel) *=
					static_cast<T*>(beta.data)[channel];
			}

			const T* a_cur = a_col_head;
			const T* b_cur = static_cast<const T*>(b_col_head_cur);

			for(size_t a_row = 0; a_row < a_rows; ++a_row)
			{
				for(size_t channel = 0; channel < channels; ++channel)
				{
					*(c_cur + channel) +=
						static_cast<T*>(alpha.data)[channel] *
						*(a_cur + channel) * *(b_cur + channel);
				}

				a_cur += a_row_size / sizeof(T);
				b_cur += b_row_size / sizeof(T);
			}

			b_col_head_cur += channels;
			c_cur += channels;
		}

		a_col_head += channels;
		c_row_cur += c_row_size / sizeof(T);
	}
}

template<typename T>
static void gemm_na_tb_i(
	const matrix_base& a, const matrix_base& b,
	const scalar_base& alpha, const scalar_base& beta,
	matrix_base& c)
{
	assert(false && "not implemented");
}

template<typename T>
static void gemm_ta_tb_i(
	const matrix_base& a, const matrix_base& b,
	const scalar_base& alpha, const scalar_base& beta,
	matrix_base& c)
{
	gemm_na_nb_i<T>(b, a, alpha, beta, c);
}

void gemm(
	const matrix_base& a, transpose_option trans_a,
	const matrix_base& b, transpose_option trans_b,
	const scalar_base& alpha, const scalar_base& beta,
	matrix_base& c)
{
	assert(trans_a != transpose_option::conjugate_transpose && "not supported");
	assert(trans_b != transpose_option::conjugate_transpose && "not supported");

	assert( tri_equal(a.channels(), b.channels(), c.channels()) );
	assert( tri_equal(a.type(), b.type(), c.type()) );

	#define MATCHA_LOCAL_CASE_MACRO_TEMP(T) \
		case type_id<T>(): \
			if(trans_a == trans_b) \
				if(trans_a == transpose_option::normal) \
					gemm_na_nb_i<T>(a, b, alpha, beta, c); \
				else \
					gemm_ta_tb_i<T>(a, b, alpha, beta, c); \
			else \
				if(trans_a == transpose_option::normal) \
					gemm_na_tb_i<T>(a, b, alpha, beta, c); \
				else \
					gemm_ta_nb_i<T>(a, b, alpha, beta, c); \
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

