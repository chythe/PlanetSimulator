#include "Shader.h"

Shader::Shader(){

}


Shader::Shader(std::string fileLocation){
	if (loadFromFile(fileLocation)){
		std::cout << "shader loaded ";
	}
	else{
		std::cout << "shader loaded incorrectly";
	}
}

Shader::~Shader(){
	glUseProgram(0); //z argumentem 0 mówi maszynie stanów, ¿e nie bêd¹ u¿ywane dane shadery,
	for (int i = 0; i < NUM_TYPES; i++){
		glDetachShader(program, shaders[i]);
	}

	glDeleteProgram(program);
}


bool Shader::loadFromFile(std::string fileLocation){
	program = glCreateProgram();
	shaders[VERTEX] = glCreateShader(GL_VERTEX_SHADER);
	shaders[FRAGMENT] = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexContent = loadShader(fileLocation + ".vs");
	std::string fragmentContent = loadShader(fileLocation + ".fs");

	GLint vertexSize[1];
	vertexSize[0] = vertexContent.size();

	GLint fragmentSize[1];
	fragmentSize[0] = fragmentContent.size();

	const GLchar * vertexContentGL[1];
	vertexContentGL[0] = vertexContent.c_str();

	const GLchar * fragmentContentGL[1];
	fragmentContentGL[0] = fragmentContent.c_str();

	glShaderSource(shaders[VERTEX], 1, vertexContentGL, vertexSize); // tu by mo¿na wszystko na tablice przerobiæ i wrzuciæ to w pêtlê 
	glCompileShader(shaders[VERTEX]);
	checkError(shaders[VERTEX], false, GL_COMPILE_STATUS, "COMPILE ERROR: ");

	glShaderSource(shaders[FRAGMENT], 1, fragmentContentGL, fragmentSize);
	glCompileShader(shaders[FRAGMENT]);
	checkError(shaders[FRAGMENT], false, GL_COMPILE_STATUS, "COMPILE ERROR: ");

	for (int i = 0; i < NUM_TYPES; i++){
		glAttachShader(program, shaders[i]);
	}
	glLinkProgram(program);
	checkError(program, true, GL_LINK_STATUS, "LINK ERROR: ");
	glUseProgram(program);


	//modelViewProjectionUniform = glGetUniformLocation(program, "modelViewProjection");
	modelUniform = glGetUniformLocation(program, "modelMatrix");
	viewUniform = glGetUniformLocation(program, "viewMatrix");
	perspectiveUniform = glGetUniformLocation(program, "perspectiveMatrix");

	//lightning uniforms 
	objectAmbientFactorUniform = glGetUniformLocation(program, "objectAmbientFactor");
	objectDiffuseFactorUniform = glGetUniformLocation(program, "objectDiffuseFactor");
	objectSpecularFactorUniform = glGetUniformLocation(program, "objectSpecularFactor");

	
	textureIndexUniform = glGetUniformLocation(program, "textureIndex");

	for (int i = 0; i < NUM_TYPES; i++){ //dopisane nie konieczne !
		glDeleteShader(shaders[i]);
	}

	return 1;
}

void Shader::checkError(GLuint handle, bool isProgram, GLenum status, std::string errorMsg){
	GLint result;
	GLchar error[1024] ={0};
	if (isProgram){
		glGetProgramiv(handle, status, &result);
	}
	else {
		glGetShaderiv(handle, status, &result);
	}

	if (result==GL_FALSE){
		if (isProgram){
			glGetProgramInfoLog(handle, 1024, NULL,error);
		}
		else {
			glGetShaderInfoLog(handle, 102, NULL, error);
		}

		std::cerr << errorMsg << error << std::endl;
	}
}

std::string Shader::loadShader(std::string fileLocation){
	std::string line;
	std::string content;
	std::ifstream file(fileLocation);

	if (file.is_open()){
		while (std::getline(file, line)){
			content += line + "\n";
		}
	}
	std::cout<<content;
	
	return content;

}
void Shader::setTextureIndex(int index){
	glUniform1i(textureIndexUniform, index); //t¹ funkcje wywolujemy dopiero po zbidnowaniu tzn po glUseProgram
}
void Shader::Update(Transform * currentTransform, Camera * currentCamera){
	glm::mat4 modelMatrix = currentTransform->getModelMatrix();
	glm::mat4 viewMatrix = currentCamera->getViewMatrix();
	glm::mat4 perspectiveMatrix = currentCamera->getPerspectiveMatrix();


	glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(perspectiveUniform, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));

}

void Shader::updateLightning(glm::vec3 objectAmbientFactor, glm::vec3 objectDiffuseFactor, glm::vec3 objectSpecularFactor){
	glUniform3fv(objectAmbientFactorUniform, 1, glm::value_ptr(objectAmbientFactor));
	glUniform3fv(objectDiffuseFactorUniform,1, glm::value_ptr(objectDiffuseFactor));
	glUniform3fv(objectSpecularFactorUniform, 1, glm::value_ptr(objectSpecularFactor));
	
}

void Shader::Bind(){
	glUseProgram(program);
}