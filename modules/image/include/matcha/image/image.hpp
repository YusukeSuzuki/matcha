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
#ifndef MATCHA_IMAGE_HPP__
#define MATCHA_IMAGE_HPP__

#include <matcha/math/matrix.hpp>

namespace matcha { namespace image {

using namespace math;
using image_base = matrix_base;
template<typename T> using image = matrix<T>;

struct size
{
	int width;
	int height;

	size(const matrix_base& image);
};

struct rect
{
	int x;
	int y;
	int width;
	int height;
};

enum class color_space
{
	grayscale,
	rgb,
	rgba,
	bgr,
	bgra
};

template<typename T>
image<T> make_image(int width, int height, int channels);

void make_integral(const image_base& src, image_base& dst);

} // end of namespace image
} // end of namespace matcha

#include <matcha/image/image.templates.hpp>

#endif
