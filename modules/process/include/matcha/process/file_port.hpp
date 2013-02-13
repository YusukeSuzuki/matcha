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
#ifndef MATCHA_PROCESS_FILE_PORT_HPP__
#define MATCHA_PROCESS_FILE_PORT_HPP__

#include <matcha/process/port.hpp>

#include <memory>
#include <set>
#include <string>

namespace matcha { namespace process {

class file_port : public port
{
public:
	enum class flag
	{
		read,
		write,
	};

	file_port(const std::string& path, const std::set<flag>& flags);

	file_port& write(const std::string& str);

	port& handle(event& event);

private:
	class implementation;
	std::shared_ptr<implementation> implementation_;
};

} // end of namespace process
} // end of namespace matcha

#endif
