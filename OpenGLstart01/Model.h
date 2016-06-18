// ***********************************************************************
// Assembly         : 
// Author           : Przemek
// Created          : 06-17-2016
//
// Last Modified By : Przemek
// Last Modified On : 06-17-2016
// ***********************************************************************
// <copyright file="Model.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "assimp\scene.h"
#include "assimp\cimport.h"
#include "assimp\postprocess.h"


#include "Shader.h"
#include "Texture.h"


#include  <iostream>
#include <vector>




/// <summary>
/// Class Model. 
/// Loads from file.
/// Draws the mesh with textures
/// </summary>
class Model{
public:
	
	/// <summary>
	/// The shader class object
	/// </summary>
	Shader shader;
	/// <summary>
	/// The transform class objcet
	/// </summary>
	Transform transform;


	/// <summary>
	/// The mesh vertices count of single object in the model
	/// </summary>
	std::vector<GLfloat> meshVerticesCount;
	/// <summary>
	/// All part of vector represents the sum number of hitherto loaded model objects
	/// </summary>
	std::vector<GLfloat> meshStartingVertexIndex;
	/// <summary>
	/// The textures. The buffers indicators fot the textures
	/// </summary>
	std::vector<GLuint> textures;
	/// <summary>
	/// The vao is an OpenGL Object that stores all of the state needed to supply vertex data
	/// </summary>
	GLuint vao;

	/// <summary>
	/// Draws this instance.
	/// Bind vao than for all the objects in the model draw bind texture and draw the object.
	/// Every sets of data of single verticies are collected in vao. 
	/// The datas indicators int the vao table are determined by meshStartingVertexIndex and meshVerticesCount
	/// </summary>
	void draw() const;
	


	/// <summary>
	/// Gets the index of the mesh starting vertex.
	/// </summary>
	/// <returns>std.vector&lt;_Ty, _Alloc&gt;.</returns>
	std::vector<GLfloat>  getMeshStartingVertexIndex() const;
	/// <summary>
	/// Gets the textures.
	/// </summary>
	/// <returns>std.vector&lt;_Ty, _Alloc&gt;.</returns>
	std::vector<GLuint>	  getTextures() const;
	/// <summary>
	/// Gets the mesh vertices count.
	/// </summary>
	/// <returns>std.vector&lt;_Ty, _Alloc&gt;.</returns>
	std::vector<GLfloat>  getMeshVerticesCount() const;
	/// <summary>
	/// Gets the vao.
	/// </summary>
	/// <returns>GLuint.</returns>
	GLuint  getVao() const;

	/// <summary>
	/// Gets the shader.
	/// </summary>
	/// <returns>Shader &.</returns>
	Shader& getShader();
	
	/// <summary>
	/// Gets the transform.
	/// </summary>
	/// <returns>Transform &.</returns>
	Transform& getTransform();
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Model"/> class from file.
	/// Data are loaded from special file type for example Collada or OBJ
	/// Loads the data for all objects described in model file like vertices and textures coordinations.
	/// All needed data for future rendering are saved in the this class variables: vao, meshStartingVertexIndex, meshVerticesCount
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	Model(std::string fileName);
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Model"/> class - copy consturcotr.
	/// </summary>
	/// <param name="model">The other model.</param>
	Model(const Model & model);
};