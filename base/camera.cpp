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

#include <iostream>

#include <GL/glfw.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;

namespace fengine
{

Fengine_camera::Fengine_camera():
		m_projection_mat(0.0f),
		m_horizontal_angle(3.14f),
		m_vertical_angle(0.0f),
		m_initial_fov(45.0f),
		m_speed(3.0f),
		m_mouse_speed(0.005f),
		m_perspective(4.0f / 3.0f)
{
	int width = 0;
	int height = 0;
	glfwGetWindowSize(&width, &height);

	//Ensure we can capture the escape key being pressed below
	glfwEnable( GLFW_STICKY_KEYS );
	glfwSetMousePos(width/2, height/2);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	m_projection_mat = perspective(
			m_initial_fov,	// The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
			m_perspective,	// Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
			0.1f,			// Near clipping plane. Keep as big as possible, or you'll get precision issues.
			100.0f			// Far clipping plane. Keep as little as possible.
			);
}

Fengine_camera::Fengine_camera(vec3 &pos, vec3 &look_at, vec3 &up):
		Fengine_object::Fengine_object(pos, look_at, up),
		m_projection_mat(0.0f),
		m_horizontal_angle(3.14f),
		m_vertical_angle(0.0f),
		m_initial_fov(45.0f),
		m_speed(3.0f),
		m_mouse_speed(0.005f),
		m_perspective(4.0f / 3.0f)
{
	Fengine_camera();
}

Fengine_camera::~Fengine_camera()
{

}

void Fengine_camera::update()
{
	Fengine_object::update();
}

// Moves the camera based on what keypresses and mouse movements have happened
void Fengine_camera::move_camera()
{
	// glfwGetTime is called only once, the first time this function is called
	static double last_time = glfwGetTime();

	// Compute time difference between current and last frame
	double current_time = glfwGetTime();
	float delta_time = float(current_time - last_time);

	// Get mouse position
	int xpos = 0;
	int ypos = 0;
	glfwGetMousePos(&xpos, &ypos);

	int width = 0;
	int height = 0;
	glfwGetWindowSize(&width, &height);

	// Reset mouse position for next frame
	glfwSetMousePos(width/2, height/2);

	// Compute new orientation
	m_horizontal_angle += m_mouse_speed * float(width/2 - xpos);
	m_vertical_angle   += m_mouse_speed * float(height/2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	vec3 direction(
			cos(m_vertical_angle) * sin(m_horizontal_angle),
			sin(m_vertical_angle),
			cos(m_vertical_angle) * cos(m_horizontal_angle)
			);

	// Right vector
	vec3 right = vec3(
			sin(m_horizontal_angle - 3.14f/2.0f),
			0,
			cos(m_horizontal_angle - 3.14f/2.0f)
			);

	// Up vector
	m_up = cross( right, direction );

	// Move forward
	if (glfwGetKey( 'W' ) == GLFW_PRESS)
	{
		m_position += direction * delta_time * m_speed;
	}
	// Move backward
	if (glfwGetKey( 'S' ) == GLFW_PRESS)
	{
		m_position -= direction * delta_time * m_speed;
	}
	// Strafe right
	if (glfwGetKey( 'D' ) == GLFW_PRESS)
	{
		m_position += right * delta_time * m_speed;
	}
	// Strafe left
	if (glfwGetKey( 'A' ) == GLFW_PRESS)
	{
		m_position -= right * delta_time * m_speed;
	}

	float fov = m_initial_fov - 5 * glfwGetMouseWheel();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	m_projection_mat = perspective(fov, m_perspective, 0.1f, 100.0f);

	//cout << "Position of cam: " <<m_position.x << " " << m_position.y << " " << m_position.z << endl;
	//cout << "Last time:" << last_time << endl;
	//cout << "Direction" << direction.x << " " << direction.y << " " << direction.z << endl;

	// Camera matrix
	m_model_matrix = lookAt(
			m_position,				//Set the cameras position
			m_position + direction,	//Looks at the same position but in the direction we calculated
			m_up
			);

	// For the next frame, the "last time" will be "now"
	last_time = current_time;
}

// Gets the projection matrix
mat4 &Fengine_camera::get_projection_matrix()
{
	return m_projection_mat;
}

}
