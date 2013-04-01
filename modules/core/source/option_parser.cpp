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
#include "matcha/core/option_parser.hpp"

#include <string>

#include <getopt.h>

namespace matcha { namespace core {

class option_parser::implementation
{
public:
	implementation()
	{
	}

	implementation(const std::vector<key>& keys)
	{
	}

	~implementation() noexcept
	{
	}

	void operator =(const key& key)
	{
		keys_ = {key};
	}

	void operator =(const std::vector<key>& keys)
	{
		keys_ = keys;
	}

	void operator +=(const key& key)
	{
		keys_.push_back(key);
	}

	void operator +=(const std::vector<key>& keys)
	{
		keys_.insert(keys_.end(), keys.begin(), keys.end());
	}

	void parse(int argc,const char* argv[])
	{
		for(;;)
		{
			struct ::option options[] =
			{
				{"add", required_argument, 0, 0},
				{}
			};

			int option_index = 0;

			std::vector<char*> args(argc);

			for(int i = 0; i < argc; ++i)
			{
				//args[i] = argv[i];
			}
			
			int c = getopt_long(argc, &args[0], "", options, &option_index);

			switch(c)
			{
			case 0:
				break;
			default:
				break;
			}
		}
	}

	void parse(const std::vector<std::string>& args)
	{
		std::vector<const char*> argv;

		for(auto& s : args)
		{
			argv.push_back(s.c_str());
		}

		parse(args.size(), &argv[0]);
	}

private:
	std::vector<key> keys_;
};

option_parser::option_parser() :
	implementation_( new implementation() )
{
}

option_parser::option_parser(const std::vector<key>& keys) :
	implementation_( new implementation(keys) )
{
}

option_parser::~option_parser() noexcept
{
}

option_parser&
option_parser::operator +(const key& key)
{
	return *this;
}

option_parser&
option_parser::operator +(const std::vector<key>& keys)
{
	return *this;
}

option_parser&
option_parser::operator =(const key& key)
{
	return *this;
}

option_parser&
option_parser::operator =(const std::vector<key>& keys)
{
	return *this;
}

option_parser&
option_parser::operator +=(const key& key)
{
	return *this;
}

option_parser&
option_parser::operator +=(const std::vector<key>& keys)
{
	return *this;
}

std::multimap<std::string, std::string>
option_parser::parse(int argc, char* argv[])
{
	return std::multimap<std::string, std::string>();
}

std::multimap<std::string, std::string>
option_parser::parse(const std::vector<std::string>& args)
{
	return std::multimap<std::string, std::string>();
}

} // end of namespace core
} // end of namespace matcha

