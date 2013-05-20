/**
*  model.cpp
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

#include "model.hpp"
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;

namespace fengine
{

Fengine_model::Fengine_model()
{

}

Fengine_model::Fengine_model(
		const string &model_path,
		Fengine_shader &shader,
		vec3 &pos,
		vec3 &look_at,
		vec3 &up
		):
		Fengine_object(pos, look_at, up),
		m_shader_p(nullptr),
		m_matrix_id(0),
		m_vertex_buffer(0)
{
	m_shader_p = &shader;

	// Get a handle for our "MVP" uniform
	m_matrix_id = glGetUniformLocation(m_shader_p->get_program_id(), "MVP");

	//Load the model to populate the vertices, UVs and normals
	load_model(model_path);

	glGenBuffers(1, &m_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vec3), &m_vertices[0], GL_STATIC_DRAW);
}

Fengine_model::~Fengine_model()
{
	glDeleteBuffers(1, &m_vertex_buffer);
	//glDeleteTextures(1, &TextureID);
	//glDeleteVertexArrays(1, &VertexArrayID);
}

void Fengine_model::update()
{
	Fengine_object::update();
}

void Fengine_model::draw(mat4 &mvp)
{
	//Use our shader
	glUseProgram(m_shader_p->get_program_id());

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(m_matrix_id, 1, GL_FALSE, &mvp[0][0]);

	// First attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);

	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the model
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

	glDisableVertexAttribArray(0);
}

glm::mat4 Fengine_model::get_model_matrix()
{
	return m_model_matrix;
}

bool Fengine_model::load_model(string model_path)
{
	cout << "Loading OBJ file " << model_path << endl;

	vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	vector<vec3> temp_vertices;
	vector<vec2> temp_uvs;
	vector<vec3> temp_normals;


	FILE * file = fopen(model_path.c_str(), "r");
	if( file == NULL ){
		cout << "Cannot open file: " << model_path << endl;
		return false;
	}

	while( true )
	{
		char lineHeader[128];

		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);

		if (res == EOF)
		{
			break; // EOF = End Of File. Quit the loop.
		}

		// else : parse lineHeader

		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{
			string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

			int matches = fscanf(
					file,
					"%d/%d/%d %d/%d/%d %d/%d/%d\n",
					&vertexIndex[0],
					&uvIndex[0],
					&normalIndex[0],
					&vertexIndex[1],
					&uvIndex[1],
					&normalIndex[1],
					&vertexIndex[2],
					&uvIndex[2],
					&normalIndex[2]
					);

			if (matches != 9)
			{
				cout << "File cannot be read by parser! " << model_path << endl;
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);

			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ )
	{
		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		vec3 vertex = temp_vertices[ vertexIndex-1 ];
		vec2 uv = temp_uvs[ uvIndex-1 ];
		vec3 normal = temp_normals[ normalIndex-1 ];

		//cout << "Vertex: " << vertex.x << " " <<  vertex.y << " " << vertex.z << endl;
		//cout << "UV: " << uv.x << " " <<  uv.y << endl;
		//cout << "Normal: " << normal.x << " " <<  normal.y << " " << normal.z << endl;

		// Put the attributes in buffers
		m_vertices.push_back(vertex);
		m_uvs.push_back(uv);
		m_normals.push_back(normal);
	}

	cout << "Vertices vec size: " << m_vertices.size() << endl;

	return true;
}

}
