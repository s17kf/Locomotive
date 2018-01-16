#pragma once


#ifndef CYLINDERSIDE_H
#define CYLINDERSIDE_H

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




class CylinderSide {

	float radius;
	float height;
	unsigned int pieces;
	unsigned int indicesCount;
	glm::vec3 positon;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	std::string textureName;
	unsigned int texture;
	//Shader shader;
	float *vertices;
	unsigned int *indices;


public:
	CylinderSide() :radius(0), height(0), pieces(0), positon(0, 0, 0) {};
	CylinderSide(glm::vec3 position, float radius, float height, unsigned int pieces, std::string textureName);
	void draw(Shader &shader);
	void draw(Shader &shader, unsigned int winWidth, unsigned int winHeight);
	//	void setValues(glm::vec3 position, float width, float height, float length, std::string textureName, float *textCoord);
	~CylinderSide();

private:
	void generateVerticesArray(unsigned int vertSize);
	void generateIndicesArray();

	GLuint LoadMipmapTexture(GLuint texId, const char* fname)
	{
		int width, height;
		unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
		if (image == nullptr)
			throw std::exception("Failed to load texture file");

		GLuint texture;
		glGenTextures(1, &texture);

		glActiveTexture(texId);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
		return texture;
	}
};



#endif // !CYLINDERSIDE_H
