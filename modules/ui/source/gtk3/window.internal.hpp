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
#ifndef MATCHA_UI_WINDOW_INTERNAL_HPP__
#define MATCHA_UI_WINDOW_INTERNAL_HPP__

#include <matcha/core/optional.hpp>
#include <matcha/ui/window.hpp>

#include <gtk/gtk.h>

namespace matcha { namespace ui {

template<typename T>
GtkWidget* widghet_cast(T* widget)
{
	return reinterpret_cast<GtkWidget*>(widget);
}

template<typename T>
auto widget_cast(GtkWidget* widget) -> T*
{
	return reinterpret_cast<T*>(widget);
}

class window::implementation
{
public:
	implementation(window* window, const std::string& title);
	virtual ~implementation() noexcept;

	void show();
	void resize(int width, int height);

	void on_delete(const window::on_delete_handler& handler);
	static void on_delete(GtkWidget* w, gpointer d);

private:
	window* window_;
	GtkWidget* widget_;
	GtkWindow* window_ptr();

	core::optional<window::on_delete_handler> on_delete_handler_;
};

} // end of namespace process
} // end of namespace matcha

#endif
