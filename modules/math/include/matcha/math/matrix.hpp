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
#ifndef MATCHA_MATH_MATRIX_HPP__
#define MATCHA_MATH_MATRIX_HPP__

#include <matcha/core/exception.hpp>

#include <matcha/math/types.hpp>
#include <matcha/math/scalar.hpp>

#include <cassert>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace matcha { namespace math {

template<typename T>
T* ptr_cast_from_int8_t(void* ptr, size_t offset)
{
	return static_cast<T*> (
		static_cast<void*> ( static_cast<int8_t*>(ptr) + offset) );
}

struct matrix_header
{
	uint32_t rows;
	uint32_t cols;
	int32_t type;      ///< matcha::math::typeid
	uint32_t channels;
	uint32_t alignment; ///< data alignment. typically 0, 4, 8, 16.
	uint32_t row_size;
	uint64_t data_size;
};

inline bool operator==(const matrix_header& a, const matrix_header& b)
{
	return
		a.rows == b.rows &&
		a.cols == b.cols &&
		a.type == b.type &&
		a.channels == b.channels &&
		a.alignment == b.alignment &&
		a.row_size == b.row_size &&
		a.data_size == b.data_size;
}

inline bool operator!=(const matrix_header& a, const matrix_header& b)
{
	return !(a == b);
}

matrix_header create_matrix_header(
	uint32_t rows, uint32_t cols, type_id_t type, uint32_t channels);

typedef struct matrix_data
{
	matrix_header header;
	void* data;
}matrix_data;

class matrix_base
{
public:
	matrix_base(const matcha::math::matrix_header& header);
	matrix_base(matrix_base&& matrixBase);

	virtual ~matrix_base() noexcept;

	uint32_t rows() const noexcept;
	uint32_t cols() const noexcept;
	uint32_t channels() const noexcept;
	int32_t type() const noexcept;

	const matcha::math::matrix_header& header() const noexcept;
	matcha::math::matrix_header& header() noexcept;

	std::shared_ptr<matrix_data> data_;

private:
	matrix_base(const matrix_base& matrix_base_a);
	matrix_base& operator=(const matrix_base& matrix_base_a);
};

template<typename T>
class matrix
{
public:
	typedef T type;

	std::shared_ptr<matcha::math::matrix_data> matrix_data()
	{
		return base.data_;
	}

	const std::shared_ptr<matcha::math::matrix_data> matrix_data() const
	{
		return base.data_;
	}

public:
	matrix(uint32_t rows, uint32_t cols) :
		base_( create_matrix_header(rows, cols, type_id<T>(), 1) )
	{
	}

	matrix(uint32_t rows, uint32_t cols, uint32_t channels) :
		base_( create_matrix_header(rows, cols, type_id<T>(), channels) )
	{
	}

	~matrix() noexcept
	{
	};

	matrix(const matrix& m);

	matrix(matrix&& m) :
		base_( std::forward<matrix_base>(m.base_) )
	{
	}

	matrix(const matrix_base& base) :
		base_(base)
	{
	}

	matrix(matrix_base&& base) :
		base_( std::forward<matrix_base>(base) )
	{
	}

	matrix& operator=(const matrix& m);
	matrix& operator=(matrix&& m);

public:
	uint32_t rows() const noexcept
	{
		return base_.rows();
	}

	uint32_t cols() const noexcept
	{
		return base_.cols();
	}

	uint32_t channels() const noexcept
	{
		return base_.channels();
	}

	uint32_t width() const noexcept
	{
		return cols();
	}

	uint32_t height() const noexcept
	{
		return rows();
	}

	type get(uint32_t row, uint32_t col, uint32_t channel)
	{
		assert( (row < base_.data_->header.rows) && "row, out of range" );
		assert( (col < base_.data_->header.cols) && "col, out of range" );
		assert( (channel < base_.data_->header.channels) && "channel, out of range" );

		type* ptr =
			static_cast<type*>(
				static_cast<void*>(
					static_cast<int8_t*>(base_.data_->data) + base_.data_->header.row_size  * row +
					sizeof(type) * (base_.data_->header.channels * col + channel) ) );
		return *ptr;
	}

	void set(uint32_t row, uint32_t col, uint32_t channel, type value)
	{
		assert( (row < base_.data_->header.rows) && "row, out of range" );
		assert( (col < base_.data_->header.cols) && "col, out of range" );
		assert( (channel < base_.data_->header.channels) && "channel, out of range" );

		type* ptr =
			static_cast<type*>(
				static_cast<void*>(
					static_cast<int8_t*>(base_.data_->data) + base_.data_->header.row_size  * row +
					sizeof(type) * (base_.data_->header.channels * col + channel) ) );
		*ptr = value;
	}

	type& operator()(uint32_t row, uint32_t col, uint32_t channel = 0)
	{
		assert( (row < base_.data_->header.rows) && "row, out of range" );
		assert( (col < base_.data_->header.cols) && "col, out of range" );
		assert( (channel < base_.data_->header.channels) && "channel, out of range" );

		type* ptr =
			static_cast<type*>(
				static_cast<void*>(
					static_cast<int8_t*>(base_.data_->data) + base_.data_->header.row_size  * row +
					sizeof(type) * (base_.data_->header.channels * col + channel) ) );
		return *ptr;
	}

	const type& operator()(uint32_t row, uint32_t col, uint32_t channel = 0) const
	{
		assert( (row < base_.data_->header.rows) && "row, out of range" );
		assert( (col < base_.data_->header.cols) && "col, out of range" );
		assert( (channel < base_.data_->header.channels) && "channel, out of range" );

		type* ptr =
			static_cast<type*>(
				static_cast<void*>(
					static_cast<int8_t*>(base_.data_->data) + base_.data_->header.row_size  * row +
					sizeof(type) * (base_.data_->header.channels * col + channel) ) );
		return *ptr;
	}

	matrix<T>& swap_row(uint32_t row1, uint32_t row2)
	{
		assert( (row1 < base_.data_->header.rows) && "row, out of range" );
		assert( (row2 < base_.data_->header.rows) && "row, out of range" );

		const size_t row1_offset = base_.data_->header.row_size  * row1;
		const size_t row2_offset = base_.data_->header.row_size  * row2;

		for(uint32_t i = 0; i < base_.data_->header.cols; ++i)
		{
			for(uint32_t j = 0; j < base_.data_->header.channels; ++j)
			{
				const size_t col_offset =
					sizeof(type) * (base_.data_->header.channels * i + j);

				type* const ptr1 = ptr_cast_from_int8_t<type>(
						base_.data_->data, row1_offset + col_offset);
				type* const ptr2 = ptr_cast_from_int8_t<type>(
						base_.data_->data, row2_offset + col_offset);

				type temp = *ptr1;
				*ptr1 = *ptr2;
				*ptr2 = temp;

			}
		}

		return *this;
	}

	matrix<T>& swap_col(uint32_t col1, uint32_t col2)
	{
		assert( (col1 < base_.data_->header.cols) && "col, out of range" );
		assert( (col2 < base_.data_->header.cols) && "col, out of range" );

		const size_t col1_offset = sizeof(type) * base_.data_->header.channels * col1;
		const size_t col2_offset = sizeof(type) * base_.data_->header.channels * col2;
		const size_t row_size = sizeof(type) * base_.data_->header.rows;

		for(uint32_t i = 0; i < base_.data_->header.rows; ++i)
		{
			type* ptr1 = ptr_cast_from_int8_t<type>(
				base_.data_->data, row_size * i + col1_offset);
			type* ptr2 = ptr_cast_from_int8_t<type>(
				base_.data_->data, row_size * i + col2_offset);

			for(uint32_t j = 0; j < base_.data_->header.channels; ++j)
			{
				type temp = *(ptr1 + j);
				*(ptr1 + j) = *(ptr2 + j);
				*(ptr2 + j) = temp;

			}
		}

		return *this;
	}


	const matrix_base& base() const
	{
		return this->base_;
	}

	matrix_base& base()
	{
		return this->base_;
	}

private:
	matrix();

	matrix_base base_;
};

} // end of namespace math
} // end of namespace matcha

#endif
