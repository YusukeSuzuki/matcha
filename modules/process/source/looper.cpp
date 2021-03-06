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
#include "matcha/process/looper.hpp"
#include "looper.internal.hpp"

namespace matcha { namespace process {

looper::looper() :
	implementation_( new looper::implementation(this) )
{
}

looper::~looper() noexcept
{
}

void
looper::run()
{
	implementation_->run();
}

void
looper::quit()
{
	implementation_->quit();
}

looper::before_run_handler_function&
looper::before_run_handler()
{
	return implementation_->before_run_handler();
}

matcha::process::listener&
looper::listener()
{
	return implementation_->listener();
}

const matcha::process::listener&
looper::listener() const
{
	return implementation_->listener();
}

} // end of namespace process
} // end of namespace matcha

