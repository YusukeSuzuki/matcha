/*
 * Matcha Robotics Application Framework
 *
 * Copyright (C) 2011 Yusuke Suzuki 
 *
 *    Licensed under the Apache License, Version 2.0 (the License);
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an AS IS BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#ifndef MATCHA_CORE_OPTION_PARSER_HPP__
#define MATCHA_CORE_OPTION_PARSER_HPP__

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace matcha { namespace core {

class option_parser
{
public:
	struct key
	{
		std::string key_short;
		std::string key_long;
		bool has_argument;
	};

	option_parser();
	option_parser(const std::vector<key>& keys);

	virtual ~option_parser() noexcept;

	option_parser& operator +(const key& key);
	option_parser& operator +(const std::vector<key>& keys);

	option_parser& operator =(const key& key);
	option_parser& operator =(const std::vector<key>& keys);

	option_parser& operator +=(const key& key);
	option_parser& operator +=(const std::vector<key>& keys);

	std::multimap<std::string, std::string> parse(
		int argc, char* argv[]);
	std::multimap<std::string, std::string> parse(
		const std::vector<std::string>& args);

private:
	class implementation;
	std::shared_ptr<implementation> implementation_;
};

} // end of namespace core
} // end of namespace matcha

#endif
