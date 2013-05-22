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
#include "types.hpp"

#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

///
///	@fn	GLuint load_dds_texture(const string texture_path)
///
///	@brief	Helper function that loads in a DDS texture from the passed in path
///
///	@param[in]	texture_path	The path to the texture on disk
///
///	@return	The texture ID
///
GLuint load_dds_texture(const string &texture_path)
{
	bool load_failed = false;

	// Create one OpenGL texture
	GLuint texture_id = 0;

	unsigned char header[124];

	FILE *fp;

	// Try to open the file
	fp = fopen(texture_path.c_str(), "rb");
	if (fp == NULL)
	{
		cout << "Texture file cannot be opened: " << texture_path << endl;
		load_failed = true;
	}

	if(!load_failed)
	{
		// Verify the type of file
		char filecode[4];
		fread(filecode, 1, 4, fp);
		if (strncmp(filecode, "DDS ", 4) != 0)
		{
			fclose(fp);
			cout << "Texture file is not the correct type: " << texture_path << endl;
			load_failed = true;
		}

		if(!load_failed)
		{

			// Get the surface desc
			fread(&header, 124, 1, fp);

			Uint32 height = *(Uint32*)&(header[8 ]);
			Uint32 width = *(Uint32*)&(header[12]);
			Uint32 linearSize = *(Uint32*)&(header[16]);
			Uint32 mipMapCount = *(Uint32*)&(header[24]);
			Uint32 fourCC = *(Uint32*)&(header[80]);

			Byte * buffer;
			Uint32 bufsize = 0;

			// How big is it going to be including all mipmaps?
			bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
			buffer = (Byte*)malloc(bufsize * sizeof(Byte));

			fread(buffer, 1, bufsize, fp);

			// Close the file pointer
			fclose(fp);

			//Uint32 components = (fourCC == FOURCC_DXT1) ? 3 : 4;
			Uint32 format = 0;

			switch(fourCC)
			{
			case FOURCC_DXT1:
				format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				break;
			case FOURCC_DXT3:
				format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				break;
			case FOURCC_DXT5:
				format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				break;
			default:
				free(buffer);
				cout << "Texture file is not the correct type: " << texture_path << endl;
				load_failed = true;
			}

			if(!load_failed)
			{
				//Create the texture
				glGenTextures(1, &texture_id);

				// "Bind" the newly created texture : all future texture functions will modify this texture
				glBindTexture(GL_TEXTURE_2D, texture_id);
				glPixelStorei(GL_UNPACK_ALIGNMENT,1);

				Uint32 blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
				Uint32 offset = 0;

				// Load the mipmaps
				for (Uint32 level = 0; level < mipMapCount && (width || height); ++level)
				{
					Uint32 size = ((width+3)/4)*((height+3)/4)*blockSize;
					glCompressedTexImage2D(
							GL_TEXTURE_2D,
							level,
							format,
							width,
							height,
							0,
							size,
							buffer + offset
							);

					offset += size;
					width  /= 2;
					height /= 2;
				}

				free(buffer);

				cout << "Loaded texture: " << texture_path << endl;
			}
		}
	}

	return texture_id;
}

namespace fengine
{

Fengine_model::Fengine_model():
				m_vertex_buffer(0),
				m_uv_buffer(0),
				m_normal_buffer(0),
				m_shader_p(0),
				m_matrix_id(0),
				m_texture_id(0)
{

}

Fengine_model::Fengine_model(
		const string &model_path,
		const string &texture_path,
		Fengine_shader &shader,
		vec3 &pos,
		vec3 &look_at,
		vec3 &up
		):
		Fengine_object(pos, look_at, up),
		m_vertex_buffer(0),
		m_uv_buffer(0),
		m_normal_buffer(0),
		m_shader_p(0),
		m_matrix_id(0),
		m_texture_id(0)
{
	m_shader_p = &shader;

	m_texture_id = load_dds_texture(texture_path);

	// Get a handle for our "myTextureSampler" uniform
	m_texture_handle = m_shader_p->get_uniform_location("myTextureSampler");

	// Get a handle for our "MVP" uniform
	//m_matrix_id = m_shader_p->get_uniform_location("MVP");

	//Load the model to populate the vertices, UVs and normals
	load_model(model_path);

	glGenBuffers(1, &m_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vec3), &m_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_uv_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uv_buffer);
	glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(vec2), &m_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_normal_buffer);
	glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(vec3), &m_normals[0], GL_STATIC_DRAW);
}

Fengine_model::~Fengine_model()
{
	glDeleteBuffers(1, &m_vertex_buffer);
	glDeleteBuffers(1, &m_uv_buffer);
	glDeleteBuffers(1, &m_normal_buffer);
	glDeleteTextures(1, &m_texture_id);
}

void Fengine_model::update()
{
	Fengine_object::update();
}

void Fengine_model::draw(mat4 &mvp)
{
	//Use our shader
	//glUseProgram(m_shader_p->get_program_id());

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	//glUniformMatrix4fv(m_matrix_id, 1, GL_FALSE, &mvp[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);

	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(m_texture_handle, 0);

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

	// Second attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_uv_buffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_normal_buffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the model
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

bool Fengine_model::load_model(string model_path)
{
	cout << "Loading OBJ file " << model_path << endl;

	vector<Uint32> vertexIndices, uvIndices, normalIndices;
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
			Uint32 vertexIndex[3], uvIndex[3], normalIndex[3];

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
	for( Uint32 i=0; i<vertexIndices.size(); i++ )
	{
		// Get the indices of its attributes
		Uint32 vertexIndex = vertexIndices[i];
		Uint32 uvIndex = uvIndices[i];
		Uint32 normalIndex = normalIndices[i];

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
