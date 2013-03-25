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
#include "button.internal.hpp"

namespace matcha { namespace ui {

button::implementation::implementation(button* button, const std::string& label) :
	widget::implementation( gtk_button_new_with_label(label.c_str()) ),
	button_(button)
{
}

button::implementation::~implementation() noexcept
{
}

void
button::implementation::on_click(const button::on_click_handler& handler)
{
	on_click_handler_ = handler;
	g_signal_connect(widget_ptr(), "clicked",
		G_CALLBACK( (void(*)(GtkWidget*,gpointer))(&implementation::on_click)), this);
}

void
button::implementation::on_click(GtkWidget* w, gpointer d)
{
	button::implementation* button = reinterpret_cast<button::implementation*>(d);

	if(button->on_click_handler_)
	{
		(*button->on_click_handler_)(*button->button_);
	}
}

} // end of namespace ui
} // end of namespace matcha

