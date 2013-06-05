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
#ifndef MATCHA_MATH_VECTOR_HPP__
#define MATCHA_MATH_VECTOR_HPP__

#include <matcha/math/scalar.hpp>
#include <matcha/math/types.hpp>
#include <utility>

namespace matcha { namespace math {

template<typename T, unsigned d>
using vector = scalar<T,d>;

template<typename T, unsigned d>
double dot(const vector<T,d>& lhs, const vector<T,d>& rhs)
{
	double r = 0;

	for(auto i = 0; i < d; ++i)
	{
		r += lhs[i] * rhs[i];
	}

	return r;
}

template<typename T>
T cross(const vector<T,2>& lhs, const vector<T,2>& rhs)
{
	return  lhs[0] * rhs[1] - lhs[1] * rhs[0];
}

template<typename T>
vector<T,3> cross(const vector<T,3>& lhs, const vector<T,3>& rhs)
{
	return vector<T,3>(
		lhs[1] * rhs[2] - lhs[2] * rhs[1],
		lhs[2] * rhs[0] - lhs[0] * rhs[2],
		lhs[0] * rhs[1] - lhs[1] * rhs[0]
		);
}

} // end of namespace math
} // end of namespace matcha

#endif
