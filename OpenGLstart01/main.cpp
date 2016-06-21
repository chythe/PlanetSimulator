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
#include <vector>

//SFML - GUI
#include "SFML\Graphics.hpp"
#include "SFGUI\SFGUI.hpp"
#include "SFGUI\Widgets.hpp"


//GUI m_gui;

int window_width = 800;
int window_height = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void window_size_callback(GLFWwindow* window, int width, int height);
void CursorPositionCallback(GLFWwindow* window, double cursorPositionX,double cursorPositionY);


void addPlanet(std::vector<Planet*>* planets, std::vector<Model*>* models, Shader* modelShader);

void addPlanetClick();

double previousTime;
double actualTime;
double elapsedTime;
Camera camera;
Keyboard keyboard;
Mouse mouse;

int numberModels = 4;
int numberPlanets = 4;

bool addNewPlanet = false;

enum Type {
    SUN, GREEN, SAND, MOON
};

int main(){

	//GUI
	sf::RenderWindow guiWindow;
	guiWindow.create(sf::VideoMode(300, 600), "Interface");

	

    Planet objPlanet();

	//inicjalizacja glfw
	if (!glfwInit()){
		std::cout << "Error during glfw initiation";
		glfwTerminate();
		return 1;
	}

	guiWindow.resetGLStates();

	sfg::SFGUI sfgui;
	//auto button = sfg::Button::Create("Hello");

	//button->GetSignal(sfg::Button::OnLeftClick).Connect(
	//	std::bind(&addPlanetClick)
	//	);

	auto sfWindow = sfg::Window::Create();
	sfWindow->SetTitle("Hello World example");

	guiWindow.setActive(true);

	//sfWindow->Add(button);

	sfg::Desktop desktop;
	desktop.Add(sfWindow);

	//USTAWIENIA OKNA   opcja(jest to enum),wartoœæ jak¹ chcemy ustawiæ
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	//Poni¿ej tworzeenie okna z wczytaniem maksymalnych rozmiarów ekranu
	//const GLFWvidmode* video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	//GLFWwindow* window = glfwCreateWindow(video_mode->width, video_mode->height, "GL Window", glfwGetPrimaryMonitor(), NULL);
	//tworzenie okna 
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
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


	//GUI
	//m_gui.init("GUI");
	//m_gui.loadScheme("WindowsLook.scheme");
	//m_gui.setFont("DejaVuSans-10");
	//m_gui.createWidget("WindowsLook/FrameWindow", glm::vec4(0.5f, 0.5f, 0.1f, 0.05f), glm::vec4(0.0f), "TestButton");
	


	
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


    planets[GREEN]->setStartingParameters(4.5 * 1000, 0, 100, 3.0, glm::vec3(0.002, 0, 0)); //green //100
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



	


	bool guiClosed = false;
	

	while (!glfwWindowShouldClose(window) && !guiClosed)
	{
		//GUI
		guiWindow.setActive(true);
		sf::Event event;
		while (guiWindow.pollEvent(event)) {
			desktop.HandleEvent(event);

			if (event.type == sf::Event::Closed) {
				guiWindow.close();
				guiClosed = true;
			}
		}

		desktop.Update(1.0f);

		guiWindow.clear();
		sfgui.Display(guiWindow);
		guiWindow.display();



		//OpenGL
		glfwMakeContextCurrent(window);

		if (addNewPlanet) {
			addPlanet(&planets, &models, &modelShader);
			addNewPlanet = false;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // to konfiguruje kolor jaki uzyskamy po wywo³aniu glClear
		glViewport(0, 0, window_width, window_height); // aktualizacja rozmiaru rzutni

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
		
            /*for (int i = 0; i < numberPlanets; i++)
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
            }*/

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
		//

		keyboard.moveCamera(camera, window, elapsedTime);
		mouse.moveCamera(window, camera, elapsedTime);
		
		
		glfwSwapBuffers(window);// will swap the color buffer(a large buffer that contains color values for each pixel in GLFW's window) that has been used to draw in during this iteration and show it as output to the screen. 
		glfwPollEvents(); //function checks if any events are triggered and calls the corresponding functions (which we can set via callback methods). We usually call eventprocessing functions at the start of a loop iteration.
	}

	//glfwTerminate(); // zamykamy wszystkie utworzone przez glfw zasoby


//	system("pause");
	return 0;
	
}

void addPlanetClick() {
	addNewPlanet = true;
}

void addPlanet(std::vector<Planet*>* planets, std::vector<Model*>* models, Shader *modelShader) {
	Planet* planet = new Planet(models->at(GREEN), modelShader);
	planet->setLightningParameters(glm::vec3(0.1, 0.1, 0.1), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0));
	planet->setStartingParameters(4.5 * 1000, 0, 100, 3.0, glm::vec3(0.002, 0, 0));
	numberPlanets++;
	planets->push_back(planet);
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