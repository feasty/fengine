/**
*  model.hpp
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

#ifndef FENGINE_MODEL_HPP
#define FENGINE_MODEL_HPP

#include "object.hpp"
#include "shader.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace fengine
{

class Fengine_model : public Fengine_object
{
public:
	///
	/// @brief	The default contructor
	///
	Fengine_model();

	///
	/// @brief	A constructor that initialises the models position, look_at and up vectors
	///
	///	@param[in]	&model_path			The full path to the model on disk
	///	@param[in]	&shader				The shader to use with the model
	/// @param[in]	pos					The position to initialise to
	/// @param[in]	look_at				The location the model should face
	///	@param[in]	up					The up vector of the model
	///
	Fengine_model(
			const std::string &model_path,
			Fengine_shader &shader,
			glm::vec3 &pos,
			glm::vec3 &look_at,
			glm::vec3 &up
			);

	///
	/// @brief	The destructor
	///
	virtual ~Fengine_model();

	///
	///	@brief	Implementation of the object classes update method
	///
	void update();

	///
	///	@brief	This is a pure virtual which will draw the model. This is a pure virtual which must be
	///			implemented by each models base class
	///
	void draw(glm::mat4 &mvp);

	///
	///	@brief	Getter for the models matrix
	///
	///	@return	Returns the models matrix
	///
	glm::mat4 get_model_matrix();

protected:
	///
	///	@var m_shader
	///
	///	@brief	The shader to be used on the model
	///
	///	This pointer does not take ownership of the shader.
	///
	Fengine_shader	*m_shader_p;

	///
	///	@var m_matrix_id
	///
	///	@brief	Gets a handle to the shaders mvp uniform
	///
	GLuint m_matrix_id;

	///
	/// @var	m_vertex_buffer
	///
	///	@brief	The vertex buffer for our model
	///
	GLuint	m_vertex_buffer;

private:
	///
	///	@brief	Loads a model from disk into a vertex buffer
	///
	///	@param[in]	model_path		The path on disk to the model which is to be loaded
	///	@param[out]	&out_vertices	The return virtices
	///	@param[out]	&out_uvs		The return UVs
	///	@param[out]	&out_normals	The return normals
	///
	///	@return	Returns if the load was successful
	///
	bool load_model(const std::string model_path);

	///
	///	@var	m_vertices
	///
	///	@brief	The models vertices which are initialised in load_model
	///
	std::vector<glm::vec3> m_vertices;

	///
	///	@var	m_uvs
	///
	///	@brief	The models UVs which are initialised in load_model
	///
	std::vector<glm::vec2> m_uvs;

	///
	///	@var	m_normals
	///
	///	@brief	The models normals which are initialised in load_model
	///
	std::vector<glm::vec3> m_normals;

};

}

#endif //FENGINE_MODEL_HPP
