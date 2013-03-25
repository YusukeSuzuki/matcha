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
#include "window.internal.hpp"

namespace matcha { namespace ui {

window::implementation::implementation(window* window, const std::string& title) :
	window_(window),
	widget_( gtk_window_new(GTK_WINDOW_TOPLEVEL) )
{
}

window::implementation::~implementation() noexcept
{
}

void
window::implementation::show()
{
	gtk_widget_show( widget_ );
}

void
window::implementation::resize(int width, int height)
{
	gtk_window_resize( window_ptr(), width, height);
}

GtkWindow*
window::implementation::window_ptr()
{
	return reinterpret_cast<GtkWindow*>(widget_);
}

void
window::implementation::on_delete(const window::on_delete_handler& handler)
{
	on_delete_handler_ = handler;
	g_signal_connect(widget_, "destroy",
		G_CALLBACK( (void(*)(GtkWidget*, gpointer))(&implementation::on_delete) ), this);
}

void
window::implementation::on_delete(GtkWidget* w, gpointer d)
{
	window::implementation* window = reinterpret_cast<window::implementation*>(d);

	if(window->on_delete_handler_)
	{
		(*window->on_delete_handler_)(*window->window_);
	}
}

} // end of namespace process
} // end of namespace matcha

