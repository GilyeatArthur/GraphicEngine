#include "gldecs.h"

#include "crenderutils.h"
#include "Vertex.h"

#include <cstdio>
#include <iostream>

#include <fstream>
#include <istream>
#include <string>

Geometry makeGeometry(const struct Vertex *verts, size_t vsize, const unsigned int	*tris, size_t tsize)
{
	Geometry retval;
	//Define the Variables
	glGenBuffers(1, &retval.vbo); //Store my vertices
	glGenBuffers(1, &retval.ibo); // store indices
	glGenVertexArrays(1, &retval.vao); // Store attribute information

	//Scope the variable
	glBindVertexArray(retval.vao);
	glBindBuffer(GL_ARRAY_BUFFER, retval.vbo); // scope our vertices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo); // triangle is scoped

	//Initalize the variables
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris, GL_STATIC_DRAW);
	
	//Attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)16);

	//unscope the variables
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	retval.size = tsize;
	return retval;
}



void freeGeometry(Geometry &geo)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);
	geo = { 0,0,0,0 };
}

Shader makeShader(const char * vsource, const char * fsource)
{
	Shader retval;
	//create our variables
	retval.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);
	//initialize our variables
	glShaderSource(vs, 1, &vsource, 0);
	glShaderSource(fs, 1, &fsource, 0);
	//compile the shaders
	glCompileShader(vs);
	glCompileShader(fs);
	//link the shaders into a single program
	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);
	glLinkProgram(retval.handle);
	//No longer need these. Their functionality has been eaten by the program
	glDeleteShader(vs);
	glDeleteShader(fs);

	return retval;
}

void freeShader(Shader &shader)
{
	glDeleteProgram(shader.handle);
	shader.handle = 0;
}

void draw(const Shader &shader, const Geometry &geometry)
{
	glUseProgram(shader.handle);

	//binding the VAO also binds the IBO (tri) and VBO (verts)
	glBindVertexArray(geometry.vao);

	//Draw elements will draw the vertices that are currently bound
	//using an array of indicies.
	// IF AN IBO IS BOUND, we don't need to provide any indicies.
	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}

// this is C-style using fixed array size...
// use whatever technique you are comfortable with!
// load an entire file's text to an array so that loadShader can
// use it to build the shader program!
char * copyFileToArray(const char *path) //Thanks Riley!
{
	int array_size = 5012; // Define max size of array
	char * array = new char[array_size]; // Make the array
	int position = 0; // Used to keep track of position inside of the array

	std::fstream fin(path); // Loading the file at 'path'

	if (fin.is_open()) { // If we successfully opened the file
		while (!fin.eof() && position < array_size) { // Continue to loop through the file til we get to the max array size we set earlier
			fin.get(array[position]); // Grab the charater in the file
			position++; // Increase are position in the arary
		}
		array[position - 1] = '\0'; // Make sure we don't have junk at the end

		for (int i = 0; array[i] != '\0'; i++) {
			std::cout << array[i]; // Just display the info
		}
	}

	return array; // Return. duh
}

std::string cppStyleFileToString(const char *path)
{
	std::ifstream infile{ path };
	std::string file_contents{ std::istreambuf_iterator<char>(infile),
							   std::istreambuf_iterator<char>() };
	return file_contents;
}



Shader loadShader(const char *vpath, const char *fpath)
{
	char * vsource; //max of 5012 characters in source
	char * fsource; //will probably change that later

	vsource = copyFileToArray(vpath);
	fsource = copyFileToArray(fpath);

	std::string vs = cppStyleFileToString(vpath);
	std::string fs = cppStyleFileToString(fpath);
	//return makeShader(vs.c_str(), fs.c_str());

	return makeShader(vsource, fsource);
}

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "OBJ/tiny_obj_loader.h"
#include <random>

Geometry loadOBJ(const char *path)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	Vertex   *verts = new Vertex[attrib.vertices.size() / 3];
	unsigned * tris = new unsigned[shapes[0].mesh.indices.size()];

	for (int i = 0; i < attrib.vertices.size()/3; ++i)
	{
		verts[i] = { attrib.vertices[i*3],
					 attrib.vertices[i*3+1],
					 attrib.vertices[i*3+2], 1};
		
		verts[i].color[0] = rand() * 1.0f / RAND_MAX;
		verts[i].color[1] = rand() * 1.0f / RAND_MAX;
		verts[i].color[2] = rand() * 1.0f / RAND_MAX;
		verts[i].color[3] = 1;
	}

	for (int i = 0; i < shapes[0].mesh.indices.size(); ++i)
		tris[i] = shapes[0].mesh.indices[i].vertex_index;

	Geometry retval = makeGeometry(verts, attrib.vertices.size() / 3, 
									tris, shapes[0].mesh.indices.size());

	delete[] verts;
	delete[] tris;

	return retval;
}