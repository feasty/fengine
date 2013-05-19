/**
*  object.cpp
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

#include "object.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

namespace fengine
{

Fengine_object::Fengine_object():
				m_model_matrix(1.0f),
				m_position(0.0f, 0.0f, 0.0f),
				m_look_at(0.0f, 0.0f, 0.0f),
				m_up(0.0f, 1.0f, 0.0f)
{
	//Perform the translation on the objects matrix
	m_model_matrix = lookAt(m_position, m_look_at, m_up);
}

Fengine_object::Fengine_object(glm::vec3 pos, glm::vec3 look_at, glm::vec3 up):
	m_model_matrix(1.0f),
	m_position(pos),
	m_look_at(look_at),
	m_up(up)
{
	m_model_matrix = lookAt(m_position, m_look_at, m_up);
}

Fengine_object::~Fengine_object()
{

}

void Fengine_object::update()
{
	//Perform the translation on the objects matrix
	m_model_matrix = lookAt(m_position, m_look_at, m_up);
}

// Moved the object by the amount specified
void Fengine_object::move_by(GLfloat x, GLfloat y, GLfloat z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
}

// Moved the object to the position specified
void Fengine_object::move_to(GLfloat x, GLfloat y, GLfloat z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

// Moved the object to the position specified
void Fengine_object::move_to(glm::vec3 pos)
{
	m_position = pos;
}

// Gets the objects position vector
glm::mat4 &Fengine_object::get_matrix()
{
	return m_model_matrix;
}

// Sets the objects position vector
void Fengine_object::set_matrix(glm::mat4 mat)
{
	m_model_matrix = mat;
}

// Gets the objects position vector
vec3 &Fengine_object::get_position()
{
	return m_position;
}

// Sets the objects position vector
void Fengine_object::set_position(vec3 pos)
{
	m_position = pos;
}

// Gets the objects look at vector (what it's facing)
vec3 &Fengine_object::get_look_at()
{
	return m_look_at;
}

// Sets the objects look at vector (what it's facing)
void Fengine_object::set_look_at(vec3 look_at)
{
	m_look_at = look_at;
}

// Gets the objects up vector
vec3 &Fengine_object::get_up()
{
	return m_up;
}

// Sets the objects up vector
void Fengine_object::set_up(vec3 up)
{
	m_up = up;
}

}
