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
#include "Shader.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Planet.h"
#include "MovementParameters.h"

#include <iostream>
#include <vector>


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

int numberModels = 9;
int numberPlanets = 4;

enum Type {
	SUN,

	GREEN,	//r: 3
	SAND,	//r: 1.5
	MOON,	//r: 3.5
	EARTH,	//r: 1
	VENUS,	//r: 1.2
	BLUE,	//r: 1.7
	PURPLE,	//r: 2.5
	RED		//r: 0.5
};


//Create planet start
bool		createModeFlag = false,
			createFlag = false,
			planetSelectionFlag = false,
			velocitySelectionFlag = false,
			angleSelectionFlag = false,
			highSelectionFlag = false,
			rotationFirstFlag = false,
			rotationSecondFlag = false,
			rotationThirdFlag = false;

float		cVStart = 0.0,
			cVStartAdd = 1.0,
			cStartingAngle = 0.0,
			cStartingAngleAdd = 1.0,
			cStartingHigh = 0.0,
			cStartingHighAdd = 1.0,
			cRadius = 0.0,
			cRotationAdd = 0.001;

int			cPlanet = Type::GREEN;

glm::vec3	cRotation = glm::vec3(0.0, 0.0, 0.0);


void addNewPlanet(std::vector<Planet*>* planets, std::vector<Model*>* models, Shader *modelShader);
void valueSelection(float* value, float* valueAdd, int key, int action);
void displayInfo();
//Create planet end




int main(){

	std::cout.unsetf(std::ios::floatfield);
	std::cout.precision(8);

    Planet objPlanet();

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
	glfwSetKeyCallback(window, key_callback); // obsluga klawiszy
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
	

    std::vector<Model*> models;
    for (int i = 0; i < numberModels; i++){
        switch (i)
        {
        case SUN:
            models.push_back(new Model("Models/Sun/sun.dae"));
            break;
        case GREEN:
            models.push_back(new Model("Models/Green/green.dae"));
            break;
        case SAND:
            models.push_back(new Model("Models/Sand/sand.dae"));
            break;
        case MOON:
            models.push_back(new Model("Models/Moon/moon.dae"));
            break;
		case EARTH:
			models.push_back(new Model("Models/Earth/Earth.dae"));
			break;
		case VENUS:
			models.push_back(new Model("Models/Venus/venus.dae"));
			break;
		case BLUE:
			models.push_back(new Model("Models/Blue/blue.dae"));
			break;
		case PURPLE:
			models.push_back(new Model("Models/Purple/purple.dae"));
			break;
		case RED:
			models.push_back(new Model("Models/Red/red.dae"));
			break;
        }
    }

	//Model farmModel("Models/Test/test/test2.dae");
	//Transform farmTransform;
	//farmTransform.setPosition(glm::vec3(0.0, 0.0, 0.0));
	//farmTransform.update();


    std::vector<Planet*> planets;
    for (int i = 0; i < numberPlanets; i++){

        planets.push_back(new Planet(models[i], &modelShader));
    }
	


	planets[MOON]->setLightningParameters(glm::vec3(0.1, 0.1, 0.1), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0));
	planets[SAND]->setLightningParameters(glm::vec3(0.1, 0.1, 0.1), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0));
	planets[GREEN]->setLightningParameters(glm::vec3(0.1, 0.1, 0.1), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0));
	planets[SUN]->setLightningParameters(glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0));


    planets[GREEN]->setStartingParameters(3.4 * 1000, 0, 500000 * 1000, 3.0, glm::vec3(0.002, 0, 0)); //green //100
    planets[SAND]->setStartingParameters(4.6 * 1000, 0, 200000 * 1000, 1.5, glm::vec3(0, 0, 0.009)); //sand //300000 * 1000
    planets[MOON]->setStartingParameters(5 * 1000, 0, 800000 * 1000, 3.5, glm::vec3(0, 0, 0.019)); //moon //800000 * 1000
	

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glActiveTexture(GL_TEXTURE0);




	float position = 0.0f;
	float rotation = 0.0f;
	float time = 0;

	float ambient=1.0;
	float diffuse=1.0;
	float specular = 1.0;




	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // to konfiguruje kolor jaki uzyskamy po wywo³aniu glClear
		glViewport(0, 0, window_width, window_height); // aktualizacja rozmiaru rzutni

		//Create planet	start
		if (createFlag) {
			addNewPlanet(&planets, &models, &modelShader);
		}
		//Create planet end

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

			//std::cout << "Ambient  x " <<planet2.objectAmbientFactor.x<<std::endl;

			//planet2.getTransform().setPosition(glm::vec3(0.0, 4, 0.0));
		    //planet2.setLightningParameters(glm::vec3(ambient, ambient, ambient), glm::vec3(diffuse, diffuse, diffuse), glm::vec3(specular, specular, specular));

            for (int i = 1; i < numberPlanets; i++){
                if (planets[i] != NULL){
                    planets[i]->calculateNewCoordinates();
                    planets[i]->setTransform();
                }
            }
		
            for (int i = 0; i < numberPlanets; i++)
            {
                for (int j = 0; j < numberPlanets; ++j)
                {
                    if (i != j)
                    {
                        if (planets[i] != NULL && planets[j] != NULL)
                        {
                            if (planets[i]->collision(planets[j]))
                            {
                                std::cout << "KOLIZJA" << std::endl;
                                if (planets[i]->getMovementParameters().m > planets[j]->getMovementParameters().m)
                                {
                                    delete planets[j];
                                    planets[j] = NULL;
                                }
                                else
                                {
                                    delete planets[i];
                                    planets[i] = NULL;
                                }
                            }
                        }
                    }
                }
            }

			time = 0;
		}

	/*	farmTransform.setRotation(glm::vec3(0.0, rotation, 0.0));
		farmTransform.update();
		modelShader.Update(&farmTransform, &camera);
		modelShader.updateLightning(glm::vec3(ambient, ambient, ambient), glm::vec3(diffuse, diffuse, diffuse), glm::vec3(specular, specular, specular));
		farmModel.draw();*/

        for (int i = 0; i < numberPlanets; i++){
            if (planets[i] != NULL)
                planets[i]->drawComplex(camera);
        }

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


/*
Parametry do podania przy tworzeniu planety:
-predkosc startowa
-kat startowy
-wysokosc startowa
-promien
-wektor rotacji

Klawisze do obslugi:
-C: wejscie w tryb tworzenia planety / wyjscie
-Enter: dodanie planety
-1: wybor planety

*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {


	//On/Off planet creation
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		if (!createModeFlag) {			
			createModeFlag = true;

			system("cls");
			displayInfo();
		}
		else {
			createModeFlag = false;

			system("cls");
			displayInfo();
		}
	}

	//Creation
	if (createModeFlag) {

		//Confirm
		if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
			createFlag = true;

			system("cls");
			displayInfo();
		}

		//Option select
		if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
			planetSelectionFlag = true;
			velocitySelectionFlag = false;
			angleSelectionFlag = false;
			highSelectionFlag = false;
			rotationFirstFlag = false;
			rotationSecondFlag = false;
			rotationThirdFlag = false;

			system("cls");
			displayInfo();
		}
		if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
			planetSelectionFlag = false;
			velocitySelectionFlag = true;
			angleSelectionFlag = false;
			highSelectionFlag = false;
			rotationFirstFlag = false;
			rotationSecondFlag = false;
			rotationThirdFlag = false;

			system("cls");
			displayInfo();
		}
		if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
			planetSelectionFlag = false;
			velocitySelectionFlag = false;
			angleSelectionFlag = true;
			highSelectionFlag = false;
			rotationFirstFlag = false;
			rotationSecondFlag = false;
			rotationThirdFlag = false;

			system("cls");
			displayInfo();
		}
		if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
			planetSelectionFlag = false;
			velocitySelectionFlag = false;
			angleSelectionFlag = false;
			highSelectionFlag = true;
			rotationFirstFlag = false;
			rotationSecondFlag = false;
			rotationThirdFlag = false;

			system("cls");
			displayInfo();
		}
		if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
			planetSelectionFlag = false;
			velocitySelectionFlag = false;
			angleSelectionFlag = false;
			highSelectionFlag = false;
			rotationFirstFlag = true;
			rotationSecondFlag = false;
			rotationThirdFlag = false;

			system("cls");
			displayInfo();
		}
		if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
			planetSelectionFlag = false;
			velocitySelectionFlag = false;
			angleSelectionFlag = false;
			highSelectionFlag = false;
			rotationFirstFlag = false;
			rotationSecondFlag = true;
			rotationThirdFlag = false;

			system("cls");
			displayInfo();
		}
		if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
			planetSelectionFlag = false;
			velocitySelectionFlag = false;
			angleSelectionFlag = false;
			highSelectionFlag = false;
			rotationFirstFlag = false;
			rotationSecondFlag = false;
			rotationThirdFlag = true;

			system("cls");
			displayInfo();
		}

		//Option edit
		if (planetSelectionFlag) {
			if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
				if (cPlanet >= 8) {
					cPlanet = 1;
				}
				else {
					cPlanet++;
				}

				system("cls");
				displayInfo();
			}
			if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
				if (cPlanet <= 1) {
					cPlanet = 8;
				}
				else {
					cPlanet--;
				}

				system("cls");
				displayInfo();
			}
		}
		else if (velocitySelectionFlag) {
			valueSelection(&cVStart, &cVStartAdd, key, action);
			/*if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
				cVStart += cVStartAdd;

				system("cls");
				displayInfo();
			}
			if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
				cVStart -= cVStartAdd;

				system("cls");
				displayInfo();
			}
			if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
				cVStartAdd /= 10;

				system("cls");
				displayInfo();
			}
			if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
				cVStartAdd *= 10;

				system("cls");
				displayInfo();
			}*/
		}
		else if (angleSelectionFlag) {
			valueSelection(&cStartingAngle, &cStartingAngleAdd, key, action);
		}
		else if (highSelectionFlag) {
			valueSelection(&cStartingHigh, &cStartingHighAdd, key, action);
		}
		else if (rotationFirstFlag) {
			valueSelection(&cRotation.x, &cRotationAdd, key, action);
		}
		else if (rotationSecondFlag) {
			valueSelection(&cRotation.y, &cRotationAdd, key, action);
		}
		else if (rotationThirdFlag) {
			valueSelection(&cRotation.z, &cRotationAdd, key, action);
		}
	}
}

void valueSelection(float* value, float* valueAdd ,int key, int action) {
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		*value += *valueAdd;

		system("cls");
		displayInfo();
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		*value -= *valueAdd;

		system("cls");
		displayInfo();
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		*valueAdd /= 10;

		system("cls");
		displayInfo();
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		*valueAdd *= 10;

		system("cls");
		displayInfo();
	}
}

void addNewPlanet(std::vector<Planet*>* planets, std::vector<Model*>* models, Shader *modelShader) {
	Planet* planet = new Planet(models->at(cPlanet), modelShader);
	planet->setLightningParameters(glm::vec3(0.1, 0.1, 0.1), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0));


	switch (cPlanet)
	{
	case GREEN:
		cRadius = 3.0;
		break;
	case SAND:
		cRadius = 1.5;
		break;
	case MOON:
		cRadius = 3.5;
		break;
	case EARTH:
		cRadius = 1.0;
		break;
	case VENUS:
		cRadius = 1.2;
		break;
	case BLUE:
		cRadius = 1.7;
		break;
	case PURPLE:
		cRadius = 2.5;
		break;
	case RED:
		cRadius = 0.5;
		break;
	}


	planet->setStartingParameters(cVStart, cStartingAngle, cStartingHigh * 1000, cRadius, cRotation);

	numberPlanets++;
	planets->push_back(planet);
	createFlag = false;
	std::cout << "\n\nPlanet added" << std::endl;
}

void displayInfo() {
	
	if (createModeFlag) {
		std::cout << "CREATION MODE ON\nKeys: 1-7: Select option\nEnter: Add planet\nKeys UP/DOWN/LEFT/RIGHT: Change values\n\n";

		//Print selected atribute
		std::cout << "Selected atribute: ";
		if (planetSelectionFlag) {
			std::cout << "Planet";
		}
		else if (velocitySelectionFlag) {
			std::cout << "Velocity";
		}
		else if (angleSelectionFlag) {
			std::cout << "Angle";
		}
		else if (highSelectionFlag) {
			std::cout << "High";
		}
		else if (rotationFirstFlag) {
			std::cout << "Rotation (x)";
		}
		else if (rotationSecondFlag) {
			std::cout << "Rotation (y)";
		}
		else if(rotationThirdFlag) {
			std::cout << "Rotation (z)";
		}

		std::cout << "\n\n";

		//Print planet
		std::cout << "[1]Planet: ";
		switch (cPlanet)
		{
		case GREEN:
			std::cout << "Green\n";
			break;
		case SAND:
			std::cout << "Sand\n";
			break;
		case MOON:
			std::cout << "Moon\n";
			break;
		case EARTH:
			std::cout << "Earth\n";
			break;
		case VENUS:
			std::cout << "Venus\n";
			break;
		case BLUE:
			std::cout << "Blue\n";
			break;
		case PURPLE:
			std::cout << "Purple\n";
			break;
		case RED:
			std::cout << "Red\n";
			break;
		}

		//Print velocity
		std::cout << "[2]Velocity: " << cVStart << " (" << cVStartAdd << ")\n";

		//Print angle
		std::cout << "[3]Angle: " << cStartingAngle << " (" << cStartingAngleAdd << ")\n";

		//Print High
		std::cout << "[4]High: " << cStartingHigh << " * 1000 (" << cStartingHighAdd << ")\n";

		//Print Rotation
		std::cout << "[5-7]Rotation: ( " << cRotation.x << ", " << cRotation.y << ", " << cRotation.z << " ) ( " << cRotationAdd << ")\n";
	}
}