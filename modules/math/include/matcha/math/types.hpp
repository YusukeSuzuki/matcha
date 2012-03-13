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
#ifndef MATCHA_MATH_TYPES_HPP__
#define MATCHA_MATH_TYPES_HPP__

#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>

namespace matcha { namespace math {

enum class type_id_t : int32_t
{
	  int8_id = 0x0,
	 uint8_id,
	 int16_id,
	uint16_id,
	 int32_id,
	uint32_id,
	 int64_id,
	uint64_id,
	 float_id = 0x00010000,
	double_id,
	unsupported = -1
};

template<typename T> constexpr bool is_supported_type(){ return false; }
template<> constexpr bool is_supported_type<  int8_t>(){ return true; }
template<> constexpr bool is_supported_type< uint8_t>(){ return true; }
template<> constexpr bool is_supported_type< int16_t>(){ return true; }
template<> constexpr bool is_supported_type<uint16_t>(){ return true; }
template<> constexpr bool is_supported_type< int32_t>(){ return true; }
template<> constexpr bool is_supported_type<uint32_t>(){ return true; }
template<> constexpr bool is_supported_type<   float>(){ return true; }
template<> constexpr bool is_supported_type<  double>(){ return true; }

template<typename T>
constexpr type_id_t type_id()
{
	static_assert(is_supported_type<T>(), "not supported");
	return -1;
}

#define MATCHA_TYPE_ID_DECRARATION_TEMP_MACRO(X,Y) \
	template<> constexpr type_id_t type_id<X>(){ return type_id_t::Y; }
	MATCHA_TYPE_ID_DECRARATION_TEMP_MACRO(  int8_t,   int8_id);
	MATCHA_TYPE_ID_DECRARATION_TEMP_MACRO( uint8_t,  uint8_id);
	MATCHA_TYPE_ID_DECRARATION_TEMP_MACRO( int16_t,  int16_id);
	MATCHA_TYPE_ID_DECRARATION_TEMP_MACRO(uint16_t, uint16_id);
	MATCHA_TYPE_ID_DECRARATION_TEMP_MACRO( int32_t,  int32_id);
	MATCHA_TYPE_ID_DECRARATION_TEMP_MACRO(uint32_t, uint32_id);
	MATCHA_TYPE_ID_DECRARATION_TEMP_MACRO( int64_t,  int64_id);
	MATCHA_TYPE_ID_DECRARATION_TEMP_MACRO(uint64_t, uint64_id);
	MATCHA_TYPE_ID_DECRARATION_TEMP_MACRO(   float,  float_id);
	MATCHA_TYPE_ID_DECRARATION_TEMP_MACRO(  double, double_id);
#undef MATCHA_TYPE_ID_DECRARATION_TEMP_MACRO

template<typename T>
constexpr type_id_t type_id(const T&)
{
	return type_id<T>();
}

template<typename T>
constexpr bool supported_type_assert()
{
	static_assert(is_supported_type<T>(), "not supported");
	return is_supported_type<T>();
}

template<type_id_t t>
constexpr bool supported_type_assert()
{
	static_assert(t != type_id_t::unsupported, "not supported");
	return true;
}

template<typename T, bool b = true>
struct type_of_id_base
{
	typedef T type;
	static const type_id_t type_id = type_id<T>();
};

template<type_id_t t>
struct type_of_id : public type_of_id_base<void, supported_type_assert<t>()>
{
};

#define MATCHA_TYPE_OF_ID_DECRARATION_TEMP_MACRO(X, Y) \
	template<> struct type_of_id<type_id_t::X> : public type_of_id_base<Y> {};
	MATCHA_TYPE_OF_ID_DECRARATION_TEMP_MACRO(  int8_id,   int8_t);
	MATCHA_TYPE_OF_ID_DECRARATION_TEMP_MACRO( uint8_id,  uint8_t);
	MATCHA_TYPE_OF_ID_DECRARATION_TEMP_MACRO( int16_id,  int16_t);
	MATCHA_TYPE_OF_ID_DECRARATION_TEMP_MACRO(uint16_id, uint16_t);
	MATCHA_TYPE_OF_ID_DECRARATION_TEMP_MACRO( int32_id,  int32_t);
	MATCHA_TYPE_OF_ID_DECRARATION_TEMP_MACRO(uint32_id, uint32_t);
	MATCHA_TYPE_OF_ID_DECRARATION_TEMP_MACRO( int64_id,  int64_t);
	MATCHA_TYPE_OF_ID_DECRARATION_TEMP_MACRO(uint64_id, uint64_t);
	MATCHA_TYPE_OF_ID_DECRARATION_TEMP_MACRO( float_id,  float);
	MATCHA_TYPE_OF_ID_DECRARATION_TEMP_MACRO(double_id, double);
#undef MATCHA_TYPE_OF_ID_DECRARATION_TEMP_MACRO

inline std::size_t size_of_type(type_id_t type_id)
{
	#define MATCHA_SWITCH_LOCAL_MACRO(X,Y) case type_id_t::X : return sizeof(Y); break;

	switch(type_id)
	{
	MATCHA_SWITCH_LOCAL_MACRO(  int8_id,   int8_t);
	MATCHA_SWITCH_LOCAL_MACRO( uint8_id,  uint8_t);
	MATCHA_SWITCH_LOCAL_MACRO( int16_id,  int16_t);
	MATCHA_SWITCH_LOCAL_MACRO(uint16_id, uint16_t);
	MATCHA_SWITCH_LOCAL_MACRO( int32_id,  int32_t);
	MATCHA_SWITCH_LOCAL_MACRO(uint32_id, uint32_t);
	MATCHA_SWITCH_LOCAL_MACRO( int64_id,  int64_t);
	MATCHA_SWITCH_LOCAL_MACRO(uint64_id, uint64_t);
	MATCHA_SWITCH_LOCAL_MACRO( float_id,  float);
	MATCHA_SWITCH_LOCAL_MACRO(double_id, double);
	default: break;
	}

	#undef MATCHA_LOCAL_CASE_MACRO

	assert(false && "invalid type_id");
	return 0;
}

} // end of namespace math
} // end of namespace matcha

#endif
