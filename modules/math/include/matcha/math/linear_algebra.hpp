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
#ifndef MATCHA_MATH_LINEAR_ALGEBRA_HPP__
#define MATCHA_MATH_LINEAR_ALGEBRA_HPP__

#include <matcha/math/matrix.hpp>

#include <cstdint>
#include <utility>

namespace matcha { namespace math {

enum class transpose_option : int32_t
{
	normal,
	transpose,
	conjugate_transpose,
};

/**
 * c = a + b
 */
void add(const matrix_base& a, const matrix_base& b, matrix_base& c);

/**
 * return a + b
 */
template<typename T>
matrix<T> add(const matrix<T>& a, const matrix<T>& b)
{
	matrix<T> c(a.rows(), a.cols(), a.channels());
	add(a, b, c);
	return std::move(c);
}

/**
 * c = a - b
 */
void sub(const matrix_base& a, const matrix_base& b, matrix_base& c);

/**
 * return a - b
 */
template<typename T>
matrix<T> sub(const matrix<T>& a, const matrix<T>& b)
{
	matrix<T> c(a.rows(), a.cols(), a.channels());
	sub(a, b, c);
	return std::move(c);
}

/**
 * c = alpha * a * b + beta + c
 */
void gemm(
	const matrix_base& a, transpose_option trans_a,
	const matrix_base& b, transpose_option trans_b,
	const scalar_base& alpha, const scalar_base& beta,
	matrix_base& c);

} // end of namespace math
} // end of namespace matcha

#endif
