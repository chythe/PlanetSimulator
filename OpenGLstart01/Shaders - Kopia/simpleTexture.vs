#version 330

layout(location=0) in vec3 vVertex;
layout(location=1) in vec2 vTexture;

out vec2 textureCoordinates;

uniform mat4 modelViewProjection;

void main(){
	textureCoordinates = vTexture;
	gl_Position = modelViewProjection*vec4(vVertex,1.0);
}