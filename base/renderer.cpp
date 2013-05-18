/**
*  renderer.cpp
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

#include "renderer.hpp"
#include "shader.hpp"
#include "../shapes/triangle.hpp"
#include "camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace shapes;
using namespace glm;

namespace fengine
{

Fengine_renderer::Fengine_renderer()
{
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	m_projection_mat = perspective(
	    45.0f,        // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
	    4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
	    0.1f,         // Near clipping plane. Keep as big as possible, or you'll get precision issues.
	    100.0f        // Far clipping plane. Keep as little as possible.
	);
}

Fengine_renderer::~Fengine_renderer()
{

}

void Fengine_renderer::draw()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//Create our camera object
	Fengine_camera cam(
			vec3(4.0f, 3.0f, -3.0f), // Camera is at (4,3,3), in World Space
			vec3(0.0f, 0.0f, 0.0f),  // and looks at the origin
			vec3(0.0f, 1.0f, 0.0f)   // Head is up (set to 0,-1, 0 to look upside-down)
	   		);

	//TODO: Model should be the matrix associated with the asset. This is a test
	mat4 model = mat4(1.0f);

	Fengine_triangle triangle("shaders/SimpleVertexShader.vs", "shaders/SimpleFragmentShader.fs");

	mat4 mvp = m_projection_mat * cam.get_matrix() * model;

	do{
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		cam.update();

		mvp = m_projection_mat * cam.get_matrix() * model;

		triangle.draw(mvp);

		//Swap the buffers
		glfwSwapBuffers();

	}
	//Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	// Cleanup VBO
	glDeleteVertexArrays(1, &VertexArrayID);

	//Close OpenGL window and terminate GLFW
	glfwTerminate();
}

}
