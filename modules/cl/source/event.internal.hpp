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
#ifndef __MATCAH_CL_EVENT_INTERNAL_HPP_
#define __MATCAH_CL_EVENT_INTERNAL_HPP_

#include "matcha/cl/cl.hpp"

#include <algorithm>

namespace matcha { namespace cl {

class event::implementation
{
public:
	implementation(cl_event event) :
		event_(event)
	{
	}

	static std::vector<cl_event> to_cl_events(const std::vector<event>& events)
	{
		std::vector<cl_event> result(events.size());
		std::transform(events.begin(), events.end(), result.begin(),
			[](const event& event) -> cl_event
				{ return event.implementation_->event_; });
		return result;
	}


	operator cl_event()
	{
		return event_;
	}

private:
	cl_event event_;

	friend class command_queue;
};

} // end of namespace Core
} // end of namespace Matcha

#endif
