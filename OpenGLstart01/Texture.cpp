#include "Texture.h"

Texture::Texture(std::string fileName){
	loadTexture(fileName);
}
Texture::Texture(){
	
}
int Texture::loadTexture(std::string fileName){
	glActiveTexture(GL_TEXTURE0); 
	glGenTextures(1, &texture);

	FREE_IMAGE_FORMAT imageFormat = FreeImage_GetFileType(fileName.c_str(), 0);
	if (imageFormat == FIF_UNKNOWN)
		imageFormat = FreeImage_GetFIFFromFilename(fileName.c_str());

	FIBITMAP* imagePtr=0;
	if (FreeImage_FIFSupportsReading(imageFormat))
		imagePtr = FreeImage_Load(imageFormat, fileName.c_str());

	bits = FreeImage_GetBits(imagePtr);


	imageWidth = FreeImage_GetWidth(imagePtr);
	imageHeight = FreeImage_GetHeight(imagePtr);

	unsigned int colours = FreeImage_GetBPP(imagePtr);
	if (colours == 24)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0,
		GL_BGR, GL_UNSIGNED_BYTE, bits);
	else if (colours == 32)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
		0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
	
	
	return 1;
}

int Texture::loadTextureForModel(std::string fileName){
	FREE_IMAGE_FORMAT imageFormat = FIF_UNKNOWN;
	FIBITMAP* imagePtr = 0;
	BYTE* bits = 0;

	imageFormat = FreeImage_GetFileType(fileName.c_str(), 0);
	if (imageFormat == FIF_UNKNOWN)
		imageFormat = FreeImage_GetFIFFromFilename(fileName.c_str());

	if (FreeImage_FIFSupportsReading(imageFormat))
		imagePtr = FreeImage_Load(imageFormat, fileName.c_str());

	bits = FreeImage_GetBits(imagePtr);

	int imageWidth = 0;
	int imageHeight = 0;
	imageWidth = FreeImage_GetWidth(imagePtr);
	imageHeight = FreeImage_GetHeight(imagePtr);
	if ((bits == 0) || (imageWidth == 0) || (imageHeight == 0))
		return -1;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	unsigned int colours = FreeImage_GetBPP(imagePtr);
	
	if (colours == 24)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0,GL_BGR, GL_UNSIGNED_BYTE, bits);
	else if (colours == 32)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
	
	glGenerateMipmap(GL_TEXTURE_2D);

	return 1;
}

void Texture::bind(){
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_BGR,GL_UNSIGNED_BYTE, bits);
	glGenerateMipmap(GL_TEXTURE_2D);
}

GLuint Texture::getTexture(){
	return texture;
}