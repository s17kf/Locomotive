#pragma once

#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include "Const.h"
#include "Cuboid.h"
#include "Cylinder.h"


class Locomotive {
	glm::vec3 position;
	Cuboid *body;
	Cylinder *wheels;
	Cuboid *balks;

public:
	Locomotive();
	Locomotive(float width, float height, float length, float radius, std::string bodyTexName, std::string wheelTexName1, std::string wheelTexName2);
	~Locomotive();
	void draw(Shader shader, unsigned int winWidth, unsigned int winHeight);
	void moveX(float move);






};








#endif // !LOKOMTYWA_H
