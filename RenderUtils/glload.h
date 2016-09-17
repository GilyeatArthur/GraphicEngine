#pragma once

#include "globjs.h"

struct Shader loadShader(const char *vpath, const char *fpath);

struct Texture loadTexture(const char *path);

struct Geometry loadOBJ(const char *path);
