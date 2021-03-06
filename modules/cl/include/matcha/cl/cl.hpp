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
#ifndef __MATCAH_CL_H_
#define __MATCAH_CL_H_

#include <matcha/core/exception.hpp>
#include <matcha/core/type.hpp>

#include <CL/cl.h>

#include <functional>
#include <memory>
#include <set>
#include <vector>

namespace matcha { namespace cl {

class device;

class cl_exception : public core::exception
{
public:
	cl_exception(const char* where, cl_int errornumber);

	virtual ~cl_exception() noexcept;
	//virtual const char* where() const noexcept;
	//virtual const char* what() const noexcept;
};

class device
{
public:
	enum class type
	{
		preset,
		cpu,
		gpu,
		accelerator,
	};

	enum class info_name
	{
		type,
		vendor_id,
		max_compute_units,
		max_work_item_dimentions,
		max_work_item_sizes,
		max_work_group_size,
		preferred_vector_width_char,
		preferred_vector_width_short,
		preferred_vector_width_int,
		preferred_vector_width_long,
		preferred_vector_width_float,
		preferred_vector_width_double,
		preferred_vector_width_half,
		native_vector_width_char,
		native_vector_width_short,
		native_vector_width_int,
		native_vector_width_long,
		native_vector_width_float,
		native_vector_width_double,
		native_vector_width_half,
		max_clock_frequency,
		address_bits,
		max_mem_alloc_size,
		image_support,
		max_read_image_args,
		max_write_image_args,
		image2d_max_width,
		image2d_max_height,
		image3d_max_width,
		image3d_max_height,
		image3d_max_depth,
		max_samplers,
		max_parameter_size,
		mem_base_addr_align,
		min_data_type_align_size,
		single_fp_config,
		global_mem_cache_type,
		global_mem_cacheline_size,
		global_mem_cache_size,
		global_mem_size,
		max_constant_buffer_size,
		max_constant_args,
		local_mem_type,
		local_mem_size,
		error_correction_support,
		host_unified_memory,
		profiling_timer_resolution,
		endian_little,
		available,
		compiler_available,
		execution_capabilities,
		queue_properties,
		platform,
		name,
		vendor,
		driver_version,
		profile,
		version,
		opencl_c_version,
		extensions,
	};

	enum class fp_config
	{
		denorm,
		inf_nan,
		round_to_nearest,
		round_to_zero,
		round_to_inf,
		fma,
		soft_float,
	};

	enum class mem_cache_type
	{
		none,
		read_only,
		read_write,
	};

	enum class local_mem_type
	{
		local,
		global,
	};

	enum class exec_capability
	{
		kernel,
		native_kernel,
	};

	template<info_name P> struct info_type {};

	template<info_name P, typename T = typename info_type<P>::type>
	auto info() const -> T {}

	~device() noexcept;

private:
	class implementation;
	std::shared_ptr<implementation> implementation_;
	
	std::shared_ptr<typename device::implementation> implementation();
	const std::shared_ptr<typename device::implementation> implementation() const;

	device(std::shared_ptr<typename device::implementation> implementation_);

	friend class platform;
	friend class context;
	friend class program;
	friend class command_queue;
};

class platform
{
public:
	enum class info_name
	{
		profile,
		version,
		name,
		vendor,
		extensions,
	};

	static std::vector<platform> get();

	~platform() noexcept;

	std::string info(info_name param);

	std::vector<device> devices(device::type t);

private:
	class implementation;
	std::shared_ptr<implementation> implementation_;
	platform(std::shared_ptr<implementation> a_implementation);

	friend class device;
};

class context;

class buffer
{
public:
	enum class flag
	{
		read_write,
		write_only,
		read_only,
		use_host_ptr,
		alloc_host_ptr,
		copy_host_ptr,
	};

	buffer(context& context, const std::set<buffer::flag>& flags, size_t size);
	buffer(context& context, const std::set<buffer::flag>& flags,
		size_t size, void* host_ptr);

private:
	class implementation;
	std::shared_ptr<implementation> implementation_;
	std::shared_ptr<implementation> implementation();
	const std::shared_ptr<typename buffer::implementation> implementation() const;

	friend class kernel;
	friend class command_queue;
};

class event
{
public:
private:
	class implementation;
	event(std::shared_ptr<implementation> implementation);
	std::shared_ptr<implementation> implementation_;
	std::shared_ptr<typename event::implementation> implementation();
	const std::shared_ptr<typename event::implementation> implementation() const;

	friend class command_queue;
};

struct work_item
{
	size_t offset;
	size_t size;
};

class kernel;

class command_queue
{
public:
	enum class property
	{
		out_of_order_exec_mode_enable,
		profiling_enable,
	};

	command_queue(
		context& context, device& device, const std::set<property>& properties);

	// test version
	event enqueue_nd_range(kernel& kernel, size_t worksize);

	event enqueue_task(kernel& kernel);

	event enqueue_read(
		buffer& buffer, bool block_read, size_t offset, size_t size_in_bytes,
		void* out_ptr, const std::vector<event>& wait_list);

	void wait_for(const std::vector<event>& wait_list);

private:
	command_queue();

	class implementation;
	std::shared_ptr<implementation> implementation_;

	friend class context;
};

class program;

class kernel
{
public:
	kernel(program& program, const std::string& name);
	kernel(const kernel& rhs);
	kernel& operator=(const kernel& rhs);

	static std::vector<kernel> create_kernels_in_program(program& program);

	template<typename T, typename ... R>
	void enqueue(T& t, R ... r)
	{
		set_arguments(t, r ...);
	}

	void enqueue_nd_range();
	void enqueue_task();
	void enqueue_native_kernel();

	template<typename T>
	void set_arguments(unsigned int index, T& t)
	{
		set_argument(index, t);
	}

	template<typename T, typename ... R>
	void set_arguments(unsigned int index, T& t, R& ... r)
	{
		set_argument(index, t);
		set_arguments(index + 1, r ...);
	}

	template<typename T, typename ... R>
	void set_arguments(T& t, R& ... r)
	{
		set_arguments(0, t, r ...);
	}

	kernel& set_argument(unsigned int index, buffer& buffer);
	kernel& set_argument(unsigned int index, size_t size, void* ptr);

	template<typename T>
	kernel& set_argument(unsigned int index, const T& d)
	{
		set_argument(index, sizeof(T), &d);
		return *this;
	}

	enum class info_name
	{
		function_name,
		num_args,
		reference_count,
		context,
		program,
	};

	enum class workgroup_info_name
	{
		size,
		compile_size,
		local_mem_size,
		preferred_size_multiple,
		private_mem_size,
	};

private:
	class implementation;
	std::shared_ptr<implementation> implementation_;
	kernel(const std::shared_ptr<implementation>& ptr);

	friend class command_queue;
};

class context;

class program
{
public:
	enum class info_name
	{
		reference_count,
		context,
		num_devices,
		devices,
		source,
		binary_sizes,
		binaries,
	};

	enum class build_info_name
	{
		status,
		options,
		log,
	};

	program(context& context, const std::vector<std::string>& sources);
	program(const program& program);
	program& operator =(const program& rhs);
	virtual ~program() noexcept;

	program& build(const std::vector<device>& devices);

	kernel create_kernel(const std::string& name);
	std::vector<kernel> create_kernels(const std::vector<std::string>& names);
	std::vector<kernel> create_all_kernels();
	unsigned int num_kernels() const;

	template<info_name P> struct info_type {};

	template<info_name P, typename T = typename info_type<P>::type>
	auto info() const -> T{}

	template<build_info_name P> struct build_info_type {};

	template<build_info_name P, typename T = typename build_info_type<P>::type>
	auto build_info() const -> T{}

private:
	program();
	class implementation;
	std::shared_ptr<implementation> implementation_;
	std::shared_ptr<implementation> implementation();
	const std::shared_ptr<typename program::implementation> implementation() const;

	friend class kernel;
};

class context
{
public:
	using callback_function = 
		std::function<void (const std::string& errorinfo, const void* private_info,
			size_t cb) >;

	context(const std::vector<device>& devices, callback_function callback);
	context(const std::vector<device>& devices);
	context(device::type type, callback_function callback);
	context(device::type type);

	/// queue control
	command_queue create_queue(const device& device) const;

	command_queue& hold_queue(const std::string& name, command_queue& queue);
	command_queue& queue(const std::string& name);
	const command_queue& queue(const std::string& name) const;

	/// buffer control
	buffer& create_buffer(
		const std::set<buffer::flag>& flags, size_t size, void* host_ptr);

	/// program control
	program create_program(const std::vector<std::string>& sources);

	/// TBI
	void info();

private:
	context();

	class implementation;
	std::shared_ptr<implementation> implementation_;
	std::shared_ptr<implementation> implementation();
	const std::shared_ptr<typename context::implementation> implementation() const;

	friend class program;
	friend class buffer;
	friend class command_queue;
};

class memory
{
};

class image
{
};

class image2d
{
};

class image3d
{
};

class sampler
{
};

class user_event
{
};

class nd_range
{
};

} // end of namespace Core
} // end of namespace Matcha

#include <matcha/cl/bits/device_template.hpp>
#include <matcha/cl/bits/program_template.hpp>

#endif
