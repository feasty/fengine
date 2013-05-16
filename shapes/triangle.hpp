/**
*  triangle.hpp
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

#ifndef FENGINE_TRIANGLE_HPP
#define FENGINE_TRIANGLE_HPP

#include <string>

#include <GL/glew.h>

namespace shapes
{

///
/// @var	triangle
///
///	@brief	Triangle vertices coordinates
///
static const GLfloat triangle[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

class Fengine_triangle
{
public:
	///
	/// @brief	The contructor
	///
	Fengine_triangle(std::string virtex_shader, std::string fragment_shader);

	///
	/// @brief	The destructor
	///
	~Fengine_triangle();

	///
	/// @brief	Draws the triangle
	///
	void draw();

	///
	/// @brief	Sets the shader to use for rendering
	///
	void set_shader(const std::string virtex_shader, const std::string fragment_shader);

protected:

private:
	///
	///	@var m_shader_id
	///
	///	@brief	The id of the shader program
	///
	GLuint	m_shader_id;

	///
	/// @var	m_vertexbuffer
	///
	///	@brief	The vertex buffer for our triangle
	///
	GLuint	m_vertexbuffer;
};

}

#endif //FENGINE_TRIANGLE_HPP
