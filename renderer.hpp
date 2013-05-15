/**
*  renderer.hpp
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

#ifndef FENGINE_RENDERER_HPP
#define FENGINE_RENDERER_HPP

namespace fengine
{

class Fengine_renderer : public Fengine_window
{
public:

	///
	/// @brief	The contructor
	///
	Fengine_renderer();

	///
	/// @brief	The destructor
	///
	~Fengine_renderer();

	///
	/// @brief	Draws the scene
	///
	void draw();

protected:

private:

};

}

#endif //FENGINE_RENDERER_HPP
