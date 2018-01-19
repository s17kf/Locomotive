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
	Cuboid() :width(0), height(0), length(0), position(0, 0, 0), translation(0, 0, 0) {};
	Cuboid(glm::vec3 position, float width, float height, float length, std::string textureName, float *texCoord);
	void draw(Shader &shader);
	void draw(Shader &shader, unsigned int winWidth, unsigned int winHeight);
	void draw(Shader shader, glm::mat4 model);
	void draw(Shader shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	void setValues(glm::vec3 position, float width, float height, float length, std::string textureName, float *textCoord);
	~Cuboid();
	void setTranslation(glm::vec3 translation) { this->translation = translation; }
	void setPosition(glm::vec3 position) { this->position = position; }
	void setPositionX(float x) { position.x = x; }
	void setPositionY(float y) { position.y = y; }
	void setPositionZ(float z) { position.z = z; }
	void setTranslationX(float x) { translation.x = x; }
	void setTranslationY(float y) { translation.y = y; }
	void setTranslationZ(float z) { translation.z = z; }
	

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