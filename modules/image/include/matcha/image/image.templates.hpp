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
#ifndef MATCHA_IMAGE_IMAGE_TEMPLATES_HPP__
#define MATCHA_IMAGE_IMAGE_TEMPLATES_HPP__

#include <matcha/image/image.hpp>

namespace matcha { namespace image {

template<typename T>
image<T> make_image(int width, int height, int channels)
{
	return image<T>(height, width, channels);
}

extern template image<uint8_t> make_image(int width, int height, int channels);
extern template image<uint16_t> make_image(int width, int height, int channels);

} // end of namespace image
} // end of namespace matcha

#endif
