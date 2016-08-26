#include "Gallery.h"

bool Gallery::makeShader(const char * name, const char * vsource, const char * fsource)
{
	// check to make sure that the name doesn't already exist
	shaders[name] = ::makeShader(vsource, fsource);

	return true;
}

bool Gallery::loadShader(const char * name, const char * vpath, const char * fpath)
{
	if (!shaders.count(name))
	{
		shaders[name] = ::loadShader(vpath, fpath);
		if (shaders[name].handle == 0)
		{
			shaders.erase(name);
		}

		return true;
	}
	else
	{
		fprintf(stderr, "Shader %s failed to load correctly!\n", name);
		return false;
	}
}

bool Gallery::makeObject(const char *name, const Vertex *verts, size_t vsize, const unsigned *tris, size_t tsize)
{
	objects[name] = ::makeGeometry(verts, vsize, tris, tsize);

	return true;
}

bool Gallery::loadObjectOBJ(const char *name, const char *path)
{
	objects[name] = ::loadOBJ(path);

	return true;
}

const Geometry &Gallery::getObject(const char * name)
{
	// need to validate the name first.
	return objects[name];
}

const Shader &Gallery::getShader(const char * name)
{
	// need to validate the name first.
	return shaders[name];
}

bool Gallery::term()
{
	//loop through my maps and call my free functions
	for each (auto shader in shaders)
		freeShader(shader.second);

	for each(auto object in objects)
		freeGeometry(object.second);

	return true;
}

bool Gallery::init()
{
	return true;
}