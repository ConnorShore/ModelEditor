#ifndef TEXTURE 
#define TEXTURE

#include <string>
#include <GL/glew.h>

struct Texture {
	GLuint id;
	int width, height;
	std::string filePath;
};

#endif