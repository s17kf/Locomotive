#include "Cuboid.h"

unsigned int indicesInitializer[] = {
	0, 1, 2,
	0, 2, 3,
	4, 5, 6,
	4, 6, 7,
	8, 9, 10,
	8, 10, 11,
	12, 13, 14,
	12, 14, 15,
	16, 17, 18,
	16, 18, 19,
	20, 21, 22,
	20, 22, 23
};

/*
* textCoord: {front side, back side, left, right, bottom, top side}
* for each side has two values: x and y ==> size of array is: 6*2=12
*/
Cuboid::Cuboid(glm::vec3 position, float width, float height, float length, std::string textureName, float *texCoord) {
	setValues(position, width, height, length, textureName, texCoord);
}

void Cuboid::setValues(glm::vec3 position, float width, float height, float length, std::string textureName, float *texCoord) {
	unsigned int vertSize = 5;

	this->position = position;
	this->textureName = textureName;
	this->width = width;
	this->height = height;
	this->length = length;

	translation = glm::vec3(0, 0, 0);

	std::cout << position.x << " " << position.y << " " << position.z << std::endl;
	std::cout << width << " " << height << " " << length << std::endl;

	generateVerticesArray(glm::vec3(0.0, 0.0, 0.0), vertSize, texCoord);

	for (int i = 0; i < 36; i++) {
		indices[i] = indicesInitializer[i];
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// 0. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	// vertex texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	texture = LoadMipmapTexture(GL_TEXTURE0, textureName.c_str());
}

void Cuboid::draw(Shader &shader) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader.getID(), "Texture"), 0);


	shader.use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void Cuboid::draw(Shader &shader, unsigned int winWidth, unsigned int winHeight) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader.getID(), "Texture"), 0);

	//glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 model;
	//model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model,position);
	model = glm::translate(model, glm::vec3((float)glfwGetTime() / 20, 0, (float)glfwGetTime() / 20));
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));

	glm::mat4 view;
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	//view = glm::rotate(view, glm::radians(10.f), glm::vec3(1.0, 1.0, 0.0));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (GLfloat)winWidth / (GLfloat)winHeight, 0.1f, 100.0f);

	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);


	shader.use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


}

void Cuboid::draw(Shader shader, glm::mat4 model) {

	//model = glm::translate(model, position + translation);
	model = glm::translate(model, translation);
	model = glm::translate(model, position);
	shader.setMat4("model", model);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader.getID(), "Texture"), 0);


	shader.use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Cuboid::draw(Shader shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader.getID(), "Texture"), 0);


	shader.use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
}


Cuboid::~Cuboid() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

/*
* textCoord: {front side, back side, left, right, bottom, top side}
* for each side has two values: x and y ==> size of array is: 6*2=12
*/
void Cuboid::generateVerticesArray(glm::vec3 position, unsigned int vertSize, float*texCoord) {
	//front side
	vertices[0] = vertices[3 * vertSize] = position.x;
	vertices[vertSize] = vertices[2 * vertSize] = position.x + width;
	vertices[1] = vertices[vertSize + 1] = position.y;
	vertices[2 * vertSize + 1] = vertices[3 * vertSize + 1] = position.y + height;
	vertices[2] = vertices[vertSize + 2] = vertices[2 * vertSize + 2] = vertices[3 * vertSize + 2] = position.z;
	//texture
	vertices[3] = vertices[3 * vertSize + 3] = 0.0;	//x left
	vertices[vertSize + 3] = vertices[2 * vertSize + 3] = texCoord[0];//x right
	vertices[4] = vertices[vertSize + 4] = 0.0f;//y bottom
	vertices[2 * vertSize + 4] = vertices[3 * vertSize + 4] = texCoord[1];//y top

	//back side
	vertices[4 * vertSize] = vertices[7 * vertSize] = position.x;
	vertices[5 * vertSize] = vertices[6 * vertSize] = position.x + width;
	vertices[4 * vertSize + 1] = vertices[5 * vertSize + 1] = position.y;
	vertices[6 * vertSize + 1] = vertices[7 * vertSize + 1] = position.y + height;
	vertices[4 * vertSize + 2] = vertices[5 * vertSize + 2] = vertices[6 * vertSize + 2] = vertices[7 * vertSize + 2] = position.z - length;
	//texture
	vertices[4 * vertSize + 3] = vertices[7 * vertSize + 3] = 0.0;	//x left
	vertices[5 * vertSize + 3] = vertices[6 * vertSize + 3] = texCoord[2];//x right
	vertices[4 * vertSize + 4] = vertices[5 * vertSize + 4] = 0.0;//y bottom
	vertices[6 * vertSize + 4] = vertices[7 * vertSize + 4] = texCoord[3];//y top

	//left side
	vertices[8 * vertSize] = vertices[9 * vertSize] = vertices[10 * vertSize] = vertices[11 * vertSize] = position.x;
	vertices[8 * vertSize + 1] = vertices[9 * vertSize + 1] = position.y;
	vertices[10 * vertSize + 1] = vertices[11 * vertSize + 1] = position.y + height;
	vertices[8 * vertSize + 2] = vertices[11 * vertSize + 2] = position.z;
	vertices[9 * vertSize + 2] = vertices[10 * vertSize + 2] = position.z - length;
	//texture
	vertices[9 * vertSize + 3] = vertices[10 * vertSize + 3] = 0.0;	//x left
	vertices[8 * vertSize + 3] = vertices[11 * vertSize + 3] = texCoord[4];//x right
	vertices[8 * vertSize + 4] = vertices[9 * vertSize + 4] = 0.0;//y bottom
	vertices[10 * vertSize + 4] = vertices[11 * vertSize + 4] = texCoord[5];//y top

	//right side
	vertices[12 * vertSize] = vertices[13 * vertSize] = vertices[14 * vertSize] = vertices[15 * vertSize] = position.x+width;
	vertices[12 * vertSize + 1] = vertices[13 * vertSize + 1] = position.y;
	vertices[14 * vertSize + 1] = vertices[15 * vertSize + 1] = position.y + height;
	vertices[12 * vertSize + 2] = vertices[15 * vertSize + 2] = position.z;
	vertices[13 * vertSize + 2] = vertices[14 * vertSize + 2] = position.z - length;
	//texture
	vertices[12 * vertSize + 3] = vertices[15 * vertSize + 3] = 0.0;	//x left
	vertices[13 * vertSize + 3] = vertices[14 * vertSize + 3] = texCoord[6];//x right
	vertices[12 * vertSize + 4] = vertices[13 * vertSize + 4] = 0.0;//y bottom
	vertices[14 * vertSize + 4] = vertices[15 * vertSize + 4] = texCoord[7];//y top

	//bottom side
	vertices[16 * vertSize] = vertices[19 * vertSize] = position.x;
	vertices[17 * vertSize] = vertices[18 * vertSize] = position.x+width;
	vertices[16 * vertSize + 1] = vertices[17 * vertSize + 1] = vertices[18 * vertSize + 1] = vertices[19 * vertSize + 1] = position.y;
	vertices[16 * vertSize + 2] = vertices[17 * vertSize + 2] = position.z;
	vertices[18 * vertSize + 2] = vertices[19 * vertSize + 2] = position.z - length;
	//texture
	vertices[16 * vertSize + 3] = vertices[19 * vertSize + 3] = 0.0;	//x left
	vertices[17 * vertSize + 3] = vertices[18 * vertSize + 3] = texCoord[8];//x right
	vertices[18 * vertSize + 4] = vertices[19 * vertSize + 4] = 0.0;//y bottom
	vertices[16 * vertSize + 4] = vertices[17 * vertSize + 4] = texCoord[9];//y top

	//top side
	vertices[20 * vertSize] = vertices[23 * vertSize] = position.x;
	vertices[21 * vertSize] = vertices[22 * vertSize] = position.x+width;
	vertices[20 * vertSize + 1] = vertices[21 * vertSize + 1] = vertices[22 * vertSize + 1] = vertices[23 * vertSize + 1] = position.y + height;
	vertices[20 * vertSize + 2] = vertices[21 * vertSize + 2] = position.z;
	vertices[22 * vertSize + 2] = vertices[23 * vertSize + 2] = position.z - length;
	//texture
	vertices[21 * vertSize + 3] = vertices[22 * vertSize + 3] = 0.0;	//x left
	vertices[20 * vertSize + 3] = vertices[23 * vertSize + 3] = texCoord[10];//x right
	vertices[22 * vertSize + 4] = vertices[23 * vertSize + 4] = 0.0;//y bottom
	vertices[20 * vertSize + 4] = vertices[21 * vertSize + 4] = texCoord[11];//y top
}




//vertices[0] = vertices[3 * vertSize] = vertices[4 * vertSize] = vertices[7 * vertSize] = position.x;	//left side
//vertices[vertSize] = vertices[2 * vertSize] = vertices[5 * vertSize] = vertices[6 * vertSize] = position.x + width;	//right side
//vertices[0 + 1] = vertices[vertSize + 1] = vertices[4 * vertSize + 1] = vertices[5 * vertSize + 1] = position.y;	//bottom side
//vertices[2 * vertSize + 1] = vertices[3 * vertSize + 1] = vertices[6 * vertSize + 1] = vertices[7 * vertSize + 1] = position.y + height;	//top side
//vertices[0 + 2] = vertices[vertSize + 2] = vertices[2 * vertSize + 2] = vertices[3 * vertSize + 2] = position.z;	//front side
//vertices[4 * vertSize + 2] = vertices[5 * vertSize + 2] = vertices[6 * vertSize + 2] = vertices[7 * vertSize + 2] = position.z - length;	//back side