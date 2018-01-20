#include "cylinderBases.h"

CylinderBases::CylinderBases(glm::vec3 position, float radius, float height, unsigned int pieces, std::string textureName) {
	unsigned int vertSize = 8;
	//unsigned int verticesCount = 6 * pieces;
	//unsigned int indicesCount = 6 * pieces;
	unsigned int verticesCount = 2 * (pieces * 2 + 1);
	indicesCount = 6 * pieces;

	this->radius = radius;
	this->height = height;
	this->pieces = pieces;
	this->position = position;
	this->textureName = textureName;
	//vertices = new float[pieces * 4 + 2 * (pieces * 2 + 1)];
	//vertices = new float[vertSize*(2 * (pieces * 2 + 1))];
	//vertices = new float[5 * (6 * pieces)];
	//indices = new unsigned int[6 * pieces];
	vertices = new float[vertSize * verticesCount];
	indices = new unsigned int[indicesCount];
	this->rotationX = 0;

	generateVerticesArray(vertSize);
	generateIndicesArray();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// 0. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertSize * (verticesCount), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesCount, indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertSize * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	// vertex texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertSize * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertSize * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
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

void CylinderBases::draw(Shader &shader, glm::mat4 model) {
	model = glm::translate(model, position);
	model = glm::rotate(model, rotationX, glm::vec3(0,0,1));
	shader.setMat4("model", model);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader.getID(), "Texture"), 0);


	shader.use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

//void CylinderBases::draw(Shader &shader, unsigned int winWidth, unsigned int winHeight) {
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glUniform1i(glGetUniformLocation(shader.getID(), "Texture"), 0);
//
//	glm::mat4 model;
//	//model = glm::rotate(model, glm::radians(95.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//	model = glm::translate(model, position);
//	model = glm::translate(model, glm::vec3((float)glfwGetTime() / 20, 0,/* 0*/ (float)glfwGetTime() / 20));
//	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
//	//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//	model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
//
//	glm::mat4 view;
//	// note that we're translating the scene in the reverse direction of where we want to move
//	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//
//	glm::mat4 projection;
//	projection = glm::perspective(glm::radians(45.0f), (GLfloat)winWidth / (GLfloat)winHeight, 0.1f, 100.0f);
//
//
//	shader.setMat4("model", model);
//	shader.setMat4("view", view);
//	shader.setMat4("projection", projection);
//
//	shader.use();
//	glBindVertexArray(VAO);
//	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//
//
//}

void CylinderBases::generateVerticesArray(unsigned int vertSize) {
	float alpha = glm::radians((float)360.0 / pieces);
	std::cout << "alpha: " << alpha << std::endl;
	//front circle
	//circle center
	vertices[0] = vertices[1] = 0;	//x &y
	vertices[2] = height / 2;	//z
	//texture
	vertices[3] = 0.5;
	vertices[4] = 0.0;
	//normal
	vertices[5] = 0;	//x
	vertices[6] = 0;	//y
	vertices[7] = 1;	//z

	//circle
	for (int i = 1; i <= 2 * pieces; i += 2) {
		//left vert
		vertices[i*vertSize] = radius*sin(i / 2 * alpha);	//x
		vertices[i*vertSize + 1] = radius*cos(i / 2 * alpha);	//y
		vertices[i*vertSize + 2] = height / 2;	//z
		vertices[i*vertSize + 3] = 0.0;	//tex x
		vertices[i*vertSize + 4] = 1.0;	//tex y
		vertices[i*vertSize + 5] = 0.0;	//normal x
		vertices[i*vertSize + 6] = 0;	//normal y
		vertices[i*vertSize + 7] = 1.0;	//normal z
										//right vert
		vertices[(i + 1)*vertSize] = radius*sin((i + 1) / 2 * alpha);	//x
		vertices[(i + 1)*vertSize + 1] = radius*cos((i + 1) / 2 * alpha);	//y
		vertices[(i + 1)*vertSize + 2] = height / 2;	//z
		vertices[(i + 1)*vertSize + 3] = 1.0;	//tex x
		vertices[(i + 1)*vertSize + 4] = 1.0;	//tex y
		vertices[(i + 1)*vertSize + 5] = 0;	//normal x
		vertices[(i + 1)*vertSize + 6] = 0;	//normal y
		vertices[(i + 1)*vertSize + 7] = 1;	//normal z
	}

	//back circle
	//circle center
	vertices[(2 * pieces + 1)*vertSize] = vertices[(2 * pieces + 1)*vertSize + 1] = 0;	//x & y
	vertices[(2 * pieces + 1)*vertSize + 2] = -height / 2; //z
	//texture
	vertices[(2 * pieces + 1)*vertSize + 3] = 0.5;
	vertices[(2 * pieces + 1)*vertSize + 4] = 0.0;
	//normal
	vertices[(2 * pieces + 1)*vertSize + 5] = 0;	//x
	vertices[(2 * pieces + 1)*vertSize + 6] = 0;	//y
	vertices[(2 * pieces + 1)*vertSize + 7] = -1;	//z

	//circle
	for (int i = 1; i <= 2 * pieces; i += 2) {
		//left vert
		vertices[(2 * pieces + 1)*vertSize + i*vertSize] = radius*sin(i / 2 * alpha);	//x
		vertices[(2 * pieces + 1)*vertSize + i*vertSize + 1] = radius*cos(i / 2 * alpha);	//y
		vertices[(2 * pieces + 1)*vertSize + i * vertSize + 2] = -height / 2;	//z
		vertices[(2 * pieces + 1)*vertSize + i*vertSize + 3] = 0.0;	//tex x
		vertices[(2 * pieces + 1)*vertSize + i*vertSize + 4] = 1.0;	//tex y
		vertices[(2 * pieces + 1)*vertSize + i * vertSize + 5] = 0;	//normal x
		vertices[(2 * pieces + 1)*vertSize + i * vertSize + 6] = 0;	//normal y
		vertices[(2 * pieces + 1)*vertSize + i * vertSize + 7] = -1;	//normal z
																	//right vert
		vertices[(2 * pieces + 2)*vertSize + i*vertSize] = radius*sin((i + 1) / 2 * alpha);	//x
		vertices[(2 * pieces + 2)*vertSize + i*vertSize + 1] = radius*cos((i + 1) / 2 * alpha);	//y
		vertices[(2 * pieces + 2)*vertSize + i * vertSize + 2] = -height / 2;	//z
		vertices[(2 * pieces + 2)*vertSize + i*vertSize + 3] = 1.0;	//tex x
		vertices[(2 * pieces + 2)*vertSize + i*vertSize + 4] = 1.0;	//tex y
		vertices[(2 * pieces + 2)*vertSize + i * vertSize + 5] = 0;	//normal x
		vertices[(2 * pieces + 2)*vertSize + i * vertSize + 6] = 0;	//normal y
		vertices[(2 * pieces + 2)*vertSize + i * vertSize + 7] = -1;	//normal z
	}


}


void CylinderBases::generateIndicesArray() {
	for (int i = 0; i < 3 * pieces; i += 3) {
		indices[i] = 0;
		indices[i + 1] = 2 * i / 3 + 1;
		indices[i + 2] = 2 * i / 3 + 2;

		indices[3 * pieces + i] = 2 * pieces + 1;
		indices[3 * pieces + i + 1] = 2 * pieces + 1 + 2 * i / 3 + 1;
		indices[3 * pieces + i + 2] = 2 * pieces + 1 + 2 * i / 3 + 2;
	}

}

CylinderBases::~CylinderBases() {
	delete[] indices;
	delete[] vertices;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}