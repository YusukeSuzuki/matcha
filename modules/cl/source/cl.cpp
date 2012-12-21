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
#include "matcha/cl/cl.hpp"

namespace matcha { namespace cl {

static std::string i_erronumber_to_string(cl_int errornumber)
{
#define iTO_STRING(X) case X: return #X;

	switch(errornumber)
	{
	iTO_STRING(CL_SUCCESS)
	iTO_STRING(CL_DEVICE_NOT_FOUND)
	iTO_STRING(CL_DEVICE_NOT_AVAILABLE)
	iTO_STRING(CL_COMPILER_NOT_AVAILABLE)
	iTO_STRING(CL_MEM_OBJECT_ALLOCATION_FAILURE)
	iTO_STRING(CL_OUT_OF_RESOURCES)
	iTO_STRING(CL_OUT_OF_HOST_MEMORY)
	iTO_STRING(CL_PROFILING_INFO_NOT_AVAILABLE)
	iTO_STRING(CL_MEM_COPY_OVERLAP)
	iTO_STRING(CL_IMAGE_FORMAT_MISMATCH)
	iTO_STRING(CL_IMAGE_FORMAT_NOT_SUPPORTED)
	iTO_STRING(CL_BUILD_PROGRAM_FAILURE)
	iTO_STRING(CL_MAP_FAILURE)
	iTO_STRING(CL_MISALIGNED_SUB_BUFFER_OFFSET)
	iTO_STRING(CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST)

	iTO_STRING(CL_INVALID_VALUE)
	iTO_STRING(CL_INVALID_DEVICE_TYPE)
	iTO_STRING(CL_INVALID_PLATFORM)
	iTO_STRING(CL_INVALID_DEVICE)
	iTO_STRING(CL_INVALID_CONTEXT)
	iTO_STRING(CL_INVALID_QUEUE_PROPERTIES)
	iTO_STRING(CL_INVALID_COMMAND_QUEUE)
	iTO_STRING(CL_INVALID_HOST_PTR)
	iTO_STRING(CL_INVALID_MEM_OBJECT)
	iTO_STRING(CL_INVALID_IMAGE_FORMAT_DESCRIPTOR)
	iTO_STRING(CL_INVALID_IMAGE_SIZE)
	iTO_STRING(CL_INVALID_SAMPLER)
	iTO_STRING(CL_INVALID_BINARY)
	iTO_STRING(CL_INVALID_BUILD_OPTIONS)
	iTO_STRING(CL_INVALID_PROGRAM)
	iTO_STRING(CL_INVALID_PROGRAM_EXECUTABLE)
	iTO_STRING(CL_INVALID_KERNEL_NAME)
	iTO_STRING(CL_INVALID_KERNEL_DEFINITION)
	iTO_STRING(CL_INVALID_KERNEL)
	iTO_STRING(CL_INVALID_ARG_INDEX)
	iTO_STRING(CL_INVALID_ARG_VALUE)
	iTO_STRING(CL_INVALID_ARG_SIZE)
	iTO_STRING(CL_INVALID_KERNEL_ARGS)
	iTO_STRING(CL_INVALID_WORK_DIMENSION)
	iTO_STRING(CL_INVALID_WORK_GROUP_SIZE)
	iTO_STRING(CL_INVALID_WORK_ITEM_SIZE)
	iTO_STRING(CL_INVALID_GLOBAL_OFFSET)
	iTO_STRING(CL_INVALID_EVENT_WAIT_LIST)
	iTO_STRING(CL_INVALID_EVENT)
	iTO_STRING(CL_INVALID_OPERATION)
	iTO_STRING(CL_INVALID_GL_OBJECT)
	iTO_STRING(CL_INVALID_BUFFER_SIZE)
	iTO_STRING(CL_INVALID_MIP_LEVEL)
	iTO_STRING(CL_INVALID_GLOBAL_WORK_SIZE)
	}

	throw( cl_exception(MATCHA_EXCEPTION_WHERE.c_str(), CL_INVALID_VALUE) );
#undef iTO_STRING
}

cl_exception::cl_exception(const char* where, cl_int errornumber) :
	core::exception(where, i_erronumber_to_string(errornumber).c_str() )
{
}

cl_exception::~cl_exception() noexcept
{
}

} // end of namespace Core
} // end of namespace Matcha

