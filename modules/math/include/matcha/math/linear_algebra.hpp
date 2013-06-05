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

// ----------------------------------------------------------------------
// add
// ----------------------------------------------------------------------

/**
 * c = a + b
 */
void add(const matrix_base& a, const matrix_base& b, matrix_base& c);

/**
 * c = a + b
 */
template<typename T>
void add(const matrix<T>& a, const matrix<T>& b, matrix<T>& c)
{
	add(a.base(), b.base(), c.base());
}

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

// ----------------------------------------------------------------------
// sub
// ----------------------------------------------------------------------

// matrix matrix

/**
 * c = a - b
 */
void sub(const matrix_base& a, const matrix_base& b, matrix_base& c);

/**
 * c = a - b
 */
template<typename T>
void sub(const matrix<T>& a, const matrix<T>& b, matrix<T>& c)
{
	sub(a.base(), b.base(), c.base());
}

/**
 * return a - b
 */
template<typename T>
matrix<T> sub(const matrix<T>& a, const matrix<T>& b)
{
	matrix<T> c(a.rows(), a.cols(), a.channels());
	sub(a.base(), b.base(), c.base());
	return std::move(c);
}

// matrix numeric

/**
 * c = a - b
 */
template<typename T>
void sub(const matrix_base& a, T b, matrix_base& c);

#define MATCHA_EXTERN_TEMPLATE_MACRO_TEMP(T) \
	extern template void sub<T>(const matrix_base& a, T b, matrix_base& c);
MATCHA_MATH_TYPES_DECL_ALL( MATCHA_EXTERN_TEMPLATE_MACRO_TEMP )
#undef MATCHA_EXTERN_TEMPLATE_MACRO_TEMP

/**
 * c = a - b
 */
template<typename T>
void sub(T a, const matrix_base& b, matrix_base& c);

#define MATCHA_EXTERN_TEMPLATE_MACRO_TEMP(T) \
	extern template void sub<T>(T a, const matrix_base& b, matrix_base& c);
MATCHA_MATH_TYPES_DECL_ALL( MATCHA_EXTERN_TEMPLATE_MACRO_TEMP )
#undef MATCHA_EXTERN_TEMPLATE_MACRO_TEMP

/**
 * c = a - b
 */
template<typename T>
void sub(const matrix<T>& a, typename matrix<T>::type b, matrix<T>& c)
{
	sub(a.base(), b, c.base());
}

/**
 * c = a - b
 */
template<typename T>
void sub(typename matrix<T>::type a, const matrix<T>& b, matrix<T>& c)
{
	sub(a, b.base(), c.base());
}

/**
 * return a - b
 */
template<typename T>
matrix<T> sub(const matrix<T>& a, typename matrix<T>::type b)
{
	matrix<T> c(a.rows(), a.cols(), a.channels());
	sub(a.base(), b, c.base());
	return std::move(c);
}

/**
 * return a - b
 */
template<typename T>
matrix<T> sub(typename matrix<T>::type a, const matrix<T>& b)
{
	matrix<T> c(b.rows(), b.cols(), b.channels());
	sub(a, b.base(), c.base());
	return std::move(c);
}

// ----------------------------------------------------------------------
// mul
// ----------------------------------------------------------------------

/**
 * c = a * b
 */
template<typename T>
void mul(const matrix_base& a, T b, matrix_base& c);

//extern template void mul<uint8_t>(const matrix_base& a, uint8_t b, matrix_base& c);

#define MATCHA_EXTERN_TEMPLATE_MACRO_TEMP(T) \
	extern template void mul<T>(const matrix_base& a, T b, matrix_base& c);
MATCHA_MATH_TYPES_DECL_ALL( MATCHA_EXTERN_TEMPLATE_MACRO_TEMP )
#undef MATCHA_EXTERN_TEMPLATE_MACRO_TEMP

/**
 * c = a * b
 */
template<typename T>
void mul(const matrix<T>& a, typename matrix<T>::type b, matrix<T>& c)
{
	mul(a.base(), b, c.base());
}

/**
 * c = a * b
 */
template<typename T>
void mul(typename matrix<T>::type a, const matrix<T>& b, matrix<T>& c)
{
	mul(b.base(), a, c.base());
}

/**
 * return = a * b
 */
template<typename T>
matrix<T> mul(typename matrix<T>::type a, const matrix<T>& b)
{
	auto c = a;
	mul(a, b, c);
	return c;
}

/**
 * return = a * b
 */
template<typename T>
matrix<T> mul(const matrix<T>& b, typename matrix<T>::type a)
{
	auto c = a;
	mul(a, b, c);
	return c;
}

// ----------------------------------------------------------------------
// gemm
// ----------------------------------------------------------------------

/**
 * c = alpha * a * b + beta + c
 */
void gemm(
	const matrix_base& a, transpose_option trans_a,
	const matrix_base& b, transpose_option trans_b,
	const scalar_base& alpha, const scalar_base& beta,
	matrix_base& c);

/**
 * c = alpha * a * b + beta + c
 */
template<typename T>
void gemm(
	const matrix<T>& a, transpose_option trans_a,
	const matrix<T>& b, transpose_option trans_b,
	const scalar_base& alpha, const scalar_base& beta,
	matrix<T>& c)
{
	gemm(a.base(), trans_a, b.base(), trans_b, alpha, beta, c.base());
}

} // end of namespace math
} // end of namespace matcha

#endif
