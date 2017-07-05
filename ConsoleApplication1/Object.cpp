#include "Object.h"
#include "glm\glm\glm.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include "glm\glm\glm.hpp"
#include "GL/glew.h"
#include "GL/glut.h"
#include <vector>

Object::Object()
{
	currentAngle = 0.0;
	position = glm::vec3(0, 0, 0);
	
}

using namespace glm;

void Object::InitCube() {
	
	numVertex = 24;
	numIndicies = 12;
	vertex = new float[numVertex * 9];
	indices = new int[numIndicies * 3];

	float tempVertex[] =
	{
		-1.0f, +1.0f, +1.0f,  // 0
		+0.0f, +1.0f, +0.0f,  // Normal
		+1.0f, +0.0f, +0.0f,	// Color
		+1.0f, +1.0f, +1.0f,  // 1
		+0.0f, +1.0f, +0.0f,  // Normal
		+0.0f, +1.0f, +0.0f,	// Color
		+1.0f, +1.0f, -1.0f,  // 2
		+0.0f, +1.0f, +0.0f,  // Normal
		+0.0f, +0.0f, +1.0f,  // Color
		-1.0f, +1.0f, -1.0f,  // 3
		+0.0f, +1.0f, +0.0f,  // Normal
		+1.0f, +1.0f, +1.0f,  // Color
		
		-1.0f, +1.0f, -1.0f,  // 4
		+0.0f, +0.0f, -1.0f,  // Normal
		+1.0f, +0.0f, +1.0f,  // Color
		+1.0f, +1.0f, -1.0f,  // 5
		+0.0f, +0.0f, -1.0f,  // Normal
		+0.0f, +0.5f, +0.2f,  // Color
		+1.0f, -1.0f, -1.0f,  // 6
		+0.0f, +0.0f, -1.0f,  // Normal
		+0.8f, +0.6f, +0.4f,  // Color
		-1.0f, -1.0f, -1.0f,  // 7
		+0.0f, +0.0f, -1.0f,  // Normal
		+0.3f, +1.0f, +0.5f,  // Color
		
		+1.0f, +1.0f, -1.0f,  // 8
		+1.0f, +0.0f, +0.0f,  // Normal
		+0.2f, +0.5f, +0.2f,  // Color
		+1.0f, +1.0f, +1.0f,  // 9
		+1.0f, +0.0f, +0.0f,  // Normal
		+0.9f, +0.3f, +0.7f,  // Color
		+1.0f, -1.0f, +1.0f,  // 10
		+1.0f, +0.0f, +0.0f,  // Normal
		+0.3f, +0.7f, +0.5f,  // Color
		+1.0f, -1.0f, -1.0f,  // 11
		+1.0f, +0.0f, +0.0f,  // Normal
		+0.5f, +0.7f, +0.5f,  // Color
		
		-1.0f, +1.0f, +1.0f,  // 12
		-1.0f, +0.0f, +0.0f,  // Normal
		+0.7f, +0.8f, +0.2f,  // Color
		-1.0f, +1.0f, -1.0f,  // 13
		-1.0f, +0.0f, +0.0f,  // Normal
		+0.5f, +0.7f, +0.3f,  // Color
		-1.0f, -1.0f, -1.0f,  // 14
		-1.0f, +0.0f, +0.0f,  // Normal
		+0.4f, +0.7f, +0.7f,  // Color
		-1.0f, -1.0f, +1.0f,  // 15
		-1.0f, +0.0f, +0.0f,  // Normal
		+0.2f, +0.5f, +1.0f,  // Color
		
		+1.0f, +1.0f, +1.0f,  // 16
		+0.0f, +0.0f, +1.0f,  // Normal
		+0.6f, +1.0f, +0.7f,  // Color
		-1.0f, +1.0f, +1.0f,  // 17
		+0.0f, +0.0f, +1.0f,  // Normal
		+0.6f, +0.4f, +0.8f,  // Color
		-1.0f, -1.0f, +1.0f,  // 18
		+0.0f, +0.0f, +1.0f,  // Normal
		+0.2f, +0.8f, +0.7f,  // Color
		+1.0f, -1.0f, +1.0f,  // 19
		+0.0f, +0.0f, +1.0f,  // Normal
		+0.2f, +0.7f, +1.0f,  // Color
		
		+1.0f, -1.0f, -1.0f,  // 20
		+0.0f, -1.0f, +0.0f,  // Normal
		+0.8f, +0.3f, +0.7f,  // Color
		-1.0f, -1.0f, -1.0f,  // 21
		+0.0f, -1.0f, +0.0f,  // Normal
		+0.8f, +0.9f, +0.5f,  // Color
		-1.0f, -1.0f, +1.0f,  // 22
		+0.0f, -1.0f, +0.0f,  // Normal
		+0.5f, +0.8f, +0.5f,  // Color
		+1.0f, -1.0f, +1.0f,  // 23
		+0.0f, -1.0f, +0.0f,  // Normal
		+0.9f, +1.0f, +0.2f,  // Color
	};
	 int tempIndicies[] = {
		0,   1,  2,  0,  2,  3, // Top
		4,   5,  6,  4,  6,  7, // Front
		8,   9, 10,  8, 10, 11, // Right
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Back
		20, 22, 21, 20, 23, 22, // Bottom
	};
	for (int i = 0; i < numVertex * 9 ; ++i) {
		vertex[i] = tempVertex[i];
	}

	for (int i = 0; i < numIndicies * 3; ++i) {
		indices[i] = tempIndicies[i];
	}
	Mesh_Init();

}
void Object::drawCircle() {
	glutSolidSphere(0.05f, 1, 1);

}
void Object::InitSphere() {
	objectMatrix = mat4(1);
}

void Object::InitTriangle() {
	numVertex = 3;
	numIndicies = 1;
	vertex = new float[numVertex * 9];
	indices = new int[numIndicies * 3];
	float tempVertex[] =
	{
		-1.0f, -1.0f, +0.0f,  // 0
		+0.0f, +0.0f, -1.0f,  // Normal
		+1.0f, +0.0f, +0.0f,	// Color
		+1.0f, -1.0f, +0.0f,  // 1
		+0.0f, +0.0f, -1.0f,  // Normal
		+0.0f, +1.0f, +0.0f,	// Color
		+0.0f, +1.0f, -1.0f,  // 2
		+0.0f, +0.0f, -1.0f,  // Normal
		+0.0f, +0.0f, +1.0f,  // Color
	};
	int tempIndicies[] = {
		0,   1,  2
	};
	for (int i = 0; i < numVertex * 9; ++i) {
		vertex[i] = tempVertex[i];
	}

	for (int i = 0; i < numIndicies * 3; ++i) {
		indices[i] = tempIndicies[i];
	}
	Mesh_Init();
}

void Object::normalize(int a) {
	float len = sqrt(vertex[a * 9 + 3] * vertex[a * 9 + 3] + vertex[a * 9 + 4] * vertex[a * 9 + 4] + vertex[a * 9 + 5] * vertex[a * 9 + 5]);
	vertex[a * 9 + 3] /= len;
	vertex[a * 9 + 4] /= len;
	vertex[a * 9 + 5] /= len;
}
void Object::draw() {
	//glDrawElements(GL_TRIANGLES, 3 * numIndicies, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);

	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, sizeof(float) * 9, 0);
	glNormalPointer(GL_FLOAT, sizeof(float) * 9, ((float*)(sizeof(float) * 3)));
	glColorPointer(3, GL_FLOAT, sizeof(float) * 9, ((float*)(sizeof(float) * 6)));
	
	glDrawElements(GL_TRIANGLES, 3 * numIndicies, GL_UNSIGNED_INT, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);


}

void Object::Mesh_Init() {
	
	//rendering vertecies
	glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertex * 9, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 9 * numVertex, vertex);

	//rendering indices
	glGenBuffers(1, &indexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * numIndicies * 3, indices, GL_STATIC_DRAW);

}

void Object::calcNormals(int a, int b, int c) {
	float vec1X = vertex[b * 9] - vertex[a * 9];
	float vec1Y = vertex[b * 9 + 1] - vertex[a * 9 + 1];
	float vec1Z = vertex[b * 9 + 2] - vertex[a * 9 + 2];

	float vec2X = vertex[c * 9] - vertex[a * 9];
	float vec2Y = vertex[c * 9 + 1] - vertex[a * 9 + 1];
	float vec2Z = vertex[c * 9 + 2] - vertex[a * 9 + 2];

	float vec3X = vec1Y*vec2Z - vec2Y*vec1Z;
	float vec3Y = vec1Z*vec2X - vec2Z*vec1X;
	float vec3Z = vec1X*vec2Y - vec2X*vec1Y;
				
	vertex[a * 9 + 3] += vec3X, vertex[a * 9 + 4] += vec3Y, vertex[a * 9 + 5] += vec3Z;
	vertex[b * 9 + 3] += vec3X, vertex[b * 9 + 4] += vec3Y, vertex[b * 9 + 5] += vec3Z;
	vertex[c * 9 + 3] += vec3X, vertex[c * 9 + 4] += vec3Y, vertex[c * 9 + 5] += vec3Z;
}



void Object::Init(std::string file_name) {
	objectMatrix = glm::mat4(1);

	freopen(file_name.c_str(), "r", stdin);
	std::string OFFstring;
	char offs;
	std::cin >> OFFstring;
	std::cin >> numVertex >> numIndicies >> offs;
	vertex = new float[9 * numVertex];
	indices = new int[3 * numIndicies];
	//std::cout << numVertex << " " << numIndicies << "\n";

	for (int i = 0; i < numVertex; ++i) {
		float x, y, z; std::cin >> x >> y >> z;
		vertex[i * 9] = x, vertex[i * 9 + 1] = y, vertex[i * 9 + 2] = z;
		vertex[i * 9 + 3] = 0, vertex[i * 9 + 4] = 0, vertex[i * 9 + 5] = 0;
		vertex[i * 9 + 6] = 1, vertex[i * 9 + 7] = 0, vertex[i * 9 + 8] = 1; // change this 


	}

	for (int i = 0; i < numIndicies; ++i) {
		int off, a, b, c;
		std::cin >> off >> a >> b >> c;
		indices[i * 3] = a, indices[i * 3 + 1] = b, indices[i * 3 + 2] = c;
		calcNormals(a, b, c);
	}
	for (int i = 0; i < numVertex; ++i) {
		normalize(i);
	}
	Mesh_Init();
}


Object::~Object()
{
	delete indices;
	delete vertex;

}

int forIndicies[100000];



void Object::InitObj(std::string file_name) {
	FILE * file = fopen(file_name.c_str(), "r");
	
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return;		
	}
	numIndicies = 0;
	numVertex = 0;
	std::vector <float> tempV;
	std::vector <float> tempN;
	std::vector <float> tempI;
	

	while (1) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) {
			break;
		}

		if (strcmp(lineHeader, "v") == 0) {
			float a, b, c;				
			fscanf(file, "%f %f %f\n", &a, &b, &c);
			tempV.push_back(a);
			tempV.push_back(b);
			tempV.push_back(c);

		}
		else if (strcmp(lineHeader, "vn") == 0) {
			float a, b, c;
			fscanf(file, "%f %f %f\n", &a, &b, &c);
			tempN.push_back(a);
			tempN.push_back(b);
			tempN.push_back(c);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1 , vertex2 , vertex3;
			unsigned int vertexIndex[3], normalIndex[3], uvIndex[3];
			int matches = 
			
			fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
					&vertexIndex[0], &uvIndex[0], &normalIndex[0],
					&vertexIndex[1], &uvIndex[1], &normalIndex[1],
					&vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			
			
			vertexIndex[0] --;
			vertexIndex[1] --;
			vertexIndex[2] --;
			
			
			normalIndex[0] --;
			normalIndex[1] --;
			normalIndex[2] --;
			
			tempI.push_back(vertexIndex[0]);
			tempI.push_back(vertexIndex[1]);
			tempI.push_back(vertexIndex[2]);
			forIndicies[vertexIndex[0]] = normalIndex[0];
			forIndicies[vertexIndex[1]] = normalIndex[1];
			forIndicies[vertexIndex[2]] = normalIndex[2];				
		}
	}
	
	numVertex = (tempV.size() / 3);
	vertex = new float[numVertex * 9];

	for (int i = 0; i < tempV.size(); i += 3) {
		vertex[i/3 * 9 + 0] = tempV[i + 0];
		vertex[i/3 * 9 + 1] = tempV[i + 1];
		vertex[i/3 * 9 + 2] = tempV[i + 2];

		vertex[i / 3 * 9 + 3] = tempN[forIndicies[i / 3] * 3 + 0];
		vertex[i / 3 * 9 + 4] = tempN[forIndicies[i / 3] * 3 + 1];
		vertex[i / 3 * 9 + 5] = tempN[forIndicies[i / 3] * 3 + 2];

		vertex[i / 3 * 9 + 6] = 0;
		vertex[i / 3 * 9 + 7] = 0;
		vertex[i / 3 * 9 + 8] = 1;
	}

	numIndicies = tempI.size() / 3;
	indices = new int[numIndicies * 3];

	for (int i = 0; i < tempI.size(); i ++) {
		indices[i] = tempI[i];
	}
	Mesh_Init();


}