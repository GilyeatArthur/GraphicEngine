#pragma once

#include "globjs.h"

struct Shader loadShader(const char *vpath, const char *fpath, bool depth = true, bool add = false, bool face = true);

struct Texture loadTexture(const char *path);

struct Geometry loadOBJ(const char *path);

// returns the number of shapes.
// size should be > greater than that number if you want all the geometry.
unsigned loadAllOBJ(const char *path, Geometry *out, unsigned size);
