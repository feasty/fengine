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

#include <iostream>

using namespace shapes;
using namespace glm;
using namespace std;

namespace fengine
{

Fengine_renderer::Fengine_renderer():
		m_vertext_array_id(0)
{

}

Fengine_renderer::~Fengine_renderer()
{
	if(m_vertext_array_id != 0)
	{
		// Cleanup VBO
		glDeleteVertexArrays(1, &m_vertext_array_id);
	}
}

void Fengine_renderer::draw_scene()
{
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	glGenVertexArrays(1, &m_vertext_array_id);
	glBindVertexArray(m_vertext_array_id);

	vec3 cam_pos(0.0f, 3.0f, 20.0f);	// Camera is at this position, in World Space
	vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// and looks at the origin
	vec3 cam_up(0.0f, 1.0f, 0.0f);		// Head is up (set to 0,-1, 0 to look upside-down)

	//Create our camera object
	Fengine_camera cam(cam_pos,	cam_look_at, cam_up);

	//Fengine_shader basic_shader("shaders/simple.vs", "shaders/simple.fs");
	//Fengine_shader texture_shader("shaders/transform.vs", "shaders/texture.fs");
	Fengine_shader lighting_shader("shaders/simple_light.vs", "shaders/simple_light.fs");

	//Cube initialisation values
	vec3 cube1_pos(0.0f, 0.0f, 0.0f);
	vec3 cube1_look_at(0.0f, 0.0f, 1.0f);
	vec3 cube1_up(0.0f, 1.0f, 0.0f);
	Fengine_model cube1("models/shapes/cube/cube.obj", "models/shapes/cube/cube.dds", lighting_shader, cube1_pos, cube1_look_at, cube1_up);

	vec3 cube2_pos(30.0f, 0.0f, 0.0f);
	vec3 cube2_look_at(0.0f, 0.0f, 1.0f);
	vec3 cube2_up(0.0f, 1.0f, 0.0f);
	Fengine_model cube2("models/shapes/cube/cube.obj", "models/shapes/cube/cube.dds", lighting_shader, cube2_pos, cube2_look_at, cube2_up);

	vec3 monkey1_pos(15.0f, 0.0f, 0.0f);
	vec3 monkey1_look_at(0.0f, 0.0f, 1.0f);
	vec3 monkey1_up(0.0f, 1.0f, 0.0f);
	Fengine_model monkey1("models/test/monkey/monkey.obj", "models/test/monkey/monkey.dds", lighting_shader, monkey1_pos, monkey1_look_at, monkey1_up);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(lighting_shader.get_program_id());
	GLuint light_id = lighting_shader.get_uniform_location("LightPosition_worldspace");

	// Get a handle for our "MVP" uniform
	GLuint mvp_id = lighting_shader.get_uniform_location("MVP");
	GLuint view_mat_id = lighting_shader.get_uniform_location("V");
	GLuint model_mat_id = lighting_shader.get_uniform_location("M");

	vec3 light_pos = vec3(5.0f, 5.0f, 5.0f);

	//Our model, view, projection matrix
	mat4 mvp(1.0f);

	do{
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glUseProgram(lighting_shader.get_program_id());

		light_pos.z -= 0.1;

		glUniform3f(light_id, light_pos.x, light_pos.y, light_pos.z);

		cam.move_camera();

		mvp = cam.get_projection_matrix() * cam.get_matrix() * cube1.get_matrix();

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(model_mat_id, 1, GL_FALSE, &cube1.get_matrix()[0][0]);
		glUniformMatrix4fv(view_mat_id, 1, GL_FALSE, &cam.get_matrix()[0][0]);

		cube1.draw(mvp);

		mvp = cam.get_projection_matrix() * cam.get_matrix() * monkey1.get_matrix();

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(model_mat_id, 1, GL_FALSE, &monkey1.get_matrix()[0][0]);
		glUniformMatrix4fv(view_mat_id, 1, GL_FALSE, &cam.get_matrix()[0][0]);

		monkey1.draw(mvp);

		mvp = cam.get_projection_matrix() * cam.get_matrix() * cube2.get_matrix();

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(model_mat_id, 1, GL_FALSE, &cube2.get_matrix()[0][0]);
		glUniformMatrix4fv(view_mat_id, 1, GL_FALSE, &cam.get_matrix()[0][0]);

		cube2.draw(mvp);

		//Swap the buffers
		glfwSwapBuffers();

	}
	//Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	//Close OpenGL window and terminate GLFW
	glfwTerminate();
}

}
