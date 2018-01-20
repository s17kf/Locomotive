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
	Locomotive(float width, float height, float length, float radius);
	~Locomotive();
	void draw(Shader shader, glm::mat4 model);
	void moveX(float move);






};








#endif // !LOKOMTYWA_H
