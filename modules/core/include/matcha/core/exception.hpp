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
#ifndef __MATCAH_CORE_EXCEPTION_H_
#define __MATCAH_CORE_EXCEPTION_H_

#include <exception>
#include <string>

#define TO_STR19771228(N) #N
#define LINE_TO_STR19771228(N) TO_STR19771228(N)
#define MATCHA_EXCEPTION_WHERE (std::string(__FILE__ ":") + __FUNCTION__ + "(" LINE_TO_STR19771228(__LINE__) ")")

namespace matcha { namespace core {



class exception : public std::exception
{
public:
	exception(const char* where, const char* what);
	virtual ~exception() noexcept;
	virtual const char* where() const noexcept;
	virtual const char* what() const noexcept;

protected:
	exception();
	std::string where_;
	std::string what_;
};

class system_exception : public exception
{
public:
	system_exception(const char* where, int errornumber);
	virtual ~system_exception() noexcept;
	virtual const char* where() const noexcept;
	virtual const char* what() const noexcept;
};

} // end of namespace core
} // end of namespace matcha

#endif

