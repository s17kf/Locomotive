#define GLEW_STATIC
//#include <glad/glad.h>
#include "Const.h"
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <ctime>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Cuboid.h"
#include "Cylinder.h"
#include "locomotive.h"
#include "camera.h"
#include "simpleCuboid.h"
#include "light.h"
#include "tree.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void setLightParameters(Shader &shader);

const GLuint WIDTH = 800, HEIGHT = 600;

//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Camera camera(glm::vec3(-0.3f, 0.5f, 1.6f), glm::vec3(0.0,1.0,0.0),YAW+10, -10);
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0;
float lastFrame = 0;


Locomotive *locomotive;
Light *lamp;


int main()
{
	srand(time(NULL));
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

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader ourShader("locomotive.vert", "locomotive.frag");
	Shader lampShader("light.vert", "light.frag");
	Shader lightedObjectShader("lightedObject.vert", "lightedObject.frag");

	//lightedObjectShader.use();
	lightedObjectShader.setInt("material.diffuse", 0);
	//Shader cylinderShader("locomotive.vert", "locomotive.frag");

	float cuboid1TexCoord[] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
	float cuboid2TexCoord[] = { 3.0, 1.0, 3.0, 5.0, 1.0, 5.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

	//CylinderBases cylinderBases(glm::vec3(0.1, 0.1, 0.1), 0.15, 0.1, 24, "kolo.jpg");
	
	locomotive = new Locomotive(0.5, 0.2, 0.8, 0.15);
	lamp = new Light(glm::vec3(0, 0.5, 0), 0.02, 0.02, 0.02);

	Tree *tree = new Tree[TREES_COUNTER_1];
	for (int i = 0; i < TREES_COUNTER_1; ++i) {
		int z = rand() % 10;
		tree[i].setValues(glm::vec3(8 - i * 15, 0, z < 7 ? -10 : 5), 8, 1, TREE_CROWN_LEVELS_C, TREE_TRUNK_TEX, TREE_CROWN_TEX);
	}

	//Cuboid *lightedCuboid = new Cuboid(glm::vec3(-1, 2, -1), 0.5, 0.6, 0.4, "deska.png", BALK_TEX_COORD);
	//Cylinder *lightedCylinder = new Cylinder(glm::vec3(1, 2, -1), 0.6, 0.2, 12, "kolo.jpg", "black2.jpg");
	//lamp - new Light();
	//Locomotive lokomotywa2;
	//main loop
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		processInput(window);

		//cout << deltaTime << endl;

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//cylinderBases.draw(ourShader, WIDTH, HEIGHT);

		// camera/view transformation
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);
		// pass projection matrix to shader
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		ourShader.use();
		ourShader.setMat4("projection", projection);

		ourShader.setMat4("view", view);
		lightedObjectShader.use();
		lightedObjectShader.setMat4("view", view);
		lightedObjectShader.setMat4("projection", projection);
		setLightParameters(lightedObjectShader);
		locomotive->draw(lightedObjectShader, WIDTH, HEIGHT);

		lampShader.use();
		lampShader.setMat4("view", view);
		lampShader.setMat4("projection", projection);
		glm::mat4 model;// = glm::mat4();
		//model = glm::scale(model, glm::vec3(0.2));
		lamp->draw(lampShader, model);
		
		lightedObjectShader.use();
		lightedObjectShader.setMat4("view", view);
		lightedObjectShader.setMat4("projection", projection);
		for(int i=0;i<TREES_COUNTER_1;++i)
			tree[i].draw(lightedObjectShader, glm::mat4());

		
		//lightedObjectShader.setMat4("view", view);
		//lightedObjectShader.setMat4("projection", projection);
		//model = glm::scale(model, glm::vec3(0.2));
		//lightedCuboid->draw(lightedObjectShader, model);
		//lightedCylinder->draw(lightedObjectShader, model);
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
	delete lamp;
	delete[] tree;
	//delete lightedCuboid;
	//delete lightedCylinder;

//	system("PAUSE");
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	//locomotive move
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		locomotive->moveX(-deltaTime);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		locomotive->moveX(deltaTime);

	//camera move
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime); 
	
	//light move
	if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
		lamp->moveX(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
		lamp->moveX(-deltaTime);
	if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
		lamp->moveY(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS)
		lamp->moveY(-deltaTime);
	if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
		lamp->moveZ(-deltaTime);
	if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
		lamp->moveZ(deltaTime);

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	cout << "resizing" << endl;
}

void setLightParameters(Shader& shader) {
	shader.setVec3("lightPos", lamp->getPosition());
	shader.setVec3("lightColor", glm::vec3(1));
	//shader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	//shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	//shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	//shader.setFloat("material.shininess", 32.0f);

	//// light properties
	//shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	//shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	//shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	//shader.setVec3("lightPos", lamp->getPosition());
	//shader.setVec3("viewPos", camera.Position);

	////shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	////shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
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