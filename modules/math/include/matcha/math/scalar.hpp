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
#ifndef MATCHA_MATH_SCALAR_HPP__
#define MATCHA_MATH_SCALAR_HPP__

#include <matcha/math/types.hpp>

#include <utility>

namespace matcha { namespace math {

struct scalar_base
{
	type_id_t type;
	std::size_t dims;
	void* data;
};

template<typename T, unsigned d>
struct scalar 
{
	T var[d];

	operator scalar_base()
	{
		return {type_id<T>(), d, var};
	}

	T& operator[](unsigned i)
	{
		return var[i];
	}

	const T& operator[](unsigned i) const
	{
		return var[i];
	}
};

template<typename T, unsigned d, unsigned i, unsigned j = i-1 ? i-1 : 1>
T add(const scalar<T,d>& a, const scalar<T,d>& b, scalar<T,d>& c)
{
	return c[i-1] = (i-1) ? (add<T,d,j>(a,b,c), a[j]+b[j]) : a[i-1] + b[i-1];
}

template<typename T, unsigned d>
scalar<T,d> add(const scalar<T,d>& a, const scalar<T,d>& b)
{
	/**
	 * @todo more efficient implementation
	 */
	scalar<T,d> c;
	add<T,d,d>(a,b,c);
	return std::move(c);
}

} // end of namespace math
} // end of namespace matcha

#endif
