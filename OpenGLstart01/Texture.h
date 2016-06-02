#pragma once
#include "Dependencies\freeImage\FreeImage.h"
#include "Dependencies\glew\glew.h"
#include <string>


/*
	Textures handler
*/
class Texture{
	GLuint texture;
	
	
	BYTE* bits;
	int imageWidth;
	int imageHeight;
public:
	Texture(std::string filename);
	Texture();
	/*
		Before calling loadTexture(...) funtion the glActiveTexture(GL_TEXTURE"value") sholud be perform to select the place for texture
		This value should be set in shaders programm to indicate correct textures 
	*/
	int loadTexture(std::string filename);  // zwykle wczytywanie, powczytaniu trzeba zbindowa�, �eby aktywowa�
	int loadTextureForModel(std::string filename);
	GLuint getTexture();
	void bind();
};