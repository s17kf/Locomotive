#include "Cylinder.h"

Cylinder::Cylinder(glm::vec3 position, float radius, float height, unsigned int pieces, std::string textureBaseName, std::string textureSideName) {
	setValues(position, radius, height, pieces, textureBaseName, textureSideName);
}

void Cylinder::setValues(glm::vec3 position, float radius, float height, unsigned int pieces, std::string textureBaseName, std::string textureSideName) {
	this->radius = radius;
	bases = new CylinderBases(position, radius, height, pieces, textureBaseName);
	side = new CylinderSide(position, radius, height, pieces, textureSideName);
	this->position = position;
}

void Cylinder::draw(Shader shader, glm::mat4 model) {
	//model = glm::translate(model, position);
	//model = glm::rotate(model, rotation, glm::vec3(0, 0, 1));

	//shader.setMat4("model", model);

	bases->draw(shader, model);
	side->draw(shader, model);
}

Cylinder::~Cylinder() {
	delete bases;
	delete side;
}

void Cylinder::rotateX(float angle) { 
	bases->rotateX(angle);
	side->rotateX(angle);
}