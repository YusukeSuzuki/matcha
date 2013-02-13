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
#ifndef MATCHA_CORE_BITS_OPTIONAL_EXTERN_HPP__
#define MATCHA_CORE_BITS_OPTIONAL_EXTERN_HPP__

#include <matcha/core/optional.hpp>

namespace matcha { namespace core {

extern template class optional<std::string>;
extern template class optional<bool>;
extern template class optional<char>;
extern template class optional<short>;
extern template class optional<int>;
extern template class optional<long>;
extern template class optional<unsigned char>;
extern template class optional<unsigned short>;
extern template class optional<unsigned int>;
extern template class optional<unsigned long>;
extern template class optional<float>;
extern template class optional<double>;

} // end of namespace Core
} // end of namespace Matcha

#endif
