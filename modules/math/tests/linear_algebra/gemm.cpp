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

#include <matcha/math/matrix.hpp>
#include <matcha/math/types.hpp>
#include <matcha/math/scalar.hpp>
#include <matcha/math/matrix_operations.hpp>
#include <matcha/math/linear_algebra.hpp>

#include <cstdlib>
#include <iostream>

int
main(int argc, char* argv[])
{
	/**
	 * @todo write more detailed test
	 */
	using namespace std;
	using namespace matcha::math;

	double a = 2;

	matrix<double> mat1(3,3);
	fill(scalar<double, 1>({{a}}), mat1);

	matrix<double> mat2(3,3);
	fill(scalar<double, 1>({{0}}), mat2);

	double b = 2;

	mat2(0,0) = b;
	mat2(1,1) = b;
	mat2(2,2) = b;

	for(int row = 0; row < 3; ++row)
	{
		for(int col = 0; col < 3; ++col) cout << mat1(row, col) << ", ";
		cout << endl;
	}

	for(int row = 0; row < 3; ++row)
	{
		for(int col = 0; col < 3; ++col) cout << mat2(row, col) << ", ";
		cout << endl;
	}

	matrix<double> mat3(3,3);
	fill(scalar<double, 1>({{0}}), mat3);

	gemm(mat1, transpose_option::normal,  mat2, transpose_option::normal,
		scalar<double, 1>({{1}}), scalar<double, 1>({{1}}), mat3);

	for(int row = 0; row < 3; ++row)
	{
		for(int col = 0; col < 3; ++col)
		{
			if( mat3(row, col) != (a * b * 3) )
			{
				cout << mat3(row, col) << endl;
				exit(EXIT_FAILURE);
			}
		}
	}

	return 0;
}

