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

namespace matcha { namespace math {

typedef struct matrix_header
{
	uint32_t rows;
	uint32_t cols;
	uint32_t type;      ///< matcha::math::typeid
	uint32_t channels;
	uint32_t alignment; ///< data alignment. typically 0, 4, 8, 16.
	uint32_t row_size;
	uint64_t data_size;
}matrix_header;

matrix_header create_matrix_header(
	uint32_t rows, uint32_t cols, uint32_t type, uint32_t channels);

typedef struct matrix_data
{
	matrix_header header;
	void* data;
}matrix_data;

class matrix_base
{
public:
	virtual ~matrix_base() throw();
	virtual const std::type_info& element_type() const = 0;

	uint32_t rows() const noexcept;
	uint32_t height() const noexcept;
	uint32_t cols() const noexcept;
	uint32_t width() const noexcept;
	uint32_t channels() const;

	matcha::math::matrix_header matrix_header() const;

protected:
	///< @todo should pure virtual class have data member?
	matrix_base(const matcha::math::matrix_header& matrixHeader);
	matrix_base(matrix_base&& matrixBase);
	std::shared_ptr<matrix_data> data_;

private:
	matrix_base(const matrix_base& matrixBase); ///< @todo check
	matrix_base& operator=(const matrix_base& matrixBase); ///< @todo check
};

template<typename T>
class matrix : public matrix_base
{
public:
	typedef T type;

	std::shared_ptr<matcha::math::matrix_data> matrix_data()
	{
		return data_;
	}

	const std::shared_ptr<matcha::math::matrix_data> matrix_data() const
	{
		return data_;
	}

public:
	matrix(uint32_t rows, uint32_t cols, type_id_t type, uint32_t channels);

	/// @todo implement
	virtual ~matrix() noexcept
	{
	};

	matrix(const matrix& m);
	matrix(matrix&& m);
	matrix& operator=(const matrix& m);
	matrix& operator=(matrix&& m);

public:
	type get(uint32_t row, uint32_t col, uint32_t channel)
	{
		assert( (row < data_->header.rows) && "row, out of range" );
		assert( (col < data_->header.cols) && "col, out of range" );
		assert( (channel < data_->header.channels) && "channel, out of range" );

		type* ptr =
			static_cast<type*>(
				static_cast<void*>( static_cast<int8_t*>(data_->data) + data_->header.row_size  * row +
					sizeof(type) * (data_->header.channels * col + channel) ) );
		return *ptr;
	}

	void set(uint32_t row, uint32_t col, uint32_t channel, type value)
	{
		assert( (row < data_->header.rows) && "row, out of range" );
		assert( (col < data_->header.cols) && "col, out of range" );
		assert( (channel < data_->header.channels) && "channel, out of range" );

		type* ptr =
			static_cast<type*>(
				static_cast<void*>( static_cast<int8_t*>(data_->data) + data_->header.row_size  * row +
					sizeof(type) * (data_->header.channels * col + channel) ) );
		*ptr = value;
	}

	type& operator()(uint32_t row, uint32_t col, uint32_t channel = 0)
	{
		assert( (row < data_->header.rows) && "row, out of range" );
		assert( (col < data_->header.cols) && "col, out of range" );
		assert( (channel < data_->header.channels) && "channel, out of range" );

		type* ptr =
			static_cast<type*>(
				static_cast<void*>( static_cast<int8_t*>(data_->data) + data_->header.row_size  * row +
					sizeof(type) * (data_->header.channels * col + channel) ) );
		return *ptr;
	}

	const type& operator()(uint32_t row, uint32_t col, uint32_t channel = 0) const
	{
		assert( (row < data_->header.rows) && "row, out of range" );
		assert( (col < data_->header.cols) && "col, out of range" );
		assert( (channel < data_->header.channels) && "channel, out of range" );

		type* ptr =
			static_cast<type*>(
				static_cast<void*>( static_cast<int8_t*>(data_->data) + data_->header.row_size  * row +
					sizeof(type) * (data_->header.channels * col + channel) ) );
		return *ptr;
	}

public:
	virtual const std::type_info& element_type() const
	{
		return typeid(type);
	};
private:
	matrix();
};

} // end of namespace math
} // end of namespace matcha

#endif
