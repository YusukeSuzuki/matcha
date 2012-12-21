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

#include <matcha/cl/cl.hpp>

#include <iostream>

int
main(int argc, char* argv[])
{
	using namespace std;
	using namespace matcha::cl;

	try
	{
		auto platforms = platform::get();

		for(auto platform : platforms)
		{
			cout << "====" << endl;
			cout << platform.info(platform::info_name::profile) << endl;
			cout << platform.info(platform::info_name::name) << endl;
			cout << platform.info(platform::info_name::vendor) << endl;
			cout << platform.info(platform::info_name::version) << endl;
			cout << platform.info(platform::info_name::extensions) << endl;

			cout << "----" << endl;
			auto devices = platform.devices(device::type::preset);

			for(auto device : devices)
			{
				cout << device.info<device::info_name::name>() << endl;
				cout << device.info<device::info_name::vendor>() << endl;
				cout << device.info<device::info_name::version>() << endl;
				cout << device.info<device::info_name::profile>() << endl;
				cout << device.info<device::info_name::max_compute_units>() << endl;
				cout << device.info<device::info_name::max_work_item_dimentions>() << endl;
				cout << device.info<device::info_name::preferred_vector_width_char>() << endl;
				cout << device.info<device::info_name::preferred_vector_width_short>() << endl;
				cout << device.info<device::info_name::preferred_vector_width_int>() << endl;
				cout << device.info<device::info_name::preferred_vector_width_long>() << endl;
				cout << device.info<device::info_name::preferred_vector_width_float>() << endl;
				cout << device.info<device::info_name::preferred_vector_width_double>() << endl;
				cout << device.info<device::info_name::preferred_vector_width_half>() << endl;
				cout << device.info<device::info_name::native_vector_width_char>() << endl;
				cout << device.info<device::info_name::native_vector_width_short>() << endl;
				cout << device.info<device::info_name::native_vector_width_int>() << endl;
				cout << device.info<device::info_name::native_vector_width_long>() << endl;
				cout << device.info<device::info_name::native_vector_width_float>() << endl;
				cout << device.info<device::info_name::native_vector_width_double>() << endl;
				cout << device.info<device::info_name::native_vector_width_half>() << endl;
				cout << device.info<device::info_name::max_clock_frequency>() << endl;
				cout << device.info<device::info_name::address_bits>() << endl;
				cout << device.info<device::info_name::max_mem_alloc_size>() << endl;
				cout << device.info<device::info_name::image_support>() << endl;
				cout << device.info<device::info_name::max_read_image_args>() << endl;
				cout << device.info<device::info_name::max_write_image_args>() << endl;
				cout << device.info<device::info_name::image2d_max_width>() << endl;
				cout << device.info<device::info_name::image2d_max_height>() << endl;
			}
		}
	}
	catch(matcha::core::exception& e)
	{
		cout << e.where() << endl;
		throw(e);
	}

	return 0;
}

