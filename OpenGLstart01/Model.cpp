#include "Model.h"
#include <string>


Model::Model(const Model & model):meshStartingVertexIndex(model.getMeshStartingVertexIndex()),textures(model.getTextures()),meshVerticesCount(model.getMeshVerticesCount()),vao(model.getVao()){
}

Model::Model(std::string fileName){
		
	
	int verticesTotalCount = 0;
	std::vector<GLfloat> bufferVboData;
	/*
		Parameters: file location, requested operation - in that case dividing models on triangles
	*/
	const aiScene * scene = aiImportFile(fileName.c_str(), aiProcess_Triangulate);
	if (!scene)
	{
		std::cout << "Mesh not found." << std::endl;
	}
	/*
		Numbers of all object on the scene 
	*/
	for (int i = 0; i != scene->mNumMeshes; i++){   
		aiMesh* mesh = scene->mMeshes[i];
		/*
			Number of model's verices, which is currently loaded
		*/
		int meshVertices = 0;  
		/*
			Number of model's surfaces
		*/
		for (int j = 0; j != mesh->mNumFaces; j++){  //ilosc powierzchni modelu
			/*
				Fetching model's surface
			*/
			const aiFace* face = &mesh->mFaces[j];  // pobranie powierzcni modelu
			/*
				Surfaces are triangles than we need to perform loop with 3 runs
			*/
			for (int k = 0; k != 3; k++){  
				aiVector3D vertexPosition{ 0, 0, 0 };
				aiVector3D vertexNormal{ 0, 0, 0 };
				aiVector3D vertexTextureCoordinations{ 0, 0, 0 };

				/*
					Sets the possition vector
				*/
				if (mesh->HasPositions())  
					vertexPosition = mesh->mVertices[face->mIndices[k]];
				/*
					Sets the normal vector
				*/
				if (mesh->HasNormals())  
					vertexNormal = mesh->mNormals[face->mIndices[k]];
				//std::cout << "Normalx: " << vertexNormal.x <<std::endl;
				//std::cout << "Normaly: " << vertexNormal.y << std::endl;
				//std::cout << "Normalz: " << vertexNormal.z << std::endl;
				/*
					Sets the textures coordinates
				*/
				if (mesh->HasTextureCoords(0))
					vertexTextureCoordinations = mesh->mTextureCoords[0][face->mIndices[k]];

				/*
					All parameters are saved in one buffer because the one VAO will be created
					Position for values of diffrent types of parameters will be indicate in VAO
				*/
				bufferVboData.push_back(vertexPosition.x);
				bufferVboData.push_back(vertexPosition.y);
				bufferVboData.push_back(vertexPosition.z);

				bufferVboData.push_back(vertexNormal.x);
				bufferVboData.push_back(vertexNormal.y);
				bufferVboData.push_back(vertexNormal.z);

				bufferVboData.push_back(vertexTextureCoordinations.x);
				bufferVboData.push_back(vertexTextureCoordinations.y);

				meshVertices++;
			}
		}
		/*
			Saves the numbers of vertices of currently loaded model
		*/
		meshVerticesCount.push_back(meshVertices);  
		meshStartingVertexIndex.push_back(verticesTotalCount);
		verticesTotalCount += meshVertices;

		/*
			Check if thera are any materials on scene avaliable (textures for example)
		*/
		if (scene->mNumMaterials != 0)  
		{
			/*
				Fetch the material
			*/
			const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex]; 

			aiString texturePath;
			Texture texture;
			/*
				Load model textures information, fetch the path for the texture file
			*/
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
			{
				unsigned int foundPos = fileName.find_last_of("/\\");
				std::string path = fileName.substr(0, foundPos);
				std::string name(texturePath.C_Str());
				if (name[0] == '/')
					name.erase(0, 1);

				std::string filePath = path + "/" + name;
				if (!texture.loadTextureForModel(filePath)){
					std::cout << "Texture " << filePath << " not found." << std::endl;
				}
				else{
					std::cout << "Texture " << filePath << " loaded." << std::endl;
				}
					
			}
			std::cout << texture.getTexture();
			textures.push_back(texture.getTexture());
		}
	}
	/*
		Creates the buffers for loaded data
	*/
	GLuint vboBuffer = 0;
	glGenBuffers(1, &vboBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vboBuffer);
	glBufferData(GL_ARRAY_BUFFER, bufferVboData.size() * sizeof(GLfloat),bufferVboData.data(), GL_STATIC_DRAW);


	/*
		Indicates in VAO where diffrents type of parameters starts
	*/
	int singleVertexSize = 2 * 3 * sizeof(GLfloat)+2 * sizeof(GLfloat);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, singleVertexSize, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, singleVertexSize,reinterpret_cast<void*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, singleVertexSize,reinterpret_cast<void*>(2 * 3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

}


Shader& Model::getShader() {
	return shader;
}
Transform& Model::getTransform(){
	return transform;
}

std::vector<GLfloat>  Model::getMeshStartingVertexIndex() const {
	return  meshStartingVertexIndex;
}

std::vector<GLuint>  Model::getTextures() const{
	return textures;
}
std::vector<GLfloat> Model::getMeshVerticesCount() const{
	return meshVerticesCount;
}

GLuint  Model::getVao() const{
	return vao;
}

void Model::draw() const{
	glBindVertexArray(vao);
	for (int i = 0; i < meshStartingVertexIndex.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glDrawArrays(GL_TRIANGLES, meshStartingVertexIndex[i], meshVerticesCount[i]);
	}
}