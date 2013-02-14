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
#include "matcha/core/optional.hpp"

#include <string>

namespace matcha { namespace core {

template class optional<bool>;
template class optional<char>;
template class optional<short>;
template class optional<int>;
template class optional<long>;
template class optional<unsigned char>;
template class optional<unsigned short>;
template class optional<unsigned int>;
template class optional<unsigned long>;
template class optional<float>;
template class optional<double>;
template class optional<std::string>;

} // end of namespace Core
} // end of namespace Matcha

