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
#ifndef MATCHA_UI_BUTTON_INTERNAL_HPP__
#define MATCHA_UI_BUTTON_INTERNAL_HPP__

#include "matcha/ui/button.hpp"
#include "widget.internal.hpp"

#include "matcha/core/optional.hpp"

#include <gtk/gtk.h>

namespace matcha { namespace ui {

class button::implementation : public widget::implementation
{
public:
	implementation() = delete;
	implementation(button* button, const std::string& label);
	virtual ~implementation() noexcept;

	void on_click(const button::on_click_handler& handler);
	static void on_click(GtkWidget* w, gpointer d);

private:
	button* button_;

	core::optional<button::on_click_handler> on_click_handler_;
};

} // end of namespace process
} // end of namespace matcha

#endif
