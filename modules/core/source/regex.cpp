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
#include "matcha/core/regex.hpp"

#include <cerrno>
#include <cstring>

#include <regex.h>

namespace matcha { namespace core {

class regex::implementation
{
public:
	implementation(const std::string& pattern)
	{
		if( int err = regcomp(&regex_, pattern.c_str(), 0) )
		{
			auto line = MATCHA_EXCEPTION_WHERE;
			char buf[500];
			regerror(err, &regex_, buf, sizeof(buf));

			throw(matcha::core::exception(line.c_str(), buf) );
		}
	}

	virtual ~implementation() noexcept
	{
		regfree(&regex_);
	}

	bool match(const std::string& text)
	{
		regmatch_t matches[20];
		if( !regexec(&regex_, text.c_str(), 20, matches, 0) )
		{
			return false;
		}

		return true;
	}

	regex_t regex_;
};

regex::regex(const std::string& pattern) :
	implementation_( new implementation(pattern) )
{
}

regex::~regex() noexcept
{
}

bool
regex::match(const std::string& text)
{
	return implementation_->match(text);
}

} // end of namespace Core
} // end of namespace Matcha

