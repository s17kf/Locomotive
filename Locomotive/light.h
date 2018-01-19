#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include "simpleCuboid.h"


class Light: public SimpleCuboid{

public:
	Light() :SimpleCuboid() {}
	Light(glm::vec3 position, float width, float height, float length) : SimpleCuboid(position, width, height, length) {}
	void moveX(float move) { position.x += move; }
	void moveY(float move) { position.y += move; }
	void moveZ(float move) { position.z += move; }


};


#endif // !LIGHT_H
