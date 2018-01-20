#include "simpleCuboid.h"


const unsigned int vertSize = 3;
const unsigned int verticesSize = vertSize * 24;
const unsigned int indicesSize = 36;

const unsigned int indicesInitializer[] = {
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
SimpleCuboid::SimpleCuboid(glm::vec3 position, float width, float height, float length) {
	setValues(position, width, height, length);
}

void SimpleCuboid::setValues(glm::vec3 position, float width, float height, float length) {
	vertices = new float[verticesSize];
	indices = new unsigned int[indicesSize];
	this->position = position;
	this->textureName = textureName;
	this->width = width;
	this->height = height;
	this->length = length;

	translation = glm::vec3(0, 0, 0);

	std::cout << position.x << " " << position.y << " " << position.z << std::endl;
	std::cout << width << " " << height << " " << length << std::endl;

	generateVerticesArray(glm::vec3(0.0, 0.0, 0.0), vertSize);

	for (int i = 0; i < 36; i++) {
		indices[i] = indicesInitializer[i];
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// 0. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesSize, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesSize, indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertSize * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	// vertex texture coordinates


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void SimpleCuboid::draw(Shader shader, glm::mat4 model) {

	//model = glm::translate(model, position + translation);

	shader.use();
	model = glm::translate(model, translation);
	model = glm::translate(model, position);
	shader.setMat4("model", model);


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


SimpleCuboid::~SimpleCuboid() {
	delete[] vertices;
	delete[] indices;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

/*
* textCoord: {front side, back side, left, right, bottom, top side}
* for each side has two values: x and y ==> size of array is: 6*2=12
*/
void SimpleCuboid::generateVerticesArray(glm::vec3 position, unsigned int vertSize) {
	//front side
	vertices[0] = vertices[3 * vertSize] = position.x - width / 2;
	vertices[vertSize] = vertices[2 * vertSize] = position.x + width / 2;
	vertices[1] = vertices[vertSize + 1] = position.y - height / 2;
	vertices[2 * vertSize + 1] = vertices[3 * vertSize + 1] = position.y + height / 2;
	vertices[2] = vertices[vertSize + 2] = vertices[2 * vertSize + 2] = vertices[3 * vertSize + 2] = position.z + length / 2;

																		  //back side
	vertices[4 * vertSize] = vertices[7 * vertSize] = position.x - width / 2;
	vertices[5 * vertSize] = vertices[6 * vertSize] = position.x + width / 2;
	vertices[4 * vertSize + 1] = vertices[5 * vertSize + 1] = position.y - height / 2;
	vertices[6 * vertSize + 1] = vertices[7 * vertSize + 1] = position.y + height / 2;
	vertices[4 * vertSize + 2] = vertices[5 * vertSize + 2] = vertices[6 * vertSize + 2] = vertices[7 * vertSize + 2] = position.z - length / 2;

																		  //left side
	vertices[8 * vertSize] = vertices[9 * vertSize] = vertices[10 * vertSize] = vertices[11 * vertSize] = position.x - width / 2;
	vertices[8 * vertSize + 1] = vertices[9 * vertSize + 1] = position.y - height / 2;
	vertices[10 * vertSize + 1] = vertices[11 * vertSize + 1] = position.y + height / 2;
	vertices[8 * vertSize + 2] = vertices[11 * vertSize + 2] = position.z + length / 2;
	vertices[9 * vertSize + 2] = vertices[10 * vertSize + 2] = position.z - length / 2;

																			//right side
	vertices[12 * vertSize] = vertices[13 * vertSize] = vertices[14 * vertSize] = vertices[15 * vertSize] = position.x + width / 2;
	vertices[12 * vertSize + 1] = vertices[13 * vertSize + 1] = position.y - height / 2;
	vertices[14 * vertSize + 1] = vertices[15 * vertSize + 1] = position.y + height / 2;
	vertices[12 * vertSize + 2] = vertices[15 * vertSize + 2] = position.z + length / 2;
	vertices[13 * vertSize + 2] = vertices[14 * vertSize + 2] = position.z - length / 2;

																			//bottom side
	vertices[16 * vertSize] = vertices[19 * vertSize] = position.x - width / 2;
	vertices[17 * vertSize] = vertices[18 * vertSize] = position.x + width / 2;
	vertices[16 * vertSize + 1] = vertices[17 * vertSize + 1] = vertices[18 * vertSize + 1] = vertices[19 * vertSize + 1] = position.y - height / 2;
	vertices[16 * vertSize + 2] = vertices[17 * vertSize + 2] = position.z + length / 2;
	vertices[18 * vertSize + 2] = vertices[19 * vertSize + 2] = position.z - length / 2;

																			//top side
	vertices[20 * vertSize] = vertices[23 * vertSize] = position.x - width / 2;
	vertices[21 * vertSize] = vertices[22 * vertSize] = position.x + width / 2;
	vertices[20 * vertSize + 1] = vertices[21 * vertSize + 1] = vertices[22 * vertSize + 1] = vertices[23 * vertSize + 1] = position.y + height / 2;
	vertices[20 * vertSize + 2] = vertices[21 * vertSize + 2] = position.z + length / 2;;
	vertices[22 * vertSize + 2] = vertices[23 * vertSize + 2] = position.z - length / 2;;
}


