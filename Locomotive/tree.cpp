#include "tree.h"

Tree::Tree(glm::vec3 position, float height, float trunkRadius, unsigned int crownLevelsCount, std::string trunkTex, std::string crownTex) {
	setValues(position, height, trunkRadius, crownLevelsCount, trunkTex, crownTex);

}

Tree::~Tree() {
	delete trunk;
	delete[] crown;
}

void Tree::setValues(glm::vec3 position, float height, float trunkRadius, unsigned int crownLevelsCount, std::string trunkTex, std::string crownTex) {
	this->position = position;
	this->crownLevelsCount = crownLevelsCount;
	trunk = new Cylinder(glm::vec3(0, 0, -height / 2), trunkRadius, height, TREE_TRUNK_PIECES, trunkTex, trunkTex);
	crown = new Cylinder[crownLevelsCount];
	for (int i = 0; i < crownLevelsCount; ++i)
		crown[i].setValues(glm::vec3(0, 0,(-height*2/3 - i/6.0* height)), 2*(3 - i * 0.5)*trunkRadius, height / (crownLevelsCount+1), TREE_CROWN_PIECES, crownTex, crownTex);
}

void Tree::draw(Shader shader, glm::mat4 model) {
	model = glm::scale(model, glm::vec3(0.1));
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1,0,0));
	trunk->draw(shader, model);
	for (int i = 0; i < crownLevelsCount; ++i)
		crown[i].draw(shader, model);
}