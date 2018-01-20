#pragma once

#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "shprogram.h"

class Skybox {
	unsigned int VAO;
	unsigned int VBO;
	unsigned int cubemapTexture;
	float *vertices;



public:
	Skybox(std::vector<std::string> skyboxTexNames);
	~Skybox() { delete[] vertices; }
	void draw(Shader shader, glm::mat4 model);


private:
	unsigned int loadCubemap(std::vector<std::string> faces) {
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrChannels;
		for (int i = 0; i < faces.size(); ++i) {
			unsigned char* data = SOIL_load_image(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				SOIL_free_image_data(data);
			}
			else {
				std::cout << "Cubemap texture failed to load path: " << faces[i] << std::endl;
				SOIL_free_image_data(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return textureID;
	}


};



#endif // !SKYBOX_H
