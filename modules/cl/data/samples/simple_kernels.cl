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

#pragma OPENCL EXTENSION cl_khr_fp64 : enable

__kernel void set_array(
	__global float* src, float val)
{
	int gid = get_global_id(0);
	src[gid] = val;
}

__kernel void add_array(
	__global const float* src1,
	__global const float* src2,
	__global float* dst)
{
	int gid = get_global_id(0);
	dst[gid] = src1[gid] + src2[gid];
}

__kernel void set_array_double(
	__global double* src, double val)
{
	int gid = get_global_id(0);
	src[gid] = val;
}

__kernel void add_array_double(
	__global const double* src1,
	__global const double* src2,
	__global double* dst)
{
	int gid = get_global_id(0);
	dst[gid] = src1[gid] + src2[gid];
}

