/**
*  shader.hpp
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

#include <GL/glew.h>
#include <string>

#ifndef FENGINE_SHADER_HPP
#define FENGINE_SHADER_HPP

namespace fengine
{

class Fengine_shader
{
public:

	///
	/// @brief	The contructor
	///
	Fengine_shader(const std::string &vertex_file_path, const std::string &fragment_file_path);

	///
	/// @brief	The destructor
	///
	~Fengine_shader();

	///
	///	@brief	Getter for the shaders program ID
	///
	///	@return	The program ID of the loaded shaders
	///
	GLuint get_program_id();

	///
	///	@brief	Gets a uniform location ID from the shader
	///
	///	This method is used to get a handle to the shader variable name which is passed in
	///
	///	@param[in]	var_name	The shaders variable name
	///
	///	@raturn	Returns the handle ID
	///
	GLuint get_uniform_location(std::string var_name);

protected:

private:
	///
	/// @brief	Loads a vertex and fragment shader
	///
	///	@param[in]	&vertex_file_path	The full path to the vertex shader on disk
	///	@param[in]	&vertex_file_path	The full path to the fragment shader on disk
	///
	///	@return	Returns a program ID for the shader
	///
	bool load_shaders(const std::string &vertex_file_path, const std::string &fragment_file_path);

	///
	///	@var	m_program_id
	///
	///	@brief 	The program ID of the shader after it has been loaded
	///
	GLuint	m_program_id;
};

}

#endif //FENGINE_RENDERER_HPP
