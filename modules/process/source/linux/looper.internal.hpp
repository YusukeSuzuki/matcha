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
#ifndef MATCHA_PROCESS_LOOPER_INTERNAL_HPP__
#define MATCHA_PROCESS_LOOPER_INTERNAL_HPP__

#include "matcha/process/looper.hpp"
#include "matcha/process/listener.hpp"

#include <sys/epoll.h>

namespace matcha { namespace process {

class looper::implementation
{
public:
	implementation(looper* looper);
	virtual ~implementation() noexcept;

	void before_run(before_run_handler_function handler);
	before_run_handler_function& before_run_handler();

	void run();
	void quit();

	void detach();

	matcha::process::listener& listener();
	const matcha::process::listener& listener() const;

private:
	static void empty_handler(looper&) {}

	looper* looper_;
	matcha::process::listener listener_;
	before_run_handler_function before_run_handler_;
};

} // end of namespace process
} // end of namespace matcha

#endif
