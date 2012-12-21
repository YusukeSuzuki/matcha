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
#ifndef MATCHA_CORE_OPTIONAL_HPP__
#define MATCHA_CORE_OPTIONAL_HPP__

#include <memory>

namespace matcha { namespace core {

enum class none_t
{
	none,
};

const none_t none = none_t::none;

template<typename T>
class optional
{
public:
	optional() : ptr_(nullptr) {}
	optional(none_t n) : ptr_(nullptr) {}
	optional(const T& t) : ptr_( new T(t) ) {}
	optional(const optional& o) : ptr_( new T(*o) ) {};

	optional& operator = (none_t)
	{
		ptr_ = nullptr;
		return *this;
	}

	optional& operator =(const T& t)
	{
		if(ptr_) *ptr_ = t; else ptr_ = new T(t);
		return *this;
	}

	optional& operator =(const optional& o)
	{
		if(this == &o) return *this;

		if(o) return *this = none;
		
		return *this = o.get();
	}

	const T& get() const { return *ptr_; }
	T& get() { return *ptr_; }

	const T& get_value_or(const T& d) const { return *this ? *(*this) : d; }
	T& get_value_or(T& d) { return *this ? *(*this) : d; }

	const T* operator ->() const { return get_ptr(); }
	T* operator ->() { return get_ptr(); }

	const T& operator *() const { return *(ptr_.get()); }
	T& operator *() { return *(ptr_.get()); }

	const T* get_ptr() const { return ptr_.get(); }
	T* get_ptr() { return ptr_.get(); }

	operator bool() const { return ptr_.get() != nullptr; }
	bool operator!() const { return ptr_.get() == nullptr; }

private:
	std::unique_ptr<T> ptr_;
};

template<typename T>
inline bool
operator ==(const optional<T>& lhs, const optional<T>& rhs)
{
	return
		(!lhs && !rhs) ? true :
			(!lhs) ? false :
				(!rhs) ? false :
					(*lhs == *rhs);
				
}

template<typename T>
inline bool
operator !=(const optional<T>& lhs, const optional<T>& rhs)
{
	return !(lhs == rhs);
}

template<typename T>
inline bool
operator ==(const optional<T>& lhs, none_t rhs)
{
	return lhs == optional<T>(rhs);
}

template<typename T>
inline bool
operator !=(const optional<T>& lhs, none_t rhs)
{
	return !(lhs == rhs);
}

template<typename T>
inline bool
operator ==(none_t lhs, const optional<T>& rhs)
{
	return rhs == optional<T>(lhs);
}

template<typename T>
inline bool
operator !=(none_t lhs, const optional<T>& rhs)
{
	return !(lhs == rhs);
}

} // end of namespace Core
} // end of namespace Matcha

#endif
