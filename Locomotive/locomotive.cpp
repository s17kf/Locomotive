#include "locomotive.h"

unsigned int wheelPieces = 24;
float bodyTexCoord[] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 5.0, 1.0, 5.0 };
float balkTexCoord[] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
unsigned int wheelsCount = 4;
unsigned int balksCount = 2;
float wheelWidth = 0.1;
float balkWidth = 0.05;
float balkHeight = 0.05;

Locomotive::Locomotive() {
	position = glm::vec3(0, 0, 0);
	body = new Cuboid(glm::vec3(0, 0, 0), 0.8, 0.2, 0.5, "deska.png", bodyTexCoord);
	wheels = new Cylinder[wheelsCount];
	wheels[0].setValues(glm::vec3(0.1, 0.1, 0.1), 0.15, 0.1, wheelPieces, "kolo.jpg", "black.png");
	wheels[1].setValues(glm::vec3(0.7, 0.1, 0.1), 0.15, 0.1, wheelPieces, "kolo.jpg", "black.png");
	wheels[2].setValues(glm::vec3(0.1, 0.1, -0.5), 0.15, 0.1, wheelPieces, "kolo.jpg", "black.png");
	wheels[3].setValues(glm::vec3(0.7, 0.1, -0.5), 0.15, 0.1, wheelPieces, "kolo.jpg", "black.png");
	balks = new Cuboid[balksCount];
	balks[0].setValues(glm::vec3(0, 0, 0), 1.2, 0.05, 0.05, "deska.png", balkTexCoord);
	balks[1].setValues(glm::vec3(0, 0, 0.5), 1.2, 0.05, 0.05, "deska.png", balkTexCoord);
}

/*
* width - body width (body is cuboid)
* height - body height
* length - body length
* radius - wheel radius
*/
Locomotive::Locomotive(float width, float height, float length, float radius, std::string bodyTexName, std::string wheelTexName1, std::string wheelTexName2) {
	position = glm::vec3(0, 0, 0);
	body = new Cuboid(glm::vec3(0, 0, 0), length, height, width, bodyTexName, bodyTexCoord);
	wheels = new Cylinder[wheelsCount];
	wheels[0].setValues(glm::vec3(radius / 2, radius / 2, wheelWidth), radius, wheelWidth, wheelPieces, wheelTexName1, wheelTexName2);
	wheels[1].setValues(glm::vec3(length - radius / 2, radius / 2, wheelWidth), radius, wheelWidth, wheelPieces, wheelTexName1, wheelTexName2);
	wheels[2].setValues(glm::vec3(radius / 2, radius / 2, -width), radius, wheelWidth, wheelPieces, wheelTexName1, wheelTexName2);
	wheels[3].setValues(glm::vec3(length - radius / 2, radius / 2, -width), radius, wheelWidth, wheelPieces, wheelTexName1, wheelTexName2);
	balks = new Cuboid[balksCount];
	balks[0].setValues(glm::vec3(0, 0, wheelWidth + balkWidth), length - radius, balkHeight, balkWidth, "black.jpg", balkTexCoord);
	balks[1].setValues(glm::vec3(0, 0, -width - wheelWidth), length - radius, balkHeight, balkWidth, "black.jpg", balkTexCoord);
	moveX(0);
	

}


void Locomotive::draw(Shader shader, unsigned int winWidth, unsigned int winHeight) {
	glm::mat4 model;
	//model = glm::rotate(model, glm::radians(95.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, position);
	//model = glm::translate(model, glm::vec3((float)glfwGetTime() / 20, 0,/* 0*/ (float)glfwGetTime() / 20));
	//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//model = glm::translate(model, glm::vec3((float)glfwGetTime() / -20, 0,/* 0*/ (float)glfwGetTime() / 20));
	model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));


	//!!!obsluga kamery w mainie
	//glm::mat4 view;
	//// note that we're translating the scene in the reverse direction of where we want to move
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.6f));
	//view = glm::rotate(view, glm::radians(30.f), glm::vec3(1.0, 1.0, 0.0));

	//glm::mat4 projection;
	//projection = glm::perspective(glm::radians(45.0f), (GLfloat)winWidth / (GLfloat)winHeight, 0.1f, 100.0f);

	body->draw(shader, model);
	for (int i = 0; i < wheelsCount; ++i)
		wheels[i].draw(shader, model);
	for (int i = 0; i < balksCount; ++i)
		balks[i].draw(shader, model);
}

void Locomotive::moveX(float move) {
	position.x += move;
	for (int i = 0; i < wheelsCount; ++i)
		wheels[i].rotate(-move / wheels[i].getRadius());
	int cosSign = 1;
	if (cos(wheels[0].getRotation()) < 0)
		cosSign = -1;

	for (int i = 0; i < balksCount; ++i) {
		balks[i].setPositionX(wheels->getRadius()/2);
		balks[i].setPositionY(wheels->getRadius()/2-balkHeight/2);
		balks[i].setTranslationX(-(wheels->getRadius() - balkHeight)*sin(wheels->getRotation()));
		balks[i].setTranslationY((wheels->getRadius() - balkHeight)*cos(wheels->getRotation()));
	}

}

Locomotive::~Locomotive() {
	delete body;
	delete[] wheels;
	delete[] balks;
}