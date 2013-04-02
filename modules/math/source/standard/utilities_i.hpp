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
#ifndef MATCHA_MATH_UTILITIES_I_HPP__
#define MATCHA_MATH_UTILITIES_I_HPP__

namespace matcha { namespace math {

template<typename T>
inline bool tri_equal(T a, T b, T c)
{
	return (a == b) && (b == c);
}

} // end of namespace math
} // end of namespace matcha

#define MATCHA_MATH_DECL_ALL(TEMPLATE) \
	TEMPLATE(  int8_t) \
	TEMPLATE( uint8_t) \
	TEMPLATE( int16_t) \
	TEMPLATE(uint16_t) \
	TEMPLATE( int32_t) \
	TEMPLATE(uint32_t) \
	TEMPLATE( int64_t) \
	TEMPLATE(uint64_t) \
	TEMPLATE(   float) \
	TEMPLATE(  double)

#endif
