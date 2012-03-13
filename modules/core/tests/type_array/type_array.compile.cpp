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

#include <matcha/core/type_array.hpp>

#include <iostream>
#include <typeinfo>

struct test
{
	int a;
	int b;
};

namespace matcha { namespace core {

matcha_type_array_declare(test, int, int);
matcha_type_array_function_definition(test, 0, a);
matcha_type_array_function_definition(test, 1, b);

} }

int
main(int argc, char* argv[])
{
	using namespace std;
	using namespace matcha::core;

	test t1 = {1,2};
	test t2 = {3,4};

	cout << get<0>(t1) << endl;
	cout << get<1>(t1) << endl;
	cout << get<0>(t2) << endl;
	cout << get<1>(t2) << endl;

	cout << typeid( type_array<test>::get_type<0>::type ).name() << endl;

	cout << is_equal(t1, t2) << endl;

	return 0;
}

