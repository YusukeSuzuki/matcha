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
#include "matcha/ui/window.hpp"
#include "window.internal.hpp"

#include "matcha/ui/widget.hpp"

namespace matcha { namespace ui {

window::window(const std::string& title) :
	implementation_( new window::implementation(this, title) )
{
}

window::~window() noexcept
{
}

window&
window::show()
{
	implementation_->show();
	return *this;
}

window&
window::resize(int width, int height)
{
	implementation_->resize(width, height);
	return *this;
}

window&
window::on_delete(const on_delete_handler& handler)
{
	implementation_->on_delete(handler);
	return *this;
}

window&
window::add(std::shared_ptr<widget> widget)
{
	return *this;
}

} // end of namespace ui
} // end of namespace matcha

