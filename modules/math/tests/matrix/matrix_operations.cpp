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

#include <cstdlib>
#include <iostream>

int
main(int argc, char* argv[])
{
	using namespace std;
	using namespace matcha::math;

	matrix<double> mat(3,3);

	scalar<double, 1> scalar = {{3}};
	fill(scalar, mat);

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			if(mat(i,j) != 3)
			{
				exit(EXIT_FAILURE);
			}
		}
	}

	scalar.var[0] = 1.25;
	fill(scalar, mat);

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			if(mat(i,j) != 1.25)
			{
				exit(EXIT_FAILURE);
			}
		}
	}

	matrix<double> mat2( identity<double>(3,3) );

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			cout << mat2(i,j) << endl;

			if( (i == j) ? (mat2(i,j) != double(1)) : (mat2(i,j) != double(0)) )
			{
				exit(EXIT_FAILURE);
			}
		}
	}

	return 0;
}

