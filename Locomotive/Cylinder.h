#pragma once


#ifndef CYLINDER_H
#define CYLINDER_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shprogram.h"
#include "cylinderBases.h"
#include "cylinderSide.h"
//#include "textureLoader.h"




class Cylinder {

	//unsigned int VAO;
	//unsigned int VBO;
	//unsigned int EBO;
	//std::string textureBaseName;
	//std::string textureSideName;
	//unsigned int textureBase;
	//unsigned int textureSide;
	CylinderBases *bases;
	CylinderSide *side;
	glm::vec3 position;
	float rotation;


public:
	Cylinder() :rotation(0) {};
	Cylinder(glm::vec3 position, float radius, float height, unsigned int pieces, std::string textureBaseName, std::string textureSideName);
	void draw(Shader &shader);
	void draw(Shader &shader, unsigned int winWidth, unsigned int winHeight);
	void draw(Shader shader, glm::mat4 model);
	void draw(Shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	void setValues(glm::vec3 position, float radius, float height, unsigned int pieces, std::string textureBaseName, std::string textureSideName);
//	void setValues(glm::vec3 position, float width, float height, float length, std::string textureName, float *textCoord);
	~Cylinder();
	void rotate(float angle) {
		rotation += angle;
	}
private:
};



#endif // !CYLINDER_H
