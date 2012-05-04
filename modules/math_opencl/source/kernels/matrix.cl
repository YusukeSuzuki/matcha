
#pragma OPENCL_EXTENSION cl_khr_fp64 : enable

__kernel void array_set(__global float* src, float val)
{
	src[get_global_id(0)] = val;
}

_kernel void array_add(
	__global const float* src1, __global const float* src2, __global float* dst)
{
	int gid = get_global_id(0);
	dst[gid] = src1[gid] + src2[gid];
}

__kernel void array_set(__global double* src, double val)
{
	src[get_global_id(0)] = val;
}

_kernel void array_add(
	__global const double* src1, __global const double* src2, __global double* dst)
{
	int gid = get_global_id(0);
	dst[gid] = src1[gid] + src2[gid];
}

