#version 330

in vec2 textureCoordinates;
in vec3 vertexToCamera;
in vec3 normalToCamera;

uniform sampler2D textureIndex;
uniform mat4 viewMatrix;
//To powinny byæ zmienne  
uniform vec3 objectAmbientFactor;
uniform vec3 objectDiffuseFactor;
uniform vec3 objectSpecularFactor;

out vec4 fragColour;

vec3 lightPosition=vec3(0.0,0.0,0.0);
vec3 ambientColor=vec3(1.0,1.0,1.0);
vec3 diffuseColor=vec3(1.0,1.0,1.0);
vec3 specularColor=vec3(1.0,1.0,1.0);




void main(){
	//Ambient
	vec3 ambientIntense=ambientColor*objectAmbientFactor;
	
	//Difuse
	vec3 distanceToLight= vec3(viewMatrix*vec4(lightPosition,1.0))-vertexToCamera;
	vec3 lightDirection= normalize(distanceToLight);
	float dotProduct=dot(lightDirection,normalToCamera);
	dotProduct=max(dotProduct,0.0);
	vec3 diffuseIntense=diffuseColor*objectDiffuseFactor*dotProduct;
	
	//Specular
	vec3 reflection=reflect(-lightDirection,normalToCamera);
	vec3 surfaceToCamera=normalize(-vertexToCamera);
	float dotSpecular= dot(reflection,surfaceToCamera);
	dotSpecular=max(dotSpecular,0.0);
	float specularPower=10.0;
	float specularFactor=pow(dotSpecular,specularPower);
	vec3 specularIntense=specularColor* objectSpecularFactor*specularFactor;
	
	vec4 texel = texture(textureIndex, textureCoordinates);
	fragColour = vec4(ambientIntense+diffuseIntense+specularIntense,1.0)*texel;
}