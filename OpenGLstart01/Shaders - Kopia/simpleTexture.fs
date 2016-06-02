#version 330

in vec2 textureCoordinates;
uniform sampler2D textureIndex;

out vec4 fragColour;

void main(){
	vec4 texel = texture(textureIndex, textureCoordinates);
	fragColour = texel;
}