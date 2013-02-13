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

#include "matcha/process/event.hpp"
#include "event.internal.hpp"

namespace matcha { namespace process {

event::implementation::implementation(const implementation& implementation) :
	content_(implementation.content_)
{
}

event::implementation::implementation(const core::any& content) :
	content_(content)
{
}

event::implementation::~implementation() noexcept
{
}

core::any&
event::implementation::content()
{
	return content_;
}

const core::any&
event::implementation::content() const
{
	return content_;
}

} // end of namespace process
} // end of namespace matcha

