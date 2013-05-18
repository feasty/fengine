/**
*  window.cpp
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

#include "window.hpp"

using namespace glm;
using namespace std;

namespace fengine
{

Fengine_window::Fengine_window():
		m_fsaa_samples(2),
		m_gl_major_version(3),
		m_gl_minor_version(3),
		m_window_width(1024),
		m_window_height(768)
{

}

Fengine_window::~Fengine_window()
{

}

bool Fengine_window::initialise(string window_title)
{
	bool success = false;

	Vec4 bg_colour(0.0f, 0.0f, 0.4f, 0.0f);

	if(glfwInit())
	{
		glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
		glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Open a window and create its OpenGL context
		if( glfwOpenWindow( m_window_width, m_window_height, 0,0,0,0, 32,0, GLFW_WINDOW ) )
		{
			glewExperimental = true;

			// Initialise GLEW
			if (glewInit() == GLEW_OK)
			{
				glfwSetWindowTitle( window_title.c_str() );
				// Ensure we can capture the escape key being pressed below
				glfwEnable( GLFW_STICKY_KEYS );

				// Dark blue background
				glClearColor(bg_colour.x, bg_colour.y, bg_colour.z, bg_colour.a);

				success = true;
			}
		}


	}

	if(!success)
	{
		//Terminate what we have initialised if any part of creation was unsuccessful
		glfwTerminate();
	}

	return success;
}

}
