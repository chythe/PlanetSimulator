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
	//Ambient - swiatlo otoczenia jako iloczyn globalnie ustalonego swiatla otoczenia z wspolczynnikiem konkretnego obiektu sceny
	vec3 ambientIntense=ambientColor*objectAmbientFactor;
	
	//Difuse - swiato rozproszone 
	vec3 distanceToLight= vec3(viewMatrix*vec4(lightPosition,1.0))-vertexToCamera; //roznica miedzy wektorem swiatla, a wektorem punktu w przestrzeni (po przeliczeniu co do pozycji kamery)
	vec3 lightDirection= normalize(distanceToLight); // normalizacja wektora dlg 1, zachowanie kierunku
	float dotProduct=dot(lightDirection,normalToCamera); //iloczyn skalarny - wartosc tego, czy zrodlo swiatla ze sceny dociera do punktu
	dotProduct=max(dotProduct,0.0); // gdyby iloczyn skalarny byl ujemny- swiatlo nie dociera to ustawiamy na 0
	vec3 diffuseIntense=diffuseColor*objectDiffuseFactor*dotProduct; // uzalezniamy intensywnosc swiatla rozproszenia od wartosci dla konkretnego modelu
	
	//Specular lustrzane
	vec3 reflection=reflect(-lightDirection,normalToCamera); // wektor odbicia kierunku swiatla do wektora normalnego pozycji kamery (kat padania = kat odbicia)
	vec3 surfaceToCamera=normalize(-vertexToCamera); // znormalizowany wektor 
	float dotSpecular= dot(reflection,surfaceToCamera); //iloczyn skalarny - wartosc tego, czy swiatlo odbite dociera do kamery
	dotSpecular=max(dotSpecular,0.0); // gdyby swiatlo odbite nie doceiaralo do kamery (cosinus ujemny) ustawiamy wartosc 0
	float specularPower=10.0; // wspolczynik mocy odbicia 
	float specularFactor=pow(dotSpecular,specularPower); 
	vec3 specularIntense=specularColor* objectSpecularFactor*specularFactor; //intensywnosc zalezna od konkretnego modelu sceny
	
  //uzywana funkcja cosinus oddaje jakby efekt intensywnosci swiatla- im obiekt dalej od zrodla swiatla lub kierunek patrzenia mniej zgodny z kierunkiem padania swiatla
  //tym szybciej swiatlo np. odbite jest mniej widoczne
  
	vec4 texel = texture(textureIndex, textureCoordinates);  
	fragColour = vec4(ambientIntense+diffuseIntense+specularIntense,1.0)*texel;
}