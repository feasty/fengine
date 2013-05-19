/**
*  model.cpp
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

#include "model.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;

namespace fengine
{

Fengine_model::Fengine_model()
{

}

Fengine_model::Fengine_model(
		const string model_path,
		Fengine_shader &shader,
		glm::vec3 pos,
		glm::vec3 look_at,
		glm::vec3 up
		):
		Fengine_object(pos, look_at, up),
		m_shader_p(nullptr),
		m_matrix_id(0),
		m_vertex_buffer(0)
{
	m_shader_p = &shader;

	// Get a handle for our "MVP" uniform
	m_matrix_id = glGetUniformLocation(m_shader_p->get_program_id(), "MVP");

	const GLfloat *model = load_model(model_path);

	glGenBuffers(1, &m_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model), model, GL_STATIC_DRAW);
}

Fengine_model::~Fengine_model()
{
	glDeleteBuffers(1, &m_vertex_buffer);
}

void Fengine_model::update()
{
	Fengine_object::update();
}

const GLfloat *Fengine_model::load_model(string model_path)
{
	//Just returns a triangle at the moment until this method is properly implemented
	static const GLfloat tri[] = {
			-1.0f, -1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			 0.0f,  1.0f, 0.0f,
		};

	return tri;
}

}
