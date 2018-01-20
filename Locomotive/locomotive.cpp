#include "locomotive.h"


Locomotive::Locomotive() {
	position = glm::vec3(0, 0, 0);
	body = new Cuboid(glm::vec3(0, 0, 0), 0.8, 0.2, 0.5, "deska.png", BODY_TEX_COORD);
	wheels = new Cylinder[WHEELS_COUNT];
	wheels[0].setValues(glm::vec3(0.1, 0.1, 0.1), 0.15, 0.1, WHEEL_PIECES, "kolo.jpg", "black.png");
	wheels[1].setValues(glm::vec3(0.7, 0.1, 0.1), 0.15, 0.1, WHEEL_PIECES, "kolo.jpg", "black.png");
	wheels[2].setValues(glm::vec3(0.1, 0.1, -0.5), 0.15, 0.1, WHEEL_PIECES, "kolo.jpg", "black.png");
	wheels[3].setValues(glm::vec3(0.7, 0.1, -0.5), 0.15, 0.1, WHEEL_PIECES, "kolo.jpg", "black.png");
	balks = new Cuboid[BALKS_COUNT];
	balks[0].setValues(glm::vec3(0, 0, 0), 1.2, 0.05, 0.05, "deska.png", BALK_TEX_COORD);
	balks[1].setValues(glm::vec3(0, 0, 0.5), 1.2, 0.05, 0.05, "deska.png", BALK_TEX_COORD);
	speedMultiplier = deltaTime = 0;
	//translation = glm::vec3(0);
}

/*
* width - body width (body is cuboid)
* height - body height
* length - body length
* radius - wheel radius
*/
Locomotive::Locomotive(float width, float height, float length, float radius) {
	position = glm::vec3(START_X, START_Y, START_Z);
	body = new Cuboid(glm::vec3(0, 0, 0), length, height, width, BODY_TEX_NAME, BODY_TEX_COORD);
	wheels = new Cylinder[WHEELS_COUNT];
	wheels[0].setValues(glm::vec3((-length + radius) / 2, (-height + radius) / 2, (width + WHEEL_WIDTH) / 2), radius, WHEEL_WIDTH, WHEEL_PIECES, WHEEL_TEX_NAME1, WHEEL_TEX_NAME2);
	wheels[1].setValues(glm::vec3((length - radius) / 2, (-height + radius) / 2, (width + WHEEL_WIDTH) / 2), radius, WHEEL_WIDTH, WHEEL_PIECES, WHEEL_TEX_NAME1, WHEEL_TEX_NAME2);
	wheels[2].setValues(glm::vec3((-length + radius) / 2, (-height + radius) / 2, (-width - WHEEL_WIDTH) / 2), radius, WHEEL_WIDTH, WHEEL_PIECES, WHEEL_TEX_NAME1, WHEEL_TEX_NAME2);
	wheels[3].setValues(glm::vec3((length - radius) / 2, (-height + radius) / 2, (-width - WHEEL_WIDTH) / 2), radius, WHEEL_WIDTH, WHEEL_PIECES, WHEEL_TEX_NAME1, WHEEL_TEX_NAME2);
	balks = new Cuboid[BALKS_COUNT];
	balks[0].setValues(glm::vec3(0, (-height + radius) / 2, width / 2 + WHEEL_WIDTH + BALK_WIDTH / 2), length - radius, BALK_HEIGHT, BALK_WIDTH, BALK_TEX_NAME, BALK_TEX_COORD);
	balks[1].setValues(glm::vec3(0, (-height + radius) / 2, -width / 2 - WHEEL_WIDTH - BALK_WIDTH / 2), length - radius, BALK_HEIGHT, BALK_WIDTH, BALK_TEX_NAME, BALK_TEX_COORD);
	moveX(0);
	for (int i = 0; i < BALKS_COUNT; ++i) {
		balks[i].setTranslationX(-(wheels->getRadius() - BALK_HEIGHT)*sin(wheels->getRotation()));
		balks[i].setTranslationY((wheels->getRadius() - BALK_HEIGHT)*cos(wheels->getRotation()));
	}
	speedMultiplier = deltaTime = 0;
//	translation = glm::vec3(0);
}


void Locomotive::draw(Shader shader, glm::mat4 model) {
	//glm::mat4 model;
	if (speedMultiplier != 0) {
		float move = speedMultiplier * deltaTime;
		//move *= SPEED_MULTTIPLIER;
		position.x += move;
		for (int i = 0; i < WHEELS_COUNT; ++i)
			wheels[i].rotateX(-move / wheels[i].getRadius());
		//int cosSign = 1;
		//if (cos(wheels[0].getRotation()) < 0)
		//	cosSign = -1;

		for (int i = 0; i < BALKS_COUNT; ++i) {
			balks[i].setTranslationX(-(wheels->getRadius() - BALK_HEIGHT)*sin(wheels->getRotation()));
			balks[i].setTranslationY((wheels->getRadius() - BALK_HEIGHT)*cos(wheels->getRotation()));
		}

	}

	model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
	model = glm::translate(model, position);

	body->draw(shader, model);
	for (int i = 0; i < WHEELS_COUNT; ++i)
		wheels[i].draw(shader, model);
	for (int i = 0; i < BALKS_COUNT; ++i)
		balks[i].draw(shader, model);

	
}

void Locomotive::moveX(float move) {
	speedMultiplier += move;
	//move *= SPEED_MULTTIPLIER;
	//position.x += move;
	//for (int i = 0; i < WHEELS_COUNT; ++i)
	//	wheels[i].rotateX(-move / wheels[i].getRadius());
	//int cosSign = 1;
	//if (cos(wheels[0].getRotation()) < 0)
	//	cosSign = -1;

	//for (int i = 0; i < BALKS_COUNT; ++i) {
	//	balks[i].setTranslationX(-(wheels->getRadius() - BALK_HEIGHT)*sin(wheels->getRotation()));
	//	balks[i].setTranslationY((wheels->getRadius() - BALK_HEIGHT)*cos(wheels->getRotation()));
	//}
}

Locomotive::~Locomotive() {
	delete body;
	delete[] wheels;
	delete[] balks;
}