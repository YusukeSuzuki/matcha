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
#ifndef MATCHA_MATH_STREAM_HPP__
#define MATCHA_MATH_STREAM_HPP__

#include <matcha/core/exception.hpp>

#include <matcha/math/types.hpp>
#include <matcha/math/scalar.hpp>
#include <matcha/math/matrix.hpp>

 #include <ostream>

namespace matcha { namespace math { namespace easy_expression {

std::ostream& operator << (std::ostream& out, const matrix_base& m);

template<typename T>
std::ostream& operator << (std::ostream& out, const matrix<T>& m)
{
	out << m.base();
}

} // end of namespace easy_expression
} // end of namespace math
} // end of namespace matcha

#endif
