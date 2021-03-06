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
#ifndef MATCAH_UI_BUTTON_HPP__
#define MATCAH_UI_BUTTON_HPP__

#include <matcha/ui/widget.hpp>

#include <functional>
#include <memory>
#include <string>

namespace matcha { namespace ui {

class button : public widget
{
public:
	button();
	button(const std::string& label);
	virtual ~button() noexcept;

	button& show();

	using on_click_handler = std::function<void(button&)>;
	button& on_click(const on_click_handler& handler);

private:
	class implementation;
	std::shared_ptr<implementation> implementation_;
};

} // end of namespace ui
} // end of namespace matcha

#endif
