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

#include "matcha/ui/widget.hpp"

#include <gtk/gtk.h>

namespace matcha { namespace ui {

class widget::implementation
{
public:
	implementation() = delete;
	implementation(GtkWidget* gtk_widget);
	virtual ~implementation() noexcept;

	void show();

	GtkWidget* widget_ptr();

private:
	GtkWidget* widget_;
};


} // end of namespace process
} // end of namespace matcha

#endif
