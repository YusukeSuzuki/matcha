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

#define USE_LIB true

#define BOOST_TEST_MODULE matrix_operations

#if USE_LIB
	#define BOOST_TEST_DYN_LINK
	#include <boost/test/unit_test.hpp>
#else
	#define BOOST_TEST_NO_LIB
	#define BOOST_TEST_MAIN 1
	#include <boost/test/included/unit_test.hpp>
#endif

#include <matcha/math/matrix.hpp>
#include <matcha/math/types.hpp>
#include <matcha/math/scalar.hpp>
#include <matcha/math/matrix_operations.hpp>

#include <cstdlib>
#include <iostream>

BOOST_AUTO_TEST_CASE( fill_0 )
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
			BOOST_CHECK_EQUAL( mat(i,j), 3 );
		}
	}
}

BOOST_AUTO_TEST_CASE( fill_1 )
{
	using namespace std;
	using namespace matcha::math;

	matrix<double> mat(3,3);

	scalar<double, 1> scalar = {{1.25}};
	fill(scalar, mat);

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			BOOST_CHECK_EQUAL( mat(i,j), 1.25 );
		}
	}
}

BOOST_AUTO_TEST_CASE( identity_0 )
{
	using namespace std;
	using namespace matcha::math;

	matrix<double> mat( identity<double>(3,3) );

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			cout << mat(i,j) << endl;
			BOOST_CHECK_EQUAL( mat(i,j), i == j ?  double(1) : double(0) );
		}
	}
}

