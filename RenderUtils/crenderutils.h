

struct Geometry
{
	unsigned vbo, ibo, vao, size;
	//Vertex Buffer Object	: an array of vertices
	//Index Buffer Object	: an arra of idicies (triangles)
	//Vertex Array Object	: Groups the two with some formatting
	//size					: number of triangles
	
};

Geometry makeGeometry(const struct Vertex *verts, size_t vsize, 
					  const unsigned int	*tris,	size_t tsize);

void freeGeometry(Geometry &);

struct Shader
{
	unsigned handle;
};

Shader makeShader(const char *vsource, const char *fsource);

Shader loadShader(const char *vpath, const char *fpath);

void freeShader(Shader &);

void draw(const Shader &, const Geometry &);