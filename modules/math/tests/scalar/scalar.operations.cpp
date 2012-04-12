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

#define BOOST_TEST_MODULE scalar_operation

#if USE_LIB
	#define BOOST_TEST_DYN_LINK
	#include <boost/test/unit_test.hpp>
#else
	#define BOOST_TEST_NO_LIB
	#define BOOST_TEST_MAIN 1
	#include <boost/test/included/unit_test.hpp>
#endif

#include <matcha/math/scalar.hpp>

#include <cstdlib>
#include <iostream>

BOOST_AUTO_TEST_CASE( add_0 )
{
	using namespace matcha;

	math::scalar<double, 2> a;
	a[0] = 1;
	a[1] = 2;
	math::scalar<double, 2> b;
	b[0] = 3;
	b[1] = 4;

	auto c = add(a, b);
	BOOST_CHECK_EQUAL( c[0], 4 );
	BOOST_CHECK_EQUAL( c[1], 6 );
}

