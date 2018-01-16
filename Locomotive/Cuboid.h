#pragma once

#ifndef CUBOID_H
#define CUBOID_H

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




class Cuboid {

	float width;
	float height;
	float length;
	glm::vec3 positon;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	float vertices[120];
	unsigned int texture;
	std::string textureName;
	//Shader shader;

	unsigned int indices[36];

public:
	Cuboid() :width(0), height(0), length(0), positon(0, 0, 0) {};
	Cuboid(glm::vec3 position, float width, float height, float length, std::string textureName, float *texCoord);
	void draw(Shader &shader);
	void draw(Shader &shader, unsigned int winWidth, unsigned int winHeight);
	void draw(Shader shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	void setValues(glm::vec3 position, float width, float height, float length, std::string textureName, float *textCoord);
	~Cuboid();

private:
	void generateVerticesArray(glm::vec3 position, unsigned int vertSize, float*texCoord);

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


#endif // !CUBOID_H