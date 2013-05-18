/**
*  camera.hpp
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

#ifndef FENGINE_CAMERA_HPP
#define FENGINE_CAMERA_HPP

#include "object.hpp"

#include <glm/glm.hpp>

namespace fengine
{

class Fengine_camera : public Fengine_object
{
public:
	///
	/// @brief	The default contructor
	///
	Fengine_camera();

	///
	/// @brief	A constructor that initialises the cameras position, look_at and up vectors
	///
	/// @param[in]	pos		The position to initialise to
	/// @param[in]	look_at	The location the model should face
	///	@param[in]	up		The up vector of the model
	///
	Fengine_camera(glm::vec3 pos, glm::vec3 look_at, glm::vec3 up);

	///
	/// @brief	The destructor
	///
	~Fengine_camera();

	///
	///	@brief	Updates the cameras position
	///
	void update();

protected:

private:

};

}

#endif //FENGINE_CAMERA_HPP
