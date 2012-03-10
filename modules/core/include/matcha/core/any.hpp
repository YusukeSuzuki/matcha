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
#ifndef MATCHA_CORE_ANY_HPP__
#define MATCHA_CORE_ANY_HPP__

#include <type_traits>
#include <typeinfo>
#include <memory>

namespace matcha { namespace core {

/**
 * @class any
 *
 * @brief any container
 */
class any
{
public:
	/**
	 * default constructor
	 */
	any() :
		placeholder_( new void_placehoder() )
	{
	}

	/**
	 * copy constructor
	 */
	any(const any& a) :
		placeholder_( a.placeholder_->clone() )
	{
	}

	/**
	 * move constructor
	 */
	any(any&& a) :
		placeholder_( a.placeholder_ )
	{
	}

	/**
	 * assign constructor
	 */
	template<typename T>
	any(const T& a) :
		placeholder_( new placehoder<T>(a) )
	{
	}

	/**
	 * copy operator
	 */
	any& operator=(const any& a)
	{
		placeholder_ = std::shared_ptr<placeholder_base>(a.placeholder_->clone());
		return *this;
	}

	/**
	 * move operator
	 */
	any& operator=(any&& a)
	{
		swap(*this, a);
		return *this;
	}

	/**
	 * assign operator
	 */
	template<typename T>
	any& operator=(const T& a)
	{
		return *this = any(a);
	}

	/**
	 * cast to const T&
	 */
	template<typename T>
	const T& cast() const
	{
		return dynamic_cast<placehoder<T>&>(*placeholder_).something_;
	}

	/**
	 * cast to T&
	 */
	template<typename T>
	T& cast()
	{
		return dynamic_cast<placehoder<T>&>(*placeholder_).something_;
	}

	/**
	 * return if is type T
	 */
	template<typename T>
	bool Is(typename std::enable_if<std::is_void<T>::value>::type* dummy = NULL) const
	{
		return dynamic_cast<void_placehoder*>(placeholder_.get()) != NULL;
	}

	template<typename T>
	bool Is(typename std::enable_if<!std::is_void<T>::value>::type* dummy = NULL) const
	{
		return dynamic_cast<placehoder<T>*>(placeholder_.get()) != NULL;
	}

	/**
	 * return const type_info& of content
	 */
	const std::type_info& type_info() const
	{
		return placeholder_->type_info();
	}

	/**
	 * swap content
	 */
	static void swap(any& left, any& right)
	{
		std::swap(right.placeholder_, left.placeholder_);
	}

	/**
	 * destructor
	 */
	virtual ~any() throw() {}

private:
	class placeholder_base
	{
	public:
		placeholder_base() {}

		virtual ~placeholder_base() throw() {}

		virtual placeholder_base* clone() const = 0;
		virtual const std::type_info& type_info() const = 0;
	};

	template<typename T>
	class placehoder : public placeholder_base
	{
	public:
		placehoder(const T& something) :
			placeholder_base(),
			something_( something )
		{
		}

		virtual ~placehoder() throw()
		{
		}

		virtual placeholder_base* clone() const
		{
			return new placehoder(something_);
		}

		virtual const std::type_info& type_info() const
		{
			return typeid(something_);
		}

	private:
		T something_;
		friend class any;
	};

	class void_placehoder : public placeholder_base
	{
	public:
		void_placehoder() :
			placeholder_base()
		{
		}

		virtual ~void_placehoder() throw()
		{
		}

		virtual placeholder_base* clone() const
		{
			return new void_placehoder();
		}

		virtual const std::type_info& type_info() const
		{
			return typeid(void);
		}

	private:
		friend class any;
	};

	std::shared_ptr<placeholder_base> placeholder_;
};

#if 0
/**
 * return if is type T
 */
template<>
bool
Any::Is<void>() const
{
	return dynamic_cast<VoidPlacehoder*>(placeholder_.get()) != NULL;
}

template<typename T>
bool
Any::Is() const
{
	return dynamic_cast<Placehoder<T>*>(placeholder_.get()) != NULL;
}
#endif

} // end of namespace Core
} // end of namespace Matcha

#endif
