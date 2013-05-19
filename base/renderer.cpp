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

}

Fengine_renderer::~Fengine_renderer()
{

}

void Fengine_renderer::draw_scene()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//Create our camera object
	Fengine_camera cam(
			vec3(0.0f, 3.0f, 20.0f),	// Camera is at this position, in World Space
			vec3(0.0f, 0.0f, 0.0f),  	// and looks at the origin
			vec3(0.0f, 1.0f, 0.0f)   	// Head is up (set to 0,-1, 0 to look upside-down)
	   		);

	Fengine_shader basic_shader("shaders/SimpleVertexShader.vs", "shaders/SimpleFragmentShader.fs");
	Fengine_shader blue_shader("shaders/blue_shader.vs", "shaders/SimpleFragmentShader.fs");

	Fengine_triangle triangle(basic_shader);

	do{
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		cam.move_camera();

		mat4 mvp = cam.get_projection_matrix() * cam.get_matrix() * triangle.get_model_matrix();

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
