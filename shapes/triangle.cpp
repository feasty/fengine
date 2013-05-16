/**
*  triangle.cpp
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

#include "triangle.hpp"
#include "../shader.hpp"

using namespace std;
using namespace fengine;

namespace shapes
{

Fengine_triangle::Fengine_triangle(const string virtex_shader, const string fragment_shader):
		m_vertexbuffer(0)
{
	m_shader_id = Fengine_shader::load_shaders( virtex_shader, fragment_shader);

	glGenBuffers(1, &m_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
}

Fengine_triangle::~Fengine_triangle()
{
	glDeleteBuffers(1, &m_vertexbuffer);
}

void Fengine_triangle::draw()
{
	//Use our shader
	glUseProgram(m_shader_id);

	//1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);
}

void Fengine_triangle::set_shader(const string virtex_shader, const string fragment_shader)
{
	m_shader_id = Fengine_shader::load_shaders( virtex_shader, fragment_shader);
}

}
