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
#include "matcha/core/exception.hpp"

#include <cerrno>
#include <cstring>

namespace matcha { namespace core {

exception::exception() : std::exception(), where_(""), what_("")
{
}

exception::exception(const char* where, const char* what)
	:
	std::exception(),
	where_(where),
	what_(what)
{
}

exception::~exception() throw()
{
}

const char*
exception::where() const noexcept
{
	return where_.c_str();
}

const char*
exception::what() const noexcept
{
	return what_.c_str();
}

system_exception::system_exception(const char* where, int errornumber)
	:
	exception(
		where,
		(std::string("matcha::system_exception:") + strerror(errno)).c_str()
		)
{
}

system_exception::~system_exception() noexcept
{
}

const char*
system_exception::where() const noexcept
{
	return where_.c_str();
}

const char*
system_exception::what() const noexcept
{
	return what_.c_str();
}

} // end of namespace Core
} // end of namespace Matcha

