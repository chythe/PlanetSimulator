#include "Dependencies\glew\glew.h"
#include "Dependencies\glfw\glfw3.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\freeImage\FreeImage.h"
#include "Dependencies\assimp\scene.h"
#include "Dependencies\assimp\postprocess.h"
#include "Dependencies\assimp\cimport.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "Transform.h"
//#include "Camera.h"
#include "Shader.h"
#include "Vertex.h"
#include "Mesh.h"
//#include "Texture.h"
#include "Planet.h"
#include "MovementParameters.h"

#include <iostream>



int window_width = 800;
int window_height = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void window_size_callback(GLFWwindow* window, int width, int height);
void CursorPositionCallback(GLFWwindow* window, double cursorPositionX,double cursorPositionY);


double previousTime;
double actualTime;
double elapsedTime;
Camera camera;
Keyboard keyboard;
Mouse mouse;

int main(){

	

	//inicjalizacja glfw
	if (!glfwInit()){
		std::cout << "Error during glfw initiation";
		glfwTerminate();
		return 1;
	}

	//USTAWIENIA OKNA   opcja(jest to enum),wartoœæ jak¹ chcemy ustawiæ
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	//Poni¿ej tworzeenie okna z wczytaniem maksymalnych rozmiarów ekranu
	//const GLFWvidmode* video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	//GLFWwindow* window = glfwCreateWindow(video_mode->width, video_mode->height, "GL Window", glfwGetPrimaryMonitor(), NULL);
	//tworzenie okna 
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	

	// Set the required callback functions
//	glfwSetKeyCallback(window, key_callback); // obsluga klawiszy
	glfwSetWindowSizeCallback(window, window_size_callback); // obsluga zmiany rozmiaru okna 
//	glfwSetCursorPosCallback(window, CursorPositionCallback);
	

	
	//inicjalizacja glewa
	glewExperimental = GL_TRUE; //GLEW uses more modern techniques for managing OpenGL functionality
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return 1;
	}	
	glViewport(0, 0, 800, 600); // wskazujemy gdzie znajduje sie lewy gorny róg oraz rozmiar okna, mo¿na to chyba pomin¹æ

	
	

	


	
	Shader modelShader("shaders/simpleModel");
	modelShader.setTextureIndex(0);
	modelShader.Bind();
	

	

	Model model("Models/Sun/sun.dae");
	Model model2("Models/Green/green.dae");
	Model model3("Models/Sand/sand.dae");
	Model model4("Models/Moon/moon.dae");


	//Model farmModel("Models/Test/test/test2.dae");
	//Transform farmTransform;
	//farmTransform.setPosition(glm::vec3(0.0, 0.0, 0.0));
	//farmTransform.update();

	
	Planet planet4(&model4, &modelShader);
	Planet planet3(&model3, &modelShader);
	Planet planet2(&model2,&modelShader);
	Planet planet(&model,&modelShader);
	


	planet4.setLightningParameters(glm::vec3(0.1, 0.1, 0.1), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0));
	planet3.setLightningParameters(glm::vec3(0.1, 0.1, 0.1), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0));
	planet2.setLightningParameters(glm::vec3(0.1, 0.1, 0.1), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0));
	planet.setLightningParameters(glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0));


	planet2.setStartingParameters(4.5 * 1000, 0,   100, glm::vec3(0.002, 0, 0));
	planet3.setStartingParameters(4.6 * 1000, 0, 200000 * 1000, glm::vec3(0, 0, 0.009));
	planet4.setStartingParameters(5 * 1000, 0,   15000 * 1000, glm::vec3(0, 0, 0.019));
	

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glActiveTexture(GL_TEXTURE0);




	float position = 0.0f;
	float rotation = 0.0f;
	float time = 0;

	float ambient=1.0;
	float diffuse=1.0;
	float specular = 1.0;


    //glm::mat4 m1(0);
    //glm::mat4 m2(0);

    //m1[0][0] = 1;
    //m1[0][1] = 2;
    //m1[0][2] = 4;
    //m1[0][3] = 5;

    //m1[1][0] = 12;
    //m1[1][1] = 1;
    //m1[1][2] = 6;
    //m1[1][3] = 4;

    //m1[2][0] = 1;
    //m1[2][1] = 23;
    //m1[2][2] = 11;
    //m1[2][3] = 12;

    //m1[3][0] = 10;
    //m1[3][1] = 5;
    //m1[3][2] = 9;
    //m1[3][3] = 2;


    //m2[0][0] = 2;
    //m2[0][1] = 3;
    //m2[0][2] = 5;
    //m2[0][3] = 5;

    //m2[1][0] = 1;
    //m2[1][1] = 6;
    //m2[1][2] = 6;
    //m2[1][3] = 4;

    //m2[2][0] = 12;
    //m2[2][1] = 2;
    //m2[2][2] = 1;
    //m2[2][3] = 12;

    //m2[3][0] = 10;
    //m2[3][1] = 11;
    //m2[3][2] = 9;
    //m2[3][3] = 4;

    //Transform tmp;

    //glm::mat4 m3(0);

    //m3 = tmp.multipleMatrix(m2, m1);
    //std::cout << std::endl;
    //for (int i = 0; i < 4; i++)
    //{
    //    for (int j = 0; j < 4; j++)
    //    {
    //        std::cout << m3[i][j] << "\t";
    //    }
    //    std::cout << std::endl;
    //}
    //
    //m3 = m1*m2;
    //std::cout<<std::endl;
    //for (int i = 0; i < 4; i++)
    //{
    //    for (int j = 0; j < 4; j++)
    //    {
    //        std::cout << m3[i][j] << "\t";
    //    }
    //    std::cout<<std::endl;
    //}

   

    //system("pause");


	while (!glfwWindowShouldClose(window))
	{
		

		
		
		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // to konfiguruje kolor jaki uzyskamy po wywo³aniu glClear
		glViewport(0, 0, window_width, window_height);// aktualizacja rozmiaru rzutni


		previousTime = actualTime;
		actualTime = glfwGetTime();
		elapsedTime = actualTime - previousTime;


		rotation += 0.001;
		
		time += 0.04;
		if (time >= 0){
		

			//ambient += 0.0005;
			//diffuse += 0.0005;
			//specular+= 0.0005;

			if (ambient > 1.0){
				ambient = 0.0;
			}
			if (diffuse > 1.0){
				diffuse = 0.0;
			}
			if (specular > 1.0){
				specular = 0.0;
			}

			std::cout << "Ambient  x " <<planet2.objectAmbientFactor.x<<std::endl;

			//planet2.getTransform().setPosition(glm::vec3(0.0, 4, 0.0));
		//	planet2.setLightningParameters(glm::vec3(ambient, ambient, ambient), glm::vec3(diffuse, diffuse, diffuse), glm::vec3(specular, specular, specular));

			planet2.calculateNewCoordinates();
			planet2.setTransform();
			
			planet3.calculateNewCoordinates();
			planet3.setTransform();

			planet4.calculateNewCoordinates();
			planet4.setTransform();
			
			time = 0;
		}

	/*	farmTransform.setRotation(glm::vec3(0.0, rotation, 0.0));
		farmTransform.update();
		modelShader.Update(&farmTransform, &camera);
		modelShader.updateLightning(glm::vec3(ambient, ambient, ambient), glm::vec3(diffuse, diffuse, diffuse), glm::vec3(specular, specular, specular));
		farmModel.draw();*/
		
		planet4.drawComplex(camera);
		planet3.drawComplex(camera);


		planet.drawComplex(camera);
		planet2.drawComplex(camera);

		keyboard.moveCamera(camera, window, elapsedTime);
		mouse.moveCamera(window, camera, elapsedTime);
		
		
		glfwSwapBuffers(window);// will swap the color buffer(a large buffer that contains color values for each pixel in GLFW's window) that has been used to draw in during this iteration and show it as output to the screen. 
		glfwPollEvents(); //function checks if any events are triggered and calls the corresponding functions (which we can set via callback methods). We usually call eventprocessing functions at the start of a loop iteration.
	
	}

	//glfwTerminate(); // zamykamy wszystkie utworzone przez glfw zasoby


//	system("pause");
	return 0;
	
}

//glBindVertexArray(model.vao);
//for (int i = 0; i < model.meshStartingVertexIndex.size(); i++)
//{
//	glBindTexture(GL_TEXTURE_2D, model.textures[i]);
//	farmohouseShader.setTextureIndex(0);
//	farmohouseShader.Update(&farmhouseTransform, &camera);
//	glDrawArrays(GL_TRIANGLES, model.meshStartingVertexIndex[i], model.meshVerticesCount[i]);
//}


//void CursorPositionCallback(GLFWwindow* window, double cursorPositionX, double cursorPositionY)
//{
//	glfwSetCursorPos(window, window_width / 2, window_height / 2);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	float mouse_speed = 0.5f;
//s
//	horizontal_angle += mouse_speed * (float)GetTimeDelta() *
//		float(window_width / 2.0 - cursorPositionX);
//	vertical_angle += mouse_speed * (float)GetTimeDelta() *
//		float(window_height / 2.0 - cursorPositionY);
//
//	if (vertical_angle < -1.57)
//		vertical_angle = -1.57;
//	if (vertical_angle > 1.57)
//		vertical_angle = 1.57;
//
//	camera_direction = glm::vec3(cos(vertical_angle) * sin(horizontal_angle),
//		sin(vertical_angle),
//		cos(vertical_angle) * cos(horizontal_angle));
//	camera_right = glm::vec3(-cos(horizontal_angle), 0,
//		sin(horizontal_angle));
//	camera_up = glm::cross(camera_right, camera_direction);
//
//	view_matrix = glm::lookAt(camera_position, camera_position +
//		camera_direction, camera_up);
//}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	window_width = width;
	window_height = height;
}