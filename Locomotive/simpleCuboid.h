#pragma once

#ifndef SIMPLECUBOID_H
#define SIMPLECUBOID_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shprogram.h"
//#include "textureLoader.h"




class SimpleCuboid {

protected:
	float width;
	float height;
	float length;
	glm::vec3 position;
	glm::vec3 translation;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	float *vertices;
	unsigned int texture;
	std::string textureName;
	//Shader shader;

	unsigned int *indices;

public:
	SimpleCuboid() :width(0), height(0), length(0), position(0, 0, 0), translation(0, 0, 0) {};
	SimpleCuboid(glm::vec3 position, float width, float height, float length);
	void draw(Shader shader, glm::mat4 model);
	void setValues(glm::vec3 position, float width, float height, float length);
	~SimpleCuboid();
	void setTranslation(glm::vec3 translation) { this->translation = translation; }
	void setPosition(glm::vec3 position) { this->position = position; }
	void setPositionX(float x) { position.x = x; }
	void setPositionY(float y) { position.y = y; }
	void setPositionZ(float z) { position.z = z; }
	void setTranslationX(float x) { translation.x = x; }
	void setTranslationY(float y) { translation.y = y; }
	void setTranslationZ(float z) { translation.z = z; }
	glm::vec3 getPosition() { return position; }


private:
	void generateVerticesArray(glm::vec3 position, unsigned int vertSize);

};


#endif // !SIMPLECUBOID_H