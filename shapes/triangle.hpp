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

#include "../base/shader.hpp"

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

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
	Fengine_triangle(fengine::Fengine_shader &shader);

	///
	/// @brief	The destructor
	///
	~Fengine_triangle();

	///
	/// @brief	Draws the triangle
	///
	void draw(glm::mat4 &mvp);

	///
	/// @brief	Sets the shader to use for rendering
	///
	void set_shader(fengine::Fengine_shader &shader);

	///
	///	@brief	Getter for the models matrix
	///
	///	@return	Returns the models matrix
	///
	glm::mat4 get_model_matrix();

protected:

private:
	///
	///	@var	m_model_matrix
	///
	///	@brief	The object view matrix
	///
	glm::mat4	m_model_matrix;

	///
	///	@var m_shader
	///
	///	@brief	A pointer to the shader to use on the object
	///
	fengine::Fengine_shader	*m_shader_p;

	///
	///	@var m_matrix_id
	///
	///	@brief	Gets a handle to the shaders mvp uniform
	///
	GLuint m_matrix_id;

	///
	/// @var	m_vertexbuffer
	///
	///	@brief	The vertex buffer for our triangle
	///
	GLuint	m_vertexbuffer;
};

}

#endif //FENGINE_TRIANGLE_HPP
