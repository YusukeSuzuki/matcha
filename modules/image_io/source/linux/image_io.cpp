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
#include "matcha/image/image_io.hpp"

#include <matcha/core/exception.hpp>

#include <libpng/png.h>

#include <cassert>
#include <cerrno>
#include <cstdio>

extern "C"
{

static void user_error_fn(png_structp png_ptr, png_const_charp error_msg)
{
}

static void user_warning_fn(png_structp png_ptr, png_const_charp warning_msg)
{
}

static void* user_error_ptr = nullptr;

}

namespace matcha { namespace image {

template<typename... params>
bool is_in(color_space color, params... parameters)
{
	return true;
}

image_base
load_png(const std::string& path, type_id_t type, color_space color)
{
	FILE* file = fopen(path.c_str(), "rb");

	if(!file)
	{
		throw( core::system_exception(MATCHA_EXCEPTION_WHERE.c_str(), errno) );
	}

	const std::size_t header_size = 8;

	{
		png_byte header[header_size] = {};
		auto ret = fread(header, sizeof(png_byte), header_size, file);
		
		if( png_sig_cmp(header, 0, header_size) || ret != header_size )
		{
			throw( core::exception(MATCHA_EXCEPTION_WHERE.c_str(), "file is not png") );
		}
	}

	{
		png_structp png_ptr = png_create_read_struct(
			PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

		if( !png_ptr )
		{
			fclose(file);
			throw( core::exception(MATCHA_EXCEPTION_WHERE.c_str(), "file is not png") );
		}

		png_infop info_ptr = png_create_info_struct(png_ptr);

		if( !info_ptr )
		{
			fclose(file);
			png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
			throw( core::exception(MATCHA_EXCEPTION_WHERE.c_str(), "file is not png") );
		}

		png_init_io(png_ptr, file);
		png_set_sig_bytes(png_ptr, header_size);

		auto transform = PNG_TRANSFORM_IDENTITY;

		png_read_png(png_ptr, info_ptr,
			PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_BGR | PNG_TRANSFORM_STRIP_ALPHA,
			nullptr);

		auto width  = png_get_image_width(png_ptr, info_ptr);
		auto height = png_get_image_height(png_ptr, info_ptr);
		auto channels = png_get_channels(png_ptr, info_ptr);
	}

	image_base result( create_matrix_header(1,1, type, 1) );
	return result;
}

} // end of namespace image
} // end of namespace matcha

