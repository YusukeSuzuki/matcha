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
#ifndef MATCHA_PROCESS_LOOPER_HPP__
#define MATCHA_PROCESS_LOOPER_HPP__

#include <matcha/process/listener.hpp>
#include <matcha/process/handler.hpp>

#include <functional>

namespace matcha { namespace process {

class looper
{
public:
	looper();
	virtual ~looper() noexcept;

	using before_run_handler_function = std::function< void(looper&) >;

	before_run_handler_function& before_run_handler();

	void run();
	void detach();
	void quit();

	matcha::process::listener& listener();
	const matcha::process::listener& listener() const;

private:
	class implementation;
	std::unique_ptr<implementation> implementation_;
};

} // end of namespace process
} // end of namespace matcha

#endif
