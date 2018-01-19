#include "Cylinder.h"

Cylinder::Cylinder(glm::vec3 position, float radius, float height, unsigned int pieces, std::string textureBaseName, std::string textureSideName) {
	setValues(position, radius, height, pieces, textureBaseName, textureSideName);
}

void Cylinder::setValues(glm::vec3 position, float radius, float height, unsigned int pieces, std::string textureBaseName, std::string textureSideName) {
	rotation = 0;
	this->radius = radius;
	bases = new CylinderBases(position, radius, height, pieces, textureBaseName);
	side = new CylinderSide(position, radius, height, pieces, textureSideName);
	this->position = position;
}

void Cylinder::draw(Shader &shader) {
	bases->draw(shader);
	side->draw(shader);
}

void Cylinder::draw(Shader &shader, unsigned int winWidth, unsigned int winHeight) {
	//glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 model;
	//model = glm::rotate(model, glm::radians(95.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, position);
	model = glm::translate(model, glm::vec3((float)glfwGetTime() / 20, 0,/* 0*/ (float)glfwGetTime() / 20));
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));

	glm::mat4 view;
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (GLfloat)winWidth / (GLfloat)winHeight, 0.1f, 100.0f);

	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	bases->draw(shader);
	side->draw(shader);
}

void Cylinder::draw(Shader shader, glm::mat4 model) {
	model = glm::translate(model, position);
	model = glm::rotate(model, rotation, glm::vec3(0, 0, 1));

	shader.setMat4("model", model);

	bases->draw(shader);
	side->draw(shader);
}

void Cylinder::draw(Shader shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
	model = glm::translate(model, position);
	//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, rotation, glm::vec3(0, 0, 1));

	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	bases->draw(shader);
	side->draw(shader);
}

Cylinder::~Cylinder() {
	delete bases;
	delete side;
}
