#version 330

layout(location=0) in vec3 position;
layout(location=1) in vec3 normalVector;
layout(location=2) in vec2 vTexture;


uniform mat4 modelMatrix;
uniform mat4 perspectiveMatrix;
uniform mat4 viewMatrix;

out vec2 textureCoordinates;
out vec3 normalToCamera;
out vec3 vertexToCamera;

void main(){
	normalToCamera = vec3(viewMatrix*vec4(normalVector,0.0));
	vertexToCamera = vec3(viewMatrix*vec4(position,1.0));

	textureCoordinates = vTexture;
	gl_Position = perspectiveMatrix*viewMatrix*modelMatrix*vec4(position,1.0);
}