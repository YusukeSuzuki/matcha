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
#ifndef __MATCAH_CORE_TYPE_H_
#define __MATCAH_CORE_TYPE_H_

#include <tuple>
#include <type_traits>
#include <utility>

namespace matcha { namespace core {

template<typename T>
struct type_container
{
	using type = T;
};

} // end of namespace core
} // end of namespace matcha

#endif

