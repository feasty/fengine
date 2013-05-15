/**
*  window.hpp
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

#ifndef FENGINE_WINDOW_HPP
#define FENGINE_WINDOW_HPP

#include "types.hpp"

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

#include <string>

namespace fengine
{

class Fengine_window
{
public:
	///
	/// @brief	The constructor
	///
	Fengine_window();

	///
	/// @brief	The destructor
	///
	~Fengine_window();

	///
	/// @brief	Creates and initialises the GL window
	///
	/// @return	Returns if the operation was successful or not
	///
	bool initialise(std::string window_title);

	///
	/// @brief	Draws the scene
	///
	virtual void draw() = 0;

protected:

private:
	///
	///	@var	m_fsaa_samples
	///
	///	@brief	The number of FSAA samples
	///
	Uint8	m_fsaa_samples;

	///
	///	@var	m_gl_major_version
	///
	///	@brief	The OpenGL major version (defaults to 3)
	///
	Uint8	m_gl_major_version;

	///
	///	@var	m_gl_minor_version
	///
	///	@brief	The OpenGL minor version (defaults to 3)
	///
	Uint8	m_gl_minor_version;

	///
	///	@var	m_window_width
	///
	///	@brief	The window width (defaults to 1333)
	///
	Uint16	m_window_width;

	///
	///	@var	m_window_height
	///
	///	@brief	The window height (defaults to 720)
	///
	Uint16	m_window_height;
};

}

#endif //FENGINE_WINDOW_HPP
