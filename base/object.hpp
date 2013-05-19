/**
*  object.hpp
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

#ifndef FENGINE_OBJECT_HPP
#define FENGINE_OBJECT_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace fengine
{

class Fengine_object
{
public:
	///
	/// @brief	The constructor
	///
	Fengine_object();

	///
	/// @brief	A constructor that initialises the models position, look_at and up vectors
	///
	/// @param[in]	pos		The position to initialise to
	/// @param[in]	look_at	The location the model should face
	///	@param[in]	up		The up vector of the model
	///
	Fengine_object(glm::vec3 pos, glm::vec3 look_at, glm::vec3 up);

	///
	/// @brief	The destructor
	///
	virtual ~Fengine_object();

	///
	///	@brief	This is the base implementation of the update method.
	///
	///	This simply performs a translation on the object.
	///
	virtual void update();

	///
	///	@brief	Moved the object by the amount specified
	///
	virtual void move_by(GLfloat x, GLfloat y, GLfloat z);

	///
	///	@brief	Moved the object to the position specified
	///
	virtual void move_to(GLfloat x, GLfloat y, GLfloat z);

	///
	///	@brief	Moved the object to the position specified
	///
	virtual void move_to(glm::vec3 pos);

	///
	///	@brief	Gets the objects position vector
	///
	///	@return	Returns the objects position vector
	///
	glm::mat4 &get_matrix();

	///
	///	@brief	Sets the objects position vector
	///
	///	@param[in]	pos	The new objects position vector
	///
	void set_matrix(glm::mat4 mat);

	///
	///	@brief	Gets the objects position vector
	///
	///	@return	Returns the objects position vector
	///
	glm::vec3 &get_position();

	///
	///	@brief	Sets the objects position vector
	///
	///	@param[in]	pos	The new objects position vector
	///
	void set_position(glm::vec3 pos);

	///
	///	@brief	Gets the objects look at vector (what it's facing)
	///
	///	@return	Returns the objects look at vector
	///
	glm::vec3 &get_look_at();

	///
	///	@brief	Sets the objects look at vector (what it's facing)
	///
	///	@param[in]	pos	The new objects look at vector (what it's facing)
	///
	void set_look_at(glm::vec3 look_at);

	///
	///	@brief	Gets the objects up vector
	///
	///	@return	Returns the objects up vector
	///
	glm::vec3 &get_up();

	///
	///	@brief	Sets the objects up vector
	///
	///	@param[in]	pos	The new objects up vector
	///
	void set_up(glm::vec3 up);

protected:
	///
	///	@var	m_model_matrix
	///
	///	@brief	The object view matrix
	///
	glm::mat4	m_model_matrix;

	///
	///	@var	m_position
	///
	///	@brief	The objects current position to translate to
	///
	glm::vec3	m_position;

	///
	///	@var	m_look_at
	///
	///	@brief	The objects target position (what it's looking at)
	///
	glm::vec3	m_look_at;

	///
	///	@var	m_up
	///
	///	@brief	Defines what up is for the object
	///
	glm::vec3	m_up;

private:
};

}

#endif //FENGINE_OBJECT_HPP
