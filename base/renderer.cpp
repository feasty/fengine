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
#include "model.hpp"

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
	//glDeleteProgram(programID);
}

void Fengine_renderer::draw_scene()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	vec3 cam_pos(0.0f, 3.0f, 20.0f);	// Camera is at this position, in World Space
	vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// and looks at the origin
	vec3 cam_up(0.0f, 1.0f, 0.0f);		// Head is up (set to 0,-1, 0 to look upside-down)

	//Create our camera object
	Fengine_camera cam(cam_pos,	cam_look_at, cam_up);

	Fengine_shader basic_shader("shaders/SimpleVertexShader.vs", "shaders/SimpleFragmentShader.fs");
	Fengine_shader blue_shader("shaders/SimpleVertexShader.vs", "shaders/blue_shader.fs");

	Fengine_triangle triangle(basic_shader);

	//Cube initialisation values
	vec3 cube1_pos(0.0f, 0.0f, 0.0f);
	vec3 cube1_look_at(0.0f, 0.0f, 1.0f);
	vec3 cube1_up(0.0f, 1.0f, 0.0f);
	Fengine_model cube1("models/shapes/cube/cube.obj", basic_shader, cube1_pos, cube1_look_at, cube1_up);

	vec3 cube2_pos(30.0f, 0.0f, 0.0f);
	vec3 cube2_look_at(0.0f, 0.0f, 1.0f);
	vec3 cube2_up(0.0f, 1.0f, 0.0f);
	Fengine_model cube2("models/shapes/cube/cube.obj", basic_shader, cube2_pos, cube2_look_at, cube2_up);

	vec3 monkey1_pos(15.0f, 0.0f, 0.0f);
	vec3 monkey1_look_at(0.0f, 0.0f, 1.0f);
	vec3 monkey1_up(0.0f, 1.0f, 0.0f);
	Fengine_model monkey1("models/test/monkey/monkey.obj", basic_shader, monkey1_pos, monkey1_look_at, monkey1_up);

	//Our model, view, projection matrix
	mat4 mvp(1.0f);

	do{
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		cam.move_camera();

		mvp = cam.get_projection_matrix() * cam.get_matrix() * cube1.get_model_matrix();

		cube1.draw(mvp);

		mvp = cam.get_projection_matrix() * cam.get_matrix() * cube2.get_model_matrix();

		cube2.draw(mvp);

		mvp = cam.get_projection_matrix() * cam.get_matrix() * monkey1.get_model_matrix();

		monkey1.draw(mvp);

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
