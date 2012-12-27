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
#ifndef MATCHA_IMAGE_IMAGE_IO_HPP__
#define MATCHA_IMAGE_IMAGE_IO_HPP__

#include <matcha/image/image.hpp>

#include <string>

namespace matcha { namespace image {

image_base load_png(const std::string& path, type_id_t type, color_space color);

template<typename T>
image<T> load_png(const std::string& path, color_space color)
{
	static_assert( is_supported_type<T>(), "T is not supported" );
	return image<T>( load_png(path, type_id<T>(), color) );
}

void save_png(const std::string& path, const image_base& img);

} // end of namespace image
} // end of namespace matcha

#endif
