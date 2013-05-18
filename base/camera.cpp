/**
*  camera.cpp
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

#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

namespace fengine
{

Fengine_camera::Fengine_camera()
{

}

Fengine_camera::Fengine_camera(glm::vec3 pos, glm::vec3 look_at, glm::vec3 up)
{

}

Fengine_camera::~Fengine_camera()
{

}

void Fengine_camera::update()
{
	//Perform the translation on the objects matrix
	m_model_matrix = lookAt(m_position, m_look_at, m_up);
}

}
