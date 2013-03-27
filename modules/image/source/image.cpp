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
#include "matcha/image/image.hpp"

namespace matcha { namespace image {

size::size(const matrix_base& image) :
	width(image.cols()),
	height(image.rows())
{
}

template image<uint8_t> make_image(int width, int height, int channels);
template image<uint16_t> make_image(int width, int height, int channels);
template image<uint32_t> make_image(int width, int height, int channels);
template image<uint64_t> make_image(int width, int height, int channels);
template image<int8_t> make_image(int width, int height, int channels);
template image<int16_t> make_image(int width, int height, int channels);
template image<int32_t> make_image(int width, int height, int channels);
template image<int64_t> make_image(int width, int height, int channels);
template image<float> make_image(int width, int height, int channels);
template image<double> make_image(int width, int height, int channels);

} // end of namespace image
} // end of namespace matcha

