#include "Cuboid.h"


const unsigned int vertSize = 8;
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
* for each side has 4 values: x-start, x-end, y-s. and y-e. ==> size of array is: 6*4=24
*/
Cuboid::Cuboid(glm::vec3 position, float width, float height, float length, std::string textureName, const float *texCoord) {
	setValues(position, width, height, length, textureName, texCoord);
}

void Cuboid::setValues(glm::vec3 position, float width, float height, float length, std::string textureName, const float *texCoord) {
	vertices = new float[verticesSize];
	indices = new unsigned int[indicesSize];
	this->position = position;
	this->textureName = textureName;
	this->width = width;
	this->height = height;
	this->length = length;

	translation = glm::vec3(0, 0, 0);

	std::cout << "Cuboid position: ";
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
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertSize * sizeof(float), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//vertex normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertSize * sizeof(float), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);



	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	texture = LoadMipmapTexture(GL_TEXTURE0, textureName.c_str());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Cuboid::draw(Shader shader, glm::mat4 model) {

	//model = glm::translate(model, position + translation);

	shader.use();
	model = glm::translate(model, translation);
	model = glm::translate(model, position);
	shader.setMat4("model", model);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader.getID(), "Texture"), 0);


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

//void Cuboid::draw(Shader shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
//	
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glUniform1i(glGetUniformLocation(shader.getID(), "Texture"), 0);
//	model = glm::translate(model, translation);
//	model = glm::translate(model, position);
//
//	shader.use();
//	shader.setMat4("model", model);
//	shader.setMat4("view", view);
//	shader.setMat4("projection", projection);
//
//
//
//	glBindVertexArray(VAO);
//	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//
//}


Cuboid::~Cuboid() {
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
void Cuboid::generateVerticesArray(glm::vec3 position, unsigned int vertSize, const float*texCoord) {
	//front side
	vertices[0] = vertices[3 * vertSize] = -width / 2;
	vertices[vertSize] = vertices[2 * vertSize] = width / 2;
	vertices[1] = vertices[vertSize + 1] = -height / 2;
	vertices[2 * vertSize + 1] = vertices[3 * vertSize + 1] = height / 2;
	vertices[2] = vertices[vertSize + 2] = vertices[2 * vertSize + 2] = vertices[3 * vertSize + 2] = length / 2;
	//texture
	vertices[3] = vertices[3 * vertSize + 3] = texCoord[0];	//x left
	vertices[vertSize + 3] = vertices[2 * vertSize + 3] = texCoord[1];//x right
	vertices[4] = vertices[vertSize + 4] = texCoord[2];//y bottom
	vertices[2 * vertSize + 4] = vertices[3 * vertSize + 4] = texCoord[3];//y top
	//normals
	vertices[5] = vertices[vertSize + 5] = vertices[2 * vertSize + 5] = vertices[3 * vertSize + 5] = 0;	//x
	vertices[6] = vertices[vertSize + 6] = vertices[2 * vertSize + 6] = vertices[3 * vertSize + 6] = 0;	//y
	vertices[7] = vertices[vertSize + 7] = vertices[2 * vertSize + 7] = vertices[3 * vertSize + 7] = 1;	//z


	//back side
	vertices[4 * vertSize] = vertices[7 * vertSize] = -width / 2;
	vertices[5 * vertSize] = vertices[6 * vertSize] = width / 2;
	vertices[4 * vertSize + 1] = vertices[5 * vertSize + 1] = -height / 2;
	vertices[6 * vertSize + 1] = vertices[7 * vertSize + 1] = height / 2;
	vertices[4 * vertSize + 2] = vertices[5 * vertSize + 2] = vertices[6 * vertSize + 2] = vertices[7 * vertSize + 2] = -length / 2;
	//texture
	vertices[4 * vertSize + 3] = vertices[7 * vertSize + 3] = texCoord[4];	//x left
	vertices[5 * vertSize + 3] = vertices[6 * vertSize + 3] = texCoord[5];//x right
	vertices[4 * vertSize + 4] = vertices[5 * vertSize + 4] = texCoord[6];//y bottom
	vertices[6 * vertSize + 4] = vertices[7 * vertSize + 4] = texCoord[7];//y top
	//normals
	vertices[4 * vertSize + 5] = vertices[5 * vertSize + 5] = vertices[6 * vertSize + 5] = vertices[7 * vertSize + 5] = 0;	//x
	vertices[4 * vertSize + 6] = vertices[5 * vertSize + 6] = vertices[6 * vertSize + 6] = vertices[7 * vertSize + 6] = 0;	//y
	vertices[4 * vertSize + 7] = vertices[5 * vertSize + 7] = vertices[6 * vertSize + 7] = vertices[7 * vertSize + 7] = -1;	//z

	//left side
	vertices[8 * vertSize] = vertices[9 * vertSize] = vertices[10 * vertSize] = vertices[11 * vertSize] = -width / 2;
	vertices[8 * vertSize + 1] = vertices[9 * vertSize + 1] = -height / 2;
	vertices[10 * vertSize + 1] = vertices[11 * vertSize + 1] = height / 2;
	vertices[8 * vertSize + 2] = vertices[11 * vertSize + 2] = length / 2;
	vertices[9 * vertSize + 2] = vertices[10 * vertSize + 2] = -length / 2;
	//texture
	vertices[9 * vertSize + 3] = vertices[10 * vertSize + 3] = texCoord[8];	//x left
	vertices[8 * vertSize + 3] = vertices[11 * vertSize + 3] = texCoord[9];//x right
	vertices[8 * vertSize + 4] = vertices[9 * vertSize + 4] = texCoord[10];//y bottom
	vertices[10 * vertSize + 4] = vertices[11 * vertSize + 4] = texCoord[11];//y top
	//normals
	vertices[8 * vertSize + 5] = vertices[9 * vertSize + 5] = vertices[10 * vertSize + 5] = vertices[11 * vertSize + 5] = -1;	//x
	vertices[8 * vertSize + 6] = vertices[9 * vertSize + 6] = vertices[10 * vertSize + 6] = vertices[11 * vertSize + 6] = 0;	//y
	vertices[8 * vertSize + 7] = vertices[9 * vertSize + 7] = vertices[10 * vertSize + 7] = vertices[11 * vertSize + 7] = 0;	//z

	//right side
	vertices[12 * vertSize] = vertices[13 * vertSize] = vertices[14 * vertSize] = vertices[15 * vertSize] = width / 2;
	vertices[12 * vertSize + 1] = vertices[13 * vertSize + 1] = -height / 2;
	vertices[14 * vertSize + 1] = vertices[15 * vertSize + 1] = height / 2;
	vertices[12 * vertSize + 2] = vertices[15 * vertSize + 2] = length / 2;
	vertices[13 * vertSize + 2] = vertices[14 * vertSize + 2] = -length / 2;
	//texture
	vertices[12 * vertSize + 3] = vertices[15 * vertSize + 3] = texCoord[12];	//x left
	vertices[13 * vertSize + 3] = vertices[14 * vertSize + 3] = texCoord[13];//x right
	vertices[12 * vertSize + 4] = vertices[13 * vertSize + 4] = texCoord[14];//y bottom
	vertices[14 * vertSize + 4] = vertices[15 * vertSize + 4] = texCoord[15];//y top
	//normals
	vertices[12 * vertSize + 5] = vertices[13 * vertSize + 5] = vertices[14 * vertSize + 5] = vertices[15 * vertSize + 5] = 1;	//x
	vertices[12 * vertSize + 6] = vertices[13 * vertSize + 6] = vertices[14 * vertSize + 6] = vertices[15 * vertSize + 6] = 0;	//y
	vertices[12 * vertSize + 7] = vertices[13 * vertSize + 7] = vertices[14 * vertSize + 7] = vertices[15 * vertSize + 7] = 0;	//z

	//bottom side
	vertices[16 * vertSize] = vertices[19 * vertSize] = -width / 2;
	vertices[17 * vertSize] = vertices[18 * vertSize] = width / 2;
	vertices[16 * vertSize + 1] = vertices[17 * vertSize + 1] = vertices[18 * vertSize + 1] = vertices[19 * vertSize + 1] = -height / 2;
	vertices[16 * vertSize + 2] = vertices[17 * vertSize + 2] = length / 2;
	vertices[18 * vertSize + 2] = vertices[19 * vertSize + 2] = -length / 2;
	//texture
	vertices[16 * vertSize + 3] = vertices[19 * vertSize + 3] = texCoord[16];	//x left
	vertices[17 * vertSize + 3] = vertices[18 * vertSize + 3] = texCoord[17];//x right
	vertices[18 * vertSize + 4] = vertices[19 * vertSize + 4] = texCoord[18];//y bottom
	vertices[16 * vertSize + 4] = vertices[17 * vertSize + 4] = texCoord[19];//y top
	//normals
	vertices[16 * vertSize + 5] = vertices[17 * vertSize + 5] = vertices[18 * vertSize + 5] = vertices[19 * vertSize + 5] = 0;	//x
	vertices[16 * vertSize + 6] = vertices[17 * vertSize + 6] = vertices[18 * vertSize + 6] = vertices[19 * vertSize + 6] = -1;	//y
	vertices[16 * vertSize + 7] = vertices[17 * vertSize + 7] = vertices[18 * vertSize + 7] = vertices[19 * vertSize + 7] = 0;	//z

	//top side
	vertices[20 * vertSize] = vertices[23 * vertSize] = -width / 2;
	vertices[21 * vertSize] = vertices[22 * vertSize] = width / 2;
	vertices[20 * vertSize + 1] = vertices[21 * vertSize + 1] = vertices[22 * vertSize + 1] = vertices[23 * vertSize + 1] = height / 2;
	vertices[20 * vertSize + 2] = vertices[21 * vertSize + 2] = length / 2;
	vertices[22 * vertSize + 2] = vertices[23 * vertSize + 2] = -length / 2;
	//texture
	vertices[21 * vertSize + 3] = vertices[22 * vertSize + 3] = texCoord[20];	//x left
	vertices[20 * vertSize + 3] = vertices[23 * vertSize + 3] = texCoord[21];//x right
	vertices[22 * vertSize + 4] = vertices[23 * vertSize + 4] = texCoord[22];//y bottom
	vertices[20 * vertSize + 4] = vertices[21 * vertSize + 4] = texCoord[23];//y top
	//normals
	vertices[20 * vertSize + 5] = vertices[21 * vertSize + 5] = vertices[22 * vertSize + 5] = vertices[23 * vertSize + 5] = 0;	//x
	vertices[20 * vertSize + 6] = vertices[21 * vertSize + 6] = vertices[22 * vertSize + 6] = vertices[23 * vertSize + 6] = 1;	//y
	vertices[20 * vertSize + 7] = vertices[21 * vertSize + 7] = vertices[22 * vertSize + 7] = vertices[23 * vertSize + 7] = 0;	//z
}




//vertices[0] = vertices[3 * vertSize] = vertices[4 * vertSize] = vertices[7 * vertSize] = position.x;	//left side
//vertices[vertSize] = vertices[2 * vertSize] = vertices[5 * vertSize] = vertices[6 * vertSize] = position.x + width;	//right side
//vertices[0 + 1] = vertices[vertSize + 1] = vertices[4 * vertSize + 1] = vertices[5 * vertSize + 1] = position.y;	//bottom side
//vertices[2 * vertSize + 1] = vertices[3 * vertSize + 1] = vertices[6 * vertSize + 1] = vertices[7 * vertSize + 1] = position.y + height;	//top side
//vertices[0 + 2] = vertices[vertSize + 2] = vertices[2 * vertSize + 2] = vertices[3 * vertSize + 2] = position.z;	//front side
//vertices[4 * vertSize + 2] = vertices[5 * vertSize + 2] = vertices[6 * vertSize + 2] = vertices[7 * vertSize + 2] = position.z - length;	//back side