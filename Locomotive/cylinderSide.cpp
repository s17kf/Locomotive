#include "cylinderSide.h"

CylinderSide::CylinderSide(glm::vec3 position, float radius, float height, unsigned int pieces, std::string textureName) {
	unsigned int vertSize = 5;
	//unsigned int verticesCount = 6 * pieces;
	//unsigned int indicesCount = 6 * pieces;
	unsigned int verticesCount = 4*pieces;
	indicesCount = 6 * pieces;

	this->radius = radius;
	this->height = height;
	this->pieces = pieces;
	this->positon = position;
	this->textureName = textureName;
	//vertices = new float[pieces * 4 + 2 * (pieces * 2 + 1)];
	//vertices = new float[vertSize*(2 * (pieces * 2 + 1))];
	//vertices = new float[5 * (6 * pieces)];
	//indices = new unsigned int[6 * pieces];
	vertices = new float[5 * verticesCount];
	indices = new unsigned int[indicesCount];

	generateVerticesArray(vertSize);
	generateIndicesArray();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// 0. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5 * (verticesCount), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesCount, indices, GL_STATIC_DRAW);

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

void CylinderSide::draw(Shader &shader) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader.getID(), "Texture"), 0);


	shader.use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void CylinderSide::draw(Shader &shader, unsigned int winWidth, unsigned int winHeight) {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader.getID(), "Texture"), 0);

	


	shader.use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


}

void CylinderSide::generateVerticesArray(unsigned int vertSize) {
	float alpha = glm::radians((float)360.0 / pieces);
	std::cout << "alpha: " << alpha << std::endl;
	//cylinder side
	//front circle
	//for (int i = 0; i < 2 * pieces; i += 2) {
	for (int i = 0; i < 2 * pieces; i += 2) {
		//left vert
		vertices[i*vertSize] = radius*sin(i / 2 * alpha);	//x
		vertices[i*vertSize + 1] = radius*cos(i / 2 * alpha);	//y
		vertices[i*vertSize + 2] = height / 2;	//z
		vertices[i*vertSize + 3] = 0.0;	//tex x
		vertices[i*vertSize + 4] = 0.0;	//tex y
										//right vert
		vertices[(i + 1)*vertSize] = radius*sin((i + 2) / 2 * alpha);	//x
		vertices[(i + 1)*vertSize + 1] = radius*cos((i + 2) / 2 * alpha);	//y
		vertices[(i + 1)*vertSize + 2] = height / 2;	//z
		vertices[(i + 1)*vertSize + 3] = 1.0;	//tex x
		vertices[(i + 1)*vertSize + 4] = 0.0;	//tex y
	}

	//back circle
	//for (int i = 2 * pieces; i < 4 * pieces; i += 2) {
	for (int i = 2 * pieces; i < 4 * pieces; i += 2) {
		//left vert
		vertices[i*vertSize] = radius*sin(i / 2 * alpha);	//x
		vertices[i*vertSize + 1] = radius*cos(i / 2 * alpha);	//y
		vertices[i*vertSize + 2] = -height / 2;	//z
		vertices[i*vertSize + 3] = 0.0;	//tex x
		vertices[i*vertSize + 4] = 1.0;	//tex y
										//right vert
		vertices[(i + 1)*vertSize] = radius*sin((i + 2) / 2 * alpha);	//x
		vertices[(i + 1)*vertSize + 1] = radius*cos((i + 2) / 2 * alpha);	//y
		vertices[(i + 1)*vertSize + 2] = -height / 2;	//z
		vertices[(i + 1)*vertSize + 3] = 1.0;	//tex x
		vertices[(i + 1)*vertSize + 4] = 1.0;	//tex y
	}


}


void CylinderSide::generateIndicesArray() {
	for (int i = 0; i < 6 * pieces; i += 6) {
		indices[i] = i / 3;
		indices[i + 1] = i / 3 + 1;
		indices[i + 2] = 2 * pieces + i / 3 + 1;

		indices[i + 3] = i / 3;
		indices[i + 4] = 2 * pieces + i / 3 + 1;
		indices[i + 5] = 2 * pieces + i / 3;
	}

}

CylinderSide::~CylinderSide() {
	delete[] indices;
	delete[] vertices;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}