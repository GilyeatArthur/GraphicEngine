#pragma once

#include "Vertex.h"
#include "window.h"

#include "globjs.h"
#include "glmake.h"
#include "glload.h"
#include "gldraw.h"

//Texture loadTexture(const char *path);
//
//Geometry makeGeometry(const struct Vertex *verts, size_t vsize, 
//					  const unsigned int	*tris,	size_t tsize);
//
//void freeGeometry(Geometry &);
//
//Geometry loadOBJ(const char *path);
//
//Shader makeShader(const char *vsource, const char *fsource);
//Shader loadShader(const char *vpath, const char *fpath);
//void freeShader(Shader &);
//
//void draw(const Shader &, const Geometry &, float time);
//void drawCam(const Shader &s, const Geometry &g, const float *M, const float *V, const float *P, float time);
//
//// color depth - 24-bit colour vs 32-bit colours vs 8-bit
//// 0 - 255, #00 - #FF
//// R   G   B   A
////#FF  FF  FF  FF
//Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels);
//Texture makeTextureF(unsigned square, const float *pixels);
//
//void freeTexture(Texture &t);
//
//void drawTex(const Shader &, const Geometry &, const Texture &, const float M[16], const float V[16], const float P[16], float time);
//
//void drawPhong(const Shader &s, const Geometry &g,
//	 const float M[16], const float V[16], const float P[16], 
//	 const Texture *T, unsigned t_count);
//
//Framebuffer makeFramebuffer(unsigned width, unsigned height, unsigned ncolors);
//
//void freeFramebuffer(Framebuffer &);
//
//void clearFramebuffer(const Framebuffer &);
//
//void drawFB(const Shader &s, const Geometry &g, const Framebuffer &f, 
//			const float M[16], const float V[16], const float P[16], 
//			const Texture *T, unsigned t_count);