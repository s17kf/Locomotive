#pragma once

#ifndef TREE_H
#define TREE_H

#include "Cylinder.h"
#include "Const.h"


class Tree {
	glm::vec3 position;
	unsigned int crownLevelsCount;
	Cylinder *trunk;
	Cylinder *crown;

public:
	Tree() :position(0), crownLevelsCount(0) {}
	Tree(glm::vec3 position, float height, float trunkRadius, unsigned int crownLevelCount, std::string trunkTex, std::string crownTex);
	void setValues(glm::vec3 position, float height, float trunkRadius, unsigned int crownLevelCount, std::string trunkTex, std::string crownTex);
	~Tree();
	void draw(Shader shader, glm::mat4 model);
	

};



#endif // !TREE_H
