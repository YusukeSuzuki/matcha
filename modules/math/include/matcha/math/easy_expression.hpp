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
#ifndef MATCHA_MATH_EASY_EXPRESSION_HPP__
#define MATCHA_MATH_EASY_EXPRESSION_HPP__

#include <matcha/core/exception.hpp>

#include <matcha/math/types.hpp>
#include <matcha/math/scalar.hpp>
#include <matcha/math/matrix.hpp>
#include <matcha/math/linear_algebra.hpp>

namespace matcha { namespace math { namespace easy_expression {

// ----------------------------------------------------------------------
// sub
// ----------------------------------------------------------------------

template<typename T>
matrix<T> operator-(const matrix<T>& a, typename matrix<T>::type b)
{
	auto c = a; ///< redundant copy
	sub(a, b, c);
	return c;
}

template<typename T>
matrix<T> operator-(typename matrix<T>::type a, const matrix<T>& b)
{
	auto c = a; ///< redundant copy
	sub(a, b, c);
	return c;
}

// ----------------------------------------------------------------------
// mul
// ----------------------------------------------------------------------

template<typename T>
matrix<T> operator*(const matrix<T>& a, typename matrix<T>::type b)
{
	auto c = a; ///< redundant copy
	mul(a, b, c);
	return c;
}

template<typename T>
matrix<T> operator*(typename matrix<T>::type b, const matrix<T>& a)
{
	auto c = a; ///< redundant copy
	mul(a, b, c);
	return c;
}

} // end of namespace easy_expression
} // end of namespace math
} // end of namespace matcha

#endif
