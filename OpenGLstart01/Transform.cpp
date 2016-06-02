#include "Transform.h"

Transform::Transform(){
	position = glm::vec3(0.0f,0.0f,10.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);

}

Transform::~Transform(){

}

glm::vec3 Transform:: normalize(const glm::vec3 vecIn)
{
    glm::vec3 normalized;
    
    float length = sqrt(vecIn.x*vecIn.x + vecIn.y*vecIn.y + vecIn.z*vecIn.z);
    
    normalized.x = vecIn.x / length;
    normalized.y = vecIn.y / length;
    normalized.z = vecIn.z / length;

    return normalized;
}


glm::mat4 Transform:: rotate(float rotation,const glm::vec3 axis)
{
    glm::vec3 axisNormalized = glm::normalize(axis);
    
    const float angle = (rotation);
    const float sinus = glm::sin(angle);
    const float cosinus = glm::cos(angle);

    glm::vec3 tmp((float(1)- cosinus)*axisNormalized);

    glm::mat4 identityMatrix(0);
    identityMatrix[0][0] = 1;
    identityMatrix[1][1] = 1;
    identityMatrix[2][2] = 1;
    identityMatrix[3][3] = 1;

    glm::mat4x4 rotate(0);

    rotate[0][0] = cosinus + tmp[0] * axis[0];
    rotate[0][1] = 0 + tmp[0] * axis[1] + sinus * axis[2];
    rotate[0][2] = 0 + tmp[0] * axis[2] - sinus * axis[1];

    rotate[1][0] = 0 + tmp[1] * axis[0] - sinus * axis[2];
    rotate[1][1] = cosinus + tmp[1] * axis[1];
    rotate[1][2] = 0 + tmp[1] * axis[2] + sinus * axis[0];

    rotate[2][0] = 0 + tmp[2] * axis[0] + sinus * axis[1];
    rotate[2][1] = 0 + tmp[2] * axis[1] - sinus * axis[0];
    rotate[2][2] = cosinus + tmp[2] * axis[2];

    glm::mat4 result(0);
    result[0] = identityMatrix[0] * rotate[0][0] + identityMatrix[1] * rotate[0][1] + identityMatrix[2] * rotate[0][2];
    result[1] = identityMatrix[0] * rotate[1][0] + identityMatrix[1] * rotate[1][1] + identityMatrix[2] * rotate[1][2];
    result[2] = identityMatrix[0] * rotate[2][0] + identityMatrix[1] * rotate[2][1] + identityMatrix[2] * rotate[2][2];
    result[3] = identityMatrix[3];
   
    return result;

}

glm::mat4 Transform:: multipleMatrix(const glm::mat4 & m1,const glm::mat4 & m2)
{

    glm::mat4 m(0);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                m[i][j] += m1[i][k] * m2[k][j];
            }
          
        }
    }
    return m;
    
}

glm::mat4 Transform::translate(const glm::vec3 position)
{
    glm::mat4 m(0);
   
    m[0][0] = 1;
    m[1][1] = 1;
    m[2][2] = 1;
    m[3][3] = 1;


    glm::mat4 result(m);
    result[3] = m[0] * position[0] + m[1] * position[1] + m[2] * position[2] + m[3];
    return result;
  
    
}


void Transform::update(){
	
	glm::mat4 translateMatrix = translate(position);
	
   // glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); //kat obrotu oraz os wzgledem której sie obracamy
   // glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
   // glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
   // glm::mat4 rotationMatrix = rotX*rotY*rotZ;


    glm::mat4 rotX = rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotY = rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotZ = rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotationMatrix = multipleMatrix(multipleMatrix(rotZ, rotY), rotX);

	glm::mat4 scaleMatrix = glm::scale(scale);
	modelMatrix = translateMatrix*rotationMatrix*scaleMatrix;

}

void Transform:: setPosition(glm::vec3 position){
	this->position = position;
}
void Transform::setRotation(glm::vec3 rotation){
	this->rotation = rotation;
}
void Transform::setScale(glm::vec3 scale){
	this->scale = scale;
}

glm::vec3  Transform::getPosition(){
	return position;
}
glm::vec3  Transform::getRotation(){
	return rotation;
}
glm::vec3  Transform::getScale(){
	return scale;
}
glm::mat4  Transform::getModelMatrix(){
	return modelMatrix;
}

