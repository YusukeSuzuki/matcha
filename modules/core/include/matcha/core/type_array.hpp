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
#ifndef __MATCAH_CORE_TYPE_ARRAY_H_
#define __MATCAH_CORE_TYPE_ARRAY_H_

#include <tuple>
#include <type_traits>
#include <utility>

namespace matcha { namespace core {

template<typename T0, typename H0, typename ...Args0>
struct type_array_base
{
	template<unsigned i, typename T, typename S>
	struct zero_type
	{
		typedef S type;
	};
 
	template<typename T, typename S>
	struct zero_type<0, T, S>
	{
		typedef T type;
	};
 
	template<unsigned i, typename... Args1>
	struct get_type_recurse;
 
	template<unsigned i>
	struct get_type_recurse<i>{};
 
	template<unsigned i, typename T1, typename... Args1>
	struct get_type_recurse<i, T1, Args1...>
	{
		typedef typename zero_type< !(i == 0), T1,
			typename get_type_recurse< (i == 0 ? 0 : i - 1), Args1...>::type >::type type;
	};
 
	template<typename T1>
	struct get_type_recurse<0, T1>
	{
		typedef T1 type;
	};
 
	template<unsigned i>
	struct get_type
	{
		typedef typename get_type_recurse<i, H0, Args0...>::type type;
	};

	static const std::size_t size = sizeof...(Args0) + 1;
};
 
template<typename T, unsigned i>
struct get_type
{
	typedef typename T::template get_type<i>::type type;
};
 
template<typename T>
struct type_array
{
};
 
template<unsigned i, typename T>
auto get(T&) ->
	typename type_array<T>::template get_type<i>::type&;

template<unsigned i, typename T>
auto get(const T&) ->
	const typename type_array<T>::template get_type<i>::type&;

#if 0

template<unsigned i,typename T, typename U, unsigned j = (i - 1) ? i - 1: 1>
inline T& copy_recurse(T& lhs, U& rhs)
{
	get<i-1>(lhs) = get<i-1>(rhs);
	return (i - 1) ? copy_recurse<j>(lhs, rhs) : lhs;
}

template<typename T, typename U>
inline T& copy(T& lhs, U& rhs)
{
	return copy_recurse<std::tuple_size<T>::value>(lhs, rhs);
}

#endif
 
template<unsigned i,typename T, typename U, unsigned j = (i - 1) ? i - 1: 1>
inline bool operator_equal_recurse(const T& lhs, const U& rhs)
{
	return
		(i - 1) ?
		(operator_equal_recurse<j>(lhs, rhs) && (get<i-1>(lhs) == get<i-1>(rhs))) :
		(get<i-1>(lhs) == get<i-1>(rhs));
}

template<typename T, typename U>
inline bool operator==(const T& lhs, const U& rhs)
{
	return operator_equal_recurse<type_array<T>::size>(lhs, rhs);
}
 
template<typename T, template<class> class TT = type_array>
inline bool is_equal(const T& lhs, const T& rhs)
{
	return operator_equal_recurse<type_array<T>::size>(lhs, rhs);
}
 
} // end of namespace core
} // end of namespace matcha

#define matcha_type_array_declare(TYPE, MEMBER_TYPES...) \
	template<> \
	struct type_array<TYPE> : public type_array_base<TYPE, ##MEMBER_TYPES> \
	{ \
		typedef TYPE base_type; \
		type_array(base_type& t) : m_(t) \
		{ \
		} \
		TYPE& m_; \
	};

#define matcha_type_array_function_definition(TYPE, INDEX, MEMBER) \
	template<> \
	auto get<INDEX>(TYPE& t) -> type_array<TYPE>::get_type<INDEX>::type& \
		{ return t.MEMBER; } \
	template<> \
	auto get<INDEX>(const TYPE& t) -> const type_array<TYPE>::get_type<INDEX>::type& \
		{ return t.MEMBER; }

#endif

