#define GLEW_STATIC
//#include <glad/glad.h>
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Cuboid.h"
#include "Cylinder.h"
#include "locomotive.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
//GLuint LoadMipmapTexture(GLuint texId, const char* fname);

const GLuint WIDTH = 800, HEIGHT = 600;

float deltaTime = 0;
float lastFrame = 0;


Locomotive *locomotive;


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	////glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw exception("GLEW Initialization failed");

	glViewport(0, 0, WIDTH, HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader ourShader("locomotive.vert", "locomotive.frag");
	//Shader cylinderShader("locomotive.vert", "locomotive.frag");

	float cuboid1TexCoord[] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
	float cuboid2TexCoord[] = { 3.0, 1.0, 3.0, 5.0, 1.0, 5.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

	//CylinderBases cylinderBases(glm::vec3(0.1, 0.1, 0.1), 0.15, 0.1, 24, "kolo.jpg");
	
	locomotive = new Locomotive(0.5, 0.2, 0.8, 0.15, "deska.png", "kolo.jpg", "black.jpg");
	//Locomotive lokomotywa2;
	//main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		processInput(window);

		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		cout << deltaTime << endl;

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//cylinderBases.draw(ourShader, WIDTH, HEIGHT);

		locomotive->draw(ourShader, WIDTH, HEIGHT);
		//lokomotywa2.draw(ourShader, WIDTH, HEIGHT);
		//cuboid.draw(ourShader);
		//cuboid1.draw(ourShader, WIDTH, HEIGHT);
		//cuboid2.draw(ourShader, WIDTH, HEIGHT);
		//cuboid3.draw(ourShader, WIDTH, HEIGHT);
		//for (int i = 0; i < 10; ++i)
		//	cylinders[i].draw(ourShader, WIDTH, HEIGHT);
		//cylinder.draw(ourShader, WIDTH, HEIGHT);

		glfwSwapBuffers(window);
	}


	glfwTerminate();

	delete locomotive;

	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		locomotive->moveX(-deltaTime);
		//camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		locomotive->moveX(deltaTime);
		//camera.ProcessKeyboard(RIGHT, deltaTime);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	cout << "resizing" << endl;
}

//GLuint LoadMipmapTexture(GLuint texId, const char* fname)
//{
//	int width, height;
//	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
//	if (image == nullptr)
//		throw exception("Failed to load texture file");
//
//	GLuint texture;
//	glGenTextures(1, &texture);
//
//	glActiveTexture(texId);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	return texture;
//}