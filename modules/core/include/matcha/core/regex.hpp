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
#ifndef MATCHA_CORE_REGEX_HPP__
#define MATCHA_CORE_REGEX_HPP__

#include <memory>
#include <string>

namespace matcha { namespace core {

/**
 * @class regex
 *
 * @brief substitute for std::regex. this class is to be deprecated.
 */
class regex
{
public:
	regex(const std::string& pattern);
	virtual ~regex() noexcept;

	bool match(const std::string& text);

private:
	class implementation;
	std::shared_ptr<implementation> implementation_;
};

} // end of namespace Core
} // end of namespace Matcha

#endif
