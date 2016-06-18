// ***********************************************************************
// Assembly         : 
// Author           : Przemek
// Created          : 06-17-2016
//
// Last Modified By : Przemek
// Last Modified On : 06-17-2016
// ***********************************************************************
// <copyright file="Texture.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "Dependencies\freeImage\FreeImage.h"
#include "Dependencies\glew\glew.h"
#include <string>


/*
	Textures handler
*/
/// <summary>
/// Textures handler
/// </summary>
class Texture{
	
	/// <summary>
	/// The texture indicator.
	/// </summary>
	GLuint texture;
	
	
	/// <summary>
	/// The amount of bites of loaded bitmap
	/// </summary>
	BYTE* bits;
	
	/// <summary>
	/// The image width
	/// </summary>
	int imageWidth;
	
	/// <summary>
	/// The image height
	/// </summary>
	int imageHeight;

public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Texture"/> class.
	/// Data are loaded from the file. It should be some image format file
	/// </summary>
	/// <param name="filename">The filename.</param>
	Texture(std::string filename);
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Texture"/> class.
	/// </summary>
	Texture();

	/// <summary>
	/// Loads the texture from image format file
	/// Before calling loadTexture(...) funtion the glActiveTexture(GL_TEXTURE"value") sholud be perform to select the place for texture
	/// This value should be set in shaders programm to indicate correct textures
	/// This function should be use if we just load simple image.
	/// </summary>
	/// <param name="filename">The filename.</param>
	/// <returns>The correction indicator 1 correct  -1 error</returns>
	int loadTexture(std::string filename);  // zwykle wczytywanie, powczytaniu trzeba zbindowaæ, ¿eby aktywowaæ
	
	
	/// <summary>
	/// Loads the texture for Model object.
	/// It should be the method which should be use, when we load texture especially during loading Model object
	/// </summary>
	/// <param name="filename">The filename.</param>
	/// <returns>The correction indicator 1 correct -1 error</returns>
	int loadTextureForModel(std::string filename);
	
	/// <summary>
	/// Gets the texture indicator
	/// </summary>
	/// <returns>GLuint.</returns>
	GLuint getTexture();
	
	/// <summary>
	/// Binds this instance. 
	/// Binds causes that this texture is currently active and use during rendering process
	/// </summary>
	void bind();
};