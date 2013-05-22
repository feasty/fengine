/**
*  shader.cpp
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

#include "shader.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <string.h>

#include <GL/glew.h>

using namespace std;

namespace fengine
{

Fengine_shader::Fengine_shader(const string &vertex_file_path, const string &fragment_file_path):
		m_program_id(0)
{
	load_shaders(vertex_file_path, fragment_file_path);
}

Fengine_shader::~Fengine_shader()
{
	glDeleteProgram(m_program_id);
}

GLuint Fengine_shader::get_program_id()
{
	return m_program_id;
}

bool Fengine_shader::load_shaders(const string &vertex_file_path, const string &fragment_file_path)
{
	bool load_failed = false;

	// Create the shaders
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	string VertexShaderCode;
	ifstream VertexShaderStream(vertex_file_path.c_str(), ios::in);

	if(VertexShaderStream.is_open())
	{
		string Line = "";
		while(getline(VertexShaderStream, Line))
		{
			VertexShaderCode += "\n" + Line;
		}
		VertexShaderStream.close();
	}
	else
	{
		cout << "Cannot load shader " << vertex_file_path << endl;
		load_failed = true;
	}

	if(!load_failed)
	{
		// Read the Fragment Shader code from the file
		string FragmentShaderCode;
		ifstream FragmentShaderStream(fragment_file_path.c_str(), ios::in);

		if(FragmentShaderStream.is_open())
		{
			string Line = "";
			while(getline(FragmentShaderStream, Line))
			{
				FragmentShaderCode += "\n" + Line;
			}
			FragmentShaderStream.close();
		}
		else
		{
			cout << "Cannot load shader " << fragment_file_path << endl;
			load_failed = true;
		}

		if(!load_failed)
		{
			GLint Result = GL_FALSE;
			int InfoLogLength;

			// Compile Vertex Shader
			cout << "Compiling shader : " << vertex_file_path << endl;
			char const * VertexSourcePointer = VertexShaderCode.c_str();
			glShaderSource(vertex_shader_id, 1, &VertexSourcePointer , NULL);
			glCompileShader(vertex_shader_id);

			// Check Vertex Shader
			glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &Result);
			glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &InfoLogLength);

			if ( InfoLogLength > 0 )
			{
				vector<char> VertexShaderErrorMessage(InfoLogLength+1);
				glGetShaderInfoLog(vertex_shader_id, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
				cout << &VertexShaderErrorMessage[0] << endl;
			}

			// Compile Fragment Shader
			cout << "Compiling shader : " << fragment_file_path << endl;
			char const * FragmentSourcePointer = FragmentShaderCode.c_str();
			glShaderSource(fragment_shader_id, 1, &FragmentSourcePointer , NULL);
			glCompileShader(fragment_shader_id);

			// Check Fragment Shader
			glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &Result);
			glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &InfoLogLength);

			if ( InfoLogLength > 0 )
			{
				vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
				glGetShaderInfoLog(fragment_shader_id, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
				cout << &FragmentShaderErrorMessage[0] << endl;
			}

			// Link the program
			cout << "Linking program" << endl;
			GLuint program_id = glCreateProgram();
			glAttachShader(program_id, vertex_shader_id);
			glAttachShader(program_id, fragment_shader_id);
			glLinkProgram(program_id);

			// Check the program
			glGetProgramiv(program_id, GL_LINK_STATUS, &Result);
			glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &InfoLogLength);

			if ( InfoLogLength > 0 ){
				vector<char> ProgramErrorMessage(InfoLogLength+1);
				glGetProgramInfoLog(program_id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
				cout << &ProgramErrorMessage[0] << endl;
			}

			glDeleteShader(vertex_shader_id);
			glDeleteShader(fragment_shader_id);

			m_program_id = program_id;
		}
	}

	return load_failed;
}

GLuint Fengine_shader::get_uniform_location(std::string var_name)
{
	return glGetUniformLocation(m_program_id, var_name.c_str());
}

}
