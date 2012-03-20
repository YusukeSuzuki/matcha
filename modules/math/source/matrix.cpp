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
#include "matcha/math/matrix.hpp"

namespace matcha { namespace math {

uint32_t matrix_base::rows() const noexcept
{
	return data_->header.rows;
}

uint32_t matrix_base::cols() const noexcept
{
	return data_->header.cols;
}

uint32_t matrix_base::channels() const noexcept
{
	return data_->header.channels;
}

const matrix_header& matrix_base::matrix_header() const noexcept
{
	return data_->header;
}

matrix_header& matrix_base::matrix_header() noexcept
{
	return data_->header;
}

} // end of namespace math
} // end of namespace matcha

