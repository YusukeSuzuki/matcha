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
	using namespace std;
	using namespace matcha::math;

	const int a = 3, b = 5, c = 3 + 5;

	matrix<int> mat1(3,3);
	fill(scalar<int, 1>({{a}}), mat1);

	matrix<int> mat2(3,3);
	fill(scalar<int, 1>({{b}}), mat2);

	matrix<int> mat3(3,3);
	add(mat1, mat2, mat3);

	for(int row = 0; row < 3; ++row)
	{
		for(int col = 0; col < 3; ++col)
		{
			if( mat3(row, col) != c )
			{
				cout << mat3(row, col) << endl;
				exit(EXIT_FAILURE);
			}
		}
	}

	return 0;
}

