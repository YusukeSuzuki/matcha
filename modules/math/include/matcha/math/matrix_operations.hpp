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
#ifndef MATCHA_MATH_MATRIX_OPERATIONS_HPP__
#define MATCHA_MATH_MATRIX_OPERATIONS_HPP__

#include <matcha/math/scalar.hpp>
#include <matcha/math/matrix.hpp>

namespace matcha { namespace math {

void fill(const scalar_base& src, matrix_base& dst);

void make_identity(matrix_base& dst);

template<typename T>
matrix<T> identity(uint32_t rows, uint32_t cols, uint32_t channels = 1)
{
	matrix<T> result(rows, cols, channels);
	make_identity( result );

	return std::move( result );
}

} // end of namespace math
} // end of namespace matcha

#endif

