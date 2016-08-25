#include "gldecs.h"

#include "crenderutils.h"
#include "Vertex.h"

#include <cstdio>

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