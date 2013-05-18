/**
*  matrix.hpp
*
*  Copyright 2012  <feasty@digitaldrugs.co.uk>
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
*  MA 02110-1301, USA.
*
**/

#ifndef FENGINE_MATRIX_HPP
#define FENGINE_MATRIX_HPP

#include <glm/glm.hpp>

namespace fengmath
{

class Fengine_matrix
{
public:
	///
	/// @brief	The contructor
	///
	Fengine_matrix();

	///
	/// @brief	The destructor
	///
	~Fengine_matrix();

	///
	///	@brief	Performs a transformation on the matrix
	///
	///	@param[in]	vec	The vector to transform with
	///
	void transform(glm::vec4 vec);

protected:

private:

};

}

#endif //FENGINE_MATRIX_HPP
